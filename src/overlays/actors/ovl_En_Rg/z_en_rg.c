#include "z_en_rg.h"

#define FLAGS 0x80000010

#define THIS ((EnRg*)thisx)

void EnRg_Init(Actor* thisx, GlobalContext* globalCtx);
void EnRg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnRg_Update(Actor* thisx, GlobalContext* globalCtx);
void EnRg_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Rg_InitVars = {
    ACTOR_EN_RG,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_OF1D_MAP,
    sizeof(EnRg),
    (ActorFunc)EnRg_Init,
    (ActorFunc)EnRg_Destroy,
    (ActorFunc)EnRg_Update,
    (ActorFunc)EnRg_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rg/func_80BF3920.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rg/func_80BF3C64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rg/func_80BF3DA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rg/func_80BF3DC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rg/func_80BF3E88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rg/func_80BF3ED4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rg/func_80BF3F14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rg/func_80BF3FF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rg/func_80BF4024.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rg/func_80BF409C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rg/func_80BF40F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rg/func_80BF416C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rg/func_80BF4220.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rg/func_80BF42BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rg/func_80BF43FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rg/func_80BF4560.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rg/func_80BF45B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rg/func_80BF47AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rg/func_80BF4934.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rg/func_80BF4964.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rg/func_80BF4AB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rg/func_80BF4D64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rg/func_80BF4DA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rg/func_80BF4EBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rg/func_80BF4FC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rg/EnRg_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rg/EnRg_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rg/EnRg_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rg/func_80BF547C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rg/func_80BF5588.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rg/EnRg_Draw.s")
