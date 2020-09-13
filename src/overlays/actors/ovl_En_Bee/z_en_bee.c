#include "z_en_bee.h"

#define FLAGS 0x00000005

#define THIS ((EnBee*)thisx)

void EnBee_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBee_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBee_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBee_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Bee_InitVars = {
    ACTOR_EN_BEE,
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_BEE,
    sizeof(EnBee),
    (ActorFunc)EnBee_Init,
    (ActorFunc)EnBee_Destroy,
    (ActorFunc)EnBee_Update,
    (ActorFunc)EnBee_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Bee_0x80B5A720/EnBee_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bee_0x80B5A720/EnBee_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bee_0x80B5A720/func_80B5A854.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bee_0x80B5A720/func_80B5A9E8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bee_0x80B5A720/func_80B5ABC4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bee_0x80B5A720/func_80B5AC3C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bee_0x80B5A720/func_80B5AF80.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bee_0x80B5A720/EnBee_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bee_0x80B5A720/EnBee_Draw.asm")
