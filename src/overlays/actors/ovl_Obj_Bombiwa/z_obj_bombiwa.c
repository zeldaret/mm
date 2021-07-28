#include "z_obj_bombiwa.h"

#define FLAGS 0x00000000

#define THIS ((ObjBombiwa*)thisx)

void ObjBombiwa_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjBombiwa_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjBombiwa_Update(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Obj_Bombiwa_InitVars = {
    ACTOR_OBJ_BOMBIWA,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_BOMBIWA,
    sizeof(ObjBombiwa),
    (ActorFunc)ObjBombiwa_Init,
    (ActorFunc)ObjBombiwa_Destroy,
    (ActorFunc)ObjBombiwa_Update,
    (ActorFunc)NULL,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_8093A940 = {
    { COLTYPE_HARD, AT_NONE, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x81C37FBE, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 55, 70, 0, { 0, 0, 0 } },
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_8093A96C = {
    { COLTYPE_HARD, AT_NONE, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x81C37BBE, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 75, 130, 0, { 0, 0, 0 } },
};

// sColChkInfoInit
static CollisionCheckInfoInit D_8093A9B8 = { 0, 12, 60, MASS_IMMOVABLE };

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_8093A9C0[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 2000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 400, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 500, ICHAIN_STOP),
};

#endif

extern ColliderCylinderInit D_8093A940;
extern ColliderCylinderInit D_8093A96C;
extern CollisionCheckInfoInit D_8093A9B8;
extern InitChainEntry D_8093A9C0[];

extern UNK_TYPE D_060009E0;
extern UNK_TYPE D_06004560;
extern UNK_TYPE D_06005990;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bombiwa/func_809393B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bombiwa/func_80939470.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bombiwa/func_8093951C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bombiwa/func_80939594.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bombiwa/ObjBombiwa_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bombiwa/ObjBombiwa_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bombiwa/func_80939794.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bombiwa/func_80939994.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bombiwa/func_80939C50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bombiwa/func_80939EE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bombiwa/func_80939EF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bombiwa/func_8093A080.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bombiwa/func_8093A1F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bombiwa/ObjBombiwa_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bombiwa/func_8093A418.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Bombiwa/func_8093A608.s")
