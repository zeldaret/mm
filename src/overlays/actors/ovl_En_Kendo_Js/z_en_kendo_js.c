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
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_JS,
    sizeof(EnKendoJs),
    (ActorFunc)EnKendoJs_Init,
    (ActorFunc)EnKendoJs_Destroy,
    (ActorFunc)EnKendoJs_Update,
    (ActorFunc)EnKendoJs_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Kendo_Js_0x80B262A0/EnKendoJs_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kendo_Js_0x80B262A0/EnKendoJs_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kendo_Js_0x80B262A0/func_80B26538.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kendo_Js_0x80B262A0/func_80B2654C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kendo_Js_0x80B262A0/func_80B26758.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kendo_Js_0x80B262A0/func_80B269A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kendo_Js_0x80B262A0/func_80B26AE8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kendo_Js_0x80B262A0/func_80B26AFC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kendo_Js_0x80B262A0/func_80B26BF8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kendo_Js_0x80B262A0/func_80B26EB4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kendo_Js_0x80B262A0/func_80B26F14.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kendo_Js_0x80B262A0/func_80B26F6C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kendo_Js_0x80B262A0/func_80B2701C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kendo_Js_0x80B262A0/func_80B27030.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kendo_Js_0x80B262A0/func_80B2714C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kendo_Js_0x80B262A0/func_80B27188.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kendo_Js_0x80B262A0/func_80B273D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kendo_Js_0x80B262A0/func_80B2740C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kendo_Js_0x80B262A0/func_80B274BC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kendo_Js_0x80B262A0/func_80B276C4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kendo_Js_0x80B262A0/func_80B276D8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kendo_Js_0x80B262A0/func_80B27760.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kendo_Js_0x80B262A0/func_80B27774.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kendo_Js_0x80B262A0/func_80B2783C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kendo_Js_0x80B262A0/func_80B27880.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kendo_Js_0x80B262A0/func_80B278C4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kendo_Js_0x80B262A0/func_80B279AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kendo_Js_0x80B262A0/func_80B279F0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kendo_Js_0x80B262A0/func_80B27A90.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kendo_Js_0x80B262A0/EnKendoJs_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kendo_Js_0x80B262A0/func_80B27B54.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kendo_Js_0x80B262A0/func_80B27B8C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kendo_Js_0x80B262A0/EnKendoJs_Draw.asm")
