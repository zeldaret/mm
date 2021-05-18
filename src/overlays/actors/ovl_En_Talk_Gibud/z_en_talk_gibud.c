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
    (ActorFunc)EnTalkGibud_Draw,
};
*/

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
