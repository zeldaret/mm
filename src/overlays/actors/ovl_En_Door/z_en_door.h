#ifndef Z_EN_DOOR_H
#define Z_EN_DOOR_H

#include "global.h"

struct EnDoor;

typedef void (*EnDoorActionFunc)(struct EnDoor* this, GlobalContext* globalCtx);

typedef struct EnDoor {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x63];
    /* 0x01A7 */ s8 unk1A7;
    /* 0x01A8 */ char unk_1A8[0x20];
    /* 0x01C8 */ EnDoorActionFunc actionFunc;
} EnDoor; // size = 0x1CC

extern const ActorInit En_Door_InitVars;

#endif // Z_EN_DOOR_H
