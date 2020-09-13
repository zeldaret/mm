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
    ACTORTYPE_BG,
    FLAGS,
    OBJECT_IKNV_OBJ,
    sizeof(BgIknvObj),
    (ActorFunc)BgIknvObj_Init,
    (ActorFunc)BgIknvObj_Destroy,
    (ActorFunc)BgIknvObj_Update,
    (ActorFunc)BgIknvObj_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Iknv_Obj_0x80BD7AB0/BgIknvObj_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Iknv_Obj_0x80BD7AB0/BgIknvObj_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Iknv_Obj_0x80BD7AB0/func_80BD7CEC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Iknv_Obj_0x80BD7AB0/BgIknvObj_UpdateType0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Iknv_Obj_0x80BD7AB0/func_80BD7E0C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Iknv_Obj_0x80BD7AB0/func_80BD7ED8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Iknv_Obj_0x80BD7AB0/func_80BD7F4C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Iknv_Obj_0x80BD7AB0/func_80BD7FDC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Iknv_Obj_0x80BD7AB0/func_80BD8040.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Iknv_Obj_0x80BD7AB0/BgIknvObj_UpdateType2.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Iknv_Obj_0x80BD7AB0/BgIknvObj_UpdateType1.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Iknv_Obj_0x80BD7AB0/BgIknvObj_UpdateDefault.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Iknv_Obj_0x80BD7AB0/BgIknvObj_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Iknv_Obj_0x80BD7AB0/BgIknvObj_Draw.asm")
