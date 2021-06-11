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
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_BJI,
    sizeof(EnBji01),
    (ActorFunc)EnBji01_Init,
    (ActorFunc)EnBji01_Destroy,
    (ActorFunc)EnBji01_Update,
    (ActorFunc)EnBji01_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bji_01/func_809CCDE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bji_01/func_809CCE98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bji_01/func_809CCEE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bji_01/func_809CD028.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bji_01/func_809CD328.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bji_01/func_809CD634.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bji_01/func_809CD6B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bji_01/func_809CD6C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bji_01/func_809CD70C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bji_01/func_809CD77C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bji_01/EnBji01_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bji_01/EnBji01_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bji_01/EnBji01_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bji_01/func_809CDA4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bji_01/func_809CDB04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bji_01/EnBji01_Draw.s")
