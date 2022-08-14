#ifndef Z_EN_RAILGIBUD_H
#define Z_EN_RAILGIBUD_H

#include "global.h"
#include "objects/object_rd/object_rd.h"

struct EnRailgibud;

typedef void (*EnRailgibudActionFunc)(struct EnRailgibud*, PlayState*);

#define ENRAILGIBUD_GET_CUTSCENE_TYPE(thisx) ((thisx)->params & 0x7F)
#define ENRAILGIBUD_IS_CUTSCENE_TYPE(thisx) ((thisx)->params & 0x80)
#define ENRAILGIBUD_GET_PATH(thisx) (((thisx)->params & 0xFF00) >> 8)

typedef struct EnRailgibud {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ColliderCylinder collider;
    /* 0x190 */ SkelAnime skelAnime;
    /* 0x1D4 */ EnRailgibudActionFunc actionFunc;
    /* 0x1D8 */ Vec3f limbPos[15];
    /* 0x28C */ s32 limbIndex;
    /* 0x290 */ UNK_TYPE1 unk290[0x4];
    /* 0x294 */ Vec3s* points;
    /* 0x298 */ s32 currentPoint;
    /* 0x29C */ s32 pathCount;
    /* 0x2A0 */ f32 drawDmgEffAlpha;
    /* 0x2A4 */ f32 drawDmgEffScale;
    /* 0x2A8 */ Vec3s jointTable[GIBDO_LIMB_MAX];
    /* 0x344 */ Vec3s morphTable[GIBDO_LIMB_MAX];
    /* 0x3E0 */ Vec3s headRotation;
    /* 0x3E6 */ Vec3s upperBodyRotation;
    /* 0x3EC */ s16 shouldWalkForward; // Only used by the "main" Gibdo
    /* 0x3EE */ s16 shouldWalkForwardNextFrame; // Only used by the "main" Gibdo
    /* 0x3F0 */ union {
                    s16 grabState;
                    s16 cutsceneAnimationIndex;
                };
    /* 0x3F2 */ union {
                    s16 playerStunWaitTimer; // Cannot stun the player if this is non-zero
                    s16 grabDamageTimer;
                    s16 headShakeTimer;
                    s16 stunTimer;
                    s16 deathTimer;
                    s16 sinkTimer;
                };
    /* 0x3F4 */ s16 grabWaitTimer; // Cannot grab the player if this is non-zero
    /* 0x3F6 */ s16 drawDmgEffTimer;
    /* 0x3F8 */ s16 type;
    /* 0x3FA */ s16 isInvincible;
    /* 0x3FC */ u16 actorActionCommand;
    /* 0x3FE */ u16 csAction;
    /* 0x400 */ u16 textId;
    /* 0x402 */ s16 timeInitialized; // unused other than setting it
    /* 0x404 */ u8 drawDmgEffType;
    /* 0x405 */ s8 unk_405; // related to player->unk_ADD
} EnRailgibud; // size = 0x408

extern const ActorInit En_Railgibud_InitVars;

#endif // Z_EN_RAILGIBUD_H
