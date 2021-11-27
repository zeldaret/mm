/*
 * File z_en_butte.c
 * Overlay: ovl_En_Butte
 * Description: Butterflies
 */

#include "z_en_butte.h"

#define FLAGS 0x00000000

#define THIS ((EnButte*)thisx)

void EnButte_Init(Actor* thisx, GlobalContext* globalCtx);
void EnButte_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnButte_Update(Actor* thisx, GlobalContext* globalCtx);
void EnButte_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_8091C794(EnButte* this, GlobalContext* globalCtx);
void func_8091CBB4(EnButte* this, GlobalContext* globalCtx);
void func_8091CFB4(EnButte* this, GlobalContext* globalCtx);
void func_8091D090(EnButte* this, GlobalContext* globalCtx);

#if 0
// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_8091D2D0[1] = {
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 5 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_8091D2F4 = {
    { COLTYPE_NONE, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_PLAYER | OC1_TYPE_1, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    1, D_8091D2D0, // sJntSphElementsInit,
};

const ActorInit En_Butte_InitVars = {
    ACTOR_EN_BUTTE,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_FIELD_KEEP,
    sizeof(EnButte),
    (ActorFunc)EnButte_Init,
    (ActorFunc)EnButte_Destroy,
    (ActorFunc)EnButte_Update,
    (ActorFunc)EnButte_Draw,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_8091D3B0[] = {
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 700, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 20, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 60, ICHAIN_STOP),
};

#endif

extern ColliderJntSphElementInit D_8091D2D0[1];
extern ColliderJntSphInit D_8091D2F4;
extern InitChainEntry D_8091D3B0[];

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Butte/func_8091C0A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Butte/func_8091C124.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Butte/func_8091C140.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Butte/func_8091C178.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Butte/EnButte_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Butte/EnButte_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Butte/func_8091C524.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Butte/func_8091C5EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Butte/func_8091C6B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Butte/func_8091C748.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Butte/func_8091C794.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Butte/func_8091CB68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Butte/func_8091CBB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Butte/func_8091CF64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Butte/func_8091CFB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Butte/func_8091D070.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Butte/func_8091D090.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Butte/EnButte_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Butte/EnButte_Draw.s")
