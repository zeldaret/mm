#ifndef Z_EN_GO_H
#define Z_EN_GO_H

#include "global.h"

struct EnGo;

typedef void (*EnGoActionFunc)(struct EnGo*, PlayState*);
/*
void* thing = [
    { ACTOR_EN_GO, { -839, 0, -1277 }, 0x7FF2 },     // ENGO_GET_F = 2 ENGO_GET_70 = 7
    { ACTOR_EN_GO, { -109, 0, -596 }, 0x7FF2 },      // ENGO_GET_F = 2 ENGO_GET_70 = 7
    { ACTOR_EN_GO, { -47, 0, -505 }, 0x7FE2 },       // ENGO_GET_F = 2 ENGO_GET_70 = 6
    { ACTOR_EN_GO, { -104, 0, 111 }, 0x7FF2 },       // ENGO_GET_F = 2 ENGO_GET_70 = 7
    { ACTOR_EN_GO, { -60, 0, 12 }, 0x7FE2 },         // ENGO_GET_F = 2 ENGO_GET_70 = 6
    { ACTOR_EN_GO, { -1336, 0, -1282 }, 0x7FE2 },    // ENGO_GET_F = 2 ENGO_GET_70 = 6
    { ACTOR_EN_GO, { -1084, 91, -1611 }, 0x7FE2 },   // ENGO_GET_F = 2 ENGO_GET_70 = 6
    { ACTOR_EN_GO, { -181, 0, 65 }, 0x7FE2 },        // ENGO_GET_F = 2 ENGO_GET_70 = 6
    { ACTOR_EN_GO, { -207, 0, -560 }, 0x7FE2 },      // ENGO_GET_F = 2 ENGO_GET_70 = 6
    { ACTOR_EN_GO, { -4975, 227, 3896 }, 0x7FE2 },   // ENGO_GET_F = 2 ENGO_GET_70 = 6
    { ACTOR_EN_GO, { -3240, 650, 1803 }, 0x7FE2 },   // ENGO_GET_F = 2 ENGO_GET_70 = 6
    { ACTOR_EN_GO, { -4639, 1091, -3293 }, 0x7FE2 }, // ENGO_GET_F = 2 ENGO_GET_70 = 6
    { ACTOR_EN_GO, { -3697, 753, 1124 }, 0x7FE2 },   // ENGO_GET_F = 2 ENGO_GET_70 = 6
    { ACTOR_EN_GO, { -3231, 321, 6676 }, 0x7FE2 },   // ENGO_GET_F = 2 ENGO_GET_70 = 6
    { ACTOR_EN_GO, { -3563, 865, -372 }, 0x7FF2 },   // ENGO_GET_F = 2 ENGO_GET_70 = 7
    { ACTOR_EN_GO, { -1341, 0, -1171 }, 0x7FF2 },    // ENGO_GET_F = 2 ENGO_GET_70 = 7
    { ACTOR_EN_GO, { -2599, 1105, -4996 }, 0x7FE2 }, // ENGO_GET_F = 2 ENGO_GET_70 = 6
    { ACTOR_EN_GO, { -3806, 255, 7222 }, 0x7FE2 },   // ENGO_GET_F = 2 ENGO_GET_70 = 6
    { ACTOR_EN_GO, { 309, 0, -610 }, 0x7F81 },       // ENGO_GET_F = 1 ENGO_GET_70 = 0 // Side to Side Squatting
    { ACTOR_EN_GO, { 256, 0, -404 }, 0x7FD1 },       // ENGO_GET_F = 1 ENGO_GET_70 = 5 // Hamstring Stretcher
    { ACTOR_EN_GO, { 256, 0, -404 }, 0x7FC1 },       // ENGO_GET_F = 1 ENGO_GET_70 = 4 // Hamstring Stretcher
    { ACTOR_EN_GO, { 195, 0, -662 }, 0x7FB1 },       // ENGO_GET_F = 1 ENGO_GET_70 = 3 // Side Stretcher
    { ACTOR_EN_GO, { 30, 0, -366 }, 0x7FA1 },        // ENGO_GET_F = 1 ENGO_GET_70 = 2 // Limb Shaker
];
*/

#define ENGO_GET_F(thisx) (((thisx)->params & 0xF) & 0xFF)
// Something to do with Animation
#define ENGO_GET_70(thisx) ((((thisx)->params & 0x70) >> 4) & 0xFF)

#define ENGO_GET_7F80(thisx) ((((thisx)->params & 0x7F80) >> 7) & 0xFF)

enum {
    /* 0 */ ENGO_F_0,
    /* 1 */ ENGO_RACER,      // Goron Racers
    /* 2 */ ENGO_SPECTATOR,  // Goron Spectators
    /* 3 */ ENGO_GATEKEEPER, // Goron Gatekeeper
    /* 4 */ ENGO_BROTHER,
    /* 5 */ ENGO_F_5,         // Shrine Gorons?
    /* 6 */ ENGO_F_6,         // Shrine Gorons?
    /* 7 */ ENGO_F_7,         // Shrine Gorons?
    /* 8 */ ENGO_PKEG_SELLER, // PowderKeg Goron
};

enum {
    /* 0 */ ENGO_70_0, // Side to Side Squatter
    /* 1 */ ENGO_70_1, // Not used in Races
    /* 2 */ ENGO_70_2, // Limb Shaker
    /* 3 */ ENGO_70_3, // Side  Stretcher
    /* 4 */ ENGO_70_4, // Hamstring Stretcher
    /* 5 */ ENGO_70_5, // Hamstring Stretcher
};

typedef enum {
    /* -1 */ ENGO_ANIM_INVALID = -1,
    /*  0 */ ENGO_ANIM_GORON_START = 0,
    /*  0 */ ENGO_ANIM_LYINGDOWNIDLE = 0,
    /*  1 */ ENGO_ANIM_LYINGDOWNIDLE_IMM,
    /*  2 */ ENGO_ANIM_UNROLL,
    /*  3 */ ENGO_ANIM_UNROLL_IMM,
    /*  4 */ ENGO_ANIM_ROLL,
    /*  5 */ ENGO_ANIM_SHIVER,
    /*  6 */ ENGO_ANIM_SHIVER_IMM,
    /*  7 */ ENGO_ANIM_DROPKEG,
    /*  8 */ ENGO_ANIM_COVEREARS,
    /*  9 */ ENGO_ANIM_SHIVERINGSURPRISED,

    // Gorons doing Gymnastics
    /*  10 */ ENGO_ANIM_TAISOU_START = 10,
    /*  10 */ ENGO_ANIM_TAISOU_10 = 10,
    /*  11 */ ENGO_ANIM_TAISOU_11,
    /*  12 */ ENGO_ANIM_TAISOU_12,
    /*  13 */ ENGO_ANIM_TAISOU_13,
    /*  14 */ ENGO_ANIM_TAISOU_14,
    /*  15 */ ENGO_ANIM_TAISOU_15,
    /*  16 */ ENGO_ANIM_TAISOU_16,
    /*  17 */ ENGO_ANIM_TAISOU_17,

    // ???
    /*  18 */ ENGO_ANIM_HAKUGIN_START = 18,
    /*  18 */ ENGO_ANIM_HAKUGIN_18 = 18,
    /*  19 */ ENGO_ANIM_HAKUGIN_19_IMM,
    /*  20 */ ENGO_ANIM_HAKUGIN_20,
    /*  21 */ ENGO_ANIM_HAKUGIN_21_IMM,

} EnGoAnimationIndex;

typedef enum {
    ENGO_VFX_NONE = 0,
    ENGO_VFX_SNOW1 = 1,
    ENGO_VFX_SNOW2 = 2,
    ENGO_VFX_SNOW3 = 3,
    ENGO_VFX_DUST1 = 4,
    ENGO_VFX_DUST2 = 5,
    ENGO_VFX_DUST3 = 6,
    ENGO_VFX_STEAM = 7,
} EnGoVfxType;

typedef struct {
    /* 0x00 */ u8 vfxType;
    /* 0x01 */ u8 alphaDenom;     /* Alpha Denominator */
    /* 0x02 */ u8 alphaNumer;     /* Alpha Numerator */
    /* 0x04 */ Vec3s rotVelocity; /* Rotational Velocity */
    /* 0x0A */ Vec3s rotAngle;    /* Rotational Position */
    /* 0x10 */
    Vec3f position;
    /* 0x1C */ Vec3f acceleration;
    /* 0x28 */ Vec3f velocity;
    /* 0x34 */ f32 scaleXY;
    /* 0x38 */ f32 scaleXYDelta;
} EnGoEffect; // size = 0x3C;

typedef struct EnGo {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ EnGoActionFunc actionFunc;
    /* 0x18C */ EnGoActionFunc priorActionFn;
    /* 0x190 */ EnGoActionFunc dialogActionFn;
    /* 0x194 */ ColliderCylinder colliderCylinder;
    /* 0x1E0 */ UNK_TYPE1 unk1E0[0x4C];
    /* 0x22C */ ColliderSphere colliderSphere;
    /* 0x284 */ Path* path;
    /* 0x288 */ s8 indexTaisou;
    /* 0x289 */ s8 indexHakuginDemo;
    /* 0x28C */ s32 msgScriptResumePos;
    /* 0x290 */ Vec3f limb17Pos;
    /* 0x29C */ Vec3f limb10Pos;
    /* 0x2A8 */ Vec3s limb17Rot;
    /* 0x2AE */ Vec3s limb10Rot;
    /* 0x2B4 */ Vec3s jointTable[18];
    /* 0x320 */ Vec3s morphTable[18];
    /* 0x38C */ Actor* targetActor;
    /* 0x390 */ u16 flags;
    /* 0x392 */ u16 lastTextId;
    /* 0x394 */ u8 currentCsAction;
    /* 0x398 */ f32 playSpeed;
    /* 0x39C */ f32 iceBlockScale;
    /* 0x3A0 */ f32 iceBlockAlpha;
    /* 0x3A4 */ f32 scale;
    /* 0x3A8 */ f32 unk_3A8;
    /* 0x3AC */ UNK_TYPE1 unk3AC[0x2];
    /* 0x3AE */ s16 unk_3AE;
    /* 0x3B0 */ s16 unk_3B0; // Limb17 rotZ
    /* 0x3B2 */ s16 unk_3B2; // Limb17 rotY
    /* 0x3B4 */ s16 unk_3B4; // Limb10 rotZ
    /* 0x3B6 */ s16 unk_3B6; // Limb10 rotY
    /* 0x3B8 */ s16 indexCutscene;
    /* 0x3BA */ s16 unk_3BA;
    /* 0x3BC */ s16 blinkCountdown;
    /* 0x3BE */ s16 indexEyeTex;
    /* 0x3C0 */ s16 cutsceneState;
    /* 0x3C2 */ s16 delayTimer;
    /* 0x3C4 */ s16 animState;
    /* 0x3C6 */ s16 harmlessTimer;
    /* 0x3C8 */ s16 limbRotTableZ[3];
    /* 0x3CE */ s16 limbRotTableY[3];
    /* 0x3D4 */ s16 unk_3D4;
    /* 0x3D8 */ void* msgEventCb;        // MsgEventCallback
    /* 0x3DC */ EnGoAnimationIndex anim; // -1 for invalid,
                                         // 2|3 Goron CircleOff/Stand,
                                         // 4 Goron Circle/Sit,
                                         // <10 use actorObjBank,
                                         // 10-17 use Taisou,
                                         // 14 useles Translate&RotateY, Draw at -4000
                                         // 18+ use Hakugin
                                         // 20 -> 21 on Anim end
                                         // 18 -> 19 on Anim end
    /* 0x3E0 */ UNK_TYPE1 unk3E0[0x4];
    /* 0x3E4 */ s32 indexPathPoint;
    /* 0x3E8 */ s32 indexEffect;
    /* 0x3EC */ s32 sleepState;
    /* 0x3F0 */ s32 unk_3F0;
    /* 0x3F4 */ s32 unk_3F4;
    /* 0x3F8 */ EnGoEffect effectTable[32];
} EnGo; // size = 0xB78

extern const ActorInit En_Go_InitVars;

#endif // Z_EN_GO_H
