#ifndef Z_BOSS_07_H
#define Z_BOSS_07_H

#include "global.h"

struct Boss07;

#define MAJORA_TENT_LENGTH 10
#define MAJORA_TENT_COUNT 25
#define MAJORA_TENT_MAX 100
#define MAJORA_WHIP_MAX_LENGTH 50

#define MAJORA_MASK_LIMB_COUNT 19
#define MAJORA_INCARNATION_LIMB_COUNT 25
#define MAJORA_WRATH_LIMB_COUNT 28
#define MAJORA_LIMB_COUNT MAX(MAJORA_MASK_LIMB_COUNT, MAX(MAJORA_INCARNATION_LIMB_COUNT, MAJORA_WRATH_LIMB_COUNT))

typedef void (*Boss07ActionFunc)(struct Boss07*, GlobalContext*);

typedef struct {
    Vec3f base;
    Vec3f pos[MAJORA_TENT_LENGTH];
    Vec3f rot[MAJORA_TENT_LENGTH];
    Vec3f pull[MAJORA_TENT_LENGTH];
} Boss07Tentacle; // size = 0x174 (0xC + 0x24 * length)

typedef struct {
    Vec3s baseRot;
    f32 gravity;
    f32 stiffness;
    f32 drag;
    f32 tension;
    Vec3f basePos;
    Vec3f pos[MAJORA_WHIP_MAX_LENGTH];
    Vec3f rot[MAJORA_WHIP_MAX_LENGTH];
    Vec3f pull[MAJORA_WHIP_MAX_LENGTH];
    f32 unk_72C[MAJORA_WHIP_MAX_LENGTH]; // unused, probably a stretch factor
} Boss07Whip; // size = 0x7F4 (0x24 + 0x28 * max)

typedef struct Boss07 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ Boss07ActionFunc actionFunc;
    /* 0x0148 */ u8 unk_148;
    /* 0x0149 */ u8 unk_149;
    /* 0x014A */ u8 unk_14A;
    /* 0x014B */ u8 unk_14B;
    /* 0x014C */ s16 actionTimer;
    /* 0x014E */ u8 actionState;
    /* 0x014F */ u8 unk_14F;
    /* 0x0150 */ s16 timers[3];
    /* 0x0156 */ s16 unk_156;
    /* 0x0158 */ s16 unk_158;
    /* 0x015A */ s16 unk_15A;
    /* 0x015C */ s16 unk_15C;
    /* 0x015E */ s16 unk_15E;
    /* 0x0160 */ s16 unk_160;
    /* 0x0162 */ s16 unk_162;
    /* 0x0164 */ Vec3f unk_164;
    /* 0x0170 */ f32 unk_170;
    /* 0x0174 */ u8 unk_174;
    /* 0x0178 */ f32 unk_178;
    /* 0x017C */ f32 unk_17C;
    /* 0x0180 */ s16 unk_180;
    /* 0x0184 */ f32 unk_184;
    /* 0x0188 */ f32 unk_188;
    /* 0x018C */ f32 unk_18C;
    /* 0x0190 */ SkelAnime skelAnime;
    /* 0x01D4 */ f32 unk_1D4;
    /* 0x01D8 */ s32 unk_1D8;
    /* 0x01DC */ Vec3s jointTable[MAJORA_LIMB_COUNT];
    /* 0x0284 */ Vec3s morphTable[MAJORA_LIMB_COUNT];
    /* 0x032C */ f32 unk_32C;
    /* 0x0330 */ f32 unk_330;
    /* 0x0334 */ Vec3f bodyPartsPos[15];
    /* 0x03E8 */ ColliderJntSph sph1;
    /* 0x0408 */ ColliderJntSphElement sphElems1[11];
    /* 0x06C8 */ ColliderJntSph sph2;
    /* 0x06E8 */ ColliderJntSphElement sphElems2[1];
    /* 0x0728 */ ColliderCylinder cyl1;
    /* 0x0774 */ u8 unk_774;
    /* 0x0778 */ s32 unk_778;
    /* 0x077C */ f32 whipScale;
    /* 0x0780 */ s32 unk_780;
    /* 0x0784 */ s32 unk_784;
    /* 0x0788 */ Boss07Whip rightWhip;
    /* 0x0F7C */ s16 unk_F7C;
    /* 0x0F7E */ s16 unk_F7E;
    /* 0x0F80 */ Vec3f unk_F80;
    /* 0x0F8C */ f32 unk_F8C;
    /* 0x0F90 */ f32 unk_F90;
    /* 0x0F94 */ Boss07Whip leftWhip;
    /* 0x1788 */ Vec3f unk_1788[2];
    /* 0x17A0 */ Vec3f unk_17A0;
    /* 0x17AC */ Vec3f unk_17AC;
    /* 0x17B8 */ f32 unk_17B8[4];
    /* 0x17C8 */ f32 unk_17C8[4];
    /* 0x17D8 */ s16 unk_17D8;
    /* 0x17DA */ s16 unk_17DA;
    /* 0x17DA */ s16 unk_17DC;
    /* 0x17E0 */ f32 unk_17E0;
    /* 0x17E4 */ f32 unk_17E4;
    /* 0x17E8 */ f32 unk_17E8;
    /* 0x17E8 */ f32 unk_17EC;
    /* 0x17F0 */ f32 unk_17F0;
    /* 0x17F4 */ f32 unk_17F4;
    /* 0x17F8 */ f32 unk_17F8;
    /* 0x17FC */ f32 unk_17FC;
    /* 0x1800 */ f32 unk_1800;
    /* 0x1804 */ u8 unk_1804;
    /* 0x1805 */ u8 unk_1805;
    /* 0x1806 */ s16 unk_1806;
    /* 0x1808 */ u8 unk_1808;
    /* 0x180c */ f32 unk_180C;
    /* 0x1810 */ Vec3f unk_1810;
    /* 0x181C */ s16 unk_181C;
    /* 0x1820 */ ColliderCylinder cyl2;
    /* 0x186C */ s16 unk_186C;
    /* 0x1870 */ f32 unk_1870;
    /* 0x1874 */ u8 unk_1874;
    /* 0x1878 */ Vec3f unk_1878;
    /* 0x1884 */ s32 unk_1884;
    /* 0x1888 */ u8 unk_1888;
    /* 0x188C */ f32 unk_188C;
    /* 0x1890 */ f32 unk_1890;
    /* 0x1894 */ f32 unk_1894;
    /* 0x1898 */ f32 unk_1898;
    /* 0x189C */ Vec3f unk_189C;
    /* 0x18A8 */ Vec3f unk_18A8;
    /* 0x18B4 */ Vec3f unk_18B4;
    /* 0x18C0 */ f32 unk_18C0;
    /* 0x18C4 */ s16 unk_18C4;
    /* 0x18C6 */ s16 unk_18C6;
    /* 0x18C8 */ s16 unk_18C8;
    /* 0x18CC */ f32 unk_18CC;
    /* 0x18D0 */ f32 unk_18D0;
    /* 0x18D4 */ s16 unk_18D4;
    /* 0x18D6 */ s16 unk_18D6;
    /* 0x18D8 */ s16 unk_18D8;
    /* 0x18DA */ u8 unk_18DA;
    /* 0x18DB */ u8 unk_18DB;
    /* 0x18DC */ s32 effectIndex;
    /* 0x18E0 */ Vec3f unk_18E0;
    /* 0x18EC */ u8 unk_18EC;
    /* 0x18ED */ u8 unk_18ED;
    /* 0x18F0 */ ColliderQuad quad1;
    /* 0x1970 */ ColliderQuad quad2;
    /* 0x19F0 */ Boss07Tentacle tentacles[MAJORA_TENT_MAX];
    /* 0xAB40 */ s16 unk_AB40;
    /* 0xAB44 */ f32 unk_AB44;
    /* 0xAB48 */ u8 unk_AB48;
    /* 0xAB4C */ f32 unk_AB4C;
    /* 0xAB50 */ f32 deathLightScale[30];
    /* 0xABC8 */ u32 unk_ABC8;
    /* 0xABCC */ s32 unk_ABCC;
    /* 0xABD0 */ s16 csState;
    /* 0xABD2 */ s16 csCamIndex;
    /* 0xABD4 */ Vec3f csCamEye;
    /* 0xABE0 */ Vec3f csCamAt;
    /* 0xABEC */ Vec3f csCamNextEye;
    /* 0xABF8 */ Vec3f csCamNextAt;
    /* 0xAC04 */ f32 csCamRotY;
    /* 0xAC08 */ f32 csCamRotVel;
    /* 0xAC0C */ f32 csCamSpeedMod;
    /* 0xAC10 */ Vec3f csCamEyeMod;
    /* 0xAC1C */ char unkAC1C[4];
} Boss07; // size = 0xAC20

extern const ActorInit Boss_07_InitVars;

typedef enum {
    /*   0 */ MAJORA_BOSS,
    /*  10 */ MAJORA_MASK = 10,
    /*  11 */ MAJORA_MASK_CS,
    /*  20 */ MAJORA_INCARNATION = 20,
    /*  21 */ MAJORA_AFTERIMAGE,
    /*  30 */ MAJORA_WRATH = 30,
    /* 100 */ MAJORA_REMAINS_SHOT = 100,
    /* 101 */ MAJORA_INCARNATION_SHOT,
    /* 150 */ MAJORA_STATIC = 150,
    /* 180 */ MAJORA_TOP = 180,
    /* 200 */ MAJORA_REMAINS = 200,
} MajoraParams;

#endif // Z_BOSS_07_H
