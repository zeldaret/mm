/*
 * File: z_en_js.c
 * Overlay: ovl_En_Js
 * Description: Moon Child
 */

#include "z_en_js.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10)

#define THIS ((EnJs*)thisx)

void EnJs_Init(Actor* thisx, GlobalContext* globalCtx);
void EnJs_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnJs_Update(Actor* thisx, GlobalContext* globalCtx);
void EnJs_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Js_InitVars = {
    ACTOR_EN_JS,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_OB,
    sizeof(EnJs),
    (ActorFunc)EnJs_Init,
    (ActorFunc)EnJs_Destroy,
    (ActorFunc)EnJs_Update,
    (ActorFunc)EnJs_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_8096ABA0 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_ENEMY, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 20, 40, 0, { 0, 0, 0 } },
};

#endif

extern ColliderCylinderInit D_8096ABA0;

extern UNK_TYPE D_06010880;
extern UNK_TYPE D_06016F58;
extern UNK_TYPE D_06017E98;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/EnJs_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/EnJs_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80968A5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80968B18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80968B8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80968CB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80968DD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80968E38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80968F48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_809691B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_809692A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_8096933C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80969400.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80969494.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_809694E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80969530.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_809695FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80969688.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_809696EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_8096971C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80969748.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80969898.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80969AA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80969B5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80969C54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_80969DA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_8096A080.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_8096A104.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_8096A184.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_8096A1E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_8096A2C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_8096A38C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_8096A6F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/EnJs_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/func_8096A9F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Js/EnJs_Draw.s")
