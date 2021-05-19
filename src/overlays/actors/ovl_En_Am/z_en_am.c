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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Am_0x808AFCD0/EnAm_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Am_0x808AFCD0/EnAm_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Am_0x808AFCD0/func_808AFE38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Am_0x808AFCD0/func_808AFF9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Am_0x808AFCD0/func_808B0040.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Am_0x808AFCD0/func_808B00D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Am_0x808AFCD0/func_808B0124.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Am_0x808AFCD0/func_808B0208.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Am_0x808AFCD0/func_808B0358.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Am_0x808AFCD0/func_808B03C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Am_0x808AFCD0/func_808B0460.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Am_0x808AFCD0/func_808B04A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Am_0x808AFCD0/func_808B04E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Am_0x808AFCD0/func_808B0508.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Am_0x808AFCD0/func_808B057C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Am_0x808AFCD0/func_808B05C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Am_0x808AFCD0/func_808B0640.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Am_0x808AFCD0/func_808B066C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Am_0x808AFCD0/func_808B06D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Am_0x808AFCD0/func_808B07A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Am_0x808AFCD0/func_808B0820.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Am_0x808AFCD0/func_808B0894.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Am_0x808AFCD0/func_808B0AD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Am_0x808AFCD0/func_808B0B4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Am_0x808AFCD0/func_808B0B9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Am_0x808AFCD0/EnAm_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Am_0x808AFCD0/func_808B0EA4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Am_0x808AFCD0/EnAm_Draw.asm")
