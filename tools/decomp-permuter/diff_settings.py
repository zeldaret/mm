#!/usr/bin/env python3

def apply(config, args):
    config['baseimg'] = 'baserom.z64'
    config['myimg'] = 'rom.z64'
    config['mapfile'] = 'build/mm.map'
    config['source_directories'] = ['./src','./include']
