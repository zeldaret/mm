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
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_GELDB,
    sizeof(EnGe3),
    (ActorFunc)EnGe3_Init,
    (ActorFunc)EnGe3_Destroy,
    (ActorFunc)EnGe3_Update,
    (ActorFunc)EnGe3_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Ge3_0x8099FEB0/EnGe3_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ge3_0x8099FEB0/EnGe3_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ge3_0x8099FEB0/func_809A0070.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ge3_0x8099FEB0/func_809A00F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ge3_0x8099FEB0/func_809A020C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ge3_0x8099FEB0/func_809A024C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ge3_0x8099FEB0/func_809A0350.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ge3_0x8099FEB0/func_809A03AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ge3_0x8099FEB0/func_809A03FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ge3_0x8099FEB0/func_809A04D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ge3_0x8099FEB0/func_809A0820.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ge3_0x8099FEB0/func_809A08A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ge3_0x8099FEB0/EnGe3_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ge3_0x8099FEB0/func_809A096C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ge3_0x8099FEB0/func_809A0A14.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ge3_0x8099FEB0/func_809A0C60.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ge3_0x8099FEB0/EnGe3_Draw.asm")
