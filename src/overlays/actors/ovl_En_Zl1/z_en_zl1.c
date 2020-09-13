#include "z_en_zl1.h"

#define FLAGS 0x00000019

#define THIS ((EnZl1*)thisx)

void EnZl1_Init(Actor* thisx, GlobalContext* globalCtx);
void EnZl1_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnZl1_Update(Actor* thisx, GlobalContext* globalCtx);
void EnZl1_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Zl1_InitVars = {
    ACTOR_EN_ZL1,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_ZL1,
    sizeof(EnZl1),
    (ActorFunc)EnZl1_Init,
    (ActorFunc)EnZl1_Destroy,
    (ActorFunc)EnZl1_Update,
    (ActorFunc)EnZl1_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Zl1_0x8089ED90/EnZl1_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zl1_0x8089ED90/EnZl1_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zl1_0x8089ED90/EnZl1_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zl1_0x8089ED90/EnZl1_Draw.asm")
