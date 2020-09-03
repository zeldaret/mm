#include "z_en_hanabi.h"

#define FLAGS 0x00000030

#define THIS ((EnHanabi*)thisx)

void EnHanabi_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHanabi_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHanabi_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Hanabi_InitVars = {
    ACTOR_EN_HANABI,
    ACTORTYPE_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnHanabi),
    (ActorFunc)EnHanabi_Init,
    (ActorFunc)EnHanabi_Destroy,
    (ActorFunc)EnHanabi_Update,
    (ActorFunc)NULL
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Hanabi_0x80B22C00/func_80B22C00.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hanabi_0x80B22C00/func_80B22C2C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hanabi_0x80B22C00/func_80B22C80.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hanabi_0x80B22C00/func_80B22E0C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hanabi_0x80B22C00/func_80B22F34.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hanabi_0x80B22C00/func_80B22FA8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hanabi_0x80B22C00/EnHanabi_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hanabi_0x80B22C00/EnHanabi_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hanabi_0x80B22C00/func_80B234C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hanabi_0x80B22C00/func_80B235CC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hanabi_0x80B22C00/func_80B236C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hanabi_0x80B22C00/func_80B23894.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hanabi_0x80B22C00/func_80B238D4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hanabi_0x80B22C00/func_80B23910.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hanabi_0x80B22C00/func_80B23934.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hanabi_0x80B22C00/EnHanabi_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hanabi_0x80B22C00/func_80B23A38.asm")
