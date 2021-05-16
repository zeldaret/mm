#include "z_en_po_sisters.h"

#define FLAGS 0x00005015

#define THIS ((EnPoSisters*)thisx)

void EnPoSisters_Init(Actor* thisx, GlobalContext* globalCtx);
void EnPoSisters_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnPoSisters_Update(Actor* thisx, GlobalContext* globalCtx);
void EnPoSisters_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Po_Sisters_InitVars = {
    ACTOR_EN_PO_SISTERS,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_PO_SISTERS,
    sizeof(EnPoSisters),
    (ActorFunc)EnPoSisters_Init,
    (ActorFunc)EnPoSisters_Destroy,
    (ActorFunc)EnPoSisters_Update,
    (ActorFunc)EnPoSisters_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/EnPoSisters_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/EnPoSisters_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1A648.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1A768.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1A894.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1A9B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1AA88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1AAE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1AB5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1ABB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1AC40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1ACB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1AE28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1AE3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1AF8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1B020.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1B0E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1B168.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1B280.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1B2F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1B3A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1B444.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1B5B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1B628.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1B70C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1B7BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1B860.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1B940.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1BA3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1BA90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1BC4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1BCA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1BCF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1BE4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1BF2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1C030.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1C0A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1C2E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1C340.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1C408.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/EnPoSisters_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1C974.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1CB44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/func_80B1CD34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Po_Sisters/EnPoSisters_Draw.s")
