#include "z_obj_raillift.h"

#define FLAGS 0x00000010

#define THIS ((ObjRaillift*)thisx)

void ObjRaillift_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjRaillift_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjRaillift_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjRaillift_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Raillift_InitVars = {
    ACTOR_OBJ_RAILLIFT,
    ACTORTYPE_BG,
    FLAGS,
    OBJECT_RAILLIFT,
    sizeof(ObjRaillift),
    (ActorFunc)ObjRaillift_Init,
    (ActorFunc)ObjRaillift_Destroy,
    (ActorFunc)ObjRaillift_Update,
    (ActorFunc)ObjRaillift_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Raillift_0x80A19910/func_80A19910.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Raillift_0x80A19910/ObjRaillift_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Raillift_0x80A19910/ObjRaillift_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Raillift_0x80A19910/func_80A19B98.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Raillift_0x80A19910/func_80A19BA8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Raillift_0x80A19910/func_80A19E84.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Raillift_0x80A19910/func_80A19EE0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Raillift_0x80A19910/func_80A19F18.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Raillift_0x80A19910/func_80A19F78.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Raillift_0x80A19910/ObjRaillift_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Raillift_0x80A19910/ObjRaillift_Draw.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Raillift_0x80A19910/func_80A1A330.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Raillift_0x80A19910/func_80A1A360.asm")
