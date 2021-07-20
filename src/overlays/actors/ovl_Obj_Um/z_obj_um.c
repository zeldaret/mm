#include "z_obj_um.h"

#define FLAGS 0x00000039

#define THIS ((ObjUm*)thisx)

void ObjUm_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjUm_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjUm_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjUm_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0

const ActorInit Obj_Um_InitVars = {
    ACTOR_OBJ_UM,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_UM,
    sizeof(ObjUm),
    (ActorFunc)ObjUm_Init,
    (ActorFunc)ObjUm_Destroy,
    (ActorFunc)ObjUm_Update,
    (ActorFunc)ObjUm_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B7C138 = {
    { COLTYPE_HIT3, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0x00000020, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
    { 40, 64, 0, { 0, 0, 0 } },
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80B7C254[] = {
    ICHAIN_F32(uncullZoneScale, 1200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 300, ICHAIN_STOP),
};

#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B77770.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B77FA4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B781DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B783E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B78764.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B78A54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B78C18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B78D08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B78DF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B78E2C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B78E38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B78E88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B78EBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B78EFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/ObjUm_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/ObjUm_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B79524.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B79560.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B795A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B79734.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B797EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7984C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B79A24.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B79A50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B79BA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B79F10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B79FFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7A070.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7A0E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7A144.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7A1B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7A240.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7A2AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7A394.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7A400.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7A494.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7A614.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7A7AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7A860.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7AB78.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7ABE4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7AC94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7AD34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7AE58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7AEFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7AF30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7B154.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7B18C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/ObjUm_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7B598.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7B93C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7BABC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/func_80B7BEA4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Um_0x80B77770/ObjUm_Draw.asm")
