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
    ACTORTYPE_BG,
    FLAGS,
    OBJECT_CRACE_OBJECT,
    sizeof(BgCraceMovebg),
    (ActorFunc)BgCraceMovebg_Init,
    (ActorFunc)BgCraceMovebg_Destroy,
    (ActorFunc)BgCraceMovebg_Update,
    (ActorFunc)BgCraceMovebg_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Crace_Movebg_0x80A706F0/BgCraceMovebg_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Crace_Movebg_0x80A706F0/func_80A7090C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Crace_Movebg_0x80A706F0/func_80A70970.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Crace_Movebg_0x80A706F0/func_80A7099C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Crace_Movebg_0x80A706F0/func_80A709E4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Crace_Movebg_0x80A706F0/func_80A70A08.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Crace_Movebg_0x80A706F0/func_80A70A84.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Crace_Movebg_0x80A706F0/func_80A70A9C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Crace_Movebg_0x80A706F0/BgCraceMovebg_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Crace_Movebg_0x80A706F0/BgCraceMovebg_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Crace_Movebg_0x80A706F0/func_80A70C04.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Crace_Movebg_0x80A706F0/func_80A70D74.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Crace_Movebg_0x80A706F0/func_80A70DA8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Crace_Movebg_0x80A706F0/func_80A70E2C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Crace_Movebg_0x80A706F0/func_80A70E70.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Crace_Movebg_0x80A706F0/func_80A70F14.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Crace_Movebg_0x80A706F0/func_80A70F2C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Crace_Movebg_0x80A706F0/func_80A70FF4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Crace_Movebg_0x80A706F0/func_80A71040.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Crace_Movebg_0x80A706F0/BgCraceMovebg_Draw.asm")
