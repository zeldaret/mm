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
    ACTORTYPE_ITEMACTION,
    FLAGS,
    OBJECT_SEK,
    sizeof(ObjWarpstone),
    (ActorFunc)ObjWarpstone_Init,
    (ActorFunc)ObjWarpstone_Destroy,
    (ActorFunc)ObjWarpstone_Update,
    (ActorFunc)ObjWarpstone_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Warpstone_0x80B92B10/func_80B92B10.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Warpstone_0x80B92B10/ObjWarpstone_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Warpstone_0x80B92B10/ObjWarpstone_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Warpstone_0x80B92B10/func_80B92C00.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Warpstone_0x80B92B10/func_80B92C48.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Warpstone_0x80B92B10/func_80B92CD0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Warpstone_0x80B92B10/func_80B92DC4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Warpstone_0x80B92B10/ObjWarpstone_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Warpstone_0x80B92B10/ObjWarpstone_Draw.asm")
