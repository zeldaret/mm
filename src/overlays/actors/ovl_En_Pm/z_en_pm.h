#ifndef Z_EN_PM_H
#define Z_EN_PM_H

#include "global.h"

struct EnPm;

typedef void (*EnPmActionFunc)(struct EnPm*, GlobalContext*);
typedef s32 (*EnPmFunc)(struct EnPm*, GlobalContext*);
typedef s32 (*EnPmFunc2)(struct EnPm*, GlobalContext*);

typedef struct EnPm {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ EnPmActionFunc actionFunc;
    /* 0x018C */ EnPmFunc2 unk_18C;
    /* 0x0190 */ ColliderCylinder colliderCylinder;
    /* 0x01DC */ ColliderSphere colliderSphere;
    /* 0x0234 */ Path* unk_234;
    /* 0x0238 */ Vec3f unk_238;
    /* 0x0244 */ f32 unk_244;
    /* 0x0248 */ s32 unk_248;
    /* 0x024C */ s32 unk_24C;
    /* 0x0250 */ s32 unk_250;
    /* 0x0254 */ s32 unk_254;
    /* 0x0258 */ u8 unk_258;
    /* 0x025C */ UNK_TYPE* unk_25C;
    /* 0x0260 */ s8 unk_260;
    /* 0x0264 */ s32 unk_264;
    /* 0x0268 */ Actor* unk_268;
    /* 0x026C */ Vec3f unk_26C;
    /* 0x0278 */ Vec3f unk_278;
    /* 0x0284 */ Vec3f unk_284;
    /* 0x0290 */ Vec3s unk_290;
    /* 0x0296 */ Vec3s jointTable[16];
    /* 0x02F6 */ Vec3s morphTable[16];
    /* 0x0356 */ u16 unk_356;
    /* 0x0358 */ u16 unk_358;
    /* 0x035C */ f32 unk_35C;
    /* 0x0360 */ f32 unk_360;
    /* 0x0364 */ f32 unk_364;
    /* 0x0368 */ f32 unk_368;
    /* 0x036C */ s16 unk_36C;
    /* 0x036E */ s16 unk_36E;
    /* 0x0370 */ s16 unk_370;
    /* 0x0372 */ s16 unk_372;
    /* 0x0374 */ s16 unk_374;
    /* 0x0376 */ s16 unk_376;
    /* 0x0378 */ s16 unk_378;
    /* 0x037C */ EnPmFunc unk_37C;
    /* 0x0380 */ s32 unk_380;
    /* 0x0384 */ s32 unk_384;
    /* 0x0388 */ s32 unk_388;
    /* 0x038C */ s32 unk_38C;
    /* 0x0390 */ UNK_TYPE1 unk390[0x4];
    /* 0x0394 */ s32 unk_394;
    /* 0x0398 */ s32 unk_398;
    /* 0x039C */ UNK_TYPE1 unk39C[0x4];
} EnPm; // size = 0x3A0

extern const ActorInit En_Pm_InitVars;

#endif // Z_EN_PM_H
