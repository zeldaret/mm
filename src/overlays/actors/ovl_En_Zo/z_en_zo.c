#include "z_en_zo.h"

#define FLAGS 0x00000019

#define THIS ((EnZo*)thisx)

void EnZo_Init(Actor* thisx, GlobalContext* globalCtx);
void EnZo_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnZo_Update(Actor* thisx, GlobalContext* globalCtx);
void EnZo_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Zo_InitVars = {
    ACTOR_EN_ZO,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_ZO,
    sizeof(EnZo),
    (ActorFunc)EnZo_Init,
    (ActorFunc)EnZo_Destroy,
    (ActorFunc)EnZo_Update,
    (ActorFunc)EnZo_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zo/func_8099E790.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zo/func_8099E858.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zo/func_8099E96C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zo/func_8099E9E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zo/func_8099EA60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zo/func_8099EBD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zo/func_8099EC50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zo/func_8099ED4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zo/func_8099EE24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zo/EnZo_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zo/EnZo_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zo/EnZo_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zo/func_8099EFF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zo/func_8099F15C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zo/EnZo_Draw.s")
