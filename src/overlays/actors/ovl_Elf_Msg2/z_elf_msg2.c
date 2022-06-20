/*
 * File: z_elf_msg2.c
 * Overlay: ovl_Elf_Msg2
 * Description: Tatl Hint (Z-target-activated C-up hint?)
 */

#include "z_elf_msg2.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ElfMsg2*)thisx)

void ElfMsg2_Init(Actor* thisx, GlobalContext* globalCtx);
void ElfMsg2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ElfMsg2_Update(Actor* thisx, GlobalContext* globalCtx);

void func_8096EFD0(ElfMsg2* this, GlobalContext* globalCtx);

void ElfMsg2_SetupAction(ElfMsg2* this, ElfMsg2ActionFunc actionFunc);

#if 0
const ActorInit Elf_Msg2_InitVars = {
    ACTOR_ELF_MSG2,
    ACTORCAT_BG,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ElfMsg2),
    (ActorFunc)ElfMsg2_Init,
    (ActorFunc)ElfMsg2_Destroy,
    (ActorFunc)ElfMsg2_Update,
    (ActorFunc)NULL,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_8096F0B0[] = {
    ICHAIN_VEC3F_DIV1000(scale, 200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 1000, ICHAIN_STOP),
};

#endif

extern InitChainEntry D_8096F0B0[];

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg2/D_8096F0C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg2/ElfMsg2_SetupAction.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg2/func_8096EC4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg2/ElfMsg2_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg2/ElfMsg2_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg2/func_8096EE50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg2/func_8096EE64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg2/func_8096EF98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg2/func_8096EFD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg2/ElfMsg2_Update.s")
