#!/usr/bin/env python3

import os
import sys
import struct
import argparse
import re
from actor_symbols import resolve_symbol

ICHAIN_MACROS = [
    'ICHAIN_U8',
    'ICHAIN_S8',
    'ICHAIN_U16',
    'ICHAIN_S16',
    'ICHAIN_U32',
    'ICHAIN_S32',
    'ICHAIN_F32',
    'ICHAIN_F32_DIV1000',
    'ICHAIN_VEC3F',
    'ICHAIN_VEC3F_DIV1000',
    'ICHAIN_VEC3S',
]

Z64_ACTOR_PATH = "../../include/z64actor.h"

def get_actor_var_names():
    in_actor = False
    actor_vars = {}
    with open(os.path.dirname(os.path.realpath(__file__)) + os.sep + Z64_ACTOR_PATH) as actor_h:
        for line in actor_h:
            if in_actor:
                if "}" in line:
                    # Reached the end of the actor struct so break out
                    break
                
                # Parse out the memory address (from the comment) and the variable name
                regex = r'.*\/\* (.*) \*\/\s+(struct)?\s*.+\s+(.+);.*'
                actor_var_info = re.match(regex, line)

                if actor_var_info:
                    # Strip off the 0x0* part and store it
                    new_var_index = re.sub('0x0*', '', actor_var_info[1])
                    actor_vars[new_var_index] = actor_var_info[3]

            elif "typedef struct Actor {" in line:
                # Found the Actor struct
                in_actor = True
    return actor_vars

def HexParse(s):
    return int(s, 16)

def main():
    parser = argparse.ArgumentParser(description='Decompiles an InitChain')
    parser.add_argument('address', help='VRAM or VROM address of an InitChain', type=HexParse)
    parser.add_argument('--offsets', action="store_true", help='Use offsets as variable names.')
    args = parser.parse_args()

    file_path, file_offset = resolve_symbol(args.address)

    with open(file_path, 'rb') as f:
        filedata = f.read()

    print ('static InitChainEntry sInitChain[] = {')
    
    actor_variable_names = get_actor_var_names()

    while True:
        entry = struct.unpack('>I', filedata[file_offset:file_offset+4])[0]
        file_offset += 4

        cont = entry >> 31
        t = (entry >> 27) & 0xF
        offset = ((entry) >> 16) & 0x7FF
        value = (entry) & 0xFFFF
        if value >= 0x8000 and not ICHAIN_MACROS[t].startswith('ICHAIN_U'):
            value -= 0x10000

        var_name = '{0:X}'.format(offset)

        if args.offsets:
            var_name = "unk" + var_name
        elif var_name in actor_variable_names:
            var_name = actor_variable_names[var_name]
        
        print('    {0}({1}, {2}, {3}),'.format(ICHAIN_MACROS[t], var_name, value, ('ICHAIN_CONTINUE' if cont == 1 else 'ICHAIN_STOP')))
        if cont == 0:
            break
    print ('};')

if __name__ == "__main__":
    main()
