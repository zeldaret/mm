#ifndef Z_EN_GO_H
#define Z_EN_GO_H

#include "global.h"

struct EnGo;

typedef void (*EnGoActionFunc)(struct EnGo*, PlayState*);

#define ENGO_GET_TYPE(thisx) (((thisx)->params & 0xF) & 0xFF)
#define ENGO_GET_SUBTYPE(thisx) ((((thisx)->params & 0x70) >> 4) & 0xFF)

#define ENGO_GET_7F80(thisx) ((((thisx)->params & 0x7F80) >> 7) & 0xFF)

#define ENGO_NUM_EFFECTS 32

extern const ActorInit En_Go_InitVars;

typedef struct EnGoEffect {
    /* 0x00 */ u8 effectType;
    /* 0x01 */ u8 alphaDenom;
    /* 0x02 */ u8 alphaNumer;
    /* 0x04 */ Vec3s rotVelocity;
    /* 0x0A */ Vec3s rotAngle;
    /* 0x10 */ Vec3f position;
    /* 0x1C */ Vec3f acceleration;
    /* 0x28 */ Vec3f velocity;
    /* 0x34 */ f32 scaleXY;
    /* 0x38 */ f32 scaleXYDelta;
} EnGoEffect; // size = 0x3C;

typedef struct EnGo {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ EnGoActionFunc actionFunc;
    /* 0x18C */ EnGoActionFunc interruptedActionFn;
    /* 0x190 */ EnGoActionFunc graveBroDialogActionFn;
    /* 0x194 */ ColliderCylinder colliderCylinder;
    /* 0x1E0 */ UNK_TYPE1 unk1E0[0x4C];
    /* 0x22C */ ColliderSphere colliderSphere;
    /* 0x284 */ Path* gatekeeperPath;
    /* 0x288 */ s8 indexTaisou;
    /* 0x289 */ s8 indexHakuginDemo;
    /* 0x28C */ s32 msgScriptResumePos;
    /* 0x290 */ Vec3f headPos;
    /* 0x29C */ Vec3f bodyPos;
    /* 0x2A8 */ Vec3s headRot;
    /* 0x2AE */ Vec3s bodyRot;
    /* 0x2B4 */ Vec3s jointTable[18];
    /* 0x320 */ Vec3s morphTable[18];
    /* 0x38C */ Actor* attentionTarget;
    /* 0x390 */ u16 actionFlags;
    /* 0x392 */ u16 lastTextId;
    /* 0x394 */ u8 brotherThawCurrentCsAction;
    /* 0x398 */ f32 currAnimPlaySpeed;
    /* 0x39C */ f32 iceBlockScale;
    /* 0x3A0 */ f32 iceBlockAlpha;
    /* 0x3A4 */ f32 scaleFactor;
    /* 0x3A8 */ f32 scaleFactorPoundDistortion;
    /* 0x3AC */ UNK_TYPE1 unk3AC[0x2];
    /* 0x3AE */ union {
        s16 snorePhase;      // Used whilst a Goron is sleeping, +1024 at a time
        s16 elapsedHangtime; // Hangtime at the top of a pound.
    };
    /* 0x3B0 */ s16 headRotZ;
    /* 0x3B2 */ s16 headRotY;
    /* 0x3B4 */ s16 bodyRotZ;
    /* 0x3B6 */ s16 bodyRotY;
    /* 0x3B8 */ s16 indexCutscene;
    /* 0x3BA */ s16 loseAttentionTimer;
    /* 0x3BC */ s16 eyeTimer;
    /* 0x3BE */ s16 eyeTexIndex;
    /* 0x3C0 */ s16 cutsceneState;
    /* 0x3C2 */ s16 cutsceneDelayTimer;
    /* 0x3C4 */ s16 gatekeeperAnimState;
    /* 0x3C6 */ s16 harmlessTimer;
    /* 0x3C8 */ s16 limbRotTableZ[3];
    /* 0x3CE */ s16 limbRotTableY[3];
    /* 0x3D4 */ s16 surprisePhase;
    /* 0x3D8 */ void* msgEventCb;
    /* 0x3DC */ s32 currAnimIndex;
    /* 0x3E0 */ UNK_TYPE1 unk3E0[0x4];
    /* 0x3E4 */ s32 indexPathPoint;
    /* 0x3E8 */ s32 indexEffect;
    /* 0x3EC */ s32 sleepState;
    /* 0x3F0 */ s32 brotherThawCutsceneActive;
    /* 0x3F4 */ s32 changedText;
    /* 0x3F8 */ EnGoEffect effectTable[ENGO_NUM_EFFECTS];
} EnGo; // size = 0xB78

/**
 * Goron Type, identified by bits [3..0] of the actor's params
 *
 * - The ENGO_STRETCHER and ENGO_SPECTATOR types share the same subtype domain (EnGoGoronRaceSubtype: [0,7])
 * - ENGO_BROTHER types have their own subtype domain (EnGoBrotherSubtype: [0,1])
 * - Others have no subtypes.
 */
typedef enum EnGoType {
    /* 0 */ ENGO_F_0 = 0,
    /* 1 */ ENGO_STRETCHER,        // Racers stretching before the Goron Race
    /* 2 */ ENGO_SPECTATOR,        // Spectators to the Goron Race
    /* 3 */ ENGO_GATEKEEPER,       // Gatekeeper to the Goron Shrine
    /* 4 */ ENGO_GRAVEBRO,         // GraveMaker and Gravemaker's Brother
    /* 5 */ ENGO_ASIDE_STORE,      // Shrine Goron Outside Store
    /* 6 */ ENGO_ASIDE_ELDERSROOM, // Shrine Goron Outside Elder's room
    /* 7 */ ENGO_ASIDE_ELDERSSON,  // Shrine Goron Stage Left of throne
    /* 8 */ ENGO_PKEG_SELLER,      // PowderKeg Goron
} EnGoType;

typedef enum EnGoGoronRaceSubtype {
    /* 0 */ ENGO_STRETCHER_A = 0,
    /* 1 */ ENGO_STRETCHER_B,
    /* 2 */ ENGO_STRETCHER_C,
    /* 3 */ ENGO_STRETCHER_D,
    /* 4 */ ENGO_STRETCHER_HAMSTRINGSIT,
    /* 5 */ ENGO_STRETCHER_HAMSTRINGSTAND,
    /* 6 */ ENGO_SPECTATOR_CHEER,
    /* 7 */ ENGO_SPECTATOR_SHOUTING,
} EnGoGoronRaceSubtype;

typedef enum EnGoBrotherSubtype {
    /* 0 */ ENGO_GRAVEBRO_GRAVEMAKER = 0,
    /* 1 */ ENGO_GRAVEBRO_FROZEN,
} EnGoBrotherSubtype;

#endif // Z_EN_GO_H
