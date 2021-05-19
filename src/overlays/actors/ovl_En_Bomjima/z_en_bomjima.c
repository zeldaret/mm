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
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_CS,
    sizeof(EnBomjima),
    (ActorFunc)EnBomjima_Init,
    (ActorFunc)EnBomjima_Destroy,
    (ActorFunc)EnBomjima_Update,
    (ActorFunc)EnBomjima_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjima_0x80BFE170/EnBomjima_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjima_0x80BFE170/EnBomjima_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjima_0x80BFE170/func_80BFE32C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjima_0x80BFE170/func_80BFE494.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjima_0x80BFE170/func_80BFE524.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjima_0x80BFE170/func_80BFE65C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjima_0x80BFE170/func_80BFE67C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjima_0x80BFE170/func_80BFEA94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjima_0x80BFE170/func_80BFEB1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjima_0x80BFE170/func_80BFEB64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjima_0x80BFE170/func_80BFEFF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjima_0x80BFE170/func_80BFF03C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjima_0x80BFE170/func_80BFF120.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjima_0x80BFE170/func_80BFF174.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjima_0x80BFE170/func_80BFF3F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjima_0x80BFE170/func_80BFF430.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjima_0x80BFE170/func_80BFF4F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjima_0x80BFE170/func_80BFF52C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjima_0x80BFE170/func_80BFF6CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjima_0x80BFE170/func_80BFF754.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjima_0x80BFE170/func_80BFF9B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjima_0x80BFE170/func_80BFFB40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjima_0x80BFE170/func_80BFFBC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjima_0x80BFE170/func_80BFFCFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjima_0x80BFE170/func_80BFFD48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjima_0x80BFE170/func_80BFFE48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjima_0x80BFE170/func_80BFFF54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjima_0x80BFE170/func_80C0011C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjima_0x80BFE170/func_80C00168.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjima_0x80BFE170/func_80C00234.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjima_0x80BFE170/func_80C00284.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjima_0x80BFE170/EnBomjima_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjima_0x80BFE170/func_80C007F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bomjima_0x80BFE170/EnBomjima_Draw.asm")
