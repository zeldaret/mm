#include "z_en_elf.h"

#define FLAGS 0x02000030

#define THIS ((EnElf*)thisx)

void EnElf_Init(Actor* thisx, GlobalContext* globalCtx);
void EnElf_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnElf_Update(Actor* thisx, GlobalContext* globalCtx);
void EnElf_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Elf_InitVars = {
    ACTOR_EN_ELF,
    ACTORTYPE_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnElf),
    (ActorFunc)EnElf_Init,
    (ActorFunc)EnElf_Destroy,
    (ActorFunc)EnElf_Update,
    (ActorFunc)EnElf_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Elf_0x8088C510/func_8088C510.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Elf_0x8088C510/func_8088C51C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Elf_0x8088C510/func_8088C804.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Elf_0x8088C510/func_8088C858.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Elf_0x8088C510/func_8088C920.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Elf_0x8088C510/func_8088C9CC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Elf_0x8088C510/func_8088CBAC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Elf_0x8088C510/func_8088CC48.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Elf_0x8088C510/func_8088CD3C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Elf_0x8088C510/EnElf_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Elf_0x8088C510/EnElf_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Elf_0x8088C510/func_8088D3EC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Elf_0x8088C510/func_8088D470.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Elf_0x8088C510/func_8088D504.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Elf_0x8088C510/func_8088D5A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Elf_0x8088C510/func_8088D660.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Elf_0x8088C510/func_8088D7F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Elf_0x8088C510/func_8088D864.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Elf_0x8088C510/func_8088D8D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Elf_0x8088C510/func_8088D9BC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Elf_0x8088C510/func_8088DB4C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Elf_0x8088C510/func_8088DCA4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Elf_0x8088C510/func_8088DD34.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Elf_0x8088C510/func_8088E018.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Elf_0x8088C510/func_8088E0E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Elf_0x8088C510/func_8088E0F0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Elf_0x8088C510/func_8088E304.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Elf_0x8088C510/func_8088E484.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Elf_0x8088C510/func_8088E5A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Elf_0x8088C510/func_8088E60C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Elf_0x8088C510/func_8088E850.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Elf_0x8088C510/func_8088EF18.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Elf_0x8088C510/func_8088EFA4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Elf_0x8088C510/func_8088F214.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Elf_0x8088C510/func_8088F5F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Elf_0x8088C510/func_8088F9E4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Elf_0x8088C510/func_8088FA38.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Elf_0x8088C510/func_8088FC34.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Elf_0x8088C510/func_8088FD04.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Elf_0x8088C510/func_8088FDCC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Elf_0x8088C510/func_8088FE64.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Elf_0x8088C510/func_8089010C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Elf_0x8088C510/EnElf_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Elf_0x8088C510/func_80890494.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Elf_0x8088C510/EnElf_Draw.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Elf_0x8088C510/func_808908D0.asm")
