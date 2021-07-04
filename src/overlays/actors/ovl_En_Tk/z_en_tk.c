#include "z_en_tk.h"

#define FLAGS 0x00000009

#define THIS ((EnTk*)thisx)

void EnTk_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTk_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTk_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTk_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Tk_InitVars = {
    ACTOR_EN_TK,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_TK,
    sizeof(EnTk),
    (ActorFunc)EnTk_Init,
    (ActorFunc)EnTk_Destroy,
    (ActorFunc)EnTk_Update,
    (ActorFunc)EnTk_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/func_80AEC460.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/func_80AEC524.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/func_80AEC658.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/EnTk_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/EnTk_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/func_80AECA3C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/func_80AECA90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/func_80AECB0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/func_80AECB6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/func_80AECE0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/func_80AECE60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/func_80AED354.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/func_80AED38C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/func_80AED4F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/func_80AED544.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/func_80AED610.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/func_80AED898.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/func_80AED940.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/func_80AEDBEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/func_80AEDC4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/func_80AEDCBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/func_80AEDD4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/func_80AEDDA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/func_80AEDE10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/func_80AEDF5C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/func_80AEE2A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/func_80AEE2C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/func_80AEE300.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/func_80AEE374.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/func_80AEE414.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/func_80AEE478.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/func_80AEE4D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/func_80AEE650.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/func_80AEE6B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/func_80AEE784.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/func_80AEE7E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/func_80AEE86C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/func_80AEE9B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/func_80AEEA4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/func_80AEEAD4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/func_80AEEB88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/func_80AEED38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/func_80AEF048.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/func_80AEF094.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/func_80AEF15C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/func_80AEF1B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/func_80AEF1C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/func_80AEF210.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/func_80AEF220.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/func_80AEF278.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/func_80AEF2C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/func_80AEF2D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/EnTk_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/func_80AEF5F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/func_80AEF65C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/func_80AEF6A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tk_0x80AEC460/EnTk_Draw.asm")
