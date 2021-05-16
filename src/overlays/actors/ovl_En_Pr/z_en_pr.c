#include "z_en_pr.h"

#define FLAGS 0x00000015

#define THIS ((EnPr*)thisx)

void EnPr_Init(Actor* thisx, GlobalContext* globalCtx);
void EnPr_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnPr_Update(Actor* thisx, GlobalContext* globalCtx);
void EnPr_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Pr_InitVars = {
    ACTOR_EN_PR,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_PR,
    sizeof(EnPr),
    (ActorFunc)EnPr_Init,
    (ActorFunc)EnPr_Destroy,
    (ActorFunc)EnPr_Update,
    (ActorFunc)EnPr_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr/EnPr_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr/EnPr_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr/func_80A3242C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr/func_80A324E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr/func_80A325E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr/func_80A326F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr/func_80A32740.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr/func_80A32854.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr/func_80A3289C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr/func_80A3295C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr/func_80A32984.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr/func_80A32A40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr/func_80A32AF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr/func_80A32B20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr/func_80A32CDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr/func_80A32D28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr/func_80A32E60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr/func_80A32EA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr/func_80A32F48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr/func_80A33098.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr/EnPr_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr/func_80A3357C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr/func_80A335B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr/EnPr_Draw.s")
