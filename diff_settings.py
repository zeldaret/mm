#!/usr/bin/env python3

def apply(config, args):
    config['baseimg'] = 'baseroms/us/baserom-decompressed.z64'
    config['myimg'] = 'build/us/mm-us.z64'
    config['mapfile'] = 'build/us/mm-us.map'
    config['source_directories'] = ['./src','./include']
    config['objdump_flags'] = ['-M','reg-names=32']
    config['makeflags'] = ['KEEP_MDEBUG=1']
