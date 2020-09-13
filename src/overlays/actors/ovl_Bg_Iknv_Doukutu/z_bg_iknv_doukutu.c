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
    ACTORTYPE_BG,
    FLAGS,
    OBJECT_IKNV_OBJ,
    sizeof(BgIknvDoukutu),
    (ActorFunc)BgIknvDoukutu_Init,
    (ActorFunc)BgIknvDoukutu_Destroy,
    (ActorFunc)BgIknvDoukutu_Update,
    (ActorFunc)BgIknvDoukutu_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Iknv_Doukutu_0x80BD6F10/BgIknvDoukutu_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Iknv_Doukutu_0x80BD6F10/BgIknvDoukutu_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Iknv_Doukutu_0x80BD6F10/func_80BD716C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Iknv_Doukutu_0x80BD6F10/func_80BD71BC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Iknv_Doukutu_0x80BD6F10/func_80BD7250.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Iknv_Doukutu_0x80BD6F10/func_80BD72BC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Iknv_Doukutu_0x80BD6F10/func_80BD7360.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Iknv_Doukutu_0x80BD6F10/func_80BD73D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Iknv_Doukutu_0x80BD6F10/BgIknvDoukutu_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Iknv_Doukutu_0x80BD6F10/BgIknvDoukutu_Draw.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Iknv_Doukutu_0x80BD6F10/func_80BD7538.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Iknv_Doukutu_0x80BD6F10/func_80BD7768.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Iknv_Doukutu_0x80BD6F10/func_80BD7820.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Iknv_Doukutu_0x80BD6F10/func_80BD78C4.asm")
