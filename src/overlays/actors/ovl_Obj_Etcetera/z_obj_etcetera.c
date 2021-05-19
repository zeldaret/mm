#include "z_obj_etcetera.h"

#define FLAGS 0x00000010

#define THIS ((ObjEtcetera*)thisx)

void ObjEtcetera_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjEtcetera_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjEtcetera_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Etcetera_InitVars = {
    ACTOR_OBJ_ETCETERA,
    ACTORCAT_BG,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjEtcetera),
    (ActorFunc)ObjEtcetera_Init,
    (ActorFunc)ObjEtcetera_Destroy,
    (ActorFunc)ObjEtcetera_Update,
    (ActorFunc)NULL,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Etcetera_0x80A7BC70/ObjEtcetera_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Etcetera_0x80A7BC70/ObjEtcetera_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Etcetera_0x80A7BC70/func_80A7BDC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Etcetera_0x80A7BC70/func_80A7BE8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Etcetera_0x80A7BC70/func_80A7BF08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Etcetera_0x80A7BC70/func_80A7C168.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Etcetera_0x80A7BC70/func_80A7C1F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Etcetera_0x80A7BC70/func_80A7C308.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Etcetera_0x80A7BC70/ObjEtcetera_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Etcetera_0x80A7BC70/func_80A7C690.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Etcetera_0x80A7BC70/func_80A7C718.asm")
