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
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_GLA,
    sizeof(EnGe2),
    (ActorFunc)EnGe2_Init,
    (ActorFunc)EnGe2_Destroy,
    (ActorFunc)EnGe2_Update,
    (ActorFunc)EnGe2_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Ge2_0x80B8B2D0/EnGe2_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ge2_0x80B8B2D0/EnGe2_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ge2_0x80B8B2D0/func_80B8B514.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ge2_0x80B8B2D0/func_80B8B5AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ge2_0x80B8B2D0/func_80B8B6B4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ge2_0x80B8B2D0/func_80B8B7A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ge2_0x80B8B2D0/func_80B8B848.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ge2_0x80B8B2D0/func_80B8B90C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ge2_0x80B8B2D0/func_80B8BA40.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ge2_0x80B8B2D0/func_80B8BB3C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ge2_0x80B8B2D0/func_80B8BC1C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ge2_0x80B8B2D0/func_80B8BC78.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ge2_0x80B8B2D0/func_80B8BCEC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ge2_0x80B8B2D0/func_80B8BD38.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ge2_0x80B8B2D0/func_80B8BD90.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ge2_0x80B8B2D0/func_80B8BE08.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ge2_0x80B8B2D0/func_80B8BF04.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ge2_0x80B8B2D0/func_80B8BFC8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ge2_0x80B8B2D0/func_80B8C048.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ge2_0x80B8B2D0/func_80B8C0B0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ge2_0x80B8B2D0/func_80B8C13C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ge2_0x80B8B2D0/func_80B8C45C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ge2_0x80B8B2D0/func_80B8C59C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ge2_0x80B8B2D0/func_80B8C644.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ge2_0x80B8B2D0/func_80B8C9B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ge2_0x80B8B2D0/EnGe2_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ge2_0x80B8B2D0/func_80B8CC0C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ge2_0x80B8B2D0/func_80B8CCB4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ge2_0x80B8B2D0/func_80B8CCFC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ge2_0x80B8B2D0/EnGe2_Draw.asm")
