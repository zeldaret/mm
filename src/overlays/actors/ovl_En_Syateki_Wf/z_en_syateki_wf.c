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
    (ActorFunc)EnSyatekiWf_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Wf_0x80A1FE50/EnSyatekiWf_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Wf_0x80A1FE50/EnSyatekiWf_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Wf_0x80A1FE50/func_80A200E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Wf_0x80A1FE50/func_80A201CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Wf_0x80A1FE50/func_80A20284.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Wf_0x80A1FE50/func_80A2030C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Wf_0x80A1FE50/func_80A20320.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Wf_0x80A1FE50/func_80A20378.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Wf_0x80A1FE50/func_80A203DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Wf_0x80A1FE50/func_80A20670.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Wf_0x80A1FE50/func_80A206DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Wf_0x80A1FE50/func_80A20710.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Wf_0x80A1FE50/func_80A2075C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Wf_0x80A1FE50/func_80A2079C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Wf_0x80A1FE50/func_80A20800.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Wf_0x80A1FE50/func_80A20858.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Wf_0x80A1FE50/func_80A208F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Wf_0x80A1FE50/EnSyatekiWf_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Wf_0x80A1FE50/func_80A20CF4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Wf_0x80A1FE50/func_80A20D10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Syateki_Wf_0x80A1FE50/EnSyatekiWf_Draw.asm")
