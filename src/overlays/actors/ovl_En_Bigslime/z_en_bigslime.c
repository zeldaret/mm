#include "z_en_bigslime.h"

#define FLAGS 0x00000235

#define THIS ((EnBigslime*)thisx)

void EnBigslime_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBigslime_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBigslime_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBigslime_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Bigslime_InitVars = {
    ACTOR_EN_BIGSLIME,
    ACTORCAT_BOSS,
    FLAGS,
    OBJECT_BIGSLIME,
    sizeof(EnBigslime),
    (ActorFunc)EnBigslime_Init,
    (ActorFunc)EnBigslime_Destroy,
    (ActorFunc)EnBigslime_Update,
    (ActorFunc)EnBigslime_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_808F02A0 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_NO_PUSH | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x20000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NONE, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
    { 30, 60, 0, { 0, 0, 0 } },
};


// sColChkInfoInit
static CollisionCheckInfoInit D_808F02CC = { 10, 100, 100, 50 };


// static DamageTable sDamageTable = {
static DamageTable D_808F02D4 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0xE),
    /* Goron punch    */ DMG_ENTRY(1, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(1, 0xF),
    /* Fire arrow     */ DMG_ENTRY(1, 0x2),
    /* Ice arrow      */ DMG_ENTRY(1, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(0, 0xD),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x1),
    /* Zora barrier   */ DMG_ENTRY(0, 0x5),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0xF),
    /* Zora punch     */ DMG_ENTRY(1, 0x0),
    /* Spin attack    */ DMG_ENTRY(1, 0x0),
    /* Sword beam     */ DMG_ENTRY(1, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0xF),
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_808F0338[] = {
    ICHAIN_S8(hintId, 95, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(targetArrowOffset, -13221, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -2000, ICHAIN_CONTINUE),
    ICHAIN_U8(targetMode, 5, ICHAIN_STOP),
};


extern ColliderCylinderInit D_808F02A0;
extern CollisionCheckInfoInit D_808F02CC;
extern DamageTable D_808F02D4;
extern InitChainEntry D_808F0338[];
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/EnBigslime_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/EnBigslime_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E5388.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E5430.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E5484.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E574C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E5988.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E5A00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E5BB0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E5ED4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E601C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E616C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E62B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E64D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E6538.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E6570.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E670C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E6828.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E68AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E69AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E69F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E6A70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E6B08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E6B68.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E6C18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E6C44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E6C70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E6CC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E6D58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E6E80.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E6F08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E6F50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E6FE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E7048.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E7154.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E71FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E732C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E7354.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E75D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E7770.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E7AF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E7B80.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E7D68.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E8064.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E836C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E844C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E84DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E88B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E89CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E8C38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E8CCC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E90A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E91EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E9778.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E97D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E994C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E9AE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E9DA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E9DD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E9F38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808E9FC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808EA14C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808EA1C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808EA264.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808EA2D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808EA538.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808EA5E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808EA748.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808EA7A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808EA80C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808EA860.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808EA8FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808EA9B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808EAA40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808EAA8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808EAAF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808EAB74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808EABCC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808EACEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808EAEBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808EB0A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808EB178.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808EB24C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808EB328.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808EB574.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808EB690.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808EB708.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808EB7F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808EB804.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808EB83C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808EB8B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808EB9E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808EBBE4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808EBED0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808EC158.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808EC354.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/EnBigslime_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808EC708.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808EC990.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808ECD14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808ED07C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/EnBigslime_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigslime_0x808E4FC0/func_808ED3F4.asm")
