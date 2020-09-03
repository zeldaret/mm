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
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_ANI,
    sizeof(EnAni),
    (ActorFunc)EnAni_Init,
    (ActorFunc)EnAni_Destroy,
    (ActorFunc)EnAni_Update,
    (ActorFunc)EnAni_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Ani_0x809679D0/func_809679D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ani_0x809679D0/func_80967A48.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ani_0x809679D0/func_80967AB4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ani_0x809679D0/EnAni_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ani_0x809679D0/EnAni_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ani_0x809679D0/func_80967D20.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ani_0x809679D0/func_80967DA0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ani_0x809679D0/func_80967DCC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ani_0x809679D0/func_80967E34.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ani_0x809679D0/func_80967E90.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ani_0x809679D0/func_80967F20.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ani_0x809679D0/func_80967FA4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ani_0x809679D0/func_809680B0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ani_0x809679D0/func_80968164.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ani_0x809679D0/EnAni_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ani_0x809679D0/func_80968504.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ani_0x809679D0/func_8096854C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ani_0x809679D0/EnAni_Draw.asm")
