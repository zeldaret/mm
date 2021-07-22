#include "z_en_dekunuts.h"

#define FLAGS 0x00000005

#define THIS ((EnDekunuts*)thisx)

void EnDekunuts_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDekunuts_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDekunuts_Update(Actor* thisx, GlobalContext* globalCtx);
void EnDekunuts_Draw(Actor* thisx, GlobalContext* globalCtx);

#if(0)
const ActorInit En_Dekunuts_InitVars = {
    ACTOR_EN_DEKUNUTS,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_DEKUNUTS,
    sizeof(EnDekunuts),
    (ActorFunc)EnDekunuts_Init,
    (ActorFunc)EnDekunuts_Destroy,
    (ActorFunc)EnDekunuts_Update,
    (ActorFunc)EnDekunuts_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_808BEF30 = {
    { COLTYPE_HIT6, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 18, 32, 0, { 0, 0, 0 } },
};


// sColChkInfoInit
static CollisionCheckInfoInit D_808BEF5C = { 1, 18, 32, MASS_IMMOVABLE };


// static DamageTable sDamageTable = {
static DamageTable D_808BEF64 = {
    /* Deku Nut       */ DMG_ENTRY(1, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0x0),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(1, 0x0),
    /* Fire arrow     */ DMG_ENTRY(2, 0x2),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(1, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(2, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(1, 0x0),
    /* Zora barrier   */ DMG_ENTRY(1, 0x5),
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
static InitChainEntry D_808BEF84[] = {
    ICHAIN_S8(hintId, 77, ICHAIN_CONTINUE),
    ICHAIN_F32(gravity, -1, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 2600, ICHAIN_STOP),
};


extern ColliderCylinderInit D_808BEF30;
extern CollisionCheckInfoInit D_808BEF5C;
extern DamageTable D_808BEF64;
extern InitChainEntry D_808BEF84[];
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/EnDekunuts_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/EnDekunuts_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BD348.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BD3B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BD428.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BD49C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BD78C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BD7D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BD870.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BD8D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BDA08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BDA4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BDC9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BDCF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BDD54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BDE7C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BDEF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BDF60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BDFB8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BE1CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BE22C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BE294.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BE358.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BE3A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BE3FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BE484.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BE4D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BE680.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BE6C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BE73C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/EnDekunuts_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BEBD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BED30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/EnDekunuts_Draw.asm")
