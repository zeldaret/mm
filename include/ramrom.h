#ifndef _RAMROM_H_
#define _RAMROM_H_

#include <PR/ultratypes.h>

typedef struct {
    /* 0 */ long type;
    /* 4 */ long length;
    /* 8 */ long magic;
    /* 12 */ unsigned char userdata[24564];
} RamRomBuffer;

#endif
