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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ge3_0x8099FEB0/EnGe3_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ge3_0x8099FEB0/EnGe3_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ge3_0x8099FEB0/func_809A0070.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ge3_0x8099FEB0/func_809A00F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ge3_0x8099FEB0/func_809A020C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ge3_0x8099FEB0/func_809A024C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ge3_0x8099FEB0/func_809A0350.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ge3_0x8099FEB0/func_809A03AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ge3_0x8099FEB0/func_809A03FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ge3_0x8099FEB0/func_809A04D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ge3_0x8099FEB0/func_809A0820.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ge3_0x8099FEB0/func_809A08A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ge3_0x8099FEB0/EnGe3_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ge3_0x8099FEB0/func_809A096C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ge3_0x8099FEB0/func_809A0A14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ge3_0x8099FEB0/func_809A0C60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ge3_0x8099FEB0/EnGe3_Draw.asm")
