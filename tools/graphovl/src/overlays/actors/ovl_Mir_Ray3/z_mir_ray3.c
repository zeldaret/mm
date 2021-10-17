#include "z_mir_ray3.h"

#define FLAGS 0x00000030

#define THIS ((MirRay3*)thisx)

void MirRay3_Init(Actor* thisx, GlobalContext* globalCtx);
void MirRay3_Destroy(Actor* thisx, GlobalContext* globalCtx);
void MirRay3_Update(Actor* thisx, GlobalContext* globalCtx);
void MirRay3_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Mir_Ray3_InitVars = {
    ACTOR_MIR_RAY3,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_MIR_RAY,
    sizeof(MirRay3),
    (ActorFunc)MirRay3_Init,
    (ActorFunc)MirRay3_Destroy,
    (ActorFunc)MirRay3_Update,
    (ActorFunc)MirRay3_Draw,
};

// static ColliderQuadInit sQuadInit = {
static ColliderQuadInit D_80B9F420 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_PLAYER, AC_NONE, OC1_NONE, OC2_NONE, COLSHAPE_QUAD, },
    { ELEMTYPE_UNK0, { 0x00200000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_NONE, },
    { { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } },
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B9F470 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER | AC_TYPE_OTHER, OC1_NONE, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00200000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
    { 10, 10, 0, { 0, 0, 0 } },
};

#endif

extern ColliderQuadInit D_80B9F420;
extern ColliderCylinderInit D_80B9F470;

extern UNK_TYPE D_060003F8;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Mir_Ray3/MirRay3_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Mir_Ray3/MirRay3_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Mir_Ray3/MirRay3_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Mir_Ray3/func_80B9E544.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Mir_Ray3/func_80B9E5F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Mir_Ray3/func_80B9E7D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Mir_Ray3/func_80B9E8D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Mir_Ray3/MirRay3_Draw.s")
