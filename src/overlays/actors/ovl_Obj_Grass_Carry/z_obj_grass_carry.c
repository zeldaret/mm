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


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_809ABBD0 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_PLAYER, AC_NONE, OC1_ON | OC1_TYPE_PLAYER | OC1_TYPE_2, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00400000, 0x00, 0x02 }, { 0x00000000, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NONE, BUMP_NONE, OCELEM_ON, },
    { 10, 44, 0, { 0, 0, 0 } },
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_809ABC4C[] = {
    ICHAIN_F32_DIV1000(gravity, -3200, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(minVelocityY, -17000, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 400, ICHAIN_STOP),
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
