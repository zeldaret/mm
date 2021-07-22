#include "z_boss_hakugin.h"

#define FLAGS 0x00000035

#define THIS ((BossHakugin*)thisx)

void BossHakugin_Init(Actor* thisx, GlobalContext* globalCtx);
void BossHakugin_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BossHakugin_Update(Actor* thisx, GlobalContext* globalCtx);
void BossHakugin_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Boss_Hakugin_InitVars = {
    ACTOR_BOSS_HAKUGIN,
    ACTORCAT_BOSS,
    FLAGS,
    OBJECT_BOSS_HAKUGIN,
    sizeof(BossHakugin),
    (ActorFunc)BossHakugin_Init,
    (ActorFunc)BossHakugin_Destroy,
    (ActorFunc)BossHakugin_Update,
    (ActorFunc)BossHakugin_Draw,
};


// static ColliderJntSphElementInit sJntSphElementsInit[19] = {
static ColliderJntSphElementInit D_80B0E700[19] = {
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NONE, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 16, { { 1300, 200, 0 }, 30 }, 270 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 15, { { 1400, 300, 0 }, 35 }, 270 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 2, { { 1600, -400, 0 }, 26 }, 270 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 6, { { 1700, 200, 400 }, 18 }, 270 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 8, { { 1000, 0, 0 }, 10 }, 270 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 9, { { 500, 0, 0 }, 9 }, 270 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 11, { { 1700, 200, -400 }, 18 }, 270 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 13, { { 1000, 0, 0 }, 10 }, 270 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 14, { { 500, 0, 0 }, 9 }, 270 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 21, { { 800, 0, 400 }, 15 }, 270 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 22, { { 500, 200, 0 }, 9 }, 270 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 24, { { 300, 0, 0 }, 8 }, 270 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 25, { { 500, 100, 0 }, 9 }, 270 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 28, { { 800, 0, -400 }, 15 }, 270 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 29, { { 500, 200, 0 }, 9 }, 270 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 31, { { 300, 0, 0 }, 8 }, 270 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 32, { { 500, 100, 0 }, 9 }, 270 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 16, { { 2400, -400, -2900 }, 12 }, 270 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_NO_HITMARK, OCELEM_ON, },
        { 16, { { 2400, -400, 2900 }, 12 }, 270 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_80B0E9AC = {
    { COLTYPE_METAL, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    19, D_80B0E700, // sJntSphElementsInit,
};


// static ColliderTrisElementInit sTrisElementsInit[1] = {
static ColliderTrisElementInit D_80B0E9BC[1] = {
    {
        { ELEMTYPE_UNK5, { 0x20000000, 0x03, 0x08 }, { 0x00000000, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NONE, BUMP_NONE, OCELEM_NONE, },
        { { { 22.0f, 0.0f, 100.0f }, { 0.0f, 0.0f, -100.0f }, { -22.0f, 0.0f, 100.0f } } },
    },
};

// static ColliderTrisInit sTrisInit = {
static ColliderTrisInit D_80B0E9F8 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_ENEMY, AC_NONE, OC1_NONE, OC2_TYPE_1, COLSHAPE_TRIS, },
    1, D_80B0E9BC, // sTrisElementsInit,
};


// static ColliderSphereInit sSphereInit = {
static ColliderSphereInit D_80B0EA08 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_ENEMY, AC_NONE, OC1_NONE, OC2_TYPE_2, COLSHAPE_SPHERE, },
    { ELEMTYPE_UNK5, { 0x20000000, 0x00, 0x08 }, { 0x00000000, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_HARD, BUMP_NONE, OCELEM_NONE, },
    { 1, { { 0, 0, 0 }, 23 }, 100 },
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B0EA34 = {
    { COLTYPE_HARD, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x02, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NONE, BUMP_ON, OCELEM_ON, },
    { 170, 40, 0, { 0, 0, 0 } },
};


// static DamageTable sDamageTable = {
static DamageTable D_80B0EA60 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xC),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0xE),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0x0),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(1, 0x0),
    /* Fire arrow     */ DMG_ENTRY(1, 0x2),
    /* Ice arrow      */ DMG_ENTRY(1, 0x3),
    /* Light arrow    */ DMG_ENTRY(1, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(1, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0x0),
    /* Zora punch     */ DMG_ENTRY(1, 0x0),
    /* Spin attack    */ DMG_ENTRY(1, 0x0),
    /* Sword beam     */ DMG_ENTRY(1, 0xD),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0xC),
};


// sColChkInfoInit
static CollisionCheckInfoInit D_80B0EA80 = { 30, 80, 100, MASS_IMMOVABLE };


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80B0EAD8[] = {
    ICHAIN_S8(hintId, 27, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 27, ICHAIN_CONTINUE),
    ICHAIN_U8(targetMode, 5, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -2000, ICHAIN_STOP),
};


extern ColliderJntSphElementInit D_80B0E700[19];
extern ColliderJntSphInit D_80B0E9AC;
extern ColliderTrisElementInit D_80B0E9BC[1];
extern ColliderTrisInit D_80B0E9F8;
extern ColliderSphereInit D_80B0EA08;
extern ColliderCylinderInit D_80B0EA34;
extern DamageTable D_80B0EA60;
extern CollisionCheckInfoInit D_80B0EA80;
extern InitChainEntry D_80B0EAD8[];
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/BossHakugin_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/BossHakugin_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0573C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B057A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B058C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B05A64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B05B04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B05CBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B05D4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B05EE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0607C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B06558.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B06600.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0696C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B06B20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B06C08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B06D38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B06F48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0728C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B07450.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B07700.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0791C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B07B88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B07BFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B07DA4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B07EEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B08018.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B08124.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0813C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0825C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B082AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B08550.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0863C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B08848.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B08960.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B08C1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B08CB8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B09178.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B091D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B093C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B094E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B09840.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B098BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B09A94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B09C78.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B09DFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B09E20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B09E84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B09EDC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B09F7C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0A2A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0A5EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0A638.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0A87C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0A8C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0AC30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0ADFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0B238.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0B34C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0B3F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0B548.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0B660.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/BossHakugin_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0C000.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0C1BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0C398.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0C570.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0C7B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0CAF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0CCD8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0CF24.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/BossHakugin_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0D2B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0D69C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0D750.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0D9CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0DFA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0E548.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_Hakugin_0x80B05290/func_80B0E5A4.asm")
