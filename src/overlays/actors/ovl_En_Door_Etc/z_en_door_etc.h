#ifndef Z_EN_DOOR_ETC_H
#define Z_EN_DOOR_ETC_H

#include <global.h>

struct EnDoorEtc;

typedef struct EnDoorEtc {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xB8];
} EnDoorEtc; // size = 0x1FC

extern const ActorInit En_Door_Etc_InitVars;

#endif // Z_EN_DOOR_ETC_H
