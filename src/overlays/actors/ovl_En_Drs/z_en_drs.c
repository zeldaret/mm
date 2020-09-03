#include "z_en_drs.h"

#define FLAGS 0x00000000

#define THIS ((EnDrs*)thisx)

void EnDrs_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDrs_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDrs_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Drs_InitVars = {
    ACTOR_EN_DRS,
    ACTORTYPE_PROP,
    FLAGS,
    OBJECT_DRS,
    sizeof(EnDrs),
    (ActorFunc)EnDrs_Init,
    (ActorFunc)EnDrs_Destroy,
    (ActorFunc)EnDrs_Update,
    (ActorFunc)NULL
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Drs_0x80C1E290/func_80C1E290.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Drs_0x80C1E290/func_80C1E2D4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Drs_0x80C1E290/func_80C1E3DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Drs_0x80C1E290/EnDrs_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Drs_0x80C1E290/EnDrs_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Drs_0x80C1E290/EnDrs_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Drs_0x80C1E290/func_80C1E4B0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Drs_0x80C1E290/func_80C1E568.asm")
