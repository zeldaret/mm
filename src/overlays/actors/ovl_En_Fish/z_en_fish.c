#include "z_en_fish.h"

#define FLAGS 0x00000000

#define THIS ((EnFish*)thisx)

void EnFish_Init(Actor* thisx, GlobalContext* globalCtx);
void EnFish_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnFish_Update(Actor* thisx, GlobalContext* globalCtx);
void EnFish_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Fish_InitVars = {
    ACTOR_EN_FISH,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnFish),
    (ActorFunc)EnFish_Init,
    (ActorFunc)EnFish_Destroy,
    (ActorFunc)EnFish_Update,
    (ActorFunc)EnFish_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish/func_8091D630.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish/func_8091D660.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish/func_8091D6C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish/func_8091D728.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish/func_8091D7C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish/func_8091D840.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish/func_8091D904.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish/func_8091D944.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish/func_8091DA14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish/EnFish_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish/EnFish_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish/func_8091DD48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish/func_8091DDF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish/func_8091DEE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish/func_8091DF68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish/func_8091E070.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish/func_8091E128.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish/func_8091E2E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish/func_8091E34C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish/func_8091E5EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish/func_8091E658.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish/func_8091E810.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish/func_8091E880.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish/func_8091E9A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish/func_8091EAF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish/func_8091ECF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish/func_8091ED70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish/func_8091EF30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish/func_8091EFE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish/func_8091F344.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish/func_8091F3BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish/func_8091F5A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish/func_8091F830.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish/EnFish_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish/func_8091F994.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish/EnFish_Draw.s")
