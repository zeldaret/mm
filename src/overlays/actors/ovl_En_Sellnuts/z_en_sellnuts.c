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
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_DNT,
    sizeof(EnSellnuts),
    (ActorFunc)EnSellnuts_Init,
    (ActorFunc)EnSellnuts_Destroy,
    (ActorFunc)EnSellnuts_Update,
    (ActorFunc)EnSellnuts_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Sellnuts_0x80ADADD0/func_80ADADD0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sellnuts_0x80ADADD0/func_80ADAE64.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sellnuts_0x80ADADD0/func_80ADAFC0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sellnuts_0x80ADADD0/func_80ADB040.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sellnuts_0x80ADADD0/func_80ADB08C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sellnuts_0x80ADADD0/func_80ADB0D8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sellnuts_0x80ADADD0/func_80ADB254.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sellnuts_0x80ADADD0/func_80ADB4F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sellnuts_0x80ADADD0/func_80ADB544.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sellnuts_0x80ADADD0/func_80ADB924.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sellnuts_0x80ADADD0/func_80ADBAB8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sellnuts_0x80ADADD0/func_80ADBBEC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sellnuts_0x80ADADD0/func_80ADBC60.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sellnuts_0x80ADADD0/func_80ADBCE4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sellnuts_0x80ADADD0/func_80ADBD64.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sellnuts_0x80ADADD0/func_80ADBE80.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sellnuts_0x80ADADD0/func_80ADBFA0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sellnuts_0x80ADADD0/func_80ADC034.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sellnuts_0x80ADADD0/func_80ADC118.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sellnuts_0x80ADADD0/func_80ADC2CC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sellnuts_0x80ADADD0/func_80ADC37C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sellnuts_0x80ADADD0/func_80ADC580.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sellnuts_0x80ADADD0/func_80ADC5A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sellnuts_0x80ADADD0/func_80ADC6D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sellnuts_0x80ADADD0/func_80ADC7B4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sellnuts_0x80ADADD0/func_80ADC8C4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sellnuts_0x80ADADD0/func_80ADCA64.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sellnuts_0x80ADADD0/func_80ADCC04.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sellnuts_0x80ADADD0/func_80ADCD3C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sellnuts_0x80ADADD0/func_80ADCE4C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sellnuts_0x80ADADD0/func_80ADCFE8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sellnuts_0x80ADADD0/EnSellnuts_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sellnuts_0x80ADADD0/EnSellnuts_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sellnuts_0x80ADADD0/EnSellnuts_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sellnuts_0x80ADADD0/func_80ADD4E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sellnuts_0x80ADADD0/func_80ADD7B4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sellnuts_0x80ADADD0/func_80ADD7CC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sellnuts_0x80ADADD0/EnSellnuts_Draw.asm")
