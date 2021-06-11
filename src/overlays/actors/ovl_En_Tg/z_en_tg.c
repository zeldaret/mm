#include "z_en_tg.h"

#define FLAGS 0x00000009

#define THIS ((EnTg*)thisx)

void EnTg_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTg_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTg_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Tg_InitVars = {
    ACTOR_EN_TG,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_MU,
    sizeof(EnTg),
    (ActorFunc)EnTg_Init,
    (ActorFunc)EnTg_Destroy,
    (ActorFunc)EnTg_Update,
    (ActorFunc)EnTg_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/func_8098F800.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/func_8098F8A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/func_8098F928.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/EnTg_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/EnTg_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/func_8098FA70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/EnTg_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/func_8098FBB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/func_8098FBD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/EnTg_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/func_8098FD50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/func_8098FEA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tg/func_8099000C.s")
