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


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B27C30 = {
    { COLTYPE_NONE, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 18, 30, 0, { 0, 0, 0 } },
};


// sColChkInfoInit
static CollisionCheckInfoInit2 D_80B27C5C = { 0, 0, 0, 0, MASS_IMMOVABLE };

*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kendo_Js_0x80B262A0/EnKendoJs_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kendo_Js_0x80B262A0/EnKendoJs_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kendo_Js_0x80B262A0/func_80B26538.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kendo_Js_0x80B262A0/func_80B2654C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kendo_Js_0x80B262A0/func_80B26758.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kendo_Js_0x80B262A0/func_80B269A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kendo_Js_0x80B262A0/func_80B26AE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kendo_Js_0x80B262A0/func_80B26AFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kendo_Js_0x80B262A0/func_80B26BF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kendo_Js_0x80B262A0/func_80B26EB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kendo_Js_0x80B262A0/func_80B26F14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kendo_Js_0x80B262A0/func_80B26F6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kendo_Js_0x80B262A0/func_80B2701C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kendo_Js_0x80B262A0/func_80B27030.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kendo_Js_0x80B262A0/func_80B2714C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kendo_Js_0x80B262A0/func_80B27188.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kendo_Js_0x80B262A0/func_80B273D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kendo_Js_0x80B262A0/func_80B2740C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kendo_Js_0x80B262A0/func_80B274BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kendo_Js_0x80B262A0/func_80B276C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kendo_Js_0x80B262A0/func_80B276D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kendo_Js_0x80B262A0/func_80B27760.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kendo_Js_0x80B262A0/func_80B27774.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kendo_Js_0x80B262A0/func_80B2783C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kendo_Js_0x80B262A0/func_80B27880.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kendo_Js_0x80B262A0/func_80B278C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kendo_Js_0x80B262A0/func_80B279AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kendo_Js_0x80B262A0/func_80B279F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kendo_Js_0x80B262A0/func_80B27A90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kendo_Js_0x80B262A0/EnKendoJs_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kendo_Js_0x80B262A0/func_80B27B54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kendo_Js_0x80B262A0/func_80B27B8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kendo_Js_0x80B262A0/EnKendoJs_Draw.asm")
