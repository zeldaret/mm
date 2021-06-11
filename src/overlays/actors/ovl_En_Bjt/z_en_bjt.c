#include "z_en_bjt.h"

#define FLAGS 0x00000009

#define THIS ((EnBjt*)thisx)

void EnBjt_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBjt_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBjt_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBjt_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Bjt_InitVars = {
    ACTOR_EN_BJT,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_BJT,
    sizeof(EnBjt),
    (ActorFunc)EnBjt_Init,
    (ActorFunc)EnBjt_Destroy,
    (ActorFunc)EnBjt_Update,
    (ActorFunc)EnBjt_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bjt/func_80BFD2E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bjt/func_80BFD30C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bjt/func_80BFD3A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bjt/func_80BFD434.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bjt/func_80BFD4FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bjt/func_80BFD5E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bjt/func_80BFD6BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bjt/func_80BFD8F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bjt/func_80BFD984.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bjt/func_80BFDA48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bjt/func_80BFDAE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bjt/EnBjt_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bjt/EnBjt_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bjt/EnBjt_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bjt/EnBjt_Draw.s")
