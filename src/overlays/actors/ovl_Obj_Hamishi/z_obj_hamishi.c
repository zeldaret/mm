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
    (ActorFunc)ObjHamishi_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hamishi_0x809A0F20/func_809A0F20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hamishi_0x809A0F20/func_809A0F78.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hamishi_0x809A0F20/func_809A10F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hamishi_0x809A0F20/func_809A13A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hamishi_0x809A0F20/func_809A1408.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hamishi_0x809A0F20/ObjHamishi_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hamishi_0x809A0F20/ObjHamishi_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hamishi_0x809A0F20/ObjHamishi_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hamishi_0x809A0F20/ObjHamishi_Draw.asm")
