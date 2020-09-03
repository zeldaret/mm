#include "z_en_zl4.h"

#define FLAGS 0x00000030

#define THIS ((EnZl4*)thisx)

void EnZl4_Init(Actor* thisx, GlobalContext* globalCtx);
void EnZl4_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnZl4_Update(Actor* thisx, GlobalContext* globalCtx);
void EnZl4_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Zl4_InitVars = {
    ACTOR_EN_ZL4,
    ACTORTYPE_ITEMACTION,
    FLAGS,
    OBJECT_STK,
    sizeof(EnZl4),
    (ActorFunc)EnZl4_Init,
    (ActorFunc)EnZl4_Destroy,
    (ActorFunc)EnZl4_Update,
    (ActorFunc)EnZl4_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Zl4_0x809A1BB0/func_809A1BB0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zl4_0x809A1BB0/EnZl4_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zl4_0x809A1BB0/EnZl4_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zl4_0x809A1BB0/func_809A1D0C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zl4_0x809A1BB0/EnZl4_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zl4_0x809A1BB0/func_809A1D60.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zl4_0x809A1BB0/func_809A1DA4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zl4_0x809A1BB0/func_809A1DBC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zl4_0x809A1BB0/func_809A1DD0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zl4_0x809A1BB0/func_809A1E28.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zl4_0x809A1BB0/EnZl4_Draw.asm")
