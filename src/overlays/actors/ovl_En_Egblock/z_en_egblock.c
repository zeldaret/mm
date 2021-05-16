#include "z_en_egblock.h"

#define FLAGS 0x08000000

#define THIS ((EnEgblock*)thisx)

void EnEgblock_Init(Actor* thisx, GlobalContext* globalCtx);
void EnEgblock_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnEgblock_Update(Actor* thisx, GlobalContext* globalCtx);
void EnEgblock_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Egblock_InitVars = {
    ACTOR_EN_EGBLOCK,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_EG,
    sizeof(EnEgblock),
    (ActorFunc)EnEgblock_Init,
    (ActorFunc)EnEgblock_Destroy,
    (ActorFunc)EnEgblock_Update,
    (ActorFunc)EnEgblock_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egblock/EnEgblock_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egblock/EnEgblock_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egblock/func_80ABA8A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egblock/func_80ABA988.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egblock/func_80ABA9B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egblock/EnEgblock_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egblock/EnEgblock_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egblock/func_80ABAAF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egblock/func_80ABACB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Egblock/func_80ABAE64.s")
