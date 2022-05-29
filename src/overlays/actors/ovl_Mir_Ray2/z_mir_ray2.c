/*
 * File: z_mir_ray2.c
 * Overlay: ovl_Mir_Ray2
 * Description: Reflectable light ray (static beam)
 */

#include "z_mir_ray2.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((MirRay2*)thisx)

void MirRay2_Init(Actor* thisx, GlobalContext* globalCtx);
void MirRay2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void MirRay2_Update(Actor* thisx, GlobalContext* globalCtx);
void MirRay2_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Mir_Ray2_InitVars = {
    ACTOR_MIR_RAY2,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_MIR_RAY,
    sizeof(MirRay2),
    (ActorFunc)MirRay2_Init,
    (ActorFunc)MirRay2_Destroy,
    (ActorFunc)MirRay2_Update,
    (ActorFunc)MirRay2_Draw,
};

// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_80AF4350[1] = {
    {
        { ELEMTYPE_UNK0, { 0x00200000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_NONE, },
        { 0, { { 0, 0, 0 }, 50 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_80AF4374 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_OTHER, AC_NONE, OC1_NONE, OC2_NONE, COLSHAPE_JNTSPH, },
    1, D_80AF4350, // sJntSphElementsInit,
};

#endif

extern ColliderJntSphElementInit D_80AF4350[1];
extern ColliderJntSphInit D_80AF4374;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Mir_Ray2/func_80AF3F70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Mir_Ray2/func_80AF3FE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Mir_Ray2/MirRay2_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Mir_Ray2/MirRay2_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Mir_Ray2/MirRay2_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Mir_Ray2/MirRay2_Draw.s")
