#!/usr/bin/env python3

def apply(config, args):
    config['baseimg'] = 'baserom.mm.us.rev1.z64'
    config['myimg'] = 'mm.us.rev1.rom.z64'
    config['mapfile'] = 'build/mm.map'
    config['source_directories'] = ['./src','./include']
