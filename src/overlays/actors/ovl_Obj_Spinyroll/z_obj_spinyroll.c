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
    ACTORTYPE_PROP,
    FLAGS,
    OBJECT_SPINYROLL,
    sizeof(ObjSpinyroll),
    (ActorFunc)ObjSpinyroll_Init,
    (ActorFunc)ObjSpinyroll_Destroy,
    (ActorFunc)ObjSpinyroll_Update,
    (ActorFunc)ObjSpinyroll_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1DA50.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1DAAC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1DB2C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1DC5C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1DCCC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1DD18.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1DE10.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1DE58.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1DE84.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1DEB8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1DFA0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1E074.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1E2D8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1E334.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1E394.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1E3D8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1E648.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1E694.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1E6D4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Spinyroll_0x80A1DA50/ObjSpinyroll_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Spinyroll_0x80A1DA50/ObjSpinyroll_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1E9C4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1E9E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1EA10.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1EA4C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1EAAC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1EAE0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1EB40.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1EB54.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1EC24.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1EC38.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1ECC0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Spinyroll_0x80A1DA50/func_80A1ECD4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Spinyroll_0x80A1DA50/ObjSpinyroll_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Spinyroll_0x80A1DA50/ObjSpinyroll_Draw.asm")
