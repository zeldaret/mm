#include "z_obj_boat.h"

#define FLAGS 0x00000010

#define THIS ((ObjBoat*)thisx)

void ObjBoat_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjBoat_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjBoat_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjBoat_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Boat_InitVars = {
    ACTOR_OBJ_BOAT,
    ACTORTYPE_BG,
    FLAGS,
    OBJECT_KAIZOKU_OBJ,
    sizeof(ObjBoat),
    (ActorFunc)ObjBoat_Init,
    (ActorFunc)ObjBoat_Destroy,
    (ActorFunc)ObjBoat_Update,
    (ActorFunc)ObjBoat_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Boat_0x80B9AF50/func_80B9AF50.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Boat_0x80B9AF50/ObjBoat_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Boat_0x80B9AF50/ObjBoat_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Boat_0x80B9AF50/func_80B9B124.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Boat_0x80B9AF50/ObjBoat_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Boat_0x80B9AF50/func_80B9B428.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Boat_0x80B9AF50/ObjBoat_Draw.asm")
