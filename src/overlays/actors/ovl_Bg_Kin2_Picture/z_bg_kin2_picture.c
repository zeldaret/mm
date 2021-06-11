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

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Picture/func_80B6EFA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Picture/func_80B6EFEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Picture/func_80B6F098.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Picture/BgKin2Picture_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Picture/BgKin2Picture_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Picture/func_80B6F4C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Picture/func_80B6F4D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Picture/func_80B6F5A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Picture/func_80B6F5B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Picture/func_80B6F61C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Picture/func_80B6F640.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Picture/func_80B6F708.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Picture/func_80B6F72C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Picture/func_80B6F8F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Picture/func_80B6F90C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Picture/BgKin2Picture_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Picture/BgKin2Picture_Draw.s")
