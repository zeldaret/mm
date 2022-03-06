/*
 * File: z_en_bee.c
 * Overlay: ovl_En_Bee
 * Description: Giant Bee
 */

#include "z_en_bee.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4)

#define THIS ((EnBee*)thisx)

void EnBee_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBee_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBee_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBee_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80B5A9E8(EnBee* this, GlobalContext* globalCtx);
void func_80B5AC3C(EnBee* this, GlobalContext* globalCtx);

#if 0
const ActorInit En_Bee_InitVars = {
    ACTOR_EN_BEE,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_BEE,
    sizeof(EnBee),
    (ActorFunc)EnBee_Init,
    (ActorFunc)EnBee_Destroy,
    (ActorFunc)EnBee_Update,
    (ActorFunc)EnBee_Draw,
};

// static DamageTable sDamageTable = {
static DamageTable D_80B5B214 = {
    /* Deku Nut       */ DMG_ENTRY(1, 0xF),
    /* Deku Stick     */ DMG_ENTRY(1, 0xF),
    /* Horse trample  */ DMG_ENTRY(1, 0xF),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(1, 0xF),
    /* Normal arrow   */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0xF),
    /* Goron punch    */ DMG_ENTRY(1, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(1, 0xF),
    /* Fire arrow     */ DMG_ENTRY(2, 0xF),
    /* Ice arrow      */ DMG_ENTRY(2, 0xF),
    /* Light arrow    */ DMG_ENTRY(2, 0xF),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(1, 0xF),
    /* Deku bubble    */ DMG_ENTRY(1, 0xF),
    /* Deku launch    */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(1, 0xF),
    /* Zora barrier   */ DMG_ENTRY(1, 0xF),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0xF),
    /* Zora punch     */ DMG_ENTRY(1, 0xF),
    /* Spin attack    */ DMG_ENTRY(1, 0xF),
    /* Sword beam     */ DMG_ENTRY(1, 0xF),
    /* Normal Roll    */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0xF),
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B5B234 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x08, 0x02 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 6, 13, -4, { 0, 0, 0 } },
};

#endif

extern DamageTable D_80B5B214;
extern ColliderCylinderInit D_80B5B234;

extern UNK_TYPE D_0600005C;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bee/EnBee_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bee/EnBee_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bee/func_80B5A854.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bee/func_80B5A9E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bee/func_80B5ABC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bee/func_80B5AC3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bee/func_80B5AF80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bee/EnBee_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bee/EnBee_Draw.s")
