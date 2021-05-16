#include "z_en_wf.h"

#define FLAGS 0x00000415

#define THIS ((EnWf*)thisx)

void EnWf_Init(Actor* thisx, GlobalContext* globalCtx);
void EnWf_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnWf_Update(Actor* thisx, GlobalContext* globalCtx);
void EnWf_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Wf_InitVars = {
    ACTOR_EN_WF,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_WF,
    sizeof(EnWf),
    (ActorFunc)EnWf_Init,
    (ActorFunc)EnWf_Destroy,
    (ActorFunc)EnWf_Update,
    (ActorFunc)EnWf_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/EnWf_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/EnWf_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/func_809907D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/func_80990854.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/func_809908E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/func_80990948.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/func_80990C6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/func_80990E4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/func_80990EAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/func_80990ED4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/func_80990F0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/func_80990F50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/func_80990FC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/func_80991040.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/func_809910F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/func_80991174.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/func_80991200.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/func_80991280.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/func_80991438.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/func_8099149C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/func_80991738.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/func_8099177C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/func_80991948.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/func_809919F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/func_80991C04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/func_80991C80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/func_80991FD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/func_80992068.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/func_8099223C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/func_809922B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/func_809923B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/func_809923E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/func_8099245C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/func_809924EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/func_809926D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/func_80992784.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/func_8099282C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/func_809928CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/func_80992A74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/func_80992B8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/func_80992D6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/func_80992E0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/func_80992FD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/func_80993018.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/func_80993148.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/func_80993194.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/func_80993350.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/func_809933A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/func_80993524.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/func_8099357C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/func_80993738.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/func_8099386C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/EnWf_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/func_80993E50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/func_80993E94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/EnWf_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wf/func_8099408C.s")
