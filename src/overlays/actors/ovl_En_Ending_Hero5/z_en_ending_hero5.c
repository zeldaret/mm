#include "z_en_ending_hero5.h"

#define FLAGS 0x00000009

#define THIS ((EnEndingHero5*)thisx)

void EnEndingHero5_Init(Actor* thisx, GlobalContext* globalCtx);
void EnEndingHero5_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnEndingHero5_Update(Actor* thisx, GlobalContext* globalCtx);
void EnEndingHero5_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Ending_Hero5_InitVars = {
    ACTOR_EN_ENDING_HERO5,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_DAIKU,
    sizeof(EnEndingHero5),
    (ActorFunc)EnEndingHero5_Init,
    (ActorFunc)EnEndingHero5_Destroy,
    (ActorFunc)EnEndingHero5_Update,
    (ActorFunc)EnEndingHero5_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Ending_Hero5_0x80C238C0/EnEndingHero5_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ending_Hero5_0x80C238C0/EnEndingHero5_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ending_Hero5_0x80C238C0/func_80C23980.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ending_Hero5_0x80C238C0/func_80C2399C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ending_Hero5_0x80C238C0/EnEndingHero5_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ending_Hero5_0x80C238C0/func_80C23A30.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ending_Hero5_0x80C238C0/EnEndingHero5_Draw.asm")
