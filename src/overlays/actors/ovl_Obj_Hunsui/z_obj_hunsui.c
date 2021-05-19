#include "z_obj_hunsui.h"

#define FLAGS 0x00000030

#define THIS ((ObjHunsui*)thisx)

void ObjHunsui_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjHunsui_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjHunsui_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjHunsui_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Hunsui_InitVars = {
    ACTOR_OBJ_HUNSUI,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_HUNSUI,
    sizeof(ObjHunsui),
    (ActorFunc)ObjHunsui_Init,
    (ActorFunc)ObjHunsui_Destroy,
    (ActorFunc)ObjHunsui_Update,
    (ActorFunc)ObjHunsui_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hunsui_0x80B9C450/func_80B9C450.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hunsui_0x80B9C450/func_80B9C5E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hunsui_0x80B9C450/ObjHunsui_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hunsui_0x80B9C450/ObjHunsui_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hunsui_0x80B9C450/ObjHunsui_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hunsui_0x80B9C450/func_80B9CE64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hunsui_0x80B9C450/func_80B9D094.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hunsui_0x80B9C450/func_80B9D0FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hunsui_0x80B9C450/func_80B9D120.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hunsui_0x80B9C450/func_80B9D288.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hunsui_0x80B9C450/func_80B9D2BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hunsui_0x80B9C450/func_80B9D334.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hunsui_0x80B9C450/func_80B9D4D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hunsui_0x80B9C450/func_80B9D508.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hunsui_0x80B9C450/func_80B9D714.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hunsui_0x80B9C450/ObjHunsui_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hunsui_0x80B9C450/func_80B9DA60.asm")
