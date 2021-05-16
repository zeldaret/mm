#include "z_bg_dy_yoseizo.h"

#define FLAGS 0x02000030

#define THIS ((BgDyYoseizo*)thisx)

void BgDyYoseizo_Init(Actor* thisx, GlobalContext* globalCtx);
void BgDyYoseizo_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgDyYoseizo_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Bg_Dy_Yoseizo_InitVars = {
    ACTOR_BG_DY_YOSEIZO,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_DY_OBJ,
    sizeof(BgDyYoseizo),
    (ActorFunc)BgDyYoseizo_Init,
    (ActorFunc)BgDyYoseizo_Destroy,
    (ActorFunc)BgDyYoseizo_Update,
    (ActorFunc)NULL
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dy_Yoseizo/BgDyYoseizo_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dy_Yoseizo/BgDyYoseizo_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dy_Yoseizo/func_80A0A96C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dy_Yoseizo/func_80A0A9E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dy_Yoseizo/func_80A0AA40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dy_Yoseizo/func_80A0AD50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dy_Yoseizo/func_80A0AE1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dy_Yoseizo/func_80A0AFDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dy_Yoseizo/func_80A0B078.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dy_Yoseizo/func_80A0B184.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dy_Yoseizo/func_80A0B290.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dy_Yoseizo/func_80A0B35C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dy_Yoseizo/func_80A0B500.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dy_Yoseizo/func_80A0B5F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dy_Yoseizo/func_80A0B75C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dy_Yoseizo/func_80A0B834.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dy_Yoseizo/func_80A0B8CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dy_Yoseizo/func_80A0BB08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dy_Yoseizo/BgDyYoseizo_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dy_Yoseizo/func_80A0BCD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dy_Yoseizo/func_80A0BD40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dy_Yoseizo/func_80A0BE60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dy_Yoseizo/func_80A0BF70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dy_Yoseizo/func_80A0C270.s")
