/*
 * File: z_en_kendo_js.c
 * Overlay: ovl_En_Kendo_Js
 * Description: Swordsman
 */

#include "z_en_kendo_js.h"

#define FLAGS 0x0A000019

#define THIS ((EnKendoJs*)thisx)

void EnKendoJs_Init(Actor* thisx, GlobalContext* globalCtx);
void EnKendoJs_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnKendoJs_Update(Actor* thisx, GlobalContext* globalCtx);
void EnKendoJs_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
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

#endif

extern ColliderCylinderInit D_80B27C30;
extern CollisionCheckInfoInit2 D_80B27C5C;

extern UNK_TYPE D_0600016C;
extern UNK_TYPE D_06000F4C;

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
