#include "z_bg_inibs_movebg.h"

#define FLAGS 0x00000030

#define THIS ((BgInibsMovebg*)thisx)

void BgInibsMovebg_Init(Actor* thisx, GlobalContext* globalCtx);
void BgInibsMovebg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgInibsMovebg_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0

const ActorInit Bg_Inibs_Movebg_InitVars = {
    ACTOR_BG_INIBS_MOVEBG,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_INIBS_OBJECT,
    sizeof(BgInibsMovebg),
    (ActorFunc)BgInibsMovebg_Init,
    (ActorFunc)BgInibsMovebg_Destroy,
    (ActorFunc)Actor_Noop,
    (ActorFunc)BgInibsMovebg_Draw,
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80B96578[] = {
    ICHAIN_VEC3F_DIV1000(scale, 1000, ICHAIN_STOP),
};

#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Inibs_Movebg_0x80B96410/BgInibsMovebg_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Inibs_Movebg_0x80B96410/BgInibsMovebg_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Inibs_Movebg_0x80B96410/BgInibsMovebg_Draw.asm")
