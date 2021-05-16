#include "z_bg_ladder.h"

#define FLAGS 0x00000010

#define THIS ((BgLadder*)thisx)

void BgLadder_Init(Actor* thisx, GlobalContext* globalCtx);
void BgLadder_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgLadder_Update(Actor* thisx, GlobalContext* globalCtx);
void BgLadder_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Bg_Ladder_InitVars = {
    ACTOR_BG_LADDER,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_LADDER,
    sizeof(BgLadder),
    (ActorFunc)BgLadder_Init,
    (ActorFunc)BgLadder_Destroy,
    (ActorFunc)BgLadder_Update,
    (ActorFunc)BgLadder_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ladder/BgLadder_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ladder/BgLadder_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ladder/func_80A4DB88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ladder/func_80A4DBD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ladder/func_80A4DC48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ladder/func_80A4DCCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ladder/BgLadder_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ladder/BgLadder_Draw.s")
