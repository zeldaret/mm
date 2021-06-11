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
    ACTORCAT_BG,
    FLAGS,
    OBJECT_RAILLIFT,
    sizeof(ObjRaillift),
    (ActorFunc)ObjRaillift_Init,
    (ActorFunc)ObjRaillift_Destroy,
    (ActorFunc)ObjRaillift_Update,
    (ActorFunc)ObjRaillift_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Raillift/func_80A19910.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Raillift/ObjRaillift_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Raillift/ObjRaillift_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Raillift/func_80A19B98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Raillift/func_80A19BA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Raillift/func_80A19E84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Raillift/func_80A19EE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Raillift/func_80A19F18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Raillift/func_80A19F78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Raillift/ObjRaillift_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Raillift/ObjRaillift_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Raillift/func_80A1A330.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Raillift/func_80A1A360.s")
