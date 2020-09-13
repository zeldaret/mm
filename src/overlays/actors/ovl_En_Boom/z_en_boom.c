#include "z_en_boom.h"

#define FLAGS 0x00000030

#define THIS ((EnBoom*)thisx)

void EnBoom_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBoom_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBoom_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBoom_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Boom_InitVars = {
    ACTOR_EN_BOOM,
    ACTORTYPE_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnBoom),
    (ActorFunc)EnBoom_Init,
    (ActorFunc)EnBoom_Destroy,
    (ActorFunc)EnBoom_Update,
    (ActorFunc)EnBoom_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Boom_0x808A24D0/func_808A24D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Boom_0x808A24D0/func_808A24DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Boom_0x808A24D0/EnBoom_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Boom_0x808A24D0/EnBoom_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Boom_0x808A24D0/func_808A2918.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Boom_0x808A24D0/EnBoom_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Boom_0x808A24D0/EnBoom_Draw.asm")
