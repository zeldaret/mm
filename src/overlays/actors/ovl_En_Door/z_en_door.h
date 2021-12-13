#ifndef Z_EN_DOOR_H
#define Z_EN_DOOR_H

#include "global.h"

struct EnDoor;

typedef void (*EnDoorActionFunc)(struct EnDoor*, GlobalContext*);

typedef struct EnDoor {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ SkelAnime skelAnime;                   /* inferred */
    /* 0x1A0 */ u8 animIndex;
    /* 0x1A1 */ u8 unk1A1;
    /* 0x1A2 */ s8 requiredObjBankIndex;                          /* inferred */
    /* 0x1A3 */ u8 dlIndex;                          /* inferred */
    /* 0x1A4 */ u8 unk1A4;                          /* inferred */
    /* 0x1A5 */ u8 switchFlag;                          /* inferred */
    /* 0x1A6 */ u8 unk1A6;
    /* 0x1A7 */ s8 unk_1A7;
    /* 0x1A8 */ Vec3s limbTable[5];                       /* inferred */
    ///* 0x1AE */ char pad1AE[0x1A];                  /* maybe part of unk1A8[5]? */
    /* 0x1C8 */ EnDoorActionFunc actionFunc;
} EnDoor;     

extern const ActorInit En_Door_InitVars;

#endif // Z_EN_DOOR_H
