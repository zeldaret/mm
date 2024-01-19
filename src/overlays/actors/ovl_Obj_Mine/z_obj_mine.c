/*
 * File: z_obj_mine.c
 * Overlay: ovl_Obj_Mine
 * Description: Spike metal Mine
 */

#include "z_obj_mine.h"

#define FLAGS 0x00000000

#define THIS ((ObjMine*)thisx)

void ObjMine_Init(Actor* thisx, PlayState* play);
void ObjMine_Destroy(Actor* thisx, PlayState* play);
void ObjMine_Update(Actor* thisx, PlayState* play);
void ObjMine_Draw(Actor* thisx, PlayState* play);

#if 0
ActorInit Obj_Mine_InitVars = {
    /**/ ACTOR_OBJ_MINE,
    /**/ ACTORCAT_PROP,
    /**/ FLAGS,
    /**/ OBJECT_NY,
    /**/ sizeof(ObjMine),
    /**/ ObjMine_Init,
    /**/ ObjMine_Destroy,
    /**/ ObjMine_Update,
    /**/ ObjMine_Draw,
};

// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_80A84570[1] = {
    {
        { ELEMTYPE_UNK2, { 0x00000000, 0x00, 0x00 }, { 0x01CBFFBE, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 30 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_80A84594 = {
    { COLTYPE_METAL, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_PLAYER | OC1_TYPE_1, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    ARRAY_COUNT(sJntSphElementsInit), D_80A84570, // sJntSphElementsInit,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80A845E8[] = {
    ICHAIN_F32(uncullZoneForward, 1300, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 150, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 100, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_STOP),
};

#endif

extern ColliderJntSphElementInit D_80A84570[1];
extern ColliderJntSphInit D_80A84594;
extern InitChainEntry D_80A845E8[];

extern UNK_TYPE D_06000030;
extern UNK_TYPE D_06002068;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A811D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A8120C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A81288.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A8131C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A81384.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A8140C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A8146C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A81544.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A81640.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A8164C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A81684.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A81714.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A81818.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A81868.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A819A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A81A00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A81AA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A81B14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A81B7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A81D70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A81DEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A81E7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A81FFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A828A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A82C28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/ObjMine_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/ObjMine_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A82F84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A82F98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A82FA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A82FC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A83214.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A83258.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A832BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A832D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A83A74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A83A88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A83B14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A83B28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A83CEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A83D00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/ObjMine_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A83E7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/ObjMine_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A83FBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A84088.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A84338.s")
