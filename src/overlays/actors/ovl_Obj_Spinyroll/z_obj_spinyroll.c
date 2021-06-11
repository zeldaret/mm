#include "z_obj_spinyroll.h"

#define FLAGS 0x00000010

#define THIS ((ObjSpinyroll*)thisx)

void ObjSpinyroll_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjSpinyroll_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjSpinyroll_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjSpinyroll_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Spinyroll_InitVars = {
    ACTOR_OBJ_SPINYROLL,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_SPINYROLL,
    sizeof(ObjSpinyroll),
    (ActorFunc)ObjSpinyroll_Init,
    (ActorFunc)ObjSpinyroll_Destroy,
    (ActorFunc)ObjSpinyroll_Update,
    (ActorFunc)ObjSpinyroll_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Spinyroll/func_80A1DA50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Spinyroll/func_80A1DAAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Spinyroll/func_80A1DB2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Spinyroll/func_80A1DC5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Spinyroll/func_80A1DCCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Spinyroll/func_80A1DD18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Spinyroll/func_80A1DE10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Spinyroll/func_80A1DE58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Spinyroll/func_80A1DE84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Spinyroll/func_80A1DEB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Spinyroll/func_80A1DFA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Spinyroll/func_80A1E074.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Spinyroll/func_80A1E2D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Spinyroll/func_80A1E334.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Spinyroll/func_80A1E394.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Spinyroll/func_80A1E3D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Spinyroll/func_80A1E648.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Spinyroll/func_80A1E694.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Spinyroll/func_80A1E6D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Spinyroll/ObjSpinyroll_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Spinyroll/ObjSpinyroll_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Spinyroll/func_80A1E9C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Spinyroll/func_80A1E9E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Spinyroll/func_80A1EA10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Spinyroll/func_80A1EA4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Spinyroll/func_80A1EAAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Spinyroll/func_80A1EAE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Spinyroll/func_80A1EB40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Spinyroll/func_80A1EB54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Spinyroll/func_80A1EC24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Spinyroll/func_80A1EC38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Spinyroll/func_80A1ECC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Spinyroll/func_80A1ECD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Spinyroll/ObjSpinyroll_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Spinyroll/ObjSpinyroll_Draw.s")
