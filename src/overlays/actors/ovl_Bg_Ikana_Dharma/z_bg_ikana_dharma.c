/*
 * File: z_bg_ikana_dharma.c
 * Overlay: ovl_Bg_Ikana_Dharma
 * Description: Stone Tower Temple - Punchable Pillar Segments
 */

#include "z_bg_ikana_dharma.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((BgIkanaDharma*)thisx)

void BgIkanaDharma_Init(Actor* thisx, GlobalContext* globalCtx);
void BgIkanaDharma_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgIkanaDharma_Update(Actor* thisx, GlobalContext* globalCtx);
void BgIkanaDharma_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Bg_Ikana_Dharma_InitVars = {
    ACTOR_BG_IKANA_DHARMA,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_IKANA_OBJ,
    sizeof(BgIkanaDharma),
    (ActorFunc)BgIkanaDharma_Init,
    (ActorFunc)BgIkanaDharma_Destroy,
    (ActorFunc)BgIkanaDharma_Update,
    (ActorFunc)BgIkanaDharma_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BECAD0 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_NONE, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00000100, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
    { 98, 10, 25, { 0, 0, 0 } },
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80BECAFC[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 320, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 320, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -1100, ICHAIN_STOP),
};

#endif

extern ColliderCylinderInit D_80BECAD0;
extern InitChainEntry D_80BECAFC[];

extern UNK_TYPE D_060008C8;
extern UNK_TYPE D_06000C50;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Dharma/func_80BEC240.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Dharma/BgIkanaDharma_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Dharma/BgIkanaDharma_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Dharma/func_80BEC5C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Dharma/func_80BEC5E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Dharma/func_80BEC758.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Dharma/func_80BEC790.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Dharma/func_80BEC7EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Dharma/func_80BEC808.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Dharma/BgIkanaDharma_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Dharma/BgIkanaDharma_Draw.s")
