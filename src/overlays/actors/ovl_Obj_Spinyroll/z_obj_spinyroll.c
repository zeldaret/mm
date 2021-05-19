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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1DA50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1DAAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1DB2C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1DC5C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1DCCC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1DD18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1DE10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1DE58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1DE84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1DEB8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1DFA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1E074.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1E2D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1E334.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1E394.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1E3D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1E648.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1E694.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1E6D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/ObjSpinyroll_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/ObjSpinyroll_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1E9C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1E9E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1EA10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1EA4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1EAAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1EAE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1EB40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1EB54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1EC24.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1EC38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1ECC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1ECD4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/ObjSpinyroll_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spinyroll_0x80A1DA50/ObjSpinyroll_Draw.asm")
