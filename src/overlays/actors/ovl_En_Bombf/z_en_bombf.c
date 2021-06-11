#include "z_en_bombf.h"

#define FLAGS 0x00000011

#define THIS ((EnBombf*)thisx)

void EnBombf_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBombf_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBombf_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBombf_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Bombf_InitVars = {
    ACTOR_EN_BOMBF,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_BOMBF,
    sizeof(EnBombf),
    (ActorFunc)EnBombf_Init,
    (ActorFunc)EnBombf_Destroy,
    (ActorFunc)EnBombf_Update,
    (ActorFunc)EnBombf_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombf/func_808AE8C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombf/EnBombf_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombf/EnBombf_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombf/func_808AEAB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombf/func_808AEAE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombf/func_808AEE3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombf/func_808AEF68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombf/func_808AEFD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombf/EnBombf_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombf/func_808AF86C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombf/EnBombf_Draw.s")
