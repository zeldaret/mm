#ifndef Z_EN_DOOR_H
#define Z_EN_DOOR_H

#include "global.h"

struct EnDoor;

typedef void (*EnDoorActionFunc)(struct EnDoor*, GlobalContext*);

typedef struct EnDoor {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x5C];
    /* 0x1A0 */ s8 unk1A0;
    /* 0x1A1 */ s8 unk1A1;
    /* 0x1A2 */ char unk1A2[0x5];
    /* 0x1A7 */ s8 unk1A7;
    /* 0x1A8 */ char unk_1A8[0x20];
    /* 0x1C8 */ EnDoorActionFunc actionFunc;
} EnDoor; // size = 0x1CC

extern const ActorInit En_Door_InitVars;

#endif // Z_EN_DOOR_H
