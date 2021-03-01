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

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Warp_Uzu_0x80A66180/EnWarpUzu_Init.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Warp_Uzu_0x80A66180/EnWarpUzu_Destroy.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Warp_Uzu_0x80A66180/func_80A66208.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Warp_Uzu_0x80A66180/func_80A66278.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Warp_Uzu_0x80A66180/func_80A66384.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Warp_Uzu_0x80A66180/func_80A663E8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Warp_Uzu_0x80A66180/EnWarpUzu_Update.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Warp_Uzu_0x80A66180/EnWarpUzu_Draw.asm")
