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
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_FLOWERPOT,
    sizeof(ObjFlowerpot),
    (ActorFunc)ObjFlowerpot_Init,
    (ActorFunc)ObjFlowerpot_Destroy,
    (ActorFunc)ObjFlowerpot_Update,
    (ActorFunc)ObjFlowerpot_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Flowerpot/func_80A1B3D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Flowerpot/func_80A1B840.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Flowerpot/func_80A1B914.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Flowerpot/func_80A1B994.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Flowerpot/func_80A1B9CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Flowerpot/func_80A1BA04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Flowerpot/func_80A1BA44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Flowerpot/func_80A1BD80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Flowerpot/func_80A1C0FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Flowerpot/func_80A1C328.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Flowerpot/func_80A1C554.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Flowerpot/func_80A1C5E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Flowerpot/func_80A1C62C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Flowerpot/ObjFlowerpot_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Flowerpot/ObjFlowerpot_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Flowerpot/func_80A1C818.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Flowerpot/func_80A1C838.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Flowerpot/func_80A1CBF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Flowerpot/func_80A1CC0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Flowerpot/func_80A1CD10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Flowerpot/func_80A1CEF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Flowerpot/ObjFlowerpot_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Flowerpot/ObjFlowerpot_Draw.s")
