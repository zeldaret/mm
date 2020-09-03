#include "z_en_kbt.h"

#define FLAGS 0x00000009

#define THIS ((EnKbt*)thisx)

void EnKbt_Init(Actor* thisx, GlobalContext* globalCtx);
void EnKbt_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnKbt_Update(Actor* thisx, GlobalContext* globalCtx);
void EnKbt_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Kbt_InitVars = {
    ACTOR_EN_KBT,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_KBT,
    sizeof(EnKbt),
    (ActorFunc)EnKbt_Init,
    (ActorFunc)EnKbt_Destroy,
    (ActorFunc)EnKbt_Update,
    (ActorFunc)EnKbt_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Kbt_0x80B33D30/EnKbt_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kbt_0x80B33D30/EnKbt_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kbt_0x80B33D30/func_80B33E64.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kbt_0x80B33D30/func_80B33E8C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kbt_0x80B33D30/func_80B33EF0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kbt_0x80B33D30/func_80B3403C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kbt_0x80B33D30/func_80B34078.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kbt_0x80B33D30/func_80B3415C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kbt_0x80B33D30/func_80B34314.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kbt_0x80B33D30/func_80B34574.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kbt_0x80B33D30/func_80B34598.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kbt_0x80B33D30/EnKbt_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kbt_0x80B33D30/func_80B349C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kbt_0x80B33D30/func_80B34A00.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kbt_0x80B33D30/EnKbt_Draw.asm")
