#include "z_en_encount4.h"

#define FLAGS 0x08000010

#define THIS ((EnEncount4*)thisx)

void EnEncount4_Init(Actor* thisx, GlobalContext* globalCtx);
void EnEncount4_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnEncount4_Update(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Encount4_InitVars = {
    ACTOR_EN_ENCOUNT4,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnEncount4),
    (ActorFunc)EnEncount4_Init,
    (ActorFunc)EnEncount4_Destroy,
    (ActorFunc)EnEncount4_Update,
    (ActorFunc)NULL,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Encount4/EnEncount4_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Encount4/EnEncount4_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Encount4/func_809C3FD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Encount4/func_809C4078.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Encount4/func_809C42A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Encount4/func_809C4598.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Encount4/func_809C464C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Encount4/EnEncount4_Update.s")
