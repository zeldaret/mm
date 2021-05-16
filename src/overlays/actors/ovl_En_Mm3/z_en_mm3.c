#include "z_en_mm3.h"

#define FLAGS 0x00000019

#define THIS ((EnMm3*)thisx)

void EnMm3_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMm3_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMm3_Update(Actor* thisx, GlobalContext* globalCtx);
void EnMm3_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Mm3_InitVars = {
    ACTOR_EN_MM3,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_MM,
    sizeof(EnMm3),
    (ActorFunc)EnMm3_Init,
    (ActorFunc)EnMm3_Destroy,
    (ActorFunc)EnMm3_Update,
    (ActorFunc)EnMm3_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mm3/EnMm3_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mm3/EnMm3_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mm3/func_80A6F22C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mm3/func_80A6F270.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mm3/func_80A6F2C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mm3/func_80A6F3B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mm3/func_80A6F5E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mm3/func_80A6F9C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mm3/func_80A6F9DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mm3/func_80A6FBA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mm3/func_80A6FBFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mm3/func_80A6FE1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mm3/func_80A6FE30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mm3/func_80A6FED8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mm3/func_80A6FEEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mm3/func_80A6FFAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mm3/func_80A70084.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mm3/EnMm3_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mm3/func_80A701E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mm3/func_80A702B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mm3/EnMm3_Draw.s")
