#include "z_obj_spidertent.h"

#define FLAGS 0x10000000

#define THIS ((ObjSpidertent*)thisx)

void ObjSpidertent_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjSpidertent_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjSpidertent_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjSpidertent_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Spidertent_InitVars = {
    ACTOR_OBJ_SPIDERTENT,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_SPIDERTENT,
    sizeof(ObjSpidertent),
    (ActorFunc)ObjSpidertent_Init,
    (ActorFunc)ObjSpidertent_Destroy,
    (ActorFunc)ObjSpidertent_Update,
    (ActorFunc)ObjSpidertent_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Spidertent/func_80B2FB10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Spidertent/func_80B2FB94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Spidertent/func_80B2FC98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Spidertent/func_80B300F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Spidertent/func_80B30410.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Spidertent/func_80B30480.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Spidertent/ObjSpidertent_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Spidertent/ObjSpidertent_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Spidertent/func_80B307E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Spidertent/func_80B30808.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Spidertent/func_80B30A2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Spidertent/func_80B30A4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Spidertent/func_80B30AD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Spidertent/func_80B30AF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Spidertent/ObjSpidertent_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Spidertent/ObjSpidertent_Draw.s")
