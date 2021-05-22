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
    (ActorFunc)EnBbfall_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/EnBbfall_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/EnBbfall_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/func_808BF344.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/func_808BF3B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/func_808BF438.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/func_808BF4B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/func_808BF514.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/func_808BF578.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/func_808BF5AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/func_808BF5E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/func_808BF734.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/func_808BF7A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/func_808BF830.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/func_808BF894.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/func_808BF8DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/func_808BFA18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/func_808BFA3C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/func_808BFAB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/func_808BFB4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/func_808BFCCC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/func_808BFE58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/func_808BFF8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/func_808C00A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/func_808C013C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/func_808C0178.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/func_808C01E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/EnBbfall_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/func_808C07D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/func_808C080C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bbfall_0x808BF220/EnBbfall_Draw.asm")
