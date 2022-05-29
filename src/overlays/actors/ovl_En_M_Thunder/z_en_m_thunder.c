/*
 * File: z_en_m_thunder.c
 * Overlay: ovl_En_M_Thunder
 * Description: Spin attack and sword beams
 */

#include "z_en_m_thunder.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((EnMThunder*)thisx)

void EnMThunder_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMThunder_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMThunder_Update(Actor* thisx, GlobalContext* globalCtx);
void EnMThunder_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_M_Thunder_InitVars = {
    ACTOR_EN_M_THUNDER,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnMThunder),
    (ActorFunc)EnMThunder_Init,
    (ActorFunc)EnMThunder_Destroy,
    (ActorFunc)EnMThunder_Update,
    (ActorFunc)EnMThunder_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_808B7120 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_PLAYER, AC_NONE, OC1_NONE, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK2, { 0x01000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NONE, BUMP_ON, OCELEM_ON, },
    { 200, 200, 0, { 0, 0, 0 } },
};

#endif

extern ColliderCylinderInit D_808B7120;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_M_Thunder/func_808B53C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_M_Thunder/EnMThunder_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_M_Thunder/EnMThunder_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_M_Thunder/func_808B5890.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_M_Thunder/func_808B58CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_M_Thunder/func_808B5984.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_M_Thunder/func_808B5EEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_M_Thunder/func_808B5F68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_M_Thunder/func_808B60D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_M_Thunder/func_808B6310.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_M_Thunder/EnMThunder_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_M_Thunder/func_808B65BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_M_Thunder/EnMThunder_Draw.s")
