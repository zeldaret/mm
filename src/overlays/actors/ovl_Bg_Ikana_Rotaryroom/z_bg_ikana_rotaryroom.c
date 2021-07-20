#include "z_bg_ikana_rotaryroom.h"

#define FLAGS 0x00000030

#define THIS ((BgIkanaRotaryroom*)thisx)

void BgIkanaRotaryroom_Init(Actor* thisx, GlobalContext* globalCtx);
void BgIkanaRotaryroom_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgIkanaRotaryroom_Update(Actor* thisx, GlobalContext* globalCtx);
void BgIkanaRotaryroom_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0

const ActorInit Bg_Ikana_Rotaryroom_InitVars = {
    ACTOR_BG_IKANA_ROTARYROOM,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_IKANA_OBJ,
    sizeof(BgIkanaRotaryroom),
    (ActorFunc)BgIkanaRotaryroom_Init,
    (ActorFunc)BgIkanaRotaryroom_Destroy,
    (ActorFunc)BgIkanaRotaryroom_Update,
    (ActorFunc)BgIkanaRotaryroom_Draw,
};


// static ColliderJntSphElementInit sJntSphElementsInit[2] = {
static ColliderJntSphElementInit D_80B820E0[2] = {
    {
        { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x00002000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { 0, { { -3450, 450, 0 }, 60 }, 100 },
    },
    {
        { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x00002000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { 0, { { 3450, 450, 0 }, 60 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_80B82128 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_NONE, COLSHAPE_JNTSPH, },
    2, D_80B820E0, // sJntSphElementsInit,
};


// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_80B82138[1] = {
    {
        { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x00002000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { 0, { { -3750, 1200, 0 }, 60 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_80B8215C = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_NONE, COLSHAPE_JNTSPH, },
    1, D_80B82138, // sJntSphElementsInit,
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80B82214[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom_0x80B802E0/func_80B802E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom_0x80B802E0/func_80B80358.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom_0x80B802E0/func_80B80440.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom_0x80B802E0/func_80B80550.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom_0x80B802E0/func_80B80778.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom_0x80B802E0/func_80B80894.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom_0x80B802E0/func_80B80C88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom_0x80B802E0/func_80B80F08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom_0x80B802E0/func_80B81010.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom_0x80B802E0/func_80B81234.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom_0x80B802E0/func_80B814B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom_0x80B802E0/func_80B81570.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom_0x80B802E0/func_80B816A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom_0x80B802E0/BgIkanaRotaryroom_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom_0x80B802E0/BgIkanaRotaryroom_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom_0x80B802E0/func_80B818B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom_0x80B802E0/func_80B818C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom_0x80B802E0/func_80B81978.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom_0x80B802E0/func_80B8198C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom_0x80B802E0/func_80B819DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom_0x80B802E0/func_80B819F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom_0x80B802E0/func_80B81A64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom_0x80B802E0/func_80B81A80.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom_0x80B802E0/func_80B81B84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom_0x80B802E0/func_80B81BA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom_0x80B802E0/func_80B81DAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom_0x80B802E0/func_80B81DC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom_0x80B802E0/BgIkanaRotaryroom_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ikana_Rotaryroom_0x80B802E0/BgIkanaRotaryroom_Draw.asm")
