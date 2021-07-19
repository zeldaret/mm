#include "z_elf_msg3.h"

#define FLAGS 0x00000010

#define THIS ((ElfMsg3*)thisx)

void ElfMsg3_Init(Actor* thisx, GlobalContext* globalCtx);
void ElfMsg3_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ElfMsg3_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Elf_Msg3_InitVars = {
    ACTOR_ELF_MSG3,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ElfMsg3),
    (ActorFunc)ElfMsg3_Init,
    (ActorFunc)ElfMsg3_Destroy,
    (ActorFunc)ElfMsg3_Update,
    (ActorFunc)NULL,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg3/func_80A2CD10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg3/func_80A2CD1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg3/ElfMsg3_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg3/ElfMsg3_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg3/func_80A2CF50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg3/func_80A2CF7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg3/ElfMsg3_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Elf_Msg3/D_80A2D1F0.s")
