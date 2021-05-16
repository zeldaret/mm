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
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_GK,
    sizeof(EnGk),
    (ActorFunc)EnGk_Init,
    (ActorFunc)EnGk_Destroy,
    (ActorFunc)EnGk_Update,
    (ActorFunc)EnGk_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B50410.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B50710.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B507A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B50854.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B50954.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B509A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B50B38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B50C78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B50E14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B50ED4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B5100C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B5123C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B51308.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B51398.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B51410.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B51510.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B51698.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B51760.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B51970.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B51B40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B51D9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B51EA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B51FD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B5202C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B5216C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B521E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B5227C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B52340.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B52430.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B5253C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B525E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B52654.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/EnGk_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/EnGk_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/EnGk_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B52AD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B52AF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/func_80B52D8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gk/EnGk_Draw.s")
