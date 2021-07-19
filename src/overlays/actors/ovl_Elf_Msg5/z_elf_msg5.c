#include "z_elf_msg5.h"

#define FLAGS 0x00000010

#define THIS ((ElfMsg5*)thisx)

void ElfMsg5_Init(Actor* thisx, GlobalContext* globalCtx);
void ElfMsg5_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ElfMsg5_Update(Actor* thisx, GlobalContext* globalCtx);

/*
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
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg5/func_80AFD990.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg5/ElfMsg5_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg5/ElfMsg5_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg5/func_80AFDB38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg5/ElfMsg5_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg5/D_80AFDBE0.s")
