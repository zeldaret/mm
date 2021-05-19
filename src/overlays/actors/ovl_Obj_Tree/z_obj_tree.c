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
    (ActorFunc)ObjTree_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tree_0x80B9A0B0/ObjTree_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tree_0x80B9A0B0/ObjTree_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tree_0x80B9A0B0/func_80B9A20C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tree_0x80B9A0B0/func_80B9A220.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tree_0x80B9A0B0/func_80B9A230.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tree_0x80B9A0B0/func_80B9A27C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tree_0x80B9A0B0/func_80B9A348.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tree_0x80B9A0B0/ObjTree_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Tree_0x80B9A0B0/ObjTree_Draw.asm")
