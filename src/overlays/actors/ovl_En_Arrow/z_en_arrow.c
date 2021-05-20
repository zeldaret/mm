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
    (ActorFunc)EnArrow_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Arrow_0x8088A240/EnArrow_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Arrow_0x8088A240/EnArrow_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Arrow_0x8088A240/func_8088A514.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Arrow_0x8088A240/func_8088A594.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Arrow_0x8088A240/func_8088A7D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Arrow_0x8088A240/func_8088A894.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Arrow_0x8088A240/func_8088AA98.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Arrow_0x8088A240/func_8088ACE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Arrow_0x8088A240/func_8088B630.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Arrow_0x8088A240/func_8088B6B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Arrow_0x8088A240/EnArrow_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Arrow_0x8088A240/func_8088B88C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Arrow_0x8088A240/EnArrow_Draw.asm")
