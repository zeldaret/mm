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
    ACTORTYPE_BG,
    FLAGS,
    OBJECT_D_LIFT,
    sizeof(ObjLift),
    (ActorFunc)ObjLift_Init,
    (ActorFunc)ObjLift_Destroy,
    (ActorFunc)ObjLift_Update,
    (ActorFunc)ObjLift_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lift_0x8093D3C0/func_8093D3C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lift_0x8093D3C0/ObjLift_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lift_0x8093D3C0/ObjLift_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lift_0x8093D3C0/func_8093D760.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lift_0x8093D3C0/func_8093D7A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lift_0x8093D3C0/func_8093D88C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lift_0x8093D3C0/func_8093D8B4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lift_0x8093D3C0/func_8093D9C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lift_0x8093D3C0/func_8093DA48.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lift_0x8093D3C0/func_8093DB70.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lift_0x8093D3C0/func_8093DB90.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lift_0x8093D3C0/ObjLift_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lift_0x8093D3C0/ObjLift_Draw.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lift_0x8093D3C0/func_8093DC90.asm")
