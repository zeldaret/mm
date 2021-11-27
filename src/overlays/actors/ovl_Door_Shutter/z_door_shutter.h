#ifndef Z_DOOR_SHUTTER_H
#define Z_DOOR_SHUTTER_H

#include "global.h"

struct DoorShutter;

typedef void (*DoorShutterActionFunc)(struct DoorShutter*, GlobalContext*);

typedef struct DoorShutter {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x28];
    /* 0x016C */ DoorShutterActionFunc actionFunc;
} DoorShutter; // size = 0x170

extern const ActorInit Door_Shutter_InitVars;

#endif // Z_DOOR_SHUTTER_H
