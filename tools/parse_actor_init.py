#!/usr/bin/env python3
# TODO generalize

data = [
    0xC8580005,
    0xB874FE0C,
    0x801F0002,
    0x30540FA0
]

last_continue = True
for entry in data:
    if not last_continue:
        print('Error: entries after entry without continue bit')

    value = entry & 0xFFFF
    offset = (entry >> 16) & 0x7FF
    type = (entry >> 27) & 0xF
    _continue = (entry >> 31) & 0x1

    # convert to signed short
    if value >= 0x8000:
        value -= 0x10000

    # TODO which ones are signed?
    print('0x{:X}: '.format(offset), end='')
    if type == 0:
        print('char {}'.format(value))
    elif type == 1:
        print('char {}'.format(value))
    elif type == 2:
        print('short {}'.format(value))
    elif type == 3:
        print('short {}'.format(value))
    elif type == 4:
        print('int {}'.format(value))
    elif type == 5:
        print('int {}'.format(value))
    elif type == 6:
        print('float {:f}'.format(value))
    elif type == 7:
        print('float {:f}'.format(value / 1000))
    elif type == 8:
        print('Vector3f ({0:f}, {0:f}, {0:f})'.format(value))
    elif type == 9:
        value /= 1000
        print('Vector3f ({0:f}, {0:f}, {0:f})'.format(value))
    elif type == 10:
        print('Vector3f ({0}, {0}, {0})'.format(value))
    else:
        print('Error: invalid type ' + str(value))

    if not _continue:
        print('END')

    last_continue = _continue

