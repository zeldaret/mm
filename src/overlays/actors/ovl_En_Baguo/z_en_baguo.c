#include "z_en_baguo.h"

#define FLAGS 0x00000005

#define THIS ((EnBaguo*)thisx)

void EnBaguo_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBaguo_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBaguo_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Baguo_InitVars = {
    ACTOR_EN_BAGUO,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_GMO,
    sizeof(EnBaguo),
    (ActorFunc)EnBaguo_Init,
    (ActorFunc)EnBaguo_Destroy,
    (ActorFunc)EnBaguo_Update,
    (ActorFunc)NULL
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baguo/EnBaguo_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baguo/EnBaguo_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baguo/func_80A3B220.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baguo/func_80A3B2CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baguo/func_80A3B3E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baguo/func_80A3B5E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baguo/func_80A3B794.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baguo/func_80A3B7B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baguo/func_80A3B8F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baguo/func_80A3B958.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baguo/EnBaguo_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baguo/func_80A3BE24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baguo/func_80A3BE60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baguo/func_80A3BF0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baguo/func_80A3C008.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Baguo/func_80A3C17C.s")
