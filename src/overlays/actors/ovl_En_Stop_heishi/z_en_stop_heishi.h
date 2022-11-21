#ifndef Z_EN_STOP_HEISHI_H
#define Z_EN_STOP_HEISHI_H

#include "global.h"
#include "objects/object_sdn/object_sdn.h"

struct EnStopheishi;

typedef void (*EnStopheishiActionFunc)(struct EnStopheishi*, PlayState*);

#define ENSTOPHEISHI_GET_SWITCH_FLAG(this) (((this)->actor.params) & 0x3F)
#define ENSTOPHEISHI_GET_C(this) ((((this)->actor.params) >> 0xC) & 0xF)

typedef struct EnStopheishi {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ Vec3s limbDrawTable[SOLDIER_LIMB_MAX];
    /* 0x01EE */ Vec3s transitionDrawTable[SOLDIER_LIMB_MAX];
    /* 0x0254 */ EnStopheishiActionFunc actionFunc;
    /* 0x0258 */ s16 headZRot;
    /* 0x025A */ s16 headXRot;
    /* ox025C */ char unk_25C[2];
    /* 0x025E */ s16 pitchToPlayer;
    /* 0x0260 */ s16 headXRotTarget;
    /* 0x0262 */ s16 unk_262; //Unused
    /* 0x0264 */ u8 unk_264; //Locking value at `0` prevents leaving the guard pose, however locking to 1 doesn't prevent guarding.
    /* 0x0265 */ u8 unk_265;
    /* 0x0266 */ s16 unk_266;
    /* 0x0268 */ s32 currentAnim;
    /* 0x026C */ f32 currentAnimFrameCount;
    /* 0x0270 */ s16 timer;
    /* 0x0272 */ s16 headTurnTimer1;
    /* 0x0274 */ s16 unk_274;
    /* 0x0276 */ s16 unk_276;
    /* 0x0278 */ s16 disableCollider;
    /* 0x027A */ s16 switchFlag;
    /* 0x027C */ s16 messageIndex;
    /* 0x027E */ s16 unk_27E;
    /* 0x0280 */ s16 yRotTarget;
    /* 0x0284 */ s32 headTurnTimer2;
    /* 0x0288 */ f32 unk_288;
    /* 0x028C */ f32 maxMoveStep;
    /* 0x028C */ Vec3f headWorldPos;
    /* 0x029C */ ColliderCylinder collider;
} EnStopheishi; // size = 0x2E8

#endif // Z_EN_STOP_HEISHI_H
