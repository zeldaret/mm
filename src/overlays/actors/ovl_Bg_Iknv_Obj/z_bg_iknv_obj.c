#include "z_bg_iknv_obj.h"

#define FLAGS 0x00000010

#define THIS ((BgIknvObj*)thisx)

void BgIknvObj_Init(Actor* thisx, GlobalContext* globalCtx);
void BgIknvObj_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgIknvObj_Update(Actor* thisx, GlobalContext* globalCtx);
void BgIknvObj_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Bg_Iknv_Obj_InitVars = {
    ACTOR_BG_IKNV_OBJ,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_IKNV_OBJ,
    sizeof(BgIknvObj),
    (ActorFunc)BgIknvObj_Init,
    (ActorFunc)BgIknvObj_Destroy,
    (ActorFunc)BgIknvObj_Update,
    (ActorFunc)BgIknvObj_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Iknv_Obj/BgIknvObj_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Iknv_Obj/BgIknvObj_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Iknv_Obj/func_80BD7CEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Iknv_Obj/BgIknvObj_UpdateType0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Iknv_Obj/func_80BD7E0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Iknv_Obj/func_80BD7ED8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Iknv_Obj/func_80BD7F4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Iknv_Obj/func_80BD7FDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Iknv_Obj/func_80BD8040.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Iknv_Obj/BgIknvObj_UpdateType2.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Iknv_Obj/BgIknvObj_UpdateType1.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Iknv_Obj/BgIknvObj_UpdateDefault.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Iknv_Obj/BgIknvObj_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Iknv_Obj/BgIknvObj_Draw.s")
