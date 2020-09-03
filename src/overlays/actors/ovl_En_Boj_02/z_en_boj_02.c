#include "z_en_boj_02.h"

#define FLAGS 0x00000019

#define THIS ((EnBoj02*)thisx)

void EnBoj02_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBoj02_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBoj02_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBoj02_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Boj_02_InitVars = {
    ACTOR_EN_BOJ_02,
    ACTORTYPE_NPC,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnBoj02),
    (ActorFunc)EnBoj02_Init,
    (ActorFunc)EnBoj02_Destroy,
    (ActorFunc)EnBoj02_Update,
    (ActorFunc)EnBoj02_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Boj_02_0x809C3E10/EnBoj02_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Boj_02_0x809C3E10/EnBoj02_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Boj_02_0x809C3E10/EnBoj02_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Boj_02_0x809C3E10/EnBoj02_Draw.asm")
