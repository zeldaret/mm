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
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_RAT,
    sizeof(EnRat),
    (ActorFunc)EnRat_Init,
    (ActorFunc)EnRat_Destroy,
    (ActorFunc)EnRat_Update,
    (ActorFunc)EnRat_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Rat_0x80A56150/EnRat_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rat_0x80A56150/EnRat_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rat_0x80A56150/func_80A563CC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rat_0x80A56150/func_80A56444.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rat_0x80A56150/func_80A5665C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rat_0x80A56150/func_80A566E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rat_0x80A56150/func_80A56994.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rat_0x80A56150/func_80A56AFC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rat_0x80A56150/func_80A56EB8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rat_0x80A56150/func_80A56F68.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rat_0x80A56150/func_80A57010.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rat_0x80A56150/func_80A57118.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rat_0x80A56150/func_80A57180.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rat_0x80A56150/func_80A5723C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rat_0x80A56150/func_80A57330.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rat_0x80A56150/func_80A57384.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rat_0x80A56150/func_80A57488.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rat_0x80A56150/func_80A574E8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rat_0x80A56150/func_80A57570.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rat_0x80A56150/func_80A575F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rat_0x80A56150/func_80A5764C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rat_0x80A56150/func_80A57918.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rat_0x80A56150/func_80A57984.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rat_0x80A56150/func_80A57A08.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rat_0x80A56150/func_80A57A9C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rat_0x80A56150/EnRat_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rat_0x80A56150/func_80A57F10.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rat_0x80A56150/func_80A57F4C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rat_0x80A56150/EnRat_Draw.asm")
