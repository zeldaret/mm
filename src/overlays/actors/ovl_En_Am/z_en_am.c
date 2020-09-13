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
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_AM,
    sizeof(EnAm),
    (ActorFunc)EnAm_Init,
    (ActorFunc)EnAm_Destroy,
    (ActorFunc)EnAm_Update,
    (ActorFunc)EnAm_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Am_0x808AFCD0/EnAm_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Am_0x808AFCD0/EnAm_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Am_0x808AFCD0/func_808AFE38.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Am_0x808AFCD0/func_808AFF9C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Am_0x808AFCD0/func_808B0040.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Am_0x808AFCD0/func_808B00D8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Am_0x808AFCD0/func_808B0124.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Am_0x808AFCD0/func_808B0208.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Am_0x808AFCD0/func_808B0358.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Am_0x808AFCD0/func_808B03C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Am_0x808AFCD0/func_808B0460.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Am_0x808AFCD0/func_808B04A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Am_0x808AFCD0/func_808B04E4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Am_0x808AFCD0/func_808B0508.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Am_0x808AFCD0/func_808B057C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Am_0x808AFCD0/func_808B05C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Am_0x808AFCD0/func_808B0640.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Am_0x808AFCD0/func_808B066C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Am_0x808AFCD0/func_808B06D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Am_0x808AFCD0/func_808B07A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Am_0x808AFCD0/func_808B0820.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Am_0x808AFCD0/func_808B0894.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Am_0x808AFCD0/func_808B0AD0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Am_0x808AFCD0/func_808B0B4C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Am_0x808AFCD0/func_808B0B9C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Am_0x808AFCD0/EnAm_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Am_0x808AFCD0/func_808B0EA4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Am_0x808AFCD0/EnAm_Draw.asm")
