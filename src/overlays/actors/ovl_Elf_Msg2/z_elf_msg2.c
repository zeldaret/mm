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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Elf_Msg2_0x8096EC40/func_8096EC40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Elf_Msg2_0x8096EC40/func_8096EC4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Elf_Msg2_0x8096EC40/ElfMsg2_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Elf_Msg2_0x8096EC40/ElfMsg2_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Elf_Msg2_0x8096EC40/func_8096EE50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Elf_Msg2_0x8096EC40/func_8096EE64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Elf_Msg2_0x8096EC40/func_8096EF98.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Elf_Msg2_0x8096EC40/func_8096EFD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Elf_Msg2_0x8096EC40/ElfMsg2_Update.asm")
