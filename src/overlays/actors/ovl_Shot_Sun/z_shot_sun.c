/*
 * File: z_shot_sun.c
 * Overlay: ovl_Shot_Sun
 * Description:
 */

#include "z_shot_sun.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((ShotSun*)thisx)

void ShotSun_Init(Actor* thisx, GlobalContext* globalCtx);
void ShotSun_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ShotSun_Update(Actor* thisx, GlobalContext* globalCtx);

void func_80973740(ShotSun* this, GlobalContext* globalCtx);
void func_80973804(ShotSun* this, GlobalContext* globalCtx);
void func_809738D0(ShotSun* this, GlobalContext* globalCtx);
void func_80973960(ShotSun* this, GlobalContext* globalCtx);

#if 0
const ActorInit Shot_Sun_InitVars = {
    ACTOR_SHOT_SUN,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ShotSun),
    (ActorFunc)ShotSun_Init,
    (ActorFunc)ShotSun_Destroy,
    (ActorFunc)ShotSun_Update,
    (ActorFunc)NULL,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80973BA0 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00000020, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 30, 60, 0, { 0, 0, 0 } },
};

#endif

extern ColliderCylinderInit D_80973BA0;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Shot_Sun/ShotSun_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Shot_Sun/ShotSun_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Shot_Sun/func_80973740.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Shot_Sun/func_80973804.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Shot_Sun/func_809738D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Shot_Sun/func_80973960.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Shot_Sun/ShotSun_Update.s")
