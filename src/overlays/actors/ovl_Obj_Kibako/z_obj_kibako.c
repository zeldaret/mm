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
    (ActorFunc)NULL,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_Kibako_0x809261B0/func_809261B0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_Kibako_0x809261B0/func_80926224.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_Kibako_0x809261B0/func_809262BC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_Kibako_0x809261B0/func_80926318.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_Kibako_0x809261B0/func_80926394.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_Kibako_0x809261B0/ObjKibako_Init.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_Kibako_0x809261B0/ObjKibako_Destroy.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_Kibako_0x809261B0/func_8092650C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_Kibako_0x809261B0/func_809267EC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_Kibako_0x809261B0/func_80926B40.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_Kibako_0x809261B0/func_80926B54.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_Kibako_0x809261B0/func_80926BE0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_Kibako_0x809261B0/func_80926BF4.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_Kibako_0x809261B0/func_80926EF4.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_Kibako_0x809261B0/func_80926F08.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_Kibako_0x809261B0/func_8092703C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_Kibako_0x809261B0/func_809270F8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_Kibako_0x809261B0/ObjKibako_Update.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Obj_Kibako_0x809261B0/func_80927334.asm")
