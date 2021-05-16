#include "z_en_st.h"

#define FLAGS 0x01004035

#define THIS ((EnSt*)thisx)

void EnSt_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSt_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSt_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_St_InitVars = {
    ACTOR_EN_ST,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_ST,
    sizeof(EnSt),
    (ActorFunc)EnSt_Init,
    (ActorFunc)EnSt_Destroy,
    (ActorFunc)EnSt_Update,
    (ActorFunc)NULL
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/func_808A5050.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/func_808A52A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/func_808A54B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/func_808A576C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/func_808A5988.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/func_808A5AF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/func_808A5BEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/func_808A5CCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/func_808A5D7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/func_808A5DCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/func_808A5F28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/func_808A6064.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/func_808A60E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/func_808A61F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/func_808A6220.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/func_808A63E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/func_808A6468.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/func_808A650C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/func_808A6580.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/func_808A6A3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/func_808A6A78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/func_808A6C04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/func_808A6D84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/func_808A6E24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/func_808A701C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/EnSt_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/EnSt_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/EnSt_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/func_808A73E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_St/func_808A7478.s")
