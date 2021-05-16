#include "z_en_arrow.h"

#define FLAGS 0x00000030

#define THIS ((EnArrow*)thisx)

void EnArrow_Init(Actor* thisx, GlobalContext* globalCtx);
void EnArrow_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnArrow_Update(Actor* thisx, GlobalContext* globalCtx);
void EnArrow_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Arrow_InitVars = {
    ACTOR_EN_ARROW,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnArrow),
    (ActorFunc)EnArrow_Init,
    (ActorFunc)EnArrow_Destroy,
    (ActorFunc)EnArrow_Update,
    (ActorFunc)EnArrow_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Arrow/EnArrow_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Arrow/EnArrow_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Arrow/func_8088A514.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Arrow/func_8088A594.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Arrow/func_8088A7D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Arrow/func_8088A894.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Arrow/func_8088AA98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Arrow/func_8088ACE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Arrow/func_8088B630.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Arrow/func_8088B6B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Arrow/EnArrow_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Arrow/func_8088B88C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Arrow/EnArrow_Draw.s")
