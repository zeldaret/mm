#include "z_obj_smork.h"

#define FLAGS 0x00000030

#define THIS ((ObjSmork*)thisx)

void ObjSmork_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjSmork_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjSmork_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjSmork_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Smork_InitVars = {
    ACTOR_OBJ_SMORK,
    ACTORTYPE_PROP,
    FLAGS,
    OBJECT_F53_OBJ,
    sizeof(ObjSmork),
    (ActorFunc)ObjSmork_Init,
    (ActorFunc)ObjSmork_Destroy,
    (ActorFunc)ObjSmork_Update,
    (ActorFunc)ObjSmork_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Smork_0x80A3D680/func_80A3D680.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Smork_0x80A3D680/func_80A3D940.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Smork_0x80A3D680/func_80A3D9C4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Smork_0x80A3D680/ObjSmork_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Smork_0x80A3D680/ObjSmork_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Smork_0x80A3D680/ObjSmork_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Smork_0x80A3D680/ObjSmork_Draw.asm")
