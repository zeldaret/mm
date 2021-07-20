#include "z_en_cne_01.h"

#define FLAGS 0x00000019

#define THIS ((EnCne01*)thisx)

void EnCne01_Init(Actor* thisx, GlobalContext* globalCtx);
void EnCne01_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnCne01_Update(Actor* thisx, GlobalContext* globalCtx);
void EnCne01_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0

const ActorInit En_Cne_01_InitVars = {
    ACTOR_EN_CNE_01,
    ACTORCAT_NPC,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnCne01),
    (ActorFunc)EnCne01_Init,
    (ActorFunc)EnCne01_Destroy,
    (ActorFunc)EnCne01_Update,
    (ActorFunc)EnCne01_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_809CBF00 = {
    { COLTYPE_HIT0, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 18, 64, 0, { 0, 0, 0 } },
};


// sColChkInfoInit
static CollisionCheckInfoInit2 D_809CBF2C = { 0, 0, 0, 0, MASS_IMMOVABLE };


// static DamageTable sDamageTable = {
static DamageTable D_809CBF38 = {
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

#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Cne_01_0x809CB290/func_809CB290.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Cne_01_0x809CB290/func_809CB404.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Cne_01_0x809CB290/func_809CB4A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Cne_01_0x809CB290/func_809CB520.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Cne_01_0x809CB290/func_809CB5A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Cne_01_0x809CB290/func_809CB5D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Cne_01_0x809CB290/func_809CB5FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Cne_01_0x809CB290/EnCne01_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Cne_01_0x809CB290/EnCne01_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Cne_01_0x809CB290/EnCne01_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Cne_01_0x809CB290/func_809CB920.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Cne_01_0x809CB290/func_809CBBC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Cne_01_0x809CB290/func_809CBCA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Cne_01_0x809CB290/EnCne01_Draw.asm")
