#include "z_obj_flowerpot.h"

#define FLAGS 0x00000000

#define THIS ((ObjFlowerpot*)thisx)

void ObjFlowerpot_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjFlowerpot_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjFlowerpot_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjFlowerpot_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Flowerpot_InitVars = {
    ACTOR_OBJ_FLOWERPOT,
    ACTORTYPE_PROP,
    FLAGS,
    OBJECT_FLOWERPOT,
    sizeof(ObjFlowerpot),
    (ActorFunc)ObjFlowerpot_Init,
    (ActorFunc)ObjFlowerpot_Destroy,
    (ActorFunc)ObjFlowerpot_Update,
    (ActorFunc)ObjFlowerpot_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1B3D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1B840.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1B914.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1B994.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1B9CC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1BA04.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1BA44.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1BD80.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1C0FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1C328.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1C554.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1C5E8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1C62C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Flowerpot_0x80A1B3D0/ObjFlowerpot_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Flowerpot_0x80A1B3D0/ObjFlowerpot_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1C818.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1C838.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1CBF8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1CC0C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1CD10.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1CEF4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Flowerpot_0x80A1B3D0/ObjFlowerpot_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Flowerpot_0x80A1B3D0/ObjFlowerpot_Draw.asm")
