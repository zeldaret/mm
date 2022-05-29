/*
 * File: z_eff_lastday.c
 * Overlay: ovl_Eff_Lastday
 * Description: Moon Crash Cutscene Fire Wall
 */

#include "z_eff_lastday.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((EffLastday*)thisx)

void EffLastday_Init(Actor* thisx, GlobalContext* globalCtx);
void EffLastday_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EffLastday_Update(Actor* thisx, GlobalContext* globalCtx);
void EffLastday_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80BEBD0C(EffLastday* this, GlobalContext* globalCtx);
void func_80BEBDF8(EffLastday* this, GlobalContext* globalCtx);
void func_80BEBEB8(EffLastday* this, GlobalContext* globalCtx);
void func_80BEBF78(EffLastday* this, GlobalContext* globalCtx);

#if 0
const ActorInit Eff_Lastday_InitVars = {
    ACTOR_EFF_LASTDAY,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_LASTDAY,
    sizeof(EffLastday),
    (ActorFunc)EffLastday_Init,
    (ActorFunc)EffLastday_Destroy,
    (ActorFunc)EffLastday_Update,
    (ActorFunc)EffLastday_Draw,
};

#endif

extern UNK_TYPE D_06000000;
extern UNK_TYPE D_06000510;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Eff_Lastday/EffLastday_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Eff_Lastday/EffLastday_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Eff_Lastday/func_80BEBD0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Eff_Lastday/func_80BEBDF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Eff_Lastday/func_80BEBEB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Eff_Lastday/func_80BEBF78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Eff_Lastday/EffLastday_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Eff_Lastday/func_80BEC0A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Eff_Lastday/EffLastday_Draw.s")
