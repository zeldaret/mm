/*
 * File: z_elf_msg4.c
 * Overlay: ovl_Elf_Msg4
 * Description: Tatl Hint (another proximity-activated C-up hint?)
 */

#include "z_elf_msg4.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ElfMsg4*)thisx)

void ElfMsg4_Init(Actor* thisx, GlobalContext* globalCtx);
void ElfMsg4_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ElfMsg4_Update(Actor* thisx, GlobalContext* globalCtx);

void func_80AFD668(ElfMsg4* this, GlobalContext* globalCtx);
void func_80AFD770(ElfMsg4* this, GlobalContext* globalCtx);

#if 0
const ActorInit Elf_Msg4_InitVars = {
    ACTOR_ELF_MSG4,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ElfMsg4),
    (ActorFunc)ElfMsg4_Init,
    (ActorFunc)ElfMsg4_Destroy,
    (ActorFunc)ElfMsg4_Update,
    (ActorFunc)NULL,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80AFD8F0[] = {
    ICHAIN_VEC3F_DIV1000(scale, 1000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 1000, ICHAIN_STOP),
};

#endif

extern InitChainEntry D_80AFD8F0[];

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg4/D_80AFD900.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg4/func_80AFD380.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg4/ElfMsg4_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg4/ElfMsg4_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg4/func_80AFD5B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg4/func_80AFD5E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg4/func_80AFD668.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg4/func_80AFD770.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg4/ElfMsg4_Update.s")
