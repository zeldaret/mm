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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Wturn_0x808A7930/ObjWturn_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Wturn_0x808A7930/func_808A7954.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Wturn_0x808A7930/func_808A7968.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Wturn_0x808A7930/func_808A7A24.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Wturn_0x808A7930/func_808A7A5C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Wturn_0x808A7930/func_808A7AAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Wturn_0x808A7930/func_808A7BA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Wturn_0x808A7930/func_808A7C04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Wturn_0x808A7930/func_808A7C78.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Wturn_0x808A7930/ObjWturn_Update.asm")
