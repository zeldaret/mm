#ifndef Z_EN_DOOR_ETC_H
#define Z_EN_DOOR_ETC_H

#include "global.h"

struct EnDoorEtc;

#define ENDOORETC_GET_SWITCHFLAG(thisx) ((thisx)->params & 0x7F)

typedef void (*EnDoorEtcActionFunc)(struct EnDoorEtc*, PlayState*);

typedef struct EnDoorEtc {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char pad_144[0x5D];
    /* 0x1A1 */ u8 unk_1A1;
    /* 0x1A2 */ s8 objectIndex;
    /* 0x1A3 */ u8 dListIndex; // Never read, inferred from ovl_En_Door
    /* 0x1A4 */ s16 angle;
    /* 0x1A6 */ s16 timer;
    /* 0x1A8 */ ColliderCylinder collider;
    /* 0x1F4 */ u8 unk_1F4;
    /* 0x1F8 */ EnDoorEtcActionFunc actionFunc;
} EnDoorEtc; // size = 0x1FC

#endif // Z_EN_DOOR_ETC_H
