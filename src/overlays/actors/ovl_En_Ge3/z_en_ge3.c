/*
 * File: z_en_ge3.c
 * Overlay: ovl_En_Ge3
 * Description: Aviel
 */

#include "z_en_ge3.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10 | ACTOR_FLAG_80000000)

#define THIS ((EnGe3*)thisx)

void EnGe3_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGe3_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGe3_Update(Actor* thisx, GlobalContext* globalCtx);
void EnGe3_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Ge3_InitVars = {
    ACTOR_EN_GE3,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_GELDB,
    sizeof(EnGe3),
    (ActorFunc)EnGe3_Init,
    (ActorFunc)EnGe3_Destroy,
    (ActorFunc)EnGe3_Update,
    (ActorFunc)EnGe3_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_809A0DA0 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x01000222, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 20, 50, 0, { 0, 0, 0 } },
};

#endif

extern ColliderCylinderInit D_809A0DA0;

extern UNK_TYPE D_0600A808;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge3/EnGe3_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge3/EnGe3_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge3/func_809A0070.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge3/func_809A00F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge3/func_809A020C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge3/func_809A024C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge3/func_809A0350.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge3/func_809A03AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge3/func_809A03FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge3/func_809A04D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge3/func_809A0820.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge3/func_809A08A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge3/EnGe3_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge3/func_809A096C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge3/func_809A0A14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge3/func_809A0C60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge3/EnGe3_Draw.s")
