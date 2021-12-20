/*
 * File: z_en_am.c
 * Overlay: ovl_En_Am
 * Description: Armos
 */

#include "z_en_am.h"

#define FLAGS 0x00000405

#define THIS ((EnAm*)thisx)

void EnAm_Init(Actor* thisx, GlobalContext* globalCtx);
void EnAm_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnAm_Update(Actor* thisx, GlobalContext* globalCtx);
void EnAm_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_808B0040(EnAm* this, GlobalContext* globalCtx);
void func_808B0124(EnAm* this, GlobalContext* globalCtx);
void func_808B03C0(EnAm* this, GlobalContext* globalCtx);
void func_808B04A8(EnAm* this, GlobalContext* globalCtx);
void func_808B0508(EnAm* this, GlobalContext* globalCtx);
void func_808B05C8(EnAm* this, GlobalContext* globalCtx);
void func_808B066C(EnAm* this, GlobalContext* globalCtx);
void func_808B07A8(EnAm* this, GlobalContext* globalCtx);
void func_808B0894(EnAm* this, GlobalContext* globalCtx);
void func_808B0B4C(EnAm* this, GlobalContext* globalCtx);

#if 0
const ActorInit En_Am_InitVars = {
    ACTOR_EN_AM,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_AM,
    sizeof(EnAm),
    (ActorFunc)EnAm_Init,
    (ActorFunc)EnAm_Destroy,
    (ActorFunc)EnAm_Update,
    (ActorFunc)EnAm_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_808B1070 = {
    { COLTYPE_HIT5, AT_NONE | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x08 }, { 0x81C2C788, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
    { 23, 98, 0, { 0, 0, 0 } },
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_808B109C = {
    { COLTYPE_METAL, AT_NONE, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_NONE, OC2_NONE, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x760D3877, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
    { 23, 98, 0, { 0, 0, 0 } },
};

// static DamageTable sDamageTable = {
static DamageTable D_808B10C8 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0xF),
    /* Deku Stick     */ DMG_ENTRY(0, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0xF),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(0, 0xF),
    /* Normal arrow   */ DMG_ENTRY(0, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0xD),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(1, 0x0),
    /* Fire arrow     */ DMG_ENTRY(0, 0xF),
    /* Ice arrow      */ DMG_ENTRY(0, 0xF),
    /* Light arrow    */ DMG_ENTRY(0, 0xF),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(1, 0x0),
    /* Deku bubble    */ DMG_ENTRY(0, 0xF),
    /* Deku launch    */ DMG_ENTRY(2, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0xF),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0x0),
    /* Zora punch     */ DMG_ENTRY(1, 0x0),
    /* Spin attack    */ DMG_ENTRY(1, 0x0),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0xF),
};

// sColChkInfoInit
static CollisionCheckInfoInit D_808B10E8 = { 1, 23, 98, MASS_HEAVY };

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_808B10F0[] = {
    ICHAIN_VEC3F_DIV1000(scale, 14, ICHAIN_CONTINUE),
    ICHAIN_S8(hintId, 19, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -4000, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 2000, ICHAIN_STOP),
};

#endif

extern ColliderCylinderInit D_808B1070;
extern ColliderCylinderInit D_808B109C;
extern DamageTable D_808B10C8;
extern CollisionCheckInfoInit D_808B10E8;
extern InitChainEntry D_808B10F0[];

extern UNK_TYPE D_06000238;
extern UNK_TYPE D_0600033C;
extern UNK_TYPE D_06005B3C;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/EnAm_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/EnAm_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/func_808AFE38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/func_808AFF9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/func_808B0040.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/func_808B00D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/func_808B0124.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/func_808B0208.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/func_808B0358.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/func_808B03C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/func_808B0460.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/func_808B04A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/func_808B04E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/func_808B0508.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/func_808B057C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/func_808B05C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/func_808B0640.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/func_808B066C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/func_808B06D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/func_808B07A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/func_808B0820.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/func_808B0894.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/func_808B0AD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/func_808B0B4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/func_808B0B9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/EnAm_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/func_808B0EA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/EnAm_Draw.s")
