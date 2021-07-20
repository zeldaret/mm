#include "z_boss_03.h"

#define FLAGS 0x00000035

#define THIS ((Boss03*)thisx)

void Boss03_Init(Actor* thisx, GlobalContext* globalCtx);
void Boss03_Destroy(Actor* thisx, GlobalContext* globalCtx);
void Boss03_Update(Actor* thisx, GlobalContext* globalCtx);
void Boss03_Draw(Actor* thisx, GlobalContext* globalCtx);

/*

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

*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_03_0x809E2760/func_809E2760.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_03_0x809E2760/func_809E2788.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_03_0x809E2760/func_809E2880.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_03_0x809E2760/func_809E299C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_03_0x809E2760/func_809E2AB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_03_0x809E2760/func_809E2B8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_03_0x809E2760/func_809E2C1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_03_0x809E2760/func_809E2C3C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_03_0x809E2760/func_809E2D64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_03_0x809E2760/func_809E2DA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_03_0x809E2760/Boss03_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_03_0x809E2760/Boss03_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_03_0x809E2760/func_809E344C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_03_0x809E2760/func_809E34B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_03_0x809E2760/func_809E38EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_03_0x809E2760/func_809E3968.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_03_0x809E2760/func_809E3D34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_03_0x809E2760/func_809E3D98.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_03_0x809E2760/func_809E4180.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_03_0x809E2760/func_809E421C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_03_0x809E2760/func_809E4674.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_03_0x809E2760/func_809E475C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_03_0x809E2760/func_809E4910.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_03_0x809E2760/func_809E497C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_03_0x809E2760/func_809E4C34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_03_0x809E2760/func_809E4C90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_03_0x809E2760/func_809E4E2C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_03_0x809E2760/func_809E4E80.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_03_0x809E2760/func_809E5ADC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_03_0x809E2760/func_809E5B64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_03_0x809E2760/func_809E65F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_03_0x809E2760/func_809E6640.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_03_0x809E2760/func_809E69A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_03_0x809E2760/func_809E6A38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_03_0x809E2760/func_809E6B70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_03_0x809E2760/func_809E6BC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_03_0x809E2760/func_809E6CB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_03_0x809E2760/Boss03_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_03_0x809E2760/func_809E7920.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_03_0x809E2760/func_809E79C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_03_0x809E2760/func_809E7AA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_03_0x809E2760/Boss03_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_03_0x809E2760/func_809E7D00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_03_0x809E2760/func_809E81E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_03_0x809E2760/func_809E8810.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_03_0x809E2760/func_809E8BEC.asm")
