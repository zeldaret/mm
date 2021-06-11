#include "z_obj_rotlift.h"

#define FLAGS 0x00000000

#define THIS ((ObjRotlift*)thisx)

void ObjRotlift_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjRotlift_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjRotlift_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjRotlift_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Rotlift_InitVars = {
    ACTOR_OBJ_ROTLIFT,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_ROTLIFT,
    sizeof(ObjRotlift),
    (ActorFunc)ObjRotlift_Init,
    (ActorFunc)ObjRotlift_Destroy,
    (ActorFunc)ObjRotlift_Update,
    (ActorFunc)ObjRotlift_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Rotlift/func_80B95E20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Rotlift/ObjRotlift_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Rotlift/ObjRotlift_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Rotlift/ObjRotlift_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Rotlift/ObjRotlift_Draw.s")
