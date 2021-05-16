#include "z_oceff_spot.h"

#define FLAGS 0x02000010

#define THIS ((OceffSpot*)thisx)

void OceffSpot_Init(Actor* thisx, GlobalContext* globalCtx);
void OceffSpot_Destroy(Actor* thisx, GlobalContext* globalCtx);
void OceffSpot_Update(Actor* thisx, GlobalContext* globalCtx);
void OceffSpot_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Oceff_Spot_InitVars = {
    ACTOR_OCEFF_SPOT,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(OceffSpot),
    (ActorFunc)OceffSpot_Init,
    (ActorFunc)OceffSpot_Destroy,
    (ActorFunc)OceffSpot_Update,
    (ActorFunc)OceffSpot_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Spot/func_80972680.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Spot/OceffSpot_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Spot/OceffSpot_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Spot/func_80972844.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Spot/func_809728F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Spot/func_80972934.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Spot/OceffSpot_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Spot/OceffSpot_Draw.s")
