#include "z_en_ms.h"

#define FLAGS 0x00000009

#define THIS ((EnMs*)thisx)

void EnMs_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMs_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMs_Update(Actor* thisx, GlobalContext* globalCtx);
void EnMs_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Ms_InitVars = {
    ACTOR_EN_MS,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_MS,
    sizeof(EnMs),
    (ActorFunc)EnMs_Init,
    (ActorFunc)EnMs_Destroy,
    (ActorFunc)EnMs_Update,
    (ActorFunc)EnMs_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ms/EnMs_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ms/EnMs_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ms/func_80952734.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ms/func_809527F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ms/func_809529AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ms/func_80952A1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ms/EnMs_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ms/EnMs_Draw.s")
