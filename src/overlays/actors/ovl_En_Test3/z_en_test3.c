/*
 * File: z_en_test3.c
 * Overlay: ovl_En_Test3
 * Description: Kafei
 */

#include "z_en_test3.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20 | ACTOR_FLAG_4000000)

#define THIS ((EnTest3*)thisx)

void EnTest3_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTest3_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTest3_Update(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Test3_InitVars = {
    ACTOR_EN_TEST3,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_TEST3,
    sizeof(EnTest3),
    (ActorFunc)EnTest3_Init,
    (ActorFunc)EnTest3_Destroy,
    (ActorFunc)EnTest3_Update,
    (ActorFunc)NULL,
};

#endif

extern UNK_TYPE D_0600EDD0;
extern UNK_TYPE D_0600F7EC;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test3/func_80A3E7E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test3/func_80A3E80C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test3/func_80A3E870.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test3/func_80A3E884.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test3/func_80A3E898.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test3/func_80A3E960.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test3/func_80A3E97C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test3/func_80A3E9DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test3/func_80A3EA30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test3/func_80A3EAC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test3/func_80A3EAF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test3/func_80A3EB8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test3/func_80A3EBFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test3/func_80A3EC30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test3/func_80A3EC44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test3/func_80A3ECEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test3/func_80A3ED24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test3/EnTest3_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test3/EnTest3_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test3/func_80A3F080.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test3/func_80A3F09C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test3/func_80A3F0B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test3/func_80A3F114.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test3/func_80A3F15C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test3/func_80A3F2BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test3/func_80A3F384.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test3/func_80A3F4A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test3/func_80A3F534.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test3/func_80A3F5A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test3/func_80A3F62C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test3/func_80A3F73C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test3/func_80A3F8D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test3/func_80A3F9A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test3/func_80A3F9E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test3/func_80A3FA58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test3/func_80A3FBCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test3/func_80A3FBE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test3/func_80A3FDE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test3/func_80A3FE20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test3/func_80A3FF10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test3/func_80A3FFD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test3/func_80A40098.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test3/func_80A40230.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test3/func_80A40678.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test3/func_80A40824.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test3/func_80A4084C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test3/func_80A40908.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test3/func_80A409D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test3/func_80A40A6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test3/EnTest3_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test3/func_80A40CF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test3/func_80A40F34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test3/func_80A4129C.s")
