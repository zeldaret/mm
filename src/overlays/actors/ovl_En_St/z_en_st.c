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
    (ActorFunc)NULL,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_St_0x808A5050/func_808A5050.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_St_0x808A5050/func_808A52A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_St_0x808A5050/func_808A54B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_St_0x808A5050/func_808A576C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_St_0x808A5050/func_808A5988.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_St_0x808A5050/func_808A5AF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_St_0x808A5050/func_808A5BEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_St_0x808A5050/func_808A5CCC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_St_0x808A5050/func_808A5D7C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_St_0x808A5050/func_808A5DCC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_St_0x808A5050/func_808A5F28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_St_0x808A5050/func_808A6064.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_St_0x808A5050/func_808A60E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_St_0x808A5050/func_808A61F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_St_0x808A5050/func_808A6220.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_St_0x808A5050/func_808A63E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_St_0x808A5050/func_808A6468.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_St_0x808A5050/func_808A650C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_St_0x808A5050/func_808A6580.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_St_0x808A5050/func_808A6A3C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_St_0x808A5050/func_808A6A78.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_St_0x808A5050/func_808A6C04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_St_0x808A5050/func_808A6D84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_St_0x808A5050/func_808A6E24.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_St_0x808A5050/func_808A701C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_St_0x808A5050/EnSt_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_St_0x808A5050/EnSt_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_St_0x808A5050/EnSt_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_St_0x808A5050/func_808A73E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_St_0x808A5050/func_808A7478.asm")
