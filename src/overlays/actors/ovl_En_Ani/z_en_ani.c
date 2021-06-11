#include "z_en_ani.h"

#define FLAGS 0x00000009

#define THIS ((EnAni*)thisx)

void EnAni_Init(Actor* thisx, GlobalContext* globalCtx);
void EnAni_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnAni_Update(Actor* thisx, GlobalContext* globalCtx);
void EnAni_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Ani_InitVars = {
    ACTOR_EN_ANI,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_ANI,
    sizeof(EnAni),
    (ActorFunc)EnAni_Init,
    (ActorFunc)EnAni_Destroy,
    (ActorFunc)EnAni_Update,
    (ActorFunc)EnAni_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ani/func_809679D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ani/func_80967A48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ani/func_80967AB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ani/EnAni_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ani/EnAni_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ani/func_80967D20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ani/func_80967DA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ani/func_80967DCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ani/func_80967E34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ani/func_80967E90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ani/func_80967F20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ani/func_80967FA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ani/func_809680B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ani/func_80968164.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ani/EnAni_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ani/func_80968504.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ani/func_8096854C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ani/EnAni_Draw.s")
