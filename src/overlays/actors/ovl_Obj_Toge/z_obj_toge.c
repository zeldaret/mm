#include "z_obj_toge.h"

#define FLAGS 0x00000010

#define THIS ((ObjToge*)thisx)

void ObjToge_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjToge_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjToge_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjToge_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Toge_InitVars = {
    ACTOR_OBJ_TOGE,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_TRAP,
    sizeof(ObjToge),
    (ActorFunc)ObjToge_Init,
    (ActorFunc)ObjToge_Destroy,
    (ActorFunc)ObjToge_Update,
    (ActorFunc)ObjToge_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Toge/func_809A41C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Toge/func_809A42A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Toge/func_809A43A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Toge/func_809A43EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Toge/ObjToge_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Toge/ObjToge_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Toge/func_809A4744.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Toge/func_809A477C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Toge/func_809A4804.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Toge/func_809A481C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Toge/func_809A488C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Toge/func_809A48AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Toge/ObjToge_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Toge/ObjToge_Draw.s")
