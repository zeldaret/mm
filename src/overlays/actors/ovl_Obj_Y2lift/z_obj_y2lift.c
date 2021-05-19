#include "z_obj_y2lift.h"

#define FLAGS 0x00000010

#define THIS ((ObjY2lift*)thisx)

void ObjY2lift_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjY2lift_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjY2lift_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjY2lift_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Y2lift_InitVars = {
    ACTOR_OBJ_Y2LIFT,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_KAIZOKU_OBJ,
    sizeof(ObjY2lift),
    (ActorFunc)ObjY2lift_Init,
    (ActorFunc)ObjY2lift_Destroy,
    (ActorFunc)ObjY2lift_Update,
    (ActorFunc)ObjY2lift_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Y2lift_0x80B9A650/ObjY2lift_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Y2lift_0x80B9A650/ObjY2lift_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Y2lift_0x80B9A650/ObjY2lift_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Y2lift_0x80B9A650/ObjY2lift_Draw.asm")
