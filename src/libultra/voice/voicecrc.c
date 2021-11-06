#include "global.h"

u8 __osVoiceContDataCrc(u8* data, u32 arg1) {
    u32 bit;
    u32 byte;
    u32 ret = 0;

    for (byte = arg1; byte > 0; byte--) {
        for (bit = 0x80; bit > 0; bit >>= 1) {
            ret <<= 1;
            if (*data & bit) {
                if (ret & 0x100) {
                    ret ^= 0x84;
                } else {
                    ret++;
                }
            } else if (ret & 0x100) {
                ret ^= 0x85;
            }
        }
        data++;
    }

    do {
        ret <<= 1;
        if (ret & 0x100) {
            ret ^= 0x85;
        }
        byte++;
    } while (byte < 8);

    return ret;
}
