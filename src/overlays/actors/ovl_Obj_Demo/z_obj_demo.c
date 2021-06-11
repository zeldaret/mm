#include "z_obj_demo.h"

#define FLAGS 0x00000010

#define THIS ((ObjDemo*)thisx)

void ObjDemo_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjDemo_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Demo_InitVars = {
    ACTOR_OBJ_DEMO,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjDemo),
    (ActorFunc)ObjDemo_Init,
    (ActorFunc)Actor_NoOp,
    (ActorFunc)ObjDemo_Update,
    (ActorFunc)NULL,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Demo/ObjDemo_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Demo/func_80983634.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Demo/func_80983678.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Demo/func_80983704.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Demo/ObjDemo_Update.s")
