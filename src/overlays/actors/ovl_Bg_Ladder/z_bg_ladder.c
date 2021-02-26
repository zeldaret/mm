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
    (ActorFunc)BgLadder_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ladder_0x80A4D9F0/BgLadder_Init.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ladder_0x80A4D9F0/BgLadder_Destroy.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ladder_0x80A4D9F0/func_80A4DB88.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ladder_0x80A4D9F0/func_80A4DBD8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ladder_0x80A4D9F0/func_80A4DC48.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ladder_0x80A4D9F0/func_80A4DCCC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ladder_0x80A4D9F0/BgLadder_Update.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Bg_Ladder_0x80A4D9F0/BgLadder_Draw.asm")
