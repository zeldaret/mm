#include "z_en_po_fusen.h"

#define FLAGS 0x80100030

#define THIS ((EnPoFusen*)thisx)

void EnPoFusen_Init(Actor* thisx, GlobalContext* globalCtx);
void EnPoFusen_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnPoFusen_Update(Actor* thisx, GlobalContext* globalCtx);
void EnPoFusen_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Po_Fusen_InitVars = {
    ACTOR_EN_PO_FUSEN,
    ACTORTYPE_PROP,
    FLAGS,
    OBJECT_PO_FUSEN,
    sizeof(EnPoFusen),
    (ActorFunc)EnPoFusen_Init,
    (ActorFunc)EnPoFusen_Destroy,
    (ActorFunc)EnPoFusen_Update,
    (ActorFunc)EnPoFusen_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Fusen_0x80AC1270/EnPoFusen_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Fusen_0x80AC1270/EnPoFusen_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Fusen_0x80AC1270/func_80AC1450.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Fusen_0x80AC1270/func_80AC14A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Fusen_0x80AC1270/func_80AC1574.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Fusen_0x80AC1270/func_80AC158C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Fusen_0x80AC1270/func_80AC18EC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Fusen_0x80AC1270/func_80AC192C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Fusen_0x80AC1270/func_80AC19B0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Fusen_0x80AC1270/func_80AC19DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Fusen_0x80AC1270/EnPoFusen_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Fusen_0x80AC1270/func_80AC1A68.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Fusen_0x80AC1270/func_80AC1CE8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Fusen_0x80AC1270/func_80AC1D00.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Po_Fusen_0x80AC1270/EnPoFusen_Draw.asm")
