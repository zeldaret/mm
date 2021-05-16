#include "z_en_drs.h"

#define FLAGS 0x00000000

#define THIS ((EnDrs*)thisx)

void EnDrs_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDrs_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDrs_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Drs_InitVars = {
    ACTOR_EN_DRS,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_DRS,
    sizeof(EnDrs),
    (ActorFunc)EnDrs_Init,
    (ActorFunc)EnDrs_Destroy,
    (ActorFunc)EnDrs_Update,
    (ActorFunc)NULL
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Drs/func_80C1E290.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Drs/func_80C1E2D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Drs/func_80C1E3DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Drs/EnDrs_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Drs/EnDrs_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Drs/EnDrs_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Drs/func_80C1E4B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Drs/func_80C1E568.s")
