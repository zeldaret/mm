#include "z_obj_kibako2.h"

#define FLAGS 0x00000000

#define THIS ((ObjKibako2*)thisx)

void ObjKibako2_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjKibako2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjKibako2_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjKibako2_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Kibako2_InitVars = {
    ACTOR_OBJ_KIBAKO2,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_KIBAKO2,
    sizeof(ObjKibako2),
    (ActorFunc)ObjKibako2_Init,
    (ActorFunc)ObjKibako2_Destroy,
    (ActorFunc)ObjKibako2_Update,
    (ActorFunc)ObjKibako2_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Kibako2_0x8098E5C0/func_8098E5C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Kibako2_0x8098E5C0/func_8098E62C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Kibako2_0x8098E5C0/func_8098E8A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Kibako2_0x8098E5C0/func_8098E900.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Kibako2_0x8098E5C0/func_8098E9C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Kibako2_0x8098E5C0/ObjKibako2_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Kibako2_0x8098E5C0/ObjKibako2_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Kibako2_0x8098E5C0/func_8098EB78.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Kibako2_0x8098E5C0/func_8098EC68.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Kibako2_0x8098E5C0/func_8098ED20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Kibako2_0x8098E5C0/ObjKibako2_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Kibako2_0x8098E5C0/ObjKibako2_Draw.asm")
