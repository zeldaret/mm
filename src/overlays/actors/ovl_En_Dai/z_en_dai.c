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
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_DAI,
    sizeof(EnDai),
    (ActorFunc)EnDai_Init,
    (ActorFunc)EnDai_Destroy,
    (ActorFunc)EnDai_Update,
    (ActorFunc)EnDai_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dai_0x80B3DFF0/func_80B3DFF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dai_0x80B3DFF0/func_80B3E168.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dai_0x80B3DFF0/func_80B3E460.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dai_0x80B3DFF0/func_80B3E5B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dai_0x80B3DFF0/func_80B3E5DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dai_0x80B3DFF0/func_80B3E69C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dai_0x80B3DFF0/func_80B3E7C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dai_0x80B3DFF0/func_80B3E834.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dai_0x80B3DFF0/func_80B3E8BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dai_0x80B3DFF0/func_80B3E96C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dai_0x80B3DFF0/func_80B3EC10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dai_0x80B3DFF0/func_80B3EC84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dai_0x80B3DFF0/func_80B3ED88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dai_0x80B3DFF0/func_80B3EE8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dai_0x80B3DFF0/func_80B3EEDC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dai_0x80B3DFF0/func_80B3EF90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dai_0x80B3DFF0/func_80B3F00C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dai_0x80B3DFF0/func_80B3F044.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dai_0x80B3DFF0/EnDai_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dai_0x80B3DFF0/EnDai_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dai_0x80B3DFF0/EnDai_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dai_0x80B3DFF0/func_80B3F598.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dai_0x80B3DFF0/func_80B3F614.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dai_0x80B3DFF0/func_80B3F6EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dai_0x80B3DFF0/func_80B3F78C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dai_0x80B3DFF0/func_80B3F920.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dai_0x80B3DFF0/EnDai_Draw.asm")
