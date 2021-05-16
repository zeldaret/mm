#include "z_bg_lbfshot.h"

#define FLAGS 0x00000000

#define THIS ((BgLbfshot*)thisx)

void BgLbfshot_Init(Actor* thisx, GlobalContext* globalCtx);
void BgLbfshot_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgLbfshot_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Bg_Lbfshot_InitVars = {
    ACTOR_BG_LBFSHOT,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_LBFSHOT,
    sizeof(BgLbfshot),
    (ActorFunc)BgLbfshot_Init,
    (ActorFunc)BgLbfshot_Destroy,
    (ActorFunc)Actor_NoOp,
    (ActorFunc)BgLbfshot_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Lbfshot/BgLbfshot_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Lbfshot/BgLbfshot_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Lbfshot/BgLbfshot_Draw.s")
