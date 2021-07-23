#include "z_en_bba_01.h"

#define FLAGS 0x00000019

#define THIS ((EnBba01*)thisx)

void EnBba01_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBba01_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBba01_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBba01_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Bba_01_InitVars = {
    ACTOR_EN_BBA_01,
    ACTORCAT_NPC,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnBba01),
    (ActorFunc)EnBba01_Init,
    (ActorFunc)EnBba01_Destroy,
    (ActorFunc)EnBba01_Update,
    (ActorFunc)EnBba01_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_809CCC80 = {
    { COLTYPE_HIT0, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 18, 64, 0, { 0, 0, 0 } },
};


// sColChkInfoInit
static CollisionCheckInfoInit2 D_809CCCAC = { 0, 0, 0, 0, MASS_IMMOVABLE };


// static DamageTable sDamageTable = {
static DamageTable D_809CCCB8 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(0, 0x0),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(0, 0x0),
    /* Zora boomerang */ DMG_ENTRY(0, 0x0),
    /* Normal arrow   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0x0),
    /* Goron punch    */ DMG_ENTRY(0, 0x0),
    /* Sword          */ DMG_ENTRY(0, 0x0),
    /* Goron pound    */ DMG_ENTRY(0, 0x0),
    /* Fire arrow     */ DMG_ENTRY(0, 0x0),
    /* Ice arrow      */ DMG_ENTRY(0, 0x0),
    /* Light arrow    */ DMG_ENTRY(0, 0x0),
    /* Goron spikes   */ DMG_ENTRY(0, 0x0),
    /* Deku spin      */ DMG_ENTRY(0, 0x0),
    /* Deku bubble    */ DMG_ENTRY(0, 0x0),
    /* Deku launch    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(0, 0x0),
    /* Zora punch     */ DMG_ENTRY(0, 0x0),
    /* Spin attack    */ DMG_ENTRY(0, 0x0),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(0, 0x0),
};


extern ColliderCylinderInit D_809CCC80;
extern CollisionCheckInfoInit2 D_809CCCAC;
extern DamageTable D_809CCCB8;
#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bba_01/func_809CC060.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bba_01/func_809CC1D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bba_01/func_809CC270.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bba_01/func_809CC2F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bba_01/func_809CC370.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bba_01/func_809CC3A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bba_01/func_809CC3CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bba_01/EnBba01_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bba_01/EnBba01_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bba_01/EnBba01_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bba_01/func_809CC6F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bba_01/func_809CC984.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bba_01/func_809CCA5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bba_01/EnBba01_Draw.s")
