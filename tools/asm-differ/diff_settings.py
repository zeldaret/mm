#!/usr/bin/env python3

def apply(config, args):
    config['baseimg'] = 'target.bin'
    config['myimg'] = 'source.bin'
    config['mapfile'] = 'build.map'
    config['source_directories'] = ['.']
