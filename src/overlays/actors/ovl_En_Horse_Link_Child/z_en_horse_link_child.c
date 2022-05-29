/*
 * File: z_en_horse_link_child.c
 * Overlay: ovl_En_Horse_Link_Child
 * Description: Child Epona
 */

#include "z_en_horse_link_child.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_2000000)

#define THIS ((EnHorseLinkChild*)thisx)

void EnHorseLinkChild_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHorseLinkChild_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHorseLinkChild_Update(Actor* thisx, GlobalContext* globalCtx);
void EnHorseLinkChild_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Horse_Link_Child_InitVars = {
    ACTOR_EN_HORSE_LINK_CHILD,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_HORSE_LINK_CHILD,
    sizeof(EnHorseLinkChild),
    (ActorFunc)EnHorseLinkChild_Init,
    (ActorFunc)EnHorseLinkChild_Destroy,
    (ActorFunc)EnHorseLinkChild_Update,
    (ActorFunc)EnHorseLinkChild_Draw,
};

// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_808DFED4[1] = {
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
        { 13, { { 0, 0, 0 }, 10 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_808DFEF8 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1 | OC2_UNK1, COLSHAPE_JNTSPH, },
    1, D_808DFED4, // sJntSphElementsInit,
};

// sColChkInfoInit
static CollisionCheckInfoInit D_808DFF08 = { 10, 35, 100, MASS_HEAVY };

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_808DFF2C[] = {
    ICHAIN_F32(uncullZoneScale, 1200, ICHAIN_STOP),
};

#endif

extern ColliderJntSphElementInit D_808DFED4[1];
extern ColliderJntSphInit D_808DFEF8;
extern CollisionCheckInfoInit D_808DFF08;
extern InitChainEntry D_808DFF2C[];

extern UNK_TYPE D_06002F98;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Link_Child/func_808DE5C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Link_Child/func_808DE660.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Link_Child/func_808DE728.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Link_Child/EnHorseLinkChild_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Link_Child/EnHorseLinkChild_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Link_Child/func_808DE9A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Link_Child/func_808DEA0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Link_Child/func_808DEA54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Link_Child/func_808DEB14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Link_Child/func_808DECA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Link_Child/func_808DED40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Link_Child/func_808DEFE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Link_Child/func_808DF088.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Link_Child/func_808DF194.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Link_Child/func_808DF560.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Link_Child/func_808DF620.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Link_Child/func_808DF788.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Link_Child/func_808DF838.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Link_Child/EnHorseLinkChild_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Link_Child/func_808DFC3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Link_Child/func_808DFDC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Horse_Link_Child/EnHorseLinkChild_Draw.s")
