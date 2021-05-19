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
    (ActorFunc)EnWf_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/EnWf_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/EnWf_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/func_809907D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/func_80990854.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/func_809908E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/func_80990948.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/func_80990C6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/func_80990E4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/func_80990EAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/func_80990ED4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/func_80990F0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/func_80990F50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/func_80990FC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/func_80991040.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/func_809910F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/func_80991174.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/func_80991200.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/func_80991280.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/func_80991438.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/func_8099149C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/func_80991738.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/func_8099177C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/func_80991948.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/func_809919F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/func_80991C04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/func_80991C80.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/func_80991FD8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/func_80992068.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/func_8099223C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/func_809922B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/func_809923B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/func_809923E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/func_8099245C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/func_809924EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/func_809926D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/func_80992784.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/func_8099282C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/func_809928CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/func_80992A74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/func_80992B8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/func_80992D6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/func_80992E0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/func_80992FD4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/func_80993018.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/func_80993148.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/func_80993194.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/func_80993350.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/func_809933A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/func_80993524.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/func_8099357C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/func_80993738.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/func_8099386C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/EnWf_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/func_80993E50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/func_80993E94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/EnWf_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Wf_0x80990310/func_8099408C.asm")
