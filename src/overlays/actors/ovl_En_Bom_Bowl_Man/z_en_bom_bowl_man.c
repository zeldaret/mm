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
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_CS,
    sizeof(EnBomBowlMan),
    (ActorFunc)EnBomBowlMan_Init,
    (ActorFunc)EnBomBowlMan_Destroy,
    (ActorFunc)EnBomBowlMan_Update,
    (ActorFunc)EnBomBowlMan_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Bom_Bowl_Man_0x809C4790/EnBomBowlMan_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bom_Bowl_Man_0x809C4790/EnBomBowlMan_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bom_Bowl_Man_0x809C4790/func_809C493C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bom_Bowl_Man_0x809C4790/func_809C49CC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bom_Bowl_Man_0x809C4790/func_809C4B50.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bom_Bowl_Man_0x809C4790/func_809C4B6C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bom_Bowl_Man_0x809C4790/func_809C4BC4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bom_Bowl_Man_0x809C4790/func_809C4DA4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bom_Bowl_Man_0x809C4790/func_809C51B4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bom_Bowl_Man_0x809C4790/func_809C52B4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bom_Bowl_Man_0x809C4790/func_809C5310.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bom_Bowl_Man_0x809C4790/func_809C53A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bom_Bowl_Man_0x809C4790/func_809C5408.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bom_Bowl_Man_0x809C4790/func_809C5524.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bom_Bowl_Man_0x809C4790/func_809C5598.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bom_Bowl_Man_0x809C4790/func_809C5738.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bom_Bowl_Man_0x809C4790/func_809C59A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bom_Bowl_Man_0x809C4790/func_809C59F0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bom_Bowl_Man_0x809C4790/func_809C5AA4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bom_Bowl_Man_0x809C4790/func_809C5B1C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bom_Bowl_Man_0x809C4790/func_809C5BA0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bom_Bowl_Man_0x809C4790/func_809C5BF4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bom_Bowl_Man_0x809C4790/EnBomBowlMan_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bom_Bowl_Man_0x809C4790/func_809C5F44.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bom_Bowl_Man_0x809C4790/EnBomBowlMan_Draw.asm")
