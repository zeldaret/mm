#include "z_obj_kinoko.h"

#define FLAGS 0x00000010

#define THIS ((ObjKinoko*)thisx)

void ObjKinoko_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjKinoko_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjKinoko_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjKinoko_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Kinoko_InitVars = {
    ACTOR_OBJ_KINOKO,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjKinoko),
    (ActorFunc)ObjKinoko_Init,
    (ActorFunc)ObjKinoko_Destroy,
    (ActorFunc)ObjKinoko_Update,
    (ActorFunc)ObjKinoko_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Kinoko_0x80BB4700/ObjKinoko_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Kinoko_0x80BB4700/ObjKinoko_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Kinoko_0x80BB4700/ObjKinoko_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Kinoko_0x80BB4700/ObjKinoko_Draw.asm")
