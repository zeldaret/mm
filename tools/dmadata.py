import os, struct, sys, ast, argparse

def align_up(base, align_to):
    return ((base + align_to - 1) // align_to) * align_to

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('files', help='file list')
    parser.add_argument('out', help='output file')
    parser.add_argument('-l', '--linkscript', help='output linker script for file VROM addresses', metavar='filename')
    parser.add_argument('-u', '--uncompressed', help='build dmadata from only uncompressed files', action='store_true', default=False)
    args = parser.parse_args()

    with open(args.out, 'wb') as dmadata, open(args.files, 'r') as files:
        curr_vrom = 0
        curr_phys = 0
        dmadata_table = ast.literal_eval(files.read())
        linker_info = list()
        for base_file, comp_file, alignment, size_if_missing in dmadata_table:
            try:
                uncompressed = comp_file == ''
                missing = base_file == '' and comp_file == ''
                blank = missing and size_if_missing == 0
                is_dmadata = base_file.endswith('dmadata')

                alignment = max(alignment, 0x10)

                if missing:
                    vrom_size = size_if_missing
                    phys_size = 0
                elif is_dmadata:
                    vrom_size = len(dmadata_table) * 0x10
                    phys_size = vrom_size
                else:
                    vrom_size = os.path.getsize(base_file)
                    if uncompressed or args.uncompressed:
                        phys_size = vrom_size
                    else:
                        phys_size = os.path.getsize(comp_file)

                if blank:
                    vrom_start = 0
                    vrom_end = 0
                else:
                    vrom_start = align_up(curr_vrom, alignment)
                    vrom_end = vrom_start + vrom_size

                if blank:
                    phys_start = 0
                    phys_end = 0
                elif missing:
                    phys_start = 0xFFFFFFFF
                    phys_end = 0xFFFFFFFF
                else:
                    phys_start = align_up(curr_phys, 0x10)
                    phys_end = 0 if uncompressed else phys_start + phys_size

                curr_vrom = align_up(curr_vrom, alignment) + vrom_size
                curr_phys = align_up(curr_phys, 0x10) + phys_size

                dmadata.write(vrom_start.to_bytes(4, 'big'))
                dmadata.write(vrom_end.to_bytes(4, 'big'))
                dmadata.write(phys_start.to_bytes(4, 'big'))
                dmadata.write(phys_end.to_bytes(4, 'big'))

                if base_file != '':
                     linker_info.append((os.path.basename(base_file), vrom_start, vrom_end))
            except:
                print('Error when processing entry ' + base_file)
                sys.exit(1)

        if args.linkscript:
            with open(args.linkscript, 'w') as file:
                for name, vrom_start, vrom_end in linker_info:
                    formatted_name = '_' + name if name[0].isdigit() else name
                    file.write('{}_vrom_start = 0x{:08X};\n'.format(formatted_name, vrom_start))
                    file.write('{}_vrom_end = 0x{:08X};\n'.format(formatted_name, vrom_end))
                    file.write('\n')
