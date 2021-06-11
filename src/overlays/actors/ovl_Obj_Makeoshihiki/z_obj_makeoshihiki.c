#include "z_obj_makeoshihiki.h"

#define FLAGS 0x00000010

#define THIS ((ObjMakeoshihiki*)thisx)

void ObjMakeoshihiki_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjMakeoshihiki_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Makeoshihiki_InitVars = {
    ACTOR_OBJ_MAKEOSHIHIKI,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjMakeoshihiki),
    (ActorFunc)ObjMakeoshihiki_Init,
    (ActorFunc)Actor_NoOp,
    (ActorFunc)ObjMakeoshihiki_Update,
    (ActorFunc)NULL,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Makeoshihiki/func_80972350.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Makeoshihiki/func_809723C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Makeoshihiki/ObjMakeoshihiki_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Makeoshihiki/ObjMakeoshihiki_Update.s")
