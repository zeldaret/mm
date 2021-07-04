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
    (ActorFunc)EnJg_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/func_80B73A90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/func_80B73AE4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/func_80B73B98.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/func_80B73C58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/func_80B73DF4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/func_80B73E3C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/func_80B73F1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/func_80B7406C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/func_80B7408C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/func_80B74134.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/func_80B741F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/func_80B742F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/func_80B74440.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/func_80B74550.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/func_80B747C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/func_80B74840.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/func_80B749D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/func_80B74AD8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/func_80B74B54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/func_80B74BC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/func_80B74E5C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/func_80B750A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/func_80B7517C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/func_80B751F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/EnJg_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/EnJg_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/EnJg_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/func_80B75658.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/func_80B75708.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Jg_0x80B73A90/EnJg_Draw.asm")
