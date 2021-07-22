#include "z_en_bat.h"

#define FLAGS 0x00005005

#define THIS ((EnBat*)thisx)

void EnBat_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBat_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBat_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBat_Draw(Actor* thisx, GlobalContext* globalCtx);

#if(0)
const ActorInit En_Bat_InitVars = {
    ACTOR_EN_BAT,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_BAT,
    sizeof(EnBat),
    (ActorFunc)EnBat_Init,
    (ActorFunc)EnBat_Destroy,
    (ActorFunc)EnBat_Update,
    (ActorFunc)EnBat_Draw,
};


// static ColliderSphereInit sSphereInit = {
static ColliderSphereInit D_80A44A00 = {
    { COLTYPE_HIT3, AT_NONE | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_SPHERE, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_HARD, BUMP_ON, OCELEM_ON, },
    { 1, { { 0, 0, 0 }, 15 }, 100 },
};


// static DamageTable sDamageTable = {
static DamageTable D_80A44A2C = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
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
static CollisionCheckInfoInit D_80A44A4C = { 1, 15, 30, 10 };


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80A44A54[] = {
    ICHAIN_S8(hintId, 96, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 3000, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -500, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 2000, ICHAIN_STOP),
};


extern ColliderSphereInit D_80A44A00;
extern DamageTable D_80A44A2C;
extern CollisionCheckInfoInit D_80A44A4C;
extern InitChainEntry D_80A44A54[];
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bat_0x80A434E0/EnBat_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bat_0x80A434E0/EnBat_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bat_0x80A434E0/func_80A437CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bat_0x80A434E0/func_80A43810.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bat_0x80A434E0/func_80A43870.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bat_0x80A434E0/func_80A438D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bat_0x80A434E0/func_80A438F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bat_0x80A434E0/func_80A4392C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bat_0x80A434E0/func_80A43CA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bat_0x80A434E0/func_80A43CE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bat_0x80A434E0/func_80A43F60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bat_0x80A434E0/func_80A44114.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bat_0x80A434E0/func_80A44294.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bat_0x80A434E0/func_80A4431C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bat_0x80A434E0/func_80A443D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bat_0x80A434E0/EnBat_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bat_0x80A434E0/EnBat_Draw.asm")
