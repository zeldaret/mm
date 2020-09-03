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
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_BB,
    sizeof(EnBbfall),
    (ActorFunc)EnBbfall_Init,
    (ActorFunc)EnBbfall_Destroy,
    (ActorFunc)EnBbfall_Update,
    (ActorFunc)EnBbfall_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Bbfall_0x808BF220/EnBbfall_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bbfall_0x808BF220/EnBbfall_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bbfall_0x808BF220/func_808BF344.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bbfall_0x808BF220/func_808BF3B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bbfall_0x808BF220/func_808BF438.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bbfall_0x808BF220/func_808BF4B4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bbfall_0x808BF220/func_808BF514.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bbfall_0x808BF220/func_808BF578.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bbfall_0x808BF220/func_808BF5AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bbfall_0x808BF220/func_808BF5E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bbfall_0x808BF220/func_808BF734.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bbfall_0x808BF220/func_808BF7A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bbfall_0x808BF220/func_808BF830.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bbfall_0x808BF220/func_808BF894.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bbfall_0x808BF220/func_808BF8DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bbfall_0x808BF220/func_808BFA18.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bbfall_0x808BF220/func_808BFA3C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bbfall_0x808BF220/func_808BFAB4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bbfall_0x808BF220/func_808BFB4C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bbfall_0x808BF220/func_808BFCCC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bbfall_0x808BF220/func_808BFE58.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bbfall_0x808BF220/func_808BFF8C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bbfall_0x808BF220/func_808C00A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bbfall_0x808BF220/func_808C013C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bbfall_0x808BF220/func_808C0178.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bbfall_0x808BF220/func_808C01E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bbfall_0x808BF220/EnBbfall_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bbfall_0x808BF220/func_808C07D4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bbfall_0x808BF220/func_808C080C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bbfall_0x808BF220/EnBbfall_Draw.asm")
