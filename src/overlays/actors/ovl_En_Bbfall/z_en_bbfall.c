#include "z_en_bbfall.h"

#define FLAGS 0x00000215

#define THIS ((EnBbfall*)thisx)

void EnBbfall_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBbfall_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBbfall_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBbfall_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Bbfall_InitVars = {
    ACTOR_EN_BBFALL,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_BB,
    sizeof(EnBbfall),
    (ActorFunc)EnBbfall_Init,
    (ActorFunc)EnBbfall_Destroy,
    (ActorFunc)EnBbfall_Update,
    (ActorFunc)EnBbfall_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/EnBbfall_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/EnBbfall_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808BF344.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808BF3B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808BF438.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808BF4B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808BF514.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808BF578.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808BF5AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808BF5E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808BF734.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808BF7A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808BF830.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808BF894.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808BF8DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808BFA18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808BFA3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808BFAB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808BFB4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808BFCCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808BFE58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808BFF8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808C00A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808C013C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808C0178.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808C01E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/EnBbfall_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808C07D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808C080C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/EnBbfall_Draw.s")
