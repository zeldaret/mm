#include "z_en_am.h"

#define FLAGS 0x00000405

#define THIS ((EnAm*)thisx)

void EnAm_Init(Actor* thisx, GlobalContext* globalCtx);
void EnAm_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnAm_Update(Actor* thisx, GlobalContext* globalCtx);
void EnAm_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Am_InitVars = {
    ACTOR_EN_AM,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_AM,
    sizeof(EnAm),
    (ActorFunc)EnAm_Init,
    (ActorFunc)EnAm_Destroy,
    (ActorFunc)EnAm_Update,
    (ActorFunc)EnAm_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/EnAm_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/EnAm_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/func_808AFE38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/func_808AFF9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/func_808B0040.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/func_808B00D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/func_808B0124.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/func_808B0208.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/func_808B0358.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/func_808B03C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/func_808B0460.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/func_808B04A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/func_808B04E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/func_808B0508.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/func_808B057C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/func_808B05C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/func_808B0640.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/func_808B066C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/func_808B06D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/func_808B07A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/func_808B0820.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/func_808B0894.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/func_808B0AD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/func_808B0B4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/func_808B0B9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/EnAm_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/func_808B0EA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Am/EnAm_Draw.s")
