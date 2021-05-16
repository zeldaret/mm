#include "z_obj_grass_carry.h"

#define FLAGS 0x00800030

#define THIS ((ObjGrassCarry*)thisx)

void ObjGrassCarry_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjGrassCarry_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjGrassCarry_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Grass_Carry_InitVars = {
    ACTOR_OBJ_GRASS_CARRY,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_FIELD_KEEP,
    sizeof(ObjGrassCarry),
    (ActorFunc)ObjGrassCarry_Init,
    (ActorFunc)ObjGrassCarry_Destroy,
    (ActorFunc)ObjGrassCarry_Update,
    (ActorFunc)NULL
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Grass_Carry/func_809AAE60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Grass_Carry/func_809AAE94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Grass_Carry/func_809AAF18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Grass_Carry/func_809AAF58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Grass_Carry/func_809AAF9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Grass_Carry/func_809AAFE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Grass_Carry/ObjGrassCarry_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Grass_Carry/ObjGrassCarry_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Grass_Carry/func_809AB3C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Grass_Carry/func_809AB3D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Grass_Carry/func_809AB428.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Grass_Carry/func_809AB43C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Grass_Carry/func_809AB474.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Grass_Carry/func_809AB4A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Grass_Carry/func_809AB5FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Grass_Carry/func_809AB610.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Grass_Carry/func_809AB6FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Grass_Carry/func_809AB77C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Grass_Carry/ObjGrassCarry_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Grass_Carry/func_809ABB7C.s")
