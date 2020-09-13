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
    ACTORTYPE_BG,
    FLAGS,
    OBJECT_D_LIFT,
    sizeof(ObjChikuwa),
    (ActorFunc)ObjChikuwa_Init,
    (ActorFunc)ObjChikuwa_Destroy,
    (ActorFunc)ObjChikuwa_Update,
    (ActorFunc)ObjChikuwa_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Chikuwa_0x809B1550/func_809B1550.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Chikuwa_0x809B1550/ObjChikuwa_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Chikuwa_0x809B1550/ObjChikuwa_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Chikuwa_0x809B1550/func_809B17D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Chikuwa_0x809B1550/func_809B1AA0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Chikuwa_0x809B1550/ObjChikuwa_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Chikuwa_0x809B1550/ObjChikuwa_Draw.asm")
