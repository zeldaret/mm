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
    (ActorFunc)NULL,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dy_Yoseizo_0x80A0A8A0/BgDyYoseizo_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dy_Yoseizo_0x80A0A8A0/BgDyYoseizo_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dy_Yoseizo_0x80A0A8A0/func_80A0A96C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dy_Yoseizo_0x80A0A8A0/func_80A0A9E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dy_Yoseizo_0x80A0A8A0/func_80A0AA40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dy_Yoseizo_0x80A0A8A0/func_80A0AD50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dy_Yoseizo_0x80A0A8A0/func_80A0AE1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dy_Yoseizo_0x80A0A8A0/func_80A0AFDC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dy_Yoseizo_0x80A0A8A0/func_80A0B078.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dy_Yoseizo_0x80A0A8A0/func_80A0B184.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dy_Yoseizo_0x80A0A8A0/func_80A0B290.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dy_Yoseizo_0x80A0A8A0/func_80A0B35C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dy_Yoseizo_0x80A0A8A0/func_80A0B500.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dy_Yoseizo_0x80A0A8A0/func_80A0B5F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dy_Yoseizo_0x80A0A8A0/func_80A0B75C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dy_Yoseizo_0x80A0A8A0/func_80A0B834.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dy_Yoseizo_0x80A0A8A0/func_80A0B8CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dy_Yoseizo_0x80A0A8A0/func_80A0BB08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dy_Yoseizo_0x80A0A8A0/BgDyYoseizo_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dy_Yoseizo_0x80A0A8A0/func_80A0BCD8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dy_Yoseizo_0x80A0A8A0/func_80A0BD40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dy_Yoseizo_0x80A0A8A0/func_80A0BE60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dy_Yoseizo_0x80A0A8A0/func_80A0BF70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dy_Yoseizo_0x80A0A8A0/func_80A0C270.asm")
