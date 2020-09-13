#include "z_obj_entotu.h"

#define FLAGS 0x00000030

#define THIS ((ObjEntotu*)thisx)

void ObjEntotu_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjEntotu_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjEntotu_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjEntotu_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Entotu_InitVars = {
    ACTOR_OBJ_ENTOTU,
    ACTORTYPE_PROP,
    FLAGS,
    OBJECT_F53_OBJ,
    sizeof(ObjEntotu),
    (ActorFunc)ObjEntotu_Init,
    (ActorFunc)ObjEntotu_Destroy,
    (ActorFunc)ObjEntotu_Update,
    (ActorFunc)ObjEntotu_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Entotu_0x80A34700/func_80A34700.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Entotu_0x80A34700/func_80A349C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Entotu_0x80A34700/func_80A34A44.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Entotu_0x80A34700/func_80A34B28.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Entotu_0x80A34700/ObjEntotu_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Entotu_0x80A34700/ObjEntotu_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Entotu_0x80A34700/ObjEntotu_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Entotu_0x80A34700/ObjEntotu_Draw.asm")
