#ifndef Z_DOOR_SPIRAL_H
#define Z_DOOR_SPIRAL_H

#include "global.h"

struct DoorSpiral;

typedef struct DoorSpiral {
    /* 0x000 */ Actor actor;
    /* 0x144 */ u8 shouldClimb;
    /* 0x145 */ UNK_TYPE1 unk_145[0x3];
    /* 0x148 */ UNK_TYPE1 unk_148[0x8];
} DoorSpiral; // size = 0x150

#endif // Z_DOOR_SPIRAL_H
