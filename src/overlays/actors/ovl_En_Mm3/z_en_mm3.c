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
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_MM,
    sizeof(EnMm3),
    (ActorFunc)EnMm3_Init,
    (ActorFunc)EnMm3_Destroy,
    (ActorFunc)EnMm3_Update,
    (ActorFunc)EnMm3_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Mm3_0x80A6F0A0/EnMm3_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mm3_0x80A6F0A0/EnMm3_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mm3_0x80A6F0A0/func_80A6F22C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mm3_0x80A6F0A0/func_80A6F270.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mm3_0x80A6F0A0/func_80A6F2C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mm3_0x80A6F0A0/func_80A6F3B4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mm3_0x80A6F0A0/func_80A6F5E4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mm3_0x80A6F0A0/func_80A6F9C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mm3_0x80A6F0A0/func_80A6F9DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mm3_0x80A6F0A0/func_80A6FBA0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mm3_0x80A6F0A0/func_80A6FBFC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mm3_0x80A6F0A0/func_80A6FE1C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mm3_0x80A6F0A0/func_80A6FE30.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mm3_0x80A6F0A0/func_80A6FED8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mm3_0x80A6F0A0/func_80A6FEEC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mm3_0x80A6F0A0/func_80A6FFAC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mm3_0x80A6F0A0/func_80A70084.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mm3_0x80A6F0A0/EnMm3_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mm3_0x80A6F0A0/func_80A701E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mm3_0x80A6F0A0/func_80A702B0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Mm3_0x80A6F0A0/EnMm3_Draw.asm")
