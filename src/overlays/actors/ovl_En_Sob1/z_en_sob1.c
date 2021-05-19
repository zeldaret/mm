#include "z_en_sob1.h"

#define FLAGS 0x00000019

#define THIS ((EnSob1*)thisx)

void EnSob1_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSob1_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSob1_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Sob1_InitVars = {
    ACTOR_EN_OSSAN,
    ACTORCAT_NPC,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnSob1),
    (ActorFunc)EnSob1_Init,
    (ActorFunc)EnSob1_Destroy,
    (ActorFunc)EnSob1_Update,
    (ActorFunc)NULL,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0C810.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0C8AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0C8B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0C938.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0CA38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0CC88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0CCEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0CD48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0CE10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/EnSob1_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/EnSob1_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0D034.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0D0B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0D188.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0D1F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0D258.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0D2B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0D320.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0D388.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0D3C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0D414.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0D4A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0D628.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0D74C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0D77C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0D850.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0D904.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0DA5C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0DAAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0DB78.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0DCC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0DD40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0DE64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0DFD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0E0C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0E1B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0E258.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0E330.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0E420.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0E4DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0E518.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0E554.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0E884.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0E96C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0E9E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0EA84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0EAF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0EBC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0EC98.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0ED7C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0EDA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0EE3C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0EEC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0EF48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0F014.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0F1C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0F284.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0F2C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0F2FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0F39C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0F3D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0F470.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0F554.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0F638.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0F6B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/EnSob1_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0FADC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0FD4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A0FEE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A10290.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A102C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A10308.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A10344.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A10368.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A104E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sob1_0x80A0C810/func_80A10608.asm")
