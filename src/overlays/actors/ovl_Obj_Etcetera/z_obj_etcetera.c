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

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Etcetera/ObjEtcetera_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Etcetera/ObjEtcetera_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Etcetera/func_80A7BDC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Etcetera/func_80A7BE8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Etcetera/func_80A7BF08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Etcetera/func_80A7C168.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Etcetera/func_80A7C1F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Etcetera/func_80A7C308.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Etcetera/ObjEtcetera_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Etcetera/func_80A7C690.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Etcetera/func_80A7C718.s")
