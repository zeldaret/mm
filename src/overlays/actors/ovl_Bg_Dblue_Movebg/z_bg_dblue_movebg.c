#include "z_bg_dblue_movebg.h"

#define FLAGS 0x00000030

#define THIS ((BgDblueMovebg*)thisx)

void BgDblueMovebg_Init(Actor* thisx, GlobalContext* globalCtx);
void BgDblueMovebg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgDblueMovebg_Update(Actor* thisx, GlobalContext* globalCtx);
void BgDblueMovebg_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Bg_Dblue_Movebg_InitVars = {
    ACTOR_BG_DBLUE_MOVEBG,
    ACTORTYPE_BG,
    FLAGS,
    OBJECT_DBLUE_OBJECT,
    sizeof(BgDblueMovebg),
    (ActorFunc)BgDblueMovebg_Init,
    (ActorFunc)BgDblueMovebg_Destroy,
    (ActorFunc)BgDblueMovebg_Update,
    (ActorFunc)BgDblueMovebg_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Dblue_Movebg_0x80A29A80/func_80A29A80.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Dblue_Movebg_0x80A29A80/BgDblueMovebg_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Dblue_Movebg_0x80A29A80/BgDblueMovebg_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Dblue_Movebg_0x80A29A80/func_80A2A128.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Dblue_Movebg_0x80A29A80/func_80A2A1E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Dblue_Movebg_0x80A29A80/func_80A2A32C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Dblue_Movebg_0x80A29A80/func_80A2A444.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Dblue_Movebg_0x80A29A80/func_80A2A670.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Dblue_Movebg_0x80A29A80/func_80A2A688.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Dblue_Movebg_0x80A29A80/func_80A2A714.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Dblue_Movebg_0x80A29A80/func_80A2A7F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Dblue_Movebg_0x80A29A80/func_80A2AAB8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Dblue_Movebg_0x80A29A80/func_80A2ABD0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Dblue_Movebg_0x80A29A80/func_80A2AED0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Dblue_Movebg_0x80A29A80/func_80A2B1A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Dblue_Movebg_0x80A29A80/BgDblueMovebg_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Dblue_Movebg_0x80A29A80/func_80A2B274.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Dblue_Movebg_0x80A29A80/func_80A2B308.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Dblue_Movebg_0x80A29A80/BgDblueMovebg_Draw.asm")
