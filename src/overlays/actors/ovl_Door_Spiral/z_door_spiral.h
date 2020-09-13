#ifndef Z_DOOR_SPIRAL_H
#define Z_DOOR_SPIRAL_H

#include <global.h>

struct DoorSpiral;

typedef struct DoorSpiral {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xC];
} DoorSpiral; // size = 0x150

extern const ActorInit Door_Spiral_InitVars;

#endif // Z_DOOR_SPIRAL_H
