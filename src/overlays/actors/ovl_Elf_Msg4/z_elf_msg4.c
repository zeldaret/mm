#include "z_elf_msg4.h"

#define FLAGS 0x00000010

#define THIS ((ElfMsg4*)thisx)

void ElfMsg4_Init(Actor* thisx, GlobalContext* globalCtx);
void ElfMsg4_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ElfMsg4_Update(Actor* thisx, GlobalContext* globalCtx);

#if 0

const ActorInit Elf_Msg4_InitVars = {
    ACTOR_ELF_MSG4,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ElfMsg4),
    (ActorFunc)ElfMsg4_Init,
    (ActorFunc)ElfMsg4_Destroy,
    (ActorFunc)ElfMsg4_Update,
    (ActorFunc)NULL,
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80AFD8F0[] = {
    ICHAIN_VEC3F_DIV1000(scale, 1000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 1000, ICHAIN_STOP),
};

#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Elf_Msg4_0x80AFD380/func_80AFD380.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Elf_Msg4_0x80AFD380/ElfMsg4_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Elf_Msg4_0x80AFD380/ElfMsg4_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Elf_Msg4_0x80AFD380/func_80AFD5B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Elf_Msg4_0x80AFD380/func_80AFD5E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Elf_Msg4_0x80AFD380/func_80AFD668.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Elf_Msg4_0x80AFD380/func_80AFD770.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Elf_Msg4_0x80AFD380/ElfMsg4_Update.asm")
