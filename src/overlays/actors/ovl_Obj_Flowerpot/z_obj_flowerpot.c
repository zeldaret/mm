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
    (ActorFunc)ObjFlowerpot_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1B3D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1B840.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1B914.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1B994.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1B9CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1BA04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1BA44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1BD80.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1C0FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1C328.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1C554.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1C5E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1C62C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Flowerpot_0x80A1B3D0/ObjFlowerpot_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Flowerpot_0x80A1B3D0/ObjFlowerpot_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1C818.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1C838.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1CBF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1CC0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1CD10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Flowerpot_0x80A1B3D0/func_80A1CEF4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Flowerpot_0x80A1B3D0/ObjFlowerpot_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Flowerpot_0x80A1B3D0/ObjFlowerpot_Draw.asm")
