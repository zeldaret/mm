#include "z_en_boj_03.h"

#define FLAGS 0x00000019

#define THIS ((EnBoj03*)thisx)

void EnBoj03_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBoj03_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBoj03_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBoj03_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Boj_03_InitVars = {
    ACTOR_EN_BOJ_03,
    ACTORTYPE_NPC,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnBoj03),
    (ActorFunc)EnBoj03_Init,
    (ActorFunc)EnBoj03_Destroy,
    (ActorFunc)EnBoj03_Update,
    (ActorFunc)EnBoj03_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Boj_03_0x809C3EA0/EnBoj03_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Boj_03_0x809C3EA0/EnBoj03_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Boj_03_0x809C3EA0/EnBoj03_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Boj_03_0x809C3EA0/EnBoj03_Draw.asm")
