#include "z_obj_mure3.h"

#define FLAGS 0x00000000

#define THIS ((ObjMure3*)thisx)

void ObjMure3_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjMure3_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjMure3_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Mure3_InitVars = {
    ACTOR_OBJ_MURE3,
    ACTORCAT_BG,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjMure3),
    (ActorFunc)ObjMure3_Init,
    (ActorFunc)ObjMure3_Destroy,
    (ActorFunc)ObjMure3_Update,
    (ActorFunc)NULL
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mure3/func_8098F040.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mure3/func_8098F110.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mure3/func_8098F220.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mure3/func_8098F364.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mure3/func_8098F438.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mure3/ObjMure3_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mure3/ObjMure3_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mure3/func_8098F598.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mure3/func_8098F5AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mure3/func_8098F5D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mure3/func_8098F5E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mure3/func_8098F66C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mure3/func_8098F680.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mure3/ObjMure3_Update.s")
