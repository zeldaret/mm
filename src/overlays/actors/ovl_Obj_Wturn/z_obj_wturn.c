#include "z_obj_wturn.h"

#define FLAGS 0x02100010

#define THIS ((ObjWturn*)thisx)

void ObjWturn_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjWturn_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Wturn_InitVars = {
    ACTOR_OBJ_WTURN,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjWturn),
    (ActorFunc)ObjWturn_Init,
    (ActorFunc)Actor_Noop,
    (ActorFunc)ObjWturn_Update,
    (ActorFunc)NULL,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Wturn/ObjWturn_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Wturn/func_808A7954.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Wturn/func_808A7968.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Wturn/func_808A7A24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Wturn/func_808A7A5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Wturn/func_808A7AAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Wturn/func_808A7BA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Wturn/func_808A7C04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Wturn/func_808A7C78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Wturn/ObjWturn_Update.s")
