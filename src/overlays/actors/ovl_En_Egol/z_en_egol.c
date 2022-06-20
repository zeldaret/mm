/*
 * File: z_en_egol.c
 * Overlay: ovl_En_Egol
 * Description: Eyegore
 */

#include "z_en_egol.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_10 | ACTOR_FLAG_20 | ACTOR_FLAG_80000000)

#define THIS ((EnEgol*)thisx)

void EnEgol_Init(Actor* thisx, GlobalContext* globalCtx);
void EnEgol_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnEgol_Update(Actor* thisx, GlobalContext* globalCtx);
void EnEgol_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
// static ColliderJntSphElementInit sJntSphElementsInit[6] = {
static ColliderJntSphElementInit D_80A80C64[6] = {
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x04, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 6, { { 0, 0, 0 }, 0 }, 1 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x04, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 9, { { 0, 0, 0 }, 0 }, 1 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 3, { { 0, 0, 0 }, 0 }, 1 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { 4, { { 0, 0, 0 }, 0 }, 1 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { 7, { { 0, 0, 0 }, 0 }, 1 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 23, { { 0, 0, 0 }, 0 }, 1 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_80A80D3C = {
    { COLTYPE_METAL, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    6, D_80A80C64, // sJntSphElementsInit,
};

// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_80A80C40[1] = {
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { 14, { { 0, 0, 0 }, 0 }, 1 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_80A80D4C = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    1, D_80A80C40, // sJntSphElementsInit,
};

// static ColliderQuadInit sQuadInit = {
static ColliderQuadInit D_80A80D5C = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_ENEMY, AC_NONE, OC1_NONE, OC2_NONE, COLSHAPE_QUAD, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x07, 0x10 }, { 0x00000000, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL | TOUCH_UNK7, BUMP_NONE, OCELEM_NONE, },
    { { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } },
};

// static DamageTable sDamageTable = {
static DamageTable D_80A80DAC = {
    /* Deku Nut       */ DMG_ENTRY(0, 0xF),
    /* Deku Stick     */ DMG_ENTRY(0, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(2, 0xE),
    /* Zora boomerang */ DMG_ENTRY(1, 0xE),
    /* Normal arrow   */ DMG_ENTRY(1, 0xE),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0xE),
    /* Goron punch    */ DMG_ENTRY(1, 0xE),
    /* Sword          */ DMG_ENTRY(0, 0xF),
    /* Goron pound    */ DMG_ENTRY(0, 0xF),
    /* Fire arrow     */ DMG_ENTRY(2, 0xE),
    /* Ice arrow      */ DMG_ENTRY(2, 0xE),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0xE),
    /* Deku spin      */ DMG_ENTRY(1, 0xE),
    /* Deku bubble    */ DMG_ENTRY(1, 0xE),
    /* Deku launch    */ DMG_ENTRY(2, 0xE),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0xF),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0xF),
    /* Thrown object  */ DMG_ENTRY(1, 0xE),
    /* Zora punch     */ DMG_ENTRY(1, 0xE),
    /* Spin attack    */ DMG_ENTRY(0, 0xF),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0xF),
};

const ActorInit En_Egol_InitVars = {
    ACTOR_EN_EGOL,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_EG,
    sizeof(EnEgol),
    (ActorFunc)EnEgol_Init,
    (ActorFunc)EnEgol_Destroy,
    (ActorFunc)EnEgol_Update,
    (ActorFunc)EnEgol_Draw,
};

#endif

extern ColliderJntSphElementInit D_80A80C64[6];
extern ColliderJntSphInit D_80A80D3C;
extern ColliderJntSphElementInit D_80A80C40[1];
extern ColliderJntSphInit D_80A80D4C;
extern ColliderQuadInit D_80A80D5C;
extern DamageTable D_80A80DAC;

extern UNK_TYPE D_06000040;
extern UNK_TYPE D_060094E4;
extern UNK_TYPE D_0600EE4C;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7C990.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7CA18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7CBC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7CD08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/EnEgol_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/EnEgol_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7D140.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7D168.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7D1E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7D240.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7D27C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7D2C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7D710.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7D780.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7DAAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7DAF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7E2E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7E344.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7E478.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7E4B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7E7EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7E820.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7E924.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7E970.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7E9D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7EA28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7EA88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7EAD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7EB14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7EB54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7EB90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7EBDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7EC84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7ED14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7EFB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/EnEgol_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7F8E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A7FAFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/EnEgol_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A80508.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A80750.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egol/func_80A80904.s")
