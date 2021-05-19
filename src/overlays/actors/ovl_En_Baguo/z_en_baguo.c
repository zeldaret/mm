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
    (ActorFunc)NULL,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baguo_0x80A3B080/EnBaguo_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baguo_0x80A3B080/EnBaguo_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baguo_0x80A3B080/func_80A3B220.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baguo_0x80A3B080/func_80A3B2CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baguo_0x80A3B080/func_80A3B3E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baguo_0x80A3B080/func_80A3B5E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baguo_0x80A3B080/func_80A3B794.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baguo_0x80A3B080/func_80A3B7B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baguo_0x80A3B080/func_80A3B8F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baguo_0x80A3B080/func_80A3B958.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baguo_0x80A3B080/EnBaguo_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baguo_0x80A3B080/func_80A3BE24.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baguo_0x80A3B080/func_80A3BE60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baguo_0x80A3B080/func_80A3BF0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baguo_0x80A3B080/func_80A3C008.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baguo_0x80A3B080/func_80A3C17C.asm")
