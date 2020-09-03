#include "z_obj_funen.h"

#define FLAGS 0x00000030

#define THIS ((ObjFunen*)thisx)

void ObjFunen_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjFunen_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Funen_InitVars = {
    ACTOR_OBJ_FUNEN,
    ACTORTYPE_PROP,
    FLAGS,
    OBJECT_FUNEN,
    sizeof(ObjFunen),
    (ActorFunc)ObjFunen_Init,
    (ActorFunc)func_800BDFB0,
    (ActorFunc)func_800BDFB0,
    (ActorFunc)ObjFunen_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Funen_0x80A19740/ObjFunen_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Funen_0x80A19740/ObjFunen_Draw.asm")
