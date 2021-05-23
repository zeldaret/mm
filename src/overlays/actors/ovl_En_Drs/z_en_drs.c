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
    (ActorFunc)NULL,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Drs_0x80C1E290/func_80C1E290.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Drs_0x80C1E290/func_80C1E2D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Drs_0x80C1E290/func_80C1E3DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Drs_0x80C1E290/EnDrs_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Drs_0x80C1E290/EnDrs_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Drs_0x80C1E290/EnDrs_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Drs_0x80C1E290/func_80C1E4B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Drs_0x80C1E290/func_80C1E568.asm")
