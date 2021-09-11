#ifndef RAMROM_H
#define RAMROM_H

#include "PR/ultratypes.h"

typedef struct {
    /* 0x0 */ long type;
    /* 0x4 */ long length;
    /* 0x8 */ long magic;
    /* 0xC */ unsigned char userdata[24564];
} RamRomBuffer;

#endif
