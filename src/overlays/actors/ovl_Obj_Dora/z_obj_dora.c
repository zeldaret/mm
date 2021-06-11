#include "z_obj_dora.h"

#define FLAGS 0x00000010

#define THIS ((ObjDora*)thisx)

void ObjDora_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjDora_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjDora_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjDora_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Dora_InitVars = {
    ACTOR_OBJ_DORA,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_DORA,
    sizeof(ObjDora),
    (ActorFunc)ObjDora_Init,
    (ActorFunc)ObjDora_Destroy,
    (ActorFunc)ObjDora_Update,
    (ActorFunc)ObjDora_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Dora/ObjDora_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Dora/ObjDora_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Dora/func_80B60C9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Dora/func_80B60CB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Dora/func_80B60CC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Dora/func_80B60D34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Dora/func_80B60E54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Dora/func_80B60EE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Dora/ObjDora_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Dora/ObjDora_Draw.s")
