#include "z_bg_iknv_doukutu.h"

#define FLAGS 0x00000030

#define THIS ((BgIknvDoukutu*)thisx)

void BgIknvDoukutu_Init(Actor* thisx, GlobalContext* globalCtx);
void BgIknvDoukutu_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgIknvDoukutu_Update(Actor* thisx, GlobalContext* globalCtx);
void BgIknvDoukutu_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Bg_Iknv_Doukutu_InitVars = {
    ACTOR_BG_IKNV_DOUKUTU,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_IKNV_OBJ,
    sizeof(BgIknvDoukutu),
    (ActorFunc)BgIknvDoukutu_Init,
    (ActorFunc)BgIknvDoukutu_Destroy,
    (ActorFunc)BgIknvDoukutu_Update,
    (ActorFunc)BgIknvDoukutu_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Iknv_Doukutu_0x80BD6F10/BgIknvDoukutu_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Iknv_Doukutu_0x80BD6F10/BgIknvDoukutu_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Iknv_Doukutu_0x80BD6F10/func_80BD716C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Iknv_Doukutu_0x80BD6F10/func_80BD71BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Iknv_Doukutu_0x80BD6F10/func_80BD7250.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Iknv_Doukutu_0x80BD6F10/func_80BD72BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Iknv_Doukutu_0x80BD6F10/func_80BD7360.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Iknv_Doukutu_0x80BD6F10/func_80BD73D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Iknv_Doukutu_0x80BD6F10/BgIknvDoukutu_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Iknv_Doukutu_0x80BD6F10/BgIknvDoukutu_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Iknv_Doukutu_0x80BD6F10/func_80BD7538.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Iknv_Doukutu_0x80BD6F10/func_80BD7768.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Iknv_Doukutu_0x80BD6F10/func_80BD7820.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Iknv_Doukutu_0x80BD6F10/func_80BD78C4.asm")
