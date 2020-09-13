#include "z_en_st.h"

#define FLAGS 0x01004035

#define THIS ((EnSt*)thisx)

void EnSt_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSt_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSt_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_St_InitVars = {
    ACTOR_EN_ST,
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_ST,
    sizeof(EnSt),
    (ActorFunc)EnSt_Init,
    (ActorFunc)EnSt_Destroy,
    (ActorFunc)EnSt_Update,
    (ActorFunc)NULL
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_St_0x808A5050/func_808A5050.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_St_0x808A5050/func_808A52A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_St_0x808A5050/func_808A54B0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_St_0x808A5050/func_808A576C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_St_0x808A5050/func_808A5988.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_St_0x808A5050/func_808A5AF8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_St_0x808A5050/func_808A5BEC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_St_0x808A5050/func_808A5CCC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_St_0x808A5050/func_808A5D7C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_St_0x808A5050/func_808A5DCC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_St_0x808A5050/func_808A5F28.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_St_0x808A5050/func_808A6064.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_St_0x808A5050/func_808A60E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_St_0x808A5050/func_808A61F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_St_0x808A5050/func_808A6220.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_St_0x808A5050/func_808A63E8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_St_0x808A5050/func_808A6468.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_St_0x808A5050/func_808A650C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_St_0x808A5050/func_808A6580.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_St_0x808A5050/func_808A6A3C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_St_0x808A5050/func_808A6A78.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_St_0x808A5050/func_808A6C04.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_St_0x808A5050/func_808A6D84.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_St_0x808A5050/func_808A6E24.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_St_0x808A5050/func_808A701C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_St_0x808A5050/EnSt_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_St_0x808A5050/EnSt_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_St_0x808A5050/EnSt_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_St_0x808A5050/func_808A73E8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_St_0x808A5050/func_808A7478.asm")
