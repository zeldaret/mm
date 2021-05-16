#include "z_obj_funen.h"

#define FLAGS 0x00000030

#define THIS ((ObjFunen*)thisx)

void ObjFunen_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjFunen_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Funen_InitVars = {
    ACTOR_OBJ_FUNEN,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_FUNEN,
    sizeof(ObjFunen),
    (ActorFunc)ObjFunen_Init,
    (ActorFunc)Actor_NoOp,
    (ActorFunc)Actor_NoOp,
    (ActorFunc)ObjFunen_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Funen/ObjFunen_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Funen/ObjFunen_Draw.s")
