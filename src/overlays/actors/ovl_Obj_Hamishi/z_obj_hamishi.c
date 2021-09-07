#include "z_obj_hamishi.h"

#define FLAGS 0x00000010

#define THIS ((ObjHamishi*)thisx)

void ObjHamishi_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjHamishi_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjHamishi_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjHamishi_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Obj_Hamishi_InitVars = {
    ACTOR_OBJ_HAMISHI,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_FIELD_KEEP,
    sizeof(ObjHamishi),
    (ActorFunc)ObjHamishi_Init,
    (ActorFunc)ObjHamishi_Destroy,
    (ActorFunc)ObjHamishi_Update,
    (ActorFunc)ObjHamishi_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_809A1AA0 = {
    { COLTYPE_HARD, AT_NONE, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x81C37FB6, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 50, 70, 0, { 0, 0, 0 } },
};

// sColChkInfoInit
static CollisionCheckInfoInit D_809A1ACC = { 0, 12, 60, MASS_IMMOVABLE };

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_809A1AE8[] = {
    ICHAIN_VEC3F_DIV1000(scale, 400, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 2000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 250, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 500, ICHAIN_STOP),
};

#endif

extern ColliderCylinderInit D_809A1AA0;
extern CollisionCheckInfoInit D_809A1ACC;
extern InitChainEntry D_809A1AE8[];

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hamishi/func_809A0F20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hamishi/func_809A0F78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hamishi/func_809A10F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hamishi/func_809A13A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hamishi/func_809A1408.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hamishi/ObjHamishi_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hamishi/ObjHamishi_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hamishi/ObjHamishi_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Hamishi/ObjHamishi_Draw.s")
