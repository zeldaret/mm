#include "z_en_sth.h"

#define FLAGS 0x00000009

#define THIS ((EnSth*)thisx)

void EnSth_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSth_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSth_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Sth_InitVars = {
    ACTOR_EN_STH,
    ACTORTYPE_NPC,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnSth),
    (ActorFunc)EnSth_Init,
    (ActorFunc)EnSth_Destroy,
    (ActorFunc)EnSth_Update,
    (ActorFunc)NULL
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Sth_0x80B66D30/EnSth_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sth_0x80B66D30/EnSth_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sth_0x80B66D30/func_80B6703C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sth_0x80B66D30/func_80B670A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sth_0x80B66D30/func_80B67148.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sth_0x80B66D30/func_80B671A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sth_0x80B66D30/func_80B67208.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sth_0x80B66D30/func_80B672A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sth_0x80B66D30/func_80B67348.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sth_0x80B66D30/func_80B67458.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sth_0x80B66D30/func_80B67540.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sth_0x80B66D30/func_80B677BC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sth_0x80B66D30/func_80B67838.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sth_0x80B66D30/func_80B678A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sth_0x80B66D30/func_80B67958.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sth_0x80B66D30/func_80B67984.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sth_0x80B66D30/func_80B67AB4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sth_0x80B66D30/func_80B67B50.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sth_0x80B66D30/func_80B67C1C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sth_0x80B66D30/func_80B67DA0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sth_0x80B66D30/func_80B67E20.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sth_0x80B66D30/EnSth_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sth_0x80B66D30/func_80B680A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sth_0x80B66D30/func_80B681E8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sth_0x80B66D30/func_80B68310.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Sth_0x80B66D30/func_80B6849C.asm")
