/*
 * File: z_eff_kamejima_wave.c
 * Overlay: ovl_Eff_Kamejima_Wave
 * Description: Wave Created by Turtle Awakening
 */

#include "z_eff_kamejima_wave.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((EffKamejimaWave*)thisx)

void EffKamejimaWave_Init(Actor* thisx, GlobalContext* globalCtx);
void EffKamejimaWave_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EffKamejimaWave_Update(Actor* thisx, GlobalContext* globalCtx);

#if 0
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

#endif

extern UNK_TYPE D_06000000;
extern UNK_TYPE D_06000140;
extern UNK_TYPE D_06001AF0;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Eff_Kamejima_Wave/EffKamejimaWave_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Eff_Kamejima_Wave/EffKamejimaWave_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Eff_Kamejima_Wave/func_80BCEBC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Eff_Kamejima_Wave/func_80BCEC6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Eff_Kamejima_Wave/func_80BCED34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Eff_Kamejima_Wave/func_80BCEDE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Eff_Kamejima_Wave/EffKamejimaWave_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Eff_Kamejima_Wave/func_80BCEEBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Eff_Kamejima_Wave/func_80BCEF0C.s")
