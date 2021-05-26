#include "z_bg_f40_flift.h"

#define FLAGS 0x00000010

#define THIS ((BgF40Flift*)thisx)

void BgF40Flift_Init(Actor* thisx, GlobalContext* globalCtx);
void BgF40Flift_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgF40Flift_Update(Actor* thisx, GlobalContext* globalCtx);
void BgF40Flift_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Bg_F40_Flift_InitVars = {
    ACTOR_BG_F40_FLIFT,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_F40_OBJ,
    sizeof(BgF40Flift),
    (ActorFunc)BgF40Flift_Init,
    (ActorFunc)BgF40Flift_Destroy,
    (ActorFunc)BgF40Flift_Update,
    (ActorFunc)BgF40Flift_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_F40_Flift_0x808D7550/BgF40Flift_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_F40_Flift_0x808D7550/BgF40Flift_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_F40_Flift_0x808D7550/func_808D75F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_F40_Flift_0x808D7550/func_808D7714.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_F40_Flift_0x808D7550/BgF40Flift_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_F40_Flift_0x808D7550/BgF40Flift_Draw.asm")
