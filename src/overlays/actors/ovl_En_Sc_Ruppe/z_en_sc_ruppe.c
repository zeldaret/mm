/*
 * File: z_en_sc_ruppe.c
 * Overlay: ovl_En_Sc_Ruppe
 * Description: Giant Rupee
 */

#include "z_en_sc_ruppe.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((EnScRuppe*)thisx)

void EnScRuppe_Init(Actor* thisx, GlobalContext* globalCtx);
void EnScRuppe_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnScRuppe_Update(Actor* thisx, GlobalContext* globalCtx);
void EnScRuppe_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80BD6A8C(EnScRuppe* this, GlobalContext* globalCtx);
void func_80BD6B18(EnScRuppe* this, GlobalContext* globalCtx);

#if 0
const ActorInit En_Sc_Ruppe_InitVars = {
    ACTOR_EN_SC_RUPPE,
    ACTORCAT_NPC,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnScRuppe),
    (ActorFunc)EnScRuppe_Init,
    (ActorFunc)EnScRuppe_Destroy,
    (ActorFunc)EnScRuppe_Update,
    (ActorFunc)EnScRuppe_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BD6E40 = {
    { COLTYPE_NONE, AT_NONE, AC_NONE, OC1_ON | OC1_NO_PUSH | OC1_TYPE_PLAYER, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 10, 30, 0, { 0, 0, 0 } },
};

#endif

extern ColliderCylinderInit D_80BD6E40;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sc_Ruppe/func_80BD6910.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sc_Ruppe/func_80BD697C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sc_Ruppe/func_80BD6A8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sc_Ruppe/func_80BD6B18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sc_Ruppe/EnScRuppe_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sc_Ruppe/EnScRuppe_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sc_Ruppe/EnScRuppe_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sc_Ruppe/EnScRuppe_Draw.s")
