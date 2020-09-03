#include "z_obj_makeoshihiki.h"

#define FLAGS 0x00000010

#define THIS ((ObjMakeoshihiki*)thisx)

void ObjMakeoshihiki_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjMakeoshihiki_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Makeoshihiki_InitVars = {
    ACTOR_OBJ_MAKEOSHIHIKI,
    ACTORTYPE_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjMakeoshihiki),
    (ActorFunc)ObjMakeoshihiki_Init,
    (ActorFunc)func_800BDFB0,
    (ActorFunc)ObjMakeoshihiki_Update,
    (ActorFunc)NULL
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Makeoshihiki_0x80972350/func_80972350.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Makeoshihiki_0x80972350/func_809723C4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Makeoshihiki_0x80972350/ObjMakeoshihiki_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Makeoshihiki_0x80972350/ObjMakeoshihiki_Update.asm")
