#include "z_elf_msg3.h"

#define FLAGS 0x00000010

#define THIS ((ElfMsg3*)thisx)

void ElfMsg3_Init(Actor* thisx, GlobalContext* globalCtx);
void ElfMsg3_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ElfMsg3_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Elf_Msg3_InitVars = {
    ACTOR_ELF_MSG3,
    ACTORTYPE_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ElfMsg3),
    (ActorFunc)ElfMsg3_Init,
    (ActorFunc)ElfMsg3_Destroy,
    (ActorFunc)ElfMsg3_Update,
    (ActorFunc)NULL
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Elf_Msg3_0x80A2CD10/func_80A2CD10.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Elf_Msg3_0x80A2CD10/func_80A2CD1C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Elf_Msg3_0x80A2CD10/ElfMsg3_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Elf_Msg3_0x80A2CD10/ElfMsg3_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Elf_Msg3_0x80A2CD10/func_80A2CF50.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Elf_Msg3_0x80A2CD10/func_80A2CF7C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Elf_Msg3_0x80A2CD10/ElfMsg3_Update.asm")
