/*
 * File: z_eff_zoraband.c
 * Overlay: ovl_Eff_Zoraband
 * Description: Indigo-Go's (Mikau's healing cutscene)
 */

#include "z_eff_zoraband.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((EffZoraband*)thisx)

void EffZoraband_Init(Actor* thisx, GlobalContext* globalCtx);
void EffZoraband_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EffZoraband_Update(Actor* thisx, GlobalContext* globalCtx);
void EffZoraband_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80C07790(EffZoraband* this, GlobalContext* globalCtx);

#if 0
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

#endif

extern UNK_TYPE D_06000F38;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Eff_Zoraband/EffZoraband_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Eff_Zoraband/EffZoraband_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Eff_Zoraband/func_80C07790.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Eff_Zoraband/EffZoraband_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Eff_Zoraband/EffZoraband_Draw.s")
