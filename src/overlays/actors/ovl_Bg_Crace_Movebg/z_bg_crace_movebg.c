/*
 * File: z_bg_crace_movebg.c
 * Overlay: ovl_Bg_Crace_Movebg
 * Description: Huge sliding doors in Deku Shrine
 */

#include "z_bg_crace_movebg.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((BgCraceMovebg*)thisx)

void BgCraceMovebg_Init(Actor* thisx, GlobalContext* globalCtx);
void BgCraceMovebg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgCraceMovebg_Update(Actor* thisx, GlobalContext* globalCtx);
void BgCraceMovebg_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Bg_Crace_Movebg_InitVars = {
    ACTOR_BG_CRACE_MOVEBG,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_CRACE_OBJECT,
    sizeof(BgCraceMovebg),
    (ActorFunc)BgCraceMovebg_Init,
    (ActorFunc)BgCraceMovebg_Destroy,
    (ActorFunc)BgCraceMovebg_Update,
    (ActorFunc)BgCraceMovebg_Draw,
};

#endif

extern UNK_TYPE D_060003A0;
extern UNK_TYPE D_06000E00;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Crace_Movebg/BgCraceMovebg_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Crace_Movebg/func_80A7090C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Crace_Movebg/func_80A70970.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Crace_Movebg/func_80A7099C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Crace_Movebg/func_80A709E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Crace_Movebg/func_80A70A08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Crace_Movebg/func_80A70A84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Crace_Movebg/func_80A70A9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Crace_Movebg/BgCraceMovebg_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Crace_Movebg/BgCraceMovebg_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Crace_Movebg/func_80A70C04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Crace_Movebg/func_80A70D74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Crace_Movebg/func_80A70DA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Crace_Movebg/func_80A70E2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Crace_Movebg/func_80A70E70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Crace_Movebg/func_80A70F14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Crace_Movebg/func_80A70F2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Crace_Movebg/func_80A70FF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Crace_Movebg/func_80A71040.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Crace_Movebg/BgCraceMovebg_Draw.s")
