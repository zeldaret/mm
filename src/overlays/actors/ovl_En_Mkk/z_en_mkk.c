/*
 * File: z_en_mkk.c
 * Overlay: ovl_En_Mkk
 * Description: Black and White Boe (Name origin: Makkurokurosuke)
 */

#include "z_en_mkk.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4)

#define THIS ((EnMkk*)thisx)

void EnMkk_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMkk_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMkk_Update(Actor* thisx, GlobalContext* globalCtx);
void EnMkk_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A4E100(EnMkk* this, GlobalContext* globalCtx);
void func_80A4E1F0(EnMkk* this, GlobalContext* globalCtx);
void func_80A4E2E8(EnMkk* this, GlobalContext* globalCtx);
void func_80A4E60C(EnMkk* this, GlobalContext* globalCtx);
void func_80A4E72C(EnMkk* this, GlobalContext* globalCtx);
void func_80A4EE48(EnMkk* this, GlobalContext* globalCtx);
void func_80A4EF74(EnMkk* this, GlobalContext* globalCtx);

#if 0
const ActorInit En_Mkk_InitVars = {
    ACTOR_EN_MKK,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_MKK,
    sizeof(EnMkk),
    (ActorFunc)EnMkk_Init,
    (ActorFunc)EnMkk_Destroy,
    (ActorFunc)EnMkk_Update,
    (ActorFunc)EnMkk_Draw,
};

// static ColliderSphereInit sSphereInit = {
static ColliderSphereInit D_80A4F720 = {
    { COLTYPE_HIT3, AT_NONE | AT_TYPE_ENEMY, AC_NONE | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_SPHERE, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_HARD, BUMP_ON, OCELEM_ON, },
    { 1, { { 0, 0, 0 }, 15 }, 100 },
};

// sColChkInfoInit
static CollisionCheckInfoInit D_80A4F74C = { 1, 15, 30, 10 };

// static DamageTable sDamageTable = {
static DamageTable D_80A4F754 = {
    /* Deku Nut       */ DMG_ENTRY(1, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0x0),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(1, 0x0),
    /* Fire arrow     */ DMG_ENTRY(2, 0x0),
    /* Ice arrow      */ DMG_ENTRY(2, 0x0),
    /* Light arrow    */ DMG_ENTRY(2, 0x0),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(1, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(2, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(1, 0x0),
    /* Zora barrier   */ DMG_ENTRY(1, 0x0),
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
    /* Powder Keg     */ DMG_ENTRY(1, 0x0),
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80A4F774[] = {
    ICHAIN_F32_DIV1000(gravity, -500, ICHAIN_CONTINUE),
    ICHAIN_F32(terminalVelocity, -5, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 3000, ICHAIN_STOP),
};

#endif

extern ColliderSphereInit D_80A4F720;
extern CollisionCheckInfoInit D_80A4F74C;
extern DamageTable D_80A4F754;
extern InitChainEntry D_80A4F774[];

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/EnMkk_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/EnMkk_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4E0CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4E100.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4E190.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4E1F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4E22C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4E2B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4E2E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4E58C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4E60C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4E67C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4E72C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4E84C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4EBBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/EnMkk_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4EDF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4EE48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4EEF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4EF74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4F16C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/EnMkk_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mkk/func_80A4F4C8.s")
