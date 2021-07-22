#include "z_en_talk_gibud.h"

#define FLAGS 0x00000415

#define THIS ((EnTalkGibud*)thisx)

void EnTalkGibud_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTalkGibud_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTalkGibud_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTalkGibud_Draw(Actor* thisx, GlobalContext* globalCtx);

#if(0)
const ActorInit En_Talk_Gibud_InitVars = {
    ACTOR_EN_TALK_GIBUD,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_RD,
    sizeof(EnTalkGibud),
    (ActorFunc)EnTalkGibud_Init,
    (ActorFunc)EnTalkGibud_Destroy,
    (ActorFunc)EnTalkGibud_Update,
    (ActorFunc)EnTalkGibud_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B01350 = {
    { COLTYPE_HIT0, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0xF7EFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
    { 20, 70, 0, { 0, 0, 0 } },
};


// static DamageTable sDamageTable = {
static DamageTable D_80B0137C = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(2, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(0, 0xD),
    /* Normal arrow   */ DMG_ENTRY(0, 0xD),
    /* UNK_DMG_0x06   */ DMG_ENTRY(2, 0xF),
    /* Hookshot       */ DMG_ENTRY(0, 0xD),
    /* Goron punch    */ DMG_ENTRY(1, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(1, 0xF),
    /* Fire arrow     */ DMG_ENTRY(1, 0x2),
    /* Ice arrow      */ DMG_ENTRY(0, 0xD),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(0, 0x1),
    /* Deku bubble    */ DMG_ENTRY(0, 0xD),
    /* Deku launch    */ DMG_ENTRY(2, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0xC),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0xE),
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


// sColChkInfoInit
static CollisionCheckInfoInit2 D_80B0139C = { 8, 0, 0, 0, MASS_HEAVY };


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80B01448[] = {
    ICHAIN_F32(targetArrowOffset, 2000, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -3500, ICHAIN_STOP),
};


extern ColliderCylinderInit D_80B01350;
extern DamageTable D_80B0137C;
extern CollisionCheckInfoInit2 D_80B0139C;
extern InitChainEntry D_80B01448[];
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Talk_Gibud_0x80AFE8A0/EnTalkGibud_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Talk_Gibud_0x80AFE8A0/EnTalkGibud_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Talk_Gibud_0x80AFE8A0/func_80AFEB38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Talk_Gibud_0x80AFE8A0/func_80AFEB7C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Talk_Gibud_0x80AFE8A0/func_80AFEC08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Talk_Gibud_0x80AFE8A0/func_80AFEC4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Talk_Gibud_0x80AFE8A0/func_80AFED08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Talk_Gibud_0x80AFE8A0/func_80AFED7C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Talk_Gibud_0x80AFE8A0/func_80AFEFD4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Talk_Gibud_0x80AFE8A0/func_80AFF030.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Talk_Gibud_0x80AFE8A0/func_80AFF22C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Talk_Gibud_0x80AFE8A0/func_80AFF288.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Talk_Gibud_0x80AFE8A0/func_80AFF330.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Talk_Gibud_0x80AFE8A0/func_80AFF378.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Talk_Gibud_0x80AFE8A0/func_80AFF45C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Talk_Gibud_0x80AFE8A0/func_80AFF4AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Talk_Gibud_0x80AFE8A0/func_80AFF618.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Talk_Gibud_0x80AFE8A0/func_80AFF6A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Talk_Gibud_0x80AFE8A0/func_80AFF700.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Talk_Gibud_0x80AFE8A0/func_80AFF76C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Talk_Gibud_0x80AFE8A0/func_80AFF880.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Talk_Gibud_0x80AFE8A0/func_80AFF8E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Talk_Gibud_0x80AFE8A0/func_80AFF9CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Talk_Gibud_0x80AFE8A0/func_80AFFA68.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Talk_Gibud_0x80AFE8A0/func_80AFFAB0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Talk_Gibud_0x80AFE8A0/func_80AFFC10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Talk_Gibud_0x80AFE8A0/func_80AFFC9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Talk_Gibud_0x80AFE8A0/func_80AFFD3C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Talk_Gibud_0x80AFE8A0/func_80AFFE3C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Talk_Gibud_0x80AFE8A0/func_80AFFE94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Talk_Gibud_0x80AFE8A0/func_80AFFFA4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Talk_Gibud_0x80AFE8A0/func_80AFFFBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Talk_Gibud_0x80AFE8A0/func_80B000FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Talk_Gibud_0x80AFE8A0/func_80B00158.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Talk_Gibud_0x80AFE8A0/func_80B00384.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Talk_Gibud_0x80AFE8A0/func_80B0040C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Talk_Gibud_0x80AFE8A0/func_80B00484.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Talk_Gibud_0x80AFE8A0/func_80B004D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Talk_Gibud_0x80AFE8A0/func_80B005EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Talk_Gibud_0x80AFE8A0/func_80B00760.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Talk_Gibud_0x80AFE8A0/func_80B008BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Talk_Gibud_0x80AFE8A0/func_80B008FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Talk_Gibud_0x80AFE8A0/func_80B0094C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Talk_Gibud_0x80AFE8A0/func_80B00B8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Talk_Gibud_0x80AFE8A0/func_80B00C94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Talk_Gibud_0x80AFE8A0/func_80B00D9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Talk_Gibud_0x80AFE8A0/EnTalkGibud_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Talk_Gibud_0x80AFE8A0/func_80B00F08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Talk_Gibud_0x80AFE8A0/func_80B00F64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Talk_Gibud_0x80AFE8A0/EnTalkGibud_Draw.asm")
