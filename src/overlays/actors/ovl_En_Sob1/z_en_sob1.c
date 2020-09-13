#include "z_en_sob1.h"

#define FLAGS 0x00000019

#define THIS ((EnSob1*)thisx)

void EnSob1_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSob1_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSob1_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Sob1_InitVars = {
    ACTOR_EN_OSSAN,
    ACTORTYPE_NPC,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnSob1),
    (ActorFunc)EnSob1_Init,
    (ActorFunc)EnSob1_Destroy,
    (ActorFunc)EnSob1_Update,
    (ActorFunc)NULL
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0C810.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0C8AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0C8B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0C938.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0CA38.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0CC88.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0CCEC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0CD48.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0CE10.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/EnSob1_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/EnSob1_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0D034.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0D0B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0D188.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0D1F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0D258.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0D2B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0D320.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0D388.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0D3C4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0D414.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0D4A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0D628.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0D74C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0D77C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0D850.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0D904.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0DA5C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0DAAC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0DB78.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0DCC4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0DD40.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0DE64.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0DFD0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0E0C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0E1B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0E258.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0E330.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0E420.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0E4DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0E518.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0E554.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0E884.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0E96C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0E9E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0EA84.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0EAF8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0EBC0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0EC98.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0ED7C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0EDA0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0EE3C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0EEC8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0EF48.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0F014.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0F1C4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0F284.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0F2C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0F2FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0F39C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0F3D4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0F470.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0F554.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0F638.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0F6B0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/EnSob1_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0FADC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0FD4C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A0FEE8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A10290.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A102C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A10308.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A10344.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A10368.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A104E4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sob1_0x80A0C810/func_80A10608.asm")
