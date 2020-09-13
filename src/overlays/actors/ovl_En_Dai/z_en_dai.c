#include "z_en_dai.h"

#define FLAGS 0x02000039

#define THIS ((EnDai*)thisx)

void EnDai_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDai_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDai_Update(Actor* thisx, GlobalContext* globalCtx);
void EnDai_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Dai_InitVars = {
    ACTOR_EN_DAI,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_DAI,
    sizeof(EnDai),
    (ActorFunc)EnDai_Init,
    (ActorFunc)EnDai_Destroy,
    (ActorFunc)EnDai_Update,
    (ActorFunc)EnDai_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Dai_0x80B3DFF0/func_80B3DFF0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dai_0x80B3DFF0/func_80B3E168.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dai_0x80B3DFF0/func_80B3E460.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dai_0x80B3DFF0/func_80B3E5B4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dai_0x80B3DFF0/func_80B3E5DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dai_0x80B3DFF0/func_80B3E69C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dai_0x80B3DFF0/func_80B3E7C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dai_0x80B3DFF0/func_80B3E834.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dai_0x80B3DFF0/func_80B3E8BC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dai_0x80B3DFF0/func_80B3E96C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dai_0x80B3DFF0/func_80B3EC10.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dai_0x80B3DFF0/func_80B3EC84.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dai_0x80B3DFF0/func_80B3ED88.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dai_0x80B3DFF0/func_80B3EE8C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dai_0x80B3DFF0/func_80B3EEDC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dai_0x80B3DFF0/func_80B3EF90.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dai_0x80B3DFF0/func_80B3F00C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dai_0x80B3DFF0/func_80B3F044.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dai_0x80B3DFF0/EnDai_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dai_0x80B3DFF0/EnDai_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dai_0x80B3DFF0/EnDai_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dai_0x80B3DFF0/func_80B3F598.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dai_0x80B3DFF0/func_80B3F614.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dai_0x80B3DFF0/func_80B3F6EC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dai_0x80B3DFF0/func_80B3F78C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dai_0x80B3DFF0/func_80B3F920.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dai_0x80B3DFF0/EnDai_Draw.asm")
