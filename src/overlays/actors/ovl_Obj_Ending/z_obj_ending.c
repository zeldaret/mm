#include "z_obj_ending.h"

#define FLAGS 0x00000030

#define THIS ((ObjEnding*)thisx)

void ObjEnding_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjEnding_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjEnding_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Ending_InitVars = {
    ACTOR_OBJ_ENDING,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_ENDING_OBJ,
    sizeof(ObjEnding),
    (ActorFunc)ObjEnding_Init,
    (ActorFunc)func_800BDFB0,
    (ActorFunc)ObjEnding_Update,
    (ActorFunc)ObjEnding_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_Ending_0x80C25BC0/ObjEnding_Init.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_Ending_0x80C25BC0/ObjEnding_Update.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_Ending_0x80C25BC0/ObjEnding_Draw.asm")
