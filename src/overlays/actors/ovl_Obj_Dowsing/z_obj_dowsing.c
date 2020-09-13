#include "z_obj_dowsing.h"

#define FLAGS 0x00000010

#define THIS ((ObjDowsing*)thisx)

void ObjDowsing_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjDowsing_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjDowsing_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Dowsing_InitVars = {
    ACTOR_OBJ_DOWSING,
    ACTORTYPE_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjDowsing),
    (ActorFunc)ObjDowsing_Init,
    (ActorFunc)ObjDowsing_Destroy,
    (ActorFunc)ObjDowsing_Update,
    (ActorFunc)NULL
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Dowsing_0x80B23D50/func_80B23D50.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Dowsing_0x80B23D50/func_80B23DD0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Dowsing_0x80B23D50/ObjDowsing_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Dowsing_0x80B23D50/ObjDowsing_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Dowsing_0x80B23D50/ObjDowsing_Update.asm")
