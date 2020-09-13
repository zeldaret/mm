#include "z_en_boj_05.h"

#define FLAGS 0x00000019

#define THIS ((EnBoj05*)thisx)

void EnBoj05_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBoj05_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBoj05_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBoj05_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Boj_05_InitVars = {
    ACTOR_EN_BOJ_05,
    ACTORTYPE_NPC,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnBoj05),
    (ActorFunc)EnBoj05_Init,
    (ActorFunc)EnBoj05_Destroy,
    (ActorFunc)EnBoj05_Update,
    (ActorFunc)EnBoj05_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Boj_05_0x80A0C780/EnBoj05_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Boj_05_0x80A0C780/EnBoj05_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Boj_05_0x80A0C780/EnBoj05_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Boj_05_0x80A0C780/EnBoj05_Draw.asm")
