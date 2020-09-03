#include "z_en_jg.h"

#define FLAGS 0x00000019

#define THIS ((EnJg*)thisx)

void EnJg_Init(Actor* thisx, GlobalContext* globalCtx);
void EnJg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnJg_Update(Actor* thisx, GlobalContext* globalCtx);
void EnJg_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Jg_InitVars = {
    ACTOR_EN_JG,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_JG,
    sizeof(EnJg),
    (ActorFunc)EnJg_Init,
    (ActorFunc)EnJg_Destroy,
    (ActorFunc)EnJg_Update,
    (ActorFunc)EnJg_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Jg_0x80B73A90/func_80B73A90.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jg_0x80B73A90/func_80B73AE4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jg_0x80B73A90/func_80B73B98.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jg_0x80B73A90/func_80B73C58.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jg_0x80B73A90/func_80B73DF4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jg_0x80B73A90/func_80B73E3C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jg_0x80B73A90/func_80B73F1C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jg_0x80B73A90/func_80B7406C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jg_0x80B73A90/func_80B7408C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jg_0x80B73A90/func_80B74134.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jg_0x80B73A90/func_80B741F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jg_0x80B73A90/func_80B742F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jg_0x80B73A90/func_80B74440.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jg_0x80B73A90/func_80B74550.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jg_0x80B73A90/func_80B747C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jg_0x80B73A90/func_80B74840.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jg_0x80B73A90/func_80B749D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jg_0x80B73A90/func_80B74AD8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jg_0x80B73A90/func_80B74B54.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jg_0x80B73A90/func_80B74BC8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jg_0x80B73A90/func_80B74E5C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jg_0x80B73A90/func_80B750A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jg_0x80B73A90/func_80B7517C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jg_0x80B73A90/func_80B751F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jg_0x80B73A90/EnJg_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jg_0x80B73A90/EnJg_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jg_0x80B73A90/EnJg_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jg_0x80B73A90/func_80B75658.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jg_0x80B73A90/func_80B75708.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Jg_0x80B73A90/EnJg_Draw.asm")
