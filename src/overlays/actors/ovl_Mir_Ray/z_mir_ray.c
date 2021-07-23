#include "z_mir_ray.h"

#define FLAGS 0x00000030

#define THIS ((MirRay*)thisx)

void MirRay_Init(Actor* thisx, GlobalContext* globalCtx);
void MirRay_Destroy(Actor* thisx, GlobalContext* globalCtx);
void MirRay_Update(Actor* thisx, GlobalContext* globalCtx);
void MirRay_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Mir_Ray_InitVars = {
    ACTOR_MIR_RAY,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_MIR_RAY,
    sizeof(MirRay),
    (ActorFunc)MirRay_Init,
    (ActorFunc)MirRay_Destroy,
    (ActorFunc)MirRay_Update,
    (ActorFunc)MirRay_Draw,
};


// static ColliderQuadInit sQuadInit = {
static ColliderQuadInit D_808E3BF4 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_PLAYER, AC_NONE, OC1_NONE, OC2_NONE, COLSHAPE_QUAD, },
    { ELEMTYPE_UNK0, { 0x00200000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_NONE, },
    { { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } },
};


// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_808E3C44[1] = {
    {
        { ELEMTYPE_UNK0, { 0x00200000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_NONE, },
        { 0, { { 0, 0, 0 }, 50 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_808E3C68 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_PLAYER, AC_NONE, OC1_NONE, OC2_NONE, COLSHAPE_JNTSPH, },
    1, D_808E3C44, // sJntSphElementsInit,
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_808E3DB8[] = {
    ICHAIN_VEC3F_DIV1000(scale, 0, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 1000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 1000, ICHAIN_STOP),
};


extern ColliderQuadInit D_808E3BF4;
extern ColliderJntSphElementInit D_808E3C44[1];
extern ColliderJntSphInit D_808E3C68;
extern InitChainEntry D_808E3DB8[];
#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Mir_Ray/func_808E2600.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Mir_Ray/func_808E26C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Mir_Ray/MirRay_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Mir_Ray/MirRay_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Mir_Ray/MirRay_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Mir_Ray/func_808E2C68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Mir_Ray/func_808E2E1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Mir_Ray/func_808E2FF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Mir_Ray/func_808E30FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Mir_Ray/MirRay_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Mir_Ray/func_808E3984.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Mir_Ray/D_808E3DD0.s")
