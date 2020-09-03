#include "z_en_zot.h"

#define FLAGS 0x00000019

#define THIS ((EnZot*)thisx)

void EnZot_Init(Actor* thisx, GlobalContext* globalCtx);
void EnZot_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnZot_Update(Actor* thisx, GlobalContext* globalCtx);
void EnZot_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Zot_InitVars = {
    ACTOR_EN_ZOT,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_ZO,
    sizeof(EnZot),
    (ActorFunc)EnZot_Init,
    (ActorFunc)EnZot_Destroy,
    (ActorFunc)EnZot_Update,
    (ActorFunc)EnZot_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Zot_0x80B965D0/func_80B965D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zot_0x80B965D0/EnZot_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zot_0x80B965D0/EnZot_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zot_0x80B965D0/func_80B96BEC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zot_0x80B965D0/func_80B96CE4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zot_0x80B965D0/func_80B96D4C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zot_0x80B965D0/func_80B96DF0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zot_0x80B965D0/func_80B96E5C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zot_0x80B965D0/func_80B96FB0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zot_0x80B965D0/func_80B97100.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zot_0x80B965D0/func_80B97110.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zot_0x80B965D0/func_80B97194.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zot_0x80B965D0/func_80B97240.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zot_0x80B965D0/func_80B972E8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zot_0x80B965D0/func_80B973BC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zot_0x80B965D0/func_80B975F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zot_0x80B965D0/func_80B9765C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zot_0x80B965D0/func_80B97708.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zot_0x80B965D0/func_80B9787C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zot_0x80B965D0/func_80B979DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zot_0x80B965D0/func_80B97A44.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zot_0x80B965D0/func_80B97B5C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zot_0x80B965D0/func_80B97BF8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zot_0x80B965D0/func_80B97C40.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zot_0x80B965D0/func_80B97CC8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zot_0x80B965D0/func_80B97D6C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zot_0x80B965D0/func_80B97E0C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zot_0x80B965D0/func_80B97E4C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zot_0x80B965D0/func_80B97FD0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zot_0x80B965D0/func_80B980FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zot_0x80B965D0/func_80B98178.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zot_0x80B965D0/func_80B98348.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zot_0x80B965D0/func_80B9849C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zot_0x80B965D0/func_80B9854C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zot_0x80B965D0/func_80B985EC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zot_0x80B965D0/func_80B98728.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zot_0x80B965D0/func_80B98998.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zot_0x80B965D0/func_80B98A4C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zot_0x80B965D0/func_80B98AD0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zot_0x80B965D0/func_80B98BF4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zot_0x80B965D0/func_80B98CA8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zot_0x80B965D0/func_80B98E10.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zot_0x80B965D0/func_80B98F30.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zot_0x80B965D0/func_80B98F94.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zot_0x80B965D0/func_80B990A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zot_0x80B965D0/func_80B99160.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zot_0x80B965D0/func_80B991E4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zot_0x80B965D0/func_80B992C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zot_0x80B965D0/func_80B99384.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zot_0x80B965D0/EnZot_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zot_0x80B965D0/func_80B99580.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zot_0x80B965D0/func_80B995A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zot_0x80B965D0/func_80B99758.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zot_0x80B965D0/EnZot_Draw.asm")
