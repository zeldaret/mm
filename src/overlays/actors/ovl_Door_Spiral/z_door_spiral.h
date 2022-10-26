#ifndef Z_DOOR_SPIRAL_H
#define Z_DOOR_SPIRAL_H

#include "global.h"

struct DoorSpiral;

typedef void (*DoorSpiralActionFunc)(struct DoorSpiral* this, PlayState* play);

#define DOORSPIRAL_GET_PARAM_FC00(thisx) ((u16) (thisx)->params >> 0xA)
#define DOORSPIRAL_GET_PARAM_0300(thisx) (((thisx)->params >> 8) & 3)
#define DOORSPIRAL_GET_PARAM_0080(thisx) (((thisx)->params >> 7) & 1)

typedef struct DoorSpiral {
    /* 0x000 */ Actor actor;
    /* 0x144 */ u8 unk_144;
    /* 0x145 */ s8 unk_145;
    /* 0x146 */ u8 unk_146;
    /* 0x147 */ u8 unk_147;
    /* 0x148 */ u8 unk_148;
    /* 0x149 */ s8 unk_149;
    /* 0x144 */ s8 unk_14A;
    /* 0x144 */ DoorSpiralActionFunc actionFunc;
} DoorSpiral; // size = 0x150

#endif // Z_DOOR_SPIRAL_H
