#include "z_en_hs.h"

#define FLAGS 0x00000019

#define THIS ((EnHs*)thisx)

void EnHs_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHs_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHs_Update(Actor* thisx, GlobalContext* globalCtx);
void EnHs_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Hs_InitVars = {
    ACTOR_EN_HS,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_HS,
    sizeof(EnHs),
    (ActorFunc)EnHs_Init,
    (ActorFunc)EnHs_Destroy,
    (ActorFunc)EnHs_Update,
    (ActorFunc)EnHs_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hs/func_80952C50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hs/EnHs_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hs/EnHs_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hs/func_80952DFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hs/func_80952E50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hs/func_80952F00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hs/func_80952FE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hs/func_80953098.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hs/func_80953180.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hs/func_809532C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hs/func_809532D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hs/func_80953354.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hs/func_809533A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hs/func_8095345C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hs/EnHs_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hs/func_8095376C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hs/func_80953848.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hs/EnHs_Draw.s")
