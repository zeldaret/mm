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
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_PR,
    sizeof(EnPr2),
    (ActorFunc)EnPr2_Init,
    (ActorFunc)EnPr2_Destroy,
    (ActorFunc)EnPr2_Update,
    (ActorFunc)EnPr2_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Pr2_0x80A73FA0/EnPr2_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pr2_0x80A73FA0/EnPr2_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pr2_0x80A73FA0/func_80A7429C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pr2_0x80A73FA0/func_80A7436C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pr2_0x80A73FA0/func_80A74510.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pr2_0x80A73FA0/func_80A745C4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pr2_0x80A73FA0/func_80A745FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pr2_0x80A73FA0/func_80A74888.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pr2_0x80A73FA0/func_80A748E8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pr2_0x80A73FA0/func_80A74DEC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pr2_0x80A73FA0/func_80A74E90.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pr2_0x80A73FA0/func_80A751B4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pr2_0x80A73FA0/func_80A75310.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pr2_0x80A73FA0/func_80A755D8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pr2_0x80A73FA0/EnPr2_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pr2_0x80A73FA0/func_80A758E8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pr2_0x80A73FA0/func_80A75950.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pr2_0x80A73FA0/func_80A759D8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pr2_0x80A73FA0/EnPr2_Draw.asm")
