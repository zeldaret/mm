#ifndef Z_EN_DOOR_ETC_H
#define Z_EN_DOOR_ETC_H

#include "global.h"

struct EnDoorEtc;

typedef void (*EnDoorEtcActionFunc)(struct EnDoorEtc* this, GlobalContext* globalCtx);

typedef struct EnDoorEtc {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0xB4];
    /* 0x01F8 */ EnDoorEtcActionFunc actionFunc;
} EnDoorEtc; // size = 0x1FC

extern const ActorInit En_Door_Etc_InitVars;

#endif // Z_EN_DOOR_ETC_H
