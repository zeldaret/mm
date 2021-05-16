#include "z_obj_chikuwa.h"

#define FLAGS 0x00000010

#define THIS ((ObjChikuwa*)thisx)

void ObjChikuwa_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjChikuwa_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjChikuwa_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjChikuwa_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Chikuwa_InitVars = {
    ACTOR_OBJ_CHIKUWA,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_D_LIFT,
    sizeof(ObjChikuwa),
    (ActorFunc)ObjChikuwa_Init,
    (ActorFunc)ObjChikuwa_Destroy,
    (ActorFunc)ObjChikuwa_Update,
    (ActorFunc)ObjChikuwa_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Chikuwa/func_809B1550.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Chikuwa/ObjChikuwa_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Chikuwa/ObjChikuwa_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Chikuwa/func_809B17D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Chikuwa/func_809B1AA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Chikuwa/ObjChikuwa_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Chikuwa/ObjChikuwa_Draw.s")
