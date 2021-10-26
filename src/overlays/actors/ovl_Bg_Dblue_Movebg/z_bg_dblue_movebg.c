#include "z_bg_dblue_movebg.h"

#define FLAGS 0x00000030

#define THIS ((BgDblueMovebg*)thisx)

void BgDblueMovebg_Init(Actor* thisx, GlobalContext* globalCtx);
void BgDblueMovebg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgDblueMovebg_Update(Actor* thisx, GlobalContext* globalCtx);
void BgDblueMovebg_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Bg_Dblue_Movebg_InitVars = {
    ACTOR_BG_DBLUE_MOVEBG,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_DBLUE_OBJECT,
    sizeof(BgDblueMovebg),
    (ActorFunc)BgDblueMovebg_Init,
    (ActorFunc)BgDblueMovebg_Destroy,
    (ActorFunc)BgDblueMovebg_Update,
    (ActorFunc)BgDblueMovebg_Draw,
};

#endif

extern UNK_TYPE D_06004848;
extern UNK_TYPE D_060052B8;
extern UNK_TYPE D_06008778;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dblue_Movebg/func_80A29A80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dblue_Movebg/BgDblueMovebg_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dblue_Movebg/BgDblueMovebg_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dblue_Movebg/func_80A2A128.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dblue_Movebg/func_80A2A1E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dblue_Movebg/func_80A2A32C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dblue_Movebg/func_80A2A444.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dblue_Movebg/func_80A2A670.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dblue_Movebg/func_80A2A688.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dblue_Movebg/func_80A2A714.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dblue_Movebg/func_80A2A7F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dblue_Movebg/func_80A2AAB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dblue_Movebg/func_80A2ABD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dblue_Movebg/func_80A2AED0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dblue_Movebg/func_80A2B1A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dblue_Movebg/BgDblueMovebg_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dblue_Movebg/func_80A2B274.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dblue_Movebg/func_80A2B308.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dblue_Movebg/BgDblueMovebg_Draw.s")
