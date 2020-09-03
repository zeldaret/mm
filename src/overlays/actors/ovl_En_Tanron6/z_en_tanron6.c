#include "z_en_tanron6.h"

#define FLAGS 0x00000005

#define THIS ((EnTanron6*)thisx)

void EnTanron6_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTanron6_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTanron6_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTanron6_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Tanron6_InitVars = {
    ACTOR_EN_TANRON6,
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_TANRON5,
    sizeof(EnTanron6),
    (ActorFunc)EnTanron6_Init,
    (ActorFunc)EnTanron6_Destroy,
    (ActorFunc)EnTanron6_Update,
    (ActorFunc)EnTanron6_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Tanron6_0x80BE6040/EnTanron6_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tanron6_0x80BE6040/EnTanron6_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tanron6_0x80BE6040/func_80BE60BC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tanron6_0x80BE6040/func_80BE60D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tanron6_0x80BE6040/EnTanron6_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tanron6_0x80BE6040/EnTanron6_Draw.asm")
