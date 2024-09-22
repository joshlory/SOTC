import struct
import os
import sys

VRAM = 0x40010000

def read_uint32(file):
    return struct.unpack('<I', file.read(4))[0]

def read_uint8(file):
    return struct.unpack('B', file.read(1))[0]

def read_xffEntPntHdr(file):
    file.seek(0)
    hdr = {}
    hdr['ident'] = file.read(4)
    file.seek(0x1C)
    hdr['impSymIxsNrE'] = read_uint32(file)
    hdr['impSymIxs'] = read_uint32(file)
    hdr['symTabNrE'] = read_uint32(file)
    hdr['symTab'] = read_uint32(file)
    hdr['symTabStr'] = read_uint32(file)
    hdr['sectTab'] = read_uint32(file)
    file.seek(0x38)
    hdr['relocTabNrE'] = read_uint32(file)
    hdr['relocTab'] = read_uint32(file)
    hdr['sectNrE'] = read_uint32(file)
    file.seek(0x50)
    hdr['impSymIxs_Rel'] = read_uint32(file)
    hdr['symTab_Rel'] = read_uint32(file)
    hdr['symTabStr_Rel'] = read_uint32(file)
    hdr['sectTab_Rel'] = read_uint32(file)
    file.seek(0x64)
    hdr['relocTab_Rel'] = read_uint32(file)
    hdr['ssNamesOffs_Rel'] = read_uint32(file)
    hdr['ssNamesBase_Rel'] = read_uint32(file)
    return hdr

def read_xffRelocEnt(file, offset):
    file.seek(offset)
    entry = {}
    entry['type'] = read_uint32(file)
    entry['nrEnt'] = read_uint32(file)
    entry['sect'] = read_uint32(file)
    entry['addr'] = read_uint32(file)
    entry['inst'] = read_uint32(file)
    entry['addr_Rel'] = read_uint32(file)
    entry['inst_Rel'] = read_uint32(file)
    return entry

def read_xffRelocAddrEnt(file, offset):
    file.seek(offset)
    addr = read_uint32(file)
    tyIx = read_uint32(file)
    return addr, tyIx & 0xFF, tyIx >> 8

def read_xffRelocInstEnt(file, offset):
    file.seek(offset)
    instr = read_uint32(file)
    unk = read_uint32(file)
    return instr, unk

def read_xffSymEnt(file, offset):
    file.seek(offset)
    entry = {}
    entry['nameOffs'] = read_uint32(file)
    entry['addr'] = read_uint32(file)
    entry['size'] = read_uint32(file)
    info = read_uint8(file)
    entry['type'] = info & 0xF
    entry['bindAttr'] = info >> 4
    entry['unk0D'] = read_uint8(file)
    entry['sect'] = struct.unpack('<H', file.read(2))[0]
    return entry

def read_xffSectEnt(file, offset):
    file.seek(offset)
    entry = {}
    entry['memPt'] = read_uint32(file)
    entry['filePt'] = read_uint32(file)
    entry['size'] = read_uint32(file)
    entry['align'] = read_uint32(file)
    entry['type'] = read_uint32(file)
    entry['flags'] = read_uint32(file)
    entry['moved'] = read_uint32(file)
    entry['offs_Rel'] = read_uint32(file)
    return entry

def read_string(file, offset):
    file.seek(offset)
    result = bytearray()
    while True:
        char = file.read(1)
        if char == b'\0':
            return result.decode('utf-8')
        result.extend(char)

def get_symbol_info(file, sym_table, sym_str_table, sym_idx, section_names):
    sym_offset = sym_table + sym_idx * 0x10
    sym = read_xffSymEnt(file, sym_offset)
    name = read_string(file, sym_str_table + sym['nameOffs'])
    return name if name else section_names[sym['sect']], sym['addr']

def format_reloc_output(addr, relType, sym_name, text_offs_rel):
    rom_addr = text_offs_rel + addr
    reloc_type = {
        4: "MIPS_26",
        5: "MIPS_HI16",
        6: "MIPS_LO16"
    }.get(relType)

    if relType in [4, 5, 6]:
        return f"rom:0x{rom_addr:X} symbol:{sym_name} reloc:{reloc_type}"
    else:
        return None

def extract_reloc_and_symbols(filename):
    xff_name = os.path.splitext(os.path.basename(filename))[0].lower()
    relocs_output_file = os.path.join("config", f"{xff_name}.relocs.txt")
    symbols_output_file = os.path.join("config", f"{xff_name}.symbols.txt")

    with open(filename, 'rb') as file, open(relocs_output_file, 'w') as relocs_out, open(symbols_output_file, 'w') as symbols_out:
        hdr = read_xffEntPntHdr(file)

        if hdr['ident'] != b'xff2':
            print("Not a valid XFF2 file")
            return

        print(f"Number of relocation tables: {hdr['relocTabNrE']}")
        print(f"Number of symbols: {hdr['symTabNrE']}")
        print(f"Number of sections: {hdr['sectNrE']}")

        # Extract section headers
        print("\nSection Headers:")
        print("  memAbs   fileAbs  size     align    type     flags    moved    addrR")
        section_names = {}
        section_offsets = {}
        text_offs_rel = None
        for i in range(hdr['sectNrE']):
            sect_offset = hdr['sectTab_Rel'] + i * 0x20
            sect = read_xffSectEnt(file, sect_offset)
            file.seek(hdr['ssNamesOffs_Rel'] + i * 4)
            name_offset = read_uint32(file)
            section_names[i] = read_string(file, hdr['ssNamesBase_Rel'] + name_offset)
            section_offsets[i] = sect['offs_Rel']
            print(f"{i:2X} {section_names[i]}")
            print(f"{sect['memPt']:8X} {sect['filePt']:8X} {sect['size']:8X} {sect['align']:8X} {sect['type']:8X} {sect['flags']:8X} {sect['moved']:8X} {sect['offs_Rel']:8X}")

            if section_names[i] == '.text':
                text_offs_rel = sect['offs_Rel']

        # Extract symbols
        print("\nSymbols:")
        for i in range(hdr['symTabNrE']):
            sym_offset = hdr['symTab_Rel'] + i * 0x10
            sym = read_xffSymEnt(file, sym_offset)
            name = read_string(file, hdr['symTabStr_Rel'] + sym['nameOffs'])
            name = name if name else f"UNKNOWN_{i}"

            # Calculate the actual address by adding the section offset
            actual_address = sym['addr'] + section_offsets.get(sym['sect'], 0)

            print(f"  Symbol {i}:")
            print(f"    Name: {name}")
            print(f"    Address: 0x{sym['addr']:08X}")
            print(f"    Size: {sym['size']}")
            print(f"    Type: {sym['type']}")
            print(f"    Binding: {sym['bindAttr']}")
            print(f"    Section: {sym['sect']}")

            if sym['sect'] != 0 and sym['bindAttr'] != 0:
                # Write symbol information to the symbols output file
                symbols_out.write(f"{name} = 0x{(VRAM + actual_address):X};\n")

        # Extract relocation tables
        for i in range(hdr['relocTabNrE']):
            reloc_entry_offset = hdr['relocTab_Rel'] + i * 0x1C
            reloc_entry = read_xffRelocEnt(file, reloc_entry_offset)

            print(f"\nRelocation Table {i}:")
            print(f"  Type: {reloc_entry['type']}")
            print(f"  Number of entries: {reloc_entry['nrEnt']}")
            print(f"  Section: {reloc_entry['sect']}")

            addr_table_offset = reloc_entry['addr_Rel']
            inst_table_offset = reloc_entry['inst_Rel']

            for j in range(reloc_entry['nrEnt']):
                addr, relType, tgSymIx = read_xffRelocAddrEnt(file, addr_table_offset + j * 8)
                instr, unk = read_xffRelocInstEnt(file, inst_table_offset + j * 8)
                if relType == 4 and tgSymIx == 1:
                    func_offset = (instr & 0x3FFFFFF) * 4
                    sym_name = f"func_{VRAM + text_offs_rel + func_offset:08X}"
                else:
                    sym_name, sym_addr = get_symbol_info(file, hdr['symTab_Rel'], hdr['symTabStr_Rel'], tgSymIx, section_names)
                    if relType == 6 and sym_name.startswith('.'):
                        sym_name = sym_name + '+0x' + format(instr & 0xFFFF, 'X')
                formatted_output = format_reloc_output(addr, relType, sym_name, text_offs_rel)
                if formatted_output:
                    relocs_out.write(f"{formatted_output}\n")

        print(f"\nRelocation information has been written to {relocs_output_file}")
        print(f"Symbol information has been written to {symbols_output_file}")

def main(args):
    if len(args) < 1:
        print("Usage: python parse_xff_relocs.py <filename>")
        return

    filename = args[0]
    if os.path.exists(filename):
        extract_reloc_and_symbols(filename)
    else:
        print(f"File not found: {filename}")

if __name__ == "__main__":
    main(sys.argv[1:])
