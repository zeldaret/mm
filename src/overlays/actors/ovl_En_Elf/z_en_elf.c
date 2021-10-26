#include "z_en_elf.h"

#define FLAGS 0x02000030

#define THIS ((EnElf*)thisx)

void EnElf_Init(Actor* thisx, GlobalContext* globalCtx);
void EnElf_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnElf_Update(Actor* thisx, GlobalContext* globalCtx);
void EnElf_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_8088DD34(EnElf* this, GlobalContext* globalCtx);
void func_8088E018(EnElf* this, GlobalContext* globalCtx);
void func_8088E0E0(EnElf* this, GlobalContext* globalCtx);
void func_8088E0F0(EnElf* this, GlobalContext* globalCtx);
void func_8088E484(EnElf* this, GlobalContext* globalCtx);
void func_8088E850(EnElf* this, GlobalContext* globalCtx);

void EnElf_SetupAction(EnElf* this, EnElfActionFunc actionFunc);

#if 0
const ActorInit En_Elf_InitVars = {
    ACTOR_EN_ELF,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnElf),
    (ActorFunc)EnElf_Init,
    (ActorFunc)EnElf_Destroy,
    (ActorFunc)EnElf_Update,
    (ActorFunc)EnElf_Draw,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elf/EnElf_SetupAction.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elf/func_8088C51C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elf/func_8088C804.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elf/func_8088C858.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elf/func_8088C920.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elf/func_8088C9CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elf/func_8088CBAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elf/func_8088CC48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elf/func_8088CD3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elf/EnElf_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elf/EnElf_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elf/func_8088D3EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elf/func_8088D470.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elf/func_8088D504.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elf/func_8088D5A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elf/func_8088D660.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elf/func_8088D7F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elf/func_8088D864.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elf/func_8088D8D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elf/func_8088D9BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elf/func_8088DB4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elf/func_8088DCA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elf/func_8088DD34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elf/func_8088E018.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elf/func_8088E0E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elf/func_8088E0F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elf/func_8088E304.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elf/func_8088E484.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elf/func_8088E5A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elf/func_8088E60C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elf/func_8088E850.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elf/func_8088EF18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elf/func_8088EFA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elf/func_8088F214.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elf/func_8088F5F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elf/func_8088F9E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elf/func_8088FA38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elf/func_8088FC34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elf/func_8088FD04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elf/func_8088FDCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elf/func_8088FE64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elf/func_8089010C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elf/EnElf_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elf/func_80890494.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elf/EnElf_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elf/func_808908D0.s")
