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
    ACTORTYPE_PROP,
    FLAGS,
    OBJECT_OBJECT_UNSET_MILK_BIN,
    sizeof(ObjMilkBin),
    (ActorFunc)ObjMilkBin_Init,
    (ActorFunc)ObjMilkBin_Destroy,
    (ActorFunc)ObjMilkBin_Update,
    (ActorFunc)ObjMilkBin_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Milk_Bin_0x80C08E40/ObjMilkBin_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Milk_Bin_0x80C08E40/ObjMilkBin_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Milk_Bin_0x80C08E40/ObjMilkBin_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Milk_Bin_0x80C08E40/ObjMilkBin_Draw.asm")
