#include "z_en_bom_bowl_man.h"

#define FLAGS 0x00000009

#define THIS ((EnBomBowlMan*)thisx)

void EnBomBowlMan_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBomBowlMan_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBomBowlMan_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBomBowlMan_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Bom_Bowl_Man_InitVars = {
    ACTOR_EN_BOM_BOWL_MAN,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_CS,
    sizeof(EnBomBowlMan),
    (ActorFunc)EnBomBowlMan_Init,
    (ActorFunc)EnBomBowlMan_Destroy,
    (ActorFunc)EnBomBowlMan_Update,
    (ActorFunc)EnBomBowlMan_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom_Bowl_Man/EnBomBowlMan_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom_Bowl_Man/EnBomBowlMan_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom_Bowl_Man/func_809C493C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom_Bowl_Man/func_809C49CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom_Bowl_Man/func_809C4B50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom_Bowl_Man/func_809C4B6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom_Bowl_Man/func_809C4BC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom_Bowl_Man/func_809C4DA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom_Bowl_Man/func_809C51B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom_Bowl_Man/func_809C52B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom_Bowl_Man/func_809C5310.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom_Bowl_Man/func_809C53A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom_Bowl_Man/func_809C5408.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom_Bowl_Man/func_809C5524.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom_Bowl_Man/func_809C5598.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom_Bowl_Man/func_809C5738.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom_Bowl_Man/func_809C59A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom_Bowl_Man/func_809C59F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom_Bowl_Man/func_809C5AA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom_Bowl_Man/func_809C5B1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom_Bowl_Man/func_809C5BA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom_Bowl_Man/func_809C5BF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom_Bowl_Man/EnBomBowlMan_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom_Bowl_Man/func_809C5F44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom_Bowl_Man/EnBomBowlMan_Draw.s")
