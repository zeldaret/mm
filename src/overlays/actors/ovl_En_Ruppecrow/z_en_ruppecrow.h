#ifndef Z_EN_RUPPECROW_H
#define Z_EN_RUPPECROW_H

#include "global.h"

#define EN_RUPPECROW_RUPEE_COUNT (20)

#define EN_RUPPECROW_SHOULD_CRY(globalCtx) ((globalCtx->state.frames % 43) == 0)

#define EN_RUPPECROW_OSCILLATE_Y_OFFSET(this, addition, multiplier) do { \
        this->unk_2BE += addition; \
        this->actor.shape.yOffset = Math_SinS(this->unk_2BE) * multiplier; \
    } while (false);

#define EN_RUPPECROW_EFFECT_NONE (0)
#define EN_RUPPECROW_EFFECT_ICE (10)
#define EN_RUPPECROW_EFFECT_LIGHT (20)

struct EnRuppecrow;

typedef void (*EnRuppecrowActionFunc)(struct EnRuppecrow*, GlobalContext*);

typedef struct EnRuppecrow {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnItem00* rupees[EN_RUPPECROW_RUPEE_COUNT];
    /* 0x0194 */ SkelAnime skelAnime;
    /* 0x01D8 */ EnRuppecrowActionFunc actionFunc;
    /* 0x01DC */ UNK_TYPE4 unk_1DC; // unused
    /* 0x01E0 */ Vec3s joinTable[9];
    /* 0x0216 */ Vec3s morphTable[9];
    /* 0x024C */ Path* path;
    /* 0x0250 */ s32 pathIndex;
    /* 0x0254 */ ColliderJntSph collider;
    /* 0x0274 */ ColliderJntSphElement colliderElement;
    /* 0x02B4 */ u16 isGoingCounterClockwise;
    /* 0x02B6 */ u16 unk_2B6; // unused upper half of isGoingCounterClockwise bit flag
    /* 0x02B8 */ f32 speedModifier;
    /* 0x02BC */ s16 rupeeIndex;
    /* 0x02BE */ UNK_TYPE2 unk_2BE; // unused
    /* 0x02C0 */ UNK_TYPE4 unk_2C0; // unused
    /* 0x02C4 */ u8 currentEffect; 
    /* 0x02C5 */ UNK_TYPE1 unk_2C5; // unused 
    /* 0x02C6 */ UNK_TYPE1 unk_2C6; // unused
    /* 0x02C7 */ UNK_TYPE1 unk_2C7; // unused
    /* 0x02C8 */ Vec3f unk_2C8;
    /* 0x02D4 */ Vec3f limbPos[4];
} EnRuppecrow; // size = 0x304

extern const ActorInit En_Ruppecrow_InitVars;

#endif // Z_EN_RUPPECROW_H
