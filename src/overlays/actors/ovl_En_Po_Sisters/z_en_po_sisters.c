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
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_PO_SISTERS,
    sizeof(EnPoSisters),
    (ActorFunc)EnPoSisters_Init,
    (ActorFunc)EnPoSisters_Destroy,
    (ActorFunc)EnPoSisters_Update,
    (ActorFunc)EnPoSisters_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Sisters_0x80B1A3B0/EnPoSisters_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Sisters_0x80B1A3B0/EnPoSisters_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Sisters_0x80B1A3B0/func_80B1A648.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Sisters_0x80B1A3B0/func_80B1A768.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Sisters_0x80B1A3B0/func_80B1A894.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Sisters_0x80B1A3B0/func_80B1A9B0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Sisters_0x80B1A3B0/func_80B1AA88.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Sisters_0x80B1A3B0/func_80B1AAE8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Sisters_0x80B1A3B0/func_80B1AB5C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Sisters_0x80B1A3B0/func_80B1ABB8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Sisters_0x80B1A3B0/func_80B1AC40.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Sisters_0x80B1A3B0/func_80B1ACB8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Sisters_0x80B1A3B0/func_80B1AE28.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Sisters_0x80B1A3B0/func_80B1AE3C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Sisters_0x80B1A3B0/func_80B1AF8C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Sisters_0x80B1A3B0/func_80B1B020.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Sisters_0x80B1A3B0/func_80B1B0E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Sisters_0x80B1A3B0/func_80B1B168.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Sisters_0x80B1A3B0/func_80B1B280.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Sisters_0x80B1A3B0/func_80B1B2F0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Sisters_0x80B1A3B0/func_80B1B3A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Sisters_0x80B1A3B0/func_80B1B444.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Sisters_0x80B1A3B0/func_80B1B5B4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Sisters_0x80B1A3B0/func_80B1B628.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Sisters_0x80B1A3B0/func_80B1B70C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Sisters_0x80B1A3B0/func_80B1B7BC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Sisters_0x80B1A3B0/func_80B1B860.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Sisters_0x80B1A3B0/func_80B1B940.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Sisters_0x80B1A3B0/func_80B1BA3C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Sisters_0x80B1A3B0/func_80B1BA90.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Sisters_0x80B1A3B0/func_80B1BC4C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Sisters_0x80B1A3B0/func_80B1BCA0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Sisters_0x80B1A3B0/func_80B1BCF0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Sisters_0x80B1A3B0/func_80B1BE4C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Sisters_0x80B1A3B0/func_80B1BF2C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Sisters_0x80B1A3B0/func_80B1C030.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Sisters_0x80B1A3B0/func_80B1C0A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Sisters_0x80B1A3B0/func_80B1C2E8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Sisters_0x80B1A3B0/func_80B1C340.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Sisters_0x80B1A3B0/func_80B1C408.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Sisters_0x80B1A3B0/EnPoSisters_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Sisters_0x80B1A3B0/func_80B1C974.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Sisters_0x80B1A3B0/func_80B1CB44.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Sisters_0x80B1A3B0/func_80B1CD34.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Sisters_0x80B1A3B0/EnPoSisters_Draw.asm")
