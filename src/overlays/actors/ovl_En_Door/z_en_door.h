#ifndef Z_EN_DOOR_H
#define Z_EN_DOOR_H

#include <global.h>

struct EnDoor;

typedef struct EnDoor {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x5D];
    /* 0x1A1 */ u8 opening;
    /* 0x1A2 */ char unk_1A2[0x2A];
} EnDoor; // size = 0x1CC

extern const ActorInit En_Door_InitVars;

#endif // Z_EN_DOOR_H
