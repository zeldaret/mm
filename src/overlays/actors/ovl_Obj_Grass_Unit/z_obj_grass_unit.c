#include "z_obj_grass_unit.h"

#define FLAGS 0x00000000

#define THIS ((ObjGrassUnit*)thisx)

void ObjGrassUnit_Init(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Grass_Unit_InitVars = {
    ACTOR_OBJ_GRASS_UNIT,
    ACTORCAT_BG,
    FLAGS,
    GAMEPLAY_FIELD_KEEP,
    sizeof(ObjGrassUnit),
    (ActorFunc)ObjGrassUnit_Init,
    (ActorFunc)Actor_Noop,
    (ActorFunc)Actor_Noop,
    (ActorFunc)NULL,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Grass_Unit/func_809ABDE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Grass_Unit/func_809ABE54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Grass_Unit/func_809ABEC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Grass_Unit/func_809ABF38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Grass_Unit/ObjGrassUnit_Init.s")
