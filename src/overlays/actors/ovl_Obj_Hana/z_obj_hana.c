#include "z_obj_hana.h"

#define FLAGS 0x00000000

#define THIS ((ObjHana*)thisx)

void ObjHana_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjHana_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjHana_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjHana_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Hana_InitVars = {
    ACTOR_OBJ_HANA,
    ACTORTYPE_PROP,
    FLAGS,
    OBJECT_HANA,
    sizeof(ObjHana),
    (ActorFunc)ObjHana_Init,
    (ActorFunc)ObjHana_Destroy,
    (ActorFunc)ObjHana_Update,
    (ActorFunc)ObjHana_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Hana_0x8095FB10/ObjHana_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Hana_0x8095FB10/ObjHana_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Hana_0x8095FB10/ObjHana_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Hana_0x8095FB10/ObjHana_Draw.asm")
