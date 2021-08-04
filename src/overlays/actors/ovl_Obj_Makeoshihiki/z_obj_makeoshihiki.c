#include "z_obj_makeoshihiki.h"

#define FLAGS 0x00000010

#define THIS ((ObjMakeoshihiki*)thisx)

void ObjMakeoshihiki_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjMakeoshihiki_Update(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Obj_Makeoshihiki_InitVars = {
    ACTOR_OBJ_MAKEOSHIHIKI,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjMakeoshihiki),
    (ActorFunc)ObjMakeoshihiki_Init,
    (ActorFunc)Actor_Noop,
    (ActorFunc)ObjMakeoshihiki_Update,
    (ActorFunc)NULL,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Makeoshihiki/func_80972350.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Makeoshihiki/func_809723C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Makeoshihiki/ObjMakeoshihiki_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Makeoshihiki/ObjMakeoshihiki_Update.s")
