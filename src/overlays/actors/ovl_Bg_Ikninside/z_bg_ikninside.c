/*
 * File: z_bg_ikninside.c
 * Overlay: ovl_Bg_Ikninside
 * Description: Ancient Castle of Ikana Objects
 */

#include "z_bg_ikninside.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((BgIkninside*)thisx)

void BgIkninside_Init(Actor* thisx, GlobalContext* globalCtx);
void BgIkninside_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgIkninside_Update(Actor* thisx, GlobalContext* globalCtx);
void BgIkninside_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Bg_Ikninside_InitVars = {
    ACTOR_BG_IKNINSIDE,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_IKNINSIDE_OBJ,
    sizeof(BgIkninside),
    (ActorFunc)BgIkninside_Init,
    (ActorFunc)BgIkninside_Destroy,
    (ActorFunc)BgIkninside_Update,
    (ActorFunc)BgIkninside_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80C076A8 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_PLAYER, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x80000008, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
    { 32, 32, 0, { 0, 0, 0 } },
};

#endif

extern ColliderCylinderInit D_80C076A8;

extern UNK_TYPE D_0600CC78;
extern UNK_TYPE D_0600DE48;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikninside/BgIkninside_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikninside/BgIkninside_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikninside/func_80C07220.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikninside/func_80C07230.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikninside/func_80C072D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikninside/BgIkninside_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikninside/BgIkninside_Draw.s")
