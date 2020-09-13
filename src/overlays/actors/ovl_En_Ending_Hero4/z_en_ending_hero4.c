#include "z_en_ending_hero4.h"

#define FLAGS 0x00000009

#define THIS ((EnEndingHero4*)thisx)

void EnEndingHero4_Init(Actor* thisx, GlobalContext* globalCtx);
void EnEndingHero4_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnEndingHero4_Update(Actor* thisx, GlobalContext* globalCtx);
void EnEndingHero4_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Ending_Hero4_InitVars = {
    ACTOR_EN_ENDING_HERO4,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_SDN,
    sizeof(EnEndingHero4),
    (ActorFunc)EnEndingHero4_Init,
    (ActorFunc)EnEndingHero4_Destroy,
    (ActorFunc)EnEndingHero4_Update,
    (ActorFunc)EnEndingHero4_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Ending_Hero4_0x80C23690/EnEndingHero4_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ending_Hero4_0x80C23690/EnEndingHero4_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ending_Hero4_0x80C23690/func_80C23748.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ending_Hero4_0x80C23690/func_80C23764.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ending_Hero4_0x80C23690/EnEndingHero4_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ending_Hero4_0x80C23690/EnEndingHero4_Draw.asm")
