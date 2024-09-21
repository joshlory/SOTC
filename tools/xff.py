import struct
from collections import namedtuple

RelocationTable = namedtuple('RelocationTable', ['type', 'nr_ent', 'sect', 'addr_abs', 'instr_abs', 'addr_rel', 'instr_rel'])
RelocationEntry = namedtuple('RelocationEntry', ['addr', 'ty_ix', 'instr', 'ty_ix2'])

class XFFParser:
    def __init__(self, file_path):
        with open(file_path, 'rb') as f:
            self.data = f.read()
        self.pos = 0

    def read_uint32(self):
        value = struct.unpack('<I', self.data[self.pos:self.pos+4])[0]
        self.pos += 4
        return value

    def seek(self, offset):
        self.pos = offset

    def parse_xff_header(self):
        if self.data[:4] not in [b"xff\x00", b"xff2"]:
            raise ValueError("Invalid XFF signature")

        self.seek(0x38)
        self.count_38 = self.read_uint32()
        self.seek(0x64)
        self.off_64_count_38 = self.read_uint32()

    def parse_hdr5_data(self):
        self.seek(self.off_64_count_38)
        self.hdr5_data = []
        for _ in range(self.count_38):
            entry = struct.unpack('<7I', self.data[self.pos:self.pos+28])
            self.hdr5_data.append(entry)
            self.pos += 28

    def parse_relocation_tables(self):
        print(f"RelocTab NREnt = {self.count_38}")
        print(" RelTabNr type     NrEnt    Sect     addrAbs  InstrAbs AddrRel  InstrRel")

        reloc_tables = []
        for i, entry in enumerate(self.hdr5_data):
            reloc_type, nr_ent, sect, addr_abs, instr_abs = entry[0], entry[1], entry[2], entry[5], entry[6]
            addr_rel = addr_abs & 0xFFFFF
            instr_rel = instr_abs & 0xFFFFF

            reloc_table = RelocationTable(reloc_type, nr_ent, sect, addr_abs, instr_abs, addr_rel, instr_rel)
            reloc_tables.append(reloc_table)

            print(f"{i:9d} {reloc_type:9d} {nr_ent:9d} {sect:9d} {addr_abs:08X} {instr_abs:08X} {addr_rel:8X} {instr_rel:8X}")

        return reloc_tables

    def parse_relocation_entries(self, reloc_tables):
        for i, table in enumerate(reloc_tables):
            print(f"\n RELOC TAB {i} : ##################")
            print("Nr    addr     tyIx      instr    tyIx")

            if table.nr_ent == 0:
                continue

            self.seek(table.addr_abs)  # Move to the start of this relocation table
            for j in range(table.nr_ent):
                addr = self.read_uint32()
                ty_ix = self.read_uint32()
                instr = self.read_uint32()
                ty_ix2 = self.read_uint32()

                entry = RelocationEntry(addr, ty_ix, instr, ty_ix2)
                print(f"{j:3d} {entry.addr:08X} {entry.ty_ix:08X} {entry.instr:08X} {entry.ty_ix2:08X}")

    def parse(self):
        self.parse_xff_header()
        self.parse_hdr5_data()
        reloc_tables = self.parse_relocation_tables()
        self.parse_relocation_entries(reloc_tables)

# Usage
if __name__ == "__main__":
    parser = XFFParser("iso/KERNEL.XFF")
    parser.parse()
