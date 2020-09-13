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
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_DOG,
    sizeof(EnDg),
    (ActorFunc)EnDg_Init,
    (ActorFunc)EnDg_Destroy,
    (ActorFunc)EnDg_Update,
    (ActorFunc)EnDg_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Dg_0x80989140/func_80989140.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dg_0x80989140/func_80989204.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dg_0x80989140/func_8098933C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dg_0x80989140/func_80989418.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dg_0x80989140/func_809895B4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dg_0x80989140/func_80989674.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dg_0x80989140/func_80989864.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dg_0x80989140/func_80989974.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dg_0x80989140/func_809899C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dg_0x80989140/func_80989A08.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dg_0x80989140/func_80989A48.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dg_0x80989140/func_80989A9C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dg_0x80989140/func_80989ADC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dg_0x80989140/func_80989BF8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dg_0x80989140/func_80989D38.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dg_0x80989140/func_80989E18.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dg_0x80989140/func_80989FC8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dg_0x80989140/func_8098A064.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dg_0x80989140/func_8098A1B4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dg_0x80989140/func_8098A234.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dg_0x80989140/func_8098A468.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dg_0x80989140/func_8098A55C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dg_0x80989140/func_8098A618.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dg_0x80989140/func_8098A70C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dg_0x80989140/func_8098A89C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dg_0x80989140/func_8098A938.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dg_0x80989140/func_8098AAAC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dg_0x80989140/func_8098AB48.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dg_0x80989140/func_8098AC34.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dg_0x80989140/func_8098AE58.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dg_0x80989140/func_8098AF44.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dg_0x80989140/func_8098AF98.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dg_0x80989140/func_8098B004.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dg_0x80989140/func_8098B198.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dg_0x80989140/func_8098B28C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dg_0x80989140/func_8098B390.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dg_0x80989140/func_8098B464.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dg_0x80989140/func_8098B560.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dg_0x80989140/func_8098B88C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dg_0x80989140/func_8098BA64.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dg_0x80989140/func_8098BB10.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dg_0x80989140/func_8098BBEC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dg_0x80989140/func_8098BC54.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dg_0x80989140/EnDg_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dg_0x80989140/EnDg_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dg_0x80989140/EnDg_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dg_0x80989140/func_8098BFB8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dg_0x80989140/func_8098BFD4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dg_0x80989140/EnDg_Draw.asm")
