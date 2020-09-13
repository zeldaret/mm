#include "z_obj_dinner.h"

#define FLAGS 0x00000020

#define THIS ((ObjDinner*)thisx)

void ObjDinner_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjDinner_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjDinner_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjDinner_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Dinner_InitVars = {
    ACTOR_OBJ_DINNER,
    ACTORTYPE_PROP,
    FLAGS,
    OBJECT_OBJECT_UNSET_DINNER,
    sizeof(ObjDinner),
    (ActorFunc)ObjDinner_Init,
    (ActorFunc)ObjDinner_Destroy,
    (ActorFunc)ObjDinner_Update,
    (ActorFunc)ObjDinner_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Dinner_0x80BEB940/ObjDinner_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Dinner_0x80BEB940/ObjDinner_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Dinner_0x80BEB940/ObjDinner_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Dinner_0x80BEB940/ObjDinner_Draw.asm")
