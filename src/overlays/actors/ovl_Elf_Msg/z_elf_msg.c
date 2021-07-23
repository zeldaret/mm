#include "z_elf_msg.h"

#define FLAGS 0x00000010

#define THIS ((ElfMsg*)thisx)

void ElfMsg_Init(Actor* thisx, GlobalContext* globalCtx);
void ElfMsg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ElfMsg_Update(Actor* thisx, GlobalContext* globalCtx);

#if 0
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


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_8092E470[] = {
    ICHAIN_VEC3F_DIV1000(scale, 1000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 1000, ICHAIN_STOP),
};


extern InitChainEntry D_8092E470[];
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Elf_Msg_0x8092DF90/func_8092DF90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Elf_Msg_0x8092DF90/func_8092DF9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Elf_Msg_0x8092DF90/ElfMsg_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Elf_Msg_0x8092DF90/ElfMsg_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Elf_Msg_0x8092DF90/func_8092E1D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Elf_Msg_0x8092DF90/func_8092E1FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Elf_Msg_0x8092DF90/func_8092E284.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Elf_Msg_0x8092DF90/ElfMsg_Update.asm")
