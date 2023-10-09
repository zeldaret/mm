#ifndef Z_DOOR_SPIRAL_H
#define Z_DOOR_SPIRAL_H

#include "global.h"

struct DoorSpiral;

typedef void (*DoorSpiralActionFunc)(struct DoorSpiral*, PlayState*);

#define DOORSPIRAL_GET_FC00(thisx) ((u16)(thisx)->params >> 0xA)
#define DOORSPIRAL_GET_TYPE(thisx) (((thisx)->params >> 8) & 0x3)
#define DOORSPIRAL_GET_80(thisx) (((thisx)->params >> 7) & 0x1)

typedef struct DoorSpiral {
    /* 0x000 */ Actor actor;
    /* 0x144 */ u8 shouldClimb;
    /* 0x145 */ s8 unk145;
    /* 0x146 */ u8 unk146;
    /* 0x147 */ u8 unk147;
    /* 0x148 */ u8 unk148;
    /* 0x149 */ s8 objIndex;
    /* 0x14A */ s8 unk14A;
    /* 0x14B */ s8 unk14B;
    /* 0x14C */ DoorSpiralActionFunc actionFunc;
} DoorSpiral; // size = 0x150

#endif // Z_DOOR_SPIRAL_H
