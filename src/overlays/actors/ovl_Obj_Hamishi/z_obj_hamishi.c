#include "z_obj_hamishi.h"

#define FLAGS 0x00000010

#define THIS ((ObjHamishi*)thisx)

void ObjHamishi_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjHamishi_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjHamishi_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjHamishi_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Hamishi_InitVars = {
    ACTOR_OBJ_HAMISHI,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_FIELD_KEEP,
    sizeof(ObjHamishi),
    (ActorFunc)ObjHamishi_Init,
    (ActorFunc)ObjHamishi_Destroy,
    (ActorFunc)ObjHamishi_Update,
    (ActorFunc)ObjHamishi_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hamishi/func_809A0F20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hamishi/func_809A0F78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hamishi/func_809A10F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hamishi/func_809A13A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hamishi/func_809A1408.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hamishi/ObjHamishi_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hamishi/ObjHamishi_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hamishi/ObjHamishi_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hamishi/ObjHamishi_Draw.s")
