#include "z_obj_bigicicle.h"

#define FLAGS 0x00000000

#define THIS ((ObjBigicicle*)thisx)

void ObjBigicicle_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjBigicicle_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjBigicicle_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjBigicicle_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Obj_Bigicicle_InitVars = {
    ACTOR_OBJ_BIGICICLE,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_BIGICICLE,
    sizeof(ObjBigicicle),
    (ActorFunc)ObjBigicicle_Init,
    (ActorFunc)ObjBigicicle_Destroy,
    (ActorFunc)ObjBigicicle_Update,
    (ActorFunc)ObjBigicicle_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80AE9820 = {
    { COLTYPE_HARD, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00003820, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 23, 68, -40, { 0, 0, 0 } },
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80AE984C = {
    { COLTYPE_HARD, AT_NONE, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 31, 90, -150, { 0, 0, 0 } },
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80AE9888[] = {
    ICHAIN_F32(gravity, -2, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 5600, ICHAIN_STOP),
};

#endif

extern ColliderCylinderInit D_80AE9820;
extern ColliderCylinderInit D_80AE984C;
extern InitChainEntry D_80AE9888[];

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bigicicle/ObjBigicicle_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bigicicle/ObjBigicicle_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bigicicle/func_80AE8DE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bigicicle/func_80AE8FD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bigicicle/func_80AE9090.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bigicicle/func_80AE9180.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bigicicle/func_80AE9258.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bigicicle/func_80AE939C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bigicicle/ObjBigicicle_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bigicicle/ObjBigicicle_Draw.s")
