#include "z_en_test3.h"

#define FLAGS 0x04000030

#define THIS ((EnTest3*)thisx)

void EnTest3_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTest3_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTest3_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Test3_InitVars = {
    ACTOR_EN_TEST3,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_TEST3,
    sizeof(EnTest3),
    (ActorFunc)EnTest3_Init,
    (ActorFunc)EnTest3_Destroy,
    (ActorFunc)EnTest3_Update,
    (ActorFunc)NULL
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Test3_0x80A3E7E0/func_80A3E7E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test3_0x80A3E7E0/func_80A3E80C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test3_0x80A3E7E0/func_80A3E870.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test3_0x80A3E7E0/func_80A3E884.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test3_0x80A3E7E0/func_80A3E898.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test3_0x80A3E7E0/func_80A3E960.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test3_0x80A3E7E0/func_80A3E97C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test3_0x80A3E7E0/func_80A3E9DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test3_0x80A3E7E0/func_80A3EA30.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test3_0x80A3E7E0/func_80A3EAC4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test3_0x80A3E7E0/func_80A3EAF8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test3_0x80A3E7E0/func_80A3EB8C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test3_0x80A3E7E0/func_80A3EBFC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test3_0x80A3E7E0/func_80A3EC30.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test3_0x80A3E7E0/func_80A3EC44.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test3_0x80A3E7E0/func_80A3ECEC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test3_0x80A3E7E0/func_80A3ED24.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test3_0x80A3E7E0/EnTest3_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test3_0x80A3E7E0/EnTest3_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test3_0x80A3E7E0/func_80A3F080.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test3_0x80A3E7E0/func_80A3F09C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test3_0x80A3E7E0/func_80A3F0B0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test3_0x80A3E7E0/func_80A3F114.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test3_0x80A3E7E0/func_80A3F15C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test3_0x80A3E7E0/func_80A3F2BC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test3_0x80A3E7E0/func_80A3F384.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test3_0x80A3E7E0/func_80A3F4A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test3_0x80A3E7E0/func_80A3F534.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test3_0x80A3E7E0/func_80A3F5A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test3_0x80A3E7E0/func_80A3F62C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test3_0x80A3E7E0/func_80A3F73C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test3_0x80A3E7E0/func_80A3F8D4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test3_0x80A3E7E0/func_80A3F9A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test3_0x80A3E7E0/func_80A3F9E4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test3_0x80A3E7E0/func_80A3FA58.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test3_0x80A3E7E0/func_80A3FBCC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test3_0x80A3E7E0/func_80A3FBE8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test3_0x80A3E7E0/func_80A3FDE4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test3_0x80A3E7E0/func_80A3FE20.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test3_0x80A3E7E0/func_80A3FF10.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test3_0x80A3E7E0/func_80A3FFD0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test3_0x80A3E7E0/func_80A40098.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test3_0x80A3E7E0/func_80A40230.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test3_0x80A3E7E0/func_80A40678.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test3_0x80A3E7E0/func_80A40824.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test3_0x80A3E7E0/func_80A4084C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test3_0x80A3E7E0/func_80A40908.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test3_0x80A3E7E0/func_80A409D4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test3_0x80A3E7E0/func_80A40A6C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test3_0x80A3E7E0/EnTest3_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test3_0x80A3E7E0/func_80A40CF0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test3_0x80A3E7E0/func_80A40F34.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Test3_0x80A3E7E0/func_80A4129C.asm")
