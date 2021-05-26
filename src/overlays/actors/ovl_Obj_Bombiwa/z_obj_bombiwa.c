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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bombiwa_0x809393B0/func_809393B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bombiwa_0x809393B0/func_80939470.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bombiwa_0x809393B0/func_8093951C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bombiwa_0x809393B0/func_80939594.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bombiwa_0x809393B0/ObjBombiwa_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bombiwa_0x809393B0/ObjBombiwa_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bombiwa_0x809393B0/func_80939794.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bombiwa_0x809393B0/func_80939994.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bombiwa_0x809393B0/func_80939C50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bombiwa_0x809393B0/func_80939EE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bombiwa_0x809393B0/func_80939EF4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bombiwa_0x809393B0/func_8093A080.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bombiwa_0x809393B0/func_8093A1F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bombiwa_0x809393B0/ObjBombiwa_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bombiwa_0x809393B0/func_8093A418.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bombiwa_0x809393B0/func_8093A608.asm")
