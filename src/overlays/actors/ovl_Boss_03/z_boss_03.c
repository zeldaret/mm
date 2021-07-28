#include "z_boss_03.h"

#define FLAGS 0x00000035

#define THIS ((Boss03*)thisx)

void Boss03_Init(Actor* thisx, GlobalContext* globalCtx);
void Boss03_Destroy(Actor* thisx, GlobalContext* globalCtx);
void Boss03_Update(Actor* thisx, GlobalContext* globalCtx);
void Boss03_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Boss_03_InitVars = {
    ACTOR_BOSS_03,
    ACTORCAT_BOSS,
    FLAGS,
    OBJECT_BOSS03,
    sizeof(Boss03),
    (ActorFunc)Boss03_Init,
    (ActorFunc)Boss03_Destroy,
    (ActorFunc)Boss03_Update,
    (ActorFunc)Boss03_Draw,
};

// static ColliderJntSphElementInit sJntSphElementsInit[2] = {
static ColliderJntSphElementInit D_809E8ECC[2] = {
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x08 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 70 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x08 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 50 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_809E8F14 = {
    { COLTYPE_HIT3, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_PLAYER, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    2, D_809E8ECC, // sJntSphElementsInit,
};

// static ColliderJntSphElementInit sJntSphElementsInit[5] = {
static ColliderJntSphElementInit D_809E8F24[5] = {
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x08 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 2, { { 0, 0, 0 }, 20 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x08 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 5, { { 0, 0, 0 }, 20 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x08 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 6, { { 0, 0, 0 }, 70 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x08 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 7, { { 0, 0, 0 }, 70 }, 100 },
    },
    {
        { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x08 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 8, { { 0, 0, 0 }, 30 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_809E8FD8 = {
    { COLTYPE_METAL, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_PLAYER, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    5, D_809E8F24, // sJntSphElementsInit,
};

#endif

extern ColliderJntSphElementInit D_809E8ECC[2];
extern ColliderJntSphInit D_809E8F14;
extern ColliderJntSphElementInit D_809E8F24[5];
extern ColliderJntSphInit D_809E8FD8;

extern UNK_TYPE D_06007EB0;
extern UNK_TYPE D_06007EC8;
extern UNK_TYPE D_06009554;
extern UNK_TYPE D_060099D0;
extern UNK_TYPE D_06009C14;
extern UNK_TYPE D_06009CF8;
extern UNK_TYPE D_0600A6C8;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E2760.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E2788.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E2880.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E299C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E2AB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E2B8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E2C1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E2C3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E2D64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E2DA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/Boss03_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/Boss03_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E344C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E34B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E38EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E3968.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E3D34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E3D98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E4180.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E421C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E4674.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E475C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E4910.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E497C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E4C34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E4C90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E4E2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E4E80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E5ADC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E5B64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E65F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E6640.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E69A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E6A38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E6B70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E6BC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E6CB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/Boss03_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E7920.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E79C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E7AA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/Boss03_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E7D00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E81E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E8810.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E8BEC.s")
