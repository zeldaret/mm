#include "z_en_warp_uzu.h"

#define FLAGS 0x00000019

#define THIS ((EnWarpUzu*)thisx)

void EnWarpUzu_Init(Actor* thisx, GlobalContext* globalCtx);
void EnWarpUzu_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnWarpUzu_Update(Actor* thisx, GlobalContext* globalCtx);
void EnWarpUzu_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Warp_Uzu_InitVars = {
    ACTOR_EN_WARP_UZU,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_WARP_UZU,
    sizeof(EnWarpUzu),
    (ActorFunc)EnWarpUzu_Init,
    (ActorFunc)EnWarpUzu_Destroy,
    (ActorFunc)EnWarpUzu_Update,
    (ActorFunc)EnWarpUzu_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Warp_Uzu/EnWarpUzu_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Warp_Uzu/EnWarpUzu_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Warp_Uzu/func_80A66208.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Warp_Uzu/func_80A66278.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Warp_Uzu/func_80A66384.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Warp_Uzu/func_80A663E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Warp_Uzu/EnWarpUzu_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Warp_Uzu/EnWarpUzu_Draw.s")
