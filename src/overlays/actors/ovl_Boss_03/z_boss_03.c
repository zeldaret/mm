/*
 * File: z_boss_03.c
 * Overlay: ovl_Boss_03
 * Description: Gyorg
 */

#include "z_boss_03.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((Boss03*)thisx)

void Boss03_Init(Actor* thisx, GlobalContext* globalCtx);
void Boss03_Destroy(Actor* thisx, GlobalContext* globalCtx);
void Boss03_Update(Actor* thisx, GlobalContext* globalCtx);
void Boss03_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_809E344C(Boss03* this, GlobalContext* globalCtx);
void func_809E34B8(Boss03* this, GlobalContext* globalCtx);
void func_809E3968(Boss03* this, GlobalContext* globalCtx);
void func_809E3D98(Boss03* this, GlobalContext* globalCtx);
void func_809E421C(Boss03* this, GlobalContext* globalCtx);
void func_809E475C(Boss03* this, GlobalContext* globalCtx);
void func_809E497C(Boss03* this, GlobalContext* globalCtx);
void func_809E4C90(Boss03* this, GlobalContext* globalCtx);
void func_809E4E80(Boss03* this, GlobalContext* globalCtx);
void func_809E5B64(Boss03* this, GlobalContext* globalCtx);
void func_809E6640(Boss03* this, GlobalContext* globalCtx);
void func_809E6BC0(Boss03* this, GlobalContext* globalCtx);

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
extern AnimationHeader D_06009CF8;
extern AnimationHeader D_0600A6C8;

void func_809E8810(Actor* thisx, GlobalContext* globalCtx);
void func_809E8BEC(Actor* thisx, GlobalContext* globalCtx);

void func_809E4E2C(Boss03* this, GlobalContext* globalCtx);

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E2760.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E2788.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E2880.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E299C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E2AB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E2B8C.s")


extern s32 D_809EC034; // sRandSeed0
extern s32 D_809EC038; // sRandSeed1
extern s32 D_809EC03C; // sRandSeed2

// Boss03_SeedRand(s32 seed0, s32 seed1, s32 seed2)
void func_809E2C1C(s32 seed0, s32 seed1, s32 seed2) {
    D_809EC034 = seed0;
    D_809EC038 = seed1;
    D_809EC03C = seed2;
}

// Boss03_RandZeroOne
f32 func_809E2C3C(void) {
    f32 rand;

    // Wichmann-Hill algorithm
    D_809EC034 = (D_809EC034 * 171) % 30269;
    D_809EC038 = (D_809EC038 * 172) % 30307;
    D_809EC03C = (D_809EC03C * 170) % 30323;

    rand = (D_809EC034 / 30269.0f) + (D_809EC038 / 30307.0f) + (D_809EC03C / 30323.0f);
    while (rand >= 1.0f) {
        rand -= 1.0f;
    }

    return fabsf(rand);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E2D64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E2DA0.s")

extern u8 D_809E9842;
extern Vec3f D_809E8FE8;
extern Boss03* D_809EC030;

typedef struct {
    /* 0x000 */ s8 unk_000;
    /* 0x001 */ UNK_TYPE1 unk_001[0x03];
    /* 0x004 */ UNK_TYPE1 unk_004[0x40];
} struct_809E9858; // size = 0x44

extern struct_809E9858 D_809E9858[150];

#ifdef NON_EQUIVALENT
void Boss03_Init(Actor* thisx, GlobalContext* globalCtx) {
    Vec3f sp70;
    s32 phi_s2;
    s32 phi_s3;
    s32 phi_s1;
    s32 phi_s4;
    Boss03* this = (Boss03* ) thisx;
    s32 i;
    s32 j;

    if ((gSaveContext.weekEventReg[0x37] & 0x80) != 0) {
        // ACTOR_DOOR_WARP1
        Actor_SpawnAsChild(&globalCtx->actorCtx, &this->actor, globalCtx, 0x38, 0.0f, 440.0f, 200.0f, 0, 0, 0, 1);
        // ACTOR_ITEM_B_HEART
        Actor_Spawn(&globalCtx->actorCtx, globalCtx, 0x3A, 0.0f, 440.0f, 0.0f, 0, 0, 0, 0);
        Actor_MarkForDeath(&this->actor);
        return;
    }

    if (this->actor.params == 0x23) {
        this->actor.update = func_809E8810;
        this->actor.draw = func_809E8BEC;

        this->unk_240 = Rand_ZeroFloat(1000.0f);

        this->actor.scale.x = Rand_ZeroFloat(0.0075f) + 0.027f;
        this->actor.scale.y = 0.02f;
        this->actor.scale.z = 0.015f;

        phi_s2 = 0;
        phi_s3 = 0;
        phi_s1 = 0;
        for (i = 0; i < 6; i++) {
            this->jointTable[i].x = Math_SinS((this->unk_240 * 0x100) + phi_s2) * 3000.0f;
            this->jointTable[i].y = Math_SinS((this->unk_240 * 0x180) + phi_s3) * 2000.0f;
            this->jointTable[i].z = Math_SinS((this->unk_240 * 0x10) + phi_s1) * 4000.0f;

            phi_s2 += 0x3A98; // 15000
            phi_s3 += 0x4E20; // 20000
            phi_s1 += 0x4A38; // 19000
        }

        this->actor.flags &= ~1;
        return;
    }

    this->actor.world.pos = D_809E8FE8;

    func_809E2C1C(1, 0x71A5, 0x263A);

    //for (phi_s4 = 0; phi_s4 < 5; phi_s4++) 
    for (phi_s4 = 0; (unsigned int) (phi_s4 < 5); phi_s4++)
    {
        Matrix_InsertYRotation_f((func_809E2C3C() * 3.1415927f * 0.2f) + (1.2566371f * phi_s4), 0);
        Matrix_GetStateTranslationAndScaledZ((func_809E2C3C() * 800.0f) + 400.0f, &sp70);
        // ACTOR_BOSS_03
        Actor_Spawn(&globalCtx->actorCtx, globalCtx, 0x12B, sp70.x, sp70.y, sp70.z, 0, (s16) (func_809E2C3C() * 65536.0f), 0, 0x23);
    }

    D_809EC030 = this;

    globalCtx->specialEffects = D_809E9858;

    for (j = 0; j < ARRAY_COUNT(D_809E9858); j++) {
        D_809E9858[j].unk_000 = 0;
    }

    this->actor.targetMode = 5;
    this->actor.colChkInfo.mass = 0xFE;
    this->actor.colChkInfo.health = 0xA;
    Collider_InitAndSetJntSph(globalCtx, &this->collider1, &this->actor, &D_809E8F14, this->unk_34C);
    Collider_InitAndSetJntSph(globalCtx, &this->collider2, &this->actor, &D_809E8FD8, this->unk_3EC);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &gGyorgSkel, &D_0600A6C8, this->jointTable, this->morphTable, GYORG_LIMB_MAX);
    Actor_SetScale(&this->actor, 0.2f);

    if ((gGameInfo->data[0x520] != 0) || ((gSaveContext.eventInf[5] & 0x40) != 0)) {
        this->actionFunc = func_809E344C;
        D_809E9842 = 0;
        Audio_QueueSeqCmd(0x100100FF);
    } else {
        func_809E4E2C(this, globalCtx);
        D_809E9842 = 1;
    }

    this->unk_252 = -1;
    this->unk_258 = 430.0f;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/Boss03_Init.s")
#endif

void Boss03_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    Boss03* this = THIS;
}

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

void func_809E4E2C(Boss03* this, GlobalContext* globalCtx) {
    this->actionFunc = func_809E4E80;
    Animation_MorphToLoop(&this->skelAnime, &D_06009CF8, -10.0f);
    this->skelAnime.playSpeed = 2.0f;
}

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

s32 func_809E79C4(GlobalContext* arg0, s32 arg1, Gfx** arg2, Vec3f* arg3, Vec3s* arg4, Actor* arg5);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E79C4.s")

void func_809E7AA8(GlobalContext* arg0, s32 arg1, Gfx** arg2, Vec3s* arg3, Actor* arg4);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E7AA8.s")

void Boss03_Draw(Actor* thisx, GlobalContext* globalCtx) {
    Boss03* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    if (this->unk_2D5 == 0) {
        if ((this->unk_25E & 1) != 0) {
            POLY_OPA_DISP = Gfx_SetFog(POLY_OPA_DISP, 255, 0, 0, 255, 900, 1099);
        }
        Matrix_InsertYRotation_f(this->unk_260, MTXMODE_APPLY);
        Matrix_InsertTranslation(0.0f, -600.0f, 0.0f, MTXMODE_APPLY);
        SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount, func_809E79C4, func_809E7AA8, &this->actor);
        POLY_OPA_DISP = func_801660B8(globalCtx, POLY_OPA_DISP);
    }

    this->unk_2BC = 0;
    func_809E81E4(globalCtx);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E7D00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E81E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E8810.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_03/func_809E8BEC.s")
