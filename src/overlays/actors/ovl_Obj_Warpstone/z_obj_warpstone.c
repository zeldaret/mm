#include "z_obj_warpstone.h"

#define FLAGS 0x00000009

#define THIS ((ObjWarpstone*)thisx)

void ObjWarpstone_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjWarpstone_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjWarpstone_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjWarpstone_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Warpstone_InitVars = {
    ACTOR_OBJ_WARPSTONE,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_SEK,
    sizeof(ObjWarpstone),
    (ActorFunc)ObjWarpstone_Init,
    (ActorFunc)ObjWarpstone_Destroy,
    (ActorFunc)ObjWarpstone_Update,
    (ActorFunc)ObjWarpstone_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Warpstone/func_80B92B10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Warpstone/ObjWarpstone_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Warpstone/ObjWarpstone_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Warpstone/func_80B92C00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Warpstone/func_80B92C48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Warpstone/func_80B92CD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Warpstone/func_80B92DC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Warpstone/ObjWarpstone_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Warpstone/ObjWarpstone_Draw.s")
