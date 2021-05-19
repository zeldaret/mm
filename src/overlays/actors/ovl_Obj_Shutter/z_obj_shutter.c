#include "z_obj_shutter.h"

#define FLAGS 0x00000030

#define THIS ((ObjShutter*)thisx)

void ObjShutter_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjShutter_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjShutter_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjShutter_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Shutter_InitVars = {
    ACTOR_OBJ_SHUTTER,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_F53_OBJ,
    sizeof(ObjShutter),
    (ActorFunc)ObjShutter_Init,
    (ActorFunc)ObjShutter_Destroy,
    (ActorFunc)ObjShutter_Update,
    (ActorFunc)ObjShutter_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Shutter_0x80A37ED0/ObjShutter_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Shutter_0x80A37ED0/ObjShutter_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Shutter_0x80A37ED0/ObjShutter_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Shutter_0x80A37ED0/ObjShutter_Draw.asm")
