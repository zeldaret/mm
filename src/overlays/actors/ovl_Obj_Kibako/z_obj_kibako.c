#include "z_obj_kibako.h"

#define FLAGS 0x04000010

#define THIS ((ObjKibako*)thisx)

void ObjKibako_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjKibako_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjKibako_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Kibako_InitVars = {
    ACTOR_OBJ_KIBAKO,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjKibako),
    (ActorFunc)ObjKibako_Init,
    (ActorFunc)ObjKibako_Destroy,
    (ActorFunc)ObjKibako_Update,
    (ActorFunc)NULL
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kibako/func_809261B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kibako/func_80926224.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kibako/func_809262BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kibako/func_80926318.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kibako/func_80926394.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kibako/ObjKibako_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kibako/ObjKibako_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kibako/func_8092650C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kibako/func_809267EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kibako/func_80926B40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kibako/func_80926B54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kibako/func_80926BE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kibako/func_80926BF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kibako/func_80926EF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kibako/func_80926F08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kibako/func_8092703C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kibako/func_809270F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kibako/ObjKibako_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Kibako/func_80927334.s")
