#include "z_en_bal.h"

#define FLAGS 0x00000019

#define THIS ((EnBal*)thisx)

void EnBal_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBal_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBal_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBal_Draw(Actor* thisx, GlobalContext* globalCtx);

#if(0)
const ActorInit En_Bal_InitVars = {
    ACTOR_EN_BAL,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_BAL,
    sizeof(EnBal),
    (ActorFunc)EnBal_Init,
    (ActorFunc)EnBal_Destroy,
    (ActorFunc)EnBal_Update,
    (ActorFunc)EnBal_Draw,
};


// static DamageTable sDamageTable = {
static DamageTable D_80A63CE0 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(0, 0x0),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(0, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0xE),
    /* Normal arrow   */ DMG_ENTRY(1, 0xE),
    /* UNK_DMG_0x06   */ DMG_ENTRY(1, 0xF),
    /* Hookshot       */ DMG_ENTRY(1, 0xF),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(1, 0x0),
    /* Fire arrow     */ DMG_ENTRY(2, 0x2),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(0, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0xE),
    /* Deku launch    */ DMG_ENTRY(2, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
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
    /* Powder Keg     */ DMG_ENTRY(0, 0x0),
};


// sColChkInfoInit
static CollisionCheckInfoInit2 D_80A63D00 = { 1, 0, 0, 0, MASS_IMMOVABLE };


// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_80A63D0C[1] = {
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 6, { { 2400, 0, 0 }, 50 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_80A63D30 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    1, D_80A63D0C, // sJntSphElementsInit,
};


extern DamageTable D_80A63CE0;
extern CollisionCheckInfoInit2 D_80A63D00;
extern ColliderJntSphElementInit D_80A63D0C[1];
extern ColliderJntSphInit D_80A63D30;
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/EnBal_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/EnBal_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A61A18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A61A44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A61A6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A61ADC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A61B5C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A61C9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A61CE4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A61DF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A61E5C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A62128.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A621C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A62260.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A622A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A623CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A624DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A62818.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A62830.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A629C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A62AC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A62B30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A62B78.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A62CF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A62DCC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A62ED0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A62FAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A63158.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A634B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A634C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A635DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A635F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A636AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A637FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A63884.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/EnBal_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A63A10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/func_80A63B94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bal_0x80A61810/EnBal_Draw.asm")
