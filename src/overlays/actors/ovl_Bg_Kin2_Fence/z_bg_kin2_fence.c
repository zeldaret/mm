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

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Bg_Kin2_Fence_0x80B6E820/func_80B6E820.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Bg_Kin2_Fence_0x80B6E820/func_80B6E890.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Bg_Kin2_Fence_0x80B6E820/BgKin2Fence_Init.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Bg_Kin2_Fence_0x80B6E820/BgKin2Fence_Destroy.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Bg_Kin2_Fence_0x80B6E820/func_80B6EADC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Bg_Kin2_Fence_0x80B6E820/func_80B6EAF4.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Bg_Kin2_Fence_0x80B6E820/func_80B6EBF4.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Bg_Kin2_Fence_0x80B6E820/func_80B6EC08.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Bg_Kin2_Fence_0x80B6E820/func_80B6EC70.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Bg_Kin2_Fence_0x80B6E820/func_80B6EC8C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Bg_Kin2_Fence_0x80B6E820/func_80B6ECC4.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Bg_Kin2_Fence_0x80B6E820/func_80B6ECD8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Bg_Kin2_Fence_0x80B6E820/func_80B6ED30.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Bg_Kin2_Fence_0x80B6E820/func_80B6ED58.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Bg_Kin2_Fence_0x80B6E820/BgKin2Fence_Update.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Bg_Kin2_Fence_0x80B6E820/BgKin2Fence_Draw.asm")
