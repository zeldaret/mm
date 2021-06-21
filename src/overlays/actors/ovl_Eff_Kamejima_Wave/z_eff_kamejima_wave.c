#include "z_eff_kamejima_wave.h"

#define FLAGS 0x00000010

#define THIS ((EffKamejimaWave*)thisx)

void EffKamejimaWave_Init(Actor* thisx, GlobalContext* globalCtx);
void EffKamejimaWave_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EffKamejimaWave_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Eff_Kamejima_Wave_InitVars = {
    ACTOR_EFF_KAMEJIMA_WAVE,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_KAMEJIMA,
    sizeof(EffKamejimaWave),
    (ActorFunc)EffKamejimaWave_Init,
    (ActorFunc)EffKamejimaWave_Destroy,
    (ActorFunc)EffKamejimaWave_Update,
    (ActorFunc)NULL,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Eff_Kamejima_Wave_0x80BCEB20/EffKamejimaWave_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Eff_Kamejima_Wave_0x80BCEB20/EffKamejimaWave_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Eff_Kamejima_Wave_0x80BCEB20/func_80BCEBC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Eff_Kamejima_Wave_0x80BCEB20/func_80BCEC6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Eff_Kamejima_Wave_0x80BCEB20/func_80BCED34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Eff_Kamejima_Wave_0x80BCEB20/func_80BCEDE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Eff_Kamejima_Wave_0x80BCEB20/EffKamejimaWave_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Eff_Kamejima_Wave_0x80BCEB20/func_80BCEEBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Eff_Kamejima_Wave_0x80BCEB20/func_80BCEF0C.asm")
