#ifndef Z_EN_GO_H
#define Z_EN_GO_H

#include "global.h"

struct EnGo;

typedef void (*EnGoActionFunc)(struct EnGo*, PlayState*);

#define ENGO_GET_F(thisx) (((thisx)->params & 0xF) & 0xFF)
// Something to do with Animation
#define ENGO_GET_70(thisx) ((((thisx)->params & 0x70) >> 4) & 0xFF)
#define ENGO_GET_7F80(thisx) ((((thisx)->params & 0x7F80) >> 7) & 0xFF)

enum {
    /* 0 */ ENGO_F_0,
    /* 1 */ ENGO_F_1,
    /* 2 */ ENGO_F_2,
    /* 3 */ ENGO_F_3,
    /* 4 */ ENGO_F_4,
    /* 5 */ ENGO_F_5,
    /* 6 */ ENGO_F_6,
    /* 7 */ ENGO_F_7,
    /* 8 */ ENGO_F_8,
};

enum {
    /* 0 */ ENGO_70_0,
    /* 1 */ ENGO_70_1,
    /* 2 */ ENGO_70_2,
    /* 3 */ ENGO_70_3,
    /* 4 */ ENGO_70_4,
    /* 5 */ ENGO_70_5,
};

typedef enum {
    ENGO_ANIM_INVALID,
    ENGO_ANIM_GORON_START = 0,
    ENGO_ANIM_LYINGDOWNIDLE = 0,
    ENGO_ANIM_LYINGDOWNIDLE_IMM,
    ENGO_ANIM_UNROLL,
    ENGO_ANIM_UNROLL_IMM,
    ENGO_ANIM_ROLL,
    ENGO_ANIM_SHIVER,
    ENGO_ANIM_SHIVER_IMM,
    ENGO_ANIM_DROPKEG,
    ENGO_ANIM_COVEREARS,
    ENGO_ANIM_SHIVERINGSURPRISED,

    // Gorons doing Gymnastics
    ENGO_ANIM_TAISOU_START = 10,
    ENGO_ANIM_TAISOU_10 = 10,
    ENGO_ANIM_TAISOU_11,
    ENGO_ANIM_TAISOU_12,
    ENGO_ANIM_TAISOU_13,
    ENGO_ANIM_TAISOU_14,
    ENGO_ANIM_TAISOU_15,
    ENGO_ANIM_TAISOU_16,
    ENGO_ANIM_TAISOU_17,

    // ???
    ENGO_ANIM_HAKUGIN_START = 18,
    ENGO_ANIM_HAKUGIN_18 = 18,
    ENGO_ANIM_HAKUGIN_19_IMM,
    ENGO_ANIM_HAKUGIN_20,
    ENGO_ANIM_HAKUGIN_21_IMM,

} EnGoAnimationIndex;

typedef struct {
    /* 0x00 */ u8 unk_00;
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
} EnGoStruct; // size = 0x3C;

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
    /* 0x28C */ s32 unk_28C;
    /* 0x290 */ Vec3f limb17Pos;
    /* 0x29C */ Vec3f limb10Pos;
    /* 0x2A8 */ Vec3s limb17Rot;
    /* 0x2AE */ Vec3s limb10Rot;
    /* 0x2B4 */ Vec3s jointTable[18];
    /* 0x320 */ Vec3s morphTable[18];
    /* 0x38C */ Actor* targetActor;
    /* 0x390 */ u16 flags;
    /* 0x392 */ u16 lastTextId;
    /* 0x394 */ u8 unk_394;
    /* 0x398 */ f32 playSpeed;
    /* 0x39C */ f32 unk_39C;
    /* 0x3A0 */ f32 unk_3A0;
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
    /* 0x3C2 */ s16 unk_3C2;
    /* 0x3C4 */ s16 unk_3C4;
    /* 0x3C6 */ s16 unk_3C6;
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
    /* 0x3E8 */ s32 unk_3E8;
    /* 0x3EC */ s32 sleepState;
    /* 0x3F0 */ s32 unk_3F0;
    /* 0x3F4 */ s32 unk_3F4;
    /* 0x3F8 */ EnGoStruct unk_3F8[32];
} EnGo; // size = 0xB78

extern const ActorInit En_Go_InitVars;

#endif // Z_EN_GO_H
