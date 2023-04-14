#ifndef Z_BOSS_07_H
#define Z_BOSS_07_H

#include "global.h"
#include "objects/object_boss07/object_boss07.h"

struct Boss07;

#define MAJORAS_TENT_LENGTH 10
#define MAJORAS_TENT_COUNT 25
#define MAJORAS_TENT_MAX 100
#define MAJORAS_WHIP_MAX_LENGTH 50

#define MAJORAS_LIMB_COUNT MAX(MAJORAS_MASK_LIMB_MAX, MAX(MAJORAS_INCARNATION_LIMB_MAX, MAJORAS_WRATH_LIMB_MAX))

typedef void (*Boss07ActionFunc)(struct Boss07*, struct PlayState*);

typedef enum {
    /*   0 */ MAJORAS_BOSS,
    /*  10 */ MAJORAS_MASK = 10,
    /*  11 */ MAJORAS_MASK_CS,
    /*  20 */ MAJORAS_INCARNATION = 20,
    /*  21 */ MAJORAS_AFTERIMAGE,
    /*  30 */ MAJORAS_WRATH = 30,
    /* 100 */ MAJORAS_REMAINS_SHOT = 100,
    /* 101 */ MAJORAS_INCARNATION_SHOT,
    /* 150 */ MAJORAS_STATIC = 150,
    /* 180 */ MAJORAS_TOP = 180,
    /* 200 */ MAJORAS_REMAINS = 200,
} MajoraParams;

typedef struct {
    Vec3f base;
    Vec3f pos[MAJORAS_TENT_LENGTH];
    Vec3f rot[MAJORAS_TENT_LENGTH];
    Vec3f vel[MAJORAS_TENT_LENGTH];
} Boss07Tentacle; // size = 0x174 (0xC + 0x24 * length)

typedef struct {
    Vec3s baseRot;
    f32 gravity;
    f32 mobility;
    f32 drag;
    f32 tension;
    Vec3f basePos;
    Vec3f pos[MAJORAS_WHIP_MAX_LENGTH];
    Vec3f rot[MAJORAS_WHIP_MAX_LENGTH];
    Vec3f vel[MAJORAS_WHIP_MAX_LENGTH];
    f32 unk_72C[MAJORAS_WHIP_MAX_LENGTH]; // unused, probably a stretch factor
} Boss07Whip; // size = 0x7F4 (0x24 + 0x28 * max)

typedef struct Boss07 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ Boss07ActionFunc actionFunc;
    /* 0x0148 */ u8 startDeath;
    /* 0x0149 */ u8 updateWhips;
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
    /* 0x015E */ s16 dmgFogEffectTimer;
    /* 0x0160 */ s16 motionBlurAlpha;
    /* 0x0162 */ s16 unused_162;
    /* 0x0164 */ Vec3f moveTarget;
    /* 0x0170 */ f32 vel_170; // move speed for wrath sidestep and spin, turn rate for all others
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
    /* 0x01DC */ Vec3s jointTable[MAJORAS_LIMB_COUNT];
    /* 0x0284 */ Vec3s morphTable[MAJORAS_LIMB_COUNT];
    /* 0x032C */ f32 unk_32C; // shock scale related
    /* 0x0330 */ f32 unk_330; // shock scale related
    /* 0x0334 */ Vec3f bodyPartsPos[15];
    /* 0x03E8 */ ColliderJntSph bodyCollider;
    /* 0x0408 */ ColliderJntSphElement bodyElements[11];
    /* 0x06C8 */ ColliderJntSph kickCollider;
    /* 0x06E8 */ ColliderJntSphElement kickElements[1];
    /* 0x0728 */ ColliderCylinder unusedCollider;
    /* 0x0774 */ u8 activateRemains;
    /* 0x0778 */ s32 whipTopIndex; // whip top spawn index
    /* 0x077C */ f32 whipScale;
    /* 0x0780 */ s32 whipShockIndexHigh; // whip shock index
    /* 0x0784 */ s32 whipShockIndexLow; // whip shock index
    /* 0x0788 */ Boss07Whip rightWhip;
    /* 0x0F7C */ s16 whipWrapIndex;
    /* 0x0F7E */ s16 whipGrabIndex;
    /* 0x0F80 */ Vec3f whipGrabPos;
    /* 0x0F8C */ f32 unk_F8C;
    /* 0x0F90 */ f32 unk_F90;
    /* 0x0F94 */ Boss07Whip leftWhip;
    /* 0x1788 */ Vec3f incFeetPos[2];
    /* 0x17A0 */ Vec3f incLeftHandPos;
    /* 0x17AC */ Vec3f incRightHandPos;
    /* 0x17B8 */ f32 unk_17B8[4]; // limb scale stuff in inc intro
    /* 0x17C8 */ f32 unk_17C8[4]; // limb scale stuff in inc intro
    /* 0x17D8 */ Vec3s csHeadRot;
    /* 0x17E0 */ f32 armScale;
    /* 0x17E4 */ f32 legScale;
    /* 0x17E8 */ f32 unk_17E8; // limb pump average
    /* 0x17E8 */ f32 unk_17EC; // limb pump amplitude
    /* 0x17F0 */ f32 chestScaleY;
    /* 0x17F4 */ f32 chestScaleX; 
    /* 0x17F8 */ f32 unk_17F8; // effect scale
    /* 0x17FC */ f32 unk_17FC; // effect steam
    /* 0x1800 */ f32 unk_1800; // effect alpha
    /* 0x1804 */ u8 unk_1804; // damage effect type
    /* 0x1805 */ u8 unk_1805; // damage state
    /* 0x1806 */ s16 unk_1806; // timer related to damage
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
    /* 0x18CC */ f32 xRecoil;
    /* 0x18D0 */ f32 zRecoil;
    /* 0x18D4 */ s16 spinVel;
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
    /* 0x19F0 */ Boss07Tentacle tentacles[MAJORAS_TENT_MAX];
    /* 0xAB40 */ s16 timer_AB40;
    /* 0xAB44 */ f32 introOrbScale;
    /* 0xAB48 */ u8 noShadow;
    /* 0xAB4C */ f32 deathOrbScale;
    /* 0xAB50 */ f32 deathLightScale[30];
    /* 0xABC8 */ u32 timer_ABC8;
    /* 0xABCC */ s32 timer_ABCC;
    /* 0xABD0 */ s16 csState;
    /* 0xABD2 */ s16 subCamIndex;
    /* 0xABD4 */ Vec3f subCamEye;
    /* 0xABE0 */ Vec3f subCamAt;
    /* 0xABEC */ Vec3f subCamNextEye;
    /* 0xABF8 */ Vec3f subCamNextAt;
    /* 0xAC04 */ f32 subCamRotY;
    /* 0xAC08 */ f32 subCamRotVel;
    /* 0xAC0C */ f32 subCamSpeedMod;
    /* 0xAC10 */ UNK_TYPE1 unkAC10[4]; // probably float
    /* 0xAC14 */ f32 subCamEyeModY;
    /* 0xAC18 */ UNK_TYPE1 unkAC18[8]; // probably floats
} Boss07; // size = 0xAC20

#endif // Z_BOSS_07_H
