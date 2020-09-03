#include "z_en_torch.h"

#define FLAGS 0x00000000

#define THIS ((EnTorch*)thisx)

void EnTorch_Init(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Torch_InitVars = {
    ACTOR_EN_TORCH,
    ACTORTYPE_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnTorch),
    (ActorFunc)EnTorch_Init,
    (ActorFunc)NULL,
    (ActorFunc)NULL,
    (ActorFunc)NULL
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Torch_0x80973550/EnTorch_Init.asm")
