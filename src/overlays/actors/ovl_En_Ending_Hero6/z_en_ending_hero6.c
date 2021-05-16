#include "z_en_ending_hero6.h"

#define FLAGS 0x00000009

#define THIS ((EnEndingHero6*)thisx)

void EnEndingHero6_Init(Actor* thisx, GlobalContext* globalCtx);
void EnEndingHero6_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnEndingHero6_Update(Actor* thisx, GlobalContext* globalCtx);
void EnEndingHero6_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Ending_Hero6_InitVars = {
    ACTOR_EN_ENDING_HERO6,
    ACTORCAT_NPC,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnEndingHero6),
    (ActorFunc)EnEndingHero6_Init,
    (ActorFunc)EnEndingHero6_Destroy,
    (ActorFunc)EnEndingHero6_Update,
    (ActorFunc)EnEndingHero6_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ending_Hero6/EnEndingHero6_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ending_Hero6/EnEndingHero6_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ending_Hero6/func_80C23D60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ending_Hero6/func_80C23DDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ending_Hero6/func_80C23E18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ending_Hero6/EnEndingHero6_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ending_Hero6/func_80C23F14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ending_Hero6/EnEndingHero6_Draw.s")
