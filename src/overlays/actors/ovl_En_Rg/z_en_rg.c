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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/func_80BF3920.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/func_80BF3C64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/func_80BF3DA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/func_80BF3DC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/func_80BF3E88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/func_80BF3ED4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/func_80BF3F14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/func_80BF3FF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/func_80BF4024.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/func_80BF409C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/func_80BF40F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/func_80BF416C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/func_80BF4220.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/func_80BF42BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/func_80BF43FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/func_80BF4560.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/func_80BF45B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/func_80BF47AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/func_80BF4934.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/func_80BF4964.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/func_80BF4AB8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/func_80BF4D64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/func_80BF4DA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/func_80BF4EBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/func_80BF4FC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/EnRg_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/EnRg_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/EnRg_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/func_80BF547C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/func_80BF5588.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rg_0x80BF3920/EnRg_Draw.asm")
