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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hs_0x80952C50/func_80952C50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hs_0x80952C50/EnHs_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hs_0x80952C50/EnHs_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hs_0x80952C50/func_80952DFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hs_0x80952C50/func_80952E50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hs_0x80952C50/func_80952F00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hs_0x80952C50/func_80952FE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hs_0x80952C50/func_80953098.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hs_0x80952C50/func_80953180.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hs_0x80952C50/func_809532C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hs_0x80952C50/func_809532D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hs_0x80952C50/func_80953354.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hs_0x80952C50/func_809533A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hs_0x80952C50/func_8095345C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hs_0x80952C50/EnHs_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hs_0x80952C50/func_8095376C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hs_0x80952C50/func_80953848.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hs_0x80952C50/EnHs_Draw.asm")
