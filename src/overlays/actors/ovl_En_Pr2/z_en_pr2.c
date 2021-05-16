#include "z_en_pr2.h"

#define FLAGS 0x00000015

#define THIS ((EnPr2*)thisx)

void EnPr2_Init(Actor* thisx, GlobalContext* globalCtx);
void EnPr2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnPr2_Update(Actor* thisx, GlobalContext* globalCtx);
void EnPr2_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Pr2_InitVars = {
    ACTOR_EN_PR2,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_PR,
    sizeof(EnPr2),
    (ActorFunc)EnPr2_Init,
    (ActorFunc)EnPr2_Destroy,
    (ActorFunc)EnPr2_Update,
    (ActorFunc)EnPr2_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr2/EnPr2_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr2/EnPr2_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr2/func_80A7429C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr2/func_80A7436C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr2/func_80A74510.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr2/func_80A745C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr2/func_80A745FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr2/func_80A74888.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr2/func_80A748E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr2/func_80A74DEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr2/func_80A74E90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr2/func_80A751B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr2/func_80A75310.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr2/func_80A755D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr2/EnPr2_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr2/func_80A758E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr2/func_80A75950.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr2/func_80A759D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pr2/EnPr2_Draw.s")
