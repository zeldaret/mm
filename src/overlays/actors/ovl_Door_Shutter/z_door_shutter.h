#ifndef Z_DOOR_SHUTTER_H
#define Z_DOOR_SHUTTER_H

#include "global.h"

struct DoorShutter;

typedef struct DoorShutter {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x2C];
} DoorShutter; // size = 0x170

extern const ActorInit Door_Shutter_InitVars;

#endif // Z_DOOR_SHUTTER_H
