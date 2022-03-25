/*
 * File: z_elf_msg5.c
 * Overlay: ovl_Elf_Msg5
 * Description: Tatl Message (Another proximity-activated dialogue?)
 */

#include "z_elf_msg5.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ElfMsg5*)thisx)

void ElfMsg5_Init(Actor* thisx, GlobalContext* globalCtx);
void ElfMsg5_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ElfMsg5_Update(Actor* thisx, GlobalContext* globalCtx);

void func_80AFDB38(ElfMsg5* this, GlobalContext* globalCtx);

#if 0
const ActorInit Elf_Msg5_InitVars = {
    ACTOR_ELF_MSG5,
    ACTORCAT_BG,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ElfMsg5),
    (ActorFunc)ElfMsg5_Init,
    (ActorFunc)ElfMsg5_Destroy,
    (ActorFunc)ElfMsg5_Update,
    (ActorFunc)NULL,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80AFDBD0[] = {
    ICHAIN_VEC3F_DIV1000(scale, 200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 1000, ICHAIN_STOP),
};

#endif

extern InitChainEntry D_80AFDBD0[];

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg5/D_80AFDBE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg5/func_80AFD990.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg5/ElfMsg5_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg5/ElfMsg5_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg5/func_80AFDB38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg5/ElfMsg5_Update.s")
