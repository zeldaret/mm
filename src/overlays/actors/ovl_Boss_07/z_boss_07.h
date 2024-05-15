#ifndef Z_BOSS_07_H
#define Z_BOSS_07_H

#include "global.h"
#include "objects/object_boss07/object_boss07.h"

struct Boss07;

#define MAJORA_TENT_LENGTH 10
#define MAJORA_TENT_COUNT 25
#define MAJORA_TENT_MAX 100
#define MAJORA_WHIP_MAX_LENGTH 50

#define MAJORA_LIMB_COUNT MAX((s32)MAJORAS_MASK_LIMB_MAX, MAX((s32)MAJORAS_INCARNATION_LIMB_MAX, (s32)MAJORAS_WRATH_LIMB_MAX))

#define MAJORAS_WRATH_SHADOW_TEX_WIDTH 64
#define MAJORAS_WRATH_SHADOW_TEX_HEIGHT 64
#define MAJORAS_WRATH_SHADOW_TEX_SIZE ((s32)sizeof(u8[MAJORAS_WRATH_SHADOW_TEX_HEIGHT][MAJORAS_WRATH_SHADOW_TEX_WIDTH]))

#define MAJORA_GET_TYPE(thisx) ((thisx)->params)

typedef void (*Boss07ActionFunc)(struct Boss07*, struct PlayState*);

typedef enum MajoraType {
    /*   0 */ MAJORA_TYPE_BOSS,
    /*  10 */ MAJORA_TYPE_MASK = 10,
    /*  11 */ MAJORA_TYPE_MASK_CS,
    /*  20 */ MAJORA_TYPE_INCARNATION = 20,
    /*  21 */ MAJORA_TYPE_AFTERIMAGE,
    /*  30 */ MAJORA_TYPE_WRATH = 30,
    /* 100 */ MAJORA_TYPE_REMAINS_SHOT = 100,
    /* 101 */ MAJORA_TYPE_INCARNATION_SHOT,
    /* 150 */ MAJORA_TYPE_BATTLE_HANDLER = 150,
    /* 180 */ MAJORA_TYPE_TOP = 180,
    /* 200 */ MAJORA_TYPE_REMAINS = 200
} MajoraType;

typedef enum MajoraRemainsType {
    /* 0 */ MAJORA_REMAINS_TYPE_ODOLWA,
    /* 1 */ MAJORA_REMAINS_TYPE_GYORG,
    /* 2 */ MAJORA_REMAINS_TYPE_GOHT,
    /* 3 */ MAJORA_REMAINS_TYPE_TWINMOLD,
    /* 4 */ MAJORA_REMAINS_TYPE_MAX
} MajoraRemainsType;

typedef struct MajoraTentacle {
    /* 0x00 */ Vec3f base;
    /* 0x0C */ Vec3f pos[MAJORA_TENT_LENGTH];
    /* 0x84 */ Vec3f rot[MAJORA_TENT_LENGTH];
    /* 0xFC */ Vec3f velocity[MAJORA_TENT_LENGTH];
} MajoraTentacle; // size = 0x174

typedef struct MajoraWhip {
    /* 0x000 */ Vec3s baseRot;
    /* 0x008 */ f32 gravity;
    /* 0x00C */ f32 mobility;
    /* 0x010 */ f32 drag;
    /* 0x014 */ f32 tension;
    /* 0x018 */ Vec3f basePos;
    /* 0x024 */ Vec3f pos[MAJORA_WHIP_MAX_LENGTH];
    /* 0x27C */ Vec3f rot[MAJORA_WHIP_MAX_LENGTH];
    /* 0x4D4 */ Vec3f velocity[MAJORA_WHIP_MAX_LENGTH];
    /* 0x72C */ f32 unk_72C[MAJORA_WHIP_MAX_LENGTH]; // unused, probably a stretch factor
} MajoraWhip; // size = 0x7F4

typedef enum MajorasWrathBodyPart {
    /*  0 */ MAJORAS_WRATH_BODYPART_HEAD,
    /*  1 */ MAJORAS_WRATH_BODYPART_TORSO,
    /*  2 */ MAJORAS_WRATH_BODYPART_PELVIS,
    /*  3 */ MAJORAS_WRATH_BODYPART_LEFT_UPPER_ARM,
    // This body part is redundant; it's located at the exact same position as `MAJORAS_WRATH_BODYPART_LEFT_FOREARM`.
    /*  4 */ MAJORAS_WRATH_BODYPART_LEFT_LOWER_ARM_ROOT,
    /*  5 */ MAJORAS_WRATH_BODYPART_LEFT_FOREARM,
    /*  6 */ MAJORAS_WRATH_BODYPART_RIGHT_UPPER_ARM,
    // This body part is redundant; it's located at the exact same position as `MAJORAS_WRATH_BODYPART_RIGHT_FOREARM`.
    /*  7 */ MAJORAS_WRATH_BODYPART_RIGHT_LOWER_ARM_ROOT,
    /*  8 */ MAJORAS_WRATH_BODYPART_RIGHT_FOREARM,
    /*  9 */ MAJORAS_WRATH_BODYPART_RIGHT_THIGH,
    /* 10 */ MAJORAS_WRATH_BODYPART_RIGHT_SHIN,
    /* 11 */ MAJORAS_WRATH_BODYPART_RIGHT_FOOT,
    /* 12 */ MAJORAS_WRATH_BODYPART_LEFT_THIGH,
    /* 13 */ MAJORAS_WRATH_BODYPART_LEFT_SHIN,
    /* 14 */ MAJORAS_WRATH_BODYPART_LEFT_FOOT,
    /* 15 */ MAJORAS_WRATH_BODYPART_MAX
} MajorasWrathBodyPart;

typedef enum MajorasIncarnationBodyPart {
    /*  0 */ MAJORAS_INCARNATION_BODYPART_EYESTALK,
    // This body part is redundant; it's located at the exact same position as `MAJORAS_INCARNATION_BODYPART_LEFT_UPPER_ARM`.
    // Additionally, the developers used this index for both the mask limb and the left arm root limb; since the left arm
    // root limb has a larger `limbIndex` than the mask limb, that's the limb this body part ends up attached to.
    /*  1 */ MAJORAS_INCARNATION_BODYPART_LEFT_ARM_ROOT,
    // This body part is redundant; it's located at the exact same position as `MAJORAS_INCARNATION_BODYPART_RIGHT_THIGH`.
    /*  2 */ MAJORAS_INCARNATION_BODYPART_RIGHT_LEG_ROOT,
    /*  3 */ MAJORAS_INCARNATION_BODYPART_LEFT_UPPER_ARM,
    /*  4 */ MAJORAS_INCARNATION_BODYPART_LEFT_FOREARM,
    /*  5 */ MAJORAS_INCARNATION_BODYPART_LEFT_HAND,
    /*  6 */ MAJORAS_INCARNATION_BODYPART_RIGHT_UPPER_ARM,
    /*  7 */ MAJORAS_INCARNATION_BODYPART_RIGHT_FOREARM,
    /*  8 */ MAJORAS_INCARNATION_BODYPART_RIGHT_HAND,
    /*  9 */ MAJORAS_INCARNATION_BODYPART_RIGHT_THIGH,
    /* 10 */ MAJORAS_INCARNATION_BODYPART_RIGHT_SHIN,
    /* 11 */ MAJORAS_INCARNATION_BODYPART_RIGHT_FOOT,
    /* 12 */ MAJORAS_INCARNATION_BODYPART_LEFT_THIGH,
    /* 13 */ MAJORAS_INCARNATION_BODYPART_LEFT_SHIN,
    /* 14 */ MAJORAS_INCARNATION_BODYPART_LEFT_FOOT,
    /* 15 */ MAJORAS_INCARNATION_BODYPART_MAX
} MajorasIncarnationBodyPart;

#define MAJORA_BODYPART_MAX MAX((s32)MAJORAS_WRATH_BODYPART_MAX, (s32)MAJORAS_INCARNATION_BODYPART_MAX)

typedef enum MajorasWrathColliderBodyPart {
    /*  0 */ MAJORAS_WRATH_COLLIDER_BODYPART_HEAD,
    /*  1 */ MAJORAS_WRATH_COLLIDER_BODYPART_TORSO,
    /*  2 */ MAJORAS_WRATH_COLLIDER_BODYPART_PELVIS,
    /*  3 */ MAJORAS_WRATH_COLLIDER_BODYPART_LEFT_UPPER_ARM,
    /*  4 */ MAJORAS_WRATH_COLLIDER_BODYPART_LEFT_FOREARM,
    /*  5 */ MAJORAS_WRATH_COLLIDER_BODYPART_RIGHT_UPPER_ARM,
    /*  6 */ MAJORAS_WRATH_COLLIDER_BODYPART_RIGHT_FOREARM,
    /*  7 */ MAJORAS_WRATH_COLLIDER_BODYPART_LEFT_THIGH,
    /*  8 */ MAJORAS_WRATH_COLLIDER_BODYPART_LEFT_SHIN,
    /*  9 */ MAJORAS_WRATH_COLLIDER_BODYPART_RIGHT_THIGH,
    /* 10 */ MAJORAS_WRATH_COLLIDER_BODYPART_RIGHT_SHIN,
    /* 11 */ MAJORAS_WRATH_COLLIDER_BODYPART_MAX
} MajorasWrathColliderBodyPart;

typedef enum MajorasIncarnationColliderBodyPart {
    /*  0 */ MAJORAS_INCARNATION_COLLIDER_BODYPART_EYESTALK,
    // The developers used this index for both the mask limb and the left arm root limb; since the left arm
    // root limb has a larger `limbIndex` than the mask limb, that's the limb this body part ends up initially
    // attached to. However, the developers seemingly accounted for this by offsetting the collider such that
    // it actually appears attached to the mask limb instead.
    /*  1 */ MAJORAS_INCARNATION_COLLIDER_BODYPART_MASK,
    // This collider is positioned at the room origin because it isn't attached to any of Incarnation's limbs
    // within `sLimbToColliderBodyParts`; since the memory for an actor's instance is zeroed out before it's
    // used, and since this collider isn't attached to any limbs, its position will remain stuck at (0, 0, 0).
    // It seems like the developers *tried* to work around this by giving this collider a massive offset within
    // `sLimbColliderOffsets`, but it doesn't work because the offset is only applied if the collider actually
    // corresponds to a limb.
    /*  2 */ MAJORAS_INCARNATION_COLLIDER_BODYPART_ROOM_ORIGIN,
    /*  3 */ MAJORAS_INCARNATION_COLLIDER_BODYPART_LEFT_UPPER_ARM,
    /*  4 */ MAJORAS_INCARNATION_COLLIDER_BODYPART_LEFT_FOREARM,
    /*  5 */ MAJORAS_INCARNATION_COLLIDER_BODYPART_RIGHT_UPPER_ARM,
    /*  6 */ MAJORAS_INCARNATION_COLLIDER_BODYPART_RIGHT_FOREARM,
    /*  7 */ MAJORAS_INCARNATION_COLLIDER_BODYPART_LEFT_THIGH,
    /*  8 */ MAJORAS_INCARNATION_COLLIDER_BODYPART_LEFT_SHIN,
    /*  9 */ MAJORAS_INCARNATION_COLLIDER_BODYPART_RIGHT_THIGH,
    /* 10 */ MAJORAS_INCARNATION_COLLIDER_BODYPART_RIGHT_SHIN,
    /* 11 */ MAJORAS_INCARNATION_COLLIDER_BODYPART_MAX
} MajorasIncarnationColliderBodyPart;

#define MAJORA_COLLIDER_BODYPART_MAX MAX((s32)MAJORAS_WRATH_COLLIDER_BODYPART_MAX, (s32)MAJORAS_INCARNATION_COLLIDER_BODYPART_MAX)

typedef enum MajorasIncarnationPumpBodyPart {
    /* 0 */ MAJORAS_INCARNATION_PUMP_BODYPART_RIGHT_ARM,
    /* 1 */ MAJORAS_INCARNATION_PUMP_BODYPART_LEFT_ARM,
    /* 2 */ MAJORAS_INCARNATION_PUMP_BODYPART_RIGHT_LEG,
    /* 3 */ MAJORAS_INCARNATION_PUMP_BODYPART_LEFT_LEG,
    /* 4 */ MAJORAS_INCARNATION_PUMP_BODYPART_MAX
} MajorasIncarnationPumpBodyPart;

typedef struct Boss07 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ Boss07ActionFunc actionFunc;
    /* 0x0148 */ u8 shouldStartDeath;
    /* 0x0149 */ u8 shouldUpdateTentaclesOrWhips;
    /* 0x014A */ u8 envEffectOn;
    /* 0x014B */ u8 envEffectTimer;
    /* 0x014C */ s16 actionTimer;
    /* 0x014E */ u8 actionState;
    /* 0x014F */ u8 whipCrackTimer;
    /* 0x0150 */ s16 timers[3];
    /* 0x0156 */ s16 jumpSfxTimer;
    /* 0x0158 */ s16 collisionTimer; // turns off collision
    /* 0x015A */ s16 whipCollisionTimer;
    /* 0x015C */ s16 invincibilityTimer;
    /* 0x015E */ s16 damagedFlashTimer;
    /* 0x0160 */ s16 motionBlurAlpha;
    /* 0x0164 */ Vec3f moveTarget;
    /* 0x0170 */ f32 velocity_170; // move speed for wrath sidestep and spin, turn rate for all others
    /* 0x0174 */ u8 canDodge;
    /* 0x0178 */ f32 topSpinAngle; 
    /* 0x017C */ f32 topSpinRate;
    /* 0x0180 */ s16 unk_180; // top precess angle and incarnation yaw target
    /* 0x0184 */ f32 unk_184; // y rot during long whip attack
    /* 0x0188 */ f32 unk_188; // x rot during long whip attack
    /* 0x018C */ f32 flySpeedTarget;
    /* 0x0190 */ SkelAnime skelAnime;
    /* 0x01D4 */ f32 animEndFrame;
    /* 0x01D8 */ s32 bodyDecayRate;
    /* 0x01DC */ Vec3s jointTable[MAJORA_LIMB_COUNT];
    /* 0x0284 */ Vec3s morphTable[MAJORA_LIMB_COUNT];
    /* 0x032C */ f32 unk_32C; // shock scale related
    /* 0x0330 */ f32 unk_330; // shock scale related
    /* 0x0334 */ Vec3f bodyPartsPos[MAJORA_BODYPART_MAX];
    /* 0x03E8 */ ColliderJntSph bodyCollider;
    /* 0x0408 */ ColliderJntSphElement bodyColliderElements[MAJORA_COLLIDER_BODYPART_MAX];
    /* 0x06C8 */ ColliderJntSph kickCollider;
    /* 0x06E8 */ ColliderJntSphElement kickColliderElements[1];
    /* 0x0728 */ ColliderCylinder unusedCollider;
    /* 0x0774 */ u8 activateRemains;
    /* 0x0778 */ s32 whipTopIndex; // whip top spawn index
    /* 0x077C */ f32 whipScale;
    /* 0x0780 */ s32 whipShockIndexHigh; // whip shock index
    /* 0x0784 */ s32 whipShockIndexLow; // whip shock index
    /* 0x0788 */ MajoraWhip rightWhip;
    /* 0x0F7C */ s16 whipWrapIndex;
    /* 0x0F7E */ s16 whipGrabIndex;
    /* 0x0F80 */ Vec3f whipGrabPos;
    /* 0x0F8C */ f32 unk_F8C;
    /* 0x0F90 */ f32 unk_F90;
    /* 0x0F94 */ MajoraWhip leftWhip;
    /* 0x1788 */ Vec3f incarnationFeetPos[2];
    /* 0x17A0 */ Vec3f incarnationLeftHandPos;
    /* 0x17AC */ Vec3f incarnationRightHandPos;
    /* 0x17B8 */ f32 incarnationIntroBodyPartsScale[MAJORAS_INCARNATION_PUMP_BODYPART_MAX];
    /* 0x17C8 */ f32 incarnationIntroBodyPartsScaleSpeed[MAJORAS_INCARNATION_PUMP_BODYPART_MAX];
    /* 0x17D8 */ Vec3s csHeadRot;
    /* 0x17E0 */ f32 incarnationArmScale;
    /* 0x17E4 */ f32 incarnationLegScale;
    /* 0x17E8 */ f32 unk_17E8; // limb pump average
    /* 0x17E8 */ f32 unk_17EC; // limb pump amplitude
    /* 0x17F0 */ f32 incarnationMaskScaleY;
    /* 0x17F4 */ f32 incarnationMaskScaleX; 
    /* 0x17F8 */ f32 drawDmgEffScale;
    /* 0x17FC */ f32 drawDmgEffFrozenSteamScale;
    /* 0x1800 */ f32 drawDmgEffAlpha;
    /* 0x1804 */ u8 drawDmgEffType;
    /* 0x1805 */ u8 drawDmgEffState;
    /* 0x1806 */ s16 drawDmgEffTimer;
    /* 0x1808 */ u8 lensFlareOn;
    /* 0x180c */ f32 lensFlareScale;
    /* 0x1810 */ Vec3f lensFlarePos;
    /* 0x181C */ s16 shotColorIndex;
    /* 0x1820 */ ColliderCylinder spawnCollider;
    /* 0x186C */ s16 dmgShakeTimer;
    /* 0x1870 */ f32 tentLengthScale;
    /* 0x1874 */ u8 unk_1874; // wavy tentacles
    /* 0x1878 */ Vec3f tentAttachPos;
    /* 0x1884 */ s32 maskEyeState;
    /* 0x1888 */ u8 noclipTimer;
    /* 0x188C */ f32 eyeBeamsZscale;
    /* 0x1890 */ f32 beamFocusOrbScale;
    /* 0x1894 */ f32 unk_1894;
    /* 0x1898 */ f32 beamXYscale;
    /* 0x189C */ Vec3f unk_189C;
    /* 0x18A8 */ Vec3f unk_18A8;
    /* 0x18B4 */ Vec3f unk_18B4;
    /* 0x18C0 */ f32 unk_18C0;
    /* 0x18C4 */ s16 beamTargetPitch;
    /* 0x18C6 */ s16 beamTargetYaw;
    /* 0x18C8 */ s16 remainsOrbRot;
    /* 0x18CC */ f32 knockbackVelocityX;
    /* 0x18D0 */ f32 knockbackVelocityZ;
    /* 0x18D4 */ s16 angularVelocity;
    /* 0x18D6 */ s16 timer_18D6;
    /* 0x18D8 */ s16 beamDmgTimer;
    /* 0x18DA */ u8 readyDeath;
    /* 0x18DB */ u8 readyShot;
    /* 0x18DC */ s32 effectIndex;
    /* 0x18E0 */ Vec3f beamMarkLastPos;
    /* 0x18EC */ u8 beamOn;
    /* 0x18ED */ u8 beamOnLastFrame;
    /* 0x18F0 */ ColliderQuad maskFrontCollider;
    /* 0x1970 */ ColliderQuad maskBackCollider;
    /* 0x19F0 */ MajoraTentacle tentacles[MAJORA_TENT_MAX];
    /* 0xAB40 */ s16 timer_AB40;
    /* 0xAB44 */ f32 introOrbScale;
    /* 0xAB48 */ u8 noShadow;
    /* 0xAB4C */ f32 deathOrbScale;
    /* 0xAB50 */ f32 deathLightScale[30];
    /* 0xABC8 */ u32 cutsceneTimer; // used as an animation loop count in `Boss07_Incarnation_Hopak`
    /* 0xABCC */ s32 sfxTimer; // used as an index in `Boss07_Mask_IntroCutscene`
    /* 0xABD0 */ s16 cutsceneState; // TODO: investigate how it's used for something else in `Boss07_Mask_Spin`
    /* 0xABD2 */ s16 subCamId;
    /* 0xABD4 */ Vec3f subCamEye;
    /* 0xABE0 */ Vec3f subCamAt;
    /* 0xABEC */ Vec3f subCamEyeNext;
    /* 0xABF8 */ Vec3f subCamAtNext;
    /* 0xAC04 */ f32 subCamRotY;
    /* 0xAC08 */ f32 subCamRotVelocity;
    /* 0xAC0C */ f32 subCamSpeedMod;
    /* 0xAC10 */ UNK_TYPE1 unkAC10[4]; // probably float
    /* 0xAC14 */ f32 subCamEyeModY;
    /* 0xAC18 */ UNK_TYPE1 unkAC18[8]; // probably floats
} Boss07; // size = 0xAC20

#endif // Z_BOSS_07_H
