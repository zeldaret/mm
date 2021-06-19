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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_80989140.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_80989204.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098933C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_80989418.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_809895B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_80989674.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_80989864.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_80989974.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_809899C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_80989A08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_80989A48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_80989A9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_80989ADC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_80989BF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_80989D38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_80989E18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_80989FC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098A064.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098A1B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098A234.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098A468.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098A55C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098A618.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098A70C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098A89C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098A938.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098AAAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098AB48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098AC34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098AE58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098AF44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098AF98.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098B004.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098B198.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098B28C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098B390.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098B464.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098B560.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098B88C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098BA64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098BB10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098BBEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098BC54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/EnDg_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/EnDg_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/EnDg_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098BFB8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/func_8098BFD4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dg_0x80989140/EnDg_Draw.asm")
