#include "z_obj_swprize.h"

#define FLAGS 0x00000010

#define THIS ((ObjSwprize*)thisx)

void ObjSwprize_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjSwprize_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjSwprize_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Swprize_InitVars = {
    ACTOR_OBJ_SWPRIZE,
    ACTORTYPE_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjSwprize),
    (ActorFunc)ObjSwprize_Init,
    (ActorFunc)ObjSwprize_Destroy,
    (ActorFunc)ObjSwprize_Update,
    (ActorFunc)NULL
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Swprize_0x80C25360/func_80C25360.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Swprize_0x80C25360/func_80C253D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Swprize_0x80C25360/ObjSwprize_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Swprize_0x80C25360/ObjSwprize_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Swprize_0x80C25360/func_80C25640.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Swprize_0x80C25360/func_80C25654.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Swprize_0x80C25360/func_80C25698.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Swprize_0x80C25360/func_80C256AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Swprize_0x80C25360/func_80C25710.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Swprize_0x80C25360/func_80C2572C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Swprize_0x80C25360/func_80C25780.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Swprize_0x80C25360/func_80C25794.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Swprize_0x80C25360/ObjSwprize_Update.asm")
