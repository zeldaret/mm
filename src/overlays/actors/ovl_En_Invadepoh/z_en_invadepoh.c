/*
 * File z_en_invadepoh.c
 * Overlay: ovl_en_invadepoh
 * Description: Aliens event
 */

#include "z_en_invadepoh.h"
#include "../ovl_En_Door/z_en_door.h"

#define FLAGS 0x00000010

#define THIS ((EnInvadepoh*)thisx)

void EnInvadepoh_Init(Actor* thisx, GlobalContext* globalCtx);
void EnInvadepoh_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnInvadepoh_Update(Actor* thisx, GlobalContext* globalCtx);

void func_80B46DA8(EnInvadepoh* this);
void func_80B46DC8(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B46E20(EnInvadepoh* this);
void func_80B46E44(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B46EC0(EnInvadepoh* this);
void func_80B46EE8(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B46F88(EnInvadepoh* this);
void func_80B46FA8(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B47064(EnInvadepoh* this);
void func_80B47084(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B470E0(EnInvadepoh* this);
void func_80B47108(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B471C0(EnInvadepoh* this);
void func_80B471E0(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B47248(EnInvadepoh* this);
void func_80B47268(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B47298(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B47304(EnInvadepoh* this);
void func_80B47324(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B473E4(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B474DC(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B47600(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B477B4(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B48324(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B4ACF0(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B4AD3C(EnInvadepoh* this);
void func_80B4AD60(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B4ADB8(EnInvadepoh* this);
void func_80B4ADCC(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B4AEC0(EnInvadepoh* this);
void func_80B4AEDC(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B4AF80(EnInvadepoh* this);
void func_80B4AF94(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B4B024(EnInvadepoh* this);
void func_80B4B048(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B4B484(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B4B510(EnInvadepoh* this);
void func_80B4B564(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B4B724(EnInvadepoh* this);
void func_80B4B768(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B4B820(EnInvadepoh* this);
void func_80B4B864(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B48374(EnInvadepoh* this);
void func_80B483CC(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B49A00(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B4994C(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B497EC(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B49628(EnInvadepoh* this);
void func_80B49670(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B49454(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B4934C(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B491EC(EnInvadepoh* this);
void func_80B49228(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B49C38(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B49DFC(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B4A350(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B4A5E4(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B4A67C(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B4A81C(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B4BC4C(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B4C058(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B4C218(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B4C730(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B4CB0C(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B4CCCC(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B4D480(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B47568(EnInvadepoh* this);
void func_80B478F4(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B47938(EnInvadepoh* this);
void func_80B479E8(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B4843C(EnInvadepoh* this);
void func_80B484EC(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B48588(EnInvadepoh* this);
void func_80B48610(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B48848(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B47278(EnInvadepoh* this);
void func_80B48AD4(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B48E4C(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B49404(EnInvadepoh* this);
void func_80B4A570(EnInvadepoh* this);
void func_80B4C1BC(EnInvadepoh* this);
void func_80B4D290(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B4CC70(EnInvadepoh* this);
void func_80B4770C(EnInvadepoh* this);
void func_80B48948(EnInvadepoh* this);
void func_80B49904(EnInvadepoh* this);
void func_80B499BC(EnInvadepoh* this);
void func_80B492FC(EnInvadepoh* this);

void func_80B4D670(Actor* thisx, GlobalContext* globalCtx);
void func_80B47BAC(Actor* thisx, GlobalContext* globalCtx);
void func_80B47D30(Actor* thisx, GlobalContext* globalCtx);
void func_80B47FA8(Actor* thisx, GlobalContext* globalCtx);
void func_80B48060(Actor* thisx, GlobalContext* globalCtx);
void func_80B481C4(Actor* thisx, GlobalContext* globalCtx);
void func_80B4827C(Actor* thisx, GlobalContext* globalCtx);
void func_80B48620(Actor* thisx, GlobalContext* globalCtx);
void func_80B48FB0(Actor* thisx, GlobalContext* globalCtx);
void func_80B49F88(Actor* thisx, GlobalContext* globalCtx);
void func_80B4A9C8(Actor* thisx, GlobalContext* globalCtx);
void func_80B4B0C4(Actor* thisx, GlobalContext* globalCtx);
void func_80B4CE54(Actor* thisx, GlobalContext* globalCtx);
void func_80B4B8BC(Actor* thisx, GlobalContext* globalCtx);
void func_80B4C3A0(Actor* thisx, GlobalContext* globalCtx);
void func_80B49B1C(Actor* thisx, GlobalContext* globalCtx);
void func_80B4E158(Actor* thisx, GlobalContext* globalCtx);
void func_80B4E3F0(Actor* thisx, GlobalContext* globalCtx);
void func_80B4D9B4(Actor* thisx, GlobalContext* globalCtx);
void func_80B4E1B0(Actor* thisx, GlobalContext* globalCtx);
void func_80B4E324(Actor* thisx, GlobalContext* globalCtx);
void func_80B4BA84(Actor* thisx, GlobalContext* globalCtx);
void func_80B4E660(Actor* thisx, GlobalContext* globalCtx);
void func_80B4C5C0(Actor* thisx, GlobalContext* globalCtx);
void func_80B4E7BC(Actor* thisx, GlobalContext* globalCtx);
void func_80B4A1B8(Actor* thisx, GlobalContext* globalCtx);
void func_80B4ABDC(Actor* thisx, GlobalContext* globalCtx);
void func_80B4D054(Actor* thisx, GlobalContext* globalCtx);
void func_80B4DB14(Actor* thisx, GlobalContext* globalCtx);
void func_80B4D760(Actor* thisx, GlobalContext* globalCtx);
void func_80B4A168(Actor* thisx, GlobalContext* globalCtx);
void func_80B4873C(Actor* thisx, GlobalContext* globalCtx);
void func_80B490F0(Actor* thisx, GlobalContext* globalCtx);
void func_80B4AB8C(Actor* thisx, GlobalContext* globalCtx);
void func_80B4B218(Actor* thisx, GlobalContext* globalCtx);
void func_80B4BA30(Actor* thisx, GlobalContext* globalCtx);
void func_80B4C568(Actor* thisx, GlobalContext* globalCtx);
void func_80B4CFFC(Actor* thisx, GlobalContext* globalCtx);

void func_80B4627C(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B46414(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B46520(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B465CC(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B46644(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B46644(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B468B4(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B46644(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B46644(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B46644(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B469C4(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B46A80(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B46644(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B46414(EnInvadepoh* this, GlobalContext* globalCtx);

void func_80B46BB0(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B46BC0(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B46C08(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B46C34(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B46C50(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B46C50(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B46C7C(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B46C50(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B46C50(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B46C50(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B46C94(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B46CC0(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B46CF4(EnInvadepoh* this, GlobalContext* globalCtx);
void func_80B46D28(EnInvadepoh* this, GlobalContext* globalCtx);

void func_80B46184(unkStruct_80B50350* unkStruct);

s32 func_80B450C0(f32* arg0, f32* arg1, f32 arg2, f32 arg3, f32 arg4);
s32 func_80B4516C(EnInvadepoh* this);

void func_80B45A4C(EnInvadePohStruct* s, s32* u);
void func_80B45A94(EnInvadePohStruct* s, s32* u);
void func_80B45B1C(EnInvadePohStruct* s, s32* u);

extern AnimatedMaterial* D_80B503FC;
extern AnimatedMaterial* D_80B50400;
extern AnimatedMaterial D_06000560;
extern AnimatedMaterial D_06000550;
extern AnimationHeader D_06004264;
extern FlexSkeletonHeader D_06004010;
extern FlexSkeletonHeader D_06004E50;
extern FlexSkeletonHeader D_06004C30;
extern FlexSkeletonHeader D_06013928;
extern AnimationHeader D_06004E98;
extern AnimationHeader D_06002A8C;
extern AnimationHeader D_060021C8;
extern AnimationHeader D_06001BD8;
extern AnimationHeader D_06000998;
extern AnimationHeader D_06001560;
extern AnimationHeader D_06002A8C;
extern AnimationHeader D_06014088;
extern AnimationHeader D_06009E58;
extern AnimationHeader D_06009E58;
extern AnimationHeader D_06016720;
extern AnimationHeader D_0600A174;
extern AnimationHeader D_06009E58;
extern AnimationHeader D_06001674;
extern AnimationHeader D_06001D80;
extern AnimationHeader D_060006C8;
extern AnimationHeader D_06000608;
extern AnimationHeader D_06007328;
extern AnimationHeader D_060080F0;
extern FlexSkeletonHeader D_06015C28;

extern Gfx D_0600FFC8[];
extern Gfx D_060107C8[];
extern Gfx D_06010FC8[];
extern Gfx D_060117C8[];
extern Gfx D_06011FC8[];
extern Gfx D_060127C8[];
extern Gfx D_06012BC8[];
extern Gfx D_06012FC8[];
extern Gfx D_060133C8[];
extern Gfx D_06011AD8[];
extern Gfx D_060122D8[];
extern Gfx D_06012AD8[];
extern Gfx D_060132D8[];
extern Gfx D_06013AD8[];
extern Gfx D_060142D8[];
extern Gfx D_06014AD8[];
extern Gfx D_06014ED8[];
extern Gfx D_060152D8[];
extern Gfx D_060156D8[];
extern Gfx D_04023210[];
extern Gfx D_060003B0[];
extern Gfx D_04029CB0[];
extern Gfx D_04029CF0[];
extern Gfx D_06000720[];
extern Gfx D_0402E510[];
extern Gfx D_06000080[];

extern Vec3s D_801D15BC;
extern s32 D_801BDA9C;

const ActorInit En_Invadepoh_InitVars = {
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

static ColliderCylinderInit D_80B4E8B0 = {
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

static ColliderCylinderInit D_80B4E8DC = {
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

static ColliderCylinderInit D_80B4E908 = {
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

static Vec3f D_80B4E934 = {216.0f, -20.0f, 1395.0f};

static s32 D_80B4E940 = 0;

static Gfx* D_80B4E944[] = {
    D_0600FFC8, D_060107C8, D_06010FC8, D_060117C8, D_06011FC8,
};

static Gfx* D_80B4E958[] = {
    D_060127C8,
    D_06012BC8,
    D_06012FC8,
    D_060133C8,
};

static s8 D_80B4E968 = 0;

static Gfx* D_80B4E96C[] = {
    D_06011AD8, D_060122D8, D_06012AD8, D_060132D8, D_06013AD8, D_060142D8,
};

static Gfx* D_80B4E984[] = {
    D_06014AD8,
    D_06014ED8,
    D_060152D8,
    D_060156D8,
};

static s8 D_80B4E994 = 0;

static s8 D_80B4E998 = NULL;

static s8 D_80B4E99C[] = { 0 };

static s8 D_80B4E9A0[] = { 0, 1, 2, 0 };

static s8 D_80B4E9A4[] = { 0, 1, 2, 1, 0 };

static s8 D_80B4E9AC[] = { 0, 1, 2, 2, 1, 0 };

static s8 D_80B4E9B4[] = {
    0, 1, 2, 1, 0, 1, 2, 0,
};

static s8 D_80B4E9BC[] = { 1 };

static s8 D_80B4E9C0[] = { 3 };

static unkstruct_invadepoh_0 D_80B4E9C4 = { D_80B4E99C, 1 };

static unkstruct_invadepoh_0 D_80B4E9CC = { D_80B4E9A0, 4 };

static unkstruct_invadepoh_0 D_80B4E9D4 = { D_80B4E9A4, 5 };

static unkstruct_invadepoh_0 D_80B4E9DC = { D_80B4E9AC, 6 };

static unkstruct_invadepoh_0 D_80B4E9E4 = { D_80B4E9B4, 8 };

static unkstruct_invadepoh_0 D_80B4E9EC = { D_80B4E9BC, 1 };

static unkstruct_invadepoh_0 D_80B4E9F4 = { D_80B4E9C0, 1 };

static unkstruct_invadepoh_2 D_80B4E9FC = { 0, &D_80B4E9C4 };

static unkstruct_invadepoh_1 D_80B4EA04[] = {
    { 2, 0.5f },
    { 3, 0.9f },
    { 4, 0.97f },
    { 5, 1.0f },
};

static unkstruct_invadepoh_1 D_80B4EA24[] = {
    { 1, 1.0f },
};

static unkstruct_invadepoh_4 D_80B4EA2C = { 2, &D_80B4E9C4, 4, D_80B4EA04, 0x28, 0x3c };

static unkstruct_invadepoh_3 D_80B4EA40 = {
    1,
    &D_80B4E9CC,
    1,
    D_80B4EA24,
};

static unkstruct_invadepoh_3 D_80B4EA50 = {
    1,
    &D_80B4E9D4,
    1,
    D_80B4EA24,
};

static unkstruct_invadepoh_3 D_80B4EA60 = {
    1,
    &D_80B4E9DC,
    1,
    D_80B4EA24,
};

static unkstruct_invadepoh_3 D_80B4EA70 = {
    1,
    &D_80B4E9E4,
    1,
    D_80B4EA24,
};

static unkstruct_invadepoh_2 D_80B4EA80 = {
    0,
    &D_80B4E9EC,
};

static unkstruct_invadepoh_2 D_80B4EA88 = {
    0,
    &D_80B4E9F4,
};

static void* D_80B4EA90[] = {
    &D_80B4E9FC, &D_80B4EA2C, &D_80B4EA40, &D_80B4EA50, &D_80B4EA60, &D_80B4EA70, &D_80B4EA80, &D_80B4EA88,
};

static s8 D_80B4EAB0[] = { 0 };

static s8 D_80B4EAB4[] = { 1 };

static s8 D_80B4EAB8[] = { 2 };

static s8 D_80B4EABC[] = { 3 };

static unkstruct_invadepoh_0 D_80B4EAC0 = { D_80B4EAB0, 1 };

static unkstruct_invadepoh_0 D_80B4EAC8 = { D_80B4EAB4, 1 };

static unkstruct_invadepoh_0 D_80B4EAD0 = { D_80B4EAB8, 1 };

static unkstruct_invadepoh_0 D_80B4EAD8 = { D_80B4EABC, 1 };

static unkstruct_invadepoh_2 D_80B4EAE0 = { 0, &D_80B4EAC0 };

static unkstruct_invadepoh_2 D_80B4EAE8 = { 0, &D_80B4EAC8 };

static unkstruct_invadepoh_2 D_80B4EAF0 = { 0, &D_80B4EAD0 };

static unkstruct_invadepoh_2 D_80B4EAF8 = { 0, &D_80B4EAD8 };

static void* D_80B4EB00[] = {
    &D_80B4EAE0,
    &D_80B4EAE8,
    &D_80B4EAF0,
    &D_80B4EAF8,
};

static s8 D_80B4EB10[] = { 0 };

static s8 D_80B4EB14[] = { 0, 1, 2, 0 };

static s8 D_80B4EB18[] = { 0, 1, 2, 1, 0 };

static s8 D_80B4EB20[] = { 0, 1, 2, 2, 1, 0 };

static s8 D_80B4EB28[] = { 0, 1, 2, 1, 0, 1, 2, 0 };

static unkstruct_invadepoh_0 D_80B4EB30 = { D_80B4EB10, 1 };

static unkstruct_invadepoh_0 D_80B4EB38 = { D_80B4EB14, 4 };

static unkstruct_invadepoh_0 D_80B4EB40 = { D_80B4EB18, 5 };

static unkstruct_invadepoh_0 D_80B4EB48 = { D_80B4EB20, 6 };

static unkstruct_invadepoh_0 D_80B4EB50 = { D_80B4EB28, 8 };

static unkstruct_invadepoh_2 D_80B4EB58 = { 0, &D_80B4EB30 };

static unkstruct_invadepoh_1 D_80B4EB60[] = {
    { 2, 0.5f },
    { 3, 0.9f },
    { 4, 0.95f },
    { 5, 1.0f },
};

static unkstruct_invadepoh_1 D_80B4EB80[] = {
    { 1, 1.0f },
};

static unkstruct_invadepoh_4 D_80B4EB88 = { 2, &D_80B4EB30, 4, D_80B4EB60, 0x28, 0x3C };

static unkstruct_invadepoh_3 D_80B4EB9C = {
    1,
    &D_80B4EB38,
    1,
    D_80B4EB80,
};

static unkstruct_invadepoh_3 D_80B4EBAC = {
    1,
    &D_80B4EB40,
    1,
    D_80B4EB80,
};

static unkstruct_invadepoh_3 D_80B4EBBC = {
    1,
    &D_80B4EB48,
    1,
    D_80B4EB80,
};

static unkstruct_invadepoh_3 D_80B4EBCC = {
    1,
    &D_80B4EB50,
    1,
    D_80B4EB80,
};

static void* D_80B4EBDC[] = {
    &D_80B4EB58, &D_80B4EB88, &D_80B4EB9C, &D_80B4EBAC, &D_80B4EBBC, &D_80B4EBCC,
};

static s8 D_80B4EBF4[] = { 0 };

static unkstruct_invadepoh_0 D_80B4EBF8 = { D_80B4EBF4, 1 };

static unkstruct_invadepoh_2 D_80B4EC00 = { 0, &D_80B4EBF8 };

static void* D_80B4EC08[] = { &D_80B4EC00 };

static void (*D_80B4EC0C[])(struct EnInvadePohStruct*, s32* arg1) = {
    func_80B45A4C,
    func_80B45A94,
    func_80B45B1C,
};

static Color_RGBA8 D_80B4EC18 = { 0xFF, 0xFF, 0xC8, 0xFF };

static Color_RGBA8 D_80B4EC1C = { 0xFF, 0xC8, 0x00, 0x00 };

static void (*D_80B4EC20[])(struct unkStruct_80B50350*) = { func_80B46184 };

static InitChainEntry D_80B4EC24[] = {
    ICHAIN_F32(uncullZoneForward, 20000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 500, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 600, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_STOP),
};

static InitChainEntry D_80B4EC34[] = {
    ICHAIN_F32(uncullZoneForward, 20000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 300, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_STOP),
};

static InitChainEntry D_80B4EC44[] = {
    ICHAIN_F32(uncullZoneForward, 20000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 100, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_STOP),
};

static InitChainEntry D_80B4EC54[] = {
    ICHAIN_F32(uncullZoneForward, 20000, ICHAIN_CONTINUE), ICHAIN_F32(uncullZoneScale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 100, ICHAIN_CONTINUE),  ICHAIN_F32(targetArrowOffset, 1500, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_STOP),
};

static InitChainEntry D_80B4EC68[] = {
    ICHAIN_F32(uncullZoneForward, 20000, ICHAIN_CONTINUE), ICHAIN_F32(uncullZoneScale, 1000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 1000, ICHAIN_CONTINUE), ICHAIN_VEC3S(shape, 0, ICHAIN_CONTINUE),
    ICHAIN_F32(minVelocityY, -100, ICHAIN_CONTINUE),       ICHAIN_VEC3F_DIV1000(scale, 1000, ICHAIN_STOP),
};

static InitChainEntry D_80B4EC80[] = {
    ICHAIN_F32(uncullZoneForward, 2000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 50, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 50, ICHAIN_CONTINUE),
    ICHAIN_F32(gravity, -3, ICHAIN_CONTINUE),
    ICHAIN_U8(targetMode, 4, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 7, ICHAIN_STOP),
};

static InitChainEntry D_80B4EC98[] = {
    ICHAIN_F32(uncullZoneForward, 20000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 150, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 1500, ICHAIN_CONTINUE),
    ICHAIN_U8(targetMode, 3, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_STOP),
};

static EnInvadepohInitFunc D_80B4ECB0[] = {
    func_80B4627C, func_80B46414, func_80B46520, func_80B465CC, func_80B46644, func_80B46644, func_80B468B4,
    func_80B46644, func_80B46644, func_80B46644, func_80B469C4, func_80B46A80, func_80B46644, func_80B46414,
};

static EnInvadepohDestroyFunc D_80B4ECE8[] = {
    func_80B46BB0, func_80B46BC0, func_80B46C08, func_80B46C34, func_80B46C50, func_80B46C50, func_80B46C7C,
    func_80B46C50, func_80B46C50, func_80B46C50, func_80B46C94, func_80B46CC0, func_80B46CF4, func_80B46D28,
};

static s16 D_80B4ED20[] = {
    0x0082, 0x007D, 0x0073, 0x0064, 0x0050, 0x004E, 0x004C, 0x004A,
};

static Vec3f D_80B4ED30[] = {
    { 0.01f, 0.01f, 0.01f }, { 0.02f, 0.01f, 0.005f }, { -0.01f, 0.0f, 0.0f },
    { 0.01f, 0.01f, 0.01f }, { 0.005f, 0.01f, 0.02f },
};

static Vec3f D_80B4ED6C[] = {
    { 0.0005f, 0.0279999990016f, 0.01f }, { -0.01f, 0.0f, 0.0f }, { -0.01f, 0.0f, 0.0f },
    { 0.016f, 0.0004f, 0.01f },           { -0.01f, 0.0f, 0.0f }, { 0.0005f, 0.0005f, 0.0005f },
    { 0.0002f, 0.0002f, 0.0002f },
};

static s16 D_80B4EDC0[] = { 0xE0C0, 0xE890, 0xD508 };

static s16 D_80B4EDC8[] = {
    0xF8F8,
    0xFC18,
    0x0000,
    0x07D0,
};

static Vec3f D_80B4EDD0[] = {
    { -1813.0f, 374.0f, 1900.0f }, { 2198.0f, 153.0f, 3365.0f }, { -1434.0f, 262.0f, 3365.0f },
    { -393.0f, 396.0f, 1084.0f },  { 0.0f, 1500.0f, 0.0f },
};

static unkstruct_80B4EE0C D_80B4EE0C[] = {
    { 0.08f, 0x02BC, 0xFFF6 },
    { 0.09f, 0x012C, 0xFFFB },
    { 0.05f, 0x0190, 0x0000 },
};

static Vec3f D_80B4EE24 = {
    2000.0f,
    1000.0f,
    0.0f,
};

static Vec3f D_80B4EE30 = {
    400.0f,
    270.0f,
    0.0f,
};

// bss---------------------
MtxF D_80B502A0;
MtxF D_80B502E0;
Actor* D_80B50320[0x8]; // not sure if this should be Actor* or EnInvadepoh* array
u8 D_80B50340[0x8];
UNK_TYPE1 D_80B50348;
unkStruct_80B50350 D_80B50350[0xA];
Actor* D_80B503F0;
Actor* D_80B503F4; // possibly an EnInvadepoh* pointer but probably not since 3F0 above is def an Actor*
Actor* D_80B503F8;
UNK_TYPE2 D_80B50404[0x4];
Actor* D_80B5040C;

void func_80B439B0(s32 arg0, s32 arg1) {
    arg1 -= 0x1AAA;
    if (arg1 < 0) {
        arg1 = 0;
    }

    if (!(arg0 & 1)) {
        gSaveContext.roomInf[124][arg0 >> 1] = (gSaveContext.roomInf[124][arg0 >> 1] & 0xFFFF0000) | (arg1 & 0xFFFF);
    } else {
        gSaveContext.roomInf[124][arg0 >> 1] =
            (gSaveContext.roomInf[124][arg0 >> 1] & 0xFFFF) | ((arg1 & 0xFFFF) << 0x10);
    }
}

s32 func_80B43A24(s32 arg0) {
    u32 phi_v1;

    if ((arg0 & 1) == 0) {
        phi_v1 = gSaveContext.roomInf[124][arg0 >> 1] & 0xFFFF;
    } else {
        phi_v1 = (gSaveContext.roomInf[124][arg0 >> 1] & 0xFFFF0000) >> 0x10;
    }
    return phi_v1 + 0x1AAA;
}

void func_80B43A74(s32 arg0) {
    gSaveContext.roomInf[124][4] = (gSaveContext.roomInf[124][4] & ~0xFF) | arg0 & 0xFF;
}

s32 func_80B43A9C(void) {
    return (gSaveContext.roomInf[124][4] >> 0) & 0xFF;
}

s32 func_80B43AB0(void) {
    s32 retVal = func_80B43A9C();
    if (retVal < 0xC) {
        retVal++;
        func_80B43A74(retVal);
    }
    return retVal;
}

void func_80B43AF0(s32 arg0) {
    s32 currentTime = gSaveContext.time;

    if (((CURRENT_DAY == 1) && (currentTime >= CLOCK_TIME(2, 30))) && (currentTime < CLOCK_TIME(5, 15))) {
        s32 adjustment = (0xC - func_80B43A9C()) * 25.0f;

        func_80B439B0(arg0, currentTime + adjustment);
    }
}

s32 func_80B43B80(EnInvadepoh* this) {
    s32 i;
    s32 temp = this->unk308 - 1;

    for (i = 0; i < temp; i++) {
        if (this->unk37C[i] > this->clockTime) {
            break;
        }
    }

    return i;
}

void func_80B43BC8(EnInvadepoh* this, s8* arg1, Vec3f* arg2) {
    s32 temp_s5 = this->unk308;
    f32 temp_f22 = 1.0f / this->pathTotalDist;
    Vec3s* phi_s0 = &this->pathPoints[1];
    Vec3s* phi_s1 = &this->pathPoints[0];
    f32 new_var;
    Vec3f sp70;
    s32 phi_s2;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f6;
    f32 phi_f20 = 0.0f;
    f32 phi_f24 = 0.0f;

    for (phi_s2 = 0; phi_s2 < temp_s5; phi_s2++) {
        sp70.x = phi_s0->x - phi_s1->x;
        sp70.y = phi_s0->y - phi_s1->y;
        sp70.z = phi_s0->z - phi_s1->z;
        new_var = Math3D_Vec3fMagnitude(&sp70);
        temp_f14 = phi_f20 + new_var;
        temp_f12 = temp_f14 * temp_f22;

        if (this->clockTime <= temp_f12) {
            temp_f6 = temp_f12 - phi_f24;
            *arg1 = phi_s2;
            temp_f0 = (this->clockTime - phi_f24) / temp_f6;
            arg2->x = (temp_f0 * sp70.x) + phi_s1->x;
            arg2->y = (temp_f0 * sp70.y) + phi_s1->y;
            arg2->z = (temp_f0 * sp70.z) + phi_s1->z;
            return;
        }

        phi_s1 = phi_s0;
        phi_s0++;
        phi_f20 = temp_f14;
        phi_f24 = temp_f12;
    }

    *arg1 = temp_s5;
    arg2->x = this->pathPoints[temp_s5].x;
    arg2->y = this->pathPoints[temp_s5].y;
    arg2->z = this->pathPoints[temp_s5].z;
}

void func_80B43DD4(EnInvadepoh* this, s16 arg1, s16 arg2) {
    s32 pad;
    Vec3s* arr = &this->pathPoints[this->unk309];
    s32 pad2;
    Vec3f sp30;
    Vec3f sp24;

    if (this->unk309 != this->unk308) {
        Math_Vec3s_ToVec3f(&sp30, &arr[0]);
        Math_Vec3s_ToVec3f(&sp24, &arr[1]);
        Math_ScaledStepToS(&this->actor.shape.rot.y, Math_Vec3f_Yaw(&sp30, &sp24) + arg2, arg1);
    }
}

void func_80B43E6C(EnInvadepoh* this, s16 arg1, s16 arg2, s16 arg3) {
    s32 pad;
    Vec3s* arr = &this->pathPoints[this->unk309];
    s32 pad2;
    Vec3f sp38;
    Vec3f sp2C;

    if (this->unk309 != this->unk308) {
        Math_Vec3s_ToVec3f(&sp38, &arr[0]);
        Math_Vec3s_ToVec3f(&sp2C, &arr[1]);
        Math_SmoothStepToS(&this->actor.shape.rot.y, Math_Vec3f_Yaw(&sp38, &sp2C), arg1, arg2, arg3);
    }
}

void func_80B43F0C(EnInvadepoh* this) {
    s32 pad;
    Vec3s* arr = &this->pathPoints[this->unk309];
    s32 pad2;
    Vec3f sp28;
    Vec3f sp1C;

    Math_Vec3s_ToVec3f(&sp28, &arr[0]);
    Math_Vec3s_ToVec3f(&sp1C, &arr[1]);
    this->actor.shape.rot.y = Math_Vec3f_Yaw(&sp28, &sp1C);
}

f32 func_80B43F70(EnInvadepoh* this) {
    f32 new_var;
    s32 pad;
    Vec3f sp54;
    Vec3f sp48;
    Vec3s* temp_s0;
    f32 temp_f20;
    s32 i;
    s32 temp_s4;

    temp_s4 = this->unk308 + 1;
    temp_s0 = this->pathPoints;
    temp_f20 = 0.0f;
    Math_Vec3s_ToVec3f(&sp48, temp_s0);
    temp_s0++;
    for (i = 1; i < temp_s4; i++) {
        Math_Vec3f_Copy(&sp54, &sp48);
        Math_Vec3s_ToVec3f(&sp48, temp_s0);
        new_var = Math3D_Distance(&sp54, &sp48);
        temp_s0++;
        temp_f20 += new_var;
    }

    return temp_f20;
}

void func_80B44024(EnInvadepoh* this, GlobalContext* globalCtx) {
    Path* path;

    path = &globalCtx->setupPathList[(this->actor.params >> 8) & 0x7F];
    this->unk308 = path->count - 1;
    this->pathPoints = Lib_SegmentedToVirtual(path->points);
}

void func_80B4407C(EnInvadepoh* this, s32 arg1) {
    Math_Vec3s_ToVec3f(&this->actor.world.pos, &this->pathPoints[arg1]);
}

s32 func_80B440B8(EnInvadepoh* this, f32 arg1, f32 arg2) {
    Vec3s* temp_a3 = &this->pathPoints[this->unk309 + 1];
    Vec3s* sp48 = &this->pathPoints[this->unk309];
    f32 new_var;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    f32 temp_f12_2;
    s32 pad1;
    s32 pad2;
    s16 sp1E;

    if (this->unk309 >= this->unk308) {
        return false;
    }

    sp40 = temp_a3->x - sp48->x;
    sp3C = temp_a3->z - sp48->z;
    sp1E = Math_FAtan2F(sp3C, sp40);
    sp38 = Math_CosS(sp1E);
    sp34 = Math_SinS(sp1E);
    sp30 = this->actor.world.pos.x - sp48->x;
    sp2C = this->actor.world.pos.z - sp48->z;

    if ((arg1 - arg2) < fabsf((sp30 * sp38) - (sp2C * sp34))) {
        return false;
    }

    temp_f12_2 = (sp2C * sp38) + (sp30 * sp34);
    new_var = Math3D_XZLength(sp40, sp3C);

    if ((temp_f12_2 < 0.0f) || (new_var < temp_f12_2)) {
        return false;
    }

    return true;
}

s32 func_80B44234(EnInvadepoh* this, Vec3f* vec) {
    f32 distance;
    s8 temp_s3 = this->unk308;
    f32 min = FLT_MAX;
    Vec3f sp48;
    s32 i;
    s32 ret = 0;
    Vec3s* arr;

    for (i = 0, arr = this->pathPoints; i < temp_s3; i++, arr++) {
        Math_Vec3s_ToVec3f(&sp48, arr);
        distance = Math3D_DistanceSquared(&sp48, vec);
        if (distance < min) {
            min = distance;
            ret = i;
        }
    }

    return ret;
}

void func_80B442E4(EnInvadepoh* this) {
    s32 pad;
    s32 sp18 = gSaveContext.time;
    s32 temp_v1_2 = sp18 - func_80B43A24(this->actor.params & 7);

    if (D_80B4E940 == 1) {
        this->clockTime = 0.0f;
    } else if (D_80B4E940 == 2) {
        if (temp_v1_2 < 0) {
            this->clockTime = 0.0f;
        } else {
            this->clockTime = temp_v1_2 * 0.00027777779f;
            if (this->clockTime > 1.0f) {
                this->clockTime = 1.0f;
            }
        }
    }

    this->unk309 = func_80B43B80(this);
}

void func_80B443A0(EnInvadepoh* this) {
    f32 temp_f26;
    s8 temp_s5;
    Vec3s* phi_s1;
    Vec3f sp70;
    Vec3f sp64;
    f32* phi_s0;
    f32 phi_f20;
    s32 i;

    temp_s5 = this->unk308;
    temp_f26 = 1.0f / this->pathTotalDist;
    phi_f20 = 0.0f;
    phi_s1 = this->pathPoints;
    Math_Vec3s_ToVec3f(&sp64, phi_s1);
    phi_s1++;
    phi_s0 = this->unk37C;

    for (i = 1; i < temp_s5; i++, phi_s1++, phi_s0++) {
        Math_Vec3f_Copy(&sp70, &sp64);
        Math_Vec3s_ToVec3f(&sp64, phi_s1);
        phi_f20 += Math3D_Distance(&sp70, &sp64);
        *phi_s0 = phi_f20 * temp_f26;
        if (*phi_s0 < 0.0f) {
            *phi_s0 = 0.0f;
        } else if (*phi_s0 > 1.0f) {
            *phi_s0 = 1.0f;
        }
    }
}

void func_80B444BC(EnInvadepoh* this, GlobalContext* globalCtx) {
    func_80B44024(this, globalCtx);
    this->pathTotalDist = func_80B43F70(this);
    func_80B443A0(this);
}

void func_80B444F4(EnInvadepoh* this, GlobalContext* globalCtx) {
    func_80B44024(this, globalCtx);
}

void func_80B44514(EnInvadepoh* this) {
    this->unk309++;
    if (this->unk309 >= this->unk308) {
        this->unk309 = 0;
    }
}

void func_80B44540(EnInvadepoh* this, GlobalContext* globalCtx) {
    func_80B44024(this, globalCtx);
    this->pathTotalDist = func_80B43F70(this);
}

void func_80B44570(EnInvadepoh* this) {
    s32 temp_v0 = gSaveContext.time;

    if ((temp_v0 < CLOCK_TIME(2, 0)) || (temp_v0 >= CLOCK_TIME(6, 0))) {
        this->clockTime = 0.0f;
    } else if ((temp_v0 >= CLOCK_TIME(2, 15)) && (temp_v0 < CLOCK_TIME(6, 0))) {
        this->clockTime = 1.0f;
    } else {
        f32 new_var = (temp_v0 - 0x1555) * 0.0014641288f;
        this->clockTime = new_var;
        this->clockTime = CLAMP(this->clockTime, 0.0f, 1.0f);
    }
}

void func_80B44620(EnInvadepoh* this, GlobalContext* globalCtx) {
    func_80B44024(this, globalCtx);
}

void func_80B44640(EnInvadepoh* this) {
    if (this->unk309 < this->unk308) {
        this->unk309++;
    }
}

void func_80B44664(EnInvadepoh* this, GlobalContext* globalCtx) {
    func_80B44024(this, globalCtx);
    this->unk30A = 1;
}

void func_80B44690(EnInvadepoh* this) {
    this->unk309 += this->unk30A;
    if (this->unk309 >= this->unk308) {
        this->unk309 = 0;
    } else if (this->unk309 < 0) {
        this->unk309 = this->unk308 - 1;
    }
}

void func_80B446D0(EnInvadepoh* this, GlobalContext* globalCtx) {
    func_80B44024(this, globalCtx);
    this->pathTotalDist = func_80B43F70(this);
}

void func_80B44700(EnInvadepoh* this) {
    s32 currentTime = gSaveContext.time;
    s32 new_var4 = 0xFFFF2AAB;

    if ((currentTime < CLOCK_TIME(20, 0)) && (currentTime >= CLOCK_TIME(6, 0))) {
        this->clockTime = 0.0f;
    } else if ((currentTime > 0xD7E0) || (currentTime < CLOCK_TIME(6, 0))) {
        this->clockTime = 1.0f;
    } else {
        f32 new_var = 0.00153374229558f;
        this->clockTime = (currentTime + new_var4) * new_var;
        this->clockTime = CLAMP(this->clockTime, 0.0f, 1.0f);
    }
}

void func_80B447C0(EnInvadepoh* this, GlobalContext* globalCtx) {
    s32 pad1;
    Vec3s* sp60;
    s32 pad2;
    Vec3f sp50;
    Vec3f sp44;
    f32 sp40;
    f32 sp3C;
    s32 pad3;
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    f32 phi_f2;

    sp40 = this->actor.world.pos.y;
    sp60 = &this->pathPoints[this->unk309];
    if (this->unk309 <= 0) {
        sp3C = 0.0f;
    } else {
        sp3C = this->unk37C[this->unk309 - 1];
    }

    if (this->unk309 < (this->unk308 - 1)) {
        phi_f2 = this->unk37C[this->unk309];
    } else {
        phi_f2 = 1.0f;
    }

    if ((phi_f2 - sp3C) < 0.001f) {
        Math_Vec3s_ToVec3f(&this->curPathPos, sp60);
    } else {
        sp34 = this->clockTime - sp3C;
        sp30 = phi_f2 - this->clockTime;
        sp2C = 1.0f / (phi_f2 - sp3C);
        Math_Vec3s_ToVec3f(&sp50, &sp60[0]);
        Math_Vec3s_ToVec3f(&sp44, &sp60[1]);
        this->curPathPos.x = ((sp50.x * sp30) + (sp44.x * sp34)) * sp2C;
        this->curPathPos.y = ((sp50.y * sp30) + (sp44.y * sp34)) * sp2C;
        this->curPathPos.z = ((sp50.z * sp30) + (sp44.z * sp34)) * sp2C;
    }

    Math_Vec3f_Copy(&this->actor.world, &this->curPathPos);
    func_800B4AEC(globalCtx, this, 0.0f);
    if (this->actor.floorHeight > -31999.0f) {
        if (sp40 < this->actor.floorHeight) {
            if (this->actor.velocity.y < 0.0f) {
                this->actor.velocity.y = 0.0f;
            } else {
                this->actor.velocity.y += 2.0f;
                this->actor.velocity.y = CLAMP_MAX(this->actor.velocity.y, 30.0f);
            }
            this->actor.world.pos.y = this->actor.velocity.y + sp40;
            if (this->actor.world.pos.y > this->actor.floorHeight) {
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

void func_80B44A90(EnInvadepoh* this, GlobalContext* globalCtx) {
    if (this->actor.bgCheckFlags & 1) {
        this->actor.velocity.y *= 0.3f;
        this->actor.speedXZ *= 0.8f;
    } else if ((this->actor.bgCheckFlags & 8) != 0) {
        this->actor.velocity.y *= 0.8f;
        this->actor.speedXZ *= 0.3f;
    } else {
        this->actor.velocity.y *= 0.8f;
        this->actor.speedXZ *= 0.8f;
    }
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 30.0f, 40.0f, 0.0f, 5);
}

void func_80B44B78(EnInvadepoh* this) {
}

s32 func_80B44B84(EnInvadepoh* this, GlobalContext* globalCtx, f32 speed, f32 arg3) {
    s32 pad;
    Vec3s* temp_v0_2 = &this->pathPoints[this->unk309];
    s32 temp_v0;

    temp_v0_2++;
    temp_v0 = func_80B450C0(&this->actor.world.pos.x, &this->actor.world.pos.z, temp_v0_2->x, temp_v0_2->z, speed);
    func_800B4AEC(globalCtx, &this->actor, arg3);
    func_80B4516C(this);
    return temp_v0;
}

void func_80B44C24(EnInvadepoh* this, GlobalContext* globalCtx) {
    s32 pad;
    f32 temp = this->actor.world.pos.y;

    func_80B43BC8(this, &this->unk309, &this->actor.world.pos);
    this->actor.world.pos.y = temp;
    func_800B4AEC(globalCtx, &this->actor, 50.0f);
    func_80B4516C(this);
}

s32 func_80B44C80(EnInvadepoh* this, GlobalContext* globalCtx) {
    s32 pad[6];
    Vec3s* temp_a2;
    f32 temp_f0;
    Vec3f sp6C;
    Vec3f sp60;
    f32 temp_f0_2;
    Vec3s* temp_v0_2;
    f32 temp_f0_3;
    f32 temp_f12;
    f32 temp_f2;
    f32 temp_f14;
    f32 sp44;
    s32 sp40;
    s32 temp_v1;
    s32 phi_v0;

    temp_a2 = &this->pathPoints[this->unk309];
    sp40 = 0;
    temp_v1 = this->unk309 + this->unk30A;
    if (temp_v1 >= this->unk308) {
        temp_v1 = 0;
    } else if (temp_v1 < 0) {
        temp_v1 = this->unk308 - 1;
    }

    temp_v0_2 = &this->pathPoints[temp_v1];

    temp_f0 = temp_a2->x;
    temp_f2 = temp_a2->z;
    temp_f12 = temp_v0_2->x;
    temp_f14 = temp_v0_2->z;
    sp6C.x = temp_f12 - temp_f0;
    sp6C.y = 0.0f;
    sp6C.z = temp_f14 - temp_f2;
    sp60.x = temp_f12 - this->actor.world.pos.x;
    sp60.y = 0.0f;
    sp60.z = temp_f14 - this->actor.world.pos.z;
    temp_f0_3 = temp_f0 - this->actor.world.pos.x;
    temp_f0_2 = temp_f2 - this->actor.world.pos.z;

    if (this->actor.speedXZ > 0.0f) {
        if (Math3D_AngleBetweenVectors(&sp6C, &sp60, &sp44) != 0) {
            sp40 = 1;
        } else if (sp44 <= 0.0f) {
            sp40 = 1;
        }
    }

    Math_SmoothStepToS(&this->actor.world.rot.y,
                       Math_FAtan2F(((sp60.z + temp_f0_2) * 0.9f) + sp6C.z, ((sp60.x + temp_f0_3) * 0.9f) + sp6C.x), 4,
                       0xFA0, 0x64);
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
    if (func_80B440B8(this, 50.0f, 15.0f)) {
        phi_v0 = 4;
    } else {
        phi_v0 = 5;
    }

    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 30.0f, 15.0f, 0.0f, phi_v0);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.world.rot.y, 3, 0x1F40, 0x64);
    return sp40;
}

void func_80B44E90(EnInvadepoh* this, GlobalContext* globalCtx) {
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 30.0f, 15.0f, 0.0f, 5);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.world.rot.y, 3, 0x1F40, 0x64);
}

void func_80B44EFC(EnInvadepoh* this, GlobalContext* globalCtx) {
    s32 pad;
    f32 temp = this->actor.world.pos.y;

    func_80B43BC8(this, &this->unk309, &this->actor.world.pos);
    this->actor.world.pos.y = temp;
    func_800B4AEC(globalCtx, &this->actor, 50.0f);
    func_80B4516C(this);
}

void func_80B44F58(void) {
    s32 i;
    Gfx** iter;

    if (D_80B4E968 == 0) {
        D_80B4E968 = 1;
        for (i = 0, iter = D_80B4E944; i < ARRAY_COUNT(D_80B4E944); i++, iter++) {
            *iter = Lib_SegmentedToVirtual(*iter);
        }

        for (i = 0, iter = D_80B4E958; i < ARRAY_COUNT(D_80B4E958); i++, iter++) {
            *iter = Lib_SegmentedToVirtual(*iter);
        }
    }
}

void func_80B44FEC(void) {
    s32 i;
    Gfx** iter;

    if (D_80B4E994 == 0) {
        D_80B4E994 = 1;
        for (i = 0, iter = D_80B4E96C; i < ARRAY_COUNT(D_80B4E96C); i++, iter++) {
            *iter = Lib_SegmentedToVirtual(*iter);
        }

        for (i = 0, iter = D_80B4E984; i < ARRAY_COUNT(D_80B4E984); i++, iter++) {
            *iter = Lib_SegmentedToVirtual(*iter);
        }
    }
}

void func_80B45080(void) {
    D_80B50400 = Lib_SegmentedToVirtual(&D_06000560);
    D_80B503FC = Lib_SegmentedToVirtual(&D_06000550);
}

s32 func_80B450C0(f32* x, f32* z, f32 otherX, f32 otherZ, f32 speed) {
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f0;

    temp_f12 = otherX - *x;
    temp_f14 = otherZ - *z;
    temp_f0 = Math3D_XZLength(temp_f12, temp_f14);
    if (speed < temp_f0) {
        f32 temp_f2 = speed / temp_f0;
        *x += (temp_f2 * temp_f12);
        *z += (temp_f2 * temp_f14);
        return false;
    } else {
        *x = otherX;
        *z = otherZ;
        return true;
    }
}

s32 func_80B4516C(EnInvadepoh* this) {
    if (this->actor.floorHeight > -31999.0f) {
        this->actor.world.pos.y = this->actor.floorHeight;
        return true;
    }
    return false;
}

void func_80B451A0(EnInvadepoh* this, GlobalContext* globalCtx) {
    s32 temp_v0;
    s32 temp_v0_2;
    s32 i;
    s32 phi_s1_3;

    if (D_80B4E940 == 0) {
        if (CURRENT_DAY <= 0) {
            D_80B4E940 = 1;
        } else if (CURRENT_DAY == 1) {
            temp_v0 = gSaveContext.time;
            if ((temp_v0 < CLOCK_TIME(2, 30)) || (temp_v0 >= CLOCK_TIME(6, 0))) {
                D_80B4E940 = 1;
            } else if (temp_v0 < 0x3800) {
                phi_s1_3 = 0x3800;
                for (i = 0; i < this->unk379; i++) {
                    temp_v0_2 = func_80B43A24(i);
                    if (temp_v0_2 < phi_s1_3) {
                        phi_s1_3 = temp_v0_2;
                    }
                }

                if (temp_v0 < (phi_s1_3 + 0xE11)) {
                    D_80B4E940 = 2;
                }

                if (i) {} // required
            }
        }

        if (D_80B4E940 == 0) {
            if (gSaveContext.weekEventReg[22] & 1) {
                D_80B4E940 = 3;
            } else {
                D_80B4E940 = 4;
            }
        }
    }
}

void func_80B452EC(EnInvadepoh* this, GlobalContext* globalCtx) {
    s32 phi_s2;
    s32 i;

    phi_s2 = (this->actor.params >> 8) & 0x7F;

    for (i = 0; i < this->unk379; i++) {
        D_80B50320[i] =
            Actor_Spawn(&globalCtx->actorCtx, globalCtx, 0x200, this->actor.world.pos.x, this->actor.world.pos.y,
                        this->actor.world.pos.z, 0, 0, 0, (i & 7) | ((phi_s2 << 8) & 0x7F00) | 0x10);
        if (phi_s2 != 0xFF) {
            Path* path = &globalCtx->setupPathList[phi_s2];
            phi_s2 = path->unk1;
        }
    }
}

void func_80B453F4(EnInvadepoh* this, GlobalContext* globalCtx, s32 arg2) {
    Actor_SpawnWithParent(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_EN_INVADEPOH, this->actor.home.pos.x,
                          this->actor.home.pos.y, this->actor.home.pos.z, 0, 0, 0, (arg2 & 7) | 0x20);
}

void func_80B45460(EnInvadepoh* this, GlobalContext* globalCtx) {
    Actor_SpawnWithParent(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_EN_INVADEPOH, this->actor.home.pos.x,
                          this->actor.home.pos.y, this->actor.home.pos.z, 0, 0, 0, 0x40);
}

void func_80B454BC(EnInvadepoh* this, GlobalContext* globalCtx) {
    D_80B503F0 = Actor_Spawn(&globalCtx->actorCtx, globalCtx, 512, this->actor.world.pos.x, this->actor.world.pos.y,
                             this->actor.world.pos.z, 0, 0, 0, 0x60);
}

void func_80B45518(Vec3f* vec) {
    MtxF* sysMatrix = SysMatrix_GetCurrentState();

    sysMatrix->wx = vec->x;
    sysMatrix->wy = vec->y;
    sysMatrix->wz = vec->z;
}

s32 func_80B45550(EnInvadepoh* this, GlobalContext* globalCtx, f32 arg2, s32 arg3) {
    s32 pad;
    Actor* actorIterator = globalCtx->actorCtx.actorList[ACTORCAT_DOOR].first;
    s32 retVal = false;

    while (actorIterator) {
        if ((actorIterator->id == ACTOR_EN_DOOR) && (actorIterator->update != NULL) &&
            (actorIterator->room == this->actor.room) &&
            Math3D_DistanceSquared(&actorIterator->world.pos, &this->actor.world.pos) < arg2) {
            ((EnDoor*)actorIterator)->unk1A7 = arg3;
            retVal = true;
            break;
        }
        actorIterator = actorIterator->next;
    }
    return retVal;
}

void func_80B4560C(EnInvadepoh* this, GlobalContext* globalCtx, u16 arg2) {
    this->textId = arg2;
    func_801518B0(globalCtx, arg2 & 0xFFFF, &this->actor);
}

void func_80B45648(EnInvadepoh* this) {
    s32 i;
    s16 cs = this->actor.cutscene;

    for (i = 0; i < 3; i++) {
        D_80B50404[i] = cs;
        cs = ActorCutscene_GetAdditionalCutscene(cs);
    }
}

s32 func_80B456A8(GlobalContext* globalCtx, Vec3f* vec) {
    Vec3f multDest;
    f32 wDest;

    func_800B4EDC(globalCtx, vec, &multDest, &wDest);
    if (((multDest.z > 1.0f) && (fabsf(multDest.x * wDest) < 1.0f)) && (fabsf(multDest.y * wDest) < 1.0f)) {
        s32 wX = (multDest.x * wDest * 160.0f) + 160.0f;
        s32 wY = (multDest.y * wDest * -120.0f) + 120.0f;
        s32 wZ = (s32)(multDest.z * wDest * 16352.0f) + 0x3FE0;
        s32 zBuf = func_80178A94(wX, wY);
        if (wZ < zBuf) {
            return true;
        }
    }

    return false;
}
 
void func_80B457A0(EnInvadepoh* this) {
    f32 distanceSquared;
    f32 phi_f20;
    s32 i;
    s32 phi_s5;

    phi_f20 = FLT_MAX;
    phi_s5 = -1;

    for (i = 0; i < this->unk379; i++) {
        if (((EnInvadepoh*)D_80B50320[i] != NULL) && (((EnInvadepoh*)D_80B50320[i])->drawAlien != 0)) {
            distanceSquared = Math3D_DistanceSquared(&D_80B50320[i]->world.pos, &this->actor.world.pos);
            if (distanceSquared < phi_f20) {
                phi_f20 = distanceSquared;
                phi_s5 = i;
            }
        }
        D_80B50340[i] &= ~2;
    }

    D_80B50348 = 0;
    if (phi_f20 <= SQ(2000.0f)) {
        D_80B50340[phi_s5] |= 2;
        if (phi_f20 <= SQ(340.0f)) {
            D_80B50348 = 1;
        }
    }
}

Actor* func_80B458D8(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if ((D_80B50340[i] & 2)) {
            return D_80B50320[i];
        }
    }

    return NULL;
}

s8 func_80B45980(unkstruct_invadepoh_1* arg0, s32 arg1) {
    f32 rand = Rand_ZeroOne();
    s32 i;

    arg1--;
    for (i = 0; i < arg1; i++) {
    dummy:;
        if (arg0[i].unk04 >= rand) {
            break;
        }
    }

    return (arg0 + i)->unk00;
}

void func_80B459E8(EnInvadePohStruct* s, unkstruct_invadepoh_4* u) {
    s->unk4 = u->unk00;
    s->unk8 = u;
    s->unkE = 0;
    s->unkF = *u->unk04->unk00;
    if (s->unk4 == 2) {
        s->unkC = Rand_S16Offset(u->unk10, u->unk12);
    }
}

// ISMATCHING
#ifdef NON_MATCHING
// matching, but has a warning because I haven't decoded the data well enough
// yet. The first temp is not the correct type.
void func_80B45A4C(EnInvadePohStruct* s, s32* u) {
    unkstruct_invadepoh_3* new_var = s->unk8;
    unkstruct_invadepoh_0* temp_v1 = new_var->unk4;

    if (s->unkE < (temp_v1->unk04 - 1)) {
        s->unkE++;
        s->unkF = temp_v1->unk00[s->unkE];
    }
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_0x80B439B0/func_80B45A4C.asm")
#endif

void func_80B45A94(EnInvadePohStruct* s, s32* u) {
    unkstruct_invadepoh_0* temp_v1;
    unkstruct_invadepoh_1* temp_a0;

    temp_v1 = s->unk8->unk04;
    if (s->unkE < (temp_v1->unk04 - 1)) {
        s->unkE++;
        s->unkF = temp_v1->unk00[s->unkE];
    } else {
        func_80B459E8(s, u[func_80B45980(s->unk8->unk0C, s->unk8->unk08)]);
    }
}

void func_80B45B1C(EnInvadePohStruct* s, s32* u) {
    unkstruct_invadepoh_0* temp_v1;
    unkstruct_invadepoh_1* temp_a0;

    temp_v1 = s->unk8->unk04;
    if (s->unkE < (temp_v1->unk04 - 1)) {
        s->unkE++;
        s->unkF = temp_v1->unk00[s->unkE];
    } else if (s->unkC > 0) {
        s->unkC--;
    } else {
        func_80B459E8(s, u[func_80B45980(s->unk8->unk0C, s->unk8->unk08)]);
    }
}

void func_80B45BB8(EnInvadePohStruct* s) {
    if ((s->unk0 != 0) && (s->unk8 != 0)) {
        D_80B4EC0C[s->unk4](s, s->unk0);
    }
}

// cursed
#ifdef NON_EQUIVALENT
void func_80B45C04(AlienBehaviorInfo* substruct, unkstruct_invadepoh_union* arg1, s32 arg2,
                   unkstruct_invadepoh_union* arg3, s32 arg4, Vec3s* arg5, s16 arg6, f32 arg7, f32 arg8, f32 arg9) {
    unkstruct_invadepoh_4* temp_v0;
    unkstruct_invadepoh_4* temp_v0_2;

    Math_Vec3s_Copy(&substruct->unk26, arg5);
    substruct->unk2C = arg6;
    substruct->unk30 = arg7;
    substruct->unk38 = arg8;
    substruct->unk3C = arg9;
    if (arg1 != 0) {
        temp_v0 = &arg1[arg2].unk_struct_4_elem;
        substruct->unk0.unk4 = temp_v0->unk00;
        substruct->unk0.unk0 = arg1;
        substruct->unk0.unk8 = temp_v0;
        substruct->unk0.unkC = 0;
        substruct->unk0.unkE = 0;
        substruct->unk0.unkF = *temp_v0->unk04->unk00;
    }
    if (arg3 != 0) {
        temp_v0_2 = &arg3[arg4].unk_struct_4_elem;
        substruct->unk10.unk4 = temp_v0_2->unk00;
        substruct->unk10.unk0 = arg3;
        substruct->unk10.unk8 = temp_v0_2;
        substruct->unk10.unkC = 0;
        substruct->unk10.unkE = 0;
        substruct->unk10.unkF = *temp_v0_2->unk04->unk00;
    }
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Invadepoh_0x80B439B0/func_80B45C04.asm")
#endif
void func_80B45C04(AlienBehaviorInfo* substruct, unkstruct_invadepoh_union* arg1, s32 arg2,
                   unkstruct_invadepoh_union* arg3, s32 arg4, Vec3s* arg5, s16 arg6, f32 arg7, f32 arg8, f32 arg9);

void func_80B45CE0(AlienBehaviorInfo* substruct) {
    Vec3f sp3C;
    Vec3s sp34;
    s16 step;

    sp34.x = substruct->unk26.x - substruct->unk20.x;
    sp34.y = substruct->unk26.y - substruct->unk20.y;
    sp34.z = substruct->unk26.z - substruct->unk20.z;
    Math_Vec3s_ToVec3f(&sp3C, &sp34);
    Math_Vec3f_Scale(&sp3C, substruct->unk30);
    Math_Vec3f_ToVec3s(&sp34, &sp3C);
    sp34.x = ABS(sp34.x);
    sp34.y = ABS(sp34.y);
    sp34.z = ABS(sp34.z);
    sp34.x = CLAMP_MAX(sp34.x, substruct->unk2C);
    sp34.y = CLAMP_MAX(sp34.y, substruct->unk2C);
    sp34.z = CLAMP_MAX(sp34.z, substruct->unk2C);
    Math_ScaledStepToS(&substruct->unk20.x, substruct->unk26.x, sp34.x);
    Math_ScaledStepToS(&substruct->unk20.y, substruct->unk26.y, sp34.y);
    Math_ScaledStepToS(&substruct->unk20.z, substruct->unk26.z, sp34.z);
    Math_StepToF(&substruct->unk34, substruct->unk38, substruct->unk3C);

    if (substruct->unk40 != substruct->unk42) {
        step = substruct->unk42 - substruct->unk40;
        step *= substruct->unk44;
        step = ABS(step);
        step = CLAMP(step, 0x64, substruct->unk48);
        Math_ScaledStepToS(&substruct->unk40, substruct->unk42, step);
    }
    func_80B45BB8(&substruct->unk0);
    func_80B45BB8(&substruct->unk10);
}

void func_80B45EC8(EnInvadepoh* this, GlobalContext* globalCtx, s32 arg2) {
    s16 phi_s0 = 0;
    Vec3f spA8;
    Vec3f sp9C;
    Vec3f sp90;
    f32 temp_f20;
    s32 i;

    for (i = 0; i < arg2; i++) {
        phi_s0 += (s16)(65536.0f / arg2);

        temp_f20 = (Rand_ZeroOne() * 0.5f) + 0.5f;
        spA8.x = Math_SinS(phi_s0) * temp_f20;
        spA8.z = Math_CosS(phi_s0) * temp_f20;

        sp9C.x = ((Rand_ZeroOne() * 16.0f) + (spA8.x * 30.0f)) - 8.0f;
        sp9C.y = -8.0f;
        sp9C.z = ((Rand_ZeroOne() * 16.0f) + (spA8.z * 30.0f)) - 8.0f;

        sp90.x = sp9C.x * -0.025f;
        sp90.y = sp9C.y * -0.025f;
        sp90.z = sp9C.z * -0.025f;

        spA8.x = (spA8.x * 100.0f) + this->actor.world.pos.x;
        spA8.y = ((Rand_ZeroOne() * 180.0f) + this->actor.world.pos.y) - 90.0f;
        spA8.z = (spA8.z * 100.0f) + this->actor.world.pos.z;

        EffectSsKiraKira_SpawnDispersed(globalCtx, &spA8, &sp9C, &sp90, &D_80B4EC18, &D_80B4EC1C, 6000, -0x28);
    }
}

s32 func_80B46118(Vec3f* actorPos) {
    unkStruct_80B50350* phi_v1;
    s32 i;

    for (phi_v1 = D_80B50350, i = 0; i < 10; phi_v1++, i++) {
        if (phi_v1->unk1 <= 0) {
            phi_v1->unk0 = 0;
            phi_v1->unk1 = 0x28;
            Math_Vec3f_Copy(&phi_v1->unk4, actorPos);
            phi_v1->unk2 = 0;
            return true;
        }
    }
    return false;
}

void func_80B46184(unkStruct_80B50350* unkStruct) {
    if (unkStruct->unk1 > 0x14) {
        if (unkStruct->unk2 < 0x7D) {
            unkStruct->unk2 += 0xA;
        } else {
            unkStruct->unk2 = 0x87;
        }
    } else if (unkStruct->unk2 > 0xD) {
        unkStruct->unk2 -= 0xD;

    } else {
        unkStruct->unk2 = 0;
    }
}

s32 func_80B461DC(void) {
    s32 phi_s4 = false;
    unkStruct_80B50350* phi_s0;
    s32 i;

    for (phi_s0 = D_80B50350, i = 0; i < 10; phi_s0++, i++) {
        if (phi_s0->unk1 > 0) {
            D_80B4EC20[phi_s0->unk0](phi_s0);
            phi_s0->unk1--;
            phi_s4 = true;
        }
    }
    return phi_s4;
}

void func_80B4627C(EnInvadepoh* this, GlobalContext* globalCtx) {
    s32 invadepohType;
    s32 i;

    this->actor.flags |= 0x20;
    invadepohType = (this->actor.params >> 8) & 0x7F;

    for (i = 1; i < 8; i++) {
        Path* path = &globalCtx->setupPathList[invadepohType];
        invadepohType = path->unk1;
        if (invadepohType == 0xFF) {
            break;
        }
    }

    this->unk379 = i;
    func_80B451A0(this, globalCtx);
    func_80B45648(this);
    func_800BC154(globalCtx, &globalCtx->actorCtx, &this->actor, ACTORCAT_SWITCH);

    if (D_80B4E940 == 1) {
        func_80B46DA8(this);
    } else if (D_80B4E940 == 2) {
        if (gSaveContext.time < CLOCK_TIME(2, 31)) {
            func_80B46DA8(this);
        } else {
            func_80B454BC(this, globalCtx);
            func_80B452EC(this, globalCtx);
            func_801A89A8(0x800D);
            func_80B46F88(this);
        }
    } else if (D_80B4E940 == 3) {
        if (gSaveContext.entranceIndex == 0x6460) {
            func_80B471C0(this);

        } else if (gSaveContext.entranceIndex == 0x6470) {
            func_80B47248(this);
        } else {
            func_80B47248(this);
        }
    } else if (D_80B4E940 == 4) {
        func_80B47304(this);
    }
}

void func_80B46414(EnInvadepoh* this, GlobalContext* globalCtx) {
    s32 pad;

    Actor_ProcessInitChain(&this->actor, D_80B4EC24);
    Collider_InitCylinder(globalCtx, &this->collider);
    ActorShape_Init(&this->actor.shape, 6800.0f, func_800B4088, 150.0f);
    this->actor.shape.shadowAlpha = 0x8C;
    this->actor.flags = 0x80001010;
    if (((this->actor.params >> 4) & 0xF) == 13) {
        this->actor.update = func_80B4D670;
        this->actor.world.pos.y = this->actor.home.pos.y + 150.0f;
    } else {
        this->actor.update = func_80B47BAC;
        Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &D_80B4E8B0);
        this->actor.colChkInfo.mass = 0x28;
    }
    this->bankIndex = Object_GetIndex(&globalCtx->objectCtx, OBJECT_UCH);
    if (this->bankIndex < 0) {
        Actor_MarkForDeath(&this->actor);
    }
}

void func_80B46520(EnInvadepoh* this, GlobalContext* globalCtx) {
    Actor_ProcessInitChain(&this->actor, D_80B4EC34);
    this->actor.update = func_80B47FA8;
    Actor_SpawnWithParent(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_EN_INVADEPOH, 0.0f, 0.0f, 0.0f, 0, 0, 0,
                          0x30);
    this->bankIndex = Object_GetIndex(&globalCtx->objectCtx, OBJECT_COW);
    if (this->bankIndex < 0) {
        Actor_MarkForDeath(&this->actor);
    }
}

void func_80B465CC(EnInvadepoh* this, GlobalContext* globalCtx) {
    Actor_ProcessInitChain(&this->actor, D_80B4EC44);
    this->actor.update = func_80B481C4;
    this->bankIndex = Object_GetIndex(&globalCtx->objectCtx, OBJECT_COW);
    if (this->bankIndex < 0) {
        Actor_MarkForDeath(&this->actor);
    }
}

void func_80B46644(EnInvadepoh* this, GlobalContext* globalCtx) {
    s32 pad;
    s32 temp;

    temp = (this->actor.params >> 4) & 0xF;

    Actor_ProcessInitChain(&this->actor, D_80B4EC54);

    this->actor.targetMode = (temp == 7 || temp == 0xC) ? 3 : 6;

    func_800BC154(globalCtx, &globalCtx->actorCtx, &this->actor, ACTORCAT_NPC);
    Collider_InitCylinder(globalCtx, &this->collider);
    if (temp != 4) {
        ActorShape_Init(&this->actor.shape, 0, func_800B3FC0, 18.0f);
        Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &D_80B4E8DC);
        this->actor.colChkInfo.mass = 0xFF;
    }
    if (temp == 4) {
        this->actor.update = func_80B48620;
    } else if (temp == 5) {
        this->actor.update = func_80B48FB0;
        this->actor.flags = 0x19;
    } else if (temp == 7) {
        this->actor.update = func_80B49F88;
    } else if (temp == 8) {
        this->actor.update = func_80B4A9C8;
    } else if (temp == 9) {
        this->actor.update = func_80B4B0C4;
    } else {
        this->actor.update = func_80B4CE54;
    }

    this->bankIndex = Object_GetIndex(&globalCtx->objectCtx, OBJECT_MA1);
    if (this->bankIndex < 0) {
        Actor_MarkForDeath(&this->actor);
    }
    if (temp == 5) {
        if (gSaveContext.weekEventReg[0x16] & 0x1) {
            Actor_MarkForDeath(&this->actor);
            return;
        }
    } else if (temp == 7) {
        if (gSaveContext.time < 0x4000 && gSaveContext.time >= 0x1800) {
            Actor_MarkForDeath(&this->actor);
            return;
        }
    } else if (temp != 8) {
        if (temp == 9) {
            if (gSaveContext.entranceIndex != 0x6460) {
                Actor_MarkForDeath(&this->actor);
                return;
            }
        } else if (temp == 0xC) {
            if (!(gSaveContext.weekEventReg[0x16] & 0x1)) {
                Actor_MarkForDeath(&this->actor);
            }
            D_80B503F4 = &this->actor;
        }
    }
}

void func_80B468B4(EnInvadepoh* this, GlobalContext* globalCtx) {
    Actor_ProcessInitChain(&this->actor, D_80B4EC68);
    this->actor.update = func_80B49B1C;
    this->actor.draw = func_80B4E3F0;
    func_800BC154(globalCtx, &globalCtx->actorCtx, &this->actor, ACTORCAT_NPC);
    if (D_80B4E940 == 1 || gSaveContext.time < 0x1AD8) {
        this->actor.world.pos.x += D_80B4E934.x; // this is a vec3f, the data is just being weird
        this->actor.world.pos.y += D_80B4E934.y + 3000.0f;
        this->actor.world.pos.z += D_80B4E934.z;
        func_80B491EC(this);
        return;
    }
    if (D_80B4E940 == 2) {
        this->actor.world.pos.y += 1500.0f;
        func_80B49628(this);
        return;
    }
    Actor_MarkForDeath(&this->actor);
}

void func_80B469C4(EnInvadepoh* this, GlobalContext* globalCtx) {
    s32 pad;

    Actor_ProcessInitChain(&this->actor, D_80B4EC80);
    this->actor.update = func_80B4B8BC;
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &D_80B4E908);
    this->actor.colChkInfo.mass = 0x50;
    ActorShape_Init(&this->actor.shape, 0, func_800B3FC0, 24.0f);
    this->bankIndex = Object_GetIndex(&globalCtx->objectCtx, OBJECT_DOG);
    if (this->bankIndex < 0) {
        Actor_MarkForDeath(&this->actor);
    }
}

void func_80B46A80(EnInvadepoh* this, GlobalContext* globalCtx) {
    s32 pad;

    Actor_ProcessInitChain(&this->actor, D_80B4EC98);
    this->actor.update = func_80B4C3A0;
    func_800BC154(globalCtx, &globalCtx->actorCtx, &this->actor, ACTORCAT_NPC);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &D_80B4E8DC);
    this->actor.colChkInfo.mass = 0xFE;
    ActorShape_Init(&this->actor.shape, 0, func_800B3FC0, 18.0f);
    this->bankIndex = Object_GetIndex(&globalCtx->objectCtx, OBJECT_MA2);
    if (this->bankIndex < 0) {
        Actor_MarkForDeath(&this->actor);
    }
    if (!(gSaveContext.weekEventReg[0x16] & 1)) {
        Actor_MarkForDeath(&this->actor);
    }
    D_80B503F8 = &this->actor;
}

void EnInvadepoh_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnInvadepoh* this = THIS;

    D_80B4ECB0[this->actor.params >> 4 & 0xF](this, globalCtx);
}

void func_80B46BB0(EnInvadepoh* this, GlobalContext* globalCtx) {
}

void func_80B46BC0(EnInvadepoh* this, GlobalContext* globalCtx) {
    s32 pad;
    s32 invadepohType = this->actor.params & 7;

    Collider_DestroyCylinder(globalCtx, &this->collider);
    D_80B50320[invadepohType] = 0;
}

void func_80B46C08(EnInvadepoh* this, GlobalContext* globalCtx) {
    if (this->actor.parent != NULL) {
        this->actor.parent->child = NULL;
    }

    if (this->actor.child != NULL) {
        this->actor.child->parent = NULL;
    }
}

void func_80B46C34(EnInvadepoh* this, GlobalContext* globalCtx) {
    if (this->actor.parent != NULL) {
        this->actor.parent->child = NULL;
    }
}

void func_80B46C50(EnInvadepoh* this, GlobalContext* globalCtx) {
    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void func_80B46C7C(EnInvadepoh* this, GlobalContext* globalCtx) {
    D_80B503F0 = 0;
}

void func_80B46C94(EnInvadepoh* this, GlobalContext* globalCtx) {
    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void func_80B46CC0(EnInvadepoh* this, GlobalContext* globalCtx) {
    Collider_DestroyCylinder(globalCtx, &this->collider);
    D_80B503F8 = 0;
}

void func_80B46CF4(EnInvadepoh* this, GlobalContext* globalCtx) {
    Collider_DestroyCylinder(globalCtx, &this->collider);
    D_80B503F4 = 0;
}

void func_80B46D28(EnInvadepoh* this, GlobalContext* globalCtx) {
    Collider_DestroyCylinder(globalCtx, &this->collider);
    if (!this) {} // required to match
    if (this->actor.child != NULL) {
        this->actor.child->parent = NULL;
    }
}

void EnInvadepoh_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnInvadepoh* this = THIS;

    D_80B4ECE8[this->actor.params >> 4 & 0xF](this, globalCtx);
}

void func_80B46DA8(EnInvadepoh* this) {
    D_80B4E940 = 1;
    this->actionFunc = func_80B46DC8;
}

void func_80B46DC8(EnInvadepoh* this, GlobalContext* globalCtx) {
    if ((gSaveContext.time < CLOCK_TIME(6, 0)) && (gSaveContext.time >= CLOCK_TIME(2, 30))) {
        func_80B454BC(this, globalCtx);
        func_80B452EC(this, globalCtx);
        func_80B46E20(this);
    }
}

void func_80B46E20(EnInvadepoh* this) {
    D_80B4E940 = 2;
    this->actionTimer = 2;
    this->actionFunc = func_80B46E44;
}

void func_80B46E44(EnInvadepoh* this, GlobalContext* globalCtx) {
    if (this->actionTimer > 0) {
        this->actionTimer--;
        return;
    }

    if (ActorCutscene_GetCanPlayNext(D_80B50404[0])) {
        ActorCutscene_StartAndSetUnkLinkFields(D_80B50404[0], &this->actor);
        func_80B46EC0(this);
    } else {
        ActorCutscene_SetIntentToPlay(D_80B50404[0]);
    }
}

void func_80B46EC0(EnInvadepoh* this) {
    D_80B4E940 = 2;
    this->actionTimer = 0xA0;
    this->actionFunc = func_80B46EE8;
}

void func_80B46EE8(EnInvadepoh* this, GlobalContext* globalCtx) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (this->actionTimer == D_80B4ED20[i]) {
            D_80B50340[i] |= 1;
        }
    }

    this->actionTimer--;
    if (this->actionTimer <= 0) {
        ActorCutscene_Stop(D_80B50404[0]);
        func_801A89A8(0x800D);
        func_80B46F88(this);
    }
}

void func_80B46F88(EnInvadepoh* this) {
    D_80B4E940 = 2;
    this->actionFunc = func_80B46FA8;
}

void func_80B46FA8(EnInvadepoh* this, GlobalContext* globalCtx) {
    s32 i;

    if ((gSaveContext.time < 0x4000) && (gSaveContext.time >= 0x3800)) {
        gSaveContext.weekEventReg[22] |= 1;
        func_80B47064(this);
    } else {
        func_80B457A0(this);
        for (i = 0; i < this->unk379; i++) {
            if ((D_80B50320[i] != NULL) && (((EnInvadepoh*)D_80B50320[i])->unk38A != 0)) {
                func_80B47278(this);
                break;
            }
        }
    }
}

void func_80B47064(EnInvadepoh* this) {
    D_80B4E940 = 3;
    this->actionFunc = func_80B47084;
}

void func_80B47084(EnInvadepoh* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(D_80B50404[1])) {
        ActorCutscene_StartAndSetUnkLinkFields(D_80B50404[1], &this->actor);
        func_80B470E0(this);
    } else {
        ActorCutscene_SetIntentToPlay(D_80B50404[1]);
    }
}

void func_80B470E0(EnInvadepoh* this) {
    D_80B4E940 = 3;
    this->actionTimer = 0x6E;
    this->actionFunc = func_80B47108;
}

void func_80B47108(EnInvadepoh* this, GlobalContext* globalCtx) {
    if (this->actionTimer == 0x64) {
        func_801A3098(0x19);
    }
    this->actionTimer--;
    if (this->actionTimer <= 0) {
        globalCtx->nextEntranceIndex = 0x6460;
        gSaveContext.unk_3F4A = 0;
        globalCtx->sceneLoadFlag = 0x14;
        globalCtx->unk_1887F = 0x49;
        gSaveContext.nextTransition = 0x48;
        D_801BDAA0 = 1;
        D_801BDA9C = 0;
        func_80B47248(this);
    }
}

void func_80B471C0(EnInvadepoh* this) {
    D_80B4E940 = 3;
    this->actionFunc = func_80B471E0;
}

void func_80B471E0(EnInvadepoh* this, GlobalContext* globalCtx) {
    if (D_80B4E998) {
        globalCtx->nextEntranceIndex = 0x6470;
        gSaveContext.unk_3F4A = 0;
        globalCtx->sceneLoadFlag = 0x14;
        globalCtx->unk_1887F = 0x48;
        gSaveContext.nextTransition = 0x48;
        func_80B47248(this);
    }
}

void func_80B47248(EnInvadepoh* this) {
    D_80B4E940 = 3;
    this->actionFunc = func_80B47268;
}

void func_80B47268(EnInvadepoh* this, GlobalContext* globalCtx) {
}

void func_80B47278(EnInvadepoh* this) {
    D_80B4E940 = 4;
    this->actionFunc = func_80B47298;
}

void func_80B47298(EnInvadepoh* this, GlobalContext* globalCtx) {
    globalCtx->nextEntranceIndex = 0x6400;
    gSaveContext.unk_3F4A = 0xFFF3;
    globalCtx->sceneLoadFlag = 0x14;
    globalCtx->unk_1887F = 0x48;
    gSaveContext.nextTransition = 0x48;
    gSaveContext.weekEventReg[89] |= 0x10;
    func_80B47304(this);
}

void func_80B47304(EnInvadepoh* this) {
    D_80B4E940 = 4;
    this->actionFunc = func_80B47324;
}

void func_80B47324(EnInvadepoh* this, GlobalContext* globalCtx) {
}

void EnInvadepoh_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnInvadepoh* this = THIS;

    this->actionFunc(this, globalCtx);
    if (func_80B461DC()) {
        this->actor.draw = func_80B4D9B4;
    } else {
        this->actor.draw = NULL;
    }
}

void func_80B47380(EnInvadepoh* this) {
    this->collider.base.atFlags &= ~1;
    this->collider.base.acFlags &= ~1;
    this->collider.base.ocFlags1 &= ~1;
    this->actor.flags &= 0x7FFFFFFF;
    this->alienAlpha = 0;
    this->actor.draw = NULL;
    this->drawAlien = false;
    this->drawAlienDeathEffect = false;
    this->alienBeamAlpha = 0;
    this->actionFunc = func_80B473E4;
}

void func_80B473E4(EnInvadepoh* this, GlobalContext* globalCtx) {
    func_80B442E4(this);
    func_80B447C0(this, globalCtx);
    func_80B43DD4(this, 800, 0);
    if (D_80B50340[this->actor.params & 7] & 1) {
        Actor_SetScale(&this->actor, 0.01f);
        func_80B4516C(this);
        func_80B46118(&this->actor.world.pos);
        func_80B47568(this);
    }
}

void func_80B47478(EnInvadepoh* this) {
    this->collider.base.atFlags &= ~1;
    this->collider.base.acFlags &= ~1;
    this->collider.base.ocFlags1 &= ~1;
    this->actor.flags &= 0x7FFFFFFF;
    this->alienAlpha = 0;
    this->actor.draw = 0;
    this->drawAlien = false;
    this->drawAlienDeathEffect = false;
    this->alienBeamAlpha = 0;
    this->actionFunc = func_80B474DC;
}

void func_80B474DC(EnInvadepoh* this, GlobalContext* globalCtx) {
    func_80B442E4(this);
    func_80B447C0(this, globalCtx);
    func_80B43DD4(this, 800, 0);
    if (this->clockTime > 0.0f) {
        Actor_SetScale(&this->actor, 0.01f);
        func_80B4516C(this);
        func_80B46118(&this->actor.world.pos);
        func_80B47568(this);
    }
}

void func_80B47568(EnInvadepoh* this) {
    SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_06001D80, -6.0f);
    this->collider.base.atFlags &= ~0x1;
    this->collider.base.acFlags &= ~0x1;
    this->collider.base.ocFlags1 &= ~0x1;
    this->alienAlpha = 0;
    this->actor.draw = func_80B4DB14;
    this->drawAlien = true;
    this->drawAlienDeathEffect = false;
    this->alienBeamAlpha = 0;
    this->actor.flags |= 0x80000000;
    this->actionFunc = func_80B47600;
}

void func_80B47600(EnInvadepoh* this, GlobalContext* globalCtx) {
    func_80B442E4(this);
    func_80B447C0(this, globalCtx);
    func_80B43DD4(this, 800, 0);
    func_800B9010(this, NA_SE_EN_FOLLOWERS_BEAM_PRE - SFX_FLAG);
    if (0.9999f <= this->clockTime) {
        this->unk38A = 1;
    }
    if (this->alienAlpha >= 0xF9) {
        this->alienAlpha = 0xFF;
    } else {
        this->alienAlpha += 6;
    }
    if (this->alienAlpha >= 0x81) {
        this->collider.base.atFlags |= 1;
        this->collider.base.acFlags |= 1;
        this->collider.base.ocFlags1 |= 1;
    }
    if (this->alienAlpha == 0xFF) {
        if (this->alienBeamAlpha >= 0xF5) {
            this->alienBeamAlpha = 0xFF;
            func_80B4770C(this);
        } else {
            this->alienBeamAlpha += 10;
        }
    }
}

void func_80B4770C(EnInvadepoh* this) {
    if (this->skelAnime.animCurrentSeg != &D_06001D80) {
        SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_06001D80, -6.0f);
    }
    this->collider.base.atFlags |= 1;
    this->collider.base.acFlags |= 1;
    this->collider.base.ocFlags1 |= 1;
    this->alienAlpha = 0xFF;
    this->actor.draw = func_80B4DB14;
    this->drawAlien = true;
    this->drawAlienDeathEffect = false;
    this->alienBeamAlpha = 0xFF;
    this->actor.flags |= 0x80000000;
    this->actionFunc = func_80B477B4;
}

void func_80B477B4(EnInvadepoh* this, GlobalContext* globalCtx) {
    func_80B442E4(this);
    func_80B447C0(this, globalCtx);
    func_80B43DD4(this, 0x320, 0);
    func_800B9010(&this->actor, NA_SE_EN_FOLLOWERS_BEAM_PRE - SFX_FLAG);
    if (0.9999f <= this->clockTime) {
        this->unk38A = 1;
    }
}

void func_80B47830(EnInvadepoh* this) {
    this->collider.base.atFlags &= ~1;
    this->collider.base.acFlags &= ~1;
    this->collider.base.ocFlags1 |= 1;
    SkelAnime_ChangeAnimDefaultRepeat(&this->skelAnime, &D_060006C8);
    func_800BCB70(&this->actor, 0x4000, 0xFF, 0, 0x10);
    this->alienAlpha = 0xFF;
    this->actor.draw = func_80B4DB14;
    this->drawAlien = true;
    this->drawAlienDeathEffect = false;
    this->alienBeamAlpha = 0;
    this->actionTimer = 8;
    this->counter = 0;
    this->actor.flags |= 0x80000000;
    this->actionFunc = func_80B478F4;
}

void func_80B478F4(EnInvadepoh* this, GlobalContext* globalCtx) {
    func_80B44A90(this, globalCtx);
    this->actionTimer--;
    if (this->actionTimer <= 0) {
        func_80B47938(this);
    }
}

void func_80B47938(EnInvadepoh* this) {
    this->collider.base.atFlags &= ~1;
    this->collider.base.acFlags &= ~1;
    this->collider.base.ocFlags1 &= ~1;
    SkelAnime_ChangeAnimDefaultRepeat(&this->skelAnime, &D_06000608);
    this->actor.flags &= ~1;
    this->actionTimer = 0xA;
    this->alienAlpha = 0xFF;
    this->actor.draw = func_80B4DB14;
    this->drawAlien = true;
    this->drawAlienDeathEffect = false;
    this->alienBeamAlpha = 0xFF;
    this->actor.flags |= 0x80000000;
    this->actionFunc = func_80B479E8;
}

void func_80B479E8(EnInvadepoh* this, GlobalContext* globalCtx) {
    s16 unk2F2;
    u32 index;

    func_80B44B78(this);
    if (this->counter < 5) {
        if (D_80B4ED30[this->counter].x > 0.0f) {
            this->drawAlien = true;
            this->alienBeamAlpha = 0xFF;
            Math_Vec3f_Copy(&this->actor.scale, &D_80B4ED30[this->counter]);
        } else {
            this->drawAlien = false;
            this->alienBeamAlpha = 0;
        }

    } else {
        this->drawAlien = false;
        this->alienBeamAlpha = 0;
    }

    unk2F2 = this->counter;
    if ((unk2F2 >= 2) && (unk2F2 < 9)) {
        index = unk2F2 - 2;
        if (D_80B4ED6C[index].x > 0.0f) {
            this->drawAlienDeathEffect = true;
            Math_Vec3f_Copy(&this->alienDeathEffectScale, &D_80B4ED6C[index]);
        } else {
            this->drawAlienDeathEffect = false;
        }

    } else {
        this->drawAlienDeathEffect = false;
    }

    this->counter++;
    if (this->actionTimer == 8) {
        Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_CLEAR_TAG, this->actor.world.pos.x,
                    this->actor.world.pos.y - 10.0f, this->actor.world.pos.z, 0, 0, 3, 200);
    }

    if (this->actionTimer == 8) {
        func_800BBA88(globalCtx, &this->actor);
    }

    this->actionTimer--;
    if (this->actionTimer <= 0) {
        func_80B43AF0(this->actor.params & 7);
        func_80B43AB0();
        Item_DropCollectible(globalCtx, &this->actor.world.pos, 8);
        func_80B47478(this);
    }
}

void func_80B47BAC(Actor* thisx, GlobalContext* globalCtx) {
    EnInvadepoh* this = THIS;

    if (Object_IsLoaded(&globalCtx->objectCtx, this->bankIndex)) {
        this->actor.objBankIndex = this->bankIndex;
        Actor_SetObjectSegment(globalCtx, &this->actor);
        func_80B45080();
        this->actor.update = func_80B47D30;
        SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06004E50, &D_06001D80, this->limbDrawTable,
                         this->transitionDrawTable, 14);
        this->skelAnime.animCurrentFrame = (this->actor.params & 7) * this->skelAnime.animFrameCount * 0.125f;
        func_80B444BC(this, globalCtx);
        func_80B442E4(this);
        func_80B447C0(this, globalCtx);
        func_80B43F0C(this);
        func_80B4516C(this);
        if (D_80B4E940 == 1 || gSaveContext.time < 0x1AD8) {
            func_80B47380(this);
        } else if (D_80B4E940 == 2) {
            if (this->clockTime >= 0.0001f) {
                func_80B4770C(this);
            } else {
                func_80B47568(this);
            }
        } else {
            Actor_MarkForDeath(&this->actor);
        }
    }
}

void func_80B47D30(Actor* thisx, GlobalContext* globalCtx) {
    EnInvadepoh* this = THIS;
    s32 pad;

    if (D_80B4E940 == 3) {
        if ((this->actionFunc == func_80B477B4) || (this->actionFunc == func_80B47600)) {
            thisx->speedXZ = 0.0f;
            thisx->velocity.y = 0.0f;
            thisx->gravity = 0.0f;
            func_80B47830(this);
        } else if ((this->actionFunc == func_80B474DC) || (this->actionFunc == func_80B473E4)) {
            Actor_MarkForDeath(&this->actor);
            return;
        }

    } else if (this->collider.base.acFlags & 2) {
        Actor* acAttached = this->collider.base.ac;

        thisx->speedXZ = acAttached->speedXZ * 0.5f;
        thisx->speedXZ = CLAMP(thisx->speedXZ, -60.0f, 60.0f);
        thisx->world.rot.y = acAttached->world.rot.y;
        thisx->gravity = 0.0f;
        thisx->velocity.y = acAttached->velocity.y * 0.5f;
        thisx->velocity.y = CLAMP(thisx->velocity.y, -30.0f, 30.0f);
        func_800F0568(globalCtx, &thisx->world.pos, 50, 0x3A09);
        func_80B47830(this);
    }

    this->actionFunc(this, globalCtx);
    if (thisx->draw != NULL) {
        this->animPlayFlag = SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    }

    Collider_UpdateCylinder(&this->actor, &this->collider);
    if (this->collider.base.atFlags & AT_ON) {
        CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    } else {
        this->collider.base.atFlags &= ~AT_HIT;
    }

    if (this->collider.base.acFlags & AC_ON) {
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    } else {
        this->collider.base.acFlags &= ~AC_HIT;
    }

    if (this->collider.base.ocFlags1 & OC1_ON) {
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    } else {
        this->collider.base.ocFlags1 &= ~OC1_HIT;
    }
}

void func_80B47FA8(Actor* thisx, GlobalContext* globalCtx) {
    EnInvadepoh* this = THIS;
    s32 pad;

    if (Object_IsLoaded(&globalCtx->objectCtx, this->bankIndex)) {
        this->actor.objBankIndex = this->bankIndex;
        Actor_SetObjectSegment(globalCtx, thisx);
        this->actor.update = func_80B48060;
        this->actor.draw = func_80B4E158;
        SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06004010, NULL, this->limbDrawTable, this->transitionDrawTable,
                         6);
        SkelAnime_ChangeAnimDefaultRepeat(&this->skelAnime, &D_06004264);
    }
}

void func_80B48060(Actor* thisx, GlobalContext* globalCtx) {
    EnInvadepoh* this = THIS;
    s32 pad;
    s32 temp;
    s32 pad2;
    MtxF unkMtx;

    if (D_80B503F0 == NULL || this->actor.parent == NULL) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    temp = this->actor.params & 7;
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    Math_ScaledStepToS(&this->actor.shape.rot, D_80B4EDC0[temp], 50);
    if (this->actor.child != NULL) {
        SysMatrix_StatePush();
        SysMatrix_SetStateRotationAndTranslation(this->actor.world.pos.x, this->actor.world.pos.y,
                                                 this->actor.world.pos.z, &this->actor.shape.rot);
        SysMatrix_InsertTranslation(0, 57.0f, -36.0f, MTXMODE_APPLY);
        SysMatrix_InsertXRotation_s(this->actor.shape.rot.x * -0.7f, MTXMODE_APPLY);
        SysMatrix_InsertZRotation_s(this->actor.shape.rot.z * -0.7f, MTXMODE_APPLY);
        SysMatrix_GetStateTranslation(&this->actor.child->world.pos);
        SysMatrix_CopyCurrentState(&unkMtx);
        func_8018219C(&unkMtx, &this->actor.child->shape.rot, 0);
        SysMatrix_StatePop();
    }
}

void func_80B481C4(Actor* thisx, GlobalContext* globalCtx) {
    EnInvadepoh* this = THIS;
    s32 pad;

    if (Object_IsLoaded(&globalCtx->objectCtx, this->bankIndex)) {
        this->actor.objBankIndex = this->bankIndex;
        Actor_SetObjectSegment(globalCtx, &this->actor);
        this->actor.update = func_80B4827C;
        this->actor.draw = func_80B4E1B0;
        SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06004C30, NULL, this->limbDrawTable, this->transitionDrawTable,
                         6);
        SkelAnime_ChangeAnimDefaultRepeat(&this->skelAnime, &D_06004E98);
    }
}

void func_80B4827C(Actor* thisx, GlobalContext* globalCtx) {
    EnInvadepoh* this = THIS;

    if (D_80B503F0 == NULL || this->actor.parent == NULL) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
}

void func_80B482D4(EnInvadepoh* this) {
    this->actionTimer = 0x28;
    SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_06002A8C, -10.0f);
    this->actor.draw = NULL;
    this->actionFunc = func_80B48324;
}

void func_80B48324(EnInvadepoh* this, GlobalContext* globalCtx) {
    this->actionTimer--;
    if (this->actionTimer <= 0) {
        func_80B4560C(this, globalCtx, 0x332F);
        this->actor.draw = func_80B4E324;
        func_80B48374(this);
    }
}

void func_80B48374(EnInvadepoh* this) {
    this->actionTimer = 60;
    SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_06002A8C, -10.0f);
    this->actor.draw = func_80B4E324;
    this->actionFunc = func_80B483CC;
}

void func_80B483CC(EnInvadepoh* this, GlobalContext* globalCtx) {
    if (this->actionTimer == 20) {
        f32 unkFloat = 0.1f; // required to match

        this->behaviorInfo.unk26.x = 2000;
        this->behaviorInfo.unk26.y = 0;
        this->behaviorInfo.unk26.z = 0;
        this->behaviorInfo.unk30 = unkFloat;
        this->behaviorInfo.unk2C = 1000;
    }

    this->actionTimer--;
    if (this->actionTimer <= 0) {
        func_80B4843C(this);
    }
}

void func_80B4843C(EnInvadepoh* this) {
    this->behaviorInfo.unk26.x = 3000;
    this->behaviorInfo.unk26.y = 0;
    this->behaviorInfo.unk26.z = 0;
    this->behaviorInfo.unk30 = 0.24f;
    this->behaviorInfo.unk2C = 3000;
    this->behaviorInfo.unk42 = 15000;
    this->behaviorInfo.unk44 = 0.1f;
    this->behaviorInfo.unk48 = 2000;
    this->actionTimer = 50;
    SkelAnime_ChangeAnim(&this->skelAnime, &D_06007328, 2.0f, 0.0f, 0.0f, 0, -5.0f);
    this->actor.draw = func_80B4E324;
    this->actionFunc = func_80B484EC;
}

void func_80B484EC(EnInvadepoh* this, GlobalContext* globalCtx) {
    if (this->actionTimer == 40) {
        this->behaviorInfo.unk26.y = 7000;
    } else if (this->actionTimer == 30) {
        this->behaviorInfo.unk26.y = -7000;
    } else if (this->actionTimer == 20) {
        this->behaviorInfo.unk26.y = 7000;
    } else if (this->actionTimer == 10) {
        this->behaviorInfo.unk26.y = 0;
    }
    this->actionTimer--;
    if (this->actionTimer <= 0) {
        func_80B48588(this);
    }
}

void func_80B48588(EnInvadepoh* this) {
    this->behaviorInfo.unk26.x = 0;
    this->behaviorInfo.unk26.y = 0;
    this->behaviorInfo.unk26.z = 0;
    this->behaviorInfo.unk30 = 0.24f;
    this->behaviorInfo.unk2C = 5000;
    this->behaviorInfo.unk42 = 0;
    this->behaviorInfo.unk44 = 0.28f;
    this->behaviorInfo.unk48 = 7000;
    SkelAnime_ChangeAnimTransitionStop(&this->skelAnime, &D_06009E58, -10.0f);
    this->actor.draw = func_80B4E324;
    this->actionFunc = func_80B48610;
}

void func_80B48610(EnInvadepoh* this, GlobalContext* globalCtx) {
}

void func_80B48620(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad[2];
    EnInvadepoh* this = THIS;

    if (Object_IsLoaded(&globalCtx->objectCtx, this->bankIndex)) {
        this->actor.objBankIndex = this->bankIndex;
        Actor_SetObjectSegment(globalCtx, &this->actor);
        func_80B44F58();
        this->actor.update = func_80B4873C;
        SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06013928, &D_06009E58, this->limbDrawTable,
                         this->transitionDrawTable, 23);
        func_80B45C04(&this->behaviorInfo, &D_80B4EA90, 6, &D_80B4EB00, 2, &D_801D15BC, 0x1388, 0.05f, 0.3f, 0.12f);
        SkelAnime_ChangeAnimDefaultRepeat(&this->skelAnime, &D_06009E58);
        func_80B482D4(this);
    }
}

void func_80B4873C(Actor* thisx, GlobalContext* globalCtx) {
    EnInvadepoh* this = THIS;
    s32 pad;
    AlienBehaviorInfo* substruct = &this->behaviorInfo;

    if (this->actor.parent == NULL) {
        Actor_MarkForDeath(&this->actor);
        return;
    }
    this->actionFunc(this, globalCtx);
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    func_80B45CE0(substruct);
    if (substruct->unk40 != 0) {
        this->actor.shape.rot.x = -substruct->unk40;
    }
}

void func_80B487B4(EnInvadepoh* this) {
    AlienBehaviorInfo* substruct = &this->behaviorInfo;
    u32 new_var;

    this->actionTimer = Rand_S16Offset(150, 250);
    new_var = Rand_Next();
    substruct->unk26.x = D_80B4EDC8[new_var >> 0x1E];
    substruct->unk26.y = 0;
    substruct->unk26.z = 0;
    substruct->unk30 = 0.1f;
    substruct->unk2C = 800;
    SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_06014088, -10.0f);
    this->actionFunc = func_80B48848;
}

void func_80B48848(EnInvadepoh* this, GlobalContext* globalCtx) {
    s32 pad;

    Math_StepToF(&this->actor.speedXZ, 1.6f, 0.1f);
    if (func_80B44B84(this, globalCtx, this->actor.speedXZ, 50.0f)) {
        func_80B44514(this);
        this->behaviorInfo.unk4C = 0xC8;
        this->actor.speedXZ *= 0.25f;
    } else {
        Math_StepToS(&this->behaviorInfo.unk4C, 0x7D0, 0x46);
    }
    func_80B43E6C(this, 6, this->behaviorInfo.unk4C, 0x46);
    if ((this->actor.flags & 0x40) == 0x40) {
        if (func_801378B8(&this->skelAnime, 0.0f) || func_801378B8(&this->skelAnime, 7.0f)) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_ROMANI_WALK);
        }
    }
    if (this->actionTimer > 0) {
        this->actionTimer--;
    } else {
        func_80B48948(this);
    }
}

void func_80B48948(EnInvadepoh* this) {
    AlienBehaviorInfo* substruct = &this->behaviorInfo;
    f32 rand = Rand_ZeroOne();

    this->actionTimer = Rand_S16Offset(150, 150);
    if (rand < 0.5f) {
        this->unk374 = 0;
        Math_Vec3s_Copy(&substruct->unk26, &D_801D15BC);
        substruct->unk30 = 0.1f;
        substruct->unk2C = 1000;
    } else if (rand < 0.75f) {
        this->unk374 = 1;
        substruct->unk26.x = Rand_S16Offset(0, 2000);
        substruct->unk26.y = 0;
        substruct->unk26.z = 0;
        substruct->unk30 = 0.06f;
        substruct->unk2C = 1000;
    } else if (rand < 0.8f) {
        this->unk374 = 2;
        substruct->unk26.x = Rand_S16Offset(-2000, 2000);
        substruct->unk26.y = 0;
        substruct->unk26.z = 0;
        substruct->unk30 = 0.05f;
        substruct->unk2C = 1000;
    } else {
        this->unk374 = 3;
        substruct->unk26.x = 0;
        substruct->unk26.y = 0;
        substruct->unk26.z = Rand_S16Offset(-2500, 5000);
        substruct->unk30 = 0.04f;
        substruct->unk2C = 1000;
    }

    SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_06009E58, -10.0f);
    this->actionFunc = func_80B48AD4;
}

void func_80B48AD4(EnInvadepoh* this, GlobalContext* globalCtx) {
    AlienBehaviorInfo* substruct = &this->behaviorInfo;
    Player* player;
    s16 new_var3;
    s16 temp_v1;
    s32 temp_v1_3;

    Math_StepToF(&this->actor.speedXZ, 0.0f, 0.2f);
    if (func_80B44B84(this, globalCtx, this->actor.speedXZ, 50.0f)) {
        func_80B44514(this);
    }

    if (this->unk374 == 0) {
        if ((this->actor.xzDistToPlayer < 350.0f) && ((globalCtx->gameplayFrames & 0x60) != 0)) {
            player = PLAYER;
            temp_v1 = Math_Vec3f_Pitch(&this->actor.focus.pos, &player->actor.focus.pos) * 0.85f;
            temp_v1 -= this->actor.shape.rot.x;
            substruct->unk26.x = CLAMP(temp_v1, -0x9C4, 0x9C4);
            new_var3 = (this->actor.yawTowardsPlayer - this->actor.shape.rot.y);
            temp_v1 = new_var3 * 0.7f;
            substruct->unk26.y = CLAMP(temp_v1, -0x1F40, 0x1F40);
        }

    dummy_label_558449:; // fake match? Required as it is currently

    } else {
        substruct->unk26.x = 0;
        substruct->unk26.y = 0;
    }

    if (this->actionTimer > 0) {
        temp_v1_3 = this->actionTimer & 0x1F;
        if ((temp_v1_3 == 0) && (Rand_ZeroOne() < 0.3f)) {
            temp_v1_3 = Rand_Next();
            temp_v1_3 = temp_v1_3 % 4;
            if (temp_v1_3 != this->unk374) {
                this->unk374 = temp_v1_3;
                if (this->unk374 == 0) {
                    Math_Vec3s_Copy(&substruct->unk26, &D_801D15BC);
                    substruct->unk30 = 0.07f;
                } else if (this->unk374 == 1) {
                    substruct->unk26.x = Rand_S16Offset(0x3E8, 0x3E8);
                    substruct->unk26.y = Rand_S16Offset(-0x3E8, 0x7D0);
                    substruct->unk26.z = Rand_S16Offset(-0x320, 0x640);
                    substruct->unk30 = 0.06f;
                } else if (this->unk374 == 2) {
                    substruct->unk26.x = Rand_S16Offset(-0x7D0, 0x3E8);
                    substruct->unk26.y = Rand_S16Offset(-0x3E8, 0x7D0);
                    substruct->unk26.z = Rand_S16Offset(-0x320, 0x640);
                    substruct->unk30 = 0.05f;
                } else {
                    substruct->unk26.x = Rand_S16Offset(-0x3E8, 0x7D0);
                    substruct->unk26.y = Rand_S16Offset(-0x7D0, 0xFA0);
                    substruct->unk26.z = Rand_S16Offset(-0x7D0, 0xFA0);
                    substruct->unk30 = 0.04f;
                }
            }
        }

        this->actionTimer--;
    } else {
        func_80B487B4(this);
    }
}

void func_80B48DE4(EnInvadepoh* this) {
    AlienBehaviorInfo* substruct = &this->behaviorInfo;

    this->actor.speedXZ = 0.0f;
    SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_06009E58, -10.0f);
    this->behaviorInfo.unk4C = 0;
    substruct->unk30 = 0.05f;
    substruct->unk2C = 1200;
    this->actionFunc = func_80B48E4C;
}

void func_80B48E4C(EnInvadepoh* this, GlobalContext* globalCtx) {
    AlienBehaviorInfo* substruct = &this->behaviorInfo;
    Player* player = PLAYER;
    s16 temp_v1;
    s16 diff;

    Math_StepToS(&this->behaviorInfo.unk4C, 0x7D0, 0x32);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 6, this->behaviorInfo.unk4C, 0x23);
    temp_v1 = Math_Vec3f_Pitch(&this->actor.focus.pos, &player->actor.focus.pos);
    temp_v1 *= 0.85f;
    temp_v1 -= this->actor.shape.rot.x;
    substruct->unk26.x = CLAMP(temp_v1, -0xBB8, 0xBB8);
    diff = (this->actor.yawTowardsPlayer - this->actor.shape.rot.y);
    temp_v1 = diff * 0.7f;
    substruct->unk26.y = CLAMP(temp_v1, -0x1F40, 0x1F40);
    if (func_800B867C(this, globalCtx)) {
        func_80B48948(this);
    }
}

void func_80B48FB0(Actor* thisx, GlobalContext* globalCtx) {
    EnInvadepoh* this = THIS;

    if (Object_IsLoaded(&globalCtx->objectCtx, this->bankIndex)) {
        this->actor.objBankIndex = this->bankIndex;
        Actor_SetObjectSegment(globalCtx, &this->actor);
        func_80B44F58();
        this->actor.update = func_80B490F0;
        this->actor.draw = func_80B4E324;
        this->actor.textId = 0x3330;
        SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06013928, &D_06009E58, this->limbDrawTable,
                         this->transitionDrawTable, 23);
        func_80B45C04(&this->behaviorInfo, &D_80B4EA90, 6, &D_80B4EB00, 2, &D_801D15BC, 0x64, 0.03, 0.3, 0.03);
        func_80B444F4(this, globalCtx);
        func_80B4407C(this, 0);
        func_800B4AEC(globalCtx, &this->actor, 50.0f);
        func_80B4516C(this);
        func_80B487B4(this);
    }
}

void func_80B490F0(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnInvadepoh* this = THIS;
    s32 sp2C;
    s32 isTalking;

    sp2C = (this->actor.flags & 0x40) == 0x40;
    isTalking = func_800B84D0(&this->actor, globalCtx);

    if (isTalking) {
        func_80151BB4(globalCtx, 5);
        func_80B48DE4(this);
    }
    this->actionFunc(this, globalCtx);
    if (sp2C) {
        SkelAnime_FrameUpdateMatrix(&this->skelAnime);
        func_80B45CE0(&this->behaviorInfo);
        if (this->actionFunc != func_80B48E4C) {
            if (!isTalking) {
                if (this->actor.isTargeted) {
                    func_800B8614(&this->actor, globalCtx, 100.0f);
                }
            }
        }
        Collider_UpdateCylinder(&this->actor, &this->collider);
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }
}

void func_80B491EC(EnInvadepoh* this) {
    this->unk39C = 0.0f;
    this->unk3A4 = 0.0f;
    this->unk3AA = 0;
    this->actor.gravity = -15.0f;
    this->unk3A0 = 1.0f;
    this->actionFunc = func_80B49228;
}

void func_80B49228(EnInvadepoh* this, GlobalContext* globalCtx) {
    s32 pad;
    f32 temp_f0;

    Actor_SetVelocityYRotationAndGravity(&this->actor);
    this->actor.velocity.y *= 0.97f;
    temp_f0 = Math_SmoothStepToF(&this->actor.world.pos.y, this->actor.home.pos.y + D_80B4E934.y + 300.0f, 0.7f,
                                 fabsf(this->actor.velocity.y), 1.0f);
    func_800B9010(&this->actor, NA_SE_EV_UFO_APPEAR - SFX_FLAG);
    if (fabsf(temp_f0) < 1.0f) {
        func_80B45EC8(this, globalCtx, 0x32);
        func_80B492FC(this);
    }
}

void func_80B492FC(EnInvadepoh* this) {
    this->actor.velocity.y *= 0.1f;
    this->actionTimer = 20;
    this->unk3A0 = 0.3f;
    this->unk3A4 = 0.03f;
    this->unk3AA = 3000;
    this->actionFunc = func_80B4934C;
}

void func_80B4934C(EnInvadepoh* this, GlobalContext* globalCtx) {
    f32 temp = this->actor.home.pos.y + D_80B4E934.y + 300.0f;

    if (this->actor.world.pos.y < temp) {
        this->actor.gravity = 3.0f;
    } else {
        this->actor.gravity = -2.0f;
    }
    this->actor.velocity.y *= 0.96f;
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
    func_800B9010(&this->actor, NA_SE_EV_UFO_APPEAR - SFX_FLAG);
    this->actionTimer--;
    if (this->actionTimer <= 0) {
        func_80B49404(this);
    }
}

void func_80B49404(EnInvadepoh* this) {
    this->actionTimer = 120;
    this->unk3A0 = 0.2f;
    this->unk3A4 = 0.01f;
    this->unk3AA = 3000;
    this->unk3AC = 0;
    this->counter = 0;
    this->actor.gravity = 33.0f;
    this->actionFunc = func_80B49454;
}

void func_80B49454(EnInvadepoh* this, GlobalContext* globalCtx) {
    s32 pad;
    Vec3f sp30;
    s32 pad2;

    if (this->counter < 0x19) {
        this->counter++;
    } else {
        this->counter = 0;
        this->unk3AC++;
        this->unk3AC = CLAMP_MAX(this->unk3AC, 4);
        this->actor.gravity = 33.0f;
        func_80B45EC8(this, globalCtx, 0x14);
    }

    Math_Vec3f_Sum(&D_80B4EDD0[this->unk3AC], &this->actor.home, &sp30);
    if (Math3D_DistanceSquared(&this->actor.world, &sp30) < SQ(400.0f)) {
        this->actor.speedXZ *= 0.8f;
    } else {
        Math_StepToF(&this->actor.speedXZ, 170.0f, 21.0f);
        this->actor.speedXZ *= 0.98f;
    }
    if (func_80B450C0(&this->actor.world.pos.x, &this->actor.world.pos.z, sp30.x, sp30.z, this->actor.speedXZ)) {
        this->actor.speedXZ = 0.0f;
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
    if (this->actionTimer > 0) {
        this->actionTimer--;
    } else {
        func_80B49628(this);
    }
}

void func_80B49628(EnInvadepoh* this) {
    this->unk3A0 = 0.2f;
    this->unk3A4 = 0.01f;
    this->unk3AA = 3000;
    this->actor.velocity.y *= 0.8f;
    this->actionFunc = func_80B49670;
}

void func_80B49670(EnInvadepoh* this, GlobalContext* globalCtx) {
    s32 pad;
    Vec3f sp30;

    sp30.x = this->actor.home.pos.x;
    sp30.y = this->actor.home.pos.y + 1500.0f;
    sp30.z = this->actor.home.pos.z;
    Math_SmoothStepToS(&this->actor.world.rot.y, Math_Vec3f_Yaw(&this->actor.world, &sp30), 0xA, 0xBB8, 0x64);
    if ((globalCtx->gameplayFrames % 64) < 14) {
        Math_StepToF(&this->actor.speedXZ, 5.0f, 1.0f);
    } else {
        this->actor.speedXZ *= 0.97f;
    }
    if (sp30.y < this->actor.world.pos.y) {
        this->actor.gravity = -0.5f;
    } else {
        this->actor.gravity = 2.0f;
    }
    this->actor.velocity.y *= 0.97f;
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
    if (D_80B4E940 == 3) {
        func_80B499BC(this);
    }
}

void func_80B497A4(EnInvadepoh* this) {
    this->unk3A0 = 0.2f;
    this->unk3A4 = 0.01f;
    this->unk3AA = 3000;
    this->actionTimer = 35;
    this->actor.gravity = -1.5f;
    this->actionFunc = func_80B497EC;
}

void func_80B497EC(EnInvadepoh* this, GlobalContext* globalCtx) {
    s32 pad;
    Vec3f sp30;

    sp30.x = this->actor.home.pos.x + D_80B4E934.x;
    sp30.y = this->actor.home.pos.y + D_80B4E934.y + 400.0f;
    sp30.z = this->actor.home.pos.z + D_80B4E934.z;
    Math_SmoothStepToS(&this->actor.world.rot.y, Math_Vec3f_Yaw(&this->actor.world, &sp30), 4, 0x1F40, 0x64);
    Math_StepToF(&this->actor.speedXZ, 70.0f, 3.0f);
    if (sp30.y < this->actor.world.pos.y) {
        this->actor.gravity = -2.0f;
    } else {
        this->actor.gravity = 2.0f;
    }
    this->actor.velocity.y *= 0.97f;
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
    if (this->actionTimer > 0) {
        this->actionTimer--;
    } else {
        func_80B49904(this);
    }
}

void func_80B49904(EnInvadepoh* this) {
    this->unk3A0 = 0.2f;
    this->unk3A4 = 0.01f;
    this->unk3AA = 3000;
    this->actionTimer = 60;
    this->actor.gravity = 1.0f;
    this->actionFunc = func_80B4994C;
}

void func_80B4994C(EnInvadepoh* this, GlobalContext* globalCtx) {
    Math_StepToF(&this->actor.speedXZ, 150.0f, 4.0f);
    this->actor.velocity.y *= 0.95f;
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
    if (this->actionTimer > 0) {
        this->actionTimer--;
    } else {
        Actor_MarkForDeath(&this->actor);
    }
}

void func_80B499BC(EnInvadepoh* this) {
    this->actionTimer = 40;
    this->unk3A0 = 0.2f;
    this->unk3A4 = 0.01f;
    this->unk3AA = 3000;
    this->actor.speedXZ = 0.0f;
    this->actionFunc = func_80B49A00;
}

void func_80B49A00(EnInvadepoh* this, GlobalContext* globalCtx) {
    s32 pad;
    Vec3f sp30;

    sp30.x = this->actor.home.pos.x;
    sp30.y = this->actor.home.pos.y + 800.0f;
    sp30.z = this->actor.home.pos.z;
    Math_SmoothStepToS(&this->actor.world.rot.y, Math_Vec3f_Yaw(&this->actor.world, &sp30), 4, 0x1F40, 0x64);
    Math_StepToF(&this->actor.speedXZ, 30.0f, 3.0f);
    this->actor.velocity.y *= 0.98f;
    if (sp30.y < this->actor.world.pos.y) {
        this->actor.gravity = -0.5f;
    } else {
        this->actor.gravity = 2.0f;
    }
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 4);
    if (this->actionTimer > 0) {
        this->actionTimer--;
    } else {
        func_80B497A4(this);
    }
}

void func_80B49B1C(Actor* thisx, GlobalContext* globalCtx) {
    EnInvadepoh* this = THIS;
    f32 temp;

    this->actionFunc(this, globalCtx);
    this->unk3A8 += this->unk3AA;
    Math_StepToF(&this->unk39C, this->unk3A0, this->unk3A4);
    temp = Math_SinS(this->unk3A8) * this->unk39C + 1.0f; // required
    Actor_SetScale(&this->actor, 0.27f * temp);
    Math_StepToS(&this->unk306, 0x258, 8);
    this->actor.world.rot.y += this->unk306;
    this->unk304 += 0x258;
}

void func_80B49BD0(EnInvadepoh* this) {
    AlienBehaviorInfo* substruct = &this->behaviorInfo;

    SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_06014088, -10.0f);
    substruct->unk26.x = 0;
    substruct->unk26.y = 0;
    substruct->unk26.z = 0;
    substruct->unk30 = 0.1f;
    substruct->unk2C = 800;
    this->actionFunc = func_80B49C38;
}

void func_80B49C38(EnInvadepoh* this, GlobalContext* globalCtx) {
    s32 pad;
    s32 temp_v0_2;

    func_80B44570(this);
    func_80B44C24(this, globalCtx);
    func_80B43E6C(this, 6, 0x7D0, 0x64);
    if (1) {} // required to match
    if (this->unk309 == 0 || this->unk309 + 1 == this->unk308) {
        if (this->unk378 == 0) {
            temp_v0_2 = func_800FE620(globalCtx);
            if (temp_v0_2 > 0) {
                temp_v0_2 = (REG(15) * -16.0f / temp_v0_2) - 0.5f;
                this->unk378 = func_80B45550(this, globalCtx, 6400.0f, temp_v0_2);
            }
        }
        this->actor.flags &= ~0x9;
    } else {
        this->unk378 = 0;
        this->actor.flags |= 9;
    }

    if ((this->actor.flags & 0x40) == 0x40) {
        if (func_801378B8(&this->skelAnime, 0.0f) || func_801378B8(&this->skelAnime, 7.0f)) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_ROMANI_WALK);
        }
    }
    if (0.9999f <= this->clockTime) {
        Actor_MarkForDeath(&this->actor);
    }
}

void func_80B49DA0(EnInvadepoh* this) {
    this->behaviorInfo.unk30 = 0.08f;
    this->behaviorInfo.unk2C = 2000;
    this->behaviorInfo.unk4C = 0;
    SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_06009E58, -10.0f);
    this->actionFunc = func_80B49DFC;
}

void func_80B49DFC(EnInvadepoh* this, GlobalContext* globalCtx) {
    AlienBehaviorInfo* substruct = &this->behaviorInfo;
    Player* player = PLAYER;
    s16 temp_v1;
    s16 diff;

    Math_StepToS(&this->behaviorInfo.unk4C, 0x7D0, 0x1F4);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, this->behaviorInfo.unk4C, 0x28);
    temp_v1 = (Math_Vec3f_Pitch(&this->actor.focus.pos, &player->actor.focus.pos) * 0.85f);
    temp_v1 -= this->actor.shape.rot.x;
    substruct->unk26.x = CLAMP(temp_v1, -0xBB8, 0xBB8);
    diff = (s16)(this->actor.yawTowardsPlayer - this->actor.shape.rot.y);
    temp_v1 = diff;
    temp_v1 *= 0.7f;
    substruct->unk26.y = CLAMP(temp_v1, -0x1F40, 0x1F40);
    if (func_800B867C(&this->actor, globalCtx)) {
        if (this->actor.textId == 0x332D) {
            gSaveContext.weekEventReg[54] |= 0x10;
            this->actor.textId = 0x332E;
        }
        func_80B49BD0(this);
    }
}

void func_80B49F88(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad[2];
    EnInvadepoh* this = THIS;
    s32 sp38;

    if (Object_IsLoaded(&globalCtx->objectCtx, this->bankIndex)) {
        sp38 = gSaveContext.time;
        this->actor.objBankIndex = this->bankIndex;
        Actor_SetObjectSegment(globalCtx, &this->actor);
        func_80B44F58();
        SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06013928, &D_06014088, this->limbDrawTable,
                         this->transitionDrawTable, 23);
        func_80B45C04(&this->behaviorInfo, &D_80B4EA90, 1, &D_80B4EB00, 1, &D_801D15BC, 0x64, 0.03, 0.3, 0.03);
        func_80B44540(this, globalCtx);
        func_80B44570(this);
        func_80B44C24(this, globalCtx);
        func_80B43F0C(this);
        func_80B4516C(this);
        if (0x20 & gSaveContext.weekEventReg[21]) {
            if (gSaveContext.weekEventReg[54] & 0x10) {
                this->actor.textId = 0x332E;
            } else {
                this->actor.textId = 0x332D;
            }

        } else {
            this->actor.textId = 0x332C;
        }

        if (sp38 >= 0xC000 || sp38 < 0x1555) {
            this->actor.update = func_80B4A168;
            this->actor.draw = 0;
        } else if (((sp38 < 0x4000) && (sp38 >= 0x1555)) && (sp38 < 0x1800)) {
            this->actor.update = func_80B4A1B8;
            this->actor.draw = func_80B4E324;
            func_80B49BD0(this);
        } else {
            Actor_MarkForDeath(&this->actor);
        }
    }
}

void func_80B4A168(Actor* thisx, GlobalContext* globalCtx) {
    EnInvadepoh* this = THIS;

    if ((gSaveContext.time < CLOCK_TIME(6, 0)) && (gSaveContext.time >= CLOCK_TIME(2, 0))) {
        this->actor.update = func_80B4A1B8;
        this->actor.draw = func_80B4E324;
        func_80B49BD0(this);
    }
}

void func_80B4A1B8(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnInvadepoh* this = THIS;
    s32 sp2C;
    s32 temp_v0;

    sp2C = (this->actor.flags & 0x40) == 0x40;
    temp_v0 = func_800B84D0(&this->actor, globalCtx);

    if (temp_v0) {
        func_80151BB4(globalCtx, 5);
        func_80B49DA0(this);
    }
    this->actionFunc(this, globalCtx);
    if (sp2C != 0) {
        if (this->actor.update != NULL) {
            SkelAnime_FrameUpdateMatrix(&this->skelAnime);
            func_80B45CE0(&this->behaviorInfo);
            if (this->actionFunc != func_80B49DFC) {
                if (!temp_v0) {
                    if (this->actor.isTargeted) {
                        func_800B8614(&this->actor, globalCtx, 350.0f);
                    }
                }
            }
            Collider_UpdateCylinder(&this->actor, &this->collider);
            CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        }
    }
}

void func_80B4A2C0(EnInvadepoh* this) {
    AlienBehaviorInfo* substruct = &this->behaviorInfo;

    SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_06009E58, -10.0f);
    substruct->unk26.x = 0;
    substruct->unk26.y = 0;
    substruct->unk26.z = 0;
    substruct->unk30 = 0.1f;
    substruct->unk2C = 1500;
    this->actionTimer = Rand_S16Offset(200, 200);
    this->unk304 = this->actor.shape.rot.y;
    this->actor.flags |= 9;
    this->actionFunc = func_80B4A350;
}

void func_80B4A350(EnInvadepoh* this, GlobalContext* globalCtx) {
    s16 temp_v0;
    s16 temp_v1_2;
    s16 diff;
    Vec3f sp44;
    s16 sp42;
    AlienBehaviorInfo* substruct = &this->behaviorInfo;

    if ((globalCtx->gameplayFrames % 256) == 0) {
        Math_Vec3s_ToVec3f(&sp44, this->pathPoints);
        sp42 = Math_Vec3f_Yaw(&this->actor.world, &sp44);
        temp_v0 = Rand_S16Offset(-0x1F40, 0x3E80);
        this->unk304 = temp_v0 + sp42;
        this->behaviorInfo.unk4C = 0;
    }

    Math_StepToS(&this->behaviorInfo.unk4C, 0x7D0, 0x28);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->unk304, 6, this->behaviorInfo.unk4C, 0x28);
    if (this->actor.xzDistToPlayer < 300.0f) {
        Player* player = PLAYER;

        temp_v1_2 = Math_Vec3f_Pitch(&this->actor.focus.pos, &player->actor.focus.pos);
        temp_v1_2 *= 0.85f;
        temp_v1_2 -= this->actor.shape.rot.x;
        substruct->unk26.x = CLAMP(temp_v1_2, -0x9C4, 0x9C4);
        diff = (s16)(this->actor.yawTowardsPlayer - this->actor.shape.rot.y);
        temp_v1_2 = diff;
        temp_v1_2 *= 0.7f;
        substruct->unk26.y = CLAMP(temp_v1_2, -0x1F40, 0x1F40);
        if ((globalCtx->gameplayFrames % 256) == 0) {
            substruct->unk26.z = Rand_S16Offset(-0x5DC, 0xBB8);
        }
    } else {
        substruct->unk26.x = 0;
        substruct->unk26.y = 0;
        substruct->unk26.z = 0;
    }
    if (this->actionTimer > 0) {
        this->actionTimer--;
    } else {
        func_80B4A570(this);
    }
}

void func_80B4A570(EnInvadepoh* this) {
    AlienBehaviorInfo* substruct = &this->behaviorInfo;

    SkelAnime_ChangeAnimTransitionStop(&this->skelAnime, &D_06002A8C, -10.0f);
    substruct->unk26.x = 0;
    substruct->unk26.y = 0;
    substruct->unk26.z = 0;
    substruct->unk30 = 0.1f;
    substruct->unk2C = 800;
    this->actor.flags |= 9;
    this->actionFunc = func_80B4A5E4;
}

void func_80B4A5E4(EnInvadepoh* this, GlobalContext* globalCtx) {
    if (this->animPlayFlag != 0) {
        func_80B4A2C0(this);
    }
}

void func_80B4A614(EnInvadepoh* this) {
    AlienBehaviorInfo* substruct = &this->behaviorInfo;

    SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_06014088, 0.0f);
    substruct->unk26.x = 0;
    substruct->unk26.y = 0;
    substruct->unk26.z = 0;
    substruct->unk30 = 0.1f;
    substruct->unk2C = 800;
    this->actionFunc = func_80B4A67C;
}

void func_80B4A67C(EnInvadepoh* this, GlobalContext* globalCtx) {
    s32 pad;

    Math_StepToF(&this->actor.speedXZ, 5.0f, 1.0f);
    if (func_80B44B84(this, globalCtx, this->actor.speedXZ, 50.0f)) {
        func_80B44640(this);
        this->behaviorInfo.unk4C = 0x5DC;
        this->actor.speedXZ *= 0.5f;
    } else {
        Math_StepToS(&this->behaviorInfo.unk4C, 0x190, 0x32);
    }
    func_80B43E6C(this, 6, this->behaviorInfo.unk4C, 0x32);
    if (this->unk309 == 0) {
        if (this->unk378 == 0) {
            this->unk378 = func_80B45550(this, globalCtx, 6400.0f, -0xF);
        }
        this->actor.flags &= ~0x9;
    } else {
        this->unk378 = 0;
        this->actor.flags |= 9;
    }
    if ((this->actor.flags & 0x40) == 0x40) {
        if (func_801378B8(&this->skelAnime, 0.0f) || func_801378B8(&this->skelAnime, 7.0f)) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_ROMANI_WALK);
        }
    }
    if (this->unk309 == this->unk308) {
        func_80B4A2C0(this);
    }
}

void func_80B4A7C0(EnInvadepoh* this) {
    this->behaviorInfo.unk30 = 0.08f;
    this->behaviorInfo.unk2C = 2000;
    this->behaviorInfo.unk4C = 0;
    SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_06009E58, 0.0f);
    this->actionFunc = func_80B4A81C;
}

void func_80B4A81C(EnInvadepoh* this, GlobalContext* globalCtx) {
    AlienBehaviorInfo* substruct = &this->behaviorInfo;
    Player* player = PLAYER;
    s16 temp_v1;
    s16 diff;

    Math_StepToS(&this->behaviorInfo.unk4C, 0x7D0, 0x1F4);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, this->behaviorInfo.unk4C, 0x28);
    temp_v1 = (Math_Vec3f_Pitch(&this->actor.focus.pos, &player->actor.focus.pos) * 0.85f);
    temp_v1 -= this->actor.shape.rot.x;
    substruct->unk26.x = CLAMP(temp_v1, -0xBB8, 0xBB8);
    diff = (s16)(this->actor.yawTowardsPlayer - this->actor.shape.rot.y);
    temp_v1 = diff;
    temp_v1 *= 0.7f;
    substruct->unk26.y = CLAMP(temp_v1, -0x1F40, 0x1F40);

    if (func_800B867C(this, globalCtx)) {
        if (this->actor.textId == 0x332D) {
            gSaveContext.weekEventReg[54] |= 0x10;
            this->actor.textId = 0x332E;
        }
        if (this->unk308 == this->unk309) {
            func_80B4A2C0(this);
        } else {
            func_80B4A614(this);
        }
    }
}

void func_80B4A9C8(Actor* thisx, GlobalContext* globalCtx) {
    EnInvadepoh* this = THIS;
    s32 pad[2];
    s32 sp38;

    if (Object_IsLoaded(&globalCtx->objectCtx, this->bankIndex)) {
        sp38 = gSaveContext.time;
        this->actor.objBankIndex = this->bankIndex;
        Actor_SetObjectSegment(globalCtx, &this->actor);
        func_80B44F58();
        SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06013928, &D_06014088, this->limbDrawTable,
                         this->transitionDrawTable, 23);
        func_80B45C04(&this->behaviorInfo, &D_80B4EA90, 1, &D_80B4EB00, 1, &D_801D15BC, 0x64, 0.03f, 0.3f, 0.03f);
        func_80B44620(this, globalCtx);
        if ((sp38 < 0x1800) || (sp38 >= 0x4000)) {
            this->unk309 = 0;
            this->actor.update = func_80B4AB8C;
        } else {
            this->unk309 = this->unk308;
            this->actor.update = func_80B4ABDC;
            this->actor.draw = func_80B4E324;
            func_80B4A2C0(this);
        }

        func_80B4407C(this, this->unk309);
        func_80B43F0C(this);
        func_800B4AEC(globalCtx, &this->actor, 50.0f);
        func_80B4516C(this);
        if (gSaveContext.weekEventReg[21] & 0x20) {
            if (gSaveContext.weekEventReg[54] & 0x10) {
                this->actor.textId = 0x332E;
            } else {
                this->actor.textId = 0x332D;
            }

        } else {
            this->actor.textId = 0x332C;
        }
    }
}

void func_80B4AB8C(Actor* thisx, GlobalContext* globalCtx) {
    EnInvadepoh* this = THIS;

    if ((gSaveContext.time < 0x4000) && (gSaveContext.time >= 0x1800)) {
        this->actor.update = func_80B4ABDC;
        this->actor.draw = func_80B4E324;
        func_80B4A614(this);
    }
}

void func_80B4ABDC(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnInvadepoh* this = THIS;
    s32 sp2C;
    s32 temp_v0;

    sp2C = (thisx->flags & 0x40) == 0x40;
    temp_v0 = func_800B84D0(&this->actor, globalCtx);
    if (temp_v0 != 0) {
        func_80151BB4(globalCtx, 5);
        func_80B4A7C0(&this->actor);
    }
    this->actionFunc(this, globalCtx);
    if (sp2C != 0) {
        this->animPlayFlag = SkelAnime_FrameUpdateMatrix(&this->skelAnime);
        func_80B45CE0(&this->behaviorInfo);
        if (this->actionFunc != func_80B4A81C) {
            if (temp_v0 == 0) {
                if (this->actor.isTargeted) {
                    func_800B8614(&this->actor, globalCtx, 100.0f);
                }
            }
        }
        Collider_UpdateCylinder(&this->actor, &this->collider);
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }
}

void func_80B4ACDC(EnInvadepoh* this) {
    this->actionFunc = func_80B4ACF0;
}

void func_80B4ACF0(EnInvadepoh* this, GlobalContext* globalCtx) {
    if (gSaveContext.weekEventReg[22] & 1) {
        this->actor.draw = func_80B4E324;
        this->actor.flags |= 9;
        func_80B4AD3C(this);
    }
}

void func_80B4AD3C(EnInvadepoh* this) {
    this->actor.flags |= 0x10000;
    this->actionFunc = func_80B4AD60;
}

void func_80B4AD60(EnInvadepoh* this, GlobalContext* globalCtx) {
    if (func_800B84D0(&this->actor, globalCtx)) {
        func_80B4560C(this, globalCtx, 0x3331);
        func_80B4ADB8(this);
    } else {
        func_800B8614(&this->actor, globalCtx, 2000.0f);
    }
}

void func_80B4ADB8(EnInvadepoh* this) {
    this->actionFunc = func_80B4ADCC;
}

void func_80B4ADCC(EnInvadepoh* this, GlobalContext* globalCtx) {
    if ((func_80152498(&globalCtx->msgCtx) == 5) && func_80147624(globalCtx)) {
        if (this->textId == 0x3331) {
            if (gSaveContext.weekEventReg[22] & 2) {
                func_80B4560C(this, globalCtx, 0x3334);
                func_80151BB4(globalCtx, 0x1D);
                func_80151BB4(globalCtx, 5);
                return;
            }
            func_80B4560C(this, globalCtx, 0x3333);
            return;
        }
        if (this->textId == 0x3333) {
            func_80B4AEC0(this);
            return;
        }
        if (this->textId == 0x3334) {
            func_801477B4(globalCtx);
            func_80B4B024(this);
        }
    }
}

void func_80B4AEC0(EnInvadepoh* this) {
    this->actionTimer = 2;
    this->actionFunc = func_80B4AEDC;
}

void func_80B4AEDC(EnInvadepoh* this, GlobalContext* globalCtx) {
    if (this->actionTimer > 0) {
        this->actionTimer--;
        if (this->actionTimer == 0) {
            func_801477B4(globalCtx);
        }
    }
    if (Actor_HasParent(&this->actor, globalCtx)) {
        this->actor.parent = NULL;
        gSaveContext.weekEventReg[22] |= 2;
        func_80B4AF80(this);
    } else {
        func_800B8A1C(&this->actor, globalCtx, 0x60, 2000.0f, 2000.0f);
    }
}

void func_80B4AF80(EnInvadepoh* this) {
    this->actionFunc = func_80B4AF94;
}

void func_80B4AF94(EnInvadepoh* this, GlobalContext* globalCtx) {
    if (func_800B84D0(&this->actor, globalCtx)) {
        func_80B4560C(this, globalCtx, 0x3334);
        func_80151BB4(globalCtx, 0x1E);
        func_80151BB4(globalCtx, 0x1D);
        func_80151BB4(globalCtx, 5);
        func_80B4ADB8(this);
    } else {
        func_800B85E0(&this->actor, globalCtx, 2000.0f, -1);
    }
}

void func_80B4B024(EnInvadepoh* this) {
    this->actor.flags &= ~9;
    this->actionFunc = func_80B4B048;
}

void func_80B4B048(EnInvadepoh* this, GlobalContext* globalCtx) {
    if (globalCtx->msgCtx.unk120B1 == 0) {
        if (globalCtx->msgCtx.unk11F22 == 0) {
            D_80B4E998 = 1;
        } else if ((func_80152498(&globalCtx->msgCtx) == 6) || (func_80152498(&globalCtx->msgCtx) == 5)) {
            D_80B4E998 = 1;
        }
    }
}

void func_80B4B0C4(Actor* thisx, GlobalContext* globalCtx) {
    EnInvadepoh* this = THIS;
    AlienBehaviorInfo* substruct;
    s32 pad;

    if (Object_IsLoaded(&globalCtx->objectCtx, this->bankIndex)) {
        this->actor.objBankIndex = this->bankIndex;
        Actor_SetObjectSegment(globalCtx, &this->actor);
        func_80B44F58();
        this->actor.update = func_80B4B218;
        SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06013928, &D_06014088, this->limbDrawTable,
                         this->transitionDrawTable, 23);
        SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_06009E58, 0.0f);
        substruct = &this->behaviorInfo;
        func_80B45C04(&this->behaviorInfo, &D_80B4EA90, 1, &D_80B4EB00, 3, &D_801D15BC, 0x7D0, 0.08f, 0.3f, 0.03f);
        substruct->unk30 = 0.08f;
        substruct->unk2C = 0x7D0;
        func_800B4AEC(globalCtx, &this->actor, 50.0f);
        func_80B4516C(this);
        func_80B4ACDC(this);
    }
}

void func_80B4B218(Actor* thisx, GlobalContext* globalCtx) {
    s16 diff;
    EnInvadepoh* this = THIS;
    s16 temp_v1;
    s32 sp38;
    Player* player;
    AlienBehaviorInfo* substruct = &this->behaviorInfo;

    sp38 = (this->actor.flags & 0x40) == 0x40;
    this->actionFunc(this, globalCtx);
    if (sp38 != 0 && this->actor.update != NULL) {
        SkelAnime_FrameUpdateMatrix(&this->skelAnime);
        player = PLAYER;
        Math_StepToS(&this->behaviorInfo.unk4C, 0x7D0, 0x28);
        Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 6, this->behaviorInfo.unk4C, 0x28);
        temp_v1 = (Math_Vec3f_Pitch(&this->actor.focus.pos, &player->actor.focus.pos) * 0.9f);
        temp_v1 -= this->actor.shape.rot.x;
        substruct->unk26.x = CLAMP(temp_v1, -0xBB8, 0xBB8);
        diff = (s16)(this->actor.yawTowardsPlayer - this->actor.shape.rot.y);
        temp_v1 = diff;
        temp_v1 *= 0.7f;
        substruct->unk26.y = CLAMP(temp_v1, -0x1F40, 0x1F40);
        func_80B45CE0(substruct);
        Collider_UpdateCylinder(&this->actor, &this->collider);
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }
}

void func_80B4B3DC(EnInvadepoh* this) {
    s32 pad;

    if (func_801378B8(&this->skelAnime, 1.0f) || func_801378B8(&this->skelAnime, 7.0f)) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EV_MONKEY_WALK);
    }
}

void func_80B4B430(EnInvadepoh* this) {
    SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_060021C8, -6.0f);
    this->actionTimer = Rand_S16Offset(50, 80);
    this->actionFunc = func_80B4B484;
}

void func_80B4B484(EnInvadepoh* this, GlobalContext* globalCtx) {
    Math_StepToF(&this->actor.speedXZ, 1.1f, 0.5f);
    if (func_80B44C80(this, globalCtx)) {
        func_80B44690(this);
    }
    func_80B4B3DC(this);
    if (this->unk3BC >= 0) {
        this->actionTimer = 0;
    }

    if (this->actionTimer > 0) {
        this->actionTimer--;
    } else {
        func_80B4B510(this);
    }
}

void func_80B4B510(EnInvadepoh* this) {
    SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_06001BD8, -6.0f);
    this->actionTimer = Rand_S16Offset(50, 200);
    this->actionFunc = func_80B4B564;
}

void func_80B4B564(EnInvadepoh* this, GlobalContext* globalCtx) {
    s32 pad;
    Vec3f sp28;
    f32 temp_f0;

    Math_StepToF(&this->actor.speedXZ, 3.8f, 0.45f);

    if (this->unk3BC >= 0) {
        Math_Vec3s_ToVec3f(&sp28, &this->pathPoints[this->unk3BC]);
        temp_f0 = Math3D_DistanceSquared(&this->actor.world.pos, &sp28);
        if (temp_f0 < SQ(80.0f)) {
            this->actor.speedXZ *= 0.85f;
        } else if (temp_f0 < SQ(150.0f)) {
            this->actor.speedXZ *= 0.93f;
        } else if (temp_f0 < SQ(250.0f)) {
            this->actor.speedXZ *= 0.96f;
        }
        if (this->unk309 == this->unk3BC || temp_f0 < SQ(50.0f)) {
            this->actionTimer = 0;
        }
    }
    func_80B4B3DC(this);
    if (func_80B44C80(this, globalCtx)) {
        func_80B44690(this);
    }

    if (this->actionTimer > 0) {
        this->actionTimer--;
        return;
    }
    if (this->unk3BC >= 0) {
        if (D_80B50348 == 0) {
            if (Rand_ZeroOne() < 0.4f) {
                Audio_PlayActorSound2(&this->actor, NA_SE_EV_SMALL_DOG_GROAN);
            }
        }
        func_80B4B724(this);

    } else {
        func_80B4B430(this);
    }
}

void func_80B4B724(EnInvadepoh* this) {
    SkelAnime_ChangeAnimTransitionStop(&this->skelAnime, &D_06000998, -6.0f);
    this->actionFunc = func_80B4B768;
}

void func_80B4B768(EnInvadepoh* this, GlobalContext* globalCtx) {
    s32 pad;

    Math_StepToF(&this->actor.speedXZ, 0.0f, 1.0f);
    Math_SmoothStepToS(&this->actor.world.rot.y, Actor_YawBetweenActors(&this->actor, D_80B5040C), 5, 5000, 100);
    func_80B44E90(this, globalCtx);
    if (func_801378B8(&this->skelAnime, 13.0f) || func_801378B8(&this->skelAnime, 19.0f)) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EV_SMALL_DOG_ANG_BARK);
    }
    if (this->animPlayFlag != 0) {
        func_80B4B510(this);
    }
}

void func_80B4B820(EnInvadepoh* this) {
    SkelAnime_ChangeAnimTransitionStop(&this->skelAnime, &D_06001560, -6.0f);
    this->actionFunc = func_80B4B864;
}

void func_80B4B864(EnInvadepoh* this, GlobalContext* globalCtx) {
    Math_StepToF(&this->actor.speedXZ, 0.5f, 1.0f);
    func_80B44E90(this, globalCtx);
    if (this->animPlayFlag != 0) {
        func_80B4B510(this);
    }
}

void func_80B4B8BC(Actor* thisx, GlobalContext* globalCtx) {
    EnInvadepoh* this = THIS;
    s32 pad;

    if (Object_IsLoaded(&globalCtx->objectCtx, this->bankIndex)) {
        this->actor.objBankIndex = this->bankIndex;
        Actor_SetObjectSegment(globalCtx, &this->actor);
        SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_060080F0, &D_060021C8, this->limbDrawTable,
                         this->transitionDrawTable, 13);
        func_80B45C04(&this->behaviorInfo, 0, 0, 0, 0, &D_801D15BC, 0xBB8, 0.1f, 0.0f, 0.0f);
        func_80B44664(this, globalCtx);
        func_80B4407C(this, 0);
        func_800B4AEC(globalCtx, &this->actor, 50.0f);
        func_80B4516C(this);
        Math_Vec3f_Copy(&this->curPathPos, &this->actor.world.pos);
        if (D_80B4E940 == 2) {
            this->actor.update = func_80B4BA84;
            this->actor.draw = func_80B4E660;
            this->actor.flags |= 1;
            func_80B4B430(this);
        } else if (D_80B4E940 == 1) {
            this->actor.update = func_80B4BA30;
        } else {
            Actor_MarkForDeath(&this->actor);
            if (!this) {} // required for some reason
        }
    }
}

void func_80B4BA30(Actor* thisx, GlobalContext* globalCtx) {
    EnInvadepoh* this = THIS;

    if (D_80B4E940 == 2) {
        this->actor.update = func_80B4BA84;
        this->actor.draw = func_80B4E660;
        this->actor.flags |= 1;
        func_80B4B430(this);
    }
}

void func_80B4BA84(Actor* thisx, GlobalContext* globalCtx) {
    EnInvadepoh* this = THIS;
    s32 temp_v0_3;
    s32 sp34 = (this->actor.flags & 0x40) == 0x40;
    s32 temp_v1_2;
    s32 sp2C;
    s32 temp_v0_2;
    s32 phi_v0;

    D_80B5040C = func_80B458D8();
    if (D_80B5040C == 0) {
        temp_v0_2 = (this->unk3BC < 0) ^ 1;
        this->unk3BC = -1;
        if (temp_v0_2) {
            func_80B4B820(this);
        }

    } else {
        sp2C = this->unk3BC;
        this->unk3BC = func_80B44234(this, &D_80B5040C->world.pos);
        if (sp2C != this->unk3BC) {
            phi_v0 = this->unk309;
            phi_v0 = this->unk3BC - this->unk309;
            temp_v0_3 = phi_v0;
            if (temp_v0_3 < 0) {
                phi_v0 += this->unk308;
            }

            temp_v0_3 = this->unk308 >> 1;
            if (temp_v0_3 < phi_v0) {
                this->unk30A = -1;
            } else if (phi_v0 < temp_v0_3) {
                this->unk30A = 1;
            }
        }
    }

    this->actionFunc(this, globalCtx);
    this->animPlayFlag = SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    if ((sp34 != 0) && (this->actor.update != 0)) {
        func_80B45CE0(&this->behaviorInfo);
        Collider_UpdateCylinder(&this->actor, &this->collider);
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }
}

void func_80B4BBE0(EnInvadepoh* this) {
    AlienBehaviorInfo* substruct = &this->behaviorInfo;

    SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_06016720, -6.0f);
    substruct->unk26.x = 0;
    substruct->unk26.y = 0;
    substruct->unk26.z = 0;
    substruct->unk30 = 0.1f;
    substruct->unk2C = 800;

    this->behaviorInfo.unk4C = 0;
    this->actionFunc = func_80B4BC4C;
}

void func_80B4BC4C(EnInvadepoh* this, GlobalContext* globalCtx) {
    s8 temp_v0;
    s16 diff;
    EnInvadepoh* temp_t6 = (EnInvadepoh*)D_80B503F4;
    s16 temp_v1_2;
    s32 temp_v1;
    AlienBehaviorInfo* substruct = &this->behaviorInfo;
    s16 temp_a0;
    s16 sp40;

    if (temp_t6 != NULL) {
        temp_v0 = temp_t6->unk309;
        if (temp_v0 == 0) {
            this->unk2F8 = 40.0f;
            this->unk304 = -0x8000;
            this->actor.flags &= ~0x9;

        } else if (temp_v0 < (temp_t6->unk308 - 1)) {
            this->unk2F8 = 40.0f;
            Math_ScaledStepToS(&this->unk304, -0x4800, 0xC8);
            this->actor.flags |= 9;
        } else {
            Math_StepToF(&this->unk2F8, 5.0f, 3.0f);
            Math_ScaledStepToS(&this->unk304, -0x8000, 0x12C);
            this->actor.flags &= ~0x9;
        }
        temp_a0 = this->unk304 + temp_t6->actor.world.rot.y;
        this->actor.world.pos.x = (Math_SinS(temp_a0) * this->unk2F8) + temp_t6->actor.world.pos.x;
        this->actor.world.pos.y = temp_t6->actor.world.pos.y;
        this->actor.world.pos.z = (Math_CosS(temp_a0) * this->unk2F8) + temp_t6->actor.world.pos.z;
        func_800B4AEC(globalCtx, &this->actor, 50.0f);
        func_80B4516C(this);
        Math_StepToS(&this->behaviorInfo.unk4C, 0xBB8, 0x1F5);
        if (0.0001f < Math3D_DistanceSquared(&this->actor.prevPos, &this->actor.world)) {
            Math_SmoothStepToS(&this->actor.shape.rot.y, Math_Vec3f_Yaw(&this->actor.prevPos, &this->actor.world), 3,
                               this->behaviorInfo.unk4C, 0x1F4);
        }
        temp_v1 = (globalCtx->gameplayFrames + 0x14) & 0x7F;
        if ((temp_v1 & 0x40) != 0) {
            sp40 = Math_Vec3f_Yaw(&this->actor.world, &temp_t6->actor.world.pos);
            if (temp_v1 == 0x40) {
                this->behaviorInfo.unk4C = 0;
            }
            Math_StepToS(&this->behaviorInfo.unk4C, 0x7D0, 0x28);
            Math_SmoothStepToS(&this->actor.shape.rot.y, sp40, 6, this->behaviorInfo.unk4C, 0x28);
            temp_v1_2 = Math_Vec3f_Pitch(&this->actor.focus.pos, &temp_t6->actor.focus.pos);
            temp_v1_2 *= 0.85f;
            temp_v1_2 -= this->actor.shape.rot.x;
            substruct->unk26.x = CLAMP(temp_v1_2, -0xBB8, 0xBB8);
            diff = (s16)(sp40 - this->actor.shape.rot.y);
            temp_v1_2 = diff;
            temp_v1_2 *= 0.7f;
            substruct->unk26.y = CLAMP(temp_v1_2, -0x1F40, 0x1F40);
        }
    }

    if ((this->actor.flags & 0x40) == 0x40) {
        if ((func_801378B8(&this->skelAnime, 0.0f)) || (func_801378B8(&this->skelAnime, 12.0f))) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_ROMANI_WALK);
        }
    }
    if (gSaveContext.time >= 0xD801) {
        Actor_MarkForDeath(&this->actor);
        return;
    }
    if ((temp_t6 != NULL) && (temp_t6->actionFunc == func_80B4CB0C)) {
        func_80B4C1BC(this);
    }
}

void func_80B4BFFC(EnInvadepoh* this) {
    this->behaviorInfo.unk30 = 0.08f;
    this->behaviorInfo.unk2C = 2000;
    SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_0600A174, -6.0f);
    this->behaviorInfo.unk4C = 0;
    this->actionFunc = func_80B4C058;
}

void func_80B4C058(EnInvadepoh* this, GlobalContext* globalCtx) {
    AlienBehaviorInfo* substruct = &this->behaviorInfo;
    Player* player;
    s16 temp_v1;
    s16 diff;

    player = PLAYER;
    Math_StepToS(&this->behaviorInfo.unk4C, 0x9C4, 0x1C2);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, this->behaviorInfo.unk4C, 0x28);
    temp_v1 = Math_Vec3f_Pitch(&this->actor.focus.pos, &player->actor.focus.pos);
    temp_v1 *= 0.85f;
    temp_v1 -= this->actor.shape.rot.x;
    substruct->unk26.x = CLAMP(temp_v1, -0xBB8, 0xBB8);

    diff = (s16)(this->actor.yawTowardsPlayer - this->actor.shape.rot.y);
    temp_v1 = diff;
    temp_v1 *= 0.7f;

    substruct->unk26.y = CLAMP(temp_v1, -0x1F40, 0x1F40);

    if (func_800B867C(&this->actor, globalCtx)) {
        func_80B4BBE0(this);
    }
}

void func_80B4C1BC(EnInvadepoh* this) {
    this->behaviorInfo.unk30 = 0.08f;
    this->behaviorInfo.unk2C = 2000;
    SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_0600A174, -6.0f);
    this->behaviorInfo.unk4C = 0;
    this->actionFunc = func_80B4C218;
}

void func_80B4C218(EnInvadepoh* this, GlobalContext* globalCtx) {
    AlienBehaviorInfo* substruct = &this->behaviorInfo;
    Player* player;
    Actor* temp_v0;
    s16 temp_v1;
    s16 diff;

    player = PLAYER;

    Math_StepToS(&this->behaviorInfo.unk4C, 0x7D0, 0xC8);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 6, this->behaviorInfo.unk4C, 0x28);
    temp_v1 = Math_Vec3f_Pitch(&this->actor.focus.pos, &player->actor.focus.pos);
    temp_v1 *= 0.85f;
    temp_v1 -= this->actor.shape.rot.x;
    substruct->unk26.x = CLAMP(temp_v1, -0xBB8, 0xBB8);
    diff = (s16)(this->actor.yawTowardsPlayer - this->actor.shape.rot.y);
    temp_v1 = diff;
    temp_v1 *= 0.7f;
    substruct->unk26.y = CLAMP(temp_v1, -0x1F40, 0x1F40);

    if (D_80B503F4 == NULL) { // both checks against null seem to be required
        func_80B4BBE0(this);
        return;
    }
    if (D_80B503F4 != NULL) {
        if (((EnInvadepoh*)D_80B503F4)->actionFunc != func_80B4CB0C) {
            func_80B4BBE0(this);
        }
    }
}

void func_80B4C3A0(Actor* thisx, GlobalContext* globalCtx) {
    EnInvadepoh* this = THIS;

    if (Object_IsLoaded(&globalCtx->objectCtx, this->bankIndex)) {
        s32 pad[2];
        s32 sp38 = gSaveContext.time;

        this->actor.objBankIndex = this->bankIndex;
        Actor_SetObjectSegment(globalCtx, &this->actor);
        func_80B44FEC();
        SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06015C28, &D_06016720, (0, this->limbDrawTable),
                         this->transitionDrawTable, 22);
        func_80B45C04(&this->behaviorInfo, D_80B4EBDC, 1, D_80B4EC08, 0, &D_801D15BC, 0x64, 0.03f, 0.3f, 0.03f);
        this->actor.textId = 0x33CD;
        if (sp38 < 0xD5A0) {
            this->unk304 = -0x8000;
            this->unk2F8 = 40.0f;
        } else if (sp38 >= 0xD7D4) {
            this->unk304 = -0x4800;
            this->unk2F8 = 20.0f;
        } else {
            this->unk304 = -0x8000;
            this->unk2F8 = 40.0f;
        }

        if ((sp38 >= 0x4000) && (sp38 < 0xD573)) {
            this->actor.update = func_80B4C568;
            this->actor.draw = 0;
        } else if ((sp38 >= 0xD573) && (sp38 < 0xD800)) {
            this->actor.update = func_80B4C5C0;
            this->actor.draw = func_80B4E7BC;
            func_80B4BBE0(this);
        } else {
            Actor_MarkForDeath(&this->actor);
        }
    }
}

void func_80B4C568(Actor* thisx, GlobalContext* globalCtx) {
    EnInvadepoh* this = THIS;

    if ((gSaveContext.time >= 0xD573) && (gSaveContext.time < 0xD800)) {
        this->actor.update = func_80B4C5C0;
        this->actor.draw = func_80B4E7BC;
        func_80B4BBE0(this);
    }
}

void func_80B4C5C0(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnInvadepoh* this = THIS;
    s32 sp2C;
    s32 temp_v0;

    sp2C = (this->actor.flags & 0x40) == 0x40;
    temp_v0 = func_800B84D0(&this->actor, globalCtx);
    if (temp_v0) {
        func_80151BB4(globalCtx, 6);
        func_80B4BFFC(thisx);
    }
    this->actionFunc(this, globalCtx);
    if (sp2C != 0) {
        if (this->actor.update != NULL) {
            SkelAnime_FrameUpdateMatrix(&this->skelAnime);
            func_80B45CE0(&this->behaviorInfo);
            if (this->actionFunc != func_80B4C058) {
                if (!temp_v0) {
                    if (this->actor.isTargeted) {
                        func_800B8614(&this->actor, globalCtx, 350.0f);
                    }
                }
            }
            Collider_UpdateCylinder(&this->actor, &this->collider);
            CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        }
    }
}

void func_80B4C6C8(EnInvadepoh* this) {
    AlienBehaviorInfo* substruct = &this->behaviorInfo;

    SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_06014088, -10.0f);
    substruct->unk26.x = 0;
    substruct->unk26.y = 0;
    substruct->unk26.z = 0;
    substruct->unk30 = 0.1f;
    substruct->unk2C = 0x320;
    this->actionFunc = func_80B4C730;
}

void func_80B4C730(EnInvadepoh* this, GlobalContext* globalCtx) {
    AlienBehaviorInfo* substruct = &this->behaviorInfo;
    EnInvadepoh* sp68;
    s32 phi_a2;
    s32 temp_v1_3;
    s16 temp_v1_4;
    s32 temp_v0_2;
    Vec3f sp4C;
    Vec3f sp40;
    s16 diff;
    s8 temp_v1;
    s16 sp3A;
    s8 temp_v0;
    sp68 = D_80B503F8;
    func_80B44700(this);
    func_80B44EFC(this, globalCtx);
    func_80B43E6C(this, 6, 0x7D0, 0x64);
    if (1) {} // required to match, also in the other function above that looks like this one
    temp_v1 = this->unk309;
    temp_v0 = this->unk308;
    phi_a2 = temp_v0 - 1;
    if (temp_v1 < temp_v0) {
        phi_a2 = temp_v1;
    } else if (temp_v1_3) { // fake match probably
    }

    Math_Vec3s_ToVec3f(&sp4C, &this->pathPoints[phi_a2]);
    Math_Vec3s_ToVec3f(&sp40, &this->pathPoints[phi_a2 + 1]);
    Math_SmoothStepToS(&this->actor.world.rot.y, Math_Vec3f_Yaw(&sp4C, &sp40), 5, 0x7D0, 0x64);
    if ((this->unk309 == 0) || (this->unk309 + 1 == this->unk308)) {
        if (this->unk378 == 0) {
            temp_v0_2 = func_800FE620(globalCtx);
            if (temp_v0_2 > 0) {
                temp_v0_2 = (REG(15) * -23.0f / temp_v0_2) - 0.5f;
                this->unk378 = func_80B45550(this, globalCtx, SQ(80.0f), temp_v0_2);
            }
        }

        this->actor.flags &= ~0x9;
    } else {
        this->unk378 = 0;
        this->actor.flags |= 9;
    }

    temp_v1_3 = globalCtx->gameplayFrames & 0x7F;
    if ((temp_v1_3 & 0x40) != 0) {
        sp3A = Math_Vec3f_Yaw(&this->actor.world, &sp68->actor.world);
        if (temp_v1_3 == 0x40) {
            this->behaviorInfo.unk4C = 0;
        }

        Math_StepToS(&this->behaviorInfo.unk4C, 0x7D0, 0x28);
        Math_SmoothStepToS(&this->actor.shape.rot.y, sp3A, 6, this->behaviorInfo.unk4C, 0x28);
        temp_v1_4 = Math_Vec3f_Pitch(&this->actor.focus.pos, &sp68->actor.focus.pos);
        temp_v1_4 *= 0.85f;
        temp_v1_4 -= this->actor.shape.rot.x;
        substruct->unk26.x = CLAMP(temp_v1_4, -0xBB8, 0xBB8);
        diff = (s16)(sp3A - this->actor.shape.rot.y);
        temp_v1_4 = diff;
        temp_v1_4 *= 0.7f;
        substruct->unk26.y = CLAMP(temp_v1_4, -0x1F40, 0x1F40);
    }

    if ((this->actor.flags & 0x40) == 0x40) {
        if (func_801378B8(&this->skelAnime, 0.0f) || func_801378B8(&this->skelAnime, 7.0f)) {
            Audio_PlayActorSound2(&this->actor, 0x3ABE);
        }
    }

    if (0.9999f <= this->clockTime) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    if ((sp68 != 0) && (sp68->actionFunc == func_80B4C058)) {
        func_80B4CC70(this);
    }
}

void func_80B4CAB0(EnInvadepoh* this) {
    this->behaviorInfo.unk30 = 0.08f;
    this->behaviorInfo.unk2C = 4000;
    SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_06009E58, -10.0f);
    this->behaviorInfo.unk4C = 0;
    this->actionFunc = func_80B4CB0C;
}

void func_80B4CB0C(EnInvadepoh* this, GlobalContext* globalCtx) {
    AlienBehaviorInfo* substruct = &this->behaviorInfo;
    Player* player;
    s16 temp_v1;
    s16 diff;

    player = PLAYER;
    Math_StepToS(&this->behaviorInfo.unk4C, 0xBB8, 0x1F4);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 6, this->behaviorInfo.unk4C, 0x28);
    temp_v1 = (Math_Vec3f_Pitch(&this->actor.focus.pos, &player->actor.focus.pos));
    temp_v1 *= 0.85f;
    temp_v1 -= this->actor.shape.rot.x;
    substruct->unk26.x = CLAMP(temp_v1, -0xBB8, 0xBB8);
    diff = (s16)(this->actor.yawTowardsPlayer - this->actor.shape.rot.y);
    temp_v1 = diff;
    temp_v1 *= 0.7f;
    substruct->unk26.y = CLAMP(temp_v1, -0x1F40, 0x1F40);
    if (func_800B867C(&this->actor, globalCtx)) {
        func_80B4C6C8(this);
    }
}

void func_80B4CC70(EnInvadepoh* this) {
    this->behaviorInfo.unk30 = 0.08f;
    this->behaviorInfo.unk2C = 2000;
    SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_06009E58, -10.0f);
    this->behaviorInfo.unk4C = 0;
    this->actionFunc = func_80B4CCCC;
}

void func_80B4CCCC(EnInvadepoh* this, GlobalContext* globalCtx) {
    AlienBehaviorInfo* substruct = &this->behaviorInfo;
    Player* player;
    s16 temp_v1;
    s16 diff;

    player = PLAYER;
    Math_StepToS(&this->behaviorInfo.unk4C, 0x7D0, 0xC8);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 6, this->behaviorInfo.unk4C, 0x28);
    temp_v1 = Math_Vec3f_Pitch(&this->actor.focus.pos, &player->actor.focus.pos);
    temp_v1 *= 0.85f;
    temp_v1 -= this->actor.shape.rot.x;
    substruct->unk26.x = CLAMP(temp_v1, -0xBB8, 0xBB8);
    diff = (s16)(this->actor.yawTowardsPlayer - this->actor.shape.rot.y);
    temp_v1 = diff;
    temp_v1 *= 0.7f;
    substruct->unk26.y = CLAMP(temp_v1, -0x1F40, 0x1F40);
    if (D_80B503F8 == NULL) {
        func_80B4C6C8(this);
    } else if ((D_80B503F8 != NULL) && ((EnInvadepoh*)D_80B503F8)->actionFunc != func_80B4C058) {
        func_80B4C6C8(this);
    }
}

void func_80B4CE54(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad[2];
    EnInvadepoh* this = THIS;
    s32 sp38;

    if (Object_IsLoaded(&globalCtx->objectCtx, this->bankIndex)) {
        sp38 = gSaveContext.time;

        this->actor.objBankIndex = this->bankIndex;
        Actor_SetObjectSegment(globalCtx, &this->actor);
        func_80B44F58();
        SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06013928, &D_06014088, this->limbDrawTable,
                         this->transitionDrawTable, 23);
        func_80B45C04(&this->behaviorInfo, &D_80B4EA90, 1, &D_80B4EB00, 3, &D_801D15BC, 0x64, 0.03f, 0.3f, 0.03f);
        func_80B446D0(this, globalCtx);
        this->actor.world.rot.y = this->actor.shape.rot.y;
        func_80B44700(this);
        func_80B44EFC(this, globalCtx);
        func_80B43F0C(this);
        func_80B4516C(this);
        this->actor.textId = 0x33CE;
        if ((sp38 >= 0x4000) && (sp38 < 0xD555)) {
            this->actor.update = func_80B4CFFC;
            this->actor.draw = NULL;
        } else if ((sp38 >= 0xD555) && (sp38 < 0xD7E1)) {
            this->actor.update = func_80B4D054;
            this->actor.draw = func_80B4E324;
            func_80B4C6C8(this);
        } else {
            Actor_MarkForDeath(&this->actor);
        }
    }
}

void func_80B4CFFC(Actor* thisx, GlobalContext* globalCtx) {
    EnInvadepoh* this = THIS;

    if ((gSaveContext.time >= 0xD555) && (gSaveContext.time < 0xD7E1)) {
        this->actor.update = func_80B4D054;
        this->actor.draw = func_80B4E324;
        func_80B4C6C8(this);
    }
}

void func_80B4D054(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnInvadepoh* this = THIS;
    s32 sp2C;
    s32 temp_v0;

    sp2C = (this->actor.flags & 0x40) == 0x40;
    temp_v0 = func_800B84D0(thisx, globalCtx);
    if (temp_v0) {
        func_80151BB4(globalCtx, 5);
        func_80B4CAB0(this);
    }
    this->actionFunc(this, globalCtx);
    if (sp2C != 0) {
        if (this->actor.update != NULL) {
            SkelAnime_FrameUpdateMatrix(&this->skelAnime);
            func_80B45CE0(&this->behaviorInfo);
            if (this->actionFunc != func_80B4CB0C) {
                if (!temp_v0) {
                    if (this->actor.isTargeted) {
                        func_800B8614(thisx, globalCtx, 350.0f);
                    }
                }
            }
            Collider_UpdateCylinder(&this->actor, &this->collider);
            CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        }
    }
}

void func_80B4D15C(EnInvadepoh* this) {
    s32 pad;
    s32 temp_v1 = this->actor.params & 7;
    unkstruct_80B4EE0C* temp_v0;

    SkelAnime_ChangeAnimDefaultRepeat(&this->skelAnime, &D_06001674);
    this->skelAnime.animCurrentFrame = ((this->actor.params & 7) * this->skelAnime.animFrameCount) * 0.25f;
    this->alienAlpha = 0xFF;
    this->actor.draw = func_80B4DB14;
    this->drawAlien = true;
    this->drawAlienDeathEffect = false;
    this->alienBeamAlpha = 0xFF;
    temp_v0 = &D_80B4EE0C[temp_v1];
    this->unk300 = temp_v0->unk00;
    this->unk304 = temp_v1 * 0x5555;
    this->actor.world.pos.x = this->actor.home.pos.x + (Math_SinS(this->unk304) * 80.0f);
    this->actor.world.pos.y = this->actor.home.pos.y;
    this->actor.world.pos.z = this->actor.home.pos.z + (Math_CosS(this->unk304) * 80.0f);
    this->actor.shape.rot.y = this->unk304 + 0x4000;
    this->behaviorInfo.unk4C = temp_v0->unk04;
    this->behaviorInfo.unk4E = temp_v0->unk06;
    this->actionFunc = func_80B4D290;
    this->actor.velocity.y = 0.0f;
}

void func_80B4D290(EnInvadepoh* this, GlobalContext* globalCtx) {
    f32 temp_f10;
    f32 sp28;
    Actor* temp_v1;
    if (D_80B503F0 == 0) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    Math_StepToF(&this->actor.velocity.y, 15.0f, this->unk300);
    sp28 = Math_SmoothStepToF(&this->actor.world.pos.y, this->actor.home.pos.y + 850.0f, 0.2f, this->actor.velocity.y,
                              0.01f);
    this->unk304 += 0x2BC;
    this->actor.world.pos.x = (Math_SinS(this->unk304) * 80.0f) + this->actor.home.pos.x;
    temp_f10 = Math_CosS(this->unk304) * 80.0f;
    this->behaviorInfo.unk4C += this->behaviorInfo.unk4E;
    temp_v1 = this->actor.child;
    this->actor.shape.rot.y += this->behaviorInfo.unk4C;
    this->actor.world.pos.z = this->actor.home.pos.z + ((0, temp_f10));
    if (this->actor.child != 0) {
        this->actor.child->world.pos.x = this->actor.world.pos.x;
        temp_v1->world.pos.y = this->actor.world.pos.y - 38.0f;
        temp_v1->world.pos.z = this->actor.world.pos.z;
        temp_v1->shape.rot.y = this->actor.shape.rot.y;
    }

    if (sp28 < 5.0f) {
        Actor_MarkForDeath(&this->actor);
    }
}

void func_80B4D3E4(EnInvadepoh* this) {
    SkelAnime_ChangeAnimDefaultRepeat(&this->skelAnime, &D_06001674);
    this->skelAnime.animCurrentFrame = (this->actor.params & 7) * this->skelAnime.animFrameCount * 0.25f;
    this->alienAlpha = 0xFF;
    this->actor.draw = 0;
    this->drawAlien = true;
    this->drawAlienDeathEffect = false;
    this->alienBeamAlpha = 0xFF;
    this->unk306 = 400;
    this->unk304 = 0;
    this->actionTimer = 200;
    this->actor.velocity.y = 0.0f;
    this->actionFunc = func_80B4D480;
}

void func_80B4D480(EnInvadepoh* this, GlobalContext* globalCtx) {
    f32 target;
    s32 pad2;
    s32 sp2C;
    f32 new_var3;

    sp2C = false;
    if (this->actionTimer > 0) {
        this->actionTimer--;
    }

    if (this->actionTimer > 160) {
        this->actor.draw = NULL;
    } else {
        this->actor.draw = func_80B4DB14;
        if (1) {}
        if ((this->actionTimer < 105) && (this->actionTimer >= 100)) {
            this->actor.gravity = -1.0f;
            Math_SmoothStepToS(&this->actor.shape, 0x2000, 8, 0x320, 0x28);
        } else {
            this->actor.gravity = 0.7f;
            Math_SmoothStepToS(&this->actor.shape, 0, 8, 0x320, 0x28);
        }

        this->actor.velocity.y += this->actor.gravity;
        this->actor.velocity.y *= 0.92f;
        if (this->actionTimer > 80) {
            this->actor.world.pos.y += this->actor.velocity.y;
        } else {
            target = (this->actor.home.pos.y + 850.0f);
            sp2C = Math_StepToF(&this->actor.world.pos.y, target, fabsf(this->actor.velocity.y));
        }

        new_var3 = (this->unk304 * -0.06f + this->unk306);
        new_var3 *= 0.98f;
        this->unk306 = new_var3;
        this->actor.shape.rot.y += this->unk306;

        if (this->actor.child != NULL) {
            Actor* temp_v1 = this->actor.child;

            temp_v1->world.pos.x = this->actor.world.pos.x;
            temp_v1->world.pos.y = this->actor.world.pos.y - 30.0f;
            temp_v1->world.pos.z = this->actor.world.pos.z;
            temp_v1->shape.rot.y = this->actor.shape.rot.y;
        }
    }

    if ((this->actionTimer <= 0) || sp2C) {
        Actor_MarkForDeath(&this->actor);
    }
}

void func_80B4D670(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnInvadepoh* this = THIS;
    s32 invadepohType;

    if (Object_IsLoaded(&globalCtx->objectCtx, this->bankIndex)) {
        invadepohType = this->actor.params & 7;
        this->actor.objBankIndex = this->bankIndex;
        Actor_SetObjectSegment(globalCtx, &this->actor);
        func_80B45080();
        this->actor.update = func_80B4D760;
        SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06004E50, &D_06001674, this->limbDrawTable,
                         this->transitionDrawTable, 14);
        if (invadepohType < 3) {
            func_80B453F4(this, globalCtx, invadepohType);
            func_80B4D15C(this);
        } else {
            func_80B45460(this, globalCtx);
            func_80B4D3E4(this);
        }
    }
}

void func_80B4D760(Actor* thisx, GlobalContext* globalCtx) {
    EnInvadepoh* this = THIS;

    this->actionFunc(this, globalCtx);
    if (this->actor.update != NULL) {
        SkelAnime_FrameUpdateMatrix(&this->skelAnime);
        func_800B9010(&this->actor, NA_SE_EN_FOLLOWERS_BEAM_PRE - SFX_FLAG);
    }
}

void func_80B4D7B8(GlobalContext* globalCtx) {
    s32 temp_v0;
    u32 temp_s5;
    u32 temp_s6;
    unkStruct_80B50350* phi_s2;
    s32 i;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C2DC(globalCtx->state.gfxCtx);
    for (phi_s2 = D_80B50350, i = 0; i < 10; phi_s2++, i++) {
        if (phi_s2->unk1 > 0) {
            temp_v0 = globalCtx->gameplayFrames;
            temp_s5 = (temp_v0 + ((0x10 * i) & 0xFFu)) & 0x7F; // not sure about all this
            temp_s6 = (temp_v0 * -0xF) & 0xFF;
            SysMatrix_InsertTranslation(phi_s2->unk4.x, phi_s2->unk4.y, phi_s2->unk4.z, MTXMODE_NEW);
            Matrix_Scale(0.1f, 0.1f, 0.1f, MTXMODE_APPLY);
            gDPPipeSync(POLY_XLU_DISP++);
            gDPSetPrimColor(POLY_XLU_DISP++, 0x80, 0x80, 0xFF, 0xFF, 0xAA, phi_s2->unk2);
            gDPSetEnvColor(POLY_XLU_DISP++, 0xFF, 0x32, 0x00, 0x00);
            temp_v0 = globalCtx->gameplayFrames; // required ???
            gSPSegment(POLY_XLU_DISP++, 0x08,
                       Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, temp_s5, 0, 0x20, 0x40, 1, 0, temp_s6, 0x20, 0x40));
            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, &D_0402E510);
        }
    }
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_80B4D9B4(Actor* thisx, GlobalContext* globalCtx) {
    func_80B4D7B8(globalCtx);
}

s32 func_80B4D9D8(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx,
                  Gfx** gfx) {
    return 0;
}

void func_80B4D9F4(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx, Gfx** gfx) {
    EnInvadepoh* this = THIS;

    if ((limbIndex == 12) && (this->alienBeamAlpha != 0)) {
        SysMatrix_StatePush();
        SysMatrix_InsertZRotation_s(-0x53ED, MTXMODE_APPLY);
        Matrix_RotateY(-0x3830, MTXMODE_APPLY);
        Matrix_Scale(1.0f, 1.0f, 1.5f, MTXMODE_APPLY);
        SysMatrix_CopyCurrentState(&D_80B502A0);
        SysMatrix_StatePop();
    } else if ((limbIndex == 13) && (this->alienBeamAlpha != 0)) {
        SysMatrix_StatePush();
        SysMatrix_InsertZRotation_s(-0x53ED, MTXMODE_APPLY);
        Matrix_RotateY(-0x47D0, MTXMODE_APPLY);
        Matrix_Scale(1.0f, 1.0f, 1.5f, MTXMODE_APPLY);
        SysMatrix_CopyCurrentState(&D_80B502E0);
        SysMatrix_StatePop();
    }
    if (limbIndex == 11) {
        SysMatrix_MultiplyVector3fByState(&D_80B4EE24, &this->actor.focus.pos);
    }
}

void func_80B4DB14(Actor* thisx, GlobalContext* globalCtx) {
    EnInvadepoh* this = THIS;
    Gfx* gfx;
    GraphicsContext* spCC;

    spCC = globalCtx->state.gfxCtx;
    OPEN_DISPS(spCC);
    func_8012C2DC(spCC);
    SysMatrix_StatePush();
    if (this->drawAlien) {
        Gfx* new_var6;
        Gfx* spBC;
        GraphicsContext* spB8;

        if (this->alienAlpha == 255) {
            func_8012C28C(globalCtx->state.gfxCtx);
            AnimatedMat_Draw(globalCtx, D_80B50400);
            Scene_SetRenderModeXlu(globalCtx, 0, 1);
            gDPSetEnvColor(spCC->polyOpa.p++, 0, 0, 0, 255);
            spCC->polyOpa.p = SkelAnime_DrawSV2(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl,
                                                this->skelAnime.dListCount, func_80B4D9D8, func_80B4D9F4, &this->actor,
                                                spCC->polyOpa.p);
        } else {
            AnimatedMat_Draw(globalCtx, D_80B50400);
            Scene_SetRenderModeXlu(globalCtx, 1, 2);
            gDPSetEnvColor(spCC->polyXlu.p++, 0, 0, 0, this->alienAlpha);
            spCC->polyXlu.p = SkelAnime_DrawSV2(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl,
                                                this->skelAnime.dListCount, func_80B4D9D8, func_80B4D9F4, &this->actor,
                                                spCC->polyXlu.p);
        }

        if (this->alienBeamAlpha != 0) {
            AnimatedMat_Draw(globalCtx, D_80B503FC);
            spB8 = globalCtx->state.gfxCtx;
            gfx = spBC = spB8->polyXlu.p;
            gDPPipeSync(spBC++);
            gDPSetPrimColor(spBC++, 0, 255, 240, 180, 100, 60);
            gDPSetEnvColor(spBC++, 255, 255, 255, this->alienBeamAlpha * 0.5882353f);
            SysMatrix_InsertMatrix(&D_80B502A0, MTXMODE_NEW);
            gSPMatrix(spBC++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(spBC++, D_06000080);
            SysMatrix_InsertMatrix(&D_80B502E0, MTXMODE_NEW);
            gSPMatrix(spBC++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(spBC++, D_06000080);
            spB8->polyXlu.p = spBC;
        }
    }

    if (this->drawAlienDeathEffect) {
        SysMatrix_SetStateRotationAndTranslation(this->actor.world.pos.x, this->actor.world.pos.y + 68.0f,
                                                 this->actor.world.pos.z, &this->actor.shape.rot);
        Matrix_Scale(this->alienDeathEffectScale.x, this->alienDeathEffectScale.y, this->alienDeathEffectScale.z,
                     MTXMODE_APPLY);
        gSPMatrix(spCC->polyXlu.p++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(spCC->polyXlu.p++, D_06000720);
    }

    if (this->drawAlien) {
        Vec3f sp80;
        Vec3f sp74;
        s32 alpha2;
        GraphicsContext* sp6C = globalCtx->state.gfxCtx;
        u32 pad;

        gfx = sp6C->polyXlu.p;
        gfx = func_8012C868(gfx);
        gSPSetOtherMode(gfx++, G_SETOTHERMODE_H, 4, 4, 0x00000080);
        gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0);
        SysMatrix_InsertMatrix(&globalCtx->mf_187FC, MTXMODE_NEW);
        SysMatrix_GetStateTranslationAndScaledZ(60.0f, &sp80);
        sp74.x = thisx->world.pos.x + sp80.x;
        sp74.y = thisx->world.pos.y + sp80.y + 68.0f;
        sp74.z = thisx->world.pos.z + sp80.z;
        SysMatrix_InsertTranslation(sp74.x, sp74.y, sp74.z, MTXMODE_NEW);
        Matrix_Scale(0.25f, 0.25f, 0.25f, MTXMODE_APPLY);
        alpha2 = this->alienAlpha * 0.39215687f;
        gSPDisplayList(gfx++, D_04029CB0);
        gDPSetPrimColor(gfx++, 0, 0, 0xF0, 0xB4, 0x64, alpha2);
        gSPMatrix(gfx++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(gfx++, D_04029CF0);
        sp6C->polyXlu.p = gfx;
        if ((this->alienAlpha > 128) && func_80B456A8(globalCtx, &sp74)) {
            func_800F9824(globalCtx, &globalCtx->envCtx, &globalCtx->view, globalCtx->state.gfxCtx, sp74, 10.0f, 9.0f, 0, 0);
        }
    }

    SysMatrix_StatePop();
    CLOSE_DISPS(spCC);
}

s32 func_80B4E120(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    if (limbIndex == 5) {
        EnInvadepoh* this = THIS;
        rot->x -= this->actor.shape.rot.x;
    }
    return 0;
}

void func_80B4E158(Actor* thisx, GlobalContext* globalCtx) {
    EnInvadepoh* this = THIS;

    func_8012C5B0(globalCtx->state.gfxCtx);
    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount,
                     func_80B4E120, NULL, &this->actor);
}

void func_80B4E1B0(Actor* thisx, GlobalContext* globalCtx) {
    EnInvadepoh* this = THIS;

    func_8012C5B0(globalCtx->state.gfxCtx);
    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount, NULL,
                     NULL, &this->actor);
}

s32 func_80B4E200(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    if (limbIndex == 14) {
        EnInvadepoh* this = THIS; // both of these needed to match
        rot->x += this->behaviorInfo.unk20.y;
        rot->y += this->behaviorInfo.unk20.z;
        rot->z += this->behaviorInfo.unk20.x;
    } else if (limbIndex == 13) {
        EnInvadepoh* this = THIS; // both of these needed to match
        rot->x += (s16)(this->behaviorInfo.unk34 * this->behaviorInfo.unk20.y);
        rot->z += this->behaviorInfo.unk40;
    }
    return 0;
}

void func_80B4E2AC(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnInvadepoh* this = THIS;

    if (limbIndex == 19) {
        OPEN_DISPS(globalCtx->state.gfxCtx);
        gSPDisplayList(POLY_OPA_DISP++, D_060003B0);
        CLOSE_DISPS(globalCtx->state.gfxCtx);
    } else if (limbIndex == 14) {
        SysMatrix_MultiplyVector3fByState(&D_80B4EE30, &this->actor.focus.pos);
    }
}

void func_80B4E324(Actor* thisx, GlobalContext* globalCtx) {
    EnInvadepoh* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x09, D_80B4E958[this->behaviorInfo.unk10.unkF]);
    gSPSegment(POLY_OPA_DISP++, 0x08, D_80B4E944[this->behaviorInfo.unk0.unkF]);
    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount,
                     func_80B4E200, func_80B4E2AC, &this->actor);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_80B4E3F0(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad[2];
    Vec3f sp5C;

    SysMatrix_StatePush();
    SysMatrix_InsertMatrix(&globalCtx->mf_187FC, MTXMODE_NEW);
    SysMatrix_GetStateTranslationAndScaledZ(200.0f, &sp5C);
    SysMatrix_StatePop();
    sp5C.x += thisx->world.pos.x;
    sp5C.y += thisx->world.pos.y;
    sp5C.z += thisx->world.pos.z;
    func_80B45518(&sp5C);
    SysMatrix_NormalizeXYZ(&globalCtx->mf_187FC);
    SysMatrix_InsertZRotation_s(((EnInvadepoh*)thisx)->unk304, MTXMODE_APPLY);
    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C2DC(globalCtx->state.gfxCtx);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetPrimColor(POLY_XLU_DISP++, 0xFF, 0x80, 0xFF, 0xFF, 0x00, 0xB4);
    gDPSetEnvColor(POLY_XLU_DISP++, 0xFF, 0x32, 0x00, 0x00);
    gSPDisplayList(POLY_XLU_DISP++, D_04023210);
    if (func_80B456A8(globalCtx, &sp5C)) {
        func_800F9824(globalCtx, &globalCtx->envCtx, &globalCtx->view, globalCtx->state.gfxCtx, sp5C, 20.0f, 9.0f, 0,
                      0);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

s32 func_80B4E5B0(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    if ((limbIndex == 5) || (limbIndex == 6) || (limbIndex == 7)) {
        EnInvadepoh* this = THIS;
        rot->x += this->behaviorInfo.unk20.x;
        rot->y += this->behaviorInfo.unk20.y;
        rot->z += this->behaviorInfo.unk20.z;
    }

    return 0;
}

void func_80B4E61C(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    if (limbIndex == 5) {
        SysMatrix_GetStateTranslationAndScaledY(20.0f, &thisx->focus.pos);
    }
}

void func_80B4E660(Actor* thisx, GlobalContext* globalCtx) {
    EnInvadepoh* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);
    gDPSetEnvColor(POLY_OPA_DISP++, 255, 255, 200, 0);
    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount,
                     func_80B4E5B0, func_80B4E61C, &this->actor);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

s32 func_80B4E6E4(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    if (limbIndex == 9) {
        EnInvadepoh* this = THIS; // both of these needed to match
        rot->x += this->behaviorInfo.unk20.y;
        rot->y += this->behaviorInfo.unk20.z;
        rot->z += this->behaviorInfo.unk20.x;
    } else if (limbIndex == 2) {
        EnInvadepoh* this = THIS; // both of these needed to match
        rot->x += (s16)(this->behaviorInfo.unk34 * this->behaviorInfo.unk20.y);
    }
    return 0;
}

void func_80B4E784(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    if (limbIndex == 9) {
        SysMatrix_GetStateTranslation(&thisx->focus.pos);
    }
}

void func_80B4E7BC(Actor* thisx, GlobalContext* globalCtx) {
    EnInvadepoh* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x09, D_80B4E984[this->behaviorInfo.unk10.unkF]);
    gSPSegment(POLY_OPA_DISP++, 0x08, D_80B4E96C[this->behaviorInfo.unk0.unkF]);
    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount,
                     func_80B4E6E4, func_80B4E784, &this->actor);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
