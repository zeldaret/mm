#include "z_en_sekihi.h"

#define FLAGS 0x00000019

#define THIS ((EnSekihi*)thisx)

void EnSekihi_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSekihi_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSekihi_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Sekihi_InitVars = {
    ACTOR_EN_SEKIHI,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnSekihi),
    (ActorFunc)EnSekihi_Init,
    (ActorFunc)EnSekihi_Destroy,
    (ActorFunc)EnSekihi_Update,
    (ActorFunc)NULL,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sekihi_0x80A44C80/EnSekihi_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sekihi_0x80A44C80/EnSekihi_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sekihi_0x80A44C80/func_80A44DE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sekihi_0x80A44C80/func_80A44F40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sekihi_0x80A44C80/func_80A450B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sekihi_0x80A44C80/func_80A45130.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sekihi_0x80A44C80/EnSekihi_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sekihi_0x80A44C80/func_80A45164.asm")
