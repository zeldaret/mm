import os
import struct
import sys

OUT = 'build/baserom/dmadata'

from dmadata_table import *

def align_up(base, align_to):
    return ((base + align_to - 1) // align_to) * align_to

if __name__ == "__main__":
    with open(OUT, 'wb') as dmadata:
        curr_vrom = 0
        curr_phys = 0
        for base_file, comp_file, alignment, size_if_missing in dmadata_table:
            try:
                uncompressed = comp_file == ''
                missing = base_file == '' and comp_file == ''
                blank = missing and size_if_missing == 0
                is_dmadata = base_file == 'dmadata'

                alignment = max(alignment, 0x10)

                if missing:
                    vrom_size = size_if_missing
                    phys_size = 0
                elif is_dmadata:
                    vrom_size = len(dmadata_table) * 0x10
                    phys_size = vrom_size
                else:
                    vrom_size = os.path.getsize(base_file)
                    if uncompressed:
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
            except:
                print('Error when processing entry ' + base_file)
                sys.exit(1)
