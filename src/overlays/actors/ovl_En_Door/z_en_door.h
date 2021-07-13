#ifndef Z_EN_DOOR_H
#define Z_EN_DOOR_H

#include <global.h>

struct EnDoor;

typedef struct EnDoor {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x63];
    /* 0x1A7 */ s8 unk1A7;
    /* 0x1A8 */ char unk_1A8[0x24];
} EnDoor; // size = 0x1CC

extern const ActorInit En_Door_InitVars;

#endif // Z_EN_DOOR_H
