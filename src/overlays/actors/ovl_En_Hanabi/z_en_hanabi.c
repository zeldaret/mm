/*
 * File: z_en_hanabi.c
 * Overlay: ovl_En_Hanabi
 * Description: Fireworks
 */

#include "z_en_hanabi.h"

#define FLAGS 0x00000030

#define THIS ((EnHanabi*)thisx)

void EnHanabi_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHanabi_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHanabi_Update(Actor* thisx, GlobalContext* globalCtx);

void func_80B23894(EnHanabi* this, GlobalContext* globalCtx);
void func_80B238D4(EnHanabi* this, GlobalContext* globalCtx);
void func_80B23910(EnHanabi* this, GlobalContext* globalCtx);
void func_80B23934(EnHanabi* this, GlobalContext* globalCtx);

#if 0
const ActorInit En_Hanabi_InitVars = {
    ACTOR_EN_HANABI,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnHanabi),
    (ActorFunc)EnHanabi_Init,
    (ActorFunc)EnHanabi_Destroy,
    (ActorFunc)EnHanabi_Update,
    (ActorFunc)NULL,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hanabi/func_80B22C00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hanabi/func_80B22C2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hanabi/func_80B22C80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hanabi/func_80B22E0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hanabi/func_80B22F34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hanabi/func_80B22FA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hanabi/EnHanabi_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hanabi/EnHanabi_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hanabi/func_80B234C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hanabi/func_80B235CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hanabi/func_80B236C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hanabi/func_80B23894.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hanabi/func_80B238D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hanabi/func_80B23910.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hanabi/func_80B23934.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hanabi/EnHanabi_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hanabi/func_80B23A38.s")
