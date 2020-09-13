#include "z_bg_ikana_dharma.h"

#define FLAGS 0x00000010

#define THIS ((BgIkanaDharma*)thisx)

void BgIkanaDharma_Init(Actor* thisx, GlobalContext* globalCtx);
void BgIkanaDharma_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgIkanaDharma_Update(Actor* thisx, GlobalContext* globalCtx);
void BgIkanaDharma_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Bg_Ikana_Dharma_InitVars = {
    ACTOR_BG_IKANA_DHARMA,
    ACTORTYPE_BG,
    FLAGS,
    OBJECT_IKANA_OBJ,
    sizeof(BgIkanaDharma),
    (ActorFunc)BgIkanaDharma_Init,
    (ActorFunc)BgIkanaDharma_Destroy,
    (ActorFunc)BgIkanaDharma_Update,
    (ActorFunc)BgIkanaDharma_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Dharma_0x80BEC240/func_80BEC240.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Dharma_0x80BEC240/BgIkanaDharma_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Dharma_0x80BEC240/BgIkanaDharma_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Dharma_0x80BEC240/func_80BEC5C4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Dharma_0x80BEC240/func_80BEC5E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Dharma_0x80BEC240/func_80BEC758.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Dharma_0x80BEC240/func_80BEC790.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Dharma_0x80BEC240/func_80BEC7EC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Dharma_0x80BEC240/func_80BEC808.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Dharma_0x80BEC240/BgIkanaDharma_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ikana_Dharma_0x80BEC240/BgIkanaDharma_Draw.asm")
