#include "z_obj_bombiwa.h"

#define FLAGS 0x00000000

#define THIS ((ObjBombiwa*)thisx)

void ObjBombiwa_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjBombiwa_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjBombiwa_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Bombiwa_InitVars = {
    ACTOR_OBJ_BOMBIWA,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_BOMBIWA,
    sizeof(ObjBombiwa),
    (ActorFunc)ObjBombiwa_Init,
    (ActorFunc)ObjBombiwa_Destroy,
    (ActorFunc)ObjBombiwa_Update,
    (ActorFunc)NULL,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bombiwa/func_809393B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bombiwa/func_80939470.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bombiwa/func_8093951C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bombiwa/func_80939594.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bombiwa/ObjBombiwa_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bombiwa/ObjBombiwa_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bombiwa/func_80939794.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bombiwa/func_80939994.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bombiwa/func_80939C50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bombiwa/func_80939EE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bombiwa/func_80939EF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bombiwa/func_8093A080.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bombiwa/func_8093A1F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bombiwa/ObjBombiwa_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bombiwa/func_8093A418.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bombiwa/func_8093A608.s")
