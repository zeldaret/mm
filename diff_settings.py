#!/usr/bin/env python3
def add_custom_arguments(parser):
    parser.add_argument("-v", "--version", dest="mm_version", help="MM version", default="n64-jp-1.1")

def apply(config, args):
    version = args.mm_version
    config['baseimg'] = f'baseroms/{version}/baserom-decompressed.z64'
    config['myimg'] = f'build/{version}/mm-{version}.z64'
    config['mapfile'] = f'build/{version}/mm-{version}.map'
    config['source_directories'] = ['src', 'include', 'spec']
    config['objdump_flags'] = ['-M','reg-names=32']
    config['makeflags'] = [f'VERSION={version}', 'KEEP_MDEBUG=1', 'WERROR=0', 'OBJDUMP_BUILD=0']
