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
    (ActorFunc)NULL,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Grass_Carry_0x809AAE60/func_809AAE60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Grass_Carry_0x809AAE60/func_809AAE94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Grass_Carry_0x809AAE60/func_809AAF18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Grass_Carry_0x809AAE60/func_809AAF58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Grass_Carry_0x809AAE60/func_809AAF9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Grass_Carry_0x809AAE60/func_809AAFE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Grass_Carry_0x809AAE60/ObjGrassCarry_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Grass_Carry_0x809AAE60/ObjGrassCarry_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Grass_Carry_0x809AAE60/func_809AB3C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Grass_Carry_0x809AAE60/func_809AB3D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Grass_Carry_0x809AAE60/func_809AB428.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Grass_Carry_0x809AAE60/func_809AB43C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Grass_Carry_0x809AAE60/func_809AB474.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Grass_Carry_0x809AAE60/func_809AB4A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Grass_Carry_0x809AAE60/func_809AB5FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Grass_Carry_0x809AAE60/func_809AB610.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Grass_Carry_0x809AAE60/func_809AB6FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Grass_Carry_0x809AAE60/func_809AB77C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Grass_Carry_0x809AAE60/ObjGrassCarry_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Grass_Carry_0x809AAE60/func_809ABB7C.asm")
