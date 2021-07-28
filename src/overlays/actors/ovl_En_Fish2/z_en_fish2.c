#include "z_en_fish2.h"

#define FLAGS 0x00000019

#define THIS ((EnFish2*)thisx)

void EnFish2_Init(Actor* thisx, GlobalContext* globalCtx);
void EnFish2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnFish2_Update(Actor* thisx, GlobalContext* globalCtx);
void EnFish2_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Fish2_InitVars = {
    ACTOR_EN_FISH2,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_FB,
    sizeof(EnFish2),
    (ActorFunc)EnFish2_Init,
    (ActorFunc)EnFish2_Destroy,
    (ActorFunc)EnFish2_Update,
    (ActorFunc)EnFish2_Draw,
};

// static ColliderJntSphElementInit sJntSphElementsInit[2] = {
static ColliderJntSphElementInit D_80B2B318[2] = {
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 0 }, 1 },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
        { 17, { { 0, 0, 0 }, 0 }, 1 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_80B2B360 = {
    { COLTYPE_HARD, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    2, D_80B2B318, // sJntSphElementsInit,
};

#endif

extern ColliderJntSphElementInit D_80B2B318[2];
extern ColliderJntSphInit D_80B2B360;

extern UNK_TYPE D_060013AC;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish2/func_80B28370.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish2/func_80B28478.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish2/EnFish2_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish2/EnFish2_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish2/func_80B287F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish2/func_80B288E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish2/func_80B2899C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish2/func_80B289DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish2/func_80B28B5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish2/func_80B28C14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish2/func_80B29128.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish2/func_80B2913C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish2/func_80B29194.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish2/func_80B29250.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish2/func_80B2938C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish2/func_80B293C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish2/func_80B2951C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish2/func_80B295A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish2/func_80B29778.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish2/func_80B297FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish2/func_80B29E5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish2/func_80B29EE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish2/func_80B2A01C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish2/func_80B2A094.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish2/func_80B2A23C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish2/func_80B2A448.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish2/func_80B2A498.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish2/EnFish2_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish2/func_80B2ABF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish2/func_80B2AC20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish2/EnFish2_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish2/func_80B2ADB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish2/func_80B2AF80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fish2/func_80B2B180.s")
