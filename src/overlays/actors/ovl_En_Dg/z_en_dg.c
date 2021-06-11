#include "z_en_dg.h"

#define FLAGS 0x00800019

#define THIS ((EnDg*)thisx)

void EnDg_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDg_Update(Actor* thisx, GlobalContext* globalCtx);
void EnDg_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Dg_InitVars = {
    ACTOR_EN_DG,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_DOG,
    sizeof(EnDg),
    (ActorFunc)EnDg_Init,
    (ActorFunc)EnDg_Destroy,
    (ActorFunc)EnDg_Update,
    (ActorFunc)EnDg_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_80989140.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_80989204.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098933C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_80989418.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_809895B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_80989674.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_80989864.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_80989974.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_809899C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_80989A08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_80989A48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_80989A9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_80989ADC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_80989BF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_80989D38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_80989E18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_80989FC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098A064.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098A1B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098A234.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098A468.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098A55C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098A618.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098A70C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098A89C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098A938.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098AAAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098AB48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098AC34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098AE58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098AF44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098AF98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098B004.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098B198.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098B28C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098B390.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098B464.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098B560.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098B88C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098BA64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098BB10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098BBEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098BC54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/EnDg_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/EnDg_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/EnDg_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098BFB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/func_8098BFD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dg/EnDg_Draw.s")
