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
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_NY,
    sizeof(ObjMine),
    (ActorFunc)ObjMine_Init,
    (ActorFunc)ObjMine_Destroy,
    (ActorFunc)ObjMine_Update,
    (ActorFunc)ObjMine_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A811D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A8120C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A81288.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A8131C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A81384.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A8140C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A8146C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A81544.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A81640.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A8164C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A81684.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A81714.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A81818.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A81868.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A819A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A81A00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A81AA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A81B14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A81B7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A81D70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A81DEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A81E7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A81FFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A828A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A82C28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/ObjMine_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/ObjMine_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A82F84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A82F98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A82FA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A82FC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A83214.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A83258.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A832BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A832D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A83A74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A83A88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A83B14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A83B28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A83CEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A83D00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/ObjMine_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A83E7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/ObjMine_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A83FBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A84088.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A84338.s")
