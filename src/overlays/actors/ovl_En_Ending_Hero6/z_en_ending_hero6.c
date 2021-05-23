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
    (ActorFunc)EnEndingHero6_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ending_Hero6_0x80C23C90/EnEndingHero6_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ending_Hero6_0x80C23C90/EnEndingHero6_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ending_Hero6_0x80C23C90/func_80C23D60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ending_Hero6_0x80C23C90/func_80C23DDC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ending_Hero6_0x80C23C90/func_80C23E18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ending_Hero6_0x80C23C90/EnEndingHero6_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ending_Hero6_0x80C23C90/func_80C23F14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ending_Hero6_0x80C23C90/EnEndingHero6_Draw.asm")
