#include "z_en_bombf.h"

#define FLAGS 0x00000011

#define THIS ((EnBombf*)thisx)

void EnBombf_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBombf_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBombf_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBombf_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Bombf_InitVars = {
    ACTOR_EN_BOMBF,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_BOMBF,
    sizeof(EnBombf),
    (ActorFunc)EnBombf_Init,
    (ActorFunc)EnBombf_Destroy,
    (ActorFunc)EnBombf_Update,
    (ActorFunc)EnBombf_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_808AFB20 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER | AC_TYPE_OTHER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK2, { 0x00000000, 0x00, 0x00 }, { 0x00013A28, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 9, 18, 10, { 0, 0, 0 } },
};

// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_808AFB4C[1] = {
    {
        { ELEMTYPE_UNK0, { 0x00000008, 0x00, 0x08 }, { 0x00000000, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NONE, BUMP_NONE, OCELEM_NONE, },
        { 0, { { 0, 0, 0 }, 0 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_808AFB70 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_ALL, AC_NONE, OC1_NONE, OC2_NONE, COLSHAPE_JNTSPH, },
    1, D_808AFB4C, // sJntSphElementsInit,
};

#endif

extern ColliderCylinderInit D_808AFB20;
extern ColliderJntSphElementInit D_808AFB4C[1];
extern ColliderJntSphInit D_808AFB70;

extern UNK_TYPE D_06000340;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombf/func_808AE8C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombf/EnBombf_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombf/EnBombf_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombf/func_808AEAB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombf/func_808AEAE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombf/func_808AEE3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombf/func_808AEF68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombf/func_808AEFD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombf/EnBombf_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombf/func_808AF86C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombf/EnBombf_Draw.s")
