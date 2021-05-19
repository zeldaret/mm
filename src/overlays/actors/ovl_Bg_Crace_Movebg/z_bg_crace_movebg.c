#include "z_bg_crace_movebg.h"

#define FLAGS 0x00000010

#define THIS ((BgCraceMovebg*)thisx)

void BgCraceMovebg_Init(Actor* thisx, GlobalContext* globalCtx);
void BgCraceMovebg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgCraceMovebg_Update(Actor* thisx, GlobalContext* globalCtx);
void BgCraceMovebg_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
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
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Crace_Movebg_0x80A706F0/BgCraceMovebg_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Crace_Movebg_0x80A706F0/func_80A7090C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Crace_Movebg_0x80A706F0/func_80A70970.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Crace_Movebg_0x80A706F0/func_80A7099C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Crace_Movebg_0x80A706F0/func_80A709E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Crace_Movebg_0x80A706F0/func_80A70A08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Crace_Movebg_0x80A706F0/func_80A70A84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Crace_Movebg_0x80A706F0/func_80A70A9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Crace_Movebg_0x80A706F0/BgCraceMovebg_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Crace_Movebg_0x80A706F0/BgCraceMovebg_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Crace_Movebg_0x80A706F0/func_80A70C04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Crace_Movebg_0x80A706F0/func_80A70D74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Crace_Movebg_0x80A706F0/func_80A70DA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Crace_Movebg_0x80A706F0/func_80A70E2C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Crace_Movebg_0x80A706F0/func_80A70E70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Crace_Movebg_0x80A706F0/func_80A70F14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Crace_Movebg_0x80A706F0/func_80A70F2C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Crace_Movebg_0x80A706F0/func_80A70FF4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Crace_Movebg_0x80A706F0/func_80A71040.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Crace_Movebg_0x80A706F0/BgCraceMovebg_Draw.asm")
