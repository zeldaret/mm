#include "z_en_famos.h"

#define FLAGS 0x00000005

#define THIS ((EnFamos*)thisx)

void EnFamos_Init(Actor* thisx, GlobalContext* globalCtx);
void EnFamos_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnFamos_Update(Actor* thisx, GlobalContext* globalCtx);
void EnFamos_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Famos_InitVars = {
    ACTOR_EN_FAMOS,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_FAMOS,
    sizeof(EnFamos),
    (ActorFunc)EnFamos_Init,
    (ActorFunc)EnFamos_Destroy,
    (ActorFunc)EnFamos_Update,
    (ActorFunc)EnFamos_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_808AE600 = {
    { COLTYPE_METAL, AT_NONE | AT_TYPE_ENEMY, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK2, { 0x20000000, 0x04, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 20, 80, 0, { 0, 0, 0 } },
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_808AE62C = {
    { COLTYPE_NONE, AT_NONE | AT_TYPE_ENEMY, AC_NONE, OC1_NONE, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x04, 0x08 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_NONE, },
    { 70, 10, 0, { 0, 0, 0 } },
};


// static ColliderJntSphElementInit sJntSphElementsInit[2] = {
static ColliderJntSphElementInit D_808AE658[2] = {
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00002000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { 2, { { 2500, 0, 0 }, 20 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00002000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { 2, { { -1500, 0, 0 }, 20 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_808AE6A0 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    2, D_808AE658, // sJntSphElementsInit,
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_808AE6B8[] = {
    ICHAIN_S8(hintId, 15, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 3500, ICHAIN_STOP),
};


extern ColliderCylinderInit D_808AE600;
extern ColliderCylinderInit D_808AE62C;
extern ColliderJntSphElementInit D_808AE658[2];
extern ColliderJntSphInit D_808AE6A0;
extern InitChainEntry D_808AE6B8[];
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/EnFamos_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/EnFamos_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808ACB58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808ACD2C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808ACF1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808ACF98.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808AD05C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808AD170.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808AD18C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808AD1F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808AD294.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808AD31C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808AD378.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808AD3E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808AD42C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808AD54C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808AD5B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808AD66C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808AD68C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808AD7EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808AD840.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808AD888.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808AD8B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808ADA74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808ADAE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808ADB4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808ADB70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808ADC40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808ADC64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808ADD20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808ADDA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808ADE00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808ADE74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808ADFA4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808ADFF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808AE030.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/EnFamos_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808AE304.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808AE3A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/func_808AE3FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Famos_0x808AC920/EnFamos_Draw.asm")
