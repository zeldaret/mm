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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rat_0x80A56150/EnRat_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rat_0x80A56150/EnRat_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rat_0x80A56150/func_80A563CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rat_0x80A56150/func_80A56444.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rat_0x80A56150/func_80A5665C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rat_0x80A56150/func_80A566E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rat_0x80A56150/func_80A56994.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rat_0x80A56150/func_80A56AFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rat_0x80A56150/func_80A56EB8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rat_0x80A56150/func_80A56F68.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rat_0x80A56150/func_80A57010.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rat_0x80A56150/func_80A57118.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rat_0x80A56150/func_80A57180.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rat_0x80A56150/func_80A5723C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rat_0x80A56150/func_80A57330.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rat_0x80A56150/func_80A57384.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rat_0x80A56150/func_80A57488.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rat_0x80A56150/func_80A574E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rat_0x80A56150/func_80A57570.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rat_0x80A56150/func_80A575F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rat_0x80A56150/func_80A5764C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rat_0x80A56150/func_80A57918.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rat_0x80A56150/func_80A57984.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rat_0x80A56150/func_80A57A08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rat_0x80A56150/func_80A57A9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rat_0x80A56150/EnRat_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rat_0x80A56150/func_80A57F10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rat_0x80A56150/func_80A57F4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rat_0x80A56150/EnRat_Draw.asm")
