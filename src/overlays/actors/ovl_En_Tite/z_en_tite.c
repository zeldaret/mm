#include "z_en_tite.h"

#define FLAGS 0x00000205

#define THIS ((EnTite*)thisx)

void EnTite_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTite_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTite_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTite_Draw(Actor* thisx, GlobalContext* globalCtx);

#if(0)
const ActorInit En_Tite_InitVars = {
    ACTOR_EN_TITE,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_TITE,
    sizeof(EnTite),
    (ActorFunc)EnTite_Init,
    (ActorFunc)EnTite_Destroy,
    (ActorFunc)EnTite_Update,
    (ActorFunc)EnTite_Draw,
};


// static ColliderSphereInit sSphereInit = {
static ColliderSphereInit D_80896AD0 = {
    { COLTYPE_HIT6, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_SPHERE, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x08 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_HARD, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
    { 0, { { 0, 1500, 0 }, 20 }, 100 },
};


// static DamageTable sDamageTable = {
static DamageTable D_80896AFC = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0xF),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(0, 0x0),
    /* Fire arrow     */ DMG_ENTRY(2, 0x2),
    /* Ice arrow      */ DMG_ENTRY(1, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(0, 0x1),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(2, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x1),
    /* Zora barrier   */ DMG_ENTRY(0, 0x5),
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


// sColChkInfoInit
static CollisionCheckInfoInit D_80896B1C = { 2, 40, 40, MASS_HEAVY };


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80896B50[] = {
    ICHAIN_S8(hintId, 70, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 2000, ICHAIN_CONTINUE),
    ICHAIN_F32(minVelocityY, -40, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -1000, ICHAIN_STOP),
};


extern ColliderSphereInit D_80896AD0;
extern DamageTable D_80896AFC;
extern CollisionCheckInfoInit D_80896B1C;
extern InitChainEntry D_80896B50[];
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/EnTite_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/EnTite_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80893A18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80893A34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80893A9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80893ADC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80893B10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80893B70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80893BCC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80893DD4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80893E54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80893ED4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80893F30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80893FD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80894024.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_8089408C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_808942B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80894414.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80894454.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_8089452C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_808945B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_808945EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80894638.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_8089484C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80894910.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80894B2C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80894BC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80894DD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80894E0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80895020.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_808951B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_808952EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80895424.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_808955E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80895640.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_808956B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_808956FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80895738.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_8089595C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80895A10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80895AC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80895CB0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80895D08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80895DE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80895E28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80895FF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_808963B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/EnTite_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80896750.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/func_80896788.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tite_0x808937F0/EnTite_Draw.asm")
