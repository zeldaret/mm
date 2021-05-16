#include "z_obj_blockstop.h"

#define FLAGS 0x00000010

#define THIS ((ObjBlockstop*)thisx)

void ObjBlockstop_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjBlockstop_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Blockstop_InitVars = {
    ACTOR_OBJ_BLOCKSTOP,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjBlockstop),
    (ActorFunc)ObjBlockstop_Init,
    (ActorFunc)Actor_NoOp,
    (ActorFunc)ObjBlockstop_Update,
    (ActorFunc)NULL
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Blockstop/ObjBlockstop_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Blockstop/func_809466F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Blockstop/func_809467E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Blockstop/ObjBlockstop_Update.s")
