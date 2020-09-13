#include "z_obj_lupygamelift.h"

#define FLAGS 0x00000030

#define THIS ((ObjLupygamelift*)thisx)

void ObjLupygamelift_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjLupygamelift_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjLupygamelift_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjLupygamelift_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Lupygamelift_InitVars = {
    ACTOR_OBJ_LUPYGAMELIFT,
    ACTORTYPE_BG,
    FLAGS,
    OBJECT_RAILLIFT,
    sizeof(ObjLupygamelift),
    (ActorFunc)ObjLupygamelift_Init,
    (ActorFunc)ObjLupygamelift_Destroy,
    (ActorFunc)ObjLupygamelift_Update,
    (ActorFunc)ObjLupygamelift_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lupygamelift_0x80AF0170/ObjLupygamelift_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lupygamelift_0x80AF0170/ObjLupygamelift_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lupygamelift_0x80AF0170/func_80AF0394.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lupygamelift_0x80AF0170/func_80AF04BC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lupygamelift_0x80AF0170/func_80AF04D8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lupygamelift_0x80AF0170/func_80AF0514.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lupygamelift_0x80AF0170/func_80AF0530.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lupygamelift_0x80AF0170/ObjLupygamelift_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Lupygamelift_0x80AF0170/ObjLupygamelift_Draw.asm")
