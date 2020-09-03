#include "z_obj_mine.h"

#define FLAGS 0x00000000

#define THIS ((ObjMine*)thisx)

void ObjMine_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjMine_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjMine_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjMine_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Mine_InitVars = {
    ACTOR_OBJ_MINE,
    ACTORTYPE_PROP,
    FLAGS,
    OBJECT_NY,
    sizeof(ObjMine),
    (ActorFunc)ObjMine_Init,
    (ActorFunc)ObjMine_Destroy,
    (ActorFunc)ObjMine_Update,
    (ActorFunc)ObjMine_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mine_0x80A811D0/func_80A811D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mine_0x80A811D0/func_80A8120C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mine_0x80A811D0/func_80A81288.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mine_0x80A811D0/func_80A8131C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mine_0x80A811D0/func_80A81384.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mine_0x80A811D0/func_80A8140C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mine_0x80A811D0/func_80A8146C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mine_0x80A811D0/func_80A81544.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mine_0x80A811D0/func_80A81640.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mine_0x80A811D0/func_80A8164C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mine_0x80A811D0/func_80A81684.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mine_0x80A811D0/func_80A81714.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mine_0x80A811D0/func_80A81818.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mine_0x80A811D0/func_80A81868.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mine_0x80A811D0/func_80A819A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mine_0x80A811D0/func_80A81A00.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mine_0x80A811D0/func_80A81AA4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mine_0x80A811D0/func_80A81B14.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mine_0x80A811D0/func_80A81B7C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mine_0x80A811D0/func_80A81D70.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mine_0x80A811D0/func_80A81DEC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mine_0x80A811D0/func_80A81E7C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mine_0x80A811D0/func_80A81FFC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mine_0x80A811D0/func_80A828A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mine_0x80A811D0/func_80A82C28.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mine_0x80A811D0/ObjMine_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mine_0x80A811D0/ObjMine_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mine_0x80A811D0/func_80A82F84.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mine_0x80A811D0/func_80A82F98.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mine_0x80A811D0/func_80A82FA8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mine_0x80A811D0/func_80A82FC8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mine_0x80A811D0/func_80A83214.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mine_0x80A811D0/func_80A83258.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mine_0x80A811D0/func_80A832BC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mine_0x80A811D0/func_80A832D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mine_0x80A811D0/func_80A83A74.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mine_0x80A811D0/func_80A83A88.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mine_0x80A811D0/func_80A83B14.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mine_0x80A811D0/func_80A83B28.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mine_0x80A811D0/func_80A83CEC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mine_0x80A811D0/func_80A83D00.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mine_0x80A811D0/ObjMine_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mine_0x80A811D0/func_80A83E7C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mine_0x80A811D0/ObjMine_Draw.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mine_0x80A811D0/func_80A83FBC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mine_0x80A811D0/func_80A84088.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Mine_0x80A811D0/func_80A84338.asm")
