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
    (ActorFunc)EnMThunder_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_M_Thunder_0x808B53C0/func_808B53C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_M_Thunder_0x808B53C0/EnMThunder_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_M_Thunder_0x808B53C0/EnMThunder_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_M_Thunder_0x808B53C0/func_808B5890.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_M_Thunder_0x808B53C0/func_808B58CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_M_Thunder_0x808B53C0/func_808B5984.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_M_Thunder_0x808B53C0/func_808B5EEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_M_Thunder_0x808B53C0/func_808B5F68.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_M_Thunder_0x808B53C0/func_808B60D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_M_Thunder_0x808B53C0/func_808B6310.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_M_Thunder_0x808B53C0/EnMThunder_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_M_Thunder_0x808B53C0/func_808B65BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_M_Thunder_0x808B53C0/EnMThunder_Draw.asm")
