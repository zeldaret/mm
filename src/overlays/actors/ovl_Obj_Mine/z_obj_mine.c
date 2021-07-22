#include "z_obj_mine.h"

#define FLAGS 0x00000000

#define THIS ((ObjMine*)thisx)

void ObjMine_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjMine_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjMine_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjMine_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Obj_Mine_InitVars = {
    ACTOR_OBJ_MINE,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_NY,
    sizeof(ObjMine),
    (ActorFunc)ObjMine_Init,
    (ActorFunc)ObjMine_Destroy,
    (ActorFunc)ObjMine_Update,
    (ActorFunc)ObjMine_Draw,
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
    1, D_80A84570, // sJntSphElementsInit,
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80A845E8[] = {
    ICHAIN_F32(uncullZoneForward, 1300, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 150, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 100, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_STOP),
};


extern ColliderJntSphElementInit D_80A84570[1];
extern ColliderJntSphInit D_80A84594;
extern InitChainEntry D_80A845E8[];
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mine_0x80A811D0/func_80A811D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mine_0x80A811D0/func_80A8120C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mine_0x80A811D0/func_80A81288.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mine_0x80A811D0/func_80A8131C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mine_0x80A811D0/func_80A81384.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mine_0x80A811D0/func_80A8140C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mine_0x80A811D0/func_80A8146C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mine_0x80A811D0/func_80A81544.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mine_0x80A811D0/func_80A81640.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mine_0x80A811D0/func_80A8164C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mine_0x80A811D0/func_80A81684.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mine_0x80A811D0/func_80A81714.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mine_0x80A811D0/func_80A81818.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mine_0x80A811D0/func_80A81868.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mine_0x80A811D0/func_80A819A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mine_0x80A811D0/func_80A81A00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mine_0x80A811D0/func_80A81AA4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mine_0x80A811D0/func_80A81B14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mine_0x80A811D0/func_80A81B7C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mine_0x80A811D0/func_80A81D70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mine_0x80A811D0/func_80A81DEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mine_0x80A811D0/func_80A81E7C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mine_0x80A811D0/func_80A81FFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mine_0x80A811D0/func_80A828A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mine_0x80A811D0/func_80A82C28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mine_0x80A811D0/ObjMine_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mine_0x80A811D0/ObjMine_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mine_0x80A811D0/func_80A82F84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mine_0x80A811D0/func_80A82F98.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mine_0x80A811D0/func_80A82FA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mine_0x80A811D0/func_80A82FC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mine_0x80A811D0/func_80A83214.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mine_0x80A811D0/func_80A83258.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mine_0x80A811D0/func_80A832BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mine_0x80A811D0/func_80A832D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mine_0x80A811D0/func_80A83A74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mine_0x80A811D0/func_80A83A88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mine_0x80A811D0/func_80A83B14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mine_0x80A811D0/func_80A83B28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mine_0x80A811D0/func_80A83CEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mine_0x80A811D0/func_80A83D00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mine_0x80A811D0/ObjMine_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mine_0x80A811D0/func_80A83E7C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mine_0x80A811D0/ObjMine_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mine_0x80A811D0/func_80A83FBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mine_0x80A811D0/func_80A84088.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Mine_0x80A811D0/func_80A84338.asm")
