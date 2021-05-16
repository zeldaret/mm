#include "z_en_m_thunder.h"

#define FLAGS 0x00000010

#define THIS ((EnMThunder*)thisx)

void EnMThunder_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMThunder_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMThunder_Update(Actor* thisx, GlobalContext* globalCtx);
void EnMThunder_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_M_Thunder_InitVars = {
    ACTOR_EN_M_THUNDER,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnMThunder),
    (ActorFunc)EnMThunder_Init,
    (ActorFunc)EnMThunder_Destroy,
    (ActorFunc)EnMThunder_Update,
    (ActorFunc)EnMThunder_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_M_Thunder/func_808B53C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_M_Thunder/EnMThunder_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_M_Thunder/EnMThunder_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_M_Thunder/func_808B5890.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_M_Thunder/func_808B58CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_M_Thunder/func_808B5984.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_M_Thunder/func_808B5EEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_M_Thunder/func_808B5F68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_M_Thunder/func_808B60D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_M_Thunder/func_808B6310.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_M_Thunder/EnMThunder_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_M_Thunder/func_808B65BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_M_Thunder/EnMThunder_Draw.s")
