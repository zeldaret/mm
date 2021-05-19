#include "z_bg_dblue_balance.h"

#define FLAGS 0x00000000

#define THIS ((BgDblueBalance*)thisx)

void BgDblueBalance_Init(Actor* thisx, GlobalContext* globalCtx);
void BgDblueBalance_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgDblueBalance_Update(Actor* thisx, GlobalContext* globalCtx);
void BgDblueBalance_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Bg_Dblue_Balance_InitVars = {
    ACTOR_BG_DBLUE_BALANCE,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_DBLUE_OBJECT,
    sizeof(BgDblueBalance),
    (ActorFunc)BgDblueBalance_Init,
    (ActorFunc)BgDblueBalance_Destroy,
    (ActorFunc)BgDblueBalance_Update,
    (ActorFunc)BgDblueBalance_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dblue_Balance_0x80B823B0/func_80B823B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dblue_Balance_0x80B823B0/func_80B82454.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dblue_Balance_0x80B823B0/func_80B8259C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dblue_Balance_0x80B823B0/func_80B8264C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dblue_Balance_0x80B823B0/func_80B828E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dblue_Balance_0x80B823B0/func_80B8296C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dblue_Balance_0x80B823B0/func_80B82B00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dblue_Balance_0x80B823B0/BgDblueBalance_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dblue_Balance_0x80B823B0/BgDblueBalance_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dblue_Balance_0x80B823B0/func_80B82DC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dblue_Balance_0x80B823B0/func_80B82DE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dblue_Balance_0x80B823B0/BgDblueBalance_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dblue_Balance_0x80B823B0/func_80B8330C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dblue_Balance_0x80B823B0/func_80B83344.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dblue_Balance_0x80B823B0/func_80B8335C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dblue_Balance_0x80B823B0/func_80B833A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dblue_Balance_0x80B823B0/func_80B833C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dblue_Balance_0x80B823B0/func_80B83518.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dblue_Balance_0x80B823B0/BgDblueBalance_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dblue_Balance_0x80B823B0/func_80B83758.asm")
