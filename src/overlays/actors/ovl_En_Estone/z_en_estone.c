/*
 * File: z_en_estone.c
 * Overlay: ovl_En_Estone
 * Description: Eyegore Rubble
 */

#include "z_en_estone.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((EnEstone*)thisx)

void EnEstone_Init(Actor* thisx, GlobalContext* globalCtx);
void EnEstone_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnEstone_Update(Actor* thisx, GlobalContext* globalCtx);
void EnEstone_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A9A1DC(EnEstone* this, GlobalContext* globalCtx);
void func_80A9A4B0(EnEstone* this, GlobalContext* globalCtx);

#if 0
const ActorInit En_Estone_InitVars = {
    ACTOR_EN_ESTONE,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_EG,
    sizeof(EnEstone),
    (ActorFunc)EnEstone_Init,
    (ActorFunc)EnEstone_Destroy,
    (ActorFunc)EnEstone_Update,
    (ActorFunc)EnEstone_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80A9AB70 = {
    { COLTYPE_HARD, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
    { 30, 30, -10, { 0, 0, 0 } },
};

#endif

extern ColliderCylinderInit D_80A9AB70;

extern UNK_TYPE D_06010240;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Estone/EnEstone_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Estone/EnEstone_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Estone/func_80A9A1DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Estone/func_80A9A4B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Estone/EnEstone_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Estone/EnEstone_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Estone/func_80A9A774.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Estone/func_80A9A870.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Estone/func_80A9A9C0.s")
