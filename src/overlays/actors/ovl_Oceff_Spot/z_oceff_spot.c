/*
 * File: z_oceff_spot.c
 * Overlay: ovl_Oceff_Spot
 * Description: Sun's Song Ocarina Effect
 */

#include "z_oceff_spot.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_2000000)

#define THIS ((OceffSpot*)thisx)

void OceffSpot_Init(Actor* thisx, GlobalContext* globalCtx);
void OceffSpot_Destroy(Actor* thisx, GlobalContext* globalCtx);
void OceffSpot_Update(Actor* thisx, GlobalContext* globalCtx);
void OceffSpot_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_809728F8(OceffSpot* this, GlobalContext* globalCtx);
void func_80972934(OceffSpot* this, GlobalContext* globalCtx);

void OceffSpot_SetupAction(OceffSpot* this, OceffSpotActionFunc actionFunc);

#if 0
const ActorInit Oceff_Spot_InitVars = {
    ACTOR_OCEFF_SPOT,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(OceffSpot),
    (ActorFunc)OceffSpot_Init,
    (ActorFunc)OceffSpot_Destroy,
    (ActorFunc)OceffSpot_Update,
    (ActorFunc)OceffSpot_Draw,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80973478[] = {
    ICHAIN_VEC3F_DIV1000(scale, 0, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 1500, ICHAIN_STOP),
};

#endif

extern InitChainEntry D_80973478[];

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Spot/OceffSpot_SetupAction.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Spot/OceffSpot_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Spot/OceffSpot_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Spot/func_80972844.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Spot/func_809728F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Spot/func_80972934.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Spot/OceffSpot_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Spot/OceffSpot_Draw.s")
