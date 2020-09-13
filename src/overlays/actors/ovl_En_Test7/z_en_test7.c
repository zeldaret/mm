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
    ACTORTYPE_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnTest7),
    (ActorFunc)EnTest7_Init,
    (ActorFunc)EnTest7_Destroy,
    (ActorFunc)EnTest7_Update,
    (ActorFunc)EnTest7_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Test7_0x80AF0820/func_80AF0820.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test7_0x80AF0820/func_80AF082C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test7_0x80AF0820/func_80AF0838.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test7_0x80AF0820/func_80AF0984.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test7_0x80AF0820/func_80AF0C30.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test7_0x80AF0820/func_80AF0CDC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test7_0x80AF0820/func_80AF10D8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test7_0x80AF0820/func_80AF118C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test7_0x80AF0820/func_80AF14FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test7_0x80AF0820/func_80AF1730.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test7_0x80AF0820/EnTest7_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test7_0x80AF0820/EnTest7_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test7_0x80AF0820/func_80AF19A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test7_0x80AF0820/func_80AF1A2C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test7_0x80AF0820/func_80AF1B68.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test7_0x80AF0820/func_80AF1CA0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test7_0x80AF0820/func_80AF1E44.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test7_0x80AF0820/func_80AF1F48.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test7_0x80AF0820/func_80AF2030.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test7_0x80AF0820/func_80AF21E8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test7_0x80AF0820/func_80AF2318.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test7_0x80AF0820/func_80AF2350.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test7_0x80AF0820/func_80AF24D8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test7_0x80AF0820/func_80AF2654.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test7_0x80AF0820/func_80AF2808.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test7_0x80AF0820/func_80AF2854.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test7_0x80AF0820/func_80AF2938.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test7_0x80AF0820/func_80AF29C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test7_0x80AF0820/func_80AF2AE8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test7_0x80AF0820/func_80AF2BAC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test7_0x80AF0820/func_80AF2C48.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test7_0x80AF0820/func_80AF2DB4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test7_0x80AF0820/func_80AF2EC8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test7_0x80AF0820/func_80AF2F98.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test7_0x80AF0820/func_80AF30F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test7_0x80AF0820/EnTest7_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test7_0x80AF0820/func_80AF31D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test7_0x80AF0820/EnTest7_Draw.asm")
