#include "z_en_tru_mt.h"

#define FLAGS 0x00000039

#define THIS ((EnTruMt*)thisx)

void EnTruMt_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTruMt_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTruMt_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTruMt_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Tru_Mt_InitVars = {
    ACTOR_EN_TRU_MT,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_TRU,
    sizeof(EnTruMt),
    (ActorFunc)EnTruMt_Init,
    (ActorFunc)EnTruMt_Destroy,
    (ActorFunc)EnTruMt_Update,
    (ActorFunc)EnTruMt_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru_Mt/func_80B76030.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru_Mt/func_80B76110.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru_Mt/func_80B76188.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru_Mt/func_80B761FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru_Mt/func_80B76368.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru_Mt/func_80B763C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru_Mt/func_80B76440.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru_Mt/func_80B76540.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru_Mt/func_80B76600.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru_Mt/func_80B7679C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru_Mt/func_80B768F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru_Mt/func_80B76924.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru_Mt/func_80B76980.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru_Mt/func_80B76A64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru_Mt/func_80B76BB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru_Mt/func_80B76C38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru_Mt/EnTruMt_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru_Mt/EnTruMt_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru_Mt/EnTruMt_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru_Mt/func_80B76ED4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru_Mt/func_80B77008.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru_Mt/func_80B77078.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru_Mt/func_80B77354.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tru_Mt/EnTruMt_Draw.s")
