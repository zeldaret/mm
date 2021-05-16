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
    (ActorFunc)EnZot_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zot/func_80B965D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zot/EnZot_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zot/EnZot_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zot/func_80B96BEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zot/func_80B96CE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zot/func_80B96D4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zot/func_80B96DF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zot/func_80B96E5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zot/func_80B96FB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zot/func_80B97100.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zot/func_80B97110.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zot/func_80B97194.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zot/func_80B97240.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zot/func_80B972E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zot/func_80B973BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zot/func_80B975F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zot/func_80B9765C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zot/func_80B97708.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zot/func_80B9787C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zot/func_80B979DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zot/func_80B97A44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zot/func_80B97B5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zot/func_80B97BF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zot/func_80B97C40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zot/func_80B97CC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zot/func_80B97D6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zot/func_80B97E0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zot/func_80B97E4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zot/func_80B97FD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zot/func_80B980FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zot/func_80B98178.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zot/func_80B98348.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zot/func_80B9849C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zot/func_80B9854C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zot/func_80B985EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zot/func_80B98728.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zot/func_80B98998.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zot/func_80B98A4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zot/func_80B98AD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zot/func_80B98BF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zot/func_80B98CA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zot/func_80B98E10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zot/func_80B98F30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zot/func_80B98F94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zot/func_80B990A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zot/func_80B99160.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zot/func_80B991E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zot/func_80B992C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zot/func_80B99384.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zot/EnZot_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zot/func_80B99580.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zot/func_80B995A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zot/func_80B99758.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zot/EnZot_Draw.s")
