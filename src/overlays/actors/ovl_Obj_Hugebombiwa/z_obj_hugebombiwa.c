#include "z_obj_hugebombiwa.h"

#define FLAGS 0x00000010

#define THIS ((ObjHugebombiwa*)thisx)

void ObjHugebombiwa_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjHugebombiwa_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjHugebombiwa_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjHugebombiwa_Draw(Actor* thisx, GlobalContext* globalCtx);

#if(0)
const ActorInit Obj_Hugebombiwa_InitVars = {
    ACTOR_OBJ_HUGEBOMBIWA,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_BOMBIWA,
    sizeof(ObjHugebombiwa),
    (ActorFunc)ObjHugebombiwa_Init,
    (ActorFunc)ObjHugebombiwa_Destroy,
    (ActorFunc)ObjHugebombiwa_Update,
    (ActorFunc)ObjHugebombiwa_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80A55D00 = {
    { COLTYPE_HARD, AT_NONE, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x81C37BB6, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 180, 226, 0, { 0, 0, 0 } },
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80A55D7C[] = {
    ICHAIN_F32(uncullZoneForward, 3700, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 900, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 900, ICHAIN_STOP),
};


extern ColliderCylinderInit D_80A55D00;
extern InitChainEntry D_80A55D7C[];
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hugebombiwa_0x80A53BE0/func_80A53BE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hugebombiwa_0x80A53BE0/func_80A53E60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hugebombiwa_0x80A53BE0/func_80A541F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hugebombiwa_0x80A53BE0/func_80A54600.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hugebombiwa_0x80A53BE0/func_80A54980.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hugebombiwa_0x80A53BE0/func_80A54A0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hugebombiwa_0x80A53BE0/ObjHugebombiwa_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hugebombiwa_0x80A53BE0/ObjHugebombiwa_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hugebombiwa_0x80A53BE0/func_80A54BF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hugebombiwa_0x80A53BE0/func_80A54C04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hugebombiwa_0x80A53BE0/func_80A54CD8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hugebombiwa_0x80A53BE0/func_80A54CEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hugebombiwa_0x80A53BE0/func_80A54E10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hugebombiwa_0x80A53BE0/func_80A55064.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hugebombiwa_0x80A53BE0/func_80A55310.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hugebombiwa_0x80A53BE0/func_80A55564.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hugebombiwa_0x80A53BE0/ObjHugebombiwa_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hugebombiwa_0x80A53BE0/ObjHugebombiwa_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Hugebombiwa_0x80A53BE0/func_80A55B34.asm")
