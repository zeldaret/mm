#include "z_en_neo_reeba.h"

#define FLAGS 0x00000205

#define THIS ((EnNeoReeba*)thisx)

void EnNeoReeba_Init(Actor* thisx, GlobalContext* globalCtx);
void EnNeoReeba_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnNeoReeba_Update(Actor* thisx, GlobalContext* globalCtx);
void EnNeoReeba_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Neo_Reeba_InitVars = {
    ACTOR_EN_NEO_REEBA,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_RB,
    sizeof(EnNeoReeba),
    (ActorFunc)EnNeoReeba_Init,
    (ActorFunc)EnNeoReeba_Destroy,
    (ActorFunc)EnNeoReeba_Update,
    (ActorFunc)EnNeoReeba_Draw,
};


// static DamageTable sDamageTable = {
static DamageTable D_80B7E500 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0xE),
    /* Horse trample  */ DMG_ENTRY(1, 0xF),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(1, 0xE),
    /* Normal arrow   */ DMG_ENTRY(1, 0xE),
    /* UNK_DMG_0x06   */ DMG_ENTRY(1, 0xF),
    /* Hookshot       */ DMG_ENTRY(0, 0xC),
    /* Goron punch    */ DMG_ENTRY(1, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(1, 0xF),
    /* Fire arrow     */ DMG_ENTRY(2, 0x2),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(0, 0x1),
    /* Deku bubble    */ DMG_ENTRY(1, 0xE),
    /* Deku launch    */ DMG_ENTRY(2, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0xD),
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


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B7E520 = {
    { COLTYPE_HIT5, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x08, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
    { 18, 30, 0, { 0, 0, 0 } },
};


extern DamageTable D_80B7E500;
extern ColliderCylinderInit D_80B7E520;
#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/EnNeoReeba_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/EnNeoReeba_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7CA34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7CA70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7CB3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7CB88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7CCE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7CD28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7CE34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7CE94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7CFA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7CFFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7D130.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7D150.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7D254.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7D2E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7D360.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7D398.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7D3EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7D47C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7D4FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7D5A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7D6D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7D788.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7D9B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7DC80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7DD7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7DF34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7E0BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7E260.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/EnNeoReeba_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7E378.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/EnNeoReeba_Draw.s")
