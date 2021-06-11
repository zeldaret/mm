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

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjima/EnBomjima_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjima/EnBomjima_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjima/func_80BFE32C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjima/func_80BFE494.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjima/func_80BFE524.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjima/func_80BFE65C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjima/func_80BFE67C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjima/func_80BFEA94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjima/func_80BFEB1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjima/func_80BFEB64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjima/func_80BFEFF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjima/func_80BFF03C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjima/func_80BFF120.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjima/func_80BFF174.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjima/func_80BFF3F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjima/func_80BFF430.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjima/func_80BFF4F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjima/func_80BFF52C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjima/func_80BFF6CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjima/func_80BFF754.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjima/func_80BFF9B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjima/func_80BFFB40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjima/func_80BFFBC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjima/func_80BFFCFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjima/func_80BFFD48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjima/func_80BFFE48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjima/func_80BFFF54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjima/func_80C0011C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjima/func_80C00168.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjima/func_80C00234.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjima/func_80C00284.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjima/EnBomjima_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjima/func_80C007F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjima/EnBomjima_Draw.s")
