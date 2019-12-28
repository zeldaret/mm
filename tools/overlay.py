#!/usr/bin/env python3
import sys, argparse

from elftools.elf.elffile import ELFFile
from elftools.elf.relocation import RelocationSection

def get_section_type_from_name(name):
    if name == '.text':
        return 1
    elif name == '.data':
        return 2
    elif name == '.rodata':
        return 3
    elif name == '.bss': # TODO is this actually a thing? It doesn't fit in 2 bits and why would there be a relocation in .bss?
        return 4
    else:
        assert False, 'Unrecognized section for relocation: ' + name

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('input', help='Input object file to create overlay info', metavar='input')
    parser.add_argument('output', help='Overlay info output', metavar='output')
    args = parser.parse_args()

    with open(args.input, 'rb') as f, open(args.output, 'w') as out:
        elffile = ELFFile(f)

        out.write('.section .ovl\n');

        relocs = []
        for section in elffile.iter_sections():
            if isinstance(section, RelocationSection):
                symtab = elffile.get_section(section['sh_link'])
                for reloc in section.iter_relocations():
                    symbol = symtab.get_symbol(reloc['r_info_sym'])
                    if symbol.entry['st_shndx'] != 'SHN_UNDEF':
                        section_id = get_section_type_from_name(section.name[4:])
                        relocation_type = reloc['r_info_type']
                        offset = reloc['r_offset']
                        assert offset <= 0xFFFFFF, 'Object too big to convert into overlay'
                        word = (section_id << 30) | (relocation_type << 24) | (offset)
                        relocs.append(word)

        text_section = elffile.get_section_by_name('.text')
        data_section = elffile.get_section_by_name('.data')
        rodata_section = elffile.get_section_by_name('.rodata')
        bss_section = elffile.get_section_by_name('.bss')

        text_size = text_section.data_size if text_section is not None else 0
        data_size = data_section.data_size if data_section is not None else 0
        rodata_size = rodata_section.data_size if rodata_section is not None else 0
        bss_size = bss_section.data_size if bss_section is not None else 0

        out.write('.word 0x{:08X}\n'.format(text_size));
        out.write('.word 0x{:08X}\n'.format(data_size));
        out.write('.word 0x{:08X}\n'.format(rodata_size));
        out.write('.word 0x{:08X}\n'.format(bss_size));
        out.write('.word 0x{:08X}\n'.format(len(relocs)));
        for reloc in relocs:
            out.write('.word 0x{:08X}\n'.format(reloc));
        offset = len(relocs) + 5
        while (offset % 4) != 3:
            out.write('.word 0\n');
            offset += 1
        out.write('.word 0x{:08X}\n'.format(offset*4 + 4));
