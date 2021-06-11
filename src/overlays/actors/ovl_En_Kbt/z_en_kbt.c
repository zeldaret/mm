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
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_KBT,
    sizeof(EnKbt),
    (ActorFunc)EnKbt_Init,
    (ActorFunc)EnKbt_Destroy,
    (ActorFunc)EnKbt_Update,
    (ActorFunc)EnKbt_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kbt/EnKbt_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kbt/EnKbt_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kbt/func_80B33E64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kbt/func_80B33E8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kbt/func_80B33EF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kbt/func_80B3403C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kbt/func_80B34078.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kbt/func_80B3415C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kbt/func_80B34314.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kbt/func_80B34574.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kbt/func_80B34598.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kbt/EnKbt_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kbt/func_80B349C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kbt/func_80B34A00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kbt/EnKbt_Draw.s")
