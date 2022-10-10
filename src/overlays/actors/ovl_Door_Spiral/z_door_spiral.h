#ifndef Z_DOOR_SPIRAL_H
#define Z_DOOR_SPIRAL_H

#include "global.h"

struct DoorSpiral;

typedef void (*DoorSpiralActionFunc)(struct DoorSpiral* this, PlayState* play);

typedef struct DoorSpiral {
    /* 0x000 */ Actor actor;
    /* 0x144 */ u8 pad144;
    /* 0x145 */ s8 unk145;
    /* 0x146 */ u8 unk146;
    /* 0x147 */ u8 unk147;
    /* 0x148 */ u8 unk148;
    /* 0x149 */ s8 unk149;
    /* 0x144 */ s8 unk_14A;
    /* 0x144 */ DoorSpiralActionFunc actionFunc;
} DoorSpiral; // size = 0x150

extern ActorInit Door_Spiral_InitVars;

#endif // Z_DOOR_SPIRAL_H
