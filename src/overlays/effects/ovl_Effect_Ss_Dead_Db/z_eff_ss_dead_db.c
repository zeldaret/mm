/*
 * File: z_eff_ss_dead_db.c
 * Overlay: ovl_Effect_Ss_Dead_Db
 * Description:
 */

#include "z_eff_ss_dead_db.h"

#define PARAMS ((EffectSsDeadDbInitParams*)initParamsx)

s32 EffectSsDeadDb_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx);
void EffectSsDeadDb_Update(GlobalContext* globalCtx, u32 index, EffectSs* this);
void EffectSsDeadDb_Draw(GlobalContext* globalCtx, u32 index, EffectSs* this);

#if 0
const EffectSsInit Effect_Ss_Dead_Db_InitVars = {
    EFFECT_SS_DEAD_DB,
    EffectSsDeadDb_Init,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Dead_Db/EffectSsDeadDb_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Dead_Db/EffectSsDeadDb_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Effect_Ss_Dead_Db/EffectSsDeadDb_Update.s")
