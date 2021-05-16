#include "z_obj_tree.h"

#define FLAGS 0x02000000

#define THIS ((ObjTree*)thisx)

void ObjTree_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjTree_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjTree_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjTree_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Tree_InitVars = {
    ACTOR_OBJ_TREE,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_TREE,
    sizeof(ObjTree),
    (ActorFunc)ObjTree_Init,
    (ActorFunc)ObjTree_Destroy,
    (ActorFunc)ObjTree_Update,
    (ActorFunc)ObjTree_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tree/ObjTree_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tree/ObjTree_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tree/func_80B9A20C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tree/func_80B9A220.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tree/func_80B9A230.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tree/func_80B9A27C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tree/func_80B9A348.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tree/ObjTree_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tree/ObjTree_Draw.s")
