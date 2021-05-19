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
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_ZO,
    sizeof(EnZot),
    (ActorFunc)EnZot_Init,
    (ActorFunc)EnZot_Destroy,
    (ActorFunc)EnZot_Update,
    (ActorFunc)EnZot_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zot_0x80B965D0/func_80B965D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zot_0x80B965D0/EnZot_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zot_0x80B965D0/EnZot_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zot_0x80B965D0/func_80B96BEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zot_0x80B965D0/func_80B96CE4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zot_0x80B965D0/func_80B96D4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zot_0x80B965D0/func_80B96DF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zot_0x80B965D0/func_80B96E5C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zot_0x80B965D0/func_80B96FB0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zot_0x80B965D0/func_80B97100.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zot_0x80B965D0/func_80B97110.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zot_0x80B965D0/func_80B97194.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zot_0x80B965D0/func_80B97240.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zot_0x80B965D0/func_80B972E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zot_0x80B965D0/func_80B973BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zot_0x80B965D0/func_80B975F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zot_0x80B965D0/func_80B9765C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zot_0x80B965D0/func_80B97708.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zot_0x80B965D0/func_80B9787C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zot_0x80B965D0/func_80B979DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zot_0x80B965D0/func_80B97A44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zot_0x80B965D0/func_80B97B5C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zot_0x80B965D0/func_80B97BF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zot_0x80B965D0/func_80B97C40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zot_0x80B965D0/func_80B97CC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zot_0x80B965D0/func_80B97D6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zot_0x80B965D0/func_80B97E0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zot_0x80B965D0/func_80B97E4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zot_0x80B965D0/func_80B97FD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zot_0x80B965D0/func_80B980FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zot_0x80B965D0/func_80B98178.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zot_0x80B965D0/func_80B98348.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zot_0x80B965D0/func_80B9849C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zot_0x80B965D0/func_80B9854C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zot_0x80B965D0/func_80B985EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zot_0x80B965D0/func_80B98728.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zot_0x80B965D0/func_80B98998.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zot_0x80B965D0/func_80B98A4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zot_0x80B965D0/func_80B98AD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zot_0x80B965D0/func_80B98BF4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zot_0x80B965D0/func_80B98CA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zot_0x80B965D0/func_80B98E10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zot_0x80B965D0/func_80B98F30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zot_0x80B965D0/func_80B98F94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zot_0x80B965D0/func_80B990A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zot_0x80B965D0/func_80B99160.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zot_0x80B965D0/func_80B991E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zot_0x80B965D0/func_80B992C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zot_0x80B965D0/func_80B99384.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zot_0x80B965D0/EnZot_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zot_0x80B965D0/func_80B99580.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zot_0x80B965D0/func_80B995A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zot_0x80B965D0/func_80B99758.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zot_0x80B965D0/EnZot_Draw.asm")
