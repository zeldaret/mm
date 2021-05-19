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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Dora_0x80B60AD0/ObjDora_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Dora_0x80B60AD0/ObjDora_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Dora_0x80B60AD0/func_80B60C9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Dora_0x80B60AD0/func_80B60CB0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Dora_0x80B60AD0/func_80B60CC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Dora_0x80B60AD0/func_80B60D34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Dora_0x80B60AD0/func_80B60E54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Dora_0x80B60AD0/func_80B60EE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Dora_0x80B60AD0/ObjDora_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Dora_0x80B60AD0/ObjDora_Draw.asm")
