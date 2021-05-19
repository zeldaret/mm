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
    (ActorFunc)EnTruMt_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_Mt_0x80B76030/func_80B76030.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_Mt_0x80B76030/func_80B76110.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_Mt_0x80B76030/func_80B76188.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_Mt_0x80B76030/func_80B761FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_Mt_0x80B76030/func_80B76368.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_Mt_0x80B76030/func_80B763C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_Mt_0x80B76030/func_80B76440.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_Mt_0x80B76030/func_80B76540.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_Mt_0x80B76030/func_80B76600.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_Mt_0x80B76030/func_80B7679C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_Mt_0x80B76030/func_80B768F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_Mt_0x80B76030/func_80B76924.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_Mt_0x80B76030/func_80B76980.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_Mt_0x80B76030/func_80B76A64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_Mt_0x80B76030/func_80B76BB8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_Mt_0x80B76030/func_80B76C38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_Mt_0x80B76030/EnTruMt_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_Mt_0x80B76030/EnTruMt_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_Mt_0x80B76030/EnTruMt_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_Mt_0x80B76030/func_80B76ED4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_Mt_0x80B76030/func_80B77008.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_Mt_0x80B76030/func_80B77078.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_Mt_0x80B76030/func_80B77354.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tru_Mt_0x80B76030/EnTruMt_Draw.asm")
