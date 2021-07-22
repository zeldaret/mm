#include "z_en_bom.h"

#define FLAGS 0x00000030

#define THIS ((EnBom*)thisx)

void EnBom_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBom_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBom_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBom_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Bom_InitVars = {
    ACTOR_EN_BOM,
    ACTORCAT_EXPLOSIVES,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnBom),
    (ActorFunc)EnBom_Init,
    (ActorFunc)EnBom_Destroy,
    (ActorFunc)EnBom_Update,
    (ActorFunc)EnBom_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80872DC8 = {
    { COLTYPE_HIT0, AT_NONE, AC_ON | AC_TYPE_PLAYER | AC_TYPE_OTHER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK2, { 0x00000000, 0x00, 0x00 }, { 0x00013828, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 6, 11, 14, { 0, 0, 0 } },
};


// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_80872DF4[1] = {
    {
        { ELEMTYPE_UNK0, { 0x00000008, 0x00, 0x02 }, { 0x00000000, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NONE, BUMP_NONE, OCELEM_NONE, },
        { 0, { { 0, 0, 0 }, 0 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_80872E18 = {
    { COLTYPE_HIT0, AT_ON | AT_TYPE_ALL, AC_NONE, OC1_NONE, OC2_NONE, COLSHAPE_JNTSPH, },
    1, D_80872DF4, // sJntSphElementsInit,
};


// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_80872E28[1] = {
    {
        { ELEMTYPE_UNK0, { 0x80000008, 0x00, 0x04 }, { 0x00000000, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NONE, BUMP_NONE, OCELEM_NONE, },
        { 0, { { 0, 0, 0 }, 0 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_80872E4C = {
    { COLTYPE_HIT0, AT_ON | AT_TYPE_ALL, AC_NONE, OC1_NONE, OC2_NONE, COLSHAPE_JNTSPH, },
    1, D_80872E28, // sJntSphElementsInit,
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80872E5C[] = {
    ICHAIN_VEC3F(scale, 0, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 2000, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -4000, ICHAIN_STOP),
};


extern ColliderCylinderInit D_80872DC8;
extern ColliderJntSphElementInit D_80872DF4[1];
extern ColliderJntSphInit D_80872E18;
extern ColliderJntSphElementInit D_80872E28[1];
extern ColliderJntSphInit D_80872E4C;
extern InitChainEntry D_80872E5C[];
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bom_0x80870DB0/EnBom_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bom_0x80870DB0/EnBom_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bom_0x80870DB0/func_80871058.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bom_0x80870DB0/func_808714D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bom_0x80870DB0/func_808715B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bom_0x80870DB0/EnBom_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bom_0x80870DB0/EnBom_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bom_0x80870DB0/func_80872648.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bom_0x80870DB0/func_808726DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bom_0x80870DB0/func_80872BC0.asm")
