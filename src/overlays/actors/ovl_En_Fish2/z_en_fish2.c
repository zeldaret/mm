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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish2_0x80B28370/func_80B28370.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish2_0x80B28370/func_80B28478.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish2_0x80B28370/EnFish2_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish2_0x80B28370/EnFish2_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish2_0x80B28370/func_80B287F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish2_0x80B28370/func_80B288E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish2_0x80B28370/func_80B2899C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish2_0x80B28370/func_80B289DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish2_0x80B28370/func_80B28B5C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish2_0x80B28370/func_80B28C14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish2_0x80B28370/func_80B29128.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish2_0x80B28370/func_80B2913C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish2_0x80B28370/func_80B29194.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish2_0x80B28370/func_80B29250.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish2_0x80B28370/func_80B2938C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish2_0x80B28370/func_80B293C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish2_0x80B28370/func_80B2951C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish2_0x80B28370/func_80B295A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish2_0x80B28370/func_80B29778.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish2_0x80B28370/func_80B297FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish2_0x80B28370/func_80B29E5C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish2_0x80B28370/func_80B29EE4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish2_0x80B28370/func_80B2A01C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish2_0x80B28370/func_80B2A094.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish2_0x80B28370/func_80B2A23C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish2_0x80B28370/func_80B2A448.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish2_0x80B28370/func_80B2A498.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish2_0x80B28370/EnFish2_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish2_0x80B28370/func_80B2ABF4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish2_0x80B28370/func_80B2AC20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish2_0x80B28370/EnFish2_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish2_0x80B28370/func_80B2ADB0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish2_0x80B28370/func_80B2AF80.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Fish2_0x80B28370/func_80B2B180.asm")
