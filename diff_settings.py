#!/usr/bin/env python3

def apply(config, args):
    config['baseimg'] = 'rom_uncompressed_match.z64'
    config['myimg'] = 'rom_uncompressed.z64'
    config['mapfile'] = 'build/mm.map'
    config['source_directories'] = ['./src','./include']
