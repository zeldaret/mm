#include "z_elf_msg.h"

#define FLAGS 0x00000010

#define THIS ((ElfMsg*)thisx)

void ElfMsg_Init(Actor* thisx, GlobalContext* globalCtx);
void ElfMsg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ElfMsg_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Elf_Msg_InitVars = {
    ACTOR_ELF_MSG,
    ACTORTYPE_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ElfMsg),
    (ActorFunc)ElfMsg_Init,
    (ActorFunc)ElfMsg_Destroy,
    (ActorFunc)ElfMsg_Update,
    (ActorFunc)NULL
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Elf_Msg_0x8092DF90/func_8092DF90.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Elf_Msg_0x8092DF90/func_8092DF9C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Elf_Msg_0x8092DF90/ElfMsg_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Elf_Msg_0x8092DF90/ElfMsg_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Elf_Msg_0x8092DF90/func_8092E1D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Elf_Msg_0x8092DF90/func_8092E1FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Elf_Msg_0x8092DF90/func_8092E284.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Elf_Msg_0x8092DF90/ElfMsg_Update.asm")
