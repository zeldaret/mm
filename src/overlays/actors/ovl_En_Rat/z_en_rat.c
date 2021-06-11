#include "z_en_rat.h"

#define FLAGS 0x00000205

#define THIS ((EnRat*)thisx)

void EnRat_Init(Actor* thisx, GlobalContext* globalCtx);
void EnRat_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnRat_Update(Actor* thisx, GlobalContext* globalCtx);
void EnRat_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Rat_InitVars = {
    ACTOR_EN_RAT,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_RAT,
    sizeof(EnRat),
    (ActorFunc)EnRat_Init,
    (ActorFunc)EnRat_Destroy,
    (ActorFunc)EnRat_Update,
    (ActorFunc)EnRat_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/EnRat_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/EnRat_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A563CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A56444.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A5665C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A566E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A56994.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A56AFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A56EB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A56F68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A57010.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A57118.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A57180.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A5723C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A57330.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A57384.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A57488.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A574E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A57570.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A575F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A5764C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A57918.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A57984.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A57A08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A57A9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/EnRat_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A57F10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A57F4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/EnRat_Draw.s")
