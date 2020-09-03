#include "z_en_ending_hero2.h"

#define FLAGS 0x00000009

#define THIS ((EnEndingHero2*)thisx)

void EnEndingHero2_Init(Actor* thisx, GlobalContext* globalCtx);
void EnEndingHero2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnEndingHero2_Update(Actor* thisx, GlobalContext* globalCtx);
void EnEndingHero2_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Ending_Hero2_InitVars = {
    ACTOR_EN_ENDING_HERO2,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_BAI,
    sizeof(EnEndingHero2),
    (ActorFunc)EnEndingHero2_Init,
    (ActorFunc)EnEndingHero2_Destroy,
    (ActorFunc)EnEndingHero2_Update,
    (ActorFunc)EnEndingHero2_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Ending_Hero2_0x80C23230/EnEndingHero2_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ending_Hero2_0x80C23230/EnEndingHero2_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ending_Hero2_0x80C23230/func_80C232E8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ending_Hero2_0x80C23230/func_80C23304.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ending_Hero2_0x80C23230/EnEndingHero2_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ending_Hero2_0x80C23230/EnEndingHero2_Draw.asm")
