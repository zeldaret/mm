#include "z_boss_06.h"

#define FLAGS 0x00000035

#define THIS ((Boss06*)thisx)

void Boss06_Init(Actor* thisx, GlobalContext* globalCtx);
void Boss06_Destroy(Actor* thisx, GlobalContext* globalCtx);
void Boss06_Update(Actor* thisx, GlobalContext* globalCtx);
void Boss06_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
// static DamageTable sDamageTable = {
static DamageTable D_809F4080 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0xF),
    /* Deku Stick     */ DMG_ENTRY(0, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(0, 0xF),
    /* Normal arrow   */ DMG_ENTRY(0, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0xF),
    /* Goron punch    */ DMG_ENTRY(0, 0xF),
    /* Sword          */ DMG_ENTRY(0, 0xF),
    /* Goron pound    */ DMG_ENTRY(0, 0xF),
    /* Fire arrow     */ DMG_ENTRY(1, 0x2),
    /* Ice arrow      */ DMG_ENTRY(0, 0x3),
    /* Light arrow    */ DMG_ENTRY(0, 0x4),
    /* Goron spikes   */ DMG_ENTRY(0, 0xF),
    /* Deku spin      */ DMG_ENTRY(0, 0xF),
    /* Deku bubble    */ DMG_ENTRY(0, 0xF),
    /* Deku launch    */ DMG_ENTRY(0, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0xF),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0xF),
    /* Light ray      */ DMG_ENTRY(0, 0xF),
    /* Thrown object  */ DMG_ENTRY(0, 0xF),
    /* Zora punch     */ DMG_ENTRY(0, 0xF),
    /* Spin attack    */ DMG_ENTRY(0, 0xF),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0xF),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(0, 0xF),
};


const ActorInit Boss_06_InitVars = {
    ACTOR_BOSS_06,
    ACTORCAT_BOSS,
    FLAGS,
    OBJECT_KNIGHT,
    sizeof(Boss06),
    (ActorFunc)Boss06_Init,
    (ActorFunc)Boss06_Destroy,
    (ActorFunc)Boss06_Update,
    (ActorFunc)Boss06_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_809F40C0 = {
    { COLTYPE_HIT3, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7FFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
    { 90, 140, 10, { 0, 0, 0 } },
};


extern DamageTable D_809F4080;
extern ColliderCylinderInit D_809F40C0;
#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_06/func_809F2120.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_06/func_809F2140.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_06/Boss06_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_06/Boss06_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_06/func_809F23CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_06/func_809F24A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_06/func_809F24C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_06/func_809F2B64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_06/func_809F2C44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_06/func_809F2E14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_06/func_809F2E34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_06/func_809F2ED0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_06/func_809F2EE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_06/Boss06_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_06/Boss06_Draw.s")
