#include "z_obj_kepn_koya.h"

#define FLAGS 0x00000000

#define THIS ((ObjKepnKoya*)thisx)

void ObjKepnKoya_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjKepnKoya_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjKepnKoya_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjKepnKoya_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Kepn_Koya_InitVars = {
    ACTOR_OBJ_KEPN_KOYA,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_KEPN_KOYA,
    sizeof(ObjKepnKoya),
    (ActorFunc)ObjKepnKoya_Init,
    (ActorFunc)ObjKepnKoya_Destroy,
    (ActorFunc)ObjKepnKoya_Update,
    (ActorFunc)ObjKepnKoya_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kepn_Koya/ObjKepnKoya_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kepn_Koya/ObjKepnKoya_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kepn_Koya/ObjKepnKoya_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kepn_Koya/ObjKepnKoya_Draw.s")
