#include "z_en_bigpamet.h"

#define FLAGS 0x00000435

#define THIS ((EnBigpamet*)thisx)

void EnBigpamet_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBigpamet_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBigpamet_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBigpamet_Draw(Actor* thisx, GlobalContext* globalCtx);

#if(0)
const ActorInit En_Bigpamet_InitVars = {
    ACTOR_EN_BIGPAMET,
    ACTORCAT_BOSS,
    FLAGS,
    OBJECT_TL,
    sizeof(EnBigpamet),
    (ActorFunc)EnBigpamet_Init,
    (ActorFunc)EnBigpamet_Destroy,
    (ActorFunc)EnBigpamet_Update,
    (ActorFunc)EnBigpamet_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80A29700 = {
    { COLTYPE_HARD, AT_NONE | AT_TYPE_ENEMY, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x04, 0x04 }, { 0xF7CF7FFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
    { 53, 50, 0, { 0, 0, 0 } },
};


// sColChkInfoInit
static CollisionCheckInfoInit D_80A2972C = { 1, 53, 60, 250 };


// static DamageTable sDamageTable = {
static DamageTable D_80A29734 = {
    /* Deku Nut       */ DMG_ENTRY(1, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0x0),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(1, 0xF),
    /* Fire arrow     */ DMG_ENTRY(1, 0x0),
    /* Ice arrow      */ DMG_ENTRY(1, 0x0),
    /* Light arrow    */ DMG_ENTRY(1, 0x0),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(1, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(1, 0x0),
    /* Zora barrier   */ DMG_ENTRY(1, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0x0),
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
static InitChainEntry D_80A29764[] = {
    ICHAIN_S8(hintId, 1, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 15, ICHAIN_CONTINUE),
    ICHAIN_F32(gravity, -2, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 4333, ICHAIN_CONTINUE),
    ICHAIN_U8(targetMode, 5, ICHAIN_STOP),
};


extern ColliderCylinderInit D_80A29700;
extern CollisionCheckInfoInit D_80A2972C;
extern DamageTable D_80A29734;
extern InitChainEntry D_80A29764[];
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/EnBigpamet_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/EnBigpamet_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A2768C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A276F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A2778C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A27970.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A27B58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A27DD8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A27FE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A2811C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A281B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A281DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A28274.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A282C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A28378.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A283A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A283F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A2844C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A284E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A2855C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A28618.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A2866C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A286C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A28708.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A28760.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A287E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A28970.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A289C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A28A28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A28A98.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A28B98.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A28D0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A28D80.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A28DC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A28E40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A28E98.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A28ED4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A28EE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A29028.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A29094.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/EnBigpamet_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A292A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A293E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A29494.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/EnBigpamet_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A29580.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A29628.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigpamet_0x80A27520/func_80A2966C.asm")
