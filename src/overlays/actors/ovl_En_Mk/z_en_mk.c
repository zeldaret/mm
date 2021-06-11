#include "z_en_mk.h"

#define FLAGS 0x00000019

#define THIS ((EnMk*)thisx)

void EnMk_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMk_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMk_Update(Actor* thisx, GlobalContext* globalCtx);
void EnMk_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Mk_InitVars = {
    ACTOR_EN_MK,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_MK,
    sizeof(EnMk),
    (ActorFunc)EnMk_Init,
    (ActorFunc)EnMk_Destroy,
    (ActorFunc)EnMk_Update,
    (ActorFunc)EnMk_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mk/func_809592E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mk/EnMk_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mk/EnMk_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mk/func_80959524.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mk/func_8095954C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mk/func_80959624.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mk/func_809596A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mk/func_80959774.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mk/func_80959844.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mk/func_80959A24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mk/func_80959C94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mk/func_80959D28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mk/func_80959E18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mk/EnMk_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mk/func_8095A150.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mk/func_8095A198.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mk/EnMk_Draw.s")
