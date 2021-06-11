#include "z_en_col_man.h"

#define FLAGS 0x00100000

#define THIS ((EnColMan*)thisx)

void EnColMan_Init(Actor* thisx, GlobalContext* globalCtx);
void EnColMan_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnColMan_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Col_Man_InitVars = {
    ACTOR_EN_COL_MAN,
    ACTORCAT_MISC,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnColMan),
    (ActorFunc)EnColMan_Init,
    (ActorFunc)EnColMan_Destroy,
    (ActorFunc)EnColMan_Update,
    (ActorFunc)NULL,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Col_Man/EnColMan_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Col_Man/EnColMan_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Col_Man/func_80AFDD60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Col_Man/func_80AFDE00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Col_Man/func_80AFDF00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Col_Man/func_80AFDF60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Col_Man/func_80AFDFB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Col_Man/func_80AFE234.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Col_Man/func_80AFE25C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Col_Man/EnColMan_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Col_Man/func_80AFE414.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Col_Man/func_80AFE4AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Col_Man/func_80AFE584.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Col_Man/func_80AFE650.s")
