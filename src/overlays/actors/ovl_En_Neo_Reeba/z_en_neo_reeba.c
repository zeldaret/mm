#include "z_en_neo_reeba.h"

#define FLAGS 0x00000205

#define THIS ((EnNeoReeba*)thisx)

void EnNeoReeba_Init(Actor* thisx, GlobalContext* globalCtx);
void EnNeoReeba_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnNeoReeba_Update(Actor* thisx, GlobalContext* globalCtx);
void EnNeoReeba_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Neo_Reeba_InitVars = {
    ACTOR_EN_NEO_REEBA,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_RB,
    sizeof(EnNeoReeba),
    (ActorFunc)EnNeoReeba_Init,
    (ActorFunc)EnNeoReeba_Destroy,
    (ActorFunc)EnNeoReeba_Update,
    (ActorFunc)EnNeoReeba_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/EnNeoReeba_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/EnNeoReeba_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7CA34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7CA70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7CB3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7CB88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7CCE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7CD28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7CE34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7CE94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7CFA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7CFFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7D130.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7D150.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7D254.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7D2E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7D360.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7D398.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7D3EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7D47C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7D4FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7D5A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7D6D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7D788.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7D9B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7DC80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7DD7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7DF34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7E0BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7E260.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/EnNeoReeba_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/func_80B7E378.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Neo_Reeba/EnNeoReeba_Draw.s")
