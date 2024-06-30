#!/usr/bin/env python3

def apply(config, args):
    config['baseimg'] = 'baseroms/n64-us/baserom-decompressed.z64'
    config['myimg'] = 'build/n64-us/mm-n64-us.z64'
    config['mapfile'] = 'build/n64-us/mm-n64-us.map'
    config['source_directories'] = ['./src','./include']
    config['objdump_flags'] = ['-M','reg-names=32']
    config['makeflags'] = ['KEEP_MDEBUG=1', 'WERROR=0', 'OBJDUMP_BUILD=0']
