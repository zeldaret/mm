#include "z_obj_milk_bin.h"

#define FLAGS 0x00000000

#define THIS ((ObjMilkBin*)thisx)

void ObjMilkBin_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjMilkBin_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjMilkBin_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjMilkBin_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Milk_Bin_InitVars = {
    ACTOR_OBJ_MILK_BIN,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_OBJECT_UNSET_MILK_BIN,
    sizeof(ObjMilkBin),
    (ActorFunc)ObjMilkBin_Init,
    (ActorFunc)ObjMilkBin_Destroy,
    (ActorFunc)ObjMilkBin_Update,
    (ActorFunc)ObjMilkBin_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Milk_Bin/ObjMilkBin_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Milk_Bin/ObjMilkBin_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Milk_Bin/ObjMilkBin_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Milk_Bin/ObjMilkBin_Draw.s")
