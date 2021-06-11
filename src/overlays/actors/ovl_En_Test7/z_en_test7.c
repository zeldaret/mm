#include "z_en_test7.h"

#define FLAGS 0x02300030

#define THIS ((EnTest7*)thisx)

void EnTest7_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTest7_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTest7_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTest7_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Test7_InitVars = {
    ACTOR_EN_TEST7,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnTest7),
    (ActorFunc)EnTest7_Init,
    (ActorFunc)EnTest7_Destroy,
    (ActorFunc)EnTest7_Update,
    (ActorFunc)EnTest7_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test7/func_80AF0820.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test7/func_80AF082C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test7/func_80AF0838.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test7/func_80AF0984.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test7/func_80AF0C30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test7/func_80AF0CDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test7/func_80AF10D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test7/func_80AF118C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test7/func_80AF14FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test7/func_80AF1730.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test7/EnTest7_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test7/EnTest7_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test7/func_80AF19A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test7/func_80AF1A2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test7/func_80AF1B68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test7/func_80AF1CA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test7/func_80AF1E44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test7/func_80AF1F48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test7/func_80AF2030.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test7/func_80AF21E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test7/func_80AF2318.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test7/func_80AF2350.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test7/func_80AF24D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test7/func_80AF2654.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test7/func_80AF2808.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test7/func_80AF2854.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test7/func_80AF2938.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test7/func_80AF29C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test7/func_80AF2AE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test7/func_80AF2BAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test7/func_80AF2C48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test7/func_80AF2DB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test7/func_80AF2EC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test7/func_80AF2F98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test7/func_80AF30F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test7/EnTest7_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test7/func_80AF31D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test7/EnTest7_Draw.s")
