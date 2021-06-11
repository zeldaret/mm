#include "z_en_kendo_js.h"

#define FLAGS 0x0A000019

#define THIS ((EnKendoJs*)thisx)

void EnKendoJs_Init(Actor* thisx, GlobalContext* globalCtx);
void EnKendoJs_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnKendoJs_Update(Actor* thisx, GlobalContext* globalCtx);
void EnKendoJs_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Kendo_Js_InitVars = {
    ACTOR_EN_KENDO_JS,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_JS,
    sizeof(EnKendoJs),
    (ActorFunc)EnKendoJs_Init,
    (ActorFunc)EnKendoJs_Destroy,
    (ActorFunc)EnKendoJs_Update,
    (ActorFunc)EnKendoJs_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kendo_Js/EnKendoJs_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kendo_Js/EnKendoJs_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kendo_Js/func_80B26538.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kendo_Js/func_80B2654C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kendo_Js/func_80B26758.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kendo_Js/func_80B269A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kendo_Js/func_80B26AE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kendo_Js/func_80B26AFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kendo_Js/func_80B26BF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kendo_Js/func_80B26EB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kendo_Js/func_80B26F14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kendo_Js/func_80B26F6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kendo_Js/func_80B2701C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kendo_Js/func_80B27030.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kendo_Js/func_80B2714C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kendo_Js/func_80B27188.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kendo_Js/func_80B273D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kendo_Js/func_80B2740C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kendo_Js/func_80B274BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kendo_Js/func_80B276C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kendo_Js/func_80B276D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kendo_Js/func_80B27760.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kendo_Js/func_80B27774.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kendo_Js/func_80B2783C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kendo_Js/func_80B27880.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kendo_Js/func_80B278C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kendo_Js/func_80B279AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kendo_Js/func_80B279F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kendo_Js/func_80B27A90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kendo_Js/EnKendoJs_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kendo_Js/func_80B27B54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kendo_Js/func_80B27B8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kendo_Js/EnKendoJs_Draw.s")
