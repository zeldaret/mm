/*
 * File: z_en_wiz.c
 * Overlay: ovl_En_Wiz
 * Description: Wizzrobe
 */

#include "z_en_wiz.h"

#define FLAGS                                                                                            \
    (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_10 | ACTOR_FLAG_20 | ACTOR_FLAG_1000 | ACTOR_FLAG_100000 | \
     ACTOR_FLAG_8000000 | ACTOR_FLAG_80000000)

#define THIS ((EnWiz*)thisx)

void EnWiz_Init(Actor* thisx, GlobalContext* globalCtx);
void EnWiz_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnWiz_Update(Actor* thisx, GlobalContext* globalCtx);
void EnWiz_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Wiz_InitVars = {
    ACTOR_EN_WIZ,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_WIZ,
    sizeof(EnWiz),
    (ActorFunc)EnWiz_Init,
    (ActorFunc)EnWiz_Destroy,
    (ActorFunc)EnWiz_Update,
    (ActorFunc)EnWiz_Draw,
};

// static ColliderJntSphElementInit sJntSphElementsInit[10] = {
static ColliderJntSphElementInit D_80A48B50[10] = {
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x00 }, { 0x01000202, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_NONE, },
        { 1, { { 0, 0, 0 }, 0 }, 1 },
    },
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { 1, { { 0, 0, 0 }, 0 }, 0 },
    },
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { 1, { { 0, 0, 0 }, 0 }, 0 },
    },
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { 1, { { 0, 0, 0 }, 0 }, 0 },
    },
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { 1, { { 0, 0, 0 }, 0 }, 0 },
    },
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { 1, { { 0, 0, 0 }, 0 }, 0 },
    },
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { 1, { { 0, 0, 0 }, 0 }, 0 },
    },
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { 1, { { 0, 0, 0 }, 0 }, 0 },
    },
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { 1, { { 0, 0, 0 }, 0 }, 0 },
    },
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { 1, { { 0, 0, 0 }, 0 }, 0 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_80A48CB8 = {
    { COLTYPE_HIT2, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    10, D_80A48B50, // sJntSphElementsInit,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80A48CC8 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0xF7CFFFFF, 0x08, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 35, 130, 0, { 0, 0, 0 } },
};

// static DamageTable sDamageTable = {
static DamageTable D_80A48CF4 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(1, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(1, 0xF),
    /* Normal arrow   */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0xF),
    /* Goron punch    */ DMG_ENTRY(1, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(3, 0xF),
    /* Fire arrow     */ DMG_ENTRY(1, 0x2),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(0, 0x0),
    /* Deku spin      */ DMG_ENTRY(1, 0xF),
    /* Deku bubble    */ DMG_ENTRY(1, 0xF),
    /* Deku launch    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x1),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0xF),
    /* Zora punch     */ DMG_ENTRY(1, 0xF),
    /* Spin attack    */ DMG_ENTRY(1, 0xF),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0xF),
};

// static DamageTable sDamageTable = {
static DamageTable D_80A48D14 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(1, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(1, 0xF),
    /* Normal arrow   */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0xF),
    /* Goron punch    */ DMG_ENTRY(2, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(3, 0xF),
    /* Fire arrow     */ DMG_ENTRY(2, 0x2),
    /* Ice arrow      */ DMG_ENTRY(1, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(0, 0x0),
    /* Deku spin      */ DMG_ENTRY(1, 0xF),
    /* Deku bubble    */ DMG_ENTRY(1, 0xF),
    /* Deku launch    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x1),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0xF),
    /* Zora punch     */ DMG_ENTRY(1, 0xF),
    /* Spin attack    */ DMG_ENTRY(1, 0xF),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0xF),
};

#endif

extern ColliderJntSphElementInit D_80A48B50[10];
extern ColliderJntSphInit D_80A48CB8;
extern ColliderCylinderInit D_80A48CC8;
extern DamageTable D_80A48CF4;
extern DamageTable D_80A48D14;

extern UNK_TYPE D_0600211C;
extern UNK_TYPE D_060025F0;
extern UNK_TYPE D_060066C0;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/EnWiz_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/EnWiz_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A455C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A456A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A45CD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A460A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A46280.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A462F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A46414.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A4668C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A46764.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A468CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A46990.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A46C88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A46CC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A46DDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A46E24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A47000.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A470D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A47298.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A473B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A4767C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A476C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A477E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/EnWiz_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A47FCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/func_80A48138.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz/EnWiz_Draw.s")
