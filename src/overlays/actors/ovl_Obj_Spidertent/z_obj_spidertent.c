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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spidertent_0x80B2FB10/func_80B2FB10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spidertent_0x80B2FB10/func_80B2FB94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spidertent_0x80B2FB10/func_80B2FC98.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spidertent_0x80B2FB10/func_80B300F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spidertent_0x80B2FB10/func_80B30410.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spidertent_0x80B2FB10/func_80B30480.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spidertent_0x80B2FB10/ObjSpidertent_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spidertent_0x80B2FB10/ObjSpidertent_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spidertent_0x80B2FB10/func_80B307E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spidertent_0x80B2FB10/func_80B30808.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spidertent_0x80B2FB10/func_80B30A2C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spidertent_0x80B2FB10/func_80B30A4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spidertent_0x80B2FB10/func_80B30AD4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spidertent_0x80B2FB10/func_80B30AF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spidertent_0x80B2FB10/ObjSpidertent_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Spidertent_0x80B2FB10/ObjSpidertent_Draw.asm")
