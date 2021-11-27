/*
 * File: z_en_fishing.c
 * Overlay: ovl_En_Fishing
 * Description: Fishing
 */

#include "z_en_fishing.h"

#define FLAGS 0x00000010

#define THIS ((EnFishing*)thisx)

void EnFishing_Init(Actor* thisx, GlobalContext* globalCtx);
void EnFishing_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnFishing_Update(Actor* thisx, GlobalContext* globalCtx);
void EnFishing_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Fishing_InitVars = {
    ACTOR_EN_FISHING,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_FISH,
    sizeof(EnFishing),
    (ActorFunc)EnFishing_Init,
    (ActorFunc)EnFishing_Destroy,
    (ActorFunc)EnFishing_Update,
    (ActorFunc)EnFishing_Draw,
};

// static ColliderJntSphElementInit sJntSphElementsInit[12] = {
static ColliderJntSphElementInit D_8090CD58[12] = {
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 30 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 30 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 30 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 30 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 30 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 30 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 30 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 30 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 30 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 30 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 30 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 30 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_8090CF08 = {
    { COLTYPE_NONE, AT_NONE | AT_TYPE_ENEMY, AC_NONE | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_PLAYER, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    12, D_8090CD58, // sJntSphElementsInit,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_8090D4D0[] = {
    ICHAIN_U8(targetMode, 5, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 0, ICHAIN_STOP),
};

#endif

extern ColliderJntSphElementInit D_8090CD58[12];
extern ColliderJntSphInit D_8090CF08;
extern InitChainEntry D_8090D4D0[];

extern UNK_TYPE D_0600007C;
extern UNK_TYPE D_06003230;
extern UNK_TYPE D_0600453C;
extern UNK_TYPE D_060074C8;
extern UNK_TYPE D_06008678;
extern UNK_TYPE D_0600B950;
extern UNK_TYPE D_0600C220;
extern UNK_TYPE D_060113D0;
extern UNK_TYPE D_06012160;
extern UNK_TYPE D_060121F0;
extern UNK_TYPE D_06014030;
extern UNK_TYPE D_060153D0;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_808FC6C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_808FC770.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_808FC790.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_808FC8B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_808FC964.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_808FCABC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_808FCC0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_808FCDBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_808FCF60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_808FD054.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/EnFishing_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/EnFishing_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_808FDCDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_808FE3F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_808FEE1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_808FEF70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_808FF064.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_808FF5E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_808FF750.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_808FFC44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_808FFF3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_80900228.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_80900A04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_80901480.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_809033F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_809036BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_809038A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_80903C60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_80903E20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/EnFishing_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_80908554.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_80908674.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_809086B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_80908734.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/EnFishing_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_809089B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_80908A64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_80908B4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_80908E08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_80909234.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_80909AD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_80909CC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_8090AB6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_8090C884.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_8090C8BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Fishing/func_8090C96C.s")
