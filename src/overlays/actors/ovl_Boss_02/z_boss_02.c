#include "z_boss_02.h"

#define FLAGS 0x00000035

#define THIS ((Boss02*)thisx)

void Boss02_Init(Actor* thisx, GlobalContext* globalCtx);
void Boss02_Destroy(Actor* thisx, GlobalContext* globalCtx);
void Boss02_Update(Actor* thisx, GlobalContext* globalCtx);
void Boss02_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
// static DamageTable sDamageTable = {
static DamageTable D_809DF550 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(0, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0x0),
    /* Goron punch    */ DMG_ENTRY(2, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(0, 0xF),
    /* Fire arrow     */ DMG_ENTRY(5, 0x2),
    /* Ice arrow      */ DMG_ENTRY(1, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(0, 0x0),
    /* Deku bubble    */ DMG_ENTRY(0, 0x0),
    /* Deku launch    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0xF),
    /* Zora punch     */ DMG_ENTRY(1, 0xF),
    /* Spin attack    */ DMG_ENTRY(1, 0xF),
    /* Sword beam     */ DMG_ENTRY(2, 0xF),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0xF),
};

// static DamageTable sDamageTable = {
static DamageTable D_809DF570 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(0, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0x0),
    /* Goron punch    */ DMG_ENTRY(2, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(0, 0xF),
    /* Fire arrow     */ DMG_ENTRY(1, 0x2),
    /* Ice arrow      */ DMG_ENTRY(5, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(0, 0x0),
    /* Deku bubble    */ DMG_ENTRY(0, 0x0),
    /* Deku launch    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0xF),
    /* Zora punch     */ DMG_ENTRY(1, 0xF),
    /* Spin attack    */ DMG_ENTRY(1, 0xF),
    /* Sword beam     */ DMG_ENTRY(2, 0xF),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0xF),
};

const ActorInit Boss_02_InitVars = {
    ACTOR_BOSS_02,
    ACTORCAT_BOSS,
    FLAGS,
    OBJECT_BOSS02,
    sizeof(Boss02),
    (ActorFunc)Boss02_Init,
    (ActorFunc)Boss02_Destroy,
    (ActorFunc)Boss02_Update,
    (ActorFunc)Boss02_Draw,
};

// static ColliderJntSphElementInit sJntSphElementsInit[22] = {
static ColliderJntSphElementInit D_809DF614[22] = {
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x04, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 85 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x04, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 2, { { 0, 0, 0 }, 85 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x04, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 3, { { 0, 0, 0 }, 85 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x04, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 4, { { 0, 0, 0 }, 85 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x04, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 5, { { 0, 0, 0 }, 85 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x04, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 6, { { 0, 0, 0 }, 85 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x04, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 7, { { 0, 0, 0 }, 85 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x04, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 8, { { 0, 0, 0 }, 85 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x04, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 9, { { 0, 0, 0 }, 85 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x04, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 10, { { 0, 0, 0 }, 85 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x04, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 11, { { 0, 0, 0 }, 85 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x04, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 12, { { 0, 0, 0 }, 85 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x04, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 13, { { 0, 0, 0 }, 85 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x04, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 14, { { 0, 0, 0 }, 85 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x04, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 15, { { 0, 0, 0 }, 85 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x04, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 16, { { 0, 0, 0 }, 85 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x04, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 17, { { 0, 0, 0 }, 85 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x04, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 18, { { 0, 0, 0 }, 85 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x04, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 19, { { 0, 0, 0 }, 85 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x04, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 20, { { 0, 0, 0 }, 85 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x04, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 21, { { 0, 0, 0 }, 85 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x04, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 130 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_809DF92C = {
    { COLTYPE_METAL, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_PLAYER, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    22, D_809DF614, // sJntSphElementsInit,
};

// static ColliderJntSphElementInit sJntSphElementsInit[2] = {
static ColliderJntSphElementInit D_809DF93C[2] = {
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x04, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 130 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x04, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 22, { { 0, 0, 0 }, 110 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_809DF984 = {
    { COLTYPE_HIT0, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_PLAYER, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    2, D_809DF93C, // sJntSphElementsInit,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_809DF994 = {
    { COLTYPE_METAL, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x04, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 150, 200, 0, { 0, 0, 0 } },
};

#endif

extern DamageTable D_809DF550;
extern DamageTable D_809DF570;
extern ColliderJntSphElementInit D_809DF614[22];
extern ColliderJntSphInit D_809DF92C;
extern ColliderJntSphElementInit D_809DF93C[2];
extern ColliderJntSphInit D_809DF984;
extern ColliderCylinderInit D_809DF994;

extern UNK_TYPE D_060002E0;
extern UNK_TYPE D_060003A0;
extern UNK_TYPE D_06008650;
extern UNK_TYPE D_06009C78;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_02/func_809DA1D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_02/func_809DA22C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_02/func_809DA24C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_02/func_809DA264.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_02/func_809DA344.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_02/func_809DA460.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_02/func_809DA50C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_02/Boss02_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_02/Boss02_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_02/func_809DAA74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_02/func_809DAA98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_02/func_809DAAA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_02/func_809DAB78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_02/func_809DBFB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_02/func_809DC218.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_02/Boss02_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_02/func_809DC78C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_02/Boss02_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_02/func_809DD0A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_02/func_809DD0CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_02/func_809DD2F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_02/func_809DD934.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_02/func_809DEAC4.s")
