#include "z_en_sellnuts.h"

#define FLAGS 0x00000039

#define THIS ((EnSellnuts*)thisx)

void EnSellnuts_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSellnuts_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSellnuts_Update(Actor* thisx, GlobalContext* globalCtx);
void EnSellnuts_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
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
*/

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
