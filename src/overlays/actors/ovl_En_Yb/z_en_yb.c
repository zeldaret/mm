#include "z_en_yb.h"

#define FLAGS 0x02000019

#define THIS ((EnYb*)thisx)

void EnYb_Init(Actor* thisx, GlobalContext* globalCtx);
void EnYb_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnYb_Update(Actor* thisx, GlobalContext* globalCtx);
void EnYb_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Yb_InitVars = {
    ACTOR_EN_YB,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_YB,
    sizeof(EnYb),
    (ActorFunc)EnYb_Init,
    (ActorFunc)EnYb_Destroy,
    (ActorFunc)EnYb_Update,
    (ActorFunc)EnYb_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Yb/EnYb_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Yb/EnYb_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Yb/func_80BFA2FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Yb/func_80BFA350.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Yb/func_80BFA444.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Yb/func_80BFA5CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Yb/func_80BFA634.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Yb/func_80BFA67C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Yb/func_80BFA6E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Yb/func_80BFA710.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Yb/func_80BFA730.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Yb/func_80BFA868.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Yb/func_80BFA91C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Yb/func_80BFA9D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Yb/func_80BFAB4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Yb/func_80BFABF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Yb/func_80BFAC88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Yb/func_80BFAE80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Yb/EnYb_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Yb/func_80BFB074.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Yb/func_80BFB0E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Yb/EnYb_Draw.s")
