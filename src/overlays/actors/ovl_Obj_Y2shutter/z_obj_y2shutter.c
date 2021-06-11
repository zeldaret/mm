#include "z_obj_y2shutter.h"

#define FLAGS 0x00000010

#define THIS ((ObjY2shutter*)thisx)

void ObjY2shutter_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjY2shutter_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjY2shutter_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjY2shutter_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Y2shutter_InitVars = {
    ACTOR_OBJ_Y2SHUTTER,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_KAIZOKU_OBJ,
    sizeof(ObjY2shutter),
    (ActorFunc)ObjY2shutter_Init,
    (ActorFunc)ObjY2shutter_Destroy,
    (ActorFunc)ObjY2shutter_Update,
    (ActorFunc)ObjY2shutter_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Y2shutter/ObjY2shutter_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Y2shutter/ObjY2shutter_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Y2shutter/func_80B9AA20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Y2shutter/ObjY2shutter_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Y2shutter/ObjY2shutter_Draw.s")
