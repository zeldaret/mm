#ifndef Z_DM_STK_H
#define Z_DM_STK_H

#include "global.h"

struct DmStk;

typedef void (*DmStkActionFunc)(struct DmStk*, GlobalContext*);

typedef struct DmStk {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ UNK_TYPE1 unk_188[0x108];
    /* 0x0290 */ DmStkActionFunc actionFunc;
    /* 0x0294 */ ColliderCylinder collider;
    /* 0x02E0 */ s16 animationId;
    /* 0x02E4 */ s32 alpha;
    /* 0x02E8 */ u32 fogR;
    /* 0x02EC */ u32 fogG;
    /* 0x02F0 */ u32 fogB;
    /* 0x02F4 */ s32 fogA;
    /* 0x02F8 */ s32 fogN;
    /* 0x02FC */ s32 fogF;
    /* 0x0300 */ f32 fogScale;
    /* 0x0304 */ Vec3f headPos; // set but never used
    /* 0x0310 */ Vec3f soundPos; // only used for Skull Kid's voice sfx in the cutscene after Oath to Order is played
    /* 0x031C */ UNK_TYPE1 unk31C[0xC];
    /* 0x0328 */ u16 tatlMessageTimer;
    /* 0x032A */ u16 bobPhase;
    /* 0x032C */ u8 maskType;
    /* 0x032D */ u8 handType;
    /* 0x032E */ u8 fadeInState;
    /* 0x032F */ u8 fadeOutState;
    /* 0x0330 */ s32 fadeOutTimer;
    /* 0x0334 */ u8 csAction;
    /* 0x0335 */ u8 unk_335; // set but never used
    /* 0x0336 */ s8 objectStkObjectIndex;
    /* 0x0337 */ s8 objectStk2ObjectIndex;
    /* 0x0338 */ s8 objectStk3ObjectIndex;
    /* 0x0339 */ u8 hitCount;
    /* 0x033A */ u8 unk_33A;
    /* 0x033B */ u8 shouldDraw;
} DmStk; // size = 0x33C

extern const ActorInit Dm_Stk_InitVars;

#endif // Z_DM_STK_H
