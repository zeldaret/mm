#include "z_en_invadepoh.h"
#include "overlays/actors/ovl_En_Door/z_en_door.h"
#include "assets/objects/gameplay_keep/gameplay_keep.h"

#define FLAGS 0x00000010

#define THIS ((EnInvadepoh*)thisx)

#if 1 // function prototypes
void EnInvadepoh_Init(Actor* thisx, PlayState* play);
void EnInvadepoh_Destroy(Actor* thisx, PlayState* play);
void EnInvadepoh_Update(Actor* thisx, PlayState* play2);

// Update functions
void EnInvadepoh_func_80B47BAC(Actor* thisx, PlayState* play2);
void EnInvadepoh_func_80B47D30(Actor* thisx, PlayState* play2);
void EnInvadepoh_func_80B47FA8(Actor* thisx, PlayState* play2);
void EnInvadepoh_func_80B48060(Actor* thisx, PlayState* play2);
void EnInvadepoh_func_80B481C4(Actor* thisx, PlayState* play2);
void EnInvadepoh_func_80B4827C(Actor* thisx, PlayState* play2);
void EnInvadepoh_func_80B4873C(Actor* thisx, PlayState* play2);
void EnInvadepoh_func_80B48620(Actor* thisx, PlayState* play2);
void EnInvadepoh_func_80B48FB0(Actor* thisx, PlayState* play2);
void EnInvadepoh_func_80B490F0(Actor* thisx, PlayState* play2);
void EnInvadepoh_func_80B49B1C(Actor* thisx, PlayState* play2);
void EnInvadepoh_func_80B49F88(Actor* thisx, PlayState* play2);
void EnInvadepoh_func_80B4A168(Actor* thisx, PlayState* play2);
void EnInvadepoh_func_80B4A1B8(Actor* thisx, PlayState* play2);
void EnInvadepoh_func_80B4A9C8(Actor* thisx, PlayState* play2);
void EnInvadepoh_func_80B4AB8C(Actor* thisx, PlayState* play2);
void EnInvadepoh_func_80B4ABDC(Actor* thisx, PlayState* play2);
void EnInvadepoh_func_80B4B0C4(Actor* thisx, PlayState* play2);
void EnInvadepoh_func_80B4B218(Actor* thisx, PlayState* play2);
void EnInvadepoh_func_80B4B8BC(Actor* thisx, PlayState* play2);
void EnInvadepoh_func_80B4BA30(Actor* thisx, PlayState* play2);
void EnInvadepoh_func_80B4BA84(Actor* thisx, PlayState* play2);
void EnInvadepoh_func_80B4C3A0(Actor* thisx, PlayState* play2);
void EnInvadepoh_func_80B4C568(Actor* thisx, PlayState* play2);
void EnInvadepoh_func_80B4C5C0(Actor* thisx, PlayState* play2);
void EnInvadepoh_func_80B4CE54(Actor* thisx, PlayState* play2);
void EnInvadepoh_func_80B4CFFC(Actor* thisx, PlayState* play2);
void EnInvadepoh_func_80B4D054(Actor* thisx, PlayState* play2);
void EnInvadepoh_func_80B4D670(Actor* thisx, PlayState* play2);

// Draw functions
void EnInvadepoh_func_80B4D760(Actor* thisx, PlayState* play2);
void EnInvadepoh_func_80B4D9B4(Actor* thisx, PlayState* play);
void EnInvadepoh_func_80B4DB14(Actor* thisx, PlayState* play2);
void EnInvadepoh_func_80B4E158(Actor* thisx, PlayState* play2);
void EnInvadepoh_func_80B4E1B0(Actor* thisx, PlayState* play2);
void EnInvadepoh_func_80B4E324(Actor* thisx, PlayState* play);
void EnInvadepoh_func_80B4E3F0(Actor* thisx, PlayState* play2);
void EnInvadepoh_func_80B4E660(Actor* thisx, PlayState* play);
void EnInvadepoh_func_80B4E7BC(Actor* thisx, PlayState* play);

// Action functions
void EnInvadepoh_func_80B46DA8(EnInvadepoh* this);
void EnInvadepoh_func_80B46DC8(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B46E20(EnInvadepoh* this);
void EnInvadepoh_func_80B46E44(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B46EC0(EnInvadepoh* this);
void EnInvadepoh_func_80B46EE8(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B46F88(EnInvadepoh* this);
void EnInvadepoh_func_80B46FA8(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B47064(EnInvadepoh* this);
void EnInvadepoh_func_80B47084(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B470E0(EnInvadepoh* this);
void EnInvadepoh_func_80B47108(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B471C0(EnInvadepoh* this);
void EnInvadepoh_func_80B471E0(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B47248(EnInvadepoh* this);
void EnInvadepoh_func_80B47268(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B47278(EnInvadepoh* this);
void EnInvadepoh_func_80B47298(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B47304(EnInvadepoh* this);
void EnInvadepoh_func_80B47324(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B473E4(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B474DC(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B47568(EnInvadepoh* this);
void EnInvadepoh_func_80B47600(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B4770C(EnInvadepoh* this);
void EnInvadepoh_func_80B477B4(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B478F4(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B47938(EnInvadepoh* this);
void EnInvadepoh_func_80B479E8(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B48324(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B48374(EnInvadepoh* this);
void EnInvadepoh_func_80B483CC(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B4843C(EnInvadepoh* this);
void EnInvadepoh_func_80B484EC(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B48588(EnInvadepoh* this);
void EnInvadepoh_func_80B48610(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B48848(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B48948(EnInvadepoh* this);
void EnInvadepoh_func_80B48AD4(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B48E4C(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B491EC(EnInvadepoh* this);
void EnInvadepoh_func_80B49228(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B492FC(EnInvadepoh* this);
void EnInvadepoh_func_80B4934C(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B49404(EnInvadepoh* this);
void EnInvadepoh_func_80B49454(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B49628(EnInvadepoh* this);
void EnInvadepoh_func_80B49670(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B497EC(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B49904(EnInvadepoh* this);
void EnInvadepoh_func_80B4994C(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B499BC(EnInvadepoh* this);
void EnInvadepoh_func_80B49A00(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B49C38(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B49DFC(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B4A350(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B4A570(EnInvadepoh* this);
void EnInvadepoh_func_80B4A5E4(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B4A67C(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B4A81C(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B4ACF0(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B4AD3C(EnInvadepoh* this);
void EnInvadepoh_func_80B4AD60(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B4ADB8(EnInvadepoh* this);
void EnInvadepoh_func_80B4ADCC(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B4AEC0(EnInvadepoh* this);
void EnInvadepoh_func_80B4AEDC(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B4AF80(EnInvadepoh* this);
void EnInvadepoh_func_80B4AF94(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B4B024(EnInvadepoh* this);
void EnInvadepoh_func_80B4B048(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B4B484(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B4B510(EnInvadepoh* this);
void EnInvadepoh_func_80B4B564(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B4B724(EnInvadepoh* this);
void EnInvadepoh_func_80B4B768(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B4B864(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B4BC4C(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B4C058(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B4C1BC(EnInvadepoh* this);
void EnInvadepoh_func_80B4C218(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B4C730(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B4CB0C(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B4CC70(EnInvadepoh* this);
void EnInvadepoh_func_80B4CCCC(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B4D290(EnInvadepoh* this, PlayState* play);
void EnInvadepoh_func_80B4D480(EnInvadepoh* this, PlayState* play);

s32 EnInvadepoh_func_80B4516C(EnInvadepoh* this);
s32 EnInvadepoh_func_80B450C0(f32* arg0, f32* arg1, f32 arg2, f32 arg3, f32 arg4);
#endif

ActorInit En_Invadepoh_InitVars = {
    ACTOR_EN_INVADEPOH,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnInvadepoh),
    (ActorFunc)EnInvadepoh_Init,
    (ActorFunc)EnInvadepoh_Destroy,
    (ActorFunc)EnInvadepoh_Update,
    (ActorFunc)NULL,
};

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

MtxF D_80B502A0;
MtxF D_80B502E0;
EnInvadepoh* D_80B50320[8];
u8 D_80B50340[8];
s8 D_80B50348;
EnInvadepohWarpEffect D_80B50350[10];
Actor* D_80B503F0;
EnInvadepoh* D_80B503F4;
EnInvadepoh* D_80B503F8;
AnimatedMaterial* sAlienEyeBeamTexAnim;
AnimatedMaterial* sAlienEmptyTexAnim;
s16 D_80B50404[3];
s16 D_80B5040A;
EnInvadepoh* D_80B5040C;

void EnInvadepoh_func_80B439B0(s32 arg0, s32 arg1) {
    arg1 -= CLOCK_TIME(2, 30);
    arg1 = CLAMP_MIN(arg1, 0);

    if ((arg0 % 2) == 0) {
        gSaveContext.save.saveInfo.unk_E64[arg0 >> 1] =
            (gSaveContext.save.saveInfo.unk_E64[arg0 >> 1] & 0xFFFF0000) | (arg1 & 0xFFFF);
    } else {
        gSaveContext.save.saveInfo.unk_E64[arg0 >> 1] =
            (gSaveContext.save.saveInfo.unk_E64[arg0 >> 1] & 0xFFFF) | ((arg1 & 0xFFFF) << 0x10);
    }
}

s32 EnInvadepoh_func_80B43A24(s32 arg0) {
    u32 var_v1;

    if ((arg0 % 2) == 0) {
        var_v1 = gSaveContext.save.saveInfo.unk_E64[arg0 >> 1] & 0xFFFF;
    } else {
        var_v1 = (gSaveContext.save.saveInfo.unk_E64[arg0 >> 1] & 0xFFFF0000) >> 0x10;
    }
    return var_v1 + CLOCK_TIME(2, 30);
}

void EnInvadepoh_func_80B43A74(s32 arg0) {
    gSaveContext.save.saveInfo.unk_E64[4] = (gSaveContext.save.saveInfo.unk_E64[4] & ~0xFF) | (arg0 & 0xFF);
}

s32 EnInvadepoh_func_80B43A9C(void) {
    return gSaveContext.save.saveInfo.unk_E64[4] & 0xFF;
}

s32 EnInvadepoh_func_80B43AB0(void) {
    s32 sp1C = EnInvadepoh_func_80B43A9C();

    if (sp1C < 12) {
        sp1C++;
        EnInvadepoh_func_80B43A74(sp1C);
    }
    return sp1C;
}

void EnInvadepoh_func_80B43AF0(s32 arg0) {
    s32 sp1C = gSaveContext.save.time;

    if ((CURRENT_DAY == 1) && (sp1C >= CLOCK_TIME(2, 30)) && (sp1C < CLOCK_TIME(5, 15))) {
        s32 sp18 = (12 - EnInvadepoh_func_80B43A9C()) * 25.0f;

        EnInvadepoh_func_80B439B0(arg0, sp1C + sp18);
    }
}

s32 EnInvadepoh_func_80B43B80(EnInvadepoh* this) {
    s32 var_v1;
    s32 var_v0 = this->unk_308 - 1;

    for (var_v1 = 0; var_v1 < var_v0; var_v1++) {
        if (this->unk_320 < this->unk_37C[var_v1]) {
            break;
        }
    }
    return var_v1;
}

void EnInvadepoh_func_80B43BC8(EnInvadepoh* this, s8* arg1, Vec3f* arg2) {
    f32 var_fs0 = 0.0f;
    f32 var_fs2 = 0.0f;
    f32 temp_fs1 = 1.0f / this->unk_310;
    s32 temp_s5 = this->unk_308;
    s32 var_s2;
    Vec3f sp70;
    Vec3s* var_s0 = this->unk_30C;
    Vec3s* var_s1 = var_s0 + 1;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fv0;
    f32 temp_fv0_2;

    for (var_s2 = 0; var_s2 < temp_s5; var_s2++) {
        sp70.x = var_s1->x - var_s0->x;
        sp70.y = var_s1->y - var_s0->y;
        sp70.z = var_s1->z - var_s0->z;
        temp_fv0_2 = Math3D_Vec3fMagnitude(&sp70);
        temp_fa1 = var_fs0 + temp_fv0_2;
        temp_fa0 = temp_fa1 * temp_fs1;
        if (this->unk_320 <= temp_fa0) {
            *arg1 = var_s2;
            temp_fv0 = (this->unk_320 - var_fs2) / (temp_fa0 - var_fs2);
            arg2->x = (temp_fv0 * sp70.x) + var_s0->x;
            arg2->y = (temp_fv0 * sp70.y) + var_s0->y;
            arg2->z = (temp_fv0 * sp70.z) + var_s0->z;
            return;
        }
        var_s0 = var_s1++;
        var_fs0 = temp_fa1;
        var_fs2 = temp_fa0;
    }
    *arg1 = temp_s5;
    arg2->x = this->unk_30C[temp_s5].x;
    arg2->y = this->unk_30C[temp_s5].y;
    arg2->z = this->unk_30C[temp_s5].z;
}

void EnInvadepoh_func_80B43DD4(EnInvadepoh* this, s16 arg1, s16 arg2) {
    s32 pad;
    Vec3s* sp40 = &this->unk_30C[this->unk_309];
    Vec3s* sp3C = sp40 + 1;
    Vec3f sp30;
    Vec3f sp24;

    if (this->unk_309 != this->unk_308) {
        Math_Vec3s_ToVec3f(&sp30, sp40);
        Math_Vec3s_ToVec3f(&sp24, sp3C);
        Math_ScaledStepToS(&this->actor.shape.rot.y, Math_Vec3f_Yaw(&sp30, &sp24) + arg2, arg1);
    }
}

void EnInvadepoh_func_80B43E6C(EnInvadepoh* this, s16 arg1, s16 arg2, s16 arg3) {
    s32 pad;
    Vec3s* sp40 = &this->unk_30C[this->unk_309];
    Vec3s* sp3C = sp40 + 1;
    Vec3f sp30;
    Vec3f sp24;

    if (this->unk_309 != this->unk_308) {
        Math_Vec3s_ToVec3f(&sp30, sp40);
        Math_Vec3s_ToVec3f(&sp24, sp3C);
        Math_SmoothStepToS(&this->actor.shape.rot.y, Math_Vec3f_Yaw(&sp30, &sp24), arg1, arg2, arg3);
    }
}

void EnInvadepoh_func_80B43F0C(EnInvadepoh* this) {
    s32 pad;
    Vec3s* sp40 = &this->unk_30C[this->unk_309];
    Vec3s* sp3C = sp40 + 1;
    Vec3f sp30;
    Vec3f sp24;

    Math_Vec3s_ToVec3f(&sp30, sp40);
    Math_Vec3s_ToVec3f(&sp24, sp3C);
    this->actor.shape.rot.y = Math_Vec3f_Yaw(&sp30, &sp24);
}

f32 EnInvadepoh_func_80B43F70(EnInvadepoh* this) {
    s32 temp_s4 = this->unk_308 + 1;
    s32 var_s1;
    Vec3f sp54;
    Vec3f sp48;
    Vec3s* var_s0 = this->unk_30C;
    f32 var_fs0 = 0.0f;

    Math_Vec3s_ToVec3f(&sp48, var_s0);
    var_s0++;
    for (var_s1 = 1; var_s1 < temp_s4; var_s1++, var_s0++) {
        Math_Vec3f_Copy(&sp54, &sp48);
        Math_Vec3s_ToVec3f(&sp48, var_s0);
        var_fs0 += Math3D_Distance(&sp54, &sp48);
    }
    return var_fs0;
}

void EnInvadepoh_func_80B44024(EnInvadepoh* this, PlayState* play) {
    Path* temp_v0 = &play->setupPathList[ENINVADEPOH_GET_PARAM_7F00(&this->actor)];

    this->unk_308 = temp_v0->count - 1;
    this->unk_30C = Lib_SegmentedToVirtual(temp_v0->points);
}

void EnInvadepoh_func_80B4407C(EnInvadepoh* this, s32 arg1) {
    Math_Vec3s_ToVec3f(&this->actor.world.pos, &this->unk_30C[arg1]);
}

s32 EnInvadepoh_func_80B440B8(EnInvadepoh* thisx, f32 arg1, f32 arg2) {
    EnInvadepoh* this = thisx; // TODO: why recast?
    Vec3s* sp48 = &this->unk_30C[this->unk_309];
    Vec3s* sp44 = &this->unk_30C[this->unk_309] + 1;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    f32 temp_fa0_2;
    f32 temp_fv0_2;
    s32 pad2;
    s16 sp1E;

    if (this->unk_309 >= this->unk_308) {
        return false;
    }
    sp40 = (sp44->x - sp48->x);
    sp3C = (sp44->z - sp48->z);
    sp1E = Math_Atan2S_XY(sp3C, sp40);
    sp38 = Math_CosS(sp1E);
    sp34 = Math_SinS(sp1E);
    sp30 = this->actor.world.pos.x - sp48->x;
    sp2C = this->actor.world.pos.z - sp48->z;
    if ((arg1 - arg2) < fabsf((sp30 * sp38) - (sp2C * sp34))) {
        return false;
    }
    temp_fv0_2 = Math3D_XZLength(sp40, sp3C);
    temp_fa0_2 = (sp2C * sp38) + (sp30 * sp34);

    if ((temp_fa0_2 < 0.0f) || (temp_fv0_2 < temp_fa0_2)) {
        return false;
    }
    return true;
}

s32 EnInvadepoh_func_80B44234(EnInvadepoh* this, Vec3f* arg1) {
    s32 var_s0;
    s32 temp_s3 = this->unk_308;
    Vec3s* var_s1;
    Vec3f sp48;
    f32 var_fs0 = FLT_MAX;
    s32 var_s4 = 0;
    f32 temp_fv0;

    for (var_s0 = 0, var_s1 = this->unk_30C; var_s0 < temp_s3; var_s0++, var_s1++) {
        Math_Vec3s_ToVec3f(&sp48, var_s1);
        temp_fv0 = Math3D_Vec3fDistSq(&sp48, arg1);
        if (temp_fv0 < var_fs0) {
            var_fs0 = temp_fv0;
            var_s4 = var_s0;
        }
    }
    return var_s4;
}

void EnInvadepoh_func_80B442E4(EnInvadepoh* this) {
    s32 pad;
    s32 sp18 = gSaveContext.save.time;
    s32 temp_v0 = EnInvadepoh_func_80B43A24(ENINVADEPOH_GET_PARAM_7(&this->actor));

    if (D_80B4E940 == 1) {
        this->unk_320 = 0.0f;
    } else if (D_80B4E940 == 2) {
        if ((sp18 - temp_v0) < 0) {
            this->unk_320 = 0.0f;
        } else {
            this->unk_320 = (sp18 - temp_v0) * (1.0f / 3600.0f);
            if (this->unk_320 > 1.0f) {
                this->unk_320 = 1.0f;
            }
        }
    }
    this->unk_309 = EnInvadepoh_func_80B43B80(this);
}

void EnInvadepoh_func_80B443A0(EnInvadepoh* this) {
    f32 temp_fs3 = 1.0f / this->unk_310;
    s32 temp_s4 = this->unk_308;
    s32 var_s1;
    Vec3f sp54;
    Vec3f sp48;
    Vec3s* var_s0 = this->unk_30C;
    f32 var_fs0 = 0.0f;
    f32* var_s2;

    Math_Vec3s_ToVec3f(&sp48, var_s0);
    var_s0++;
    var_s2 = this->unk_37C;
    for (var_s1 = 1; var_s1 < temp_s4; var_s1++, var_s0++, var_s2++) {
        Math_Vec3f_Copy(&sp54, &sp48);
        Math_Vec3s_ToVec3f(&sp48, var_s0);
        var_fs0 += Math3D_Distance(&sp54, &sp48);
        *var_s2 = var_fs0 * temp_fs3;
        if (*var_s2 < 0.0f) {
            *var_s2 = 0.0f;
        } else if (*var_s2 > 1.0f) {
            *var_s2 = 1.0f;
        }
    }
}

void EnInvadepoh_func_80B444BC(EnInvadepoh* this, PlayState* play) {
    EnInvadepoh_func_80B44024(this, play);
    this->unk_310 = EnInvadepoh_func_80B43F70(this);
    EnInvadepoh_func_80B443A0(this);
}

void EnInvadepoh_func_80B444F4(EnInvadepoh* this, PlayState* play) {
    EnInvadepoh_func_80B44024(this, play);
}

void EnInvadepoh_func_80B44514(EnInvadepoh* this) {
    this->unk_309++;
    if (this->unk_309 >= this->unk_308) {
        this->unk_309 = 0;
    }
}

void EnInvadepoh_func_80B44540(EnInvadepoh* this, PlayState* play) {
    EnInvadepoh_func_80B44024(this, play);
    this->unk_310 = EnInvadepoh_func_80B43F70(this);
}

void EnInvadepoh_func_80B44570(EnInvadepoh* this) {
    if ((gSaveContext.save.time < CLOCK_TIME(2, 00)) || (gSaveContext.save.time >= CLOCK_TIME(6, 00))) {
        this->unk_320 = 0.0f;
    } else if ((gSaveContext.save.time >= CLOCK_TIME(2, 15)) && (gSaveContext.save.time < CLOCK_TIME(6, 00))) {
        this->unk_320 = 1.0f;
    } else {
        f32 temp = (gSaveContext.save.time - CLOCK_TIME(2, 00)) * (1.0f / (CLOCK_TIME(2, 15) - CLOCK_TIME(2, 00)));

        this->unk_320 = temp;
        this->unk_320 = CLAMP(this->unk_320, 0.0f, 1.0f);
    }
}

void EnInvadepoh_func_80B44620(EnInvadepoh* this, PlayState* play) {
    EnInvadepoh_func_80B44024(this, play);
}

void EnInvadepoh_func_80B44640(EnInvadepoh* this) {
    if (this->unk_309 < this->unk_308) {
        this->unk_309++;
    }
}

void EnInvadepoh_func_80B44664(EnInvadepoh* this, PlayState* play) {
    EnInvadepoh_func_80B44024(this, play);
    this->unk_30A = 1;
}

void EnInvadepoh_func_80B44690(EnInvadepoh* this) {
    this->unk_309 += this->unk_30A;
    if (this->unk_309 >= this->unk_308) {
        this->unk_309 = 0;
    } else if (this->unk_309 < 0) {
        this->unk_309 = this->unk_308 - 1;
    }
}

void EnInvadepoh_func_80B446D0(EnInvadepoh* this, PlayState* play) {
    EnInvadepoh_func_80B44024(this, play);
    this->unk_310 = EnInvadepoh_func_80B43F70(this);
}

void EnInvadepoh_func_80B44700(EnInvadepoh* this) {
    if ((gSaveContext.save.time < CLOCK_TIME(20, 00)) && (gSaveContext.save.time >= CLOCK_TIME(6, 00))) {
        this->unk_320 = 0.0f;
    } else if ((gSaveContext.save.time >= CLOCK_TIME(20, 14) + 15) || (gSaveContext.save.time < CLOCK_TIME(6, 00))) {
        this->unk_320 = 1.0f;
    } else {
        f32 temp =
            (gSaveContext.save.time - CLOCK_TIME(20, 00)) * (1.0f / (CLOCK_TIME(20, 14) + 15 - CLOCK_TIME(20, 00)));

        this->unk_320 = temp;
        this->unk_320 = CLAMP(this->unk_320, 0.0f, 1.0f);
    }
}

void EnInvadepoh_func_80B447C0(EnInvadepoh* this, PlayState* play) {
    s32 pad;
    Vec3s* sp60;
    s32 pad2;
    Vec3f sp50;
    Vec3f sp44;
    f32 sp40 = this->actor.world.pos.y;
    f32 sp3C;
    f32 sp38;

    sp60 = &this->unk_30C[this->unk_309];
    sp3C = (this->unk_309 < 1) ? 0.0f : this->unk_37C[this->unk_309 - 1];
    sp38 = (this->unk_309 < (this->unk_308 - 1)) ? this->unk_37C[this->unk_309] : 1.0f;

    if (sp38 - sp3C < 0.001f) {
        Math_Vec3s_ToVec3f(&this->unk_314, sp60);
    } else {
        f32 sp34 = this->unk_320 - sp3C;
        f32 sp30 = sp38 - this->unk_320;
        f32 sp2C = 1.0f / (sp38 - sp3C);
        s32 pad3;

        Math_Vec3s_ToVec3f(&sp50, sp60);
        Math_Vec3s_ToVec3f(&sp44, sp60 + 1);
        this->unk_314.x = ((sp50.x * sp30) + (sp44.x * sp34)) * sp2C;
        this->unk_314.y = ((sp50.y * sp30) + (sp44.y * sp34)) * sp2C;
        this->unk_314.z = ((sp50.z * sp30) + (sp44.z * sp34)) * sp2C;
    }
    Math_Vec3f_Copy(&this->actor.world.pos, &this->unk_314);
    func_800B4AEC(play, &this->actor, 0.0f);
    if (this->actor.floorHeight > BGCHECK_Y_MIN + 1.0f) {
        if (sp40 < this->actor.floorHeight) {
            if (this->actor.velocity.y < 0.0f) {
                this->actor.velocity.y = 0.0f;
            } else {
                this->actor.velocity.y += 2.0f;
                this->actor.velocity.y = CLAMP_MAX(this->actor.velocity.y, 30.0f);
            }
            this->actor.world.pos.y = this->actor.velocity.y + sp40;
            if (this->actor.floorHeight < this->actor.world.pos.y) {
                this->actor.world.pos.y = this->actor.floorHeight;
            }
        } else {
            if (this->actor.velocity.y > 0.0f) {
                this->actor.velocity.y = 0.0f;
            } else {
                this->actor.velocity.y -= 2.0f;
            }
            this->actor.world.pos.y = this->actor.velocity.y + sp40;
            if (this->actor.world.pos.y < this->actor.floorHeight) {
                this->actor.world.pos.y = this->actor.floorHeight;
                this->actor.velocity.y = CLAMP_MIN(this->actor.velocity.y, -30.0f);
            }
        }
    } else {
        this->actor.world.pos.y = sp40;
    }
}

void EnInvadepoh_func_80B44A90(EnInvadepoh* this, PlayState* play) {
    if (this->actor.bgCheckFlags & 1) {
        this->actor.velocity.y *= 0.3f;
        this->actor.speed *= 0.8f;
    } else if (this->actor.bgCheckFlags & 8) {
        this->actor.velocity.y *= 0.8f;
        this->actor.speed *= 0.3f;
    } else {
        this->actor.velocity.y *= 0.8f;
        this->actor.speed *= 0.8f;
    }
    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(play, &this->actor, 30.0f, 40.0f, 0.0f, 5);
}

void EnInvadepoh_func_80B44B78(EnInvadepoh* this) {
}

s32 EnInvadepoh_func_80B44B84(EnInvadepoh* this, PlayState* play, f32 arg2, f32 arg3) {
    s32 pad; // TODO: recast?
    Vec3s* temp_v0_2 = &this->unk_30C[this->unk_309 + 1];
    s32 sp2C =
        EnInvadepoh_func_80B450C0(&this->actor.world.pos.x, &this->actor.world.pos.z, temp_v0_2->x, temp_v0_2->z, arg2);

    func_800B4AEC(play, &this->actor, arg3);
    EnInvadepoh_func_80B4516C(this);
    return sp2C;
}

void EnInvadepoh_func_80B44C24(EnInvadepoh* this, PlayState* play) {
    s32 pad; // TODO: recast?
    f32 sp18 = this->actor.world.pos.y;

    EnInvadepoh_func_80B43BC8(this, &this->unk_309, &this->actor.world.pos);
    this->actor.world.pos.y = sp18;
    func_800B4AEC(play, &this->actor, 50.0f);
    EnInvadepoh_func_80B4516C(this);
}

s32 EnInvadepoh_func_80B44C80(EnInvadepoh* this, PlayState* play) {
    Vec3s* temp_a2 = &this->unk_30C[this->unk_309];
    Vec3s* temp_v0_2;
    s32 var_v1;
    u32 var_v0;
    f32 temp_v0_2x;
    f32 temp_v0_2z;
    f32 temp_a2x;
    f32 temp_a2z;
    Vec3f sp6C;
    Vec3f sp60;
    Vec3f sp54;
    Vec3f sp48;
    f32 sp44;
    s32 sp40 = 0;

    var_v1 = this->unk_309 + this->unk_30A;

    if (var_v1 >= this->unk_308) {
        var_v1 = 0;
    } else if (var_v1 < 0) {
        var_v1 = this->unk_308 - 1;
    }

    temp_v0_2 = &this->unk_30C[var_v1];

    temp_a2x = temp_a2->x;
    temp_a2z = temp_a2->z;
    temp_v0_2x = temp_v0_2->x;
    temp_v0_2z = temp_v0_2->z;

    sp6C.x = temp_v0_2x - temp_a2x;
    sp6C.y = 0.0f;
    sp6C.z = temp_v0_2z - temp_a2z;

    sp60.x = temp_v0_2x - this->actor.world.pos.x;
    sp60.y = 0.0f;
    sp60.z = temp_v0_2z - this->actor.world.pos.z;

    sp54.x = temp_a2x - this->actor.world.pos.x;
    sp54.y = 0.0f;
    sp54.z = temp_a2z - this->actor.world.pos.z;

    if (this->actor.speed > 0.0f) {
        if (Math3D_AngleBetweenVectors(&sp6C, &sp60, &sp44)) {
            sp40 = 1;
        } else if (sp44 <= 0.0f) {
            sp40 = 1;
        }
    }
    sp48.x = ((sp60.x + sp54.x) * 0.9f) + sp6C.x;
    sp48.y = 0.0f;
    sp48.z = ((sp60.z + sp54.z) * 0.9f) + sp6C.z;

    Math_SmoothStepToS(&this->actor.world.rot.y, Math_Atan2S_XY(sp48.z, sp48.x), 4, 0xFA0, 0x64);
    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(play, &this->actor, 30.0f, 15.0f, 0.0f,
                            EnInvadepoh_func_80B440B8(this, 50.0f, 15.0f) ? 4 : 5);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.world.rot.y, 3, 0x1F40, 0x64);
    return sp40;
}

void EnInvadepoh_func_80B44E90(EnInvadepoh* this, PlayState* play) {
    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(play, &this->actor, 30.0f, 15.0f, 0.0f, 5);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.world.rot.y, 3, 0x1F40, 0x64);
}

void EnInvadepoh_func_80B44EFC(EnInvadepoh* this, PlayState* play) {
    s32 pad; // TODO: recast?
    f32 sp18 = this->actor.world.pos.y;

    EnInvadepoh_func_80B43BC8(this, &this->unk_309, &this->actor.world.pos);
    this->actor.world.pos.y = sp18;
    func_800B4AEC(play, &this->actor, 50.0f);
    EnInvadepoh_func_80B4516C(this);
}

void EnInvadepoh_func_80B44F58(void) {
    TexturePtr* var_s0;
    s32 i;

    if (D_80B4E968 == 0) {
        D_80B4E968 = 1;
        for (i = 0, var_s0 = sRomaniEyeTextures; i < 5; i++, var_s0++) {
            *var_s0 = Lib_SegmentedToVirtual(*var_s0);
        }
        for (i = 0, var_s0 = sRomaniMouthTextures; i < 4; i++, var_s0++) {
            *var_s0 = Lib_SegmentedToVirtual(*var_s0);
        }
    }
}

void EnInvadepoh_func_80B44FEC(void) {
    TexturePtr* var_s0;
    s32 i;

    if (D_80B4E994 == 0) {
        D_80B4E994 = 1;
        for (i = 0, var_s0 = sCremiaEyeTextures; i < 6; i++, var_s0++) {
            *var_s0 = Lib_SegmentedToVirtual(*var_s0);
        }
        for (i = 0, var_s0 = sCremiaMouthTextures; i < 4; i++, var_s0++) {
            *var_s0 = Lib_SegmentedToVirtual(*var_s0);
        }
    }
}

void EnInvadepoh_func_80B45080(void) {
    sAlienEmptyTexAnim = Lib_SegmentedToVirtual(gAlienEmptyTexAnim);
    sAlienEyeBeamTexAnim = Lib_SegmentedToVirtual(gAlienEyeBeamTexAnim);
}

s32 EnInvadepoh_func_80B450C0(f32* arg0, f32* arg1, f32 arg2, f32 arg3, f32 arg4) {
    f32 sp1C = arg2 - *arg0;
    f32 sp18 = arg3 - *arg1;
    f32 temp_fv0 = Math3D_XZLength(sp1C, sp18);

    if (arg4 < temp_fv0) {
        f32 temp_fv1 = arg4 / temp_fv0;

        *arg0 += temp_fv1 * sp1C;
        *arg1 += temp_fv1 * sp18;
        return false;
    } else {
        *arg0 = arg2;
        *arg1 = arg3;
        return true;
    }
}

s32 EnInvadepoh_func_80B4516C(EnInvadepoh* this) {
    if (this->actor.floorHeight > BGCHECK_Y_MIN + 1.0f) {
        this->actor.world.pos.y = this->actor.floorHeight;
        return true;
    }
    return false;
}

void EnInvadepoh_func_80B451A0(EnInvadepoh* this, PlayState* play) {
    if (D_80B4E940 == 0) {
        if (CURRENT_DAY < 1) {
            D_80B4E940 = 1;
        } else if (CURRENT_DAY == 1) {
            s32 sp2C = gSaveContext.save.time;

            if ((sp2C < CLOCK_TIME(2, 30)) || (sp2C >= CLOCK_TIME(6, 00))) {
                D_80B4E940 = 1;
            } else if (sp2C < CLOCK_TIME(5, 15)) {
                s32 var_s0;
                s32 var_s1 = CLOCK_TIME(5, 15);

                for (var_s0 = 0; var_s0 < this->unk_379; var_s0++) {
                    s32 temp_v0 = EnInvadepoh_func_80B43A24(var_s0);

                    var_s1 = MIN(temp_v0, var_s1);
                }

                if (sp2C < var_s1 + CLOCK_TIME(1, 19) + 6) {
                    D_80B4E940 = 2;
                }
            }
        }
        if (D_80B4E940 == 0) {
            if (gSaveContext.save.saveInfo.weekEventReg[22] & 1) {
                D_80B4E940 = 3;
            } else {
                D_80B4E940 = 4;
            }
        }
    }
}

void EnInvadepoh_func_80B452EC(EnInvadepoh* this, PlayState* play) {
    s32 var_s2 = ENINVADEPOH_GET_PARAM_7F00(&this->actor);
    s32 var_s3;

    for (var_s3 = 0; var_s3 < this->unk_379; var_s3++) {
        D_80B50320[var_s3] = (EnInvadepoh*)Actor_Spawn(
            &play->actorCtx, play, ACTOR_EN_INVADEPOH, this->actor.world.pos.x, this->actor.world.pos.y,
            this->actor.world.pos.z, 0, 0, 0, ENINVADEPOH_SET_PARAMS(var_s2, ENINVADEPOH_ALIEN_INVADER, var_s3));
        if (var_s2 != 0xFF) {
            Path* temp_v0 = &play->setupPathList[var_s2];

            var_s2 = temp_v0->unk1;
        }
    }
}

void EnInvadepoh_func_80B453F4(EnInvadepoh* this, PlayState* play, s32 arg2) {
    Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, ACTOR_EN_INVADEPOH, this->actor.home.pos.x,
                       this->actor.home.pos.y, this->actor.home.pos.z, 0, 0, 0,
                       ENINVADEPOH_SET_PARAMS(0, ENINVADEPOH_COW, arg2));
}

void EnInvadepoh_func_80B45460(EnInvadepoh* this, PlayState* play) {
    Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, ACTOR_EN_INVADEPOH, this->actor.home.pos.x,
                       this->actor.home.pos.y, this->actor.home.pos.z, 0, 0, 0,
                       ENINVADEPOH_SET_PARAMS(0, ENINVADEPOH_ROMANI_ABDUCTED, 0));
}

void EnInvadepoh_func_80B454BC(EnInvadepoh* this, PlayState* play) {
    D_80B503F0 =
        Actor_Spawn(&play->actorCtx, play, ACTOR_EN_INVADEPOH, this->actor.world.pos.x, this->actor.world.pos.y,
                    this->actor.world.pos.z, 0, 0, 0, ENINVADEPOH_SET_PARAMS(0, ENINVADEPOH_LIGHT_BALL, 0));
}

void EnInvadepoh_func_80B45518(Vec3f* arg0) {
    MtxF* temp_v0 = Matrix_GetCurrent();

    temp_v0->mf[3][0] = arg0->x;
    temp_v0->mf[3][1] = arg0->y;
    temp_v0->mf[3][2] = arg0->z;
}

s32 EnInvadepoh_func_80B45550(EnInvadepoh* this, PlayState* play, f32 arg2, s32 arg3) {
    Actor* var_s0 = play->actorCtx.actorLists[ACTORCAT_DOOR].first;
    EnDoor* door;
    s32 sp34 = 0;

    while (var_s0 != NULL) {
        if ((var_s0->id == ACTOR_EN_DOOR) && (var_s0->update != NULL)) {
            door = (EnDoor*)var_s0;
            if ((door->dyna.actor.room == this->actor.room) &&
                (Math3D_Vec3fDistSq(&door->dyna.actor.world.pos, &this->actor.world.pos) < arg2)) {

                door->unk_1A7 = arg3;
                sp34 = 1;
                break;
            }
        }
        var_s0 = var_s0->next;
    }
    return sp34;
}

void EnInvadepoh_func_80B4560C(EnInvadepoh* this, PlayState* play, u16 arg2) {
    this->unk_376 = arg2;
    Message_StartTextbox(play, arg2, &this->actor);
}

void EnInvadepoh_func_80B45648(EnInvadepoh* this) {
    s16 var_s1 = this->actor.csId;
    s32 i;

    for (i = 0; i < 3; i++) {
        D_80B50404[i] = var_s1;
        var_s1 = CutsceneManager_GetAdditionalCsId(var_s1);
    }
}

s32 EnInvadepoh_func_80B456A8(PlayState* play, Vec3f* arg1) {
    Vec3f sp34;
    f32 sp30;

    Actor_GetProjectedPos(play, arg1, &sp34, &sp30);
    if ((sp34.z > 1.0f) && (fabsf(sp34.x * sp30) < 1.0f) && (fabsf(sp34.y * sp30) < 1.0f)) {
        f32 sp2C = (sp34.x * sp30 * 160.0f) + 160.0f;
        f32 sp28 = (sp34.y * sp30 * -120.0f) + 120.0f;
        s32 sp24 = (s32)(sp34.z * sp30 * 16352.0f) + 16352;

        if (sp24 < func_80178A94(sp2C, sp28)) {
            return true;
        }
    }
    return false;
}

void EnInvadepoh_func_80B457A0(EnInvadepoh* this) {
    s32 var_s0;
    f32 var_fs0 = FLT_MAX;
    s32 var_s5 = -1;

    for (var_s0 = 0; var_s0 < this->unk_379; var_s0++) {
        if ((D_80B50320[var_s0] != NULL) && (D_80B50320[var_s0]->unk_38B != 0)) {
            f32 temp_fv0 = Math3D_Vec3fDistSq(&D_80B50320[var_s0]->actor.world.pos, &this->actor.world.pos);

            if (temp_fv0 < var_fs0) {
                var_fs0 = temp_fv0;
                var_s5 = var_s0;
            }
        }
        D_80B50340[var_s0] &= ~2;
    }
    D_80B50348 = 0;
    if (var_fs0 <= SQ(2000.0f)) {
        D_80B50340[var_s5] |= 2;
        if (var_fs0 <= SQ(340.0f)) {
            D_80B50348 = 1;
        }
    }
}

EnInvadepoh* EnInvadepoh_func_80B458D8(void) {
    s32 var_v1;

    for (var_v1 = 0; var_v1 < 8; var_v1++) {
        if (D_80B50340[var_v1] & 2) {
            return D_80B50320[var_v1];
        }
    }
    return NULL;
}

s8 EnInvadepoh_func_80B45980(EnInvadepohFaceAnimNext* arg0, s32 arg1) {
    f32 temp_fv0 = Rand_ZeroOne();
    EnInvadepohFaceAnimNext* var_v0 = arg0;
    s32 var_v1;

    arg1--;
    for (var_v1 = 0; var_v1 < arg1; var_v1++, var_v0++) {
        if (temp_fv0 <= var_v0->chance) {
            break;
        }
    }
    return (arg0 + var_v1)->index; // TODO: fake?
}

void EnInvadepoh_func_80B459E8(EnInvadePohFaceInfo* arg0, EnInvadepohFaceAnim* arg1) {
    arg0->curAnimType = arg1->type;
    arg0->curAnim = arg1;
    arg0->curFrame = 0;
    arg0->curIndex = arg1->frames->index[0];
    if (arg0->curAnimType == 2) {
        EnInvadepohFaceAnimLoopDelayed* temp = (EnInvadepohFaceAnimLoopDelayed*)arg1;

        arg0->delayTimer = Rand_S16Offset(temp->minDelay, temp->maxDelay);
    }
}

void EnInvadepoh_func_80B45A4C(EnInvadePohFaceInfo* arg0, EnInvadepohFaceAnim** arg1) {
    EnInvadepohFaceAnim* temp_v0 = arg0->curAnim;
    EnInvadepohFaceFrame* temp_v1 = temp_v0->frames;

    if (arg0->curFrame < (temp_v1->count - 1)) {
        arg0->curFrame++;
        arg0->curIndex = temp_v1->index[arg0->curFrame];
    }
}

void EnInvadepoh_func_80B45A94(EnInvadePohFaceInfo* arg0, EnInvadepohFaceAnim** arg1) {
    EnInvadepohFaceAnimLoop* temp_v0 = (EnInvadepohFaceAnimLoop*)arg0->curAnim;
    EnInvadepohFaceFrame* temp_v1 = temp_v0->anim.frames;

    if (arg0->curFrame < (temp_v1->count - 1)) {
        arg0->curFrame++;
        arg0->curIndex = temp_v1->index[arg0->curFrame];
    } else {
        EnInvadepohFaceAnim* temp_a1 = arg1[EnInvadepoh_func_80B45980(temp_v0->nextAnims, temp_v0->nextCount)];

        EnInvadepoh_func_80B459E8(arg0, temp_a1);
    }
}

void EnInvadepoh_func_80B45B1C(EnInvadePohFaceInfo* arg0, EnInvadepohFaceAnim** arg1) {
    EnInvadepohFaceAnimLoopDelayed* temp_v0 = (EnInvadepohFaceAnimLoopDelayed*)arg0->curAnim;
    EnInvadepohFaceFrame* temp_v1 = temp_v0->loop.anim.frames;

    if (arg0->curFrame < (temp_v1->count - 1)) {
        arg0->curFrame++;
        arg0->curIndex = temp_v1->index[arg0->curFrame];
    } else if (arg0->delayTimer > 0) {
        arg0->delayTimer--;
    } else {
        EnInvadepohFaceAnim* temp_a1 =
            arg1[EnInvadepoh_func_80B45980(temp_v0->loop.nextAnims, temp_v0->loop.nextCount)];

        EnInvadepoh_func_80B459E8(arg0, temp_a1);
    }
}

s8 D_80B4E99C[1] = { 0 };
s8 D_80B4E9A0[4] = { 0, 1, 2, 0 };
s8 D_80B4E9A4[5] = { 0, 1, 2, 1, 0 };
s8 D_80B4E9AC[6] = { 0, 1, 2, 2, 1, 0 };
s8 D_80B4E9B4[8] = { 0, 1, 2, 1, 0, 1, 2, 0 };
s8 D_80B4E9BC[1] = { 1 };
s8 D_80B4E9C0[1] = { 3 };
EnInvadepohFaceFrame D_80B4E9C4 = { D_80B4E99C, 1 };
EnInvadepohFaceFrame D_80B4E9CC = { D_80B4E9A0, 4 };
EnInvadepohFaceFrame D_80B4E9D4 = { D_80B4E9A4, 5 };
EnInvadepohFaceFrame D_80B4E9DC = { D_80B4E9AC, 6 };
EnInvadepohFaceFrame D_80B4E9E4 = { D_80B4E9B4, 8 };
EnInvadepohFaceFrame D_80B4E9EC = { D_80B4E9BC, 1 };
EnInvadepohFaceFrame D_80B4E9F4 = { D_80B4E9C0, 1 };
EnInvadepohFaceAnim D_80B4E9FC = { 0, &D_80B4E9C4 };
EnInvadepohFaceAnimNext D_80B4EA04[4] = {
    { 2, 0.5f },
    { 3, 0.9f },
    { 4, 0.97f },
    { 5, 1.0f },
};
EnInvadepohFaceAnimNext D_80B4EA24[1] = { 1, 1.0f };
EnInvadepohFaceAnimLoopDelayed D_80B4EA2C = { { { 2, &D_80B4E9C4 }, 4, D_80B4EA04 }, 40, 60 };
EnInvadepohFaceAnimLoop D_80B4EA40 = { { 1, &D_80B4E9CC }, 1, D_80B4EA24 };
EnInvadepohFaceAnimLoop D_80B4EA50 = { { 1, &D_80B4E9D4 }, 1, D_80B4EA24 };
EnInvadepohFaceAnimLoop D_80B4EA60 = { { 1, &D_80B4E9DC }, 1, D_80B4EA24 };
EnInvadepohFaceAnimLoop D_80B4EA70 = { { 1, &D_80B4E9E4 }, 1, D_80B4EA24 };
EnInvadepohFaceAnim D_80B4EA80 = { 0, &D_80B4E9EC };
EnInvadepohFaceAnim D_80B4EA88 = { 0, &D_80B4E9F4 };
EnInvadepohFaceAnim* D_80B4EA90[8] = {
    &D_80B4E9FC,      &D_80B4EA2C.loop.anim, &D_80B4EA40.anim, &D_80B4EA50.anim,
    &D_80B4EA60.anim, &D_80B4EA70.anim,      &D_80B4EA80,      &D_80B4EA88,
};

s8 D_80B4EAB0[1] = { 0 };
s8 D_80B4EAB4[1] = { 1 };
s8 D_80B4EAB8[1] = { 2 };
s8 D_80B4EABC[1] = { 3 };
EnInvadepohFaceFrame D_80B4EAC0 = { D_80B4EAB0, 1 };
EnInvadepohFaceFrame D_80B4EAC8 = { D_80B4EAB4, 1 };
EnInvadepohFaceFrame D_80B4EAD0 = { D_80B4EAB8, 1 };
EnInvadepohFaceFrame D_80B4EAD8 = { D_80B4EABC, 1 };
EnInvadepohFaceAnim D_80B4EAE0 = { 0, &D_80B4EAC0 };
EnInvadepohFaceAnim D_80B4EAE8 = { 0, &D_80B4EAC8 };
EnInvadepohFaceAnim D_80B4EAF0 = { 0, &D_80B4EAD0 };
EnInvadepohFaceAnim D_80B4EAF8 = { 0, &D_80B4EAD8 };
EnInvadepohFaceAnim* D_80B4EB00[4] = {
    &D_80B4EAE0,
    &D_80B4EAE8,
    &D_80B4EAF0,
    &D_80B4EAF8,
};

s8 D_80B4EB10[1] = { 0 };
s8 D_80B4EB14[4] = { 0, 1, 2, 0 };
s8 D_80B4EB18[5] = { 0, 1, 2, 1, 0 };
s8 D_80B4EB20[6] = { 0, 1, 2, 2, 1, 0 };
s8 D_80B4EB28[8] = { 0, 1, 2, 1, 0, 1, 2, 0 };
EnInvadepohFaceFrame D_80B4EB30 = { D_80B4EB10, 1 };
EnInvadepohFaceFrame D_80B4EB38 = { D_80B4EB14, 4 };
EnInvadepohFaceFrame D_80B4EB40 = { D_80B4EB18, 5 };
EnInvadepohFaceFrame D_80B4EB48 = { D_80B4EB20, 6 };
EnInvadepohFaceFrame D_80B4EB50 = { D_80B4EB28, 8 };
EnInvadepohFaceAnim D_80B4EB58 = { 0, &D_80B4EB30 };
EnInvadepohFaceAnimNext D_80B4EB60[4] = {
    { 2, 0.5f },
    { 3, 0.9f },
    { 4, 0.95f },
    { 5, 1.0f },
};
EnInvadepohFaceAnimNext D_80B4EB80[1] = { 1, 1.0f };
EnInvadepohFaceAnimLoopDelayed D_80B4EB88 = { { { 2, &D_80B4EB30 }, 4, D_80B4EB60 }, 40, 60 };
EnInvadepohFaceAnimLoop D_80B4EB9C = { { 1, &D_80B4EB38 }, 1, D_80B4EB80 };
EnInvadepohFaceAnimLoop D_80B4EBAC = { { 1, &D_80B4EB40 }, 1, D_80B4EB80 };
EnInvadepohFaceAnimLoop D_80B4EBBC = { { 1, &D_80B4EB48 }, 1, D_80B4EB80 };
EnInvadepohFaceAnimLoop D_80B4EBCC = { { 1, &D_80B4EB50 }, 1, D_80B4EB80 };
EnInvadepohFaceAnim* D_80B4EBDC[6] = {
    &D_80B4EB58, &D_80B4EB88.loop.anim, &D_80B4EB9C.anim, &D_80B4EBAC.anim, &D_80B4EBBC.anim, &D_80B4EBCC.anim,
};

s8 D_80B4EBF4[1] = { 0 };
EnInvadepohFaceFrame D_80B4EBF8 = { D_80B4EBF4, 1 };
EnInvadepohFaceAnim D_80B4EC00 = { 0, &D_80B4EBF8 };
EnInvadepohFaceAnim* D_80B4EC08[1] = { &D_80B4EC00 };

void EnInvadepoh_func_80B45BB8(EnInvadePohFaceInfo* arg0) {
    static EnInvadepohFaceFunc D_80B4EC0C[3] = {
        EnInvadepoh_func_80B45A4C,
        EnInvadepoh_func_80B45A94,
        EnInvadepoh_func_80B45B1C,
    };

    if ((arg0->animSet != NULL) && (arg0->curAnim != NULL)) {
        D_80B4EC0C[arg0->curAnimType](arg0, arg0->animSet);
    }
}

void EnInvadepoh_func_80B45C04(EnInvadePohUnkStruct_324* arg0, EnInvadepohFaceAnim** arg1, s32 arg2,
                               EnInvadepohFaceAnim** arg3, s32 arg4, Vec3s* arg5, s16 arg6, f32 arg7, f32 arg8,
                               f32 arg9) {
    Math_Vec3s_Copy(&arg0->unk_26, arg5);
    arg0->unk_2C = arg6;
    arg0->unk_30 = arg7;
    arg0->unk_38 = arg8;
    arg0->unk_3C = arg9;
    if (arg1 != NULL) {
        EnInvadepohFaceAnim* temp_v0 = arg1[arg2];

        arg0->eyeAnim.animSet = arg1;
        arg0->eyeAnim.curAnimType = temp_v0->type;
        arg0->eyeAnim.curAnim = temp_v0;
        arg0->eyeAnim.delayTimer = 0;
        arg0->eyeAnim.curFrame = 0;
        arg0->eyeAnim.curIndex = temp_v0->frames->index[0];
    }
    if (arg3 != NULL) {
        EnInvadepohFaceAnim* temp_v0 = arg3[arg4];

        arg0->mouthAnim.animSet = arg3;
        arg0->mouthAnim.curAnimType = temp_v0->type;
        arg0->mouthAnim.curAnim = temp_v0;
        arg0->mouthAnim.delayTimer = 0;
        arg0->mouthAnim.curFrame = 0;
        arg0->mouthAnim.curIndex = temp_v0->frames->index[0];
    }
}

void EnInvadepoh_func_80B45CE0(EnInvadePohUnkStruct_324* arg0) {
    Vec3f sp3C;
    Vec3s sp34;

    sp34.x = arg0->unk_26.x - arg0->unk_20.x;
    sp34.y = arg0->unk_26.y - arg0->unk_20.y;
    sp34.z = arg0->unk_26.z - arg0->unk_20.z;
    Math_Vec3s_ToVec3f(&sp3C, &sp34);
    Math_Vec3f_Scale(&sp3C, arg0->unk_30);
    Math_Vec3f_ToVec3s(&sp34, &sp3C);
    sp34.x = ABS(sp34.x);
    sp34.y = ABS(sp34.y);
    sp34.z = ABS(sp34.z);
    sp34.x = CLAMP_MAX(sp34.x, arg0->unk_2C);
    sp34.y = CLAMP_MAX(sp34.y, arg0->unk_2C);
    sp34.z = CLAMP_MAX(sp34.z, arg0->unk_2C);

    Math_ScaledStepToS(&arg0->unk_20.x, arg0->unk_26.x, sp34.x);
    Math_ScaledStepToS(&arg0->unk_20.y, arg0->unk_26.y, sp34.y);
    Math_ScaledStepToS(&arg0->unk_20.z, arg0->unk_26.z, sp34.z);
    Math_StepToF(&arg0->unk_34, arg0->unk_38, arg0->unk_3C);

    if (arg0->unk_40 != arg0->unk_42) {
        s16 var_a2 = arg0->unk_42 - arg0->unk_40;

        var_a2 *= arg0->unk_44;
        var_a2 = ABS(var_a2);
        var_a2 = CLAMP(var_a2, 100, arg0->unk_48);
        Math_ScaledStepToS(&arg0->unk_40, arg0->unk_42, var_a2);
    }
    EnInvadepoh_func_80B45BB8(&arg0->eyeAnim);
    EnInvadepoh_func_80B45BB8(&arg0->mouthAnim);
}

void EnInvadepoh_func_80B45EC8(EnInvadepoh* this, PlayState* play, s32 arg2) {
    static Color_RGBA8 D_80B4EC18 = { 255, 255, 200, 255 };
    static Color_RGBA8 D_80B4EC1C = { 255, 200, 0, 0 };
    s32 var_s1;
    Vec3f spA8;
    Vec3f sp9C;
    Vec3f sp90;
    f32 temp_fs0;
    s16 var_s0 = 0;

    for (var_s1 = 0; var_s1 < arg2; var_s1++) {
        var_s0 += (s16)(0x10000 * 1.0f / arg2);
        temp_fs0 = (Rand_ZeroOne() * 0.5f) + 0.5f;

        spA8.x = Math_SinS(var_s0) * temp_fs0;
        spA8.z = Math_CosS(var_s0) * temp_fs0;

        sp9C.x = (Rand_ZeroOne() * 16.0f) + (spA8.x * 30.0f) - 8.0f;
        sp9C.y = -8.0f;
        sp9C.z = (Rand_ZeroOne() * 16.0f) + (spA8.z * 30.0f) - 8.0f;

        sp90.x = sp9C.x * -0.025f;
        sp90.y = sp9C.y * -0.025f;
        sp90.z = sp9C.z * -0.025f;

        spA8.x = (spA8.x * 100.0f) + this->actor.world.pos.x;
        spA8.y = (Rand_ZeroOne() * 180.0f) + this->actor.world.pos.y - 90.0f;
        spA8.z = (spA8.z * 100.0f) + this->actor.world.pos.z;
        EffectSsKirakira_SpawnDispersed(play, &spA8, &sp9C, &sp90, &D_80B4EC18, &D_80B4EC1C, 6000, -40);
    }
}

s32 EnInvadepoh_func_80B46118(Vec3f* arg0) {
    EnInvadepohWarpEffect* warpEffect = D_80B50350;
    s32 i;

    for (i = 0; i < 10; i++, warpEffect++) {
        if (warpEffect->timer <= 0) {
            warpEffect->unk_0 = 0;
            warpEffect->timer = 40;
            Math_Vec3f_Copy(&warpEffect->pos, arg0);
            warpEffect->alpha = 0;
            return true;
        }
    }
    return false;
}

void EnInvadepoh_func_80B46184(EnInvadepohWarpEffect* warpEffect) {
    if (warpEffect->timer > 20) {
        if (warpEffect->alpha < 125) {
            warpEffect->alpha += 10;
        } else {
            warpEffect->alpha = 135;
        }
    } else {
        if (warpEffect->alpha > 13) {
            warpEffect->alpha -= 13;
        } else {
            warpEffect->alpha = 0;
        }
    }
}

s32 EnInvadepoh_func_80B461DC(void) {
    static void (*D_80B4EC20[1])(EnInvadepohWarpEffect*) = { EnInvadepoh_func_80B46184 };
    s32 var_s4 = 0;
    s32 i;
    EnInvadepohWarpEffect* warpEffect;

    for (i = 0, warpEffect = D_80B50350; i < 10; i++, warpEffect++) {
        if (warpEffect->timer > 0) {
            D_80B4EC20[warpEffect->unk_0](warpEffect);
            var_s4 = 1;
            warpEffect->timer -= 1;
        }
    }
    return var_s4;
}

void EnInvadepoh_func_80B4627C(Actor* thisx, PlayState* play) {
    // PlayState* play = play2; Massive problems
    EnInvadepoh* this = (EnInvadepoh*)thisx;
    s32 var_a2;
    s32 var_v1;

    this->actor.flags |= ACTOR_FLAG_20;
    var_v1 = ENINVADEPOH_GET_PARAM_7F00(&this->actor);

    for (var_a2 = 1; var_a2 < 8; var_a2++) {
        Path* path = &play->setupPathList[var_v1];

        var_v1 = path->unk1;
        if (var_v1 == 0xFF) {
            break;
        }
    }
    this->unk_379 = var_a2;
    EnInvadepoh_func_80B451A0(this, play);
    EnInvadepoh_func_80B45648(this);
    func_800BC154(play, &play->actorCtx, &this->actor, 0);
    if (D_80B4E940 == 1) {
        EnInvadepoh_func_80B46DA8(this);
    } else if (D_80B4E940 == 2) {
        if (gSaveContext.save.time < CLOCK_TIME(2, 31)) {
            EnInvadepoh_func_80B46DA8(this);
        } else {
            EnInvadepoh_func_80B454BC(this, play);
            EnInvadepoh_func_80B452EC(this, play);
            AudioSeq_QueueSeqCmd(0x8000 | NA_BGM_ALIEN_INVASION);
            EnInvadepoh_func_80B46F88(this);
        }
    } else if (D_80B4E940 == 3) {
        if (gSaveContext.save.entrance == ENTRANCE(ROMANI_RANCH, 6)) {
            EnInvadepoh_func_80B471C0(this);
        } else if (gSaveContext.save.entrance == ENTRANCE(ROMANI_RANCH, 7)) {
            EnInvadepoh_func_80B47248(this);
        } else {
            EnInvadepoh_func_80B47248(this);
        }
    } else if (D_80B4E940 == 4) {
        EnInvadepoh_func_80B47304(this);
    }
}

InitChainEntry D_80B4EC24[4] = {
    ICHAIN_F32(uncullZoneForward, 20000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 500, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 600, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_STOP),
};
void EnInvadepoh_func_80B46414(Actor* thisx, PlayState* play) {
    // PlayState* play = play2; Stack size problems
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    Actor_ProcessInitChain(&this->actor, D_80B4EC24);
    Collider_InitCylinder(play, &this->unk_2A0);
    ActorShape_Init(&this->actor.shape, 6800.0f, ActorShadow_DrawWhiteCircle, 150.0f);
    this->actor.shape.shadowAlpha = 140;
    this->actor.flags = ACTOR_FLAG_80000000 | ACTOR_FLAG_1000 | ACTOR_FLAG_10;
    if (ENINVADEPOH_GET_PARAM_F0(&this->actor) == ENINVADEPOH_ALIEN_ABDUCTOR) {
        this->actor.update = EnInvadepoh_func_80B4D670;
        this->actor.world.pos.y = this->actor.home.pos.y + 150.0f;
    } else {
        this->actor.update = EnInvadepoh_func_80B47BAC;
        Collider_SetCylinder(play, &this->unk_2A0, &this->actor, &D_80B4E8B0);
        this->actor.colChkInfo.mass = 40;
    }
    this->unk_2F4 = Object_GetIndex(&play->objectCtx, OBJECT_UCH);
    if (this->unk_2F4 < 0) {
        Actor_Kill(&this->actor);
    }
}

InitChainEntry D_80B4EC34[4] = {
    ICHAIN_F32(uncullZoneForward, 20000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 300, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_STOP),
};
void EnInvadepoh_func_80B46520(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    Actor_ProcessInitChain(&this->actor, D_80B4EC34);
    this->actor.update = EnInvadepoh_func_80B47FA8;
    Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, ACTOR_EN_INVADEPOH, 0.0f, 0.0f, 0.0f, 0, 0, 0,
                       ENINVADEPOH_SET_PARAMS(0, ENINVADEPOH_COW_TAIL, 0));
    this->unk_2F4 = Object_GetIndex(&play->objectCtx, OBJECT_COW);
    if (this->unk_2F4 < 0) {
        Actor_Kill(&this->actor);
    }
}

InitChainEntry D_80B4EC44[4] = {
    ICHAIN_F32(uncullZoneForward, 20000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 100, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_STOP),
};
void EnInvadepoh_func_80B465CC(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    Actor_ProcessInitChain(&this->actor, D_80B4EC44);
    this->actor.update = EnInvadepoh_func_80B481C4;
    this->unk_2F4 = Object_GetIndex(&play->objectCtx, OBJECT_COW);
    if (this->unk_2F4 < 0) {
        Actor_Kill(&this->actor);
    }
}

InitChainEntry D_80B4EC54[5] = {
    ICHAIN_F32(uncullZoneForward, 20000, ICHAIN_CONTINUE), ICHAIN_F32(uncullZoneScale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 100, ICHAIN_CONTINUE),  ICHAIN_F32(targetArrowOffset, 1500, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_STOP),
};
void EnInvadepoh_func_80B46644(Actor* thisx, PlayState* play) {
    // PlayState* play = play2; Stack management problems
    EnInvadepoh* this = (EnInvadepoh*)thisx;
    s32 temp_v1 = ENINVADEPOH_GET_PARAM_F0(&this->actor);

    Actor_ProcessInitChain(&this->actor, D_80B4EC54);
    if ((temp_v1 == ENINVADEPOH_ROMANI_NIGHT_1) || (temp_v1 == ENINVADEPOH_ROMANI_NIGHT_3)) {
        this->actor.targetMode = 3;
    } else {
        this->actor.targetMode = 6;
    }
    func_800BC154(play, &play->actorCtx, &this->actor, 4);
    Collider_InitCylinder(play, &this->unk_2A0);
    if (temp_v1 != ENINVADEPOH_ROMANI_ABDUCTED) {
        ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 18.0f);
        Collider_SetCylinder(play, &this->unk_2A0, &this->actor, &D_80B4E8DC);
        this->actor.colChkInfo.mass = 0xFF;
    }
    if (temp_v1 == ENINVADEPOH_ROMANI_ABDUCTED) {
        this->actor.update = EnInvadepoh_func_80B48620;
    } else if (temp_v1 == ENINVADEPOH_ROMANI_CONFUSED) {
        this->actor.update = EnInvadepoh_func_80B48FB0;
        this->actor.flags = ACTOR_FLAG_10 | ACTOR_FLAG_8 | ACTOR_FLAG_1;
    } else if (temp_v1 == ENINVADEPOH_ROMANI_NIGHT_1) {
        this->actor.update = EnInvadepoh_func_80B49F88;
    } else if (temp_v1 == ENINVADEPOH_ROMANI_UNKNOWN) {
        this->actor.update = EnInvadepoh_func_80B4A9C8;
    } else if (temp_v1 == ENINVADEPOH_ROMANI_REWARD) {
        this->actor.update = EnInvadepoh_func_80B4B0C4;
    } else {
        this->actor.update = EnInvadepoh_func_80B4CE54;
    }
    this->unk_2F4 = Object_GetIndex(&play->objectCtx, OBJECT_MA1);
    if (this->unk_2F4 < 0) {
        Actor_Kill(&this->actor);
    }
    if (temp_v1 == ENINVADEPOH_ROMANI_CONFUSED) {
        if (gSaveContext.save.saveInfo.weekEventReg[22] & 1) {
            Actor_Kill(&this->actor);
        }
    } else if (temp_v1 == ENINVADEPOH_ROMANI_NIGHT_1) {
        if ((gSaveContext.save.time < CLOCK_TIME(6, 00)) && (gSaveContext.save.time >= CLOCK_TIME(2, 15))) {
            Actor_Kill(&this->actor);
        }
    } else if (temp_v1 == ENINVADEPOH_ROMANI_UNKNOWN) {
        // nothing
    } else if (temp_v1 == ENINVADEPOH_ROMANI_REWARD) {
        if (gSaveContext.save.entrance != ENTRANCE(ROMANI_RANCH, 6)) {
            Actor_Kill(&this->actor);
        }
    } else if (temp_v1 == ENINVADEPOH_ROMANI_NIGHT_3) {
        if (!(gSaveContext.save.saveInfo.weekEventReg[22] & 1)) {
            Actor_Kill(&this->actor);
        }
        D_80B503F4 = this;
    }
}

InitChainEntry D_80B4EC68[6] = {
    ICHAIN_F32(uncullZoneForward, 20000, ICHAIN_CONTINUE), ICHAIN_F32(uncullZoneScale, 1000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 1000, ICHAIN_CONTINUE), ICHAIN_VEC3S(shape, 0, ICHAIN_CONTINUE),
    ICHAIN_F32(terminalVelocity, -100, ICHAIN_CONTINUE),   ICHAIN_VEC3F_DIV1000(scale, 1000, ICHAIN_STOP),
};
void EnInvadepoh_func_80B468B4(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    Actor_ProcessInitChain(&this->actor, D_80B4EC68);
    this->actor.update = EnInvadepoh_func_80B49B1C;
    this->actor.draw = EnInvadepoh_func_80B4E3F0;
    func_800BC154(play, &play->actorCtx, &this->actor, 4);
    if ((D_80B4E940 == 1) || (gSaveContext.save.time < CLOCK_TIME(2, 31))) {
        this->actor.world.pos.x += D_80B4E934.x;
        this->actor.world.pos.y += D_80B4E934.y + 3000.0f;
        this->actor.world.pos.z += D_80B4E934.z;
        EnInvadepoh_func_80B491EC(this);
    } else if (D_80B4E940 == 2) {
        this->actor.world.pos.y += 1500.0f;
        EnInvadepoh_func_80B49628(this);
    } else {
        Actor_Kill(&this->actor);
    }
}

InitChainEntry D_80B4EC80[6] = {
    ICHAIN_F32(uncullZoneForward, 2000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 50, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 50, ICHAIN_CONTINUE),
    ICHAIN_F32(gravity, -3, ICHAIN_CONTINUE),
    ICHAIN_U8(targetMode, 4, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 7, ICHAIN_STOP),
};
void EnInvadepoh_func_80B469C4(Actor* thisx, PlayState* play) {
    // PlayState* play = play2; Stack size problems
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    Actor_ProcessInitChain(&this->actor, D_80B4EC80);
    this->actor.update = EnInvadepoh_func_80B4B8BC;
    Collider_InitCylinder(play, &this->unk_2A0);
    Collider_SetCylinder(play, &this->unk_2A0, &this->actor, &D_80B4E908);
    this->actor.colChkInfo.mass = 0x50;
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 24.0f);
    this->unk_2F4 = Object_GetIndex(&play->objectCtx, OBJECT_DOG);
    if (this->unk_2F4 < 0) {
        Actor_Kill(&this->actor);
    }
}

InitChainEntry D_80B4EC98[6] = {
    ICHAIN_F32(uncullZoneForward, 20000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 150, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 1500, ICHAIN_CONTINUE),
    ICHAIN_U8(targetMode, 3, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_STOP),
};
void EnInvadepoh_func_80B46A80(Actor* thisx, PlayState* play) {
    // PlayState* play = play2; Stack size problems
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    Actor_ProcessInitChain(&this->actor, D_80B4EC98);
    this->actor.update = EnInvadepoh_func_80B4C3A0;
    func_800BC154(play, &play->actorCtx, &this->actor, 4);
    Collider_InitCylinder(play, &this->unk_2A0);
    Collider_SetCylinder(play, &this->unk_2A0, &this->actor, &D_80B4E8DC);
    this->actor.colChkInfo.mass = MASS_HEAVY;
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 18.0f);
    this->unk_2F4 = Object_GetIndex(&play->objectCtx, OBJECT_MA2);
    if (this->unk_2F4 < 0) {
        Actor_Kill(&this->actor);
    }
    if (!(gSaveContext.save.saveInfo.weekEventReg[22] & 1)) {
        Actor_Kill(&this->actor);
    }
    D_80B503F8 = this;
}

void EnInvadepoh_Init(Actor* thisx, PlayState* play) {
    static ActorFunc D_80B4ECB0[14] = {
        EnInvadepoh_func_80B4627C, // Event handler
        EnInvadepoh_func_80B46414, // Alien invader
        EnInvadepoh_func_80B46520, // Abducted cow
        EnInvadepoh_func_80B465CC, // Cow tail
        EnInvadepoh_func_80B46644, // Abducted Romani
        EnInvadepoh_func_80B46644, // Confused Romani
        EnInvadepoh_func_80B468B4, // Light ball
        EnInvadepoh_func_80B46644, // Night 1 Romani
        EnInvadepoh_func_80B46644, // Unknown Romani
        EnInvadepoh_func_80B46644, // Reward Romani
        EnInvadepoh_func_80B469C4, // Dog
        EnInvadepoh_func_80B46A80, // Night 3 Cremia
        EnInvadepoh_func_80B46644, // Night 3 Romani
        EnInvadepoh_func_80B46414, // Alien abductor
    };

    D_80B4ECB0[ENINVADEPOH_GET_PARAM_F0(thisx)](thisx, play);
}

void EnInvadepoh_func_80B46BB0(Actor* thisx, PlayState* play2) {
}

void EnInvadepoh_func_80B46BC0(Actor* thisx, PlayState* play2) {
    EnInvadepoh* this = (EnInvadepoh*)thisx;
    s32 sp18 = ENINVADEPOH_GET_PARAM_7(&this->actor);
    PlayState* play = play2;

    Collider_DestroyCylinder(play, &this->unk_2A0);
    D_80B50320[sp18] = NULL;
}

void EnInvadepoh_func_80B46C08(Actor* thisx, PlayState* play2) {
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    if (this->actor.parent != NULL) {
        this->actor.parent->child = NULL;
    }
    if (this->actor.child != NULL) {
        this->actor.child->parent = NULL;
    }
}

void EnInvadepoh_func_80B46C34(Actor* thisx, PlayState* play2) {
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    if (this->actor.parent != NULL) {
        this->actor.parent->child = NULL;
    }
}

void EnInvadepoh_func_80B46C50(Actor* thisx, PlayState* play2) {
    PlayState* play = play2; // both or neither recast required
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    Collider_DestroyCylinder(play, &this->unk_2A0);
}

void EnInvadepoh_func_80B46C7C(Actor* thisx, PlayState* play2) {
    D_80B503F0 = NULL;
}

void EnInvadepoh_func_80B46C94(Actor* thisx, PlayState* play2) {
    PlayState* play = play2; // both or neither recast required
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    Collider_DestroyCylinder(play, &this->unk_2A0);
}

void EnInvadepoh_func_80B46CC0(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    Collider_DestroyCylinder(play, &this->unk_2A0);
    D_80B503F8 = NULL;
}

void EnInvadepoh_func_80B46CF4(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    Collider_DestroyCylinder(play, &this->unk_2A0);
    D_80B503F4 = NULL;
}

void EnInvadepoh_func_80B46D28(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx; // this recast required

    Collider_DestroyCylinder(play, &this->unk_2A0);
    if (this->actor.child != NULL) {
        this->actor.child->parent = NULL;
    }
}

void EnInvadepoh_Destroy(Actor* thisx, PlayState* play) {
    static ActorFunc D_80B4ECE8[14] = {
        EnInvadepoh_func_80B46BB0, // Event handler
        EnInvadepoh_func_80B46BC0, // Alien invader
        EnInvadepoh_func_80B46C08, // Abducted cow
        EnInvadepoh_func_80B46C34, // Cow tail
        EnInvadepoh_func_80B46C50, // Abducted Romani
        EnInvadepoh_func_80B46C50, // Confused Romani
        EnInvadepoh_func_80B46C7C, // Light ball
        EnInvadepoh_func_80B46C50, // Night 1 Romani
        EnInvadepoh_func_80B46C50, // Unknown Romani
        EnInvadepoh_func_80B46C50, // Reward Romani
        EnInvadepoh_func_80B46C94, // Dog
        EnInvadepoh_func_80B46CC0, // Night 3 Cremia
        EnInvadepoh_func_80B46CF4, // Night 3 Romani
        EnInvadepoh_func_80B46D28, // Alien abductor
    };

    D_80B4ECE8[ENINVADEPOH_GET_PARAM_F0(thisx)](thisx, play);
}

void EnInvadepoh_func_80B46DA8(EnInvadepoh* this) {
    D_80B4E940 = 1;
    this->actionFunc = EnInvadepoh_func_80B46DC8;
}

void EnInvadepoh_func_80B46DC8(EnInvadepoh* this, PlayState* play) {
    if ((gSaveContext.save.time < CLOCK_TIME(6, 00)) && (gSaveContext.save.time >= CLOCK_TIME(2, 30))) {
        EnInvadepoh_func_80B454BC(this, play);
        EnInvadepoh_func_80B452EC(this, play);
        EnInvadepoh_func_80B46E20(this);
    }
}

void EnInvadepoh_func_80B46E20(EnInvadepoh* this) {
    D_80B4E940 = 2;
    this->unk_2F0 = 2;
    this->actionFunc = EnInvadepoh_func_80B46E44;
}

void EnInvadepoh_func_80B46E44(EnInvadepoh* this, PlayState* play) {
    if (this->unk_2F0 > 0) {
        this->unk_2F0--;
    } else if (CutsceneManager_IsNext(D_80B50404[0])) {
        CutsceneManager_StartWithPlayerCs(D_80B50404[0], &this->actor);
        EnInvadepoh_func_80B46EC0(this);
    } else {
        CutsceneManager_Queue(D_80B50404[0]);
    }
}

void EnInvadepoh_func_80B46EC0(EnInvadepoh* this) {
    D_80B4E940 = 2;
    this->unk_2F0 = 160;
    this->actionFunc = EnInvadepoh_func_80B46EE8;
}

void EnInvadepoh_func_80B46EE8(EnInvadepoh* this, PlayState* play) {
    static s16 D_80B4ED20[8] = {
        130, 125, 115, 100, 80, 78, 76, 74,
    };
    s32 i;

    for (i = 0; i < 8; i++) {
        if (this->unk_2F0 == D_80B4ED20[i]) {
            D_80B50340[i] |= 1;
        }
    }
    this->unk_2F0--;
    if (this->unk_2F0 <= 0) {
        CutsceneManager_Stop(D_80B50404[0]);
        AudioSeq_QueueSeqCmd(0x8000 | NA_BGM_ALIEN_INVASION);
        EnInvadepoh_func_80B46F88(this);
    }
}

void EnInvadepoh_func_80B46F88(EnInvadepoh* this) {
    D_80B4E940 = 2;
    this->actionFunc = EnInvadepoh_func_80B46FA8;
}

void EnInvadepoh_func_80B46FA8(EnInvadepoh* this, PlayState* play) {
    Actor** var_v1;
    EnInvadepoh* temp_a0;
    s32 var_v0;
    s8 temp_a1;
    u16 temp_v0;
    s32 i;

    if ((gSaveContext.save.time < CLOCK_TIME(6, 00)) && (gSaveContext.save.time >= CLOCK_TIME(5, 15))) {
        gSaveContext.save.saveInfo.weekEventReg[22] |= 1;
        EnInvadepoh_func_80B47064(this);
    } else {
        EnInvadepoh_func_80B457A0(this);
        for (i = 0; i < this->unk_379; i++) {
            if ((D_80B50320[i] != NULL) && (D_80B50320[i]->unk_38A)) {
                EnInvadepoh_func_80B47278(this);
                break;
            }
        }
    }
}

void EnInvadepoh_func_80B47064(EnInvadepoh* this) {
    D_80B4E940 = 3;
    this->actionFunc = EnInvadepoh_func_80B47084;
}

void EnInvadepoh_func_80B47084(EnInvadepoh* this, PlayState* play) {
    if (CutsceneManager_IsNext(D_80B50404[1])) {
        CutsceneManager_StartWithPlayerCs(D_80B50404[1], &this->actor);
        EnInvadepoh_func_80B470E0(this);
    } else {
        CutsceneManager_Queue(D_80B50404[1]);
    }
}

void EnInvadepoh_func_80B470E0(EnInvadepoh* this) {
    D_80B4E940 = 3;
    this->unk_2F0 = 110;
    this->actionFunc = EnInvadepoh_func_80B47108;
}

void EnInvadepoh_func_80B47108(EnInvadepoh* this, PlayState* play) {
    if (this->unk_2F0 == 100) {
        Audio_PlayFanfare(NA_BGM_CLEAR_EVENT);
    }
    this->unk_2F0--;
    if (this->unk_2F0 <= 0) {
        play->nextEntrance = ENTRANCE(ROMANI_RANCH, 6);
        gSaveContext.nextCutsceneIndex = 0;
        play->transitionTrigger = TRANS_TRIGGER_START;
        play->transitionType = TRANS_TYPE_73;
        gSaveContext.nextTransitionType = TRANS_TYPE_72;
        D_801BDAA0 = 1;
        D_801BDA9C = 0;
        EnInvadepoh_func_80B47248(this);
    }
}

void EnInvadepoh_func_80B471C0(EnInvadepoh* this) {
    D_80B4E940 = 3;
    this->actionFunc = EnInvadepoh_func_80B471E0;
}

void EnInvadepoh_func_80B471E0(EnInvadepoh* this, PlayState* play) {
    if (D_80B4E998 != 0) {
        play->nextEntrance = ENTRANCE(ROMANI_RANCH, 7);
        gSaveContext.nextCutsceneIndex = 0;
        play->transitionTrigger = TRANS_TRIGGER_START;
        play->transitionType = TRANS_TYPE_72;
        gSaveContext.nextTransitionType = TRANS_TYPE_72;
        EnInvadepoh_func_80B47248(this);
    }
}

void EnInvadepoh_func_80B47248(EnInvadepoh* this) {
    D_80B4E940 = 3;
    this->actionFunc = EnInvadepoh_func_80B47268;
}

void EnInvadepoh_func_80B47268(EnInvadepoh* this, PlayState* play) {
}

void EnInvadepoh_func_80B47278(EnInvadepoh* this) {
    D_80B4E940 = 4;
    this->actionFunc = EnInvadepoh_func_80B47298;
}

void EnInvadepoh_func_80B47298(EnInvadepoh* this, PlayState* play) {
    play->nextEntrance = ENTRANCE(ROMANI_RANCH, 0);
    gSaveContext.nextCutsceneIndex = 0xFFF3;
    play->transitionTrigger = TRANS_TRIGGER_START;
    play->transitionType = TRANS_TYPE_72;
    gSaveContext.nextTransitionType = TRANS_TYPE_72;
    gSaveContext.save.saveInfo.weekEventReg[89] |= 0x10;
    EnInvadepoh_func_80B47304(this);
}

void EnInvadepoh_func_80B47304(EnInvadepoh* this) {
    D_80B4E940 = 4;
    this->actionFunc = EnInvadepoh_func_80B47324;
}

void EnInvadepoh_func_80B47324(EnInvadepoh* this, PlayState* play) {
}

void EnInvadepoh_Update(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    this->actionFunc(this, play);

    this->actor.draw = EnInvadepoh_func_80B461DC() ? EnInvadepoh_func_80B4D9B4 : NULL;
}

void EnInvadepoh_func_80B47380(EnInvadepoh* this) {
    this->unk_2A0.base.atFlags &= ~AT_ON;
    this->unk_2A0.base.acFlags &= ~AC_ON;
    this->unk_2A0.base.ocFlags1 &= ~OC1_ON;
    this->actor.flags &= ~ACTOR_FLAG_80000000;
    this->unk_389 = 0;
    this->actor.draw = NULL;
    this->unk_38B = 0;
    this->unk_38C = 0;
    this->unk_38D = 0;
    this->actionFunc = EnInvadepoh_func_80B473E4;
}

void EnInvadepoh_func_80B473E4(EnInvadepoh* this, PlayState* play) {
    EnInvadepoh_func_80B442E4(this);
    EnInvadepoh_func_80B447C0(this, play);
    EnInvadepoh_func_80B43DD4(this, 0x320, 0);
    if (D_80B50340[ENINVADEPOH_GET_PARAM_7(&this->actor)] & 1) {
        Actor_SetScale(&this->actor, 0.01f);
        EnInvadepoh_func_80B4516C(this);
        EnInvadepoh_func_80B46118(&this->actor.world.pos);
        EnInvadepoh_func_80B47568(this);
    }
}

void EnInvadepoh_func_80B47478(EnInvadepoh* this) {
    this->unk_2A0.base.atFlags &= ~AT_ON;
    this->unk_2A0.base.acFlags &= ~AC_ON;
    this->unk_2A0.base.ocFlags1 &= ~OC1_ON;
    this->actor.flags &= ~ACTOR_FLAG_80000000;
    this->unk_389 = 0;
    this->actor.draw = NULL;
    this->unk_38B = 0;
    this->unk_38C = 0;
    this->unk_38D = 0;
    this->actionFunc = EnInvadepoh_func_80B474DC;
}

void EnInvadepoh_func_80B474DC(EnInvadepoh* this, PlayState* play) {
    EnInvadepoh_func_80B442E4(this);
    EnInvadepoh_func_80B447C0(this, play);
    EnInvadepoh_func_80B43DD4(this, 0x320, 0);
    if (this->unk_320 > 0.0f) {
        Actor_SetScale(&this->actor, 0.01f);
        EnInvadepoh_func_80B4516C(this);
        EnInvadepoh_func_80B46118(&this->actor.world.pos);
        EnInvadepoh_func_80B47568(this);
    }
}

void EnInvadepoh_func_80B47568(EnInvadepoh* this) {
    Animation_MorphToLoop(&this->skelAnime, &gAlienFloatAnim, -6.0f);
    this->unk_2A0.base.atFlags &= ~AT_ON;
    this->unk_2A0.base.acFlags &= ~AC_ON;
    this->unk_2A0.base.ocFlags1 &= ~OC1_ON;
    this->unk_389 = 0;
    this->actor.draw = EnInvadepoh_func_80B4DB14;
    this->unk_38B = 1;
    this->unk_38C = 0;
    this->unk_38D = 0;
    this->actor.flags |= ACTOR_FLAG_80000000;
    this->actionFunc = EnInvadepoh_func_80B47600;
}

void EnInvadepoh_func_80B47600(EnInvadepoh* this, PlayState* play) {
    EnInvadepoh_func_80B442E4(this);
    EnInvadepoh_func_80B447C0(this, play);
    EnInvadepoh_func_80B43DD4(this, 0x320, 0);
    func_800B9010(&this->actor, NA_SE_EN_FOLLOWERS_BEAM_PRE - SFX_FLAG);
    if (this->unk_320 >= 0.9999f) {
        this->unk_38A = 1;
    }
    if (this->unk_389 >= 249) {
        this->unk_389 = 255;
    } else {
        this->unk_389 += 6;
    }
    if (this->unk_389 > 128) {
        this->unk_2A0.base.atFlags |= AT_ON;
        this->unk_2A0.base.acFlags |= AC_ON;
        this->unk_2A0.base.ocFlags1 |= OC1_ON;
    }
    if (this->unk_389 == 255) {
        if (this->unk_38D >= 245) {
            this->unk_38D = 255;
            EnInvadepoh_func_80B4770C(this);
        } else {
            this->unk_38D += 10;
        }
    }
}

void EnInvadepoh_func_80B4770C(EnInvadepoh* this) {
    if (this->skelAnime.animation != &gAlienFloatAnim) {
        Animation_MorphToLoop(&this->skelAnime, &gAlienFloatAnim, -6.0f);
    }
    this->unk_2A0.base.atFlags |= AT_ON;
    this->unk_2A0.base.acFlags |= AC_ON;
    this->unk_2A0.base.ocFlags1 |= OC1_ON;
    this->unk_389 = 255;
    this->actor.draw = EnInvadepoh_func_80B4DB14;
    this->unk_38B = 1;
    this->unk_38C = 0;
    this->unk_38D = 255;
    this->actor.flags |= ACTOR_FLAG_80000000;
    this->actionFunc = EnInvadepoh_func_80B477B4;
}

void EnInvadepoh_func_80B477B4(EnInvadepoh* this, PlayState* play) {
    EnInvadepoh_func_80B442E4(this);
    EnInvadepoh_func_80B447C0(this, play);
    EnInvadepoh_func_80B43DD4(this, 0x320, 0);
    func_800B9010(&this->actor, NA_SE_EN_FOLLOWERS_BEAM_PRE - SFX_FLAG);
    if (this->unk_320 >= 0.9999f) {
        this->unk_38A = 1;
    }
}

void EnInvadepoh_func_80B47830(EnInvadepoh* this) {
    this->unk_2A0.base.atFlags &= ~AT_ON;
    this->unk_2A0.base.acFlags &= ~AC_ON;
    this->unk_2A0.base.ocFlags1 |= OC1_ON;
    Animation_PlayLoop(&this->skelAnime, &gAlienJerkingAnim);
    Actor_SetColorFilter(&this->actor, 0x4000, 0xFF, 0, 0x10);
    this->unk_389 = 255;
    this->actor.draw = EnInvadepoh_func_80B4DB14;
    this->unk_38B = 1;
    this->unk_38C = 0;
    this->unk_38D = 0;
    this->unk_2F0 = 8;
    this->unk_2F2 = 0;
    this->actor.flags |= ACTOR_FLAG_80000000;
    this->actionFunc = EnInvadepoh_func_80B478F4;
}

void EnInvadepoh_func_80B478F4(EnInvadepoh* this, PlayState* play) {
    EnInvadepoh_func_80B44A90(this, play);
    this->unk_2F0--;
    if (this->unk_2F0 <= 0) {
        EnInvadepoh_func_80B47938(this);
    }
}

void EnInvadepoh_func_80B47938(EnInvadepoh* this) {
    this->unk_2A0.base.atFlags &= ~AT_ON;
    this->unk_2A0.base.acFlags &= ~AC_ON;
    this->unk_2A0.base.ocFlags1 &= ~OC1_ON;
    Animation_PlayLoop(&this->skelAnime, &gAlienDeathAnim);
    this->actor.flags &= ~ACTOR_FLAG_1;
    this->unk_2F0 = 10;
    this->unk_389 = 255;
    this->actor.draw = EnInvadepoh_func_80B4DB14;
    this->unk_38B = 1;
    this->unk_38C = 0;
    this->unk_38D = 255;
    this->actor.flags |= ACTOR_FLAG_80000000;
    this->actionFunc = EnInvadepoh_func_80B479E8;
}

void EnInvadepoh_func_80B479E8(EnInvadepoh* this, PlayState* play) {
    static Vec3f D_80B4ED30[5] = {
        { 0.01f, 0.01f, 0.01f }, { 0.02f, 0.01f, 0.005f }, { -0.01f, 0.0f, 0.0f },
        { 0.01f, 0.01f, 0.01f }, { 0.005f, 0.01f, 0.02f },
    };
    static Vec3f D_80B4ED6C[7] = {
        { 0.0005f, 0.027999999f, 0.01f }, { -0.01f, 0.0f, 0.0f }, { -0.01f, 0.0f, 0.0f },
        { 0.016f, 0.0004f, 0.01f },       { -0.01f, 0.0f, 0.0f }, { 0.0005f, 0.0005f, 0.0005f },
        { 0.0002f, 0.0002f, 0.0002f },
    };
    Vec3f* temp;

    EnInvadepoh_func_80B44B78(this);
    if (this->unk_2F2 < 5) {
        temp = &D_80B4ED30[this->unk_2F2];
        if (temp->x > 0.0f) {
            this->unk_38B = 1;
            this->unk_38D = 255;
            Math_Vec3f_Copy(&this->actor.scale, temp);
        } else {
            this->unk_38B = 0;
            this->unk_38D = 0;
        }
    } else {
        this->unk_38B = 0;
        this->unk_38D = 0;
    }
    if ((this->unk_2F2 >= 2) && (this->unk_2F2 < 9)) {
        temp = &D_80B4ED6C[this->unk_2F2 - 2];
        if (temp->x > 0.0f) {
            this->unk_38C = 1;
            Math_Vec3f_Copy(&this->unk_390, temp);
        } else {
            this->unk_38C = 0;
        }
    } else {
        this->unk_38C = 0;
    }
    this->unk_2F2++;
    if (this->unk_2F0 == 8) {
        Actor_Spawn(&play->actorCtx, play, ACTOR_EN_CLEAR_TAG, this->actor.world.pos.x, this->actor.world.pos.y - 10.0f,
                    this->actor.world.pos.z, 0, 0, 3, CLEAR_TAG_SMOKE);
    }
    if (this->unk_2F0 == 8) {
        Enemy_StartFinishingBlow(play, &this->actor);
    }
    this->unk_2F0--;
    if (this->unk_2F0 <= 0) {
        EnInvadepoh_func_80B43AF0(ENINVADEPOH_GET_PARAM_7(&this->actor));
        EnInvadepoh_func_80B43AB0();
        Item_DropCollectible(play, &this->actor.world.pos, 8);
        EnInvadepoh_func_80B47478(this);
    }
}

void EnInvadepoh_func_80B47BAC(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    if (Object_IsLoaded(&play->objectCtx, this->unk_2F4)) {
        this->actor.objBankIndex = this->unk_2F4;
        Actor_SetObjectDependency(play, &this->actor);
        EnInvadepoh_func_80B45080();
        this->actor.update = EnInvadepoh_func_80B47D30;
        SkelAnime_InitFlex(play, &this->skelAnime, &gAlienSkel, &gAlienFloatAnim, this->unk_188, this->unk_212,
                           ALIEN_LIMB_MAX);
        this->skelAnime.curFrame = (ENINVADEPOH_GET_PARAM_7(&this->actor)) * this->skelAnime.endFrame / 8.0f;
        EnInvadepoh_func_80B444BC(this, play);
        EnInvadepoh_func_80B442E4(this);
        EnInvadepoh_func_80B447C0(this, play);
        EnInvadepoh_func_80B43F0C(this);
        EnInvadepoh_func_80B4516C(this);
        if ((D_80B4E940 == 1) || (gSaveContext.save.time < CLOCK_TIME(2, 31))) {
            EnInvadepoh_func_80B47380(this);
        } else if (D_80B4E940 == 2) {
            if (this->unk_320 >= 0.0001f) {
                EnInvadepoh_func_80B4770C(this);
            } else {
                EnInvadepoh_func_80B47568(this);
            }
        } else {
            Actor_Kill(&this->actor);
        }
    }
}

void EnInvadepoh_func_80B47D30(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    if (D_80B4E940 == 3) {
        if ((this->actionFunc == EnInvadepoh_func_80B477B4) || (this->actionFunc == EnInvadepoh_func_80B47600)) {
            thisx->speed = 0.0f;
            thisx->velocity.y = 0.0f;
            thisx->gravity = 0.0f;
            EnInvadepoh_func_80B47830(this);
        } else if ((this->actionFunc == EnInvadepoh_func_80B474DC) || (this->actionFunc == EnInvadepoh_func_80B473E4)) {
            Actor_Kill(thisx);
            return;
        }
    } else if (this->unk_2A0.base.acFlags & AC_HIT) {
        Actor* hitbox = this->unk_2A0.base.ac;

        thisx->speed = hitbox->speed * 0.5f;
        thisx->speed = CLAMP(thisx->speed, -60.0f, 60.0f);

        thisx->world.rot.y = hitbox->world.rot.y;
        thisx->gravity = 0.0f;

        thisx->velocity.y = hitbox->velocity.y * 0.5f;
        thisx->velocity.y = CLAMP(thisx->velocity.y, -30.0f, 30.0f);

        SoundSource_PlaySfxAtFixedWorldPos(play, &thisx->world.pos, 50, NA_SE_EN_INVADER_DEAD);
        EnInvadepoh_func_80B47830(this);
    }

    this->actionFunc(this, play);

    if (thisx->draw != NULL) {
        this->unk_29C = SkelAnime_Update(&this->skelAnime);
    }

    Collider_UpdateCylinder(thisx, &this->unk_2A0);

    if (this->unk_2A0.base.atFlags & AT_ON) {
        CollisionCheck_SetAT(play, &play->colChkCtx, &this->unk_2A0.base);
    } else {
        this->unk_2A0.base.atFlags &= ~AT_HIT;
    }
    if (this->unk_2A0.base.acFlags & AC_ON) {
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->unk_2A0.base);
    } else {
        this->unk_2A0.base.acFlags &= ~AC_HIT;
    }
    if (this->unk_2A0.base.ocFlags1 & OC1_ON) {
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->unk_2A0.base);
    } else {
        this->unk_2A0.base.ocFlags1 &= ~OC1_HIT;
    }
}

void EnInvadepoh_func_80B47FA8(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    if (Object_IsLoaded(&play->objectCtx, this->unk_2F4)) {
        this->actor.objBankIndex = this->unk_2F4;
        Actor_SetObjectDependency(play, &this->actor);
        this->actor.update = EnInvadepoh_func_80B48060;
        this->actor.draw = EnInvadepoh_func_80B4E158;
        SkelAnime_InitFlex(play, &this->skelAnime, &gCowSkel, NULL, this->unk_188, this->unk_212, COW_LIMB_MAX);
        Animation_PlayLoop(&this->skelAnime, &gCowMooAnim);
    }
}

void EnInvadepoh_func_80B48060(Actor* thisx, PlayState* play2) {
    static s16 D_80B4EDC0[3] = { -0x1F40, -0x1770, -0x2AF8 };
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;
    s32 sp6C;

    if ((D_80B503F0 == NULL) || (this->actor.parent == NULL)) {
        Actor_Kill(&this->actor);
        return;
    }
    sp6C = ENINVADEPOH_GET_PARAM_7(&this->actor);
    SkelAnime_Update(&this->skelAnime);
    Math_ScaledStepToS(&this->actor.shape.rot.x, D_80B4EDC0[sp6C], 0x32);
    if (this->actor.child != NULL) {
        s32 pad;
        MtxF sp28;

        Matrix_Push();
        Matrix_SetTranslateRotateYXZ(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z,
                                     &this->actor.shape.rot);
        Matrix_Translate(0.0f, 57.0f, -36.0f, MTXMODE_APPLY);
        Matrix_RotateXS(this->actor.shape.rot.x * -0.7f, MTXMODE_APPLY);
        Matrix_RotateZS(this->actor.shape.rot.z * -0.7f, MTXMODE_APPLY);
        Matrix_MultZero(&this->actor.child->world.pos);
        Matrix_Get(&sp28);
        Matrix_MtxFToYXZRot(&sp28, &this->actor.child->shape.rot, 0);
        Matrix_Pop();
    }
}

void EnInvadepoh_func_80B481C4(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    if (Object_IsLoaded(&play->objectCtx, this->unk_2F4)) {
        this->actor.objBankIndex = this->unk_2F4;
        Actor_SetObjectDependency(play, &this->actor);
        this->actor.update = EnInvadepoh_func_80B4827C;
        this->actor.draw = EnInvadepoh_func_80B4E1B0;
        SkelAnime_InitFlex(play, &this->skelAnime, &gCowTailSkel, NULL, this->unk_188, this->unk_212,
                           COW_TAIL_LIMB_MAX);
        Animation_PlayLoop(&this->skelAnime, &gCowTailSwishAnim);
    }
}

void EnInvadepoh_func_80B4827C(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    if ((D_80B503F0 == NULL) || (this->actor.parent == NULL)) {
        Actor_Kill(&this->actor);
    } else {
        SkelAnime_Update(&this->skelAnime);
    }
}

void EnInvadepoh_func_80B482D4(EnInvadepoh* this) {
    this->unk_2F0 = 40;
    Animation_MorphToLoop(&this->skelAnime, &gRomaniLookAroundAnim, -10.0f);
    this->actor.draw = NULL;
    this->actionFunc = EnInvadepoh_func_80B48324;
}

void EnInvadepoh_func_80B48324(EnInvadepoh* this, PlayState* play) {
    this->unk_2F0--;
    if (this->unk_2F0 <= 0) {
        EnInvadepoh_func_80B4560C(this, play, 0x332F); // Romani's scream when abducted
        this->actor.draw = EnInvadepoh_func_80B4E324;
        EnInvadepoh_func_80B48374(this);
    }
}

void EnInvadepoh_func_80B48374(EnInvadepoh* this) {
    this->unk_2F0 = 60;
    Animation_MorphToLoop(&this->skelAnime, &gRomaniLookAroundAnim, -10.0f);
    this->actor.draw = EnInvadepoh_func_80B4E324;
    this->actionFunc = EnInvadepoh_func_80B483CC;
}

void EnInvadepoh_func_80B483CC(EnInvadepoh* this, PlayState* play) {
    if (this->unk_2F0 == 20) {
        EnInvadePohUnkStruct_324* temp_s0 = &this->unk_324;

        temp_s0->unk_26.x = 0x7D0;
        temp_s0->unk_26.y = 0;
        temp_s0->unk_26.z = 0;
        temp_s0->unk_30 = 0.1f;
        temp_s0->unk_2C = 0x3E8;
    }

    this->unk_2F0--;
    if (this->unk_2F0 <= 0) {
        EnInvadepoh_func_80B4843C(this);
    }
}

void EnInvadepoh_func_80B4843C(EnInvadepoh* this) {
    this->unk_324.unk_26.x = 0xBB8;
    this->unk_324.unk_26.y = 0;
    this->unk_324.unk_26.z = 0;
    this->unk_324.unk_30 = 0.24f;
    this->unk_324.unk_2C = 0xBB8;
    this->unk_324.unk_42 = 0x3A98;
    this->unk_324.unk_44 = 0.1f;
    this->unk_324.unk_48 = 0x7D0;
    this->unk_2F0 = 50;

    Animation_Change(&this->skelAnime, &gRomaniRunAnim, 2.0f, 0.0f, 0.0f, 0, -5.0f);
    this->actor.draw = EnInvadepoh_func_80B4E324;
    this->actionFunc = EnInvadepoh_func_80B484EC;
}

void EnInvadepoh_func_80B484EC(EnInvadepoh* this, PlayState* play) {
    if (this->unk_2F0 == 40) {
        this->unk_324.unk_26.y = 0x1B58;
    } else if (this->unk_2F0 == 30) {
        this->unk_324.unk_26.y = -0x1B58;
    } else if (this->unk_2F0 == 20) {
        this->unk_324.unk_26.y = 0x1B58;
    } else if (this->unk_2F0 == 10) {
        this->unk_324.unk_26.y = 0;
    }
    this->unk_2F0--;
    if (this->unk_2F0 <= 0) {
        EnInvadepoh_func_80B48588(this);
    }
}

void EnInvadepoh_func_80B48588(EnInvadepoh* this) {
    this->unk_324.unk_26.x = 0;
    this->unk_324.unk_26.y = 0;
    this->unk_324.unk_26.z = 0;
    this->unk_324.unk_30 = 0.24f;
    this->unk_324.unk_2C = 0x1388;
    this->unk_324.unk_42 = 0;
    this->unk_324.unk_44 = 0.28f;
    this->unk_324.unk_48 = 0x1B58;

    Animation_MorphToPlayOnce(&this->skelAnime, &gRomaniIdleAnim, -10.0f);
    this->actor.draw = EnInvadepoh_func_80B4E324;
    this->actionFunc = EnInvadepoh_func_80B48610;
}

void EnInvadepoh_func_80B48610(EnInvadepoh* this, PlayState* play) {
}

void EnInvadepoh_func_80B48620(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;
    s32 pad;

    if (Object_IsLoaded(&play->objectCtx, this->unk_2F4)) {
        this->actor.objBankIndex = this->unk_2F4;
        Actor_SetObjectDependency(play, &this->actor);
        EnInvadepoh_func_80B44F58();
        this->actor.update = EnInvadepoh_func_80B4873C;
        SkelAnime_InitFlex(play, &this->skelAnime, &gRomaniSkel, &gRomaniIdleAnim, this->unk_188, this->unk_212,
                           ROMANI_LIMB_MAX);
        EnInvadepoh_func_80B45C04(&this->unk_324, D_80B4EA90, 6, D_80B4EB00, 2, &gZeroVec3s, 0x1388, 0.05f, 0.3f,
                                  0.12f);
        Animation_PlayLoop(&this->skelAnime, &gRomaniIdleAnim);
        EnInvadepoh_func_80B482D4(this);
    }
}

void EnInvadepoh_func_80B4873C(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;
    EnInvadePohUnkStruct_324* temp_v1 = &this->unk_324;

    if (this->actor.parent == NULL) {
        Actor_Kill(&this->actor);
        return;
    }
    this->actionFunc(this, play);
    SkelAnime_Update(&this->skelAnime);
    EnInvadepoh_func_80B45CE0(&this->unk_324);
    if (temp_v1->unk_40 != 0) {
        this->actor.shape.rot.x = -temp_v1->unk_40;
    }
}

void EnInvadepoh_func_80B487B4(EnInvadepoh* this) {
    static s16 D_80B4EDC8[4] = { -0x708, -0x3E8, 0, 0x7D0 };
    EnInvadePohUnkStruct_324* temp_v1 = &this->unk_324;

    this->unk_2F0 = Rand_S16Offset(150, 250);
    temp_v1->unk_26.x = D_80B4EDC8[Rand_Next() >> 0x1E];
    temp_v1->unk_26.y = 0;
    temp_v1->unk_26.z = 0;
    temp_v1->unk_30 = 0.1f;
    temp_v1->unk_2C = 0x320;
    Animation_MorphToLoop(&this->skelAnime, &gRomaniWalkAnim, -10.0f);
    this->actionFunc = EnInvadepoh_func_80B48848;
}

void EnInvadepoh_func_80B48848(EnInvadepoh* this, PlayState* play) {
    s32 pad;

    Math_StepToF(&this->actor.speed, 1.6f, 0.1f);
    if (EnInvadepoh_func_80B44B84(this, play, this->actor.speed, 50.0f)) {
        EnInvadepoh_func_80B44514(this);
        this->unk_370 = 0xC8;
        this->actor.speed *= 0.25f;
    } else {
        Math_StepToS(&this->unk_370, 0x7D0, 0x46);
    }
    EnInvadepoh_func_80B43E6C(this, 6, this->unk_370, 0x46);
    if (CHECK_FLAG_ALL(this->actor.flags, ACTOR_FLAG_40) &&
        (Animation_OnFrame(&this->skelAnime, 0.0f) || Animation_OnFrame(&this->skelAnime, 7.0f))) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_ROMANI_WALK);
    }
    if (this->unk_2F0 > 0) {
        this->unk_2F0--;
    } else {
        EnInvadepoh_func_80B48948(this);
    }
}

void EnInvadepoh_func_80B48948(EnInvadepoh* this) {
    EnInvadePohUnkStruct_324* sp24 = &this->unk_324;
    f32 sp28 = Rand_ZeroOne();

    this->unk_2F0 = Rand_S16Offset(150, 150);
    if (sp28 < 0.5f) {
        this->unk_374 = 0;
        Math_Vec3s_Copy(&sp24->unk_26, &gZeroVec3s);
        sp24->unk_30 = 0.1f;
        sp24->unk_2C = 0x3E8;
    } else if (sp28 < 0.75f) {
        this->unk_374 = 1;
        sp24->unk_26.x = Rand_S16Offset(0, 0x7D0);
        sp24->unk_26.y = 0;
        sp24->unk_26.z = 0;
        sp24->unk_30 = 0.06f;
        sp24->unk_2C = 0x3E8;
    } else if (sp28 < 0.8f) {
        this->unk_374 = 2;
        sp24->unk_26.x = Rand_S16Offset(-0x7D0, 0x7D0);
        sp24->unk_26.y = 0;
        sp24->unk_26.z = 0;
        sp24->unk_30 = 0.05f;
        sp24->unk_2C = 0x3E8;
    } else {
        this->unk_374 = 3;
        sp24->unk_26.x = 0;
        sp24->unk_26.y = 0;
        sp24->unk_26.z = Rand_S16Offset(-0x9C4, 0x1388);
        sp24->unk_30 = 0.04f;
        sp24->unk_2C = 0x3E8;
    }
    Animation_MorphToLoop(&this->skelAnime, &gRomaniIdleAnim, -10.0f);
    this->actionFunc = EnInvadepoh_func_80B48AD4;
}

void EnInvadepoh_func_80B48AD4(EnInvadepoh* this, PlayState* play) {
    EnInvadePohUnkStruct_324* temp_s0 = &this->unk_324;

    Math_StepToF(&this->actor.speed, 0.0f, 0.2f);
    if (EnInvadepoh_func_80B44B84(this, play, this->actor.speed, 50.0f)) {
        EnInvadepoh_func_80B44514(this);
    }
    if (this->unk_374 == 0) {
        if ((this->actor.xzDistToPlayer < 350.0f) && (play->gameplayFrames & 0x60)) {
            Player* player = GET_PLAYER(play);
            s16 temp_v0 = Math_Vec3f_Pitch(&this->actor.focus.pos, &player->actor.focus.pos) * 0.85f;

            temp_s0->unk_26.x = CLAMP((s16)(temp_v0 - this->actor.shape.rot.x), -0x9C4, 0x9C4);

            temp_v0 = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
            temp_s0->unk_26.y = CLAMP((s16)(temp_v0 * 0.7f), -0x1F40, 0x1F40);
        }
    } else {
        temp_s0->unk_26.x = 0;
        temp_s0->unk_26.y = 0;
    }
    if (this->unk_2F0 > 0) {
        s32 temp = (u32)this->unk_2F0 % 0x20;

        if ((temp == 0) && (Rand_ZeroOne() < 0.3f)) {
            s32 temp_v1_3 = (s32)Rand_Next() % 4;

            if (temp_v1_3 != this->unk_374) {
                this->unk_374 = temp_v1_3;
                if (this->unk_374 == 0) {
                    Math_Vec3s_Copy(&temp_s0->unk_26, &gZeroVec3s);
                    temp_s0->unk_30 = 0.07f;
                } else if (this->unk_374 == 1) {
                    temp_s0->unk_26.x = Rand_S16Offset(0x3E8, 0x3E8);
                    temp_s0->unk_26.y = Rand_S16Offset(-0x3E8, 0x7D0);
                    temp_s0->unk_26.z = Rand_S16Offset(-0x320, 0x640);
                    temp_s0->unk_30 = 0.06f;
                } else if (this->unk_374 == 2) {
                    temp_s0->unk_26.x = Rand_S16Offset(-0x7D0, 0x3E8);
                    temp_s0->unk_26.y = Rand_S16Offset(-0x3E8, 0x7D0);
                    temp_s0->unk_26.z = Rand_S16Offset(-0x320, 0x640);
                    temp_s0->unk_30 = 0.05f;
                } else {
                    temp_s0->unk_26.x = Rand_S16Offset(-0x3E8, 0x7D0);
                    temp_s0->unk_26.y = Rand_S16Offset(-0x7D0, 0xFA0);
                    temp_s0->unk_26.z = Rand_S16Offset(-0x7D0, 0xFA0);
                    temp_s0->unk_30 = 0.04f;
                }
            }
        }
        this->unk_2F0--;
        return;
    }
    EnInvadepoh_func_80B487B4(this);
}

void EnInvadepoh_func_80B48DE4(EnInvadepoh* this) {
    EnInvadePohUnkStruct_324* temp_v0 = &this->unk_324;

    this->actor.speed = 0.0f;
    Animation_MorphToLoop(&this->skelAnime, &gRomaniIdleAnim, -10.0f);
    this->unk_370 = 0;
    temp_v0->unk_30 = 0.05f;
    temp_v0->unk_2C = 0x4B0;
    this->actionFunc = EnInvadepoh_func_80B48E4C;
}

void EnInvadepoh_func_80B48E4C(EnInvadepoh* this, PlayState* play) {
    EnInvadePohUnkStruct_324* temp_v0 = &this->unk_324;
    Player* player = GET_PLAYER(play);
    s16 temp_v1;

    Math_StepToS(&this->unk_370, 0x7D0, 0x32);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 6, this->unk_370, 0x23);

    temp_v1 = Math_Vec3f_Pitch(&this->actor.focus.pos, &player->actor.focus.pos) * 0.85f;
    temp_v0->unk_26.x = CLAMP((s16)(temp_v1 - this->actor.shape.rot.x), -0xBB8, 0xBB8);

    temp_v1 = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
    temp_v0->unk_26.y = CLAMP((s16)(temp_v1 * 0.7f), -0x1F40, 0x1F40);

    if (Actor_TextboxIsClosing(&this->actor, play)) {
        EnInvadepoh_func_80B48948(this);
    }
}

void EnInvadepoh_func_80B48FB0(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    if (Object_IsLoaded(&play->objectCtx, this->unk_2F4)) {
        this->actor.objBankIndex = this->unk_2F4;
        Actor_SetObjectDependency(play, &this->actor);
        EnInvadepoh_func_80B44F58();
        this->actor.update = EnInvadepoh_func_80B490F0;
        this->actor.draw = EnInvadepoh_func_80B4E324;
        this->actor.textId = 0x3330; // ........
        SkelAnime_InitFlex(play, &this->skelAnime, &gRomaniSkel, &gRomaniIdleAnim, this->unk_188, this->unk_212,
                           ROMANI_LIMB_MAX);
        EnInvadepoh_func_80B45C04(&this->unk_324, D_80B4EA90, 6, D_80B4EB00, 2, &gZeroVec3s, 100, 0.03f, 0.3f, 0.03f);
        EnInvadepoh_func_80B444F4(this, play);
        EnInvadepoh_func_80B4407C(this, 0);
        func_800B4AEC(play, &this->actor, 50.0f);
        EnInvadepoh_func_80B4516C(this);
        EnInvadepoh_func_80B487B4(this);
    }
}

void EnInvadepoh_func_80B490F0(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;
    s32 sp2C = CHECK_FLAG_ALL(this->actor.flags, ACTOR_FLAG_40);
    s32 sp28 = Actor_ProcessTalkRequest(&this->actor, &play->state);

    if (sp28) {
        func_80151BB4(play, 5);
        EnInvadepoh_func_80B48DE4(this);
    }
    this->actionFunc(this, play);
    if (sp2C) {
        SkelAnime_Update(&this->skelAnime);
        EnInvadepoh_func_80B45CE0(&this->unk_324);
        if ((this->actionFunc != EnInvadepoh_func_80B48E4C) && !sp28 && this->actor.isTargeted) {
            func_800B8614(&this->actor, play, 100.0f);
        }
        Collider_UpdateCylinder(&this->actor, &this->unk_2A0);
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->unk_2A0.base);
    }
}

void EnInvadepoh_func_80B491EC(EnInvadepoh* this) {
    this->actor.gravity = -15.0f;
    this->unk_39C = 0.0f;
    this->unk_3A0 = 1.0f;
    this->unk_3A4 = 0.0f;
    this->unk_3AA = 0;
    this->actionFunc = EnInvadepoh_func_80B49228;
}

void EnInvadepoh_func_80B49228(EnInvadepoh* this, PlayState* play) {
    s32 pad;
    f32 sp28;

    Actor_UpdateVelocityWithGravity(&this->actor);
    this->actor.velocity.y *= 0.97f;
    sp28 = Math_SmoothStepToF(&this->actor.world.pos.y, this->actor.home.pos.y + D_80B4E934.y + 300.0f, 0.7f,
                              fabsf(this->actor.velocity.y), 1.0f);
    func_800B9010(&this->actor, NA_SE_EV_UFO_APPEAR - SFX_FLAG);
    if (fabsf(sp28) < 1.0f) {
        EnInvadepoh_func_80B45EC8(this, play, 50);
        EnInvadepoh_func_80B492FC(this);
    }
}

void EnInvadepoh_func_80B492FC(EnInvadepoh* this) {
    this->actor.velocity.y *= 0.1f;
    this->unk_2F0 = 20;
    this->unk_3A0 = 0.3f;
    this->unk_3A4 = 0.03f;
    this->unk_3AA = 0xBB8;
    this->actionFunc = EnInvadepoh_func_80B4934C;
}

void EnInvadepoh_func_80B4934C(EnInvadepoh* this, PlayState* play) {
    f32 temp = this->actor.home.pos.y + D_80B4E934.y + 300.0f;

    if (this->actor.world.pos.y < temp) {
        this->actor.gravity = 3.0f;
    } else {
        this->actor.gravity = -2.0f;
    }
    this->actor.velocity.y *= 0.96f;
    Actor_MoveWithGravity(&this->actor);
    func_800B9010(&this->actor, NA_SE_EV_UFO_APPEAR - SFX_FLAG);
    this->unk_2F0--;
    if (this->unk_2F0 <= 0) {
        EnInvadepoh_func_80B49404(this);
    }
}

void EnInvadepoh_func_80B49404(EnInvadepoh* this) {
    this->unk_2F0 = 120;
    this->unk_3A0 = 0.2f;
    this->unk_3A4 = 0.01f;
    this->actor.gravity = 33.0f;
    this->unk_3AA = 0xBB8;
    this->unk_3AC = 0;
    this->unk_2F2 = 0;
    this->actionFunc = EnInvadepoh_func_80B49454;
}

void EnInvadepoh_func_80B49454(EnInvadepoh* this, PlayState* play) {
    static Vec3f D_80B4EDD0[5] = {
        { -1813.0f, 374.0f, 1900.0f }, { 2198.0f, 153.0f, 3365.0f }, { -1434.0f, 262.0f, 3365.0f },
        { -393.0f, 396.0f, 1084.0f },  { 0.0f, 1500.0f, 0.0f },
    };
    s32 pad;
    Vec3f sp30;
    s32 pad2;

    if (this->unk_2F2 < 25) {
        this->unk_2F2++;
    } else {
        this->unk_2F2 = 0;
        this->unk_3AC++;
        this->unk_3AC = CLAMP_MAX(this->unk_3AC, 4);
        this->actor.gravity = 33.0f;
        EnInvadepoh_func_80B45EC8(this, play, 20);
    }
    Math_Vec3f_Sum(&D_80B4EDD0[this->unk_3AC], &this->actor.home.pos, &sp30);
    if (Math3D_Vec3fDistSq(&this->actor.world.pos, &sp30) < SQ(400.0f)) {
        this->actor.speed *= 0.8f;
    } else {
        Math_StepToF(&this->actor.speed, 170.0f, 21.0f);
        this->actor.speed *= 0.98f;
    }
    if (EnInvadepoh_func_80B450C0(&this->actor.world.pos.x, &this->actor.world.pos.z, sp30.x, sp30.z,
                                  this->actor.speed)) {
        this->actor.speed = 0.0f;
    }
    if (sp30.y < this->actor.world.pos.y) {
        Math_StepToF(&this->actor.gravity, -12.0f, 7.0f);
    } else {
        Math_StepToF(&this->actor.gravity, 5.0f, 4.0f);
    }
    this->actor.velocity.y += this->actor.gravity;
    this->actor.velocity.y *= 0.97f;
    this->actor.world.pos.y += this->actor.velocity.y;
    func_800B9010(&this->actor, NA_SE_EV_UFO_APPEAR - SFX_FLAG);
    if (this->unk_2F0 > 0) {
        this->unk_2F0--;
    } else {
        EnInvadepoh_func_80B49628(this);
    }
}

void EnInvadepoh_func_80B49628(EnInvadepoh* this) {
    this->unk_3A0 = 0.2f;
    this->unk_3A4 = 0.01f;
    this->unk_3AA = 0xBB8;
    this->actor.velocity.y *= 0.8f;
    this->actionFunc = EnInvadepoh_func_80B49670;
}

void EnInvadepoh_func_80B49670(EnInvadepoh* this, PlayState* play) {
    s32 pad;
    Vec3f sp30;

    sp30.x = this->actor.home.pos.x;
    sp30.y = this->actor.home.pos.y + 1500.0f;
    sp30.z = this->actor.home.pos.z;
    Math_SmoothStepToS(&this->actor.world.rot.y, Math_Vec3f_Yaw(&this->actor.world.pos, &sp30), 0xA, 0xBB8, 0x64);
    if ((play->gameplayFrames % 0x40) < 14) {
        Math_StepToF(&this->actor.speed, 5.0f, 1.0f);
    } else {
        this->actor.speed *= 0.97f;
    }
    this->actor.gravity = (sp30.y < this->actor.world.pos.y) ? -0.5f : 2.0f;
    this->actor.velocity.y *= 0.97f;
    Actor_MoveWithGravity(&this->actor);
    if (D_80B4E940 == 3) {
        EnInvadepoh_func_80B499BC(this);
    }
}

void EnInvadepoh_func_80B497A4(EnInvadepoh* this) {
    this->unk_3A0 = 0.2f;
    this->unk_3A4 = 0.01f;
    this->actor.gravity = -1.5f;
    this->unk_3AA = 0xBB8;
    this->unk_2F0 = 35;
    this->actionFunc = EnInvadepoh_func_80B497EC;
}

void EnInvadepoh_func_80B497EC(EnInvadepoh* this, PlayState* play) {
    s32 pad;
    Vec3f sp30;

    sp30.x = this->actor.home.pos.x + D_80B4E934.x;
    sp30.y = this->actor.home.pos.y + D_80B4E934.y + 400.0f;
    sp30.z = this->actor.home.pos.z + D_80B4E934.z;
    Math_SmoothStepToS(&this->actor.world.rot.y, Math_Vec3f_Yaw(&this->actor.world.pos, &sp30), 4, 0x1F40, (s16)0x64);
    Math_StepToF(&this->actor.speed, 70.0f, 3.0f);
    this->actor.gravity = (sp30.y < this->actor.world.pos.y) ? -2.0f : 2.0f;
    this->actor.velocity.y *= 0.97f;
    Actor_MoveWithGravity(&this->actor);
    if (this->unk_2F0 > 0) {
        this->unk_2F0--;
    } else {
        EnInvadepoh_func_80B49904(this);
    }
}

void EnInvadepoh_func_80B49904(EnInvadepoh* this) {
    this->unk_3A0 = 0.2f;
    this->unk_3A4 = 0.01f;
    this->actor.gravity = 1.0f;
    this->unk_3AA = 0xBB8;
    this->unk_2F0 = 60;
    this->actionFunc = EnInvadepoh_func_80B4994C;
}

void EnInvadepoh_func_80B4994C(EnInvadepoh* this, PlayState* play) {
    Math_StepToF(&this->actor.speed, 150.0f, 4.0f);
    this->actor.velocity.y *= 0.95f;
    Actor_MoveWithGravity(&this->actor);
    if (this->unk_2F0 > 0) {
        this->unk_2F0--;
    } else {
        Actor_Kill(&this->actor);
    }
}

void EnInvadepoh_func_80B499BC(EnInvadepoh* this) {
    this->unk_2F0 = 40;
    this->unk_3A0 = 0.2f;
    this->unk_3A4 = 0.01f;
    this->actor.speed = 0.0f;
    this->unk_3AA = 0xBB8;
    this->actionFunc = EnInvadepoh_func_80B49A00;
}

void EnInvadepoh_func_80B49A00(EnInvadepoh* this, PlayState* play) {
    s32 pad;
    Vec3f sp30;

    sp30.x = this->actor.home.pos.x;
    sp30.y = this->actor.home.pos.y + 800.0f;
    sp30.z = this->actor.home.pos.z;
    Math_SmoothStepToS(&this->actor.world.rot.y, Math_Vec3f_Yaw(&this->actor.world.pos, &sp30), 4, 0x1F40, 0x64);
    Math_StepToF(&this->actor.speed, 30.0f, 3.0f);
    this->actor.velocity.y *= 0.98f;
    this->actor.gravity = (sp30.y < this->actor.world.pos.y) ? -0.5f : 2.0f;
    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(play, &this->actor, 0.0f, 0.0f, 0.0f, 4);

    if (this->unk_2F0 > 0) {
        this->unk_2F0--;
    } else {
        EnInvadepoh_func_80B497A4(this);
    }
}

void EnInvadepoh_func_80B49B1C(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;
    f32 temp;

    this->actionFunc(this, play);

    this->unk_3A8 += this->unk_3AA;
    Math_StepToF(&this->unk_39C, this->unk_3A0, this->unk_3A4);

    temp = 1.0f + (Math_SinS(this->unk_3A8) * this->unk_39C);
    Actor_SetScale(&this->actor, 0.27f * temp);
    Math_StepToS(&this->unk_306, 0x258, 8);
    this->actor.world.rot.y += this->unk_306;
    this->unk_304 += 0x258;
}

void EnInvadepoh_func_80B49BD0(EnInvadepoh* this) {
    EnInvadePohUnkStruct_324* temp_v0 = &this->unk_324;

    Animation_MorphToLoop(&this->skelAnime, &gRomaniWalkAnim, -10.0f);
    temp_v0->unk_26.x = 0;
    temp_v0->unk_26.y = 0;
    temp_v0->unk_26.z = 0;
    temp_v0->unk_30 = 0.1f;
    temp_v0->unk_2C = 0x320;
    this->actionFunc = EnInvadepoh_func_80B49C38;
}

void EnInvadepoh_func_80B49C38(EnInvadepoh* this, PlayState* play) {
    EnInvadepoh_func_80B44570(this);
    EnInvadepoh_func_80B44C24(this, play);
    EnInvadepoh_func_80B43E6C(this, 6, 0x7D0, 0x64);

    if ((this->unk_309 == 0) || (this->unk_309 + 1 == this->unk_308)) {
        if (this->unk_378 == 0) {
            s32 temp_v0_2 = func_800FE620(play);
            s32 pad;

            if (temp_v0_2 > 0) {
                temp_v0_2 = (gRegEditor->data[0xF] * -16.0f / temp_v0_2) - 0.5f;
                this->unk_378 = EnInvadepoh_func_80B45550(this, play, 6400.0f, temp_v0_2);
            }
        }
        this->actor.flags &= ~(ACTOR_FLAG_1 | ACTOR_FLAG_8);
    } else {
        this->unk_378 = 0;
        this->actor.flags |= (ACTOR_FLAG_1 | ACTOR_FLAG_8);
    }
    if (CHECK_FLAG_ALL(this->actor.flags, ACTOR_FLAG_40) &&
        (Animation_OnFrame(&this->skelAnime, 0.0f) || Animation_OnFrame(&this->skelAnime, 7.0f))) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_ROMANI_WALK);
    }
    if (this->unk_320 >= 0.9999f) {
        Actor_Kill(&this->actor);
    }
}

void EnInvadepoh_func_80B49DA0(EnInvadepoh* this) {
    this->unk_324.unk_30 = 0.08f;
    this->unk_324.unk_2C = 0x7D0;
    this->unk_370 = 0;
    Animation_MorphToLoop(&this->skelAnime, &gRomaniIdleAnim, -10.0f);
    this->actionFunc = EnInvadepoh_func_80B49DFC;
}

void EnInvadepoh_func_80B49DFC(EnInvadepoh* this, PlayState* play) {
    EnInvadePohUnkStruct_324* temp_s0 = &this->unk_324;
    Player* player = GET_PLAYER(play);
    s16 temp_v1;

    Math_StepToS(&this->unk_370, 0x7D0, 0x1F4);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, this->unk_370, 0x28);
    temp_v1 = Math_Vec3f_Pitch(&this->actor.focus.pos, &player->actor.focus.pos) * 0.85f;
    temp_s0->unk_26.x = CLAMP((s16)(temp_v1 - this->actor.shape.rot.x), -0xBB8, 0xBB8);

    temp_v1 = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
    temp_s0->unk_26.y = CLAMP((s16)(temp_v1 * 0.7f), -0x1F40, 0x1F40);

    if (Actor_TextboxIsClosing(&this->actor, play)) {
        if (this->actor.textId == 0x332D) { // It's almost time, Grasshopper...
            gSaveContext.save.saveInfo.weekEventReg[54] |= 0x10;
            this->actor.textId = 0x332E; // If you run out of arrows...
        }
        EnInvadepoh_func_80B49BD0(this);
    }
}

void EnInvadepoh_func_80B49F88(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;
    s32 pad;
    s32 sp38;

    if (Object_IsLoaded(&play->objectCtx, this->unk_2F4)) {
        sp38 = gSaveContext.save.time;
        this->actor.objBankIndex = this->unk_2F4;
        Actor_SetObjectDependency(play, &this->actor);
        EnInvadepoh_func_80B44F58();
        SkelAnime_InitFlex(play, &this->skelAnime, &gRomaniSkel, &gRomaniWalkAnim, this->unk_188, this->unk_212,
                           ROMANI_LIMB_MAX);
        EnInvadepoh_func_80B45C04(&this->unk_324, D_80B4EA90, 1, D_80B4EB00, 1, &gZeroVec3s, 0x64, 0.03f, 0.3f, 0.03f);
        EnInvadepoh_func_80B44540(this, play);
        EnInvadepoh_func_80B44570(this);
        EnInvadepoh_func_80B44C24(this, play);
        EnInvadepoh_func_80B43F0C(this);
        EnInvadepoh_func_80B4516C(this);
        if (gSaveContext.save.saveInfo.weekEventReg[21] & 0x20) {
            if (gSaveContext.save.saveInfo.weekEventReg[54] & 0x10) {
                this->actor.textId = 0x332E; // If you run out of arrows...
            } else {
                this->actor.textId = 0x332D; // It's almost time, Grasshopper...
            }
        } else {
            this->actor.textId = 0x332C; // ...It's almost time.
        }
        if ((sp38 >= CLOCK_TIME(18, 00)) || (sp38 < CLOCK_TIME(2, 00))) {
            this->actor.update = EnInvadepoh_func_80B4A168;
            this->actor.draw = NULL;
        } else if ((sp38 < CLOCK_TIME(6, 00)) && (sp38 >= CLOCK_TIME(2, 00)) && (sp38 < CLOCK_TIME(2, 15))) {
            this->actor.update = EnInvadepoh_func_80B4A1B8;
            this->actor.draw = EnInvadepoh_func_80B4E324;
            EnInvadepoh_func_80B49BD0(this);
        } else {
            Actor_Kill(&this->actor);
        }
    }
}

void EnInvadepoh_func_80B4A168(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    if ((gSaveContext.save.time < CLOCK_TIME(6, 00)) && (gSaveContext.save.time >= CLOCK_TIME(2, 00))) {
        this->actor.update = EnInvadepoh_func_80B4A1B8;
        this->actor.draw = EnInvadepoh_func_80B4E324;
        EnInvadepoh_func_80B49BD0(this);
    }
}

void EnInvadepoh_func_80B4A1B8(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;
    s32 sp2C = CHECK_FLAG_ALL(this->actor.flags, ACTOR_FLAG_40);
    s32 sp28 = Actor_ProcessTalkRequest(&this->actor, &play->state);

    if (sp28) {
        func_80151BB4(play, 5);
        EnInvadepoh_func_80B49DA0(this);
    }
    this->actionFunc(this, play);
    if (sp2C && (this->actor.update != NULL)) {
        SkelAnime_Update(&this->skelAnime);
        EnInvadepoh_func_80B45CE0(&this->unk_324);
        if ((this->actionFunc != EnInvadepoh_func_80B49DFC) && !sp28 && this->actor.isTargeted) {
            func_800B8614(&this->actor, play, 350.0f);
        }
        Collider_UpdateCylinder(&this->actor, &this->unk_2A0);
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->unk_2A0.base);
    }
}

void EnInvadepoh_func_80B4A2C0(EnInvadepoh* this) {
    EnInvadePohUnkStruct_324* temp_v0 = &this->unk_324;

    Animation_MorphToLoop(&this->skelAnime, &gRomaniIdleAnim, -10.0f);
    temp_v0->unk_26.x = 0;
    temp_v0->unk_26.y = 0;
    temp_v0->unk_26.z = 0;
    temp_v0->unk_30 = 0.1f;
    temp_v0->unk_2C = 0x5DC;

    this->unk_2F0 = Rand_S16Offset(200, 200);
    this->unk_304 = this->actor.shape.rot.y;
    this->actor.flags |= (ACTOR_FLAG_1 | ACTOR_FLAG_8);
    this->actionFunc = EnInvadepoh_func_80B4A350;
}

void EnInvadepoh_func_80B4A350(EnInvadepoh* this, PlayState* play) {
    s32 pad;
    EnInvadePohUnkStruct_324* sp30 = &this->unk_324;

    if ((play->gameplayFrames % 0x100) == 0) {
        Vec3f sp44;
        s16 sp42;

        Math_Vec3s_ToVec3f(&sp44, this->unk_30C);
        sp42 = Math_Vec3f_Yaw(&this->actor.world.pos, &sp44);
        this->unk_304 = Rand_S16Offset(-0x1F40, 0x3E80) + sp42;
        this->unk_370 = 0;
    }
    Math_StepToS(&this->unk_370, 0x7D0, 0x28);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->unk_304, 6, this->unk_370, 0x28);
    if (this->actor.xzDistToPlayer < 300.0f) {
        Player* player = GET_PLAYER(play);
        s16 temp_v1;

        temp_v1 = Math_Vec3f_Pitch(&this->actor.focus.pos, &player->actor.focus.pos) * 0.85f;
        sp30->unk_26.x = CLAMP((s16)(temp_v1 - this->actor.shape.rot.x), -0x9C4, 0x9C4);

        temp_v1 = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
        sp30->unk_26.y = CLAMP((s16)(temp_v1 * 0.7f), -0x1F40, 0x1F40);

        if ((play->gameplayFrames % 0x100) == 0) {
            sp30->unk_26.z = Rand_S16Offset(-0x5DC, 0xBB8);
        }
    } else {
        sp30->unk_26.x = 0;
        sp30->unk_26.y = 0;
        sp30->unk_26.z = 0;
    }
    if (this->unk_2F0 > 0) {
        this->unk_2F0--;
    } else {
        EnInvadepoh_func_80B4A570(this);
    }
}

void EnInvadepoh_func_80B4A570(EnInvadepoh* this) {
    EnInvadePohUnkStruct_324* temp_v0 = &this->unk_324;

    Animation_MorphToPlayOnce(&this->skelAnime, &gRomaniLookAroundAnim, -10.0f);
    temp_v0->unk_26.x = 0;
    temp_v0->unk_26.y = 0;
    temp_v0->unk_26.z = 0;
    temp_v0->unk_30 = 0.1f;
    temp_v0->unk_2C = 0x320;
    this->actor.flags |= (ACTOR_FLAG_1 | ACTOR_FLAG_8);
    this->actionFunc = EnInvadepoh_func_80B4A5E4;
}

void EnInvadepoh_func_80B4A5E4(EnInvadepoh* this, PlayState* play) {
    if (this->unk_29C != 0) {
        EnInvadepoh_func_80B4A2C0(this);
    }
}

void EnInvadepoh_func_80B4A614(EnInvadepoh* this) {
    EnInvadePohUnkStruct_324* temp_v0 = &this->unk_324;

    Animation_MorphToLoop(&this->skelAnime, &gRomaniWalkAnim, 0.0f);
    temp_v0->unk_26.x = 0;
    temp_v0->unk_26.y = 0;
    temp_v0->unk_26.z = 0;
    temp_v0->unk_30 = 0.1f;
    temp_v0->unk_2C = 0x320;
    this->actionFunc = EnInvadepoh_func_80B4A67C;
}

void EnInvadepoh_func_80B4A67C(EnInvadepoh* this, PlayState* play) {
    s32 pad;

    Math_StepToF(&this->actor.speed, 5.0f, 1.0f);
    if (EnInvadepoh_func_80B44B84(this, play, this->actor.speed, 50.0f) != 0) {
        EnInvadepoh_func_80B44640(this);
        this->unk_370 = 0x5DC;
        this->actor.speed *= 0.5f;
    } else {
        Math_StepToS(&this->unk_370, 0x190, 0x32);
    }
    EnInvadepoh_func_80B43E6C(this, 6, this->unk_370, 0x32);
    if (this->unk_309 == 0) {
        if (this->unk_378 == 0) {
            this->unk_378 = EnInvadepoh_func_80B45550(this, play, 6400.0f, -0xF);
        }
        this->actor.flags &= ~(ACTOR_FLAG_1 | ACTOR_FLAG_8);
    } else {
        this->unk_378 = 0;
        this->actor.flags |= (ACTOR_FLAG_1 | ACTOR_FLAG_8);
    }
    if (CHECK_FLAG_ALL(this->actor.flags, ACTOR_FLAG_40) &&
        (Animation_OnFrame(&this->skelAnime, 0.0f) || Animation_OnFrame(&this->skelAnime, 7.0f))) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_ROMANI_WALK);
    }
    if (this->unk_309 == this->unk_308) {
        EnInvadepoh_func_80B4A2C0(this);
    }
}

void EnInvadepoh_func_80B4A7C0(EnInvadepoh* this) {
    this->unk_324.unk_30 = 0.08f;
    this->unk_324.unk_2C = 0x7D0;
    this->unk_370 = 0;
    Animation_MorphToLoop(&this->skelAnime, &gRomaniIdleAnim, 0.0f);
    this->actionFunc = EnInvadepoh_func_80B4A81C;
}

void EnInvadepoh_func_80B4A81C(EnInvadepoh* this, PlayState* play) {
    EnInvadePohUnkStruct_324* temp_s0 = &this->unk_324;
    Player* player = GET_PLAYER(play);
    s16 temp_v1;

    Math_StepToS(&this->unk_370, 0x7D0, 0x1F4);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, this->unk_370, (s16)0x28);
    temp_v1 = Math_Vec3f_Pitch(&this->actor.focus.pos, &player->actor.focus.pos) * 0.85f;
    temp_s0->unk_26.x = CLAMP((s16)(temp_v1 - this->actor.shape.rot.x), -0xBB8, 0xBB8);

    temp_v1 = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
    temp_s0->unk_26.y = CLAMP((s16)(temp_v1 * 0.7f), -0x1F40, 0x1F40);
    if (Actor_TextboxIsClosing(&this->actor, play)) {
        if (this->actor.textId == 0x332D) { // It's almost time, Grasshopper
            gSaveContext.save.saveInfo.weekEventReg[54] |= 0x10;
            this->actor.textId = 0x332E; // If you run out of arrows...
        }
        if (this->unk_309 == this->unk_308) {
            EnInvadepoh_func_80B4A2C0(this);
        } else {
            EnInvadepoh_func_80B4A614(this);
        }
    }
}

void EnInvadepoh_func_80B4A9C8(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;
    s32 pad;

    if (Object_IsLoaded(&play->objectCtx, this->unk_2F4)) {
        s32 sp38 = gSaveContext.save.time;

        this->actor.objBankIndex = this->unk_2F4;
        Actor_SetObjectDependency(play, &this->actor);
        EnInvadepoh_func_80B44F58();
        SkelAnime_InitFlex(play, &this->skelAnime, &gRomaniSkel, &gRomaniWalkAnim, this->unk_188, this->unk_212,
                           ROMANI_LIMB_MAX);
        EnInvadepoh_func_80B45C04(&this->unk_324, D_80B4EA90, 1, D_80B4EB00, 1, &gZeroVec3s, 100, 0.03f, 0.3f, 0.03f);
        EnInvadepoh_func_80B44620(this, play2);
        if ((sp38 < CLOCK_TIME(2, 15)) || (sp38 >= CLOCK_TIME(6, 00))) {
            this->unk_309 = 0;
            this->actor.update = EnInvadepoh_func_80B4AB8C;
        } else {
            this->unk_309 = this->unk_308;
            this->actor.update = EnInvadepoh_func_80B4ABDC;
            this->actor.draw = EnInvadepoh_func_80B4E324;
            EnInvadepoh_func_80B4A2C0(this);
        }
        EnInvadepoh_func_80B4407C(this, this->unk_309);
        EnInvadepoh_func_80B43F0C(this);
        func_800B4AEC(play, &this->actor, 50.0f);
        EnInvadepoh_func_80B4516C(this);
        if (gSaveContext.save.saveInfo.weekEventReg[21] & 0x20) {
            if (gSaveContext.save.saveInfo.weekEventReg[54] & 0x10) {
                this->actor.textId = 0x332E; // If you run out of arrows...
            } else {
                this->actor.textId = 0x332D; // It's almost time, Grasshopper...
            }
        } else {
            this->actor.textId = 0x332C; // ...It's almost time.
        }
    }
}

void EnInvadepoh_func_80B4AB8C(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    if ((gSaveContext.save.time < CLOCK_TIME(6, 00)) && (gSaveContext.save.time >= CLOCK_TIME(2, 15))) {
        this->actor.update = EnInvadepoh_func_80B4ABDC;
        this->actor.draw = EnInvadepoh_func_80B4E324;
        EnInvadepoh_func_80B4A614(this);
    }
}

void EnInvadepoh_func_80B4ABDC(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;
    s32 sp2C = CHECK_FLAG_ALL(this->actor.flags, ACTOR_FLAG_40);
    s32 sp28 = Actor_ProcessTalkRequest(&this->actor, &play->state);

    if (sp28) {
        func_80151BB4(play, 5);
        EnInvadepoh_func_80B4A7C0(this);
    }
    this->actionFunc(this, play);
    if (sp2C) {
        this->unk_29C = SkelAnime_Update(&this->skelAnime);
        EnInvadepoh_func_80B45CE0(&this->unk_324);
        if ((this->actionFunc != EnInvadepoh_func_80B4A81C) && !sp28 && this->actor.isTargeted) {
            func_800B8614(&this->actor, play, 100.0f);
        }
        Collider_UpdateCylinder(&this->actor, &this->unk_2A0);
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->unk_2A0.base);
    }
}

void EnInvadepoh_func_80B4ACDC(EnInvadepoh* this) {
    this->actionFunc = EnInvadepoh_func_80B4ACF0;
}

void EnInvadepoh_func_80B4ACF0(EnInvadepoh* this, PlayState* play) {
    if (gSaveContext.save.saveInfo.weekEventReg[22] & 1) {
        this->actor.draw = EnInvadepoh_func_80B4E324;
        this->actor.flags |= (ACTOR_FLAG_1 | ACTOR_FLAG_8);
        EnInvadepoh_func_80B4AD3C(this);
    }
}

void EnInvadepoh_func_80B4AD3C(EnInvadepoh* this) {
    this->actor.flags |= ACTOR_FLAG_10000;
    this->actionFunc = EnInvadepoh_func_80B4AD60;
}

void EnInvadepoh_func_80B4AD60(EnInvadepoh* this, PlayState* play) {
    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        EnInvadepoh_func_80B4560C(this, play, 0x3331); // We did it...We won.
        EnInvadepoh_func_80B4ADB8(this);
    } else {
        func_800B8614(&this->actor, play, 2000.0f);
    }
}

void EnInvadepoh_func_80B4ADB8(EnInvadepoh* this) {
    this->actionFunc = EnInvadepoh_func_80B4ADCC;
}

void EnInvadepoh_func_80B4ADCC(EnInvadepoh* this, PlayState* play) {
    if ((Message_GetState(&play->msgCtx) == 5) && Message_ShouldAdvance(play)) {
        if (this->unk_376 == 0x3331) { // We did it...We won.
            if (gSaveContext.save.saveInfo.weekEventReg[22] & 2) {
                EnInvadepoh_func_80B4560C(this, play, 0x3334); // I have to get back to bed...
                func_80151BB4(play, 0x1D);
                func_80151BB4(play, 5);
            } else {
                EnInvadepoh_func_80B4560C(this, play, 0x3333); // Here's Romani's thanks
            }
        } else if (this->unk_376 == 0x3333) { // Here's Romani's thanks
            EnInvadepoh_func_80B4AEC0(this);
        } else if (this->unk_376 == 0x3334) { // I have to get back to bed...
            Message_CloseTextbox(play);
            EnInvadepoh_func_80B4B024(this);
        }
    }
}

void EnInvadepoh_func_80B4AEC0(EnInvadepoh* this) {
    this->unk_2F0 = 2;
    this->actionFunc = EnInvadepoh_func_80B4AEDC;
}

void EnInvadepoh_func_80B4AEDC(EnInvadepoh* this, PlayState* play) {
    if (this->unk_2F0 > 0) {
        this->unk_2F0--;
        if (this->unk_2F0 == 0) {
            Message_CloseTextbox(play);
        }
    }
    if (Actor_HasParent(&this->actor, play)) {
        this->actor.parent = NULL;
        gSaveContext.save.saveInfo.weekEventReg[22] |= 2;
        EnInvadepoh_func_80B4AF80(this);
    } else {
        Actor_OfferGetItem(&this->actor, play, 0x60, 2000.0f, 2000.0f);
    }
}

void EnInvadepoh_func_80B4AF80(EnInvadepoh* this) {
    this->actionFunc = EnInvadepoh_func_80B4AF94;
}

void EnInvadepoh_func_80B4AF94(EnInvadepoh* this, PlayState* play) {
    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        EnInvadepoh_func_80B4560C(this, play, 0x3334); // I have to get back to bed..
        func_80151BB4(play, 0x1E);
        func_80151BB4(play, 0x1D);
        func_80151BB4(play, 5);
        EnInvadepoh_func_80B4ADB8(this);
    } else {
        func_800B85E0(&this->actor, play, 2000.0f, PLAYER_IA_MINUS1);
    }
}

void EnInvadepoh_func_80B4B024(EnInvadepoh* this) {
    this->actor.flags &= ~(ACTOR_FLAG_1 | ACTOR_FLAG_8);
    this->actionFunc = EnInvadepoh_func_80B4B048;
}

void EnInvadepoh_func_80B4B048(EnInvadepoh* this, PlayState* play) {
    if (play->msgCtx.unk120B1 == 0) {
        if (play->msgCtx.msgMode == 0) {
            D_80B4E998 = 1;
        } else if ((Message_GetState(&play->msgCtx) == 6) || (Message_GetState(&play->msgCtx) == 5)) {
            D_80B4E998 = 1;
        }
    }
}

void EnInvadepoh_func_80B4B0C4(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;
    EnInvadePohUnkStruct_324* temp_s0 = &this->unk_324;

    if (Object_IsLoaded(&play2->objectCtx, this->unk_2F4)) {
        this->actor.objBankIndex = this->unk_2F4;
        Actor_SetObjectDependency(play, &this->actor);
        EnInvadepoh_func_80B44F58();
        this->actor.update = EnInvadepoh_func_80B4B218;
        SkelAnime_InitFlex(play, &this->skelAnime, &gRomaniSkel, &gRomaniWalkAnim, this->unk_188, this->unk_212,
                           ROMANI_LIMB_MAX);
        Animation_MorphToLoop(&this->skelAnime, &gRomaniIdleAnim, 0.0f);
        EnInvadepoh_func_80B45C04(&this->unk_324, D_80B4EA90, 1, D_80B4EB00, 3, &gZeroVec3s, 0x7D0, 0.08f, 0.3f, 0.03f);
        temp_s0->unk_30 = 0.08f;
        temp_s0->unk_2C = 0x7D0;
        func_800B4AEC(play, &this->actor, 50.0f);
        EnInvadepoh_func_80B4516C(this);
        EnInvadepoh_func_80B4ACDC(this);
    }
}

void EnInvadepoh_func_80B4B218(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;
    EnInvadePohUnkStruct_324* temp_s0 = &this->unk_324;
    s32 sp38 = CHECK_FLAG_ALL(this->actor.flags, ACTOR_FLAG_40);

    this->actionFunc(this, play);

    if (sp38 && (this->actor.update != NULL)) {
        Player* player;
        s16 temp_v1;

        SkelAnime_Update(&this->skelAnime);
        player = GET_PLAYER(play);
        Math_StepToS(&this->unk_370, 0x7D0, 0x28);
        Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 6, this->unk_370, 40);
        temp_v1 = Math_Vec3f_Pitch(&this->actor.focus.pos, &player->actor.focus.pos) * 0.9f;
        temp_s0->unk_26.x = CLAMP((s16)(temp_v1 - this->actor.shape.rot.x), -0xBB8, 0xBB8);

        temp_v1 = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
        temp_s0->unk_26.y = CLAMP((s16)(temp_v1 * 0.7f), -0x1F40, 0x1F40);
        EnInvadepoh_func_80B45CE0(&this->unk_324);
        Collider_UpdateCylinder(&this->actor, &this->unk_2A0);
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->unk_2A0.base);
    }
}

void EnInvadepoh_func_80B4B3DC(EnInvadepoh* this) {
    s32 pad;

    if (Animation_OnFrame(&this->skelAnime, 1.0f) || Animation_OnFrame(&this->skelAnime, 7.0f)) {
        Actor_PlaySfx(&this->actor, NA_SE_EV_MONKEY_WALK);
    }
}

void EnInvadepoh_func_80B4B430(EnInvadepoh* this) {
    Animation_MorphToLoop(&this->skelAnime, &gDogWalkAnim, -6.0f);
    this->unk_2F0 = Rand_S16Offset(50, 80);
    this->actionFunc = EnInvadepoh_func_80B4B484;
}

void EnInvadepoh_func_80B4B484(EnInvadepoh* this, PlayState* play) {
    Math_StepToF(&this->actor.speed, 1.1f, 0.5f);
    if (EnInvadepoh_func_80B44C80(this, play)) {
        EnInvadepoh_func_80B44690(this);
    }
    EnInvadepoh_func_80B4B3DC(this);
    if (this->unk_3BC >= 0) {
        this->unk_2F0 = 0;
    }
    if (this->unk_2F0 > 0) {
        this->unk_2F0--;
    } else {
        EnInvadepoh_func_80B4B510(this);
    }
}

void EnInvadepoh_func_80B4B510(EnInvadepoh* this) {
    Animation_MorphToLoop(&this->skelAnime, &gDogRunAnim, -6.0f);
    this->unk_2F0 = Rand_S16Offset(50, 200);
    this->actionFunc = EnInvadepoh_func_80B4B564;
}

void EnInvadepoh_func_80B4B564(EnInvadepoh* this, PlayState* play) {
    Math_StepToF(&this->actor.speed, 3.8f, 0.45f);
    if (this->unk_3BC >= 0) {
        f32 temp_fv0;
        Vec3f sp28;

        Math_Vec3s_ToVec3f(&sp28, &this->unk_30C[this->unk_3BC]);
        temp_fv0 = Math3D_Vec3fDistSq(&this->actor.world.pos, &sp28);
        if (temp_fv0 < SQ(80.0f)) {
            this->actor.speed *= 0.85f;
        } else if (temp_fv0 < SQ(150.0f)) {
            this->actor.speed *= 0.93f;
        } else if (temp_fv0 < SQ(250.0f)) {
            this->actor.speed *= 0.96f;
        }
        if ((this->unk_309 == this->unk_3BC) || (temp_fv0 < SQ(50.0f))) {
            this->unk_2F0 = 0;
        }
    }
    EnInvadepoh_func_80B4B3DC(this);
    if (EnInvadepoh_func_80B44C80(this, play)) {
        EnInvadepoh_func_80B44690(this);
    }
    if (this->unk_2F0 > 0) {
        this->unk_2F0--;
    } else if (this->unk_3BC >= 0) {
        if ((D_80B50348 == 0) && (Rand_ZeroOne() < 0.4f)) {
            Actor_PlaySfx(&this->actor, NA_SE_EV_SMALL_DOG_GROAN);
        }
        EnInvadepoh_func_80B4B724(this);
    } else {
        EnInvadepoh_func_80B4B430(this);
    }
}

void EnInvadepoh_func_80B4B724(EnInvadepoh* this) {
    Animation_MorphToPlayOnce(&this->skelAnime, &gDogBarkAnim, -6.0f);
    this->actionFunc = EnInvadepoh_func_80B4B768;
}

void EnInvadepoh_func_80B4B768(EnInvadepoh* this, PlayState* play) {
    s32 pad;

    Math_StepToF(&this->actor.speed, 0.0f, 1.0f);
    Math_SmoothStepToS(&this->actor.world.rot.y, Actor_WorldYawTowardActor(&this->actor, &D_80B5040C->actor), 5, 0x1388,
                       (s16)0x64);
    EnInvadepoh_func_80B44E90(this, play);
    if (Animation_OnFrame(&this->skelAnime, 13.0f) || Animation_OnFrame(&this->skelAnime, 19.0f)) {
        Actor_PlaySfx(&this->actor, NA_SE_EV_SMALL_DOG_ANG_BARK);
    }
    if (this->unk_29C != 0) {
        EnInvadepoh_func_80B4B510(this);
    }
}

void EnInvadepoh_func_80B4B820(EnInvadepoh* this) {
    Animation_MorphToPlayOnce(&this->skelAnime, &gDogJumpAnim, -6.0f);
    this->actionFunc = EnInvadepoh_func_80B4B864;
}

void EnInvadepoh_func_80B4B864(EnInvadepoh* this, PlayState* play) {
    Math_StepToF(&this->actor.speed, 0.5f, 1.0f);
    EnInvadepoh_func_80B44E90(this, play);
    if (this->unk_29C != 0) {
        EnInvadepoh_func_80B4B510(this);
    }
}

void EnInvadepoh_func_80B4B8BC(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    if (Object_IsLoaded(&play->objectCtx, this->unk_2F4) && 1) {
        this->actor.objBankIndex = this->unk_2F4;
        Actor_SetObjectDependency(play, &this->actor);
        SkelAnime_InitFlex(play, &this->skelAnime, &gDogSkel, &gDogWalkAnim, this->unk_188, this->unk_212,
                           DOG_LIMB_MAX);
        EnInvadepoh_func_80B45C04(&this->unk_324, NULL, 0, NULL, 0, &gZeroVec3s, 0xBB8, 0.1f, 0.0f, 0.0f);
        EnInvadepoh_func_80B44664(this, play);
        EnInvadepoh_func_80B4407C(this, 0);
        func_800B4AEC(play, &this->actor, 50.0f);
        EnInvadepoh_func_80B4516C(this);
        Math_Vec3f_Copy(&this->unk_314, &this->actor.world.pos);
        if (D_80B4E940 == 2) {
            this->actor.update = EnInvadepoh_func_80B4BA84;
            this->actor.draw = EnInvadepoh_func_80B4E660;
            this->actor.flags |= ACTOR_FLAG_1;
            EnInvadepoh_func_80B4B430(this);
        } else if (D_80B4E940 == 1) {
            this->actor.update = EnInvadepoh_func_80B4BA30;
        } else {
            Actor_Kill(&this->actor);
        }
    }
}

void EnInvadepoh_func_80B4BA30(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    if (D_80B4E940 == 2) {
        this->actor.update = EnInvadepoh_func_80B4BA84;
        this->actor.draw = EnInvadepoh_func_80B4E660;
        this->actor.flags |= ACTOR_FLAG_1;
        EnInvadepoh_func_80B4B430(this);
    }
}

void EnInvadepoh_func_80B4BA84(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;
    s32 sp34 = CHECK_FLAG_ALL(this->actor.flags, ACTOR_FLAG_40);
    s32 temp;
    s32 sp2C;
    s32 temp_v1_2;
    s32 var_v0;

    D_80B5040C = EnInvadepoh_func_80B458D8();
    if (D_80B5040C == NULL) {
        temp = (this->unk_3BC < 0) ^ 1;
        this->unk_3BC = -1;
        if (temp) {
            EnInvadepoh_func_80B4B820(this);
        }
    } else {
        sp2C = this->unk_3BC;
        this->unk_3BC = EnInvadepoh_func_80B44234(this, &D_80B5040C->actor.world.pos);
        if (sp2C != this->unk_3BC) {
            var_v0 = this->unk_3BC - this->unk_309;
            if (var_v0 < 0) {
                var_v0 += this->unk_308;
            }
            temp_v1_2 = this->unk_308 >> 1;
            if (temp_v1_2 < var_v0) {
                this->unk_30A = -1;
            } else if (var_v0 < temp_v1_2) {
                this->unk_30A = 1;
            }
        }
    }
    this->actionFunc(this, play);
    this->unk_29C = SkelAnime_Update(&this->skelAnime);
    if (sp34 && (this->actor.update != NULL)) {
        EnInvadepoh_func_80B45CE0(&this->unk_324);
        Collider_UpdateCylinder(&this->actor, &this->unk_2A0);
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->unk_2A0.base);
    }
}

void EnInvadepoh_func_80B4BBE0(EnInvadepoh* this) {
    EnInvadePohUnkStruct_324* temp_v0 = &this->unk_324;

    Animation_MorphToLoop(&this->skelAnime, &gCremiaWalkAnim, -6.0f);
    temp_v0->unk_26.x = 0;
    temp_v0->unk_26.y = 0;
    temp_v0->unk_26.z = 0;
    temp_v0->unk_30 = 0.1f;
    temp_v0->unk_2C = 0x320;

    this->unk_370 = 0;
    this->actionFunc = EnInvadepoh_func_80B4BC4C;
}

void EnInvadepoh_func_80B4BC4C(EnInvadepoh* this, PlayState* play) {
    EnInvadePohUnkStruct_324* temp_s0 = &this->unk_324;
    EnInvadepoh* sp50 = D_80B503F4;
    s32 pad;
    s32 sp48;
    s32 pad2;
    s16 sp42;
    s16 sp40;
    s16 temp_v1;

    if (sp50 != NULL) {
        if (sp50->unk_309 == 0) {
            this->unk_2F8 = 40.0f;
            this->unk_304 = -0x8000;
            this->actor.flags &= ~(ACTOR_FLAG_1 | ACTOR_FLAG_8);
        } else if (sp50->unk_309 < (sp50->unk_308 - 1)) {
            this->unk_2F8 = 40.0f;
            Math_ScaledStepToS(&this->unk_304, -0x4800, 0xC8);
            this->actor.flags |= (ACTOR_FLAG_1 | ACTOR_FLAG_8);
        } else {
            Math_StepToF(&this->unk_2F8, 5.0f, 3.0f);
            Math_ScaledStepToS(&this->unk_304, -0x8000, 0x12C);
            this->actor.flags &= ~(ACTOR_FLAG_1 | ACTOR_FLAG_8);
        }
        sp42 = this->unk_304 + sp50->actor.world.rot.y;
        this->actor.world.pos.x = (Math_SinS(sp42) * this->unk_2F8) + sp50->actor.world.pos.x;
        this->actor.world.pos.y = sp50->actor.world.pos.y;
        this->actor.world.pos.z = (Math_CosS(sp42) * this->unk_2F8) + sp50->actor.world.pos.z;
        func_800B4AEC(play, &this->actor, 50.0f);
        EnInvadepoh_func_80B4516C(this);
        Math_StepToS(&this->unk_370, 0xBB8, 0x1F5);
        if (Math3D_Vec3fDistSq(&this->actor.prevPos, &this->actor.world.pos) > SQ(0.01f)) {
            Math_SmoothStepToS(&this->actor.shape.rot.y, Math_Vec3f_Yaw(&this->actor.prevPos, &this->actor.world.pos),
                               3, this->unk_370, 0x1F4);
        }
        sp48 = (play->gameplayFrames + 20) % 0x80;
        if (sp48 & 0x40) {
            sp40 = Math_Vec3f_Yaw(&this->actor.world.pos, &sp50->actor.world.pos);
            if (sp48 == 0x40) {
                this->unk_370 = 0;
            }
            Math_StepToS(&this->unk_370, 0x7D0, 0x28);
            Math_SmoothStepToS(&this->actor.shape.rot.y, sp40, 6, this->unk_370, 0x28);
            temp_v1 = Math_Vec3f_Pitch(&this->actor.focus.pos, &sp50->actor.focus.pos) * 0.85f;
            temp_s0->unk_26.x = CLAMP((s16)(temp_v1 - this->actor.shape.rot.x), -0xBB8, 0xBB8);

            temp_v1 = sp40 - this->actor.shape.rot.y;
            temp_s0->unk_26.y = CLAMP((s16)(temp_v1 * 0.7f), -0x1F40, 0x1F40);
        }
    }

    if (CHECK_FLAG_ALL(this->actor.flags, ACTOR_FLAG_40) &&
        (Animation_OnFrame(&this->skelAnime, 0.0f) || Animation_OnFrame(&this->skelAnime, 12.0f))) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_ROMANI_WALK);
    }
    if (gSaveContext.save.time > CLOCK_TIME(20, 15)) {
        Actor_Kill(&this->actor);
    } else if ((sp50 != NULL) && (sp50->actionFunc == EnInvadepoh_func_80B4CB0C)) {
        EnInvadepoh_func_80B4C1BC(this);
    }
}

void EnInvadepoh_func_80B4BFFC(EnInvadepoh* this) {
    this->unk_324.unk_30 = 0.08f;
    this->unk_324.unk_2C = 0x7D0;
    Animation_MorphToLoop(&this->skelAnime, &gCremiaIdleAnim, -6.0f);
    this->unk_370 = 0;
    this->actionFunc = EnInvadepoh_func_80B4C058;
}

void EnInvadepoh_func_80B4C058(EnInvadepoh* this, PlayState* play) {
    EnInvadePohUnkStruct_324* temp_s0 = &this->unk_324;
    Player* sp28 = GET_PLAYER(play);
    s16 temp_v1;

    Math_StepToS(&this->unk_370, 0x9C4, 0x1C2);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, this->unk_370, 0x28);
    temp_v1 = Math_Vec3f_Pitch(&this->actor.focus.pos, &sp28->actor.focus.pos) * 0.85f;
    temp_s0->unk_26.x = CLAMP((s16)(temp_v1 - this->actor.shape.rot.x), -0xBB8, 0xBB8);

    temp_v1 = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
    temp_s0->unk_26.y = CLAMP((s16)(temp_v1 * 0.7f), -0x1F40, 0x1F40);
    if (Actor_TextboxIsClosing(&this->actor, play)) {
        EnInvadepoh_func_80B4BBE0(this);
    }
}

void EnInvadepoh_func_80B4C1BC(EnInvadepoh* this) {
    this->unk_324.unk_30 = 0.08f;
    this->unk_324.unk_2C = 0x7D0;
    Animation_MorphToLoop(&this->skelAnime, &gCremiaIdleAnim, -6.0f);
    this->unk_370 = 0;
    this->actionFunc = EnInvadepoh_func_80B4C218;
}

void EnInvadepoh_func_80B4C218(EnInvadepoh* this, PlayState* play) {
    EnInvadePohUnkStruct_324* temp_s0 = &this->unk_324;
    Player* sp28 = GET_PLAYER(play);
    s16 temp_v1;

    Math_StepToS(&this->unk_370, 0x7D0, 0xC8);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 6, this->unk_370, 0x28);
    temp_v1 = Math_Vec3f_Pitch(&this->actor.focus.pos, &sp28->actor.focus.pos) * 0.85f;
    temp_s0->unk_26.x = CLAMP((s16)(temp_v1 - this->actor.shape.rot.x), -0xBB8, 0xBB8);

    temp_v1 = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
    temp_s0->unk_26.y = CLAMP((s16)(temp_v1 * 0.7f), -0x1F40, 0x1F40);
    if (D_80B503F4 == NULL) {
        EnInvadepoh_func_80B4BBE0(this);
    } else if ((D_80B503F4 != NULL) && (D_80B503F4->actionFunc != EnInvadepoh_func_80B4CB0C)) {
        EnInvadepoh_func_80B4BBE0(this);
    }
}

void EnInvadepoh_func_80B4C3A0(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;
    s32 pad;

    if (Object_IsLoaded(&play2->objectCtx, this->unk_2F4)) {
        s32 sp38 = gSaveContext.save.time;

        this->actor.objBankIndex = this->unk_2F4;
        Actor_SetObjectDependency(play, &this->actor);
        EnInvadepoh_func_80B44FEC();
        SkelAnime_InitFlex(play, &this->skelAnime, &gCremiaSkel, &gCremiaWalkAnim, this->unk_188, this->unk_212,
                           CREMIA_LIMB_MAX);
        EnInvadepoh_func_80B45C04(&this->unk_324, D_80B4EBDC, 1, D_80B4EC08, 0, &gZeroVec3s, 100, 0.03f, 0.3f, 0.03f);
        this->actor.textId = 0x33CD; // Good night... See you...tomorrow...OK?
        if (sp38 < CLOCK_TIME(20, 01) + 30) {
            this->unk_304 = -0x8000;
            this->unk_2F8 = 40.0f;
        } else if (sp38 > CLOCK_TIME(20, 14) + 1) {
            this->unk_304 = -0x4800;
            this->unk_2F8 = 20.0f;
        } else {
            this->unk_304 = -0x8000;
            this->unk_2F8 = 40.0f;
        }
        if ((CLOCK_TIME(6, 00) <= sp38) && (sp38 < CLOCK_TIME(20, 00) + 30)) {
            this->actor.update = EnInvadepoh_func_80B4C568;
            this->actor.draw = NULL;
        } else if ((CLOCK_TIME(20, 00) + 30 <= sp38) && (sp38 < CLOCK_TIME(20, 15))) {
            this->actor.update = EnInvadepoh_func_80B4C5C0;
            this->actor.draw = EnInvadepoh_func_80B4E7BC;
            EnInvadepoh_func_80B4BBE0(this);
        } else {
            Actor_Kill(&this->actor);
        }
    }
}

void EnInvadepoh_func_80B4C568(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    if ((gSaveContext.save.time >= CLOCK_TIME(20, 00) + 30) && (gSaveContext.save.time < CLOCK_TIME(20, 15))) {
        this->actor.update = EnInvadepoh_func_80B4C5C0;
        this->actor.draw = EnInvadepoh_func_80B4E7BC;
        EnInvadepoh_func_80B4BBE0(this);
    }
}

void EnInvadepoh_func_80B4C5C0(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;
    s32 sp2C = CHECK_FLAG_ALL(this->actor.flags, ACTOR_FLAG_40);
    s32 sp28 = Actor_ProcessTalkRequest(&this->actor, &play->state);

    if (sp28) {
        func_80151BB4(play, 6);
        EnInvadepoh_func_80B4BFFC(this);
    }
    this->actionFunc(this, play2);
    if (sp2C && (this->actor.update != NULL)) {
        SkelAnime_Update(&this->skelAnime);
        EnInvadepoh_func_80B45CE0(&this->unk_324);
        if ((this->actionFunc != EnInvadepoh_func_80B4C058) && !sp28 && this->actor.isTargeted) {
            func_800B8614(&this->actor, play, 350.0f);
        }
        Collider_UpdateCylinder(&this->actor, &this->unk_2A0);
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->unk_2A0.base);
    }
}

void EnInvadepoh_func_80B4C6C8(EnInvadepoh* this) {
    EnInvadePohUnkStruct_324* temp_v0 = &this->unk_324;

    Animation_MorphToLoop(&this->skelAnime, &gRomaniWalkAnim, -10.0f);
    temp_v0->unk_26.x = 0;
    temp_v0->unk_26.y = 0;
    temp_v0->unk_26.z = 0;
    temp_v0->unk_30 = 0.1f;
    temp_v0->unk_2C = 0x320;
    this->actionFunc = EnInvadepoh_func_80B4C730;
}

void EnInvadepoh_func_80B4C730(EnInvadepoh* this, PlayState* play) {
    EnInvadePohUnkStruct_324* temp_s0 = &this->unk_324;
    EnInvadepoh* sp68 = D_80B503F8;
    s32 var_a2;
    s32 sp60;
    s32 pad;
    s16 temp_v2;
    Vec3f sp4C;
    Vec3f sp40;

    EnInvadepoh_func_80B44700(this);
    EnInvadepoh_func_80B44EFC(this, play);
    EnInvadepoh_func_80B43E6C(this, 6, 0x7D0, 0x64);

    var_a2 = (this->unk_309 < this->unk_308) ? this->unk_309 : this->unk_308 - 1;

    Math_Vec3s_ToVec3f(&sp4C, &this->unk_30C[var_a2]);
    Math_Vec3s_ToVec3f(&sp40, &this->unk_30C[var_a2 + 1]);
    Math_SmoothStepToS(&this->actor.world.rot.y, Math_Vec3f_Yaw(&sp4C, &sp40) + 0, 5, 0x7D0, 100);
    if ((this->unk_309 == 0) || (this->unk_309 + 1 == this->unk_308)) {
        if (this->unk_378 == 0) {
            s32 temp_v0_2 = func_800FE620(play);

            if (temp_v0_2 > 0) {
                temp_v0_2 = (gRegEditor->data[0xF] * -23.0f / temp_v0_2) - 0.5f;
                this->unk_378 = EnInvadepoh_func_80B45550(this, play, 6400.0f, temp_v0_2);
            }
        }
        this->actor.flags &= ~(ACTOR_FLAG_1 | ACTOR_FLAG_8);
    } else {
        this->unk_378 = 0;
        this->actor.flags |= (ACTOR_FLAG_1 | ACTOR_FLAG_8);
    }
    sp60 = play->gameplayFrames % 0x80;
    if (sp60 & 0x40) {
        s16 sp3A = Math_Vec3f_Yaw(&this->actor.world.pos, &sp68->actor.world.pos);
        s16 temp_v1;
        if (sp60 == 0x40) {
            this->unk_370 = 0;
        }
        Math_StepToS(&this->unk_370, 0x7D0, 0x28);
        Math_SmoothStepToS(&this->actor.shape.rot.y, sp3A, 6, this->unk_370, 40);
        temp_v1 = Math_Vec3f_Pitch(&this->actor.focus.pos, &sp68->actor.focus.pos) * 0.85f;
        temp_s0->unk_26.x = CLAMP((s16)(temp_v1 - this->actor.shape.rot.x), -0xBB8, 0xBB8);

        temp_v1 = sp3A - this->actor.shape.rot.y;
        temp_s0->unk_26.y = CLAMP((s16)(temp_v1 * 0.7f), -0x1F40, 0x1F40);
    }
    if (CHECK_FLAG_ALL(this->actor.flags, ACTOR_FLAG_40) &&
        (Animation_OnFrame(&this->skelAnime, 0.0f) || Animation_OnFrame(&this->skelAnime, 7.0f))) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_ROMANI_WALK);
    }
    if (this->unk_320 >= 0.9999f) {
        Actor_Kill(&this->actor);
    } else if ((sp68 != NULL) && (sp68->actionFunc == EnInvadepoh_func_80B4C058)) {
        EnInvadepoh_func_80B4CC70(this);
    }
}

void EnInvadepoh_func_80B4CAB0(EnInvadepoh* this) {
    this->unk_324.unk_30 = 0.08f;
    this->unk_324.unk_2C = 0xFA0;
    Animation_MorphToLoop(&this->skelAnime, &gRomaniIdleAnim, -10.0f);
    this->unk_370 = 0;
    this->actionFunc = EnInvadepoh_func_80B4CB0C;
}

void EnInvadepoh_func_80B4CB0C(EnInvadepoh* this, PlayState* play) {
    EnInvadePohUnkStruct_324* temp_s0 = &this->unk_324;
    Player* player = GET_PLAYER(play);
    s16 temp_v1;

    Math_StepToS(&this->unk_370, 0xBB8, 0x1F4);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 6, this->unk_370, 40);
    temp_v1 = Math_Vec3f_Pitch(&this->actor.focus.pos, &player->actor.focus.pos) * 0.85f;
    temp_s0->unk_26.x = CLAMP((s16)(temp_v1 - this->actor.shape.rot.x), -0xBB8, 0xBB8);

    temp_v1 = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
    temp_s0->unk_26.y = CLAMP((s16)(temp_v1 * 0.7f), -0x1F40, 0x1F40);
    if (Actor_TextboxIsClosing(&this->actor, play)) {
        EnInvadepoh_func_80B4C6C8(this);
    }
}

void EnInvadepoh_func_80B4CC70(EnInvadepoh* this) {
    this->unk_324.unk_30 = 0.08f;
    this->unk_324.unk_2C = 0x7D0;
    Animation_MorphToLoop(&this->skelAnime, &gRomaniIdleAnim, -10.0f);
    this->unk_370 = 0;
    this->actionFunc = EnInvadepoh_func_80B4CCCC;
}

void EnInvadepoh_func_80B4CCCC(EnInvadepoh* this, PlayState* play) {
    EnInvadePohUnkStruct_324* temp_s0 = &this->unk_324;
    Player* player = GET_PLAYER(play);
    s16 temp_v1;

    Math_StepToS(&this->unk_370, 0x7D0, 0xC8);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 6, this->unk_370, 40);
    temp_v1 = Math_Vec3f_Pitch(&this->actor.focus.pos, &player->actor.focus.pos) * 0.85f;
    temp_s0->unk_26.x = CLAMP((s16)(temp_v1 - this->actor.shape.rot.x), -0xBB8, 0xBB8);

    temp_v1 = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
    temp_s0->unk_26.y = CLAMP((s16)(temp_v1 * 0.7f), -0x1F40, 0x1F40);
    if (D_80B503F8 == NULL) {
        EnInvadepoh_func_80B4C6C8(this);
    } else if ((D_80B503F8 != NULL) && (D_80B503F8->actionFunc != EnInvadepoh_func_80B4C058)) {
        EnInvadepoh_func_80B4C6C8(this);
    }
}

void EnInvadepoh_func_80B4CE54(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;
    s32 pad;

    if (Object_IsLoaded(&play2->objectCtx, this->unk_2F4)) {
        s32 sp38 = gSaveContext.save.time;

        this->actor.objBankIndex = this->unk_2F4;
        Actor_SetObjectDependency(play, &this->actor);
        EnInvadepoh_func_80B44F58();
        SkelAnime_InitFlex(play, &this->skelAnime, &gRomaniSkel, &gRomaniWalkAnim, this->unk_188, this->unk_212,
                           ROMANI_LIMB_MAX);
        EnInvadepoh_func_80B45C04(&this->unk_324, D_80B4EA90, 1, D_80B4EB00, 3, &gZeroVec3s, 100, 0.03f, 0.3f, 0.03f);
        EnInvadepoh_func_80B446D0(this, play);
        this->actor.world.rot.y = this->actor.shape.rot.y;
        EnInvadepoh_func_80B44700(this);
        EnInvadepoh_func_80B44EFC(this, play);
        EnInvadepoh_func_80B43F0C(this);
        EnInvadepoh_func_80B4516C(this);
        this->actor.textId = 0x33CE; // See you tomorrow!
        if ((sp38 >= CLOCK_TIME(6, 00)) && (sp38 < CLOCK_TIME(20, 00))) {
            this->actor.update = EnInvadepoh_func_80B4CFFC;
            this->actor.draw = NULL;
        } else if ((sp38 >= CLOCK_TIME(20, 00)) && (sp38 < CLOCK_TIME(20, 14) + 15)) {
            this->actor.update = EnInvadepoh_func_80B4D054;
            this->actor.draw = EnInvadepoh_func_80B4E324;
            EnInvadepoh_func_80B4C6C8(this);
        } else {
            Actor_Kill(&this->actor);
        }
    }
}

void EnInvadepoh_func_80B4CFFC(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    if ((gSaveContext.save.time >= CLOCK_TIME(20, 00)) && (gSaveContext.save.time < CLOCK_TIME(20, 14) + 15)) {
        this->actor.update = EnInvadepoh_func_80B4D054;
        this->actor.draw = EnInvadepoh_func_80B4E324;
        EnInvadepoh_func_80B4C6C8(this);
    }
}

void EnInvadepoh_func_80B4D054(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;
    s32 sp2C = CHECK_FLAG_ALL(this->actor.flags, ACTOR_FLAG_40);
    s32 sp28 = Actor_ProcessTalkRequest(&this->actor, &play->state);

    if (sp28 != 0) {
        func_80151BB4(play, 5);
        EnInvadepoh_func_80B4CAB0(this);
    }
    this->actionFunc(this, play);
    if (sp2C && (this->actor.update != NULL)) {
        SkelAnime_Update(&this->skelAnime);
        EnInvadepoh_func_80B45CE0(&this->unk_324);
        if ((this->actionFunc != EnInvadepoh_func_80B4CB0C) && !sp28 && this->actor.isTargeted) {
            func_800B8614(&this->actor, play, 350.0f);
        }
        Collider_UpdateCylinder(&this->actor, &this->unk_2A0);
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->unk_2A0.base);
    }
}

void EnInvadepoh_func_80B4D15C(EnInvadepoh* this) {
    static EnInvadepohUnkStruct1 D_80B4EE0C[3] = {
        { 0.08f, 0x2BC, -0xA },
        { 0.09f, 0x12C, -5 },
        { 0.05f, 0x190, 0 },
    };
    s32 pad;
    s32 sp28 = ENINVADEPOH_GET_PARAM_7(&this->actor);
    s32 pad2;

    Animation_PlayLoop(&this->skelAnime, &gAlienHoldingCowAnim);
    this->skelAnime.curFrame = (ENINVADEPOH_GET_PARAM_7(&this->actor)) * this->skelAnime.endFrame * 0.25f;
    this->unk_389 = 255;
    this->actor.draw = EnInvadepoh_func_80B4DB14;
    this->unk_38B = 1;
    this->unk_38C = 0;
    this->unk_38D = 255;
    this->unk_300 = D_80B4EE0C[sp28].unk0;
    this->unk_304 = sp28 * 0x5555;
    this->actor.world.pos.x = Math_SinS(this->unk_304) * 80.0f + this->actor.home.pos.x;
    this->actor.world.pos.y = this->actor.home.pos.y;
    this->actor.world.pos.z = Math_CosS(this->unk_304) * 80.0f + this->actor.home.pos.z;
    this->actor.shape.rot.y = this->unk_304 + 0x4000;
    this->unk_370 = D_80B4EE0C[sp28].unk4;
    this->unk_372 = D_80B4EE0C[sp28].unk6;
    this->actionFunc = EnInvadepoh_func_80B4D290;
    this->actor.velocity.y = 0.0f;
}

void EnInvadepoh_func_80B4D290(EnInvadepoh* this, PlayState* play) {
    Actor* sp2C;
    f32 sp28;

    if (D_80B503F0 == NULL) {
        Actor_Kill(&this->actor);
        return;
    }
    Math_StepToF(&this->actor.velocity.y, 15.0f, this->unk_300);
    sp28 = Math_SmoothStepToF(&this->actor.world.pos.y, this->actor.home.pos.y + 850.0f, 0.2f, this->actor.velocity.y,
                              0.01f);
    this->unk_304 += 0x2BC;
    this->actor.world.pos.x = Math_SinS(this->unk_304) * 80.0f + this->actor.home.pos.x;
    this->actor.world.pos.z = Math_CosS(this->unk_304) * 80.0f + this->actor.home.pos.z;
    this->unk_370 += this->unk_372;
    this->actor.shape.rot.y += this->unk_370;

    if (this->actor.child != NULL) {
        sp2C = this->actor.child;
        sp2C->world.pos.x = this->actor.world.pos.x;
        sp2C->world.pos.y = this->actor.world.pos.y - 38.0f;
        sp2C->world.pos.z = this->actor.world.pos.z;
        sp2C->shape.rot.y = this->actor.shape.rot.y;
    }
    if (sp28 < 5.0f) {
        Actor_Kill(&this->actor);
    }
}

void EnInvadepoh_func_80B4D3E4(EnInvadepoh* this) {
    Animation_PlayLoop(&this->skelAnime, &gAlienHoldingCowAnim);
    this->skelAnime.curFrame = (ENINVADEPOH_GET_PARAM_7(&this->actor)) * this->skelAnime.endFrame * 0.25f;
    this->unk_389 = 255;
    this->actor.draw = NULL;
    this->unk_38B = 1;
    this->unk_38C = 0;
    this->unk_38D = 255;
    this->unk_306 = 0x190;
    this->unk_304 = 0;
    this->unk_2F0 = 200;
    this->actionFunc = EnInvadepoh_func_80B4D480;
    this->actor.velocity.y = 0.0f;
}

void EnInvadepoh_func_80B4D480(EnInvadepoh* this, PlayState* play) {
    s32 pad;
    f32 pad2;
    s32 sp2C = 0;

    if (this->unk_2F0 > 0) {
        this->unk_2F0--;
    }
    if (this->unk_2F0 > 160) {
        this->actor.draw = NULL;
    } else {
        this->actor.draw = EnInvadepoh_func_80B4DB14;
        pad = (sp2C ? 0 : this->unk_2F0); //! fake
        if ((105 > pad) && (pad >= 100)) {
            this->actor.gravity = -1.0f;
            Math_SmoothStepToS(&this->actor.shape.rot.x, 0x2000, 8, 0x320, 0x28);
        } else {
            this->actor.gravity = 0.7f;
            Math_SmoothStepToS(&this->actor.shape.rot.x, 0, 8, 0x320, 0x28);
        }

        this->actor.velocity.y += this->actor.gravity;
        this->actor.velocity.y *= 0.92f;
        if (this->unk_2F0 > 80) {
            this->actor.world.pos.y += this->actor.velocity.y;
        } else {
            f32 pad3 = this->actor.home.pos.y + 850.0f;

            sp2C = Math_StepToF(&this->actor.world.pos.y, pad3, fabsf(this->actor.velocity.y));
        }
        pad2 = (this->unk_304 * -0.06f) + this->unk_306;
        pad2 *= 0.98f;
        this->unk_306 = pad2;
        this->actor.shape.rot.y += this->unk_306;
        if (this->actor.child != NULL) {
            Actor* pad1 = this->actor.child;

            pad1->world.pos.x = this->actor.world.pos.x;
            pad1->world.pos.y = this->actor.world.pos.y - 30.0f;
            pad1->world.pos.z = this->actor.world.pos.z;
            pad1->shape.rot.y = this->actor.shape.rot.y;
        }
    }
    if ((this->unk_2F0 <= 0) || sp2C) {
        Actor_Kill(&this->actor);
    }
}

void EnInvadepoh_func_80B4D670(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;
    s32 sp34;

    if (Object_IsLoaded(&play->objectCtx, this->unk_2F4)) {
        sp34 = ENINVADEPOH_GET_PARAM_7(&this->actor);
        this->actor.objBankIndex = this->unk_2F4;
        Actor_SetObjectDependency(play, &this->actor);
        EnInvadepoh_func_80B45080();
        this->actor.update = EnInvadepoh_func_80B4D760;
        SkelAnime_InitFlex(play, &this->skelAnime, &gAlienSkel, &gAlienHoldingCowAnim, this->unk_188, this->unk_212,
                           ALIEN_LIMB_MAX);
        if (sp34 < 3) {
            EnInvadepoh_func_80B453F4(this, play, sp34);
            EnInvadepoh_func_80B4D15C(this);
        } else {
            EnInvadepoh_func_80B45460(this, play);
            EnInvadepoh_func_80B4D3E4(this);
        }
    }
}

void EnInvadepoh_func_80B4D760(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    this->actionFunc(this, play);

    if (this->actor.update != NULL) {
        SkelAnime_Update(&this->skelAnime);
        func_800B9010(&this->actor, NA_SE_EN_FOLLOWERS_BEAM_PRE - SFX_FLAG);
    }
}

void EnInvadepoh_func_80B4D7B8(PlayState* play) {
    s32 i;
    EnInvadepohWarpEffect* warpEffect;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C2DC(play->state.gfxCtx);

    for (i = 0, warpEffect = D_80B50350; i < 10; i++, warpEffect++) {
        if (warpEffect->timer > 0) {
            u32 temp_s5 = (play->gameplayFrames + (u8)(i * 0x10)) % 0x80;
            u32 temp_s6 = (play->gameplayFrames * -0xF) % 0x100;

            Matrix_Translate(warpEffect->pos.x, warpEffect->pos.y, warpEffect->pos.z, MTXMODE_NEW);
            Matrix_Scale(0.1f, 0.1f, 0.1f, MTXMODE_APPLY);
            gDPPipeSync(POLY_XLU_DISP++);
            gDPSetPrimColor(POLY_XLU_DISP++, 0x80, 0x80, 255, 255, 170, warpEffect->alpha);
            gDPSetEnvColor(POLY_XLU_DISP++, 255, 50, 0, 0);
            gSPSegment(POLY_XLU_DISP++, 0x8,
                       Gfx_TwoTexScroll(play->state.gfxCtx, 0, temp_s5, 0, 0x20, 0x40, 1, 0, temp_s6, 0x20, 0x40));
            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), 2);
            gSPDisplayList(POLY_XLU_DISP++, gameplay_keep_DL_02E510);
        }
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

void EnInvadepoh_func_80B4D9B4(Actor* thisx, PlayState* play) {
    EnInvadepoh_func_80B4D7B8(play);
}

s32 EnInvadepoh_func_80B4D9D8(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx,
                              Gfx** gfx) {
    return false;
}

void EnInvadepoh_func_80B4D9F4(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* pos, Actor* thisx, Gfx** gfx) {
    static Vec3f D_80B4EE24 = { 2000.0f, 1000.0f, 0.0f };
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    if ((limbIndex == ALIEN_LIMB_LEFT_EYE) && (this->unk_38D != 0)) {
        Matrix_Push();
        Matrix_RotateZS(-0x53ED, MTXMODE_APPLY);
        Matrix_RotateYS(-0x3830, MTXMODE_APPLY);
        Matrix_Scale(1.0f, 1.0f, 1.5f, MTXMODE_APPLY);
        Matrix_Get(&D_80B502A0);
        Matrix_Pop();
    } else if ((limbIndex == ALIEN_LIMB_RIGHT_EYE) && (this->unk_38D != 0)) {
        Matrix_Push();
        Matrix_RotateZS(-0x53ED, MTXMODE_APPLY);
        Matrix_RotateYS(-0x47D0, MTXMODE_APPLY);
        Matrix_Scale(1.0f, 1.0f, 1.5f, MTXMODE_APPLY);
        Matrix_Get(&D_80B502E0);
        Matrix_Pop();
    }
    if (limbIndex == 11) {
        Matrix_MultVec3f(&D_80B4EE24, &this->actor.focus.pos);
    }
}

void EnInvadepoh_func_80B4DB14(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C2DC(play->state.gfxCtx);
    Matrix_Push();
    if (this->unk_38B != 0) {
        if (this->unk_389 == 255) {
            func_8012C28C(play->state.gfxCtx);
            AnimatedMat_Draw(play, sAlienEmptyTexAnim);
            Scene_SetRenderModeXlu(play, 0, 1);
            gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 255);
            POLY_OPA_DISP = SkelAnime_DrawFlex(play, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                               this->skelAnime.dListCount, EnInvadepoh_func_80B4D9D8,
                                               EnInvadepoh_func_80B4D9F4, &this->actor, POLY_OPA_DISP);
        } else {
            AnimatedMat_Draw(play, sAlienEmptyTexAnim);
            Scene_SetRenderModeXlu(play, 1, 2);
            gDPSetEnvColor(POLY_XLU_DISP++, 0, 0, 0, this->unk_389);
            POLY_XLU_DISP = SkelAnime_DrawFlex(play, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                               this->skelAnime.dListCount, EnInvadepoh_func_80B4D9D8,
                                               EnInvadepoh_func_80B4D9F4, &this->actor, POLY_XLU_DISP);
        }
        if (this->unk_38D != 0) {
            Gfx* ptr;

            AnimatedMat_Draw(play, sAlienEyeBeamTexAnim);

            OPEN_DISPS(play->state.gfxCtx);
            ptr = POLY_XLU_DISP;

            gDPPipeSync(ptr++);
            gDPSetPrimColor(ptr++, 0, 0xFF, 240, 180, 100, 60);
            gDPSetEnvColor(ptr++, 255, 255, 255, 100.0f / 170.0f * this->unk_38D);

            Matrix_Mult(&D_80B502A0, MTXMODE_NEW);
            gSPMatrix(ptr++, Matrix_NewMtx(play->state.gfxCtx), 2);
            gSPDisplayList(ptr++, gAlienEyeBeamDL);

            Matrix_Mult(&D_80B502E0, MTXMODE_NEW);
            gSPMatrix(ptr++, Matrix_NewMtx(play->state.gfxCtx), 2);
            gSPDisplayList(ptr++, gAlienEyeBeamDL);

            POLY_XLU_DISP = ptr;
            CLOSE_DISPS(play->state.gfxCtx);
        }
    }
    if (this->unk_38C != 0) {
        Matrix_SetTranslateRotateYXZ(this->actor.world.pos.x, this->actor.world.pos.y + 68.0f, this->actor.world.pos.z,
                                     &this->actor.shape.rot);
        Matrix_Scale(this->unk_390.x, this->unk_390.y, this->unk_390.z, MTXMODE_APPLY);
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), 2);
        gSPDisplayList(POLY_XLU_DISP++, gAlienDeathFlashDL);
    }
    if (this->unk_38B != 0) {
        Gfx* ptr;
        Vec3f sp80;
        Vec3f sp74;
        s32 temp;

        OPEN_DISPS(play->state.gfxCtx);
        ptr = POLY_XLU_DISP;

        ptr = func_8012C868(ptr);

        gDPSetDither(ptr++, G_CD_NOISE);
        gDPSetCombineLERP(ptr++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE,
                          0);

        Matrix_Mult(&play->billboardMtxF, MTXMODE_NEW);
        Matrix_MultVecZ(60.0f, &sp80);

        sp74.x = this->actor.world.pos.x + sp80.x;
        sp74.y = this->actor.world.pos.y + sp80.y + 68.0f;
        sp74.z = this->actor.world.pos.z + sp80.z;

        Matrix_Translate(sp74.x, sp74.y, sp74.z, MTXMODE_NEW);
        Matrix_Scale(0.25f, 0.25f, 0.25f, MTXMODE_APPLY);

        temp = 100.0f / 255.0f * this->unk_389;

        gSPDisplayList(ptr++, gameplay_keep_DL_029CB0);
        gDPSetPrimColor(ptr++, 0, 0, 240, 180, 100, temp);
        gSPMatrix(ptr++, Matrix_NewMtx(play->state.gfxCtx), 2);
        gSPDisplayList(ptr++, gameplay_keep_DL_029CF0);

        POLY_XLU_DISP = ptr;

        if ((this->unk_389 > 128) && EnInvadepoh_func_80B456A8(play, &sp74)) {
            func_800F9824(play, &play->envCtx, &play->view, play->state.gfxCtx, sp74, 10.0f, 9.0f, 0, 0);
        }

        CLOSE_DISPS(play->state.gfxCtx);
    }
    Matrix_Pop();

    CLOSE_DISPS(play->state.gfxCtx);
}

s32 EnInvadepoh_func_80B4E120(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnInvadepoh* this = (EnInvadepoh*)thisx;
    if (limbIndex == 5) {
        rot->x -= this->actor.shape.rot.x;
    }
    return false;
}

void EnInvadepoh_func_80B4E158(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    func_8012C5B0(play->state.gfxCtx);
    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, (s32)this->skelAnime.dListCount,
                          EnInvadepoh_func_80B4E120, NULL, &this->actor);
}

void EnInvadepoh_func_80B4E1B0(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    func_8012C5B0(play->state.gfxCtx);
    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount, NULL,
                          NULL, &this->actor);
}

s32 EnInvadepoh_func_80B4E200(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    if (limbIndex == ROMANI_LIMB_HEAD) {
        EnInvadepoh* this = ((EnInvadepoh*)thisx);

        rot->x += this->unk_324.unk_20.y;
        rot->y += this->unk_324.unk_20.z;
        rot->z += this->unk_324.unk_20.x;
    } else if (limbIndex == ROMANI_LIMB_TORSO) {
        EnInvadepoh* this = ((EnInvadepoh*)thisx);

        rot->x += (s16)(this->unk_324.unk_34 * this->unk_324.unk_20.y);
        rot->z += this->unk_324.unk_40;
    }
    return false;
}

void EnInvadepoh_func_80B4E2AC(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* pos, Actor* thisx) {
    static Vec3f D_80B4EE30 = { 400.0f, 270.0f, 0.0f };
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    if (limbIndex == ROMANI_LIMB_LEFT_HAND) {
        OPEN_DISPS(play->state.gfxCtx);

        gSPDisplayList(POLY_OPA_DISP++, gRomaniBowDL);

        CLOSE_DISPS(play->state.gfxCtx);
    } else if (limbIndex == ROMANI_LIMB_HEAD) {
        Matrix_MultVec3f(&D_80B4EE30, &this->actor.focus.pos);
    }
}

void EnInvadepoh_func_80B4E324(Actor* thisx, PlayState* play) {
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x09, sRomaniMouthTextures[this->unk_324.mouthAnim.curIndex]);
    gSPSegment(POLY_OPA_DISP++, 0x08, sRomaniEyeTextures[this->unk_324.eyeAnim.curIndex]);
    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnInvadepoh_func_80B4E200, EnInvadepoh_func_80B4E2AC, &this->actor);

    CLOSE_DISPS(play->state.gfxCtx);
}

void EnInvadepoh_func_80B4E3F0(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnInvadepoh* this = (EnInvadepoh*)thisx;
    Vec3f sp5C;

    Matrix_Push();
    Matrix_Mult(&play->billboardMtxF, MTXMODE_NEW);
    Matrix_MultVecZ(200.0f, &sp5C);
    Matrix_Pop();
    sp5C.x += this->actor.world.pos.x;
    sp5C.y += this->actor.world.pos.y;
    sp5C.z += this->actor.world.pos.z;
    EnInvadepoh_func_80B45518(&sp5C);
    Matrix_ReplaceRotation(&play->billboardMtxF);
    Matrix_RotateZS(this->unk_304, MTXMODE_APPLY);

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C2DC(play->state.gfxCtx);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), 2);
    gDPSetPrimColor(POLY_XLU_DISP++, 0xFF, 0x80, 255, 255, 0, 180);
    gDPSetEnvColor(POLY_XLU_DISP++, 255, 50, 0, 0);
    gSPDisplayList(POLY_XLU_DISP++, gEffFlash1DL);

    if (EnInvadepoh_func_80B456A8(play, &sp5C)) {
        func_800F9824(play, &play->envCtx, &play->view, play->state.gfxCtx, sp5C, 20.0f, 9.0f, 0, 0);
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

s32 EnInvadepoh_func_80B4E5B0(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    if ((limbIndex == DOG_LIMB_HEAD) || (limbIndex == DOG_LIMB_RIGHT_FACE_HAIR) ||
        (limbIndex == DOG_LIMB_LEFT_FACE_HAIR)) {
        EnInvadepoh* this = (EnInvadepoh*)thisx;

        rot->x += this->unk_324.unk_20.x;
        rot->y += this->unk_324.unk_20.y;
        rot->z += this->unk_324.unk_20.z;
    }
    return false;
}

void EnInvadepoh_func_80B4E61C(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* pos, Actor* thisx) {
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    if (limbIndex == 5) {
        Matrix_MultVecY(20.0f, &this->actor.focus.pos);
    }
}

void EnInvadepoh_func_80B4E660(Actor* thisx, PlayState* play) {
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);
    gDPSetEnvColor(POLY_OPA_DISP++, 255, 255, 200, 0);
    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnInvadepoh_func_80B4E5B0, EnInvadepoh_func_80B4E61C, &this->actor);

    CLOSE_DISPS(play->state.gfxCtx);
}

s32 EnInvadepoh_func_80B4E6E4(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    if (limbIndex == CREMIA_LIMB_HEAD) {
        EnInvadepoh* this = (EnInvadepoh*)thisx;

        rot->x += this->unk_324.unk_20.y;
        rot->y += this->unk_324.unk_20.z;
        rot->z += this->unk_324.unk_20.x;
    } else if (limbIndex == CREMIA_LIMB_TORSO) {
        EnInvadepoh* this = (EnInvadepoh*)thisx;

        rot->x += (s16)(this->unk_324.unk_34 * this->unk_324.unk_20.y);
    }
    return false;
}

void EnInvadepoh_func_80B4E784(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* pos, Actor* thisx) {
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    if (limbIndex == 9) {
        Matrix_MultZero(&this->actor.focus.pos);
    }
}

void EnInvadepoh_func_80B4E7BC(Actor* thisx, PlayState* play) {
    EnInvadepoh* this = (EnInvadepoh*)thisx;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x09, sCremiaMouthTextures[this->unk_324.mouthAnim.curIndex]);
    gSPSegment(POLY_OPA_DISP++, 0x08, sCremiaEyeTextures[this->unk_324.eyeAnim.curIndex]);
    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnInvadepoh_func_80B4E6E4, EnInvadepoh_func_80B4E784, &this->actor);

    CLOSE_DISPS(play->state.gfxCtx);
}
