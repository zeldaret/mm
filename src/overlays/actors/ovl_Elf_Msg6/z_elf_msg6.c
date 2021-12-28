/*
 * File: z_elf_msg6.c
 * Overlay: ovl_Elf_Msg6
 * Description: Tatl Hint (another proximity-activated C-up hint?)
 */

#include "z_elf_msg6.h"

#define FLAGS 0x00000010

#define THIS ((ElfMsg6*)thisx)

void ElfMsg6_Init(Actor* thisx, GlobalContext* globalCtx);
void ElfMsg6_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ElfMsg6_Update(Actor* thisx, GlobalContext* globalCtx);

void func_80BA1CF8(ElfMsg6* this, GlobalContext* globalCtx);
void func_80BA1E30(ElfMsg6* this, GlobalContext* globalCtx);
void func_80BA1F80(ElfMsg6* this, GlobalContext* globalCtx);
void func_80BA2038(ElfMsg6* this, GlobalContext* globalCtx);
void func_80BA2048(ElfMsg6* this, GlobalContext* globalCtx);
void func_80BA215C(ElfMsg6* this, GlobalContext* globalCtx);
void func_80BA21C4(ElfMsg6* this, GlobalContext* globalCtx);

#if 0
const ActorInit Elf_Msg6_InitVars = {
    ACTOR_ELF_MSG6,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ElfMsg6),
    (ActorFunc)ElfMsg6_Init,
    (ActorFunc)ElfMsg6_Destroy,
    (ActorFunc)ElfMsg6_Update,
    (ActorFunc)NULL,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg6/func_80BA15A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg6/func_80BA165C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg6/func_80BA16F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg6/ElfMsg6_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg6/ElfMsg6_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg6/func_80BA1C00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg6/func_80BA1C88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg6/func_80BA1CF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg6/func_80BA1E30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg6/func_80BA1F80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg6/func_80BA2038.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg6/func_80BA2048.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg6/func_80BA215C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg6/func_80BA21C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg6/ElfMsg6_Update.s")
