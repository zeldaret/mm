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
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_TRU,
    sizeof(EnTruMt),
    (ActorFunc)EnTruMt_Init,
    (ActorFunc)EnTruMt_Destroy,
    (ActorFunc)EnTruMt_Update,
    (ActorFunc)EnTruMt_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_Mt_0x80B76030/func_80B76030.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_Mt_0x80B76030/func_80B76110.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_Mt_0x80B76030/func_80B76188.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_Mt_0x80B76030/func_80B761FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_Mt_0x80B76030/func_80B76368.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_Mt_0x80B76030/func_80B763C4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_Mt_0x80B76030/func_80B76440.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_Mt_0x80B76030/func_80B76540.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_Mt_0x80B76030/func_80B76600.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_Mt_0x80B76030/func_80B7679C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_Mt_0x80B76030/func_80B768F0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_Mt_0x80B76030/func_80B76924.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_Mt_0x80B76030/func_80B76980.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_Mt_0x80B76030/func_80B76A64.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_Mt_0x80B76030/func_80B76BB8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_Mt_0x80B76030/func_80B76C38.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_Mt_0x80B76030/EnTruMt_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_Mt_0x80B76030/EnTruMt_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_Mt_0x80B76030/EnTruMt_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_Mt_0x80B76030/func_80B76ED4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_Mt_0x80B76030/func_80B77008.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_Mt_0x80B76030/func_80B77078.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_Mt_0x80B76030/func_80B77354.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_Mt_0x80B76030/EnTruMt_Draw.asm")
