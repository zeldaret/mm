#ifndef Z_EN_DOOR_H
#define Z_EN_DOOR_H

#include "global.h"

struct EnDoor;

typedef void (*EnDoorActionFunc)(struct EnDoor*, GlobalContext*);

#define ENDOOR_GET_PARAMS_7(thisx) (((thisx)->params >> 7) & 7)
#define ENDOOR_GET_PARAMS_7F(thisx) (((thisx)->params) & 0x7F)


typedef struct EnDoor {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ SkelAnime skelAnime;
    /* 0x1A0 */ u8 animIndex;
    /* 0x1A1 */ u8 unk_1A1;
    /* 0x1A2 */ s8 requiredObjBankIndex;
    /* 0x1A3 */ s8 dlIndex;
    /* 0x1A4 */ u8 unk_1A4;
    /* 0x1A5 */ u8 switchFlag;
    /* 0x1A6 */ u8 unk_1A6;
    /* 0x1A7 */ s8 unk_1A7;
    /* 0x1A8 */ Vec3s limbTable[5];
    /* 0x1C8 */ EnDoorActionFunc actionFunc;
} EnDoor;

extern const ActorInit En_Door_InitVars;

#endif // Z_EN_DOOR_H
