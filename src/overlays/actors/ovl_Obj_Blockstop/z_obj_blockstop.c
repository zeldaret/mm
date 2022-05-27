/*
 * File: z_obj_blockstop.c
 * Overlay: ovl_Obj_Blockstop
 * Description: Push Block Trigger - Blockstop switch triggered by pushblock (Snowhead)
 */

#include "z_obj_blockstop.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ObjBlockstop*)thisx)

void ObjBlockstop_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjBlockstop_Update(Actor* thisx, GlobalContext* globalCtx);

void func_809466F0(ObjBlockstop* this, GlobalContext* globalCtx);

#if 0
const ActorInit Obj_Blockstop_InitVars = {
    ACTOR_OBJ_BLOCKSTOP,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjBlockstop),
    (ActorFunc)ObjBlockstop_Init,
    (ActorFunc)Actor_Noop,
    (ActorFunc)ObjBlockstop_Update,
    (ActorFunc)NULL,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Blockstop/ObjBlockstop_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Blockstop/func_809466F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Blockstop/func_809467E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Blockstop/ObjBlockstop_Update.s")
