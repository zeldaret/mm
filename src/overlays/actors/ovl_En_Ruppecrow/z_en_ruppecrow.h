#ifndef Z_EN_RUPPECROW_H
#define Z_EN_RUPPECROW_H

#include "global.h"

#define EN_RUPPECROW_RUPEE_COUNT (20)
#define EN_RUPPECROW_LIMB_COUNT (9)
#define EN_RUPPECROW_LIMB_POS_COUNT (4)

#define EN_RUPPECROW_SHOULD_CRY(globalCtx) ((globalCtx->state.frames % 43) == 0)

#define EN_RUPPECROW_OSCILLATE_Y_OFFSET(this, addition, multiplier) do { \
        this->yOffset += addition; \
        this->actor.shape.yOffset = Math_SinS(this->yOffset) * multiplier; \
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
    /* 0x01E0 */ Vec3s joinTable[EN_RUPPECROW_LIMB_COUNT];
    /* 0x0216 */ Vec3s morphTable[EN_RUPPECROW_LIMB_COUNT];
    /* 0x024C */ Path* path;
    /* 0x0250 */ s32 pathIndex;
    /* 0x0254 */ ColliderJntSph collider;
    /* 0x0274 */ ColliderJntSphElement colliderElement;
    /* 0x02B4 */ u16 isGoingCounterClockwise;
    /* 0x02B6 */ u16 unk_2B6; // unused upper half of isGoingCounterClockwise bit flag
    /* 0x02B8 */ f32 speedModifier;
    /* 0x02BC */ s16 rupeeIndex;
    /* 0x02BE */ s16 yOffset;
    /* 0x02C0 */ UNK_TYPE4 unk_2C0; // unused
    /* 0x02C4 */ u8 currentEffect; 
    /* 0x02C5 */ UNK_TYPE1 unk_2C5; // unused 
    /* 0x02C6 */ UNK_TYPE1 unk_2C6; // unused
    /* 0x02C7 */ UNK_TYPE1 unk_2C7; // unused
    /* 0x02C8 */ f32 unk_2C8; // used but seems to have no effect
    /* 0x02CC */ f32 unk_2CC; // used but seems to have no effect
    /* 0x02D0 */ f32 unk_2D0;
    /* 0x02D4 */ Vec3f limbPos[EN_RUPPECROW_LIMB_POS_COUNT];
} EnRuppecrow; // size = 0x304

extern const ActorInit En_Ruppecrow_InitVars;

#endif // Z_EN_RUPPECROW_H
