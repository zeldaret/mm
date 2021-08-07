#include "z_obj_hunsui.h"

#define FLAGS 0x00000030

#define THIS ((ObjHunsui*)thisx)

void ObjHunsui_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjHunsui_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjHunsui_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjHunsui_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
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

#endif

extern UNK_TYPE D_06000220;
extern UNK_TYPE D_06000C74;
extern UNK_TYPE D_06000EC0;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hunsui/func_80B9C450.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hunsui/func_80B9C5E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hunsui/ObjHunsui_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hunsui/ObjHunsui_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hunsui/ObjHunsui_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hunsui/func_80B9CE64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hunsui/func_80B9D094.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hunsui/func_80B9D0FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hunsui/func_80B9D120.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hunsui/func_80B9D288.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hunsui/func_80B9D2BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hunsui/func_80B9D334.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hunsui/func_80B9D4D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hunsui/func_80B9D508.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hunsui/func_80B9D714.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hunsui/ObjHunsui_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hunsui/func_80B9DA60.s")
