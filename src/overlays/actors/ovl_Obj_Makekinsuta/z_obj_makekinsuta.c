#include "z_obj_makekinsuta.h"

#define FLAGS 0x00000010

#define THIS ((ObjMakekinsuta*)thisx)

void ObjMakekinsuta_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjMakekinsuta_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjMakekinsuta_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Makekinsuta_InitVars = {
    ACTOR_OBJ_MAKEKINSUTA,
    ACTORTYPE_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjMakekinsuta),
    (ActorFunc)ObjMakekinsuta_Init,
    (ActorFunc)ObjMakekinsuta_Destroy,
    (ActorFunc)ObjMakekinsuta_Update,
    (ActorFunc)NULL
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Makekinsuta_0x8099FA40/func_8099FA40.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Makekinsuta_0x8099FA40/ObjMakekinsuta_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Makekinsuta_0x8099FA40/ObjMakekinsuta_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Makekinsuta_0x8099FA40/func_8099FB64.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Makekinsuta_0x8099FA40/ObjMakekinsuta_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Obj_Makekinsuta_0x8099FA40/func_8099FD7C.asm")
