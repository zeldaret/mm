#ifndef _Z_DOOR_WARP1_H_
#define _Z_DOOR_WARP1_H_

#include <global.h>

struct DoorWarp1;

typedef struct DoorWarp1 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xC8];
} DoorWarp1; // size = 0x20C

extern const ActorInit Door_Warp1_InitVars;

#endif
