#include "z_en_bji_01.h"

#define FLAGS 0x00000019

#define THIS ((EnBji01*)thisx)

void EnBji01_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBji01_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBji01_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBji01_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Bji_01_InitVars = {
    ACTOR_EN_BJI_01,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_BJI,
    sizeof(EnBji01),
    (ActorFunc)EnBji01_Init,
    (ActorFunc)EnBji01_Destroy,
    (ActorFunc)EnBji01_Update,
    (ActorFunc)EnBji01_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Bji_01_0x809CCDE0/func_809CCDE0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bji_01_0x809CCDE0/func_809CCE98.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bji_01_0x809CCDE0/func_809CCEE8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bji_01_0x809CCDE0/func_809CD028.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bji_01_0x809CCDE0/func_809CD328.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bji_01_0x809CCDE0/func_809CD634.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bji_01_0x809CCDE0/func_809CD6B0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bji_01_0x809CCDE0/func_809CD6C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bji_01_0x809CCDE0/func_809CD70C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bji_01_0x809CCDE0/func_809CD77C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bji_01_0x809CCDE0/EnBji01_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bji_01_0x809CCDE0/EnBji01_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bji_01_0x809CCDE0/EnBji01_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bji_01_0x809CCDE0/func_809CDA4C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bji_01_0x809CCDE0/func_809CDB04.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bji_01_0x809CCDE0/EnBji01_Draw.asm")
