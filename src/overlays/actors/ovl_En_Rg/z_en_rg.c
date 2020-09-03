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
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_OF1D_MAP,
    sizeof(EnRg),
    (ActorFunc)EnRg_Init,
    (ActorFunc)EnRg_Destroy,
    (ActorFunc)EnRg_Update,
    (ActorFunc)EnRg_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Rg_0x80BF3920/func_80BF3920.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rg_0x80BF3920/func_80BF3C64.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rg_0x80BF3920/func_80BF3DA0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rg_0x80BF3920/func_80BF3DC4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rg_0x80BF3920/func_80BF3E88.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rg_0x80BF3920/func_80BF3ED4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rg_0x80BF3920/func_80BF3F14.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rg_0x80BF3920/func_80BF3FF8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rg_0x80BF3920/func_80BF4024.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rg_0x80BF3920/func_80BF409C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rg_0x80BF3920/func_80BF40F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rg_0x80BF3920/func_80BF416C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rg_0x80BF3920/func_80BF4220.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rg_0x80BF3920/func_80BF42BC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rg_0x80BF3920/func_80BF43FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rg_0x80BF3920/func_80BF4560.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rg_0x80BF3920/func_80BF45B4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rg_0x80BF3920/func_80BF47AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rg_0x80BF3920/func_80BF4934.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rg_0x80BF3920/func_80BF4964.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rg_0x80BF3920/func_80BF4AB8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rg_0x80BF3920/func_80BF4D64.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rg_0x80BF3920/func_80BF4DA8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rg_0x80BF3920/func_80BF4EBC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rg_0x80BF3920/func_80BF4FC4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rg_0x80BF3920/EnRg_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rg_0x80BF3920/EnRg_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rg_0x80BF3920/EnRg_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rg_0x80BF3920/func_80BF547C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rg_0x80BF3920/func_80BF5588.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rg_0x80BF3920/EnRg_Draw.asm")
