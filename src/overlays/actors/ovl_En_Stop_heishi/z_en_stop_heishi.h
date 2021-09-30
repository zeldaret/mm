#ifndef Z_EN_STOP_HEISHI_H
#define Z_EN_STOP_HEISHI_H

#include "global.h"

struct EnStopheishi;

typedef void (*EnStopheishiActionFunc)(struct EnStopheishi*, GlobalContext*);

typedef struct EnStopheishi {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ Vec3s limbDrawTable[17];
    /* 0x01EE */ Vec3s transitionDrawTable[17];
    /* 0x0254 */ EnStopheishiActionFunc actionFunc;
    /* 0x0258 */ char unk_258[0x6];
    /* 0x025E */ s16 pitchToPlayer;
    /* 0x0260 */ s16 unk_260;
    /* 0x0262 */ s16 unk_262;
    /* 0x0264 */ s8 unk_264;
    /* 0x0265 */ u8 unk_265;
    /* 0x0266 */ s16 unk_266;
    /* 0x0268 */ s32 unk_268;
    /* 0x026C */ f32 currentAnimFrameCount;
    /* 0x0270 */ s16 unk_270;
    /* 0x0272 */ s16 unk_272;
    /* 0x0274 */ s16 unk_274;
    /* 0x0276 */ s16 unk_276;
    /* 0x0278 */ s16 unk_278;
    /* 0x027A */ s16 unk_27A;
    /* 0x027C */ s16 unk_27C;
    /* 0x027E */ s16 unk_27E;
    /* 0x0280 */ s16 unk_280;
    /* 0x0282 */ char unk_282[2];
    /* 0x0284 */ s32 unk_284;
    /* 0x0288 */ f32 unk_288;
    /* 0x028C */ f32 unk_28C;
    /* 0x028C */ char unk_290[0xC];
    /* 0x029C */ ColliderCylinder collider;
} EnStopheishi; // size = 0x2E8

extern const ActorInit En_Stop_heishi_InitVars;

#endif // Z_EN_STOP_HEISHI_H
