/*
 * File: z_elf_msg.c
 * Overlay: ovl_Elf_Msg
 * Description: Tatl Hint (proximity-activated C-up hint?)
 */

#include "z_elf_msg.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ElfMsg*)thisx)

void ElfMsg_Init(Actor* thisx, GlobalContext* globalCtx);
void ElfMsg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ElfMsg_Update(Actor* thisx, GlobalContext* globalCtx);

void ElfMsg_SetupAction(ElfMsg* this, ElfMsgActionFunc actionFunc);

#if 0
const ActorInit Elf_Msg_InitVars = {
    ACTOR_ELF_MSG,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ElfMsg),
    (ActorFunc)ElfMsg_Init,
    (ActorFunc)ElfMsg_Destroy,
    (ActorFunc)ElfMsg_Update,
    (ActorFunc)NULL,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_8092E470[] = {
    ICHAIN_VEC3F_DIV1000(scale, 1000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 1000, ICHAIN_STOP),
};

#endif

extern InitChainEntry D_8092E470[];

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg/D_8092E480.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg/ElfMsg_SetupAction.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg/func_8092DF9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg/ElfMsg_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg/ElfMsg_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg/func_8092E1D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg/func_8092E1FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg/func_8092E284.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg/ElfMsg_Update.s")
