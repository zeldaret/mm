#include "z_en_talk_gibud.h"

#define FLAGS 0x00000415

#define THIS ((EnTalkGibud*)thisx)

void EnTalkGibud_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTalkGibud_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTalkGibud_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTalkGibud_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Talk_Gibud_InitVars = {
    ACTOR_EN_TALK_GIBUD,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_RD,
    sizeof(EnTalkGibud),
    (ActorFunc)EnTalkGibud_Init,
    (ActorFunc)EnTalkGibud_Destroy,
    (ActorFunc)EnTalkGibud_Update,
    (ActorFunc)EnTalkGibud_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/EnTalkGibud_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/EnTalkGibud_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80AFEB38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80AFEB7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80AFEC08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80AFEC4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80AFED08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80AFED7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80AFEFD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80AFF030.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80AFF22C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80AFF288.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80AFF330.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80AFF378.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80AFF45C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80AFF4AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80AFF618.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80AFF6A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80AFF700.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80AFF76C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80AFF880.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80AFF8E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80AFF9CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80AFFA68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80AFFAB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80AFFC10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80AFFC9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80AFFD3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80AFFE3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80AFFE94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80AFFFA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80AFFFBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80B000FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80B00158.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80B00384.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80B0040C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80B00484.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80B004D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80B005EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80B00760.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80B008BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80B008FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80B0094C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80B00B8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80B00C94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80B00D9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/EnTalkGibud_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80B00F08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/func_80B00F64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk_Gibud/EnTalkGibud_Draw.s")
