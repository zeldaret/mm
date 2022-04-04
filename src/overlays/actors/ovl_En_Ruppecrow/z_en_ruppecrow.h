#ifndef Z_EN_RUPPECROW_H
#define Z_EN_RUPPECROW_H

#include "global.h"
#include "objects/object_crow/object_crow.h"

#define ENRUPPECROW_GET_PATH(thisx) (((thisx)->params & 0xFC00) >> 0xA)

#define ENRUPPECROW_RUPEE_COUNT 20
#define ENRUPPECROW_LIMB_POS_COUNT 4

struct EnRuppecrow;

typedef void (*EnRuppecrowActionFunc)(struct EnRuppecrow*, GlobalContext*);

typedef struct EnRuppecrow {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnItem00* rupees[ENRUPPECROW_RUPEE_COUNT];
    /* 0x194 */ SkelAnime skelAnime;
    /* 0x1D8 */ EnRuppecrowActionFunc actionFunc;
    /* 0x1DC */ UNK_TYPE4 unk_1DC; // unused
    /* 0x1E0 */ Vec3s joinTable[OBJECT_CROW_LIMB_MAX];
    /* 0x216 */ Vec3s morphTable[OBJECT_CROW_LIMB_MAX];
    /* 0x24C */ Path* path;
    /* 0x250 */ s32 currentPoint;
    /* 0x254 */ ColliderJntSph collider;
    /* 0x274 */ ColliderJntSphElement colliderElement;
    /* 0x2B4 */ u16 isGoingCounterClockwise;
    /* 0x2B8 */ f32 speedModifier;
    /* 0x2BC */ s16 rupeeIndex;
    /* 0x2BE */ s16 yOffset;
    /* 0x2C0 */ UNK_TYPE4 unk_2C0; // unused
    /* 0x2C4 */ u8 currentEffect; 
    /* 0x2C8 */ f32 unk_2C8; // set but not used
    /* 0x2CC */ f32 unk_2CC; // set but not used
    /* 0x2D0 */ f32 iceSfxTimer;
    /* 0x2D4 */ Vec3f limbPos[ENRUPPECROW_LIMB_POS_COUNT];
} EnRuppecrow; // size = 0x304

extern const ActorInit En_Ruppecrow_InitVars;

#endif // Z_EN_RUPPECROW_H
