#include "z_en_gk.h"

#define FLAGS 0x00000009

#define THIS ((EnGk*)thisx)

void EnGk_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGk_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGk_Update(Actor* thisx, GlobalContext* globalCtx);
void EnGk_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Gk_InitVars = {
    ACTOR_EN_GK,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_GK,
    sizeof(EnGk),
    (ActorFunc)EnGk_Init,
    (ActorFunc)EnGk_Destroy,
    (ActorFunc)EnGk_Update,
    (ActorFunc)EnGk_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Gk_0x80B50410/func_80B50410.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gk_0x80B50410/func_80B50710.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gk_0x80B50410/func_80B507A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gk_0x80B50410/func_80B50854.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gk_0x80B50410/func_80B50954.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gk_0x80B50410/func_80B509A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gk_0x80B50410/func_80B50B38.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gk_0x80B50410/func_80B50C78.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gk_0x80B50410/func_80B50E14.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gk_0x80B50410/func_80B50ED4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gk_0x80B50410/func_80B5100C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gk_0x80B50410/func_80B5123C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gk_0x80B50410/func_80B51308.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gk_0x80B50410/func_80B51398.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gk_0x80B50410/func_80B51410.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gk_0x80B50410/func_80B51510.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gk_0x80B50410/func_80B51698.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gk_0x80B50410/func_80B51760.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gk_0x80B50410/func_80B51970.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gk_0x80B50410/func_80B51B40.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gk_0x80B50410/func_80B51D9C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gk_0x80B50410/func_80B51EA4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gk_0x80B50410/func_80B51FD0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gk_0x80B50410/func_80B5202C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gk_0x80B50410/func_80B5216C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gk_0x80B50410/func_80B521E8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gk_0x80B50410/func_80B5227C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gk_0x80B50410/func_80B52340.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gk_0x80B50410/func_80B52430.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gk_0x80B50410/func_80B5253C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gk_0x80B50410/func_80B525E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gk_0x80B50410/func_80B52654.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gk_0x80B50410/EnGk_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gk_0x80B50410/EnGk_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gk_0x80B50410/EnGk_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gk_0x80B50410/func_80B52AD4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gk_0x80B50410/func_80B52AF0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gk_0x80B50410/func_80B52D8C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Gk_0x80B50410/EnGk_Draw.asm")
