#include "z_en_bomjima.h"

#define FLAGS 0x00000019

#define THIS ((EnBomjima*)thisx)

void EnBomjima_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBomjima_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBomjima_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBomjima_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Bomjima_InitVars = {
    ACTOR_EN_BOMJIMA,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_CS,
    sizeof(EnBomjima),
    (ActorFunc)EnBomjima_Init,
    (ActorFunc)EnBomjima_Destroy,
    (ActorFunc)EnBomjima_Update,
    (ActorFunc)EnBomjima_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Bomjima_0x80BFE170/EnBomjima_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bomjima_0x80BFE170/EnBomjima_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bomjima_0x80BFE170/func_80BFE32C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bomjima_0x80BFE170/func_80BFE494.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bomjima_0x80BFE170/func_80BFE524.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bomjima_0x80BFE170/func_80BFE65C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bomjima_0x80BFE170/func_80BFE67C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bomjima_0x80BFE170/func_80BFEA94.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bomjima_0x80BFE170/func_80BFEB1C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bomjima_0x80BFE170/func_80BFEB64.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bomjima_0x80BFE170/func_80BFEFF0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bomjima_0x80BFE170/func_80BFF03C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bomjima_0x80BFE170/func_80BFF120.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bomjima_0x80BFE170/func_80BFF174.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bomjima_0x80BFE170/func_80BFF3F0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bomjima_0x80BFE170/func_80BFF430.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bomjima_0x80BFE170/func_80BFF4F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bomjima_0x80BFE170/func_80BFF52C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bomjima_0x80BFE170/func_80BFF6CC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bomjima_0x80BFE170/func_80BFF754.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bomjima_0x80BFE170/func_80BFF9B0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bomjima_0x80BFE170/func_80BFFB40.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bomjima_0x80BFE170/func_80BFFBC4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bomjima_0x80BFE170/func_80BFFCFC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bomjima_0x80BFE170/func_80BFFD48.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bomjima_0x80BFE170/func_80BFFE48.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bomjima_0x80BFE170/func_80BFFF54.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bomjima_0x80BFE170/func_80C0011C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bomjima_0x80BFE170/func_80C00168.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bomjima_0x80BFE170/func_80C00234.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bomjima_0x80BFE170/func_80C00284.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bomjima_0x80BFE170/EnBomjima_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bomjima_0x80BFE170/func_80C007F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bomjima_0x80BFE170/EnBomjima_Draw.asm")
