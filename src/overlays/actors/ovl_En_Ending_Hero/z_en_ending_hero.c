#include "z_en_ending_hero.h"

#define FLAGS 0x00000009

#define THIS ((EnEndingHero*)thisx)

void EnEndingHero_Init(Actor* thisx, GlobalContext* globalCtx);
void EnEndingHero_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnEndingHero_Update(Actor* thisx, GlobalContext* globalCtx);
void EnEndingHero_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Ending_Hero_InitVars = {
    ACTOR_EN_ENDING_HERO,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_DT,
    sizeof(EnEndingHero),
    (ActorFunc)EnEndingHero_Init,
    (ActorFunc)EnEndingHero_Destroy,
    (ActorFunc)EnEndingHero_Update,
    (ActorFunc)EnEndingHero_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Ending_Hero_0x80C1E690/EnEndingHero_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ending_Hero_0x80C1E690/EnEndingHero_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ending_Hero_0x80C1E690/func_80C1E748.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ending_Hero_0x80C1E690/func_80C1E764.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ending_Hero_0x80C1E690/EnEndingHero_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ending_Hero_0x80C1E690/EnEndingHero_Draw.asm")
