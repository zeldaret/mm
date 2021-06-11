#include "z_obj_lift.h"

#define FLAGS 0x00000010

#define THIS ((ObjLift*)thisx)

void ObjLift_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjLift_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjLift_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjLift_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Lift_InitVars = {
    ACTOR_OBJ_LIFT,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_D_LIFT,
    sizeof(ObjLift),
    (ActorFunc)ObjLift_Init,
    (ActorFunc)ObjLift_Destroy,
    (ActorFunc)ObjLift_Update,
    (ActorFunc)ObjLift_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lift/func_8093D3C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lift/ObjLift_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lift/ObjLift_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lift/func_8093D760.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lift/func_8093D7A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lift/func_8093D88C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lift/func_8093D8B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lift/func_8093D9C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lift/func_8093DA48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lift/func_8093DB70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lift/func_8093DB90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lift/ObjLift_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lift/ObjLift_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Lift/func_8093DC90.s")
