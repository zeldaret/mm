#include "z_obj_bigicicle.h"

#define FLAGS 0x00000000

#define THIS ((ObjBigicicle*)thisx)

void ObjBigicicle_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjBigicicle_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjBigicicle_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjBigicicle_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Bigicicle_InitVars = {
    ACTOR_OBJ_BIGICICLE,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_BIGICICLE,
    sizeof(ObjBigicicle),
    (ActorFunc)ObjBigicicle_Init,
    (ActorFunc)ObjBigicicle_Destroy,
    (ActorFunc)ObjBigicicle_Update,
    (ActorFunc)ObjBigicicle_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bigicicle/ObjBigicicle_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bigicicle/ObjBigicicle_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bigicicle/func_80AE8DE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bigicicle/func_80AE8FD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bigicicle/func_80AE9090.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bigicicle/func_80AE9180.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bigicicle/func_80AE9258.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bigicicle/func_80AE939C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bigicicle/ObjBigicicle_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bigicicle/ObjBigicicle_Draw.s")
