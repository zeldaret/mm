#include "z_en_bigpo.h"

#define FLAGS 0x00001215

#define THIS ((EnBigpo*)thisx)

void EnBigpo_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBigpo_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBigpo_Update(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Bigpo_InitVars = {
    ACTOR_EN_BIGPO,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_BIGPO,
    sizeof(EnBigpo),
    (ActorFunc)EnBigpo_Init,
    (ActorFunc)EnBigpo_Destroy,
    (ActorFunc)EnBigpo_Update,
    (ActorFunc)NULL,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B65010 = {
    { COLTYPE_HIT3, AT_NONE | AT_TYPE_ENEMY, AC_NONE | AC_TYPE_PLAYER, OC1_NONE | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
    { 35, 100, 10, { 0, 0, 0 } },
};


// sColChkInfoInit
static CollisionCheckInfoInit D_80B6503C = { 10, 35, 100, 50 };


// static DamageTable sDamageTable = {
static DamageTable D_80B65044 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0xF),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(0, 0x0),
    /* Fire arrow     */ DMG_ENTRY(1, 0x0),
    /* Ice arrow      */ DMG_ENTRY(1, 0x0),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(1, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(2, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0x0),
    /* Zora punch     */ DMG_ENTRY(1, 0x0),
    /* Spin attack    */ DMG_ENTRY(1, 0x0),
    /* Sword beam     */ DMG_ENTRY(1, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0x0),
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80B65064[] = {
    ICHAIN_S8(hintId, 90, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 3200, ICHAIN_STOP),
};


extern ColliderCylinderInit D_80B65010;
extern CollisionCheckInfoInit D_80B6503C;
extern DamageTable D_80B65044;
extern InitChainEntry D_80B65064[];
#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/EnBigpo_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/EnBigpo_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B61914.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B619B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B619FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B61AC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B61AF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B61B38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B61B70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B61C04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B61CFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B61D74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B61DA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B61E9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B61F04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B62034.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B62084.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B62154.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B621CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B622E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B623BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B624F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B6259C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B6275C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B627B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B62814.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B62830.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B62900.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B62920.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B629E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B62A68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B62AD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B62B10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B62E38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B62F10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B62FCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B631F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B63264.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B632BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B6330C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B633E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B63410.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B63450.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B63474.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B636D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B636E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B63758.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B6382C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B6383C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B63854.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B63888.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B638AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B638D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B63964.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B63980.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B63A18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B63AC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B63C28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B63D0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B63D88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/EnBigpo_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B64190.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B641E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B64240.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B64470.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B6467C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B64880.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B64B08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigpo/func_80B64DFC.s")
