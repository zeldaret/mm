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
    ACTORTYPE_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(OceffSpot),
    (ActorFunc)OceffSpot_Init,
    (ActorFunc)OceffSpot_Destroy,
    (ActorFunc)OceffSpot_Update,
    (ActorFunc)OceffSpot_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Oceff_Spot_0x80972680/func_80972680.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Oceff_Spot_0x80972680/OceffSpot_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Oceff_Spot_0x80972680/OceffSpot_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Oceff_Spot_0x80972680/func_80972844.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Oceff_Spot_0x80972680/func_809728F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Oceff_Spot_0x80972680/func_80972934.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Oceff_Spot_0x80972680/OceffSpot_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Oceff_Spot_0x80972680/OceffSpot_Draw.asm")
