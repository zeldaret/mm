#include "z_bg_kin2_fence.h"

#define FLAGS 0x00000010

#define THIS ((BgKin2Fence*)thisx)

void BgKin2Fence_Init(Actor* thisx, GlobalContext* globalCtx);
void BgKin2Fence_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgKin2Fence_Update(Actor* thisx, GlobalContext* globalCtx);
void BgKin2Fence_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Bg_Kin2_Fence_InitVars = {
    ACTOR_BG_KIN2_FENCE,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_KIN2_OBJ,
    sizeof(BgKin2Fence),
    (ActorFunc)BgKin2Fence_Init,
    (ActorFunc)BgKin2Fence_Destroy,
    (ActorFunc)BgKin2Fence_Update,
    (ActorFunc)BgKin2Fence_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Fence/func_80B6E820.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Fence/func_80B6E890.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Fence/BgKin2Fence_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Fence/BgKin2Fence_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Fence/func_80B6EADC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Fence/func_80B6EAF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Fence/func_80B6EBF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Fence/func_80B6EC08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Fence/func_80B6EC70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Fence/func_80B6EC8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Fence/func_80B6ECC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Fence/func_80B6ECD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Fence/func_80B6ED30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Fence/func_80B6ED58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Fence/BgKin2Fence_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Fence/BgKin2Fence_Draw.s")
