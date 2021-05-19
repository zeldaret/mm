#include "z_elf_msg6.h"

#define FLAGS 0x00000010

#define THIS ((ElfMsg6*)thisx)

void ElfMsg6_Init(Actor* thisx, GlobalContext* globalCtx);
void ElfMsg6_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ElfMsg6_Update(Actor* thisx, GlobalContext* globalCtx);

/*
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
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Elf_Msg6_0x80BA15A0/func_80BA15A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Elf_Msg6_0x80BA15A0/func_80BA165C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Elf_Msg6_0x80BA15A0/func_80BA16F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Elf_Msg6_0x80BA15A0/ElfMsg6_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Elf_Msg6_0x80BA15A0/ElfMsg6_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Elf_Msg6_0x80BA15A0/func_80BA1C00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Elf_Msg6_0x80BA15A0/func_80BA1C88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Elf_Msg6_0x80BA15A0/func_80BA1CF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Elf_Msg6_0x80BA15A0/func_80BA1E30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Elf_Msg6_0x80BA15A0/func_80BA1F80.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Elf_Msg6_0x80BA15A0/func_80BA2038.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Elf_Msg6_0x80BA15A0/func_80BA2048.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Elf_Msg6_0x80BA15A0/func_80BA215C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Elf_Msg6_0x80BA15A0/func_80BA21C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Elf_Msg6_0x80BA15A0/ElfMsg6_Update.asm")
