#include "z_en_sellnuts.h"

#define FLAGS 0x00000039

#define THIS ((EnSellnuts*)thisx)

void EnSellnuts_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSellnuts_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSellnuts_Update(Actor* thisx, GlobalContext* globalCtx);
void EnSellnuts_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Sellnuts_InitVars = {
    ACTOR_EN_SELLNUTS,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_DNT,
    sizeof(EnSellnuts),
    (ActorFunc)EnSellnuts_Init,
    (ActorFunc)EnSellnuts_Destroy,
    (ActorFunc)EnSellnuts_Update,
    (ActorFunc)EnSellnuts_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80ADD964 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_HIT_PLAYER, COLSHAPE_JNTSPH, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 27, 32, 0, { 0, 0, 0 } },
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80ADDB00[] = {
    ICHAIN_U8(targetMode, 0, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 30, ICHAIN_STOP),
};

#endif

extern ColliderCylinderInit D_80ADD964;
extern InitChainEntry D_80ADDB00[];

extern UNK_TYPE D_06001350;
extern UNK_TYPE D_06005488;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sellnuts/func_80ADADD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sellnuts/func_80ADAE64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sellnuts/func_80ADAFC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sellnuts/func_80ADB040.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sellnuts/func_80ADB08C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sellnuts/func_80ADB0D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sellnuts/func_80ADB254.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sellnuts/func_80ADB4F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sellnuts/func_80ADB544.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sellnuts/func_80ADB924.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sellnuts/func_80ADBAB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sellnuts/func_80ADBBEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sellnuts/func_80ADBC60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sellnuts/func_80ADBCE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sellnuts/func_80ADBD64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sellnuts/func_80ADBE80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sellnuts/func_80ADBFA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sellnuts/func_80ADC034.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sellnuts/func_80ADC118.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sellnuts/func_80ADC2CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sellnuts/func_80ADC37C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sellnuts/func_80ADC580.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sellnuts/func_80ADC5A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sellnuts/func_80ADC6D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sellnuts/func_80ADC7B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sellnuts/func_80ADC8C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sellnuts/func_80ADCA64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sellnuts/func_80ADCC04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sellnuts/func_80ADCD3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sellnuts/func_80ADCE4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sellnuts/func_80ADCFE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sellnuts/EnSellnuts_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sellnuts/EnSellnuts_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sellnuts/EnSellnuts_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sellnuts/func_80ADD4E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sellnuts/func_80ADD7B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sellnuts/func_80ADD7CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sellnuts/EnSellnuts_Draw.s")
