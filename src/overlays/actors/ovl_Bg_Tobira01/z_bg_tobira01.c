#include "z_bg_tobira01.h"

#define FLAGS 0x00000030

#define THIS ((BgTobira01*)thisx)

void BgTobira01_Init(Actor* thisx, GlobalContext* globalCtx);
void BgTobira01_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgTobira01_Update(Actor* thisx, GlobalContext* globalCtx);
void BgTobira01_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Bg_Tobira01_InitVars = {
    ACTOR_BG_TOBIRA01,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_SPOT11_OBJ,
    sizeof(BgTobira01),
    (ActorFunc)BgTobira01_Init,
    (ActorFunc)BgTobira01_Destroy,
    (ActorFunc)BgTobira01_Update,
    (ActorFunc)BgTobira01_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Tobira01_0x80B12430/func_80B12430.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Tobira01_0x80B12430/BgTobira01_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Tobira01_0x80B12430/BgTobira01_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Tobira01_0x80B12430/BgTobira01_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Tobira01_0x80B12430/BgTobira01_Draw.asm")
