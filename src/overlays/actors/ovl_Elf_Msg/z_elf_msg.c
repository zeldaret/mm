#include "z_elf_msg.h"

#define FLAGS 0x00000010

#define THIS ((ElfMsg*)thisx)

void ElfMsg_Init(Actor* thisx, GlobalContext* globalCtx);
void ElfMsg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ElfMsg_Update(Actor* thisx, GlobalContext* globalCtx);

/*
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
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg/func_8092DF90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg/func_8092DF9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg/ElfMsg_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg/ElfMsg_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg/func_8092E1D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg/func_8092E1FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg/func_8092E284.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg/ElfMsg_Update.s")
