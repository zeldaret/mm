#ifndef Z_EN_GO_H
#define Z_EN_GO_H

#include "global.h"

struct EnGo;

typedef void (*EnGoActionFunc)(struct EnGo*, PlayState*);
/*
void* thing = [
    { ACTOR_EN_GO, { -839, 0, -1277 }, 0x7FF2 },     // ENGO_GET_TYPE = 2 ENGO_GET_SUBTYPE = 7
    { ACTOR_EN_GO, { -109, 0, -596 }, 0x7FF2 },      // ENGO_GET_TYPE = 2 ENGO_GET_SUBTYPE = 7
    { ACTOR_EN_GO, { -47, 0, -505 }, 0x7FE2 },       // ENGO_GET_TYPE = 2 ENGO_GET_SUBTYPE = 6
    { ACTOR_EN_GO, { -104, 0, 111 }, 0x7FF2 },       // ENGO_GET_TYPE = 2 ENGO_GET_SUBTYPE = 7
    { ACTOR_EN_GO, { -60, 0, 12 }, 0x7FE2 },         // ENGO_GET_TYPE = 2 ENGO_GET_SUBTYPE = 6
    { ACTOR_EN_GO, { -1336, 0, -1282 }, 0x7FE2 },    // ENGO_GET_TYPE = 2 ENGO_GET_SUBTYPE = 6
    { ACTOR_EN_GO, { -1084, 91, -1611 }, 0x7FE2 },   // ENGO_GET_TYPE = 2 ENGO_GET_SUBTYPE = 6
    { ACTOR_EN_GO, { -181, 0, 65 }, 0x7FE2 },        // ENGO_GET_TYPE = 2 ENGO_GET_SUBTYPE = 6
    { ACTOR_EN_GO, { -207, 0, -560 }, 0x7FE2 },      // ENGO_GET_TYPE = 2 ENGO_GET_SUBTYPE = 6
    { ACTOR_EN_GO, { -4975, 227, 3896 }, 0x7FE2 },   // ENGO_GET_TYPE = 2 ENGO_GET_SUBTYPE = 6
    { ACTOR_EN_GO, { -3240, 650, 1803 }, 0x7FE2 },   // ENGO_GET_TYPE = 2 ENGO_GET_SUBTYPE = 6
    { ACTOR_EN_GO, { -4639, 1091, -3293 }, 0x7FE2 }, // ENGO_GET_TYPE = 2 ENGO_GET_SUBTYPE = 6
    { ACTOR_EN_GO, { -3697, 753, 1124 }, 0x7FE2 },   // ENGO_GET_TYPE = 2 ENGO_GET_SUBTYPE = 6
    { ACTOR_EN_GO, { -3231, 321, 6676 }, 0x7FE2 },   // ENGO_GET_TYPE = 2 ENGO_GET_SUBTYPE = 6
    { ACTOR_EN_GO, { -3563, 865, -372 }, 0x7FF2 },   // ENGO_GET_TYPE = 2 ENGO_GET_SUBTYPE = 7
    { ACTOR_EN_GO, { -1341, 0, -1171 }, 0x7FF2 },    // ENGO_GET_TYPE = 2 ENGO_GET_SUBTYPE = 7
    { ACTOR_EN_GO, { -2599, 1105, -4996 }, 0x7FE2 }, // ENGO_GET_TYPE = 2 ENGO_GET_SUBTYPE = 6
    { ACTOR_EN_GO, { -3806, 255, 7222 }, 0x7FE2 },   // ENGO_GET_TYPE = 2 ENGO_GET_SUBTYPE = 6
    { ACTOR_EN_GO, { 309, 0, -610 }, 0x7F81 },       // ENGO_GET_TYPE = 1 ENGO_GET_SUBTYPE = 0 // Side to Side Squatting
    { ACTOR_EN_GO, { 256, 0, -404 }, 0x7FD1 },       // ENGO_GET_TYPE = 1 ENGO_GET_SUBTYPE = 5 // Hamstring Stretcher
    { ACTOR_EN_GO, { 256, 0, -404 }, 0x7FC1 },       // ENGO_GET_TYPE = 1 ENGO_GET_SUBTYPE = 4 // Hamstring Stretcher
    { ACTOR_EN_GO, { 195, 0, -662 }, 0x7FB1 },       // ENGO_GET_TYPE = 1 ENGO_GET_SUBTYPE = 3 // Side Stretcher
    { ACTOR_EN_GO, { 30, 0, -366 }, 0x7FA1 },        // ENGO_GET_TYPE = 1 ENGO_GET_SUBTYPE = 2 // Limb Shaker


    { ACTOR_EN_GO, { 256, 0, -404 }, { SRF( 0, 0x0007), SRF(0X13E, 0x007F), SRF( 0, 0x007F) }, 0x7FD1 },
    { ACTOR_EN_GO, { 256, 0, -404 }, { SRF( 0, 0x0007), SRF(0X13E, 0x007F), SRF( 0, 0x007F) }, 0x7FC1 },
    { ACTOR_EN_GO, { 195, 0, -662 }, { SRF( 0, 0x0007), SRF( 0X8, 0x007F), SRF( 0, 0x007F) }, 0x7FB1 },
    { ACTOR_EN_GO, { 30, 0, -366 }, { SRF( 0, 0x0007), SRF( 0X95, 0x007F), SRF( 0, 0x007F) }, 0x7FA1 },



];
*/

#define ENGO_GET_TYPE(thisx) (((thisx)->params & 0xF) & 0xFF)
#define ENGO_GET_SUBTYPE(thisx) ((((thisx)->params & 0x70) >> 4) & 0xFF)

#define ENGO_GET_7F80(thisx) ((((thisx)->params & 0x7F80) >> 7) & 0xFF)

#define ENGO_NUM_EFFECTS 32
typedef enum {
    // enum {
    /* 0 */ ENGO_F_0 = 0,
    /* 1 */ ENGO_RACER,      // Racers
    /* 2 */ ENGO_SPECTATOR,  // Spectators
    /* 3 */ ENGO_GATEKEEPER, // Gatekeeper
    /* 4 */ ENGO_BROTHER,
    /* 5 */ ENGO_ASIDE_STORE,      // Shrine Goron Outside Store
    /* 6 */ ENGO_ASIDE_ELDERSROOM, // Shrine Goron Outside Elder's room
    /* 7 */ ENGO_ASIDE_ELDERSSON,  // Shrine Goron Stage Left of throne
    /* 8 */ ENGO_PKEG_SELLER,      // PowderKeg Goron
} EnGoType;

typedef enum {
    // enum {
    /* 0 */ ENGO_SQUAT_STRETCHER = 0,
    /* 1 */ ENGO_UNUSED,                   // Unused Racer
    /* 2 */ ENGO_LIMB_SHAKER,              // Limb Shaker
    /* 3 */ ENGO_SIDE_STRETCHER,           // Side  Stretcher
    /* 4 */ ENGO_HAMSTRING_STRETCHER,      // Hamstring Stretcher
    /* 5 */ ENGO_HAMSTRING_STRETCH_HELPER, // Hamstring Stretcher
} EnGoRacerSubtype;

typedef enum {
    // enum {
    /* 0 */ ENGO_ARMS_UP = 6,
    /* 1 */ ENGO_SHOUTING,
} EnGoSpectatorSubtype;

typedef enum {
    // enum {
    /* 0 */ ENGO_GRAVEBRO = 0, // GraveMaker
    /* 1 */ ENGO_FROZEBRO,     // Frozen Brother
} EnGoBrotherSubtype;

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

    // Gorons doing Gymnastics (object_taisou.c)
    /*  10 */ ENGO_ANIM_TAISOU_START = 10,
    /*  10 */ ENGO_ANIM_DOUBLE_ARM_SIDEBEND = 10,
    /*  11 */ ENGO_ANIM_SQUAT_SIDE_TO_SIDE,
    /*  12 */ ENGO_ANIM_SHAKE_LIMBS,
    /*  13 */ ENGO_ANIM_SINGLE_ARM_SIDEBEND,
    /*  14 */ ENGO_ANIM_SITTING_STRETCH,
    /*  15 */ ENGO_ANIM_CHEER,
    /*  16 */ ENGO_ANIM_SHOUT,
    /*  17 */ ENGO_ANIM_HELP_SITTING_STRETCH,

    // ???
    /*  18 */ ENGO_ANIM_HAKUGIN_START = 18,
    /*  18 */ ENGO_ANIM_HAKUGIN_18 = 18,
    /*  19 */ ENGO_ANIM_HAKUGIN_19_IMM,
    /*  20 */ ENGO_ANIM_HAKUGIN_20,
    /*  21 */ ENGO_ANIM_HAKUGIN_21_IMM,

} EnGoAnimationIndex;

typedef enum {
    ENGO_EFFECT_NONE = 0,
    ENGO_EFFECT_SNOW1 = 1,
    ENGO_EFFECT_SNOW2 = 2,
    ENGO_EFFECT_SNOW3 = 3,
    ENGO_EFFECT_DUST_START = 4,
    ENGO_EFFECT_DUST1 = 4,
    ENGO_EFFECT_DUST2 = 5,
    ENGO_EFFECT_DUST3 = 6,
    ENGO_EFFECT_STEAM_START = 7,
    ENGO_EFFECT_STEAM = 7,
} EnGoVfxType;

typedef struct {
    /* 0x00 */ u8 effectType;
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
    /* 0x290 */ Vec3f headPos;
    /* 0x29C */ Vec3f bodyPos;
    /* 0x2A8 */ Vec3s headRot;
    /* 0x2AE */ Vec3s bodyRot;
    /* 0x2B4 */ Vec3s jointTable[18];
    /* 0x320 */ Vec3s morphTable[18];
    /* 0x38C */ Actor* targetActor;
    /* 0x390 */ u16 actionFlags;
    /* 0x392 */ u16 lastTextId;
    /* 0x394 */ u8 currentCsAction;
    /* 0x398 */ f32 playSpeed;
    /* 0x39C */ f32 iceBlockScale;
    /* 0x3A0 */ f32 iceBlockAlpha;
    /* 0x3A4 */ f32 scaleFactor;
    /* 0x3A8 */ f32 scaleFactorPoundDistortion;
    /* 0x3AC */ UNK_TYPE1 unk3AC[0x2];
    /* 0x3AE */ union {
        s16 snorePhase;      // Used whilst a Goron is sleeping, +1024 at a time
        s16 elapsedHangtime; // Hangtime at the top of a pound.
    };
    /* 0x3B0 */ s16 headRotZ; // Limb17 rotZ
    /* 0x3B2 */ s16 headRotY; // Limb17 rotY
    /* 0x3B4 */ s16 bodyRotZ; // Limb10 rotZ
    /* 0x3B6 */ s16 bodyRotY; // Limb10 rotY
    /* 0x3B8 */ s16 indexCutscene;
    /* 0x3BA */ s16 loseAttentionTimer;
    /* 0x3BC */ s16 eyeTimer;
    /* 0x3BE */ s16 eyeTexIndex;
    /* 0x3C0 */ s16 cutsceneState;
    /* 0x3C2 */ s16 delayTimer;
    /* 0x3C4 */ s16 animState;
    /* 0x3C6 */ s16 harmlessTimer;
    /* 0x3C8 */ s16 limbRotTableZ[3];
    /* 0x3CE */ s16 limbRotTableY[3];
    /* 0x3D4 */ s16 surprisePhase;
    /* 0x3D8 */ void* msgEventCb; // MsgEventCallback
    /* 0x3DC */ EnGoAnimationIndex anim;
    /* 0x3E0 */ UNK_TYPE1 unk3E0[0x4];
    /* 0x3E4 */ s32 indexPathPoint;
    /* 0x3E8 */ s32 indexEffect;
    /* 0x3EC */ s32 sleepState;
    /* 0x3F0 */ s32 unk_3F0;
    /* 0x3F4 */ s32 changedText;
    /* 0x3F8 */ EnGoEffect effectTable[ENGO_NUM_EFFECTS];
} EnGo; // size = 0xB78

extern const ActorInit En_Go_InitVars;

#endif // Z_EN_GO_H
