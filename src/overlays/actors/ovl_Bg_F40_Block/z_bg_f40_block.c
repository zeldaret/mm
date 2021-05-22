#include "z_bg_f40_block.h"

#define FLAGS 0x00000010

#define THIS ((BgF40Block*)thisx)

void BgF40Block_Init(Actor* thisx, GlobalContext* globalCtx);
void BgF40Block_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgF40Block_Update(Actor* thisx, GlobalContext* globalCtx);
void BgF40Block_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Bg_F40_Block_InitVars = {
    ACTOR_BG_F40_BLOCK,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_F40_OBJ,
    sizeof(BgF40Block),
    (ActorFunc)BgF40Block_Init,
    (ActorFunc)BgF40Block_Destroy,
    (ActorFunc)BgF40Block_Update,
    (ActorFunc)BgF40Block_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_F40_Block_0x80BC3980/func_80BC3980.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_F40_Block_0x80BC3980/func_80BC3A2C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_F40_Block_0x80BC3980/func_80BC3B00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_F40_Block_0x80BC3980/func_80BC3CA4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_F40_Block_0x80BC3980/func_80BC3D08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_F40_Block_0x80BC3980/func_80BC4038.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_F40_Block_0x80BC3980/BgF40Block_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_F40_Block_0x80BC3980/BgF40Block_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_F40_Block_0x80BC3980/func_80BC41AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_F40_Block_0x80BC3980/func_80BC4228.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_F40_Block_0x80BC3980/func_80BC4344.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_F40_Block_0x80BC3980/func_80BC4380.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_F40_Block_0x80BC3980/func_80BC43CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_F40_Block_0x80BC3980/func_80BC4448.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_F40_Block_0x80BC3980/func_80BC44F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_F40_Block_0x80BC3980/func_80BC4530.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_F40_Block_0x80BC3980/func_80BC457C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_F40_Block_0x80BC3980/BgF40Block_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_F40_Block_0x80BC3980/BgF40Block_Draw.asm")
