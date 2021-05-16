#include "z_en_syateki_wf.h"

#define FLAGS 0x08000030

#define THIS ((EnSyatekiWf*)thisx)

void EnSyatekiWf_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSyatekiWf_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSyatekiWf_Update(Actor* thisx, GlobalContext* globalCtx);
void EnSyatekiWf_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Syateki_Wf_InitVars = {
    ACTOR_EN_SYATEKI_WF,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_WF,
    sizeof(EnSyatekiWf),
    (ActorFunc)EnSyatekiWf_Init,
    (ActorFunc)EnSyatekiWf_Destroy,
    (ActorFunc)EnSyatekiWf_Update,
    (ActorFunc)EnSyatekiWf_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Wf/EnSyatekiWf_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Wf/EnSyatekiWf_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Wf/func_80A200E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Wf/func_80A201CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Wf/func_80A20284.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Wf/func_80A2030C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Wf/func_80A20320.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Wf/func_80A20378.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Wf/func_80A203DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Wf/func_80A20670.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Wf/func_80A206DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Wf/func_80A20710.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Wf/func_80A2075C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Wf/func_80A2079C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Wf/func_80A20800.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Wf/func_80A20858.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Wf/func_80A208F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Wf/EnSyatekiWf_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Wf/func_80A20CF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Wf/func_80A20D10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Wf/EnSyatekiWf_Draw.s")
