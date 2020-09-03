#include "z_elf_msg6.h"

#define FLAGS 0x00000010

#define THIS ((ElfMsg6*)thisx)

void ElfMsg6_Init(Actor* thisx, GlobalContext* globalCtx);
void ElfMsg6_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ElfMsg6_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Elf_Msg6_InitVars = {
    ACTOR_ELF_MSG6,
    ACTORTYPE_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ElfMsg6),
    (ActorFunc)ElfMsg6_Init,
    (ActorFunc)ElfMsg6_Destroy,
    (ActorFunc)ElfMsg6_Update,
    (ActorFunc)NULL
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Elf_Msg6_0x80BA15A0/func_80BA15A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Elf_Msg6_0x80BA15A0/func_80BA165C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Elf_Msg6_0x80BA15A0/func_80BA16F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Elf_Msg6_0x80BA15A0/ElfMsg6_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Elf_Msg6_0x80BA15A0/ElfMsg6_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Elf_Msg6_0x80BA15A0/func_80BA1C00.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Elf_Msg6_0x80BA15A0/func_80BA1C88.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Elf_Msg6_0x80BA15A0/func_80BA1CF8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Elf_Msg6_0x80BA15A0/func_80BA1E30.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Elf_Msg6_0x80BA15A0/func_80BA1F80.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Elf_Msg6_0x80BA15A0/func_80BA2038.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Elf_Msg6_0x80BA15A0/func_80BA2048.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Elf_Msg6_0x80BA15A0/func_80BA215C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Elf_Msg6_0x80BA15A0/func_80BA21C4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Elf_Msg6_0x80BA15A0/ElfMsg6_Update.asm")
