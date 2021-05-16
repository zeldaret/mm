#include "z_en_ge2.h"

#define FLAGS 0x80000009

#define THIS ((EnGe2*)thisx)

void EnGe2_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGe2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGe2_Update(Actor* thisx, GlobalContext* globalCtx);
void EnGe2_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Ge2_InitVars = {
    ACTOR_EN_GE2,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_GLA,
    sizeof(EnGe2),
    (ActorFunc)EnGe2_Init,
    (ActorFunc)EnGe2_Destroy,
    (ActorFunc)EnGe2_Update,
    (ActorFunc)EnGe2_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/EnGe2_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/EnGe2_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/func_80B8B514.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/func_80B8B5AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/func_80B8B6B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/func_80B8B7A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/func_80B8B848.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/func_80B8B90C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/func_80B8BA40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/func_80B8BB3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/func_80B8BC1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/func_80B8BC78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/func_80B8BCEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/func_80B8BD38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/func_80B8BD90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/func_80B8BE08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/func_80B8BF04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/func_80B8BFC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/func_80B8C048.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/func_80B8C0B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/func_80B8C13C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/func_80B8C45C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/func_80B8C59C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/func_80B8C644.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/func_80B8C9B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/EnGe2_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/func_80B8CC0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/func_80B8CCB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/func_80B8CCFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/EnGe2_Draw.s")
