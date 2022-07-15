/*
 * File: z_en_rat.c
 * Overlay: ovl_En_Rat
 * Description: Real Bombchu
 */

#include "z_en_rat.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_200)

#define THIS ((EnRat*)thisx)

void EnRat_Init(Actor* thisx, PlayState* play);
void EnRat_Destroy(Actor* thisx, PlayState* play);
void EnRat_Update(Actor* thisx, PlayState* play);
void EnRat_Draw(Actor* thisx, PlayState* play);

void func_80A563CC(EnRat* this);
void func_80A5665C(EnRat* this);
void func_80A57330(EnRat* this);
void func_80A57384(EnRat* this, PlayState* play);
void func_80A57488(EnRat* this);
void func_80A574E8(EnRat* this, PlayState* play);
void func_80A575F4(EnRat* this);
void func_80A5764C(EnRat* this, PlayState* play);
void func_80A57984(EnRat* this, PlayState* play);
void func_80A57A9C(EnRat* this, PlayState* play);
void func_80A5723C(EnRat* this, PlayState* play);
void func_80A57A08(EnRat* this, PlayState* play);
s32 func_80A56AFC(EnRat* this, PlayState* play);
void func_80A57918(EnRat* this);

#if 0
const ActorInit En_Rat_InitVars = {
    ACTOR_EN_RAT,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_RAT,
    sizeof(EnRat),
    (ActorFunc)EnRat_Init,
    (ActorFunc)EnRat_Destroy,
    (ActorFunc)EnRat_Update,
    (ActorFunc)EnRat_Draw,
};

// static ColliderSphereInit sSphereInit = {
static ColliderSphereInit D_80A58400 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_SPHERE, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x08 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_HARD, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
    { 1, { { 0, 0, 0 }, 23 }, 100 },
};

// static DamageTable sDamageTable = {
static DamageTable D_80A5842C = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0xF),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(1, 0x0),
    /* Fire arrow     */ DMG_ENTRY(2, 0x0),
    /* Ice arrow      */ DMG_ENTRY(2, 0x0),
    /* Light arrow    */ DMG_ENTRY(2, 0x0),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(1, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(2, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x1),
    /* Zora barrier   */ DMG_ENTRY(1, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0x0),
    /* Zora punch     */ DMG_ENTRY(1, 0x0),
    /* Spin attack    */ DMG_ENTRY(1, 0x0),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0x0),
};

// sColChkInfoInit
static CollisionCheckInfoInit D_80A5844C = { 1, 30, 30, 50 };

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80A58464[] = {
    ICHAIN_S8(hintId, 97, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 15, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 5000, ICHAIN_STOP),
};

#endif

extern ColliderSphereInit D_80A58400;
extern DamageTable D_80A5842C;
extern CollisionCheckInfoInit D_80A5844C;
extern InitChainEntry D_80A58464[];

extern AnimationHeader D_06000174;
extern AnimationHeader D_0600026C;
extern FlexSkeletonHeader D_06001858;

extern s16 D_80A58428;
extern TexturePtr D_80A58454[];
extern EffectBlureInit2 D_80A58470;
extern s32 D_80A58494;
extern Vec3f D_80A584A8;
extern Vec3f D_80A584B4;
extern Vec3f D_80A584C0;
extern Vec3f D_80A584CC;
extern Vec3f D_80A58498;
extern Color_RGBA8 D_80A584A4;

void EnRat_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    EnRat* this = THIS;
    s32 temp_s1;
    s32 i;

    Actor_ProcessInitChain(&this->actor, D_80A58464);
    Collider_InitAndSetSphere(play, &this->collider, &this->actor, &D_80A58400);
    this->collider.dim.worldSphere.radius = D_80A58428;

    temp_s1 = this->actor.params & 0xFF;
    if (ENRAT_GET_8000(&this->actor)) {
        this->actor.params = 1;
    } else {
        this->actor.params = 0;
    }

    SkelAnime_InitFlex(play, &this->skelAnime, &D_06001858, &D_0600026C, this->jointTable, this->morphTable, 10);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 25.0f);
    if (this->actor.params == 0) {
        Effect_Add(play, &this->unk_260, EFFECT_BLURE2, 0, 0, &D_80A58470);
        Effect_Add(play, &this->unk_264, EFFECT_BLURE2, 0, 0, &D_80A58470);
        this->unk_190 = 0x1E;
    } else {
        this->unk_190 = 0x96;
    }

    CollisionCheck_SetInfo(&this->actor.colChkInfo, &D_80A5842C, &D_80A5844C);
    func_80A563CC(this);
    func_80A5665C(this);

    if ((temp_s1 == 0xFF) || (temp_s1 == 0)) {
        this->unk_258 = 350.0f;
    } else if (this->actor.params == 0) {
        this->unk_258 = temp_s1 * 0.1f * 40.0f;
    } else {
        this->unk_258 = temp_s1 * 0.5f * 40.0f;
    }

    if (!D_80A58494) {
        for (i = 0; i < 4; i++) {
            D_80A58454[i] = Lib_SegmentedToVirtual(D_80A58454[i]);
        }

        D_80A58494 = true;
    }

    func_80A57330(this);
}

void EnRat_Destroy(Actor* thisx, PlayState* play) {
    EnRat* this = THIS;

    if (this->actor.params == 0) {
        Effect_Destroy(play, this->unk_260);
        Effect_Destroy(play, this->unk_264);
    }

    Collider_DestroySphere(play, &this->collider);
}

void func_80A563CC(EnRat* this) {
    Matrix_RotateYS(this->actor.shape.rot.y, MTXMODE_NEW);
    Matrix_RotateXS(this->actor.shape.rot.x, MTXMODE_APPLY);
    Matrix_RotateZS(this->actor.shape.rot.z, MTXMODE_APPLY);
    Matrix_MultVecZ(1.0f, &this->unk_20C);
    Matrix_MultVecY(1.0f, &this->unk_218);
    Matrix_MultVecX(1.0f, &this->unk_224);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A56444.s")

void func_80A5665C(EnRat* this) {
    MtxF sp18;

    sp18.xx = this->unk_224.x;
    sp18.yx = this->unk_224.y;
    sp18.zx = this->unk_224.z;
    sp18.xy = this->unk_218.x;
    sp18.yy = this->unk_218.y;
    sp18.zy = this->unk_218.z;
    sp18.xz = this->unk_20C.x;
    sp18.yz = this->unk_20C.y;
    sp18.zz = this->unk_20C.z;
    Matrix_MtxFToYXZRot(&sp18, &this->actor.world.rot, 0);
    this->actor.world.rot.x = -this->actor.world.rot.x;
}

void func_80A566E0(EnRat* this);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A566E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A56994.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A56AFC.s")

void func_80A56EB8(EnRat* this, Vec3f* arg1, Vec3f* arg2) {
    f32 temp_fv0;
    Vec3f* tmp2;
    Vec3f* tmp1;
    Vec3f* tmp0;

    temp_fv0 = arg1->x + this->unk_254;
    tmp2 = &this->unk_224;
    tmp1 = &this->unk_218;
    tmp0 = &this->unk_20C;
    arg2->x = this->actor.world.pos.x + (tmp2->x * temp_fv0) + (tmp1->x * arg1->y) + (tmp0->x * arg1->z);
    arg2->y = this->actor.world.pos.y + (tmp2->y * temp_fv0) + (tmp1->y * arg1->y) + (tmp0->y * arg1->z);
    arg2->z = this->actor.world.pos.z + (tmp2->z * temp_fv0) + (tmp1->z * arg1->y) + (tmp0->z * arg1->z);
}

void func_80A56F68(EnRat* this, PlayState* play) {
    s32 pad;
    Vec3f sp28;

    EffectSsGRipple_Spawn(play, &this->actor.world.pos, 70, 500, 0);
    sp28.x = this->actor.world.pos.x - (this->unk_20C.x * 10.0f);
    sp28.z = this->actor.world.pos.z - (this->unk_20C.z * 10.0f);
    sp28.y = this->actor.world.pos.y + 5.0f;
    EffectSsGSplash_Spawn(play, &sp28, NULL, NULL, 1, 450);
}

void func_80A57010(EnRat* this, PlayState* play);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A57010.s")

void func_80A57118(EnRat* this, PlayState* play) {
    func_800B0EB0(play, &this->unk_230, &gZeroVec3f, &D_80A58498, &D_80A584A4, &D_80A584A4, 75, 7, 8);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A57180.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A5723C.s")

void func_80A57330(EnRat* this) {
    Animation_PlayLoop(&this->skelAnime, &D_0600026C);
    this->unk_18E = 5;
    this->actor.speedXZ = 2.0f;
    this->actionFunc = func_80A57384;
}

void func_80A57384(EnRat* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    this->actor.speedXZ = 2.0f;
    if (Animation_OnFrame(&this->skelAnime, 0.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_BOMCHU_WALK);
        if (this->unk_18E != 0) {
            this->unk_18E--;
        }
    }

    if ((this->unk_18E == 0) && (Rand_ZeroOne() < 0.05f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_BOMCHU_VOICE);
        this->unk_18E = 5;
    }

    if (!(player->stateFlags3 & PLAYER_STATE3_100) && (this->actor.xzDistToPlayer < this->unk_258) &&
        (Player_GetMask(play) != PLAYER_MASK_STONE) && (Actor_IsFacingPlayer(&this->actor, 0x3800))) {
        func_80A57488(this);
    }
}

void func_80A57488(EnRat* this) {
    this->actor.flags |= ACTOR_FLAG_10;
    Animation_MorphToLoop(&this->skelAnime, &D_06000174, -5.0f);
    this->unk_18E = 3;
    this->actor.speedXZ = 0.0f;
    this->actionFunc = func_80A574E8;
}

void func_80A574E8(EnRat* this, PlayState* play) {
    if ((this->unk_18E == 3) && (Animation_OnFrame(&this->skelAnime, 5.0f))) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_BOMCHU_AIM);
    }

    if (Animation_OnFrame(&this->skelAnime, 0.0f)) {
        this->unk_18E--;
        if (this->unk_18E == 0) {
            func_80A575F4(this);
        }
    }
}

void func_80A57570(EnRat* this) {
    s32 i;
    Vec3f* ptr;

    for (i = 0; i < ARRAY_COUNT(this->unk_23C); i++) {
        ptr = &this->unk_23C[i];
        ptr->x = randPlusMinusPoint5Scaled(6.0f);
        ptr->y = randPlusMinusPoint5Scaled(6.0f);
        ptr->z = randPlusMinusPoint5Scaled(6.0f);
    }
}

void func_80A575F4(EnRat* this) {
    Animation_MorphToLoop(&this->skelAnime, &D_0600026C, -5.0f);
    this->actor.speedXZ = 6.1f;
    func_80A57570(this);
    this->actionFunc = func_80A5764C;
}

void func_80A5764C(EnRat* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    Vec3f sp48;
    Vec3f sp3C;

    this->actor.speedXZ = 6.1f;
    if (this->unk_18C != 0) {
        if (!(player->stateFlags3 & PLAYER_STATE3_100) && (Player_GetMask(play) != PLAYER_MASK_STONE) &&
            (Actor_IsFacingPlayer(&this->actor, 0x3000))) {
            this->unk_18C = 0;
        }
    } else if ((player->stateFlags3 & PLAYER_STATE3_100) || (Player_GetMask(play) == PLAYER_MASK_STONE)) {
        this->unk_18C = 1;
    }

    if (Animation_OnFrame(&this->skelAnime, 0.0f)) {
        if (this->unk_18E != 0) {
            this->unk_18E--;
        }

        Actor_PlaySfxAtPos(&this->actor, 0x3828U);
    }

    if (this->unk_190 != 0) {
        this->unk_190--;
    }

    if ((this->unk_190 == 0) && (this->actor.params == 0)) {
        this->unk_190 = 30;
    }

    func_80A57118(this, play);
    this->unk_254 =
        (5.0f + (Rand_ZeroOne() * 3.0f)) * Math_SinS(((Rand_ZeroOne() * 512.0f) + 12288.0f) * this->unk_190);

    if (this->actor.params == 0) {
        func_80A56EB8(this, &D_80A584A8, &sp48);
        func_80A56EB8(this, &D_80A584B4, &sp3C);
        EffectBlure_AddVertex(Effect_GetByIndex(this->unk_260), &sp48, &sp3C);
        func_80A56EB8(this, &D_80A584C0, &sp3C);
        EffectBlure_AddVertex(Effect_GetByIndex(this->unk_264), &sp48, &sp3C);
    } else if ((this->actor.floorPoly != NULL) && !(play->gameplayFrames & 3)) {
        func_800B1210(play, &this->actor.world.pos, &D_80A584CC, &gZeroVec3f, 550, 50);
    }

    if ((this->actor.floorPoly == NULL) && (Animation_OnFrame(&this->skelAnime, 0.0f))) {
        func_80A56F68(this, play);
    }

    if ((this->unk_18E == 0) && (Rand_ZeroOne() < 0.05f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_BOMCHU_AIM);
        this->unk_18E = 5;
    }

    func_800B9010(&this->actor, NA_SE_EN_BOMCHU_RUN - SFX_FLAG);
    func_80A57570(this);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A57918.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A57984.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A57A08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A57A9C.s")

void EnRat_Update(Actor* thisx, PlayState* play) {
    s32 pad;
    EnRat* this = THIS;

    this->unk_18D = 0;
    if (this->unk_192 == 0) {
        SkelAnime_Update(&this->skelAnime);
    }

    if (this->collider.base.atFlags & AT_HIT) {
        this->collider.base.atFlags &= ~AT_HIT;
        this->collider.base.acFlags &= ~AC_HIT;
        this->collider.base.ocFlags1 &= ~OC1_HIT;
        if (this->collider.base.atFlags & AT_BOUNCED) {
            func_80A57918(this);
        } else {
            func_80A57A08(this, play);
            return;
        }
    } else if (this->collider.base.acFlags & AC_HIT) {
        this->collider.base.acFlags &= ~AC_HIT;
        if (this->actor.colChkInfo.damageEffect == 0xF) {
            this->unk_192 = -2;
        } else if (this->actor.colChkInfo.damageEffect == 1) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_COMMON_FREEZE);
            Actor_SetColorFilter(&this->actor, 0, 120, 0, 40);
            if (this->actionFunc == func_80A57984) {
                this->actor.speedXZ = 0.0f;
                if (this->actor.velocity.y > 0.0f) {
                    this->actor.velocity.y = 0.0f;
                }
            } else {
                this->unk_192 = 40;
            }
        } else {
            func_80A57A08(this, play);
            return;
        }
    } else if (((this->collider.base.ocFlags1 & OC1_HIT) && (((this->collider.base.oc->category == ACTORCAT_ENEMY)) ||
                                                             (this->collider.base.oc->category == ACTORCAT_BOSS) ||
                                                             (this->collider.base.oc->category == ACTORCAT_PLAYER))) ||
               ((this->actionFunc == func_80A5764C) && (this->unk_190 == 0))) {
        this->collider.base.ocFlags1 &= ~OC1_HIT;
        func_80A57A08(this, play);
        return;
    }

    this->actionFunc(this, play);

    if ((this->actionFunc != func_80A57A9C) && (this->actionFunc != func_80A5723C)) {
        if (this->unk_192 > 0) {
            this->unk_192--;
        } else if (this->unk_192 < 0) {
            if (this->unk_192 == -2) {
                this->unk_192 = -1;
            } else if ((this->actor.flags & ACTOR_FLAG_2000) != ACTOR_FLAG_2000) {
                func_80A57A08(this, play);
                return;
            }
        } else if (this->actionFunc != func_80A57984) {
            if (this->actor.floorBgId != 0x32) {
                func_80A57010(this, play);
            }

            if (this->unk_18C == 0) {
                func_80A566E0(this);
            }

            if ((this->actionFunc != func_80A574E8) && !func_80A56AFC(this, play)) {
                func_80A57A08(this, play);
                return;
            }

            if (this->unk_18D != 0) {
                func_80A5665C(this);
                this->actor.shape.rot.x = -this->actor.world.rot.x;
                this->actor.shape.rot.y = this->actor.world.rot.y;
                this->actor.shape.rot.z = this->actor.world.rot.z;
            }

            Actor_MoveWithoutGravity(&this->actor);
            this->actor.floorHeight = this->actor.world.pos.y;
        } else {
            Actor_MoveWithGravity(&this->actor);
            Actor_UpdateBgCheckInfo(play, &this->actor, 20.0f, 30.0f, 60.0f, 7);
        }

        if (SurfaceType_IsWallDamage(&play->colCtx, this->actor.floorPoly, this->actor.floorBgId) != 0) {
            func_80A57A08(this, play);
            return;
        }

        this->collider.dim.worldSphere.center.x = this->actor.world.pos.x + (this->unk_218.x * 10.0f);
        this->collider.dim.worldSphere.center.y = this->actor.world.pos.y + (this->unk_218.y * 10.0f);
        this->collider.dim.worldSphere.center.z = this->actor.world.pos.z + (this->unk_218.z * 10.0f);

        if (this->actionFunc != func_80A5723C) {
            if (this->unk_192 == 0) {
                CollisionCheck_SetAT(play, &play->colChkCtx, &this->collider.base);
            }

            CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.base);
            CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
        }

        Actor_SetFocus(&this->actor, this->actor.shape.yOffset * 0.015f);
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A57F10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/func_80A57F4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rat/EnRat_Draw.s")
