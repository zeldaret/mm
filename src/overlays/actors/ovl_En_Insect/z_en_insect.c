#include "z_en_insect.h"

#define FLAGS 0x00000000

#define THIS ((EnInsect*)thisx)

void EnInsect_Init(Actor* thisx, GlobalContext* globalCtx);
void EnInsect_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnInsect_Update(Actor* thisx, GlobalContext* globalCtx);
void EnInsect_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_8091ACC4(EnInsect* this, GlobalContext* globalCtx);
void func_8091AE5C(EnInsect* this, GlobalContext* globalCtx);
void func_8091B07C(EnInsect* this, GlobalContext* globalCtx);
void func_8091B2D8(EnInsect* this, GlobalContext* globalCtx);
void func_8091B440(EnInsect* this, GlobalContext* globalCtx);
void func_8091B670(EnInsect* this, GlobalContext* globalCtx);
void func_8091B984(EnInsect* this, GlobalContext* globalCtx);

#if 0
const ActorInit En_Insect_InitVars = {
    ACTOR_EN_INSECT,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnInsect),
    (ActorFunc)EnInsect_Init,
    (ActorFunc)EnInsect_Destroy,
    (ActorFunc)EnInsect_Update,
    (ActorFunc)EnInsect_Draw,
};

// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_8091BD84[1] = {
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 5 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_8091BDA8 = {
    { COLTYPE_NONE, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_PLAYER | OC1_TYPE_1, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    1, D_8091BD84, // sJntSphElementsInit,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_8091BDBC[] = {
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 700, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 20, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 30, ICHAIN_STOP),
};

#endif

extern ColliderJntSphElementInit D_8091BD84[1];
extern ColliderJntSphInit D_8091BDA8;
extern InitChainEntry D_8091BDBC[];

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Insect/func_8091A8A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Insect/func_8091A8C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Insect/func_8091A8F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Insect/func_8091A9E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Insect/EnInsect_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Insect/EnInsect_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Insect/func_8091AC78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Insect/func_8091ACC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Insect/func_8091AE10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Insect/func_8091AE5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Insect/func_8091B030.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Insect/func_8091B07C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Insect/func_8091B274.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Insect/func_8091B2D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Insect/func_8091B3D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Insect/func_8091B440.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Insect/func_8091B618.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Insect/func_8091B670.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Insect/func_8091B928.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Insect/func_8091B984.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Insect/EnInsect_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Insect/EnInsect_Draw.s")
