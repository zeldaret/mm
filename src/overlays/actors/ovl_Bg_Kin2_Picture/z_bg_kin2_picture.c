#include "z_bg_kin2_picture.h"

#define FLAGS 0x00000000

#define THIS ((BgKin2Picture*)thisx)

void BgKin2Picture_Init(Actor* thisx, GlobalContext* globalCtx);
void BgKin2Picture_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgKin2Picture_Update(Actor* thisx, GlobalContext* globalCtx);
void BgKin2Picture_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Bg_Kin2_Picture_InitVars = {
    ACTOR_BG_KIN2_PICTURE,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_KIN2_OBJ,
    sizeof(BgKin2Picture),
    (ActorFunc)BgKin2Picture_Init,
    (ActorFunc)BgKin2Picture_Destroy,
    (ActorFunc)BgKin2Picture_Update,
    (ActorFunc)BgKin2Picture_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Picture_0x80B6EFA0/func_80B6EFA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Picture_0x80B6EFA0/func_80B6EFEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Picture_0x80B6EFA0/func_80B6F098.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Picture_0x80B6EFA0/BgKin2Picture_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Picture_0x80B6EFA0/BgKin2Picture_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Picture_0x80B6EFA0/func_80B6F4C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Picture_0x80B6EFA0/func_80B6F4D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Picture_0x80B6EFA0/func_80B6F5A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Picture_0x80B6EFA0/func_80B6F5B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Picture_0x80B6EFA0/func_80B6F61C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Picture_0x80B6EFA0/func_80B6F640.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Picture_0x80B6EFA0/func_80B6F708.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Picture_0x80B6EFA0/func_80B6F72C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Picture_0x80B6EFA0/func_80B6F8F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Picture_0x80B6EFA0/func_80B6F90C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Picture_0x80B6EFA0/BgKin2Picture_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Kin2_Picture_0x80B6EFA0/BgKin2Picture_Draw.asm")
