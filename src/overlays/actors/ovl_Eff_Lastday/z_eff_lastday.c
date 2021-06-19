#include "z_eff_lastday.h"

#define FLAGS 0x00000030

#define THIS ((EffLastday*)thisx)

void EffLastday_Init(Actor* thisx, GlobalContext* globalCtx);
void EffLastday_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EffLastday_Update(Actor* thisx, GlobalContext* globalCtx);
void EffLastday_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
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
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Eff_Lastday_0x80BEBAC0/EffLastday_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Eff_Lastday_0x80BEBAC0/EffLastday_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Eff_Lastday_0x80BEBAC0/func_80BEBD0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Eff_Lastday_0x80BEBAC0/func_80BEBDF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Eff_Lastday_0x80BEBAC0/func_80BEBEB8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Eff_Lastday_0x80BEBAC0/func_80BEBF78.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Eff_Lastday_0x80BEBAC0/EffLastday_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Eff_Lastday_0x80BEBAC0/func_80BEC0A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Eff_Lastday_0x80BEBAC0/EffLastday_Draw.asm")
