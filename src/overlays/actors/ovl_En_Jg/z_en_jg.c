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
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_JG,
    sizeof(EnJg),
    (ActorFunc)EnJg_Init,
    (ActorFunc)EnJg_Destroy,
    (ActorFunc)EnJg_Update,
    (ActorFunc)EnJg_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/func_80B73A90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/func_80B73AE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/func_80B73B98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/func_80B73C58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/func_80B73DF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/func_80B73E3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/func_80B73F1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/func_80B7406C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/func_80B7408C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/func_80B74134.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/func_80B741F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/func_80B742F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/func_80B74440.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/func_80B74550.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/func_80B747C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/func_80B74840.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/func_80B749D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/func_80B74AD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/func_80B74B54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/func_80B74BC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/func_80B74E5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/func_80B750A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/func_80B7517C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/func_80B751F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/EnJg_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/EnJg_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/EnJg_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/func_80B75658.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/func_80B75708.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/EnJg_Draw.s")
