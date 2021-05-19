#include "z_en_bh.h"

#define FLAGS 0x00000000

#define THIS ((EnBh*)thisx)

void EnBh_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBh_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBh_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBh_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Bh_InitVars = {
    ACTOR_EN_BH,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_BH,
    sizeof(EnBh),
    (ActorFunc)EnBh_Init,
    (ActorFunc)EnBh_Destroy,
    (ActorFunc)EnBh_Update,
    (ActorFunc)EnBh_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bh_0x80C22D40/EnBh_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bh_0x80C22D40/EnBh_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bh_0x80C22D40/func_80C22DEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bh_0x80C22D40/EnBh_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bh_0x80C22D40/EnBh_Draw.asm")
