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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091D630.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091D660.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091D6C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091D728.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091D7C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091D840.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091D904.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091D944.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091DA14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/EnFish_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/EnFish_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091DD48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091DDF4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091DEE4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091DF68.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091E070.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091E128.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091E2E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091E34C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091E5EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091E658.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091E810.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091E880.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091E9A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091EAF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091ECF4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091ED70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091EF30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091EFE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091F344.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091F3BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091F5A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091F830.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/EnFish_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/func_8091F994.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish_0x8091D630/EnFish_Draw.asm")
