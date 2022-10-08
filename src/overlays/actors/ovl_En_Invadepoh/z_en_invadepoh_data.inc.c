#include "global.h"
#include "z_en_invadepoh.h"
#include "assets/objects/object_ma1/object_ma1.h"
#include "assets/objects/object_ma2/object_ma2.h"

void EnInvadepoh_func_80B4627C(Actor* thisx, PlayState* play);
void EnInvadepoh_func_80B46414(Actor* thisx, PlayState* play);
void EnInvadepoh_func_80B46520(Actor* thisx, PlayState* play2);
void EnInvadepoh_func_80B465CC(Actor* thisx, PlayState* play2);
void EnInvadepoh_func_80B46644(Actor* thisx, PlayState* play);
void EnInvadepoh_func_80B468B4(Actor* thisx, PlayState* play2);
void EnInvadepoh_func_80B469C4(Actor* thisx, PlayState* play);
void EnInvadepoh_func_80B46A80(Actor* thisx, PlayState* play);

void EnInvadepoh_func_80B46BB0(Actor* thisx, PlayState* play);
void EnInvadepoh_func_80B46BC0(Actor* thisx, PlayState* play2);
void EnInvadepoh_func_80B46C08(Actor* thisx, PlayState* play);
void EnInvadepoh_func_80B46C34(Actor* thisx, PlayState* play);
void EnInvadepoh_func_80B46C7C(Actor* thisx, PlayState* play);
void EnInvadepoh_func_80B46C50(Actor* thisx, PlayState* play2);
void EnInvadepoh_func_80B46C94(Actor* thisx, PlayState* play2);
void EnInvadepoh_func_80B46CC0(Actor* thisx, PlayState* play2);
void EnInvadepoh_func_80B46CF4(Actor* thisx, PlayState* play2);
void EnInvadepoh_func_80B46D28(Actor* thisx, PlayState* play2);

void EnInvadepoh_func_80B45A4C(EnInvadePohUnkStruct_324_1*, EnInvadepohUnkUnion**);
void EnInvadepoh_func_80B45A94(EnInvadePohUnkStruct_324_1*, EnInvadepohUnkUnion**);
void EnInvadepoh_func_80B45B1C(EnInvadePohUnkStruct_324_1*, EnInvadepohUnkUnion**);

void EnInvadepoh_func_80B46184(EnInvadepohStructD_80B50350* arg0);

ColliderCylinderInit D_80B4E8B0 = {
    {
        COLTYPE_HIT3,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK4,
        { 0xF7CFFFFF, 0x00, 0x04 },
        { 0x00003820, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NONE,
        BUMP_ON,
        OCELEM_ON,
    },
    { 40, 95, 10, { 0, 0, 0 } },
};
ColliderCylinderInit D_80B4E8DC = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0x00000000, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 18, 46, 0, { 0, 0, 0 } },
};
ColliderCylinderInit D_80B4E908 = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK1,
        { 0x00000000, 0x00, 0x00 },
        { 0x00000000, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 13, 19, 0, { 0, 0, 0 } },
};
Vec3f D_80B4E934 = { 216.0f, -20.0f, 1395.0f };
s32 D_80B4E940 = 0;
TexturePtr sRomaniEyeTextures[5] = {
    gRomaniEyeOpenTex, gRomaniEyeHalfTex, gRomaniEyeClosedTex, gRomaniEyeHappyTex, gRomaniEyeSadTex,
};
TexturePtr sRomaniMouthTextures[4] = {
    gRomaniMouthHappyTex,
    gRomaniMouthFrownTex,
    gRomaniMouthHangingOpenTex,
    gRomaniMouthSmileTex,
};
s8 D_80B4E968 = 0;
TexturePtr sCremiaEyeTextures[6] = {
    gCremiaEyeOpenTex, gCremiaEyeHalfTex, gCremiaEyeClosedTex, gCremiaEyeHappyTex, gCremiaEyeAngryTex, gCremiaEyeSadTex,
};
TexturePtr sCremiaMouthTextures[4] = {
    gCremiaMouthNormalTex,
    gCremiaMouthSlightSmileTex,
    gCremiaMouthFrownTex,
    gCremiaMouthHangingOpenTex,
};
s8 D_80B4E994 = 0;
s8 D_80B4E998 = 0;
s8 D_80B4E99C[1] = { 0 };
s8 D_80B4E9A0[4] = { 0, 1, 2, 0 };
s8 D_80B4E9A4[5] = { 0, 1, 2, 1, 0 };
s8 D_80B4E9AC[6] = { 0, 1, 2, 2, 1, 0 };
s8 D_80B4E9B4[8] = { 0, 1, 2, 1, 0, 1, 2, 0 };
s8 D_80B4E9BC[1] = { 1 };
s8 D_80B4E9C0[1] = { 3 };
EnInvadepohUnkStruct2 D_80B4E9C4 = { D_80B4E99C, 1 };
EnInvadepohUnkStruct2 D_80B4E9CC = { D_80B4E9A0, 4 };
EnInvadepohUnkStruct2 D_80B4E9D4 = { D_80B4E9A4, 5 };
EnInvadepohUnkStruct2 D_80B4E9DC = { D_80B4E9AC, 6 };
EnInvadepohUnkStruct2 D_80B4E9E4 = { D_80B4E9B4, 8 };
EnInvadepohUnkStruct2 D_80B4E9EC = { D_80B4E9BC, 1 };
EnInvadepohUnkStruct2 D_80B4E9F4 = { D_80B4E9C0, 1 };
EnInvadepohUnkStruct3 D_80B4E9FC = { 0, &D_80B4E9C4 };
EnInvadepohUnkStruct4 D_80B4EA04[4] = {
    { 2, 0.5f },
    { 3, 0.9f },
    { 4, 0.97f },
    { 5, 1.0f },
};
EnInvadepohUnkStruct4 D_80B4EA24[1] = { 1, 1.0f };
EnInvadepohUnkStruct6 D_80B4EA2C = { 2, &D_80B4E9C4, 4, D_80B4EA04, 40, 60 };
EnInvadepohUnkStruct5 D_80B4EA40 = { 1, &D_80B4E9CC, 1, D_80B4EA24 };
EnInvadepohUnkStruct5 D_80B4EA50 = { 1, &D_80B4E9D4, 1, D_80B4EA24 };
EnInvadepohUnkStruct5 D_80B4EA60 = { 1, &D_80B4E9DC, 1, D_80B4EA24 };
EnInvadepohUnkStruct5 D_80B4EA70 = { 1, &D_80B4E9E4, 1, D_80B4EA24 };
EnInvadepohUnkStruct3 D_80B4EA80 = { 0, &D_80B4E9EC };
EnInvadepohUnkStruct3 D_80B4EA88 = { 0, &D_80B4E9F4 };
EnInvadepohUnkUnion* D_80B4EA90[8] = {
    (EnInvadepohUnkUnion*)&D_80B4E9FC, (EnInvadepohUnkUnion*)&D_80B4EA2C, (EnInvadepohUnkUnion*)&D_80B4EA40,
    (EnInvadepohUnkUnion*)&D_80B4EA50, (EnInvadepohUnkUnion*)&D_80B4EA60, (EnInvadepohUnkUnion*)&D_80B4EA70,
    (EnInvadepohUnkUnion*)&D_80B4EA80, (EnInvadepohUnkUnion*)&D_80B4EA88,
};
s8 D_80B4EAB0[1] = { 0 };
s8 D_80B4EAB4[1] = { 1 };
s8 D_80B4EAB8[1] = { 2 };
s8 D_80B4EABC[1] = { 3 };
EnInvadepohUnkStruct2 D_80B4EAC0 = { D_80B4EAB0, 1 };
EnInvadepohUnkStruct2 D_80B4EAC8 = { D_80B4EAB4, 1 };
EnInvadepohUnkStruct2 D_80B4EAD0 = { D_80B4EAB8, 1 };
EnInvadepohUnkStruct2 D_80B4EAD8 = { D_80B4EABC, 1 };
EnInvadepohUnkStruct3 D_80B4EAE0 = { 0, &D_80B4EAC0 };
EnInvadepohUnkStruct3 D_80B4EAE8 = { 0, &D_80B4EAC8 };
EnInvadepohUnkStruct3 D_80B4EAF0 = { 0, &D_80B4EAD0 };
EnInvadepohUnkStruct3 D_80B4EAF8 = { 0, &D_80B4EAD8 };
EnInvadepohUnkUnion* D_80B4EB00[4] = {
    (EnInvadepohUnkUnion*)&D_80B4EAE0,
    (EnInvadepohUnkUnion*)&D_80B4EAE8,
    (EnInvadepohUnkUnion*)&D_80B4EAF0,
    (EnInvadepohUnkUnion*)&D_80B4EAF8,
};
s8 D_80B4EB10[1] = { 0 };
s8 D_80B4EB14[4] = { 0, 1, 2, 0 };
s8 D_80B4EB18[5] = { 0, 1, 2, 1, 0 };
s8 D_80B4EB20[6] = { 0, 1, 2, 2, 1, 0 };
s8 D_80B4EB28[8] = { 0, 1, 2, 1, 0, 1, 2, 0 };
EnInvadepohUnkStruct2 D_80B4EB30 = { D_80B4EB10, 1 };
EnInvadepohUnkStruct2 D_80B4EB38 = { D_80B4EB14, 4 };
EnInvadepohUnkStruct2 D_80B4EB40 = { D_80B4EB18, 5 };
EnInvadepohUnkStruct2 D_80B4EB48 = { D_80B4EB20, 6 };
EnInvadepohUnkStruct2 D_80B4EB50 = { D_80B4EB28, 8 };
EnInvadepohUnkStruct3 D_80B4EB58 = { 0, &D_80B4EB30 };
EnInvadepohUnkStruct4 D_80B4EB60[4] = {
    { 2, 0.5f },
    { 3, 0.9f },
    { 4, 0.95f },
    { 5, 1.0f },
};
EnInvadepohUnkStruct4 D_80B4EB80[1] = { 1, 1.0f };
EnInvadepohUnkStruct6 D_80B4EB88 = { 2, &D_80B4EB30, 4, D_80B4EB60, 40, 60 };
EnInvadepohUnkStruct5 D_80B4EB9C = { 1, &D_80B4EB38, 1, D_80B4EB80 };
EnInvadepohUnkStruct5 D_80B4EBAC = { 1, &D_80B4EB40, 1, D_80B4EB80 };
EnInvadepohUnkStruct5 D_80B4EBBC = { 1, &D_80B4EB48, 1, D_80B4EB80 };
EnInvadepohUnkStruct5 D_80B4EBCC = { 1, &D_80B4EB50, 1, D_80B4EB80 };
EnInvadepohUnkUnion* D_80B4EBDC[6] = {
    (EnInvadepohUnkUnion*)&D_80B4EB58, (EnInvadepohUnkUnion*)&D_80B4EB88, (EnInvadepohUnkUnion*)&D_80B4EB9C,
    (EnInvadepohUnkUnion*)&D_80B4EBAC, (EnInvadepohUnkUnion*)&D_80B4EBBC, (EnInvadepohUnkUnion*)&D_80B4EBCC,
};
s8 D_80B4EBF4[1] = { 0 };
EnInvadepohUnkStruct2 D_80B4EBF8 = { D_80B4EBF4, 1 };
EnInvadepohUnkStruct3 D_80B4EC00 = { 0, &D_80B4EBF8 };
EnInvadepohUnkUnion* D_80B4EC08[1] = { (EnInvadepohUnkUnion*)&D_80B4EC00 };
EnInvadepohUnkFunc D_80B4EC0C[3] = {
    EnInvadepoh_func_80B45A4C,
    EnInvadepoh_func_80B45A94,
    EnInvadepoh_func_80B45B1C,
};

Color_RGBA8 D_80B4EC18 = { 255, 255, 200, 255 };
Color_RGBA8 D_80B4EC1C = { 255, 200, 0, 0 };
void (*D_80B4EC20[1])(EnInvadepohStructD_80B50350*) = { EnInvadepoh_func_80B46184 };
InitChainEntry D_80B4EC24[4] = {
    ICHAIN_F32(uncullZoneForward, 20000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 500, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 600, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_STOP),
};
InitChainEntry D_80B4EC34[4] = {
    ICHAIN_F32(uncullZoneForward, 20000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 300, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_STOP),
};
InitChainEntry D_80B4EC44[4] = {
    ICHAIN_F32(uncullZoneForward, 20000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 100, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_STOP),
};
InitChainEntry D_80B4EC54[5] = {
    ICHAIN_F32(uncullZoneForward, 20000, ICHAIN_CONTINUE), ICHAIN_F32(uncullZoneScale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 100, ICHAIN_CONTINUE),  ICHAIN_F32(targetArrowOffset, 1500, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_STOP),
};
InitChainEntry D_80B4EC68[6] = {
    ICHAIN_F32(uncullZoneForward, 20000, ICHAIN_CONTINUE), ICHAIN_F32(uncullZoneScale, 1000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 1000, ICHAIN_CONTINUE), ICHAIN_VEC3S(shape, 0, ICHAIN_CONTINUE),
    ICHAIN_F32(terminalVelocity, -100, ICHAIN_CONTINUE),   ICHAIN_VEC3F_DIV1000(scale, 1000, ICHAIN_STOP),
};
InitChainEntry D_80B4EC80[6] = {
    ICHAIN_F32(uncullZoneForward, 2000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 50, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 50, ICHAIN_CONTINUE),
    ICHAIN_F32(gravity, -3, ICHAIN_CONTINUE),
    ICHAIN_U8(targetMode, 4, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 7, ICHAIN_STOP),
};
InitChainEntry D_80B4EC98[6] = {
    ICHAIN_F32(uncullZoneForward, 20000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 150, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 1500, ICHAIN_CONTINUE),
    ICHAIN_U8(targetMode, 3, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_STOP),
};
ActorFunc D_80B4ECB0[14] = {
    EnInvadepoh_func_80B4627C, EnInvadepoh_func_80B46414, EnInvadepoh_func_80B46520, EnInvadepoh_func_80B465CC,
    EnInvadepoh_func_80B46644, EnInvadepoh_func_80B46644, EnInvadepoh_func_80B468B4, EnInvadepoh_func_80B46644,
    EnInvadepoh_func_80B46644, EnInvadepoh_func_80B46644, EnInvadepoh_func_80B469C4, EnInvadepoh_func_80B46A80,
    EnInvadepoh_func_80B46644, EnInvadepoh_func_80B46414,
};
ActorFunc D_80B4ECE8[14] = {
    EnInvadepoh_func_80B46BB0, EnInvadepoh_func_80B46BC0, EnInvadepoh_func_80B46C08, EnInvadepoh_func_80B46C34,
    EnInvadepoh_func_80B46C50, EnInvadepoh_func_80B46C50, EnInvadepoh_func_80B46C7C, EnInvadepoh_func_80B46C50,
    EnInvadepoh_func_80B46C50, EnInvadepoh_func_80B46C50, EnInvadepoh_func_80B46C94, EnInvadepoh_func_80B46CC0,
    EnInvadepoh_func_80B46CF4, EnInvadepoh_func_80B46D28,
};
s16 D_80B4ED20[8] = {
    130, 125, 115, 100, 80, 78, 76, 74,
};
Vec3f D_80B4ED30[5] = {
    { 0.01f, 0.01f, 0.01f }, { 0.02f, 0.01f, 0.005f }, { -0.01f, 0.0f, 0.0f },
    { 0.01f, 0.01f, 0.01f }, { 0.005f, 0.01f, 0.02f },
};
Vec3f D_80B4ED6C[7] = {
    { 0.0005f, 0.027999999f, 0.01f }, { -0.01f, 0.0f, 0.0f }, { -0.01f, 0.0f, 0.0f },
    { 0.016f, 0.0004f, 0.01f },       { -0.01f, 0.0f, 0.0f }, { 0.0005f, 0.0005f, 0.0005f },
    { 0.0002f, 0.0002f, 0.0002f },
};
s16 D_80B4EDC0[3] = { -0x1F40, -0x1770, -0x2AF8 };
s16 D_80B4EDC8[4] = { -0x708, -0x3E8, 0, 0x7D0 };
Vec3f D_80B4EDD0[5] = {
    { -1813.0f, 374.0f, 1900.0f }, { 2198.0f, 153.0f, 3365.0f }, { -1434.0f, 262.0f, 3365.0f },
    { -393.0f, 396.0f, 1084.0f },  { 0.0f, 1500.0f, 0.0f },
};
EnInvadepohUnkStruct1 D_80B4EE0C[3] = {
    { 0.08f, 0x2BC, -0xA },
    { 0.09f, 0x12C, -5 },
    { 0.05f, 0x190, 0 },
};
Vec3f D_80B4EE24 = { 2000.0f, 1000.0f, 0.0f };
Vec3f D_80B4EE30 = { 400.0f, 270.0f, 0.0f };

MtxF D_80B502A0;
MtxF D_80B502E0;
EnInvadepoh* D_80B50320[8];
u8 D_80B50340[8];
s8 D_80B50348;
EnInvadepohStructD_80B50350 D_80B50350[10];
Actor* D_80B503F0;
EnInvadepoh* D_80B503F4;
EnInvadepoh* D_80B503F8;
AnimatedMaterial* sAlienEyeBeamTexAnim;
AnimatedMaterial* sAlienEmptyTexAnim;
s16 D_80B50404[3];
s16 D_80B5040A;
EnInvadepoh* D_80B5040C;
