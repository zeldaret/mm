#include "z_elf_msg2.h"

#define FLAGS 0x00000010

#define THIS ((ElfMsg2*)thisx)

void ElfMsg2_Init(Actor* thisx, GlobalContext* globalCtx);
void ElfMsg2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ElfMsg2_Update(Actor* thisx, GlobalContext* globalCtx);

/*
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
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg2/func_8096EC40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg2/func_8096EC4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg2/ElfMsg2_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg2/ElfMsg2_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg2/func_8096EE50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg2/func_8096EE64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg2/func_8096EF98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg2/func_8096EFD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg2/ElfMsg2_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg2/D_8096F0C0.s")
