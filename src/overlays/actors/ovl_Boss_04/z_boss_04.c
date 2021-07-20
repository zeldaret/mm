#include "z_boss_04.h"

#define FLAGS 0x00000035

#define THIS ((Boss04*)thisx)

void Boss04_Init(Actor* thisx, GlobalContext* globalCtx);
void Boss04_Destroy(Actor* thisx, GlobalContext* globalCtx);
void Boss04_Update(Actor* thisx, GlobalContext* globalCtx);
void Boss04_Draw(Actor* thisx, GlobalContext* globalCtx);

/*

// static DamageTable sDamageTable = {
static DamageTable D_809EE150 = {
    /* Deku Nut       */ DMG_ENTRY(1, 0xF),
    /* Deku Stick     */ DMG_ENTRY(1, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(2, 0xF),
    /* Zora boomerang */ DMG_ENTRY(1, 0xF),
    /* Normal arrow   */ DMG_ENTRY(2, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0xF),
    /* Goron punch    */ DMG_ENTRY(2, 0xF),
    /* Sword          */ DMG_ENTRY(2, 0xF),
    /* Goron pound    */ DMG_ENTRY(2, 0xF),
    /* Fire arrow     */ DMG_ENTRY(2, 0x2),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(2, 0xF),
    /* Deku spin      */ DMG_ENTRY(1, 0xF),
    /* Deku bubble    */ DMG_ENTRY(1, 0xF),
    /* Deku launch    */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(1, 0xF),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0xF),
    /* Light ray      */ DMG_ENTRY(0, 0xF),
    /* Thrown object  */ DMG_ENTRY(2, 0xF),
    /* Zora punch     */ DMG_ENTRY(2, 0xF),
    /* Spin attack    */ DMG_ENTRY(2, 0xF),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0xF),
};


const ActorInit Boss_04_InitVars = {
    ACTOR_BOSS_04,
    ACTORCAT_BOSS,
    FLAGS,
    OBJECT_BOSS04,
    sizeof(Boss04),
    (ActorFunc)Boss04_Init,
    (ActorFunc)Boss04_Destroy,
    (ActorFunc)Boss04_Update,
    (ActorFunc)Boss04_Draw,
};


// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_809EE190[1] = {
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x08 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 50 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_809EE1B4 = {
    { COLTYPE_HIT3, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_PLAYER, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    1, D_809EE190, // sJntSphElementsInit,
};


// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_809EE1C4[1] = {
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x08 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 70 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_809EE1E8 = {
    { COLTYPE_METAL, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_PLAYER, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    1, D_809EE1C4, // sJntSphElementsInit,
};

*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_04_0x809EC040/func_809EC040.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_04_0x809EC040/Boss04_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_04_0x809EC040/Boss04_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_04_0x809EC040/func_809EC544.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_04_0x809EC040/func_809EC568.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_04_0x809EC040/func_809ECD00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_04_0x809EC040/func_809ECD18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_04_0x809EC040/func_809ECEF4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_04_0x809EC040/func_809ECF58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_04_0x809EC040/func_809ED224.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_04_0x809EC040/func_809ED2A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_04_0x809EC040/func_809ED45C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_04_0x809EC040/func_809ED50C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_04_0x809EC040/Boss04_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_04_0x809EC040/func_809EDCCC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_04_0x809EC040/func_809EDECC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_04_0x809EC040/Boss04_Draw.asm")
