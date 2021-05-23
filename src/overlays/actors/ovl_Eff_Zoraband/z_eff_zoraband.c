#include "z_eff_zoraband.h"

#define FLAGS 0x00000030

#define THIS ((EffZoraband*)thisx)

void EffZoraband_Init(Actor* thisx, GlobalContext* globalCtx);
void EffZoraband_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EffZoraband_Update(Actor* thisx, GlobalContext* globalCtx);
void EffZoraband_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Eff_Zoraband_InitVars = {
    ACTOR_EFF_ZORABAND,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_ZORABAND,
    sizeof(EffZoraband),
    (ActorFunc)EffZoraband_Init,
    (ActorFunc)EffZoraband_Destroy,
    (ActorFunc)EffZoraband_Update,
    (ActorFunc)EffZoraband_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Eff_Zoraband_0x80C07740/EffZoraband_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Eff_Zoraband_0x80C07740/EffZoraband_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Eff_Zoraband_0x80C07740/func_80C07790.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Eff_Zoraband_0x80C07740/EffZoraband_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Eff_Zoraband_0x80C07740/EffZoraband_Draw.asm")
