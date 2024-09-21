import struct
import os

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
    file.seek(0x38)
    hdr['relocTabNrE'] = read_uint32(file)
    hdr['relocTab'] = read_uint32(file)
    file.seek(0x50)
    hdr['impSymIxs_Rel'] = read_uint32(file)
    hdr['symTab_Rel'] = read_uint32(file)
    hdr['symTabStr_Rel'] = read_uint32(file)
    file.seek(0x64)
    hdr['relocTab_Rel'] = read_uint32(file)
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

def read_string(file, offset):
    file.seek(offset)
    result = bytearray()
    while True:
        char = file.read(1)
        if char == b'\0':
            return result.decode('utf-8')
        result.extend(char)

def get_symbol_info(file, sym_table, sym_str_table, sym_idx):
    sym_offset = sym_table + sym_idx * 0x10
    sym = read_xffSymEnt(file, sym_offset)
    name = read_string(file, sym_str_table + sym['nameOffs'])
    return name if name else "UNKNOWN", sym['addr']

def format_reloc_output(addr, relType, sym_name):
    rom_addr = 0x608 + addr
    reloc_type = {
        4: "MIPS_26",
        5: "MIPS_HI16",
        6: "MIPS_LO16"
    }.get(relType, "UNKNOWN")

    if relType in [4, 5, 6]:
        return f"rom:0x{rom_addr:X} symbol:{sym_name} reloc:{reloc_type}"
    else:
        return None

def extract_reloc_and_symbols(filename):
    with open(filename, 'rb') as file:
        hdr = read_xffEntPntHdr(file)

        if hdr['ident'] != b'xff2':
            print("Not a valid XFF2 file")
            return

        print(f"Number of relocation tables: {hdr['relocTabNrE']}")
        print(f"Number of symbols: {hdr['symTabNrE']}")

        # Extract symbols
        print("\nSymbols:")
        for i in range(hdr['symTabNrE']):
            sym_offset = hdr['symTab_Rel'] + i * 0x10
            sym = read_xffSymEnt(file, sym_offset)
            name = read_string(file, hdr['symTabStr_Rel'] + sym['nameOffs'])
            name = name if name else "UNKNOWN"
            print(f"  Symbol {i}:")
            print(f"    Name: {name}")
            print(f"    Address: 0x{sym['addr']:08X}")
            print(f"    Size: {sym['size']}")
            print(f"    Type: {sym['type']}")
            print(f"    Binding: {sym['bindAttr']}")
            print(f"    Section: {sym['sect']}")

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

            print("\n  Addr Table:")
            for j in range(reloc_entry['nrEnt']):
                addr, relType, tgSymIx = read_xffRelocAddrEnt(file, addr_table_offset + j * 8)
                sym_name, sym_addr = get_symbol_info(file, hdr['symTab_Rel'], hdr['symTabStr_Rel'], tgSymIx)
                # print(f"    Entry {j}: Addr: 0x{addr:08X}, Type: {relType}, SymIdx: {tgSymIx}")
                # print(f"      Symbol: {sym_name}, Address: 0x{sym_addr:08X}")
                formatted_output = format_reloc_output(addr, relType, sym_name)
                if formatted_output:
                    print(f"{formatted_output}")

            # print("\n  Inst Table:")
            # for j in range(reloc_entry['nrEnt']):
            #     inst, relType, tgSymIx = read_xffRelocInstEnt(file, inst_table_offset + j * 8)
            #     sym_name, sym_addr = get_symbol_info(file, hdr['symTab_Rel'], hdr['symTabStr_Rel'], tgSymIx)
            #     print(f"    Entry {j}: Inst: 0x{inst:08X}, Type: {relType}, SymIdx: {tgSymIx}")
            #     print(f"      Symbol: {sym_name}, Address: 0x{sym_addr:08X}")
            #     formatted_output = format_reloc_output(inst, relType, sym_name)
            #     if formatted_output:
            #         print(f"      {formatted_output}")

if __name__ == "__main__":
    filename = "iso/TOOLS/MAPTOOL.XFF"
    if os.path.exists(filename):
        extract_reloc_and_symbols(filename)
    else:
        print(f"File not found: {filename}")