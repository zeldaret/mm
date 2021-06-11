#include "z_en_ge3.h"

#define FLAGS 0x80000019

#define THIS ((EnGe3*)thisx)

void EnGe3_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGe3_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGe3_Update(Actor* thisx, GlobalContext* globalCtx);
void EnGe3_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Ge3_InitVars = {
    ACTOR_EN_GE3,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_GELDB,
    sizeof(EnGe3),
    (ActorFunc)EnGe3_Init,
    (ActorFunc)EnGe3_Destroy,
    (ActorFunc)EnGe3_Update,
    (ActorFunc)EnGe3_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge3/EnGe3_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge3/EnGe3_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge3/func_809A0070.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge3/func_809A00F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge3/func_809A020C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge3/func_809A024C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge3/func_809A0350.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge3/func_809A03AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge3/func_809A03FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge3/func_809A04D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge3/func_809A0820.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge3/func_809A08A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge3/EnGe3_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge3/func_809A096C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge3/func_809A0A14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge3/func_809A0C60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge3/EnGe3_Draw.s")
