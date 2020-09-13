#include "z_en_ending_hero3.h"

#define FLAGS 0x00000009

#define THIS ((EnEndingHero3*)thisx)

void EnEndingHero3_Init(Actor* thisx, GlobalContext* globalCtx);
void EnEndingHero3_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnEndingHero3_Update(Actor* thisx, GlobalContext* globalCtx);
void EnEndingHero3_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Ending_Hero3_InitVars = {
    ACTOR_EN_ENDING_HERO3,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_TORYO,
    sizeof(EnEndingHero3),
    (ActorFunc)EnEndingHero3_Init,
    (ActorFunc)EnEndingHero3_Destroy,
    (ActorFunc)EnEndingHero3_Update,
    (ActorFunc)EnEndingHero3_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Ending_Hero3_0x80C23460/EnEndingHero3_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ending_Hero3_0x80C23460/EnEndingHero3_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ending_Hero3_0x80C23460/func_80C23518.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ending_Hero3_0x80C23460/func_80C23534.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ending_Hero3_0x80C23460/EnEndingHero3_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ending_Hero3_0x80C23460/EnEndingHero3_Draw.asm")
