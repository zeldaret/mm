/*
 * File: z_en_syateki_dekunuts.c
 * Overlay: ovl_En_Syateki_Dekunuts
 * Description: Shooting Gallery Deku Scrub
 */

#include "z_en_syateki_dekunuts.h"
#include "overlays/actors/ovl_En_Syateki_Man/z_en_syateki_man.h"
#include "overlays/effects/ovl_Effect_Ss_Hahen/z_eff_ss_hahen.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20 | ACTOR_FLAG_8000000)

#define THIS ((EnSyatekiDekunuts*)thisx)

void EnSyatekiDekunuts_Init(Actor* thisx, PlayState* play2);
void EnSyatekiDekunuts_Destroy(Actor* thisx, PlayState* play);
void EnSyatekiDekunuts_Update(Actor* thisx, PlayState* play);
void EnSyatekiDekunuts_Draw(Actor* thisx, PlayState* play);

void EnSyatekiDekunuts_SetupWaitForSpawn(EnSyatekiDekunuts* this);
void EnSyatekiDekunuts_WaitForSpawn(EnSyatekiDekunuts* this, PlayState* play);
void EnSyatekiDekunuts_SetupSpawn(EnSyatekiDekunuts* this);
void EnSyatekiDekunuts_Spawn(EnSyatekiDekunuts* this, PlayState* play);
void EnSyatekiDekunuts_SetupWaitToEmerge(EnSyatekiDekunuts* this);
void EnSyatekiDekunuts_WaitToEmerge(EnSyatekiDekunuts* this, PlayState* play);
void EnSyatekiDekunuts_SetupEmerge(EnSyatekiDekunuts* this);
void EnSyatekiDekunuts_Emerge(EnSyatekiDekunuts* this, PlayState* play);
void EnSyatekiDekunuts_SetupLookAround(EnSyatekiDekunuts* this);
void EnSyatekiDekunuts_LookAround(EnSyatekiDekunuts* this, PlayState* play);
void EnSyatekiDekunuts_BonusLookAround(EnSyatekiDekunuts* this, PlayState* play);
void EnSyatekiDekunuts_SetupBurrow(EnSyatekiDekunuts* this);
void EnSyatekiDekunuts_Burrow(EnSyatekiDekunuts* this, PlayState* play);
void EnSyatekiDekunuts_SetupGameEnd(EnSyatekiDekunuts* this);
void EnSyatekiDekunuts_GameEnd(EnSyatekiDekunuts* this, PlayState* play);
void EnSyatekiDekunuts_Dead(EnSyatekiDekunuts* this, PlayState* play);

typedef enum {
    /* 0 */ EN_SYATEKI_DEKUNUTS_HEADDRESS_TYPE_NORMAL,
    /* 1 */ EN_SYATEKI_DEKUNUTS_HEADDRESS_TYPE_FLIPPED_UP,
} EnSyatekiDekunutsHeaddressType;

ActorInit En_Syateki_Dekunuts_InitVars = {
    ACTOR_EN_SYATEKI_DEKUNUTS,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_DEKUNUTS,
    sizeof(EnSyatekiDekunuts),
    {
        EnSyatekiDekunuts_Init,
        EnSyatekiDekunuts_Destroy,
        EnSyatekiDekunuts_Update,
        EnSyatekiDekunuts_Draw,
    },
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_HIT6,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_NONE,
    },
    { 48, 80, 0, { 0, 0, 0 } },
};

static Cylinder16 sBonusDekuScrubColliderDimensions[] = { { 24, 40, 0, { 0, 0, 0 } } };

typedef enum {
    /* 0 */ EN_SYATEKI_DEKUNUTS_ANIM_UP,
    /* 1 */ EN_SYATEKI_DEKUNUTS_ANIM_BURROW,
    /* 2 */ EN_SYATEKI_DEKUNUTS_ANIM_IDLE, // unused
    /* 3 */ EN_SYATEKI_DEKUNUTS_ANIM_LOOK_AROUND,
    /* 4 */ EN_SYATEKI_DEKUNUTS_ANIM_DAMAGE,
    /* 5 */ EN_SYATEKI_DEKUNUTS_ANIM_DIE,
    /* 6 */ EN_SYATEKI_DEKUNUTS_ANIM_UNBURROW, // unused
} EnSyatekiDekunutsAnimation;

static AnimationInfo sAnimationInfo[] = {
    { &gDekuScrubUpAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, -1.0f },
    { &gDekuScrubBurrowAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, -1.0f },
    { &gDekuScrubIdleAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -1.0f },
    { &gDekuScrubLookAroundAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -1.0f },
    { &gDekuScrubDamageAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, -1.0f },
    { &gDekuScrubDieAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, -1.0f },
    { &gDekuScrubUnburrowAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, -1.0f },
};

static InitChainEntry sInitChain[] = {
    ICHAIN_S8(hintId, TATL_HINT_ID_MAD_SCRUB, ICHAIN_CONTINUE),
    ICHAIN_F32(gravity, 0, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 2600, ICHAIN_STOP),
};

void EnSyatekiDekunuts_Init(Actor* thisx, PlayState* play2) {
    static s32 sDrawFlowers = true; // This makes it so only one EnSyatekiDekunuts draws all the flowers.
    EnSyatekiDekunuts* this = THIS;
    PlayState* play = play2;
    s32 unkPathComparison;
    Path* path;
    EnSyatekiMan* syatekiMan = (EnSyatekiMan*)this->actor.parent;
    s32 i;

    path = syatekiMan->path;
    Collider_InitCylinder(play, &this->collider);
    Collider_SetCylinder(play, &this->collider, &this->actor, &sCylinderInit);

    if (EN_SYATEKI_DEKUNUTS_GET_TYPE(&this->actor) == EN_SYATEKI_DEKUNUTS_TYPE_BONUS) {
        Actor_SetScale(&this->actor, 0.01f);
        this->collider.dim = sBonusDekuScrubColliderDimensions[0];
        unkPathComparison = 3;
    } else {
        Actor_SetScale(&this->actor, 0.02f);
        unkPathComparison = 1;
    }

    while (path->unk2 != unkPathComparison) {
        path = &play->setupPathList[path->unk1];
    }

    for (i = 0; i < EN_SYATEKI_DEKUNUTS_GET_PARAM_FF00(&this->actor); i++) {
        path = &play->setupPathList[path->unk1];
    }

    if (sDrawFlowers == true) {
        this->shouldDrawFlowers = true;
        sDrawFlowers = false;
    } else {
        this->shouldDrawFlowers = false;
    }

    Actor_ProcessInitChain(&this->actor, sInitChain);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 35.0f);
    SkelAnime_Init(play, &this->skelAnime, &gDekuScrubSkel, &gDekuScrubBurrowAnim, this->jointTable, this->morphTable,
                   DEKU_SCRUB_LIMB_MAX);

    if (path == NULL) {
        Actor_Kill(&this->actor);
        return;
    }

    this->flowerPos = Lib_SegmentedToVirtual(path->points);
    this->index = EN_SYATEKI_DEKUNUTS_GET_INDEX(&this->actor);
    this->flowerCount = path->count;
    this->timer = 0;
    this->unk_1DC = 0;
    this->waitTimer = 0;
    EnSyatekiDekunuts_SetupWaitForSpawn(this);
}

void EnSyatekiDekunuts_Destroy(Actor* thisx, PlayState* play) {
    EnSyatekiDekunuts* this = THIS;

    Collider_DestroyCylinder(play, &this->collider);
}

void EnSyatekiDekunuts_SetupWaitForSpawn(EnSyatekiDekunuts* this) {
    Animation_PlayOnceSetSpeed(&this->skelAnime, &gDekuScrubUpAnim, 0.0f);

    this->actor.speedXZ = 0.0f;
    this->actor.world = this->actor.home;
    this->actor.prevPos = this->actor.home.pos;
    this->actor.shape.rot = this->actor.world.rot;

    this->timer = 0;
    this->unk_1DC = 0;

    if (EN_SYATEKI_DEKUNUTS_GET_TYPE(&this->actor) != EN_SYATEKI_DEKUNUTS_TYPE_BONUS) {
        this->isAlive = true;
    }

    this->actionFunc = EnSyatekiDekunuts_WaitForSpawn;
}

/**
 * Waits until the shooting gallery man sets the appropriate Deku Scrub flag to spawn.
 */
void EnSyatekiDekunuts_WaitForSpawn(EnSyatekiDekunuts* this, PlayState* play) {
    EnSyatekiMan* syatekiMan = (EnSyatekiMan*)this->actor.parent;

    if ((syatekiMan->shootingGameState == SG_GAME_STATE_RUNNING) && (this->isAlive == true) &&
        (syatekiMan->dekuScrubFlags & (1 << this->index))) {
        EnSyatekiDekunuts_SetupSpawn(this);
    } else if (syatekiMan->shootingGameState != SG_GAME_STATE_RUNNING) {
        this->isAlive = true;
    }

    if (!syatekiMan->dekuScrubFlags && !syatekiMan->guayFlags &&
        (EN_SYATEKI_DEKUNUTS_GET_TYPE(&this->actor) != EN_SYATEKI_DEKUNUTS_TYPE_BONUS)) {
        this->isAlive = true;
    }
}

/**
 * Positions the Deku Scrub to match up with its flower, then sets it up to start waiting.
 */
void EnSyatekiDekunuts_SetupSpawn(EnSyatekiDekunuts* this) {
    Vec3f pos;
    EnSyatekiMan* syatekiMan = (EnSyatekiMan*)this->actor.parent;

    this->timer = 0;
    pos.x = this->flowerPos[this->index].x;
    pos.y = this->flowerPos[this->index].y;
    pos.z = this->flowerPos[this->index].z;
    this->actor.world.pos = this->actor.prevPos = pos;
    this->actor.world.rot.y = this->actor.yawTowardsPlayer;
    this->actor.shape.rot.y = this->actor.yawTowardsPlayer;
    this->timeToBurrow = 140 - (syatekiMan->currentWave * 20);

    if ((syatekiMan->currentWave % 2) != 0) {
        this->headdressType = EN_SYATEKI_DEKUNUTS_HEADDRESS_TYPE_FLIPPED_UP;
        this->headdressRotZ = 0;
    } else {
        this->headdressType = EN_SYATEKI_DEKUNUTS_HEADDRESS_TYPE_NORMAL;
    }

    this->actionFunc = EnSyatekiDekunuts_Spawn;
}

/**
 * Waits 20 frames, then plays a sound and starts the process of making the Deku Scrubs emerge.
 */
void EnSyatekiDekunuts_Spawn(EnSyatekiDekunuts* this, PlayState* play) {
    EnSyatekiMan* syatekiMan;

    if (this->waitTimer > 20) {
        syatekiMan = (EnSyatekiMan*)this->actor.parent;
        Actor_PlaySfxAtPos(&syatekiMan->actor, NA_SE_EN_NUTS_DAMAGE);
        this->waitTimer = 0;
        EnSyatekiDekunuts_SetupWaitToEmerge(this);
    } else {
        this->waitTimer++;
    }
}

void EnSyatekiDekunuts_SetupWaitToEmerge(EnSyatekiDekunuts* this) {
    this->timer = 0;
    this->actionFunc = EnSyatekiDekunuts_WaitToEmerge;
}

/**
 * Waits 20 frames, then makes the Deku Scrubs emerge from underground.
 */
void EnSyatekiDekunuts_WaitToEmerge(EnSyatekiDekunuts* this, PlayState* play) {
    if (this->waitTimer > 20) {
        EnSyatekiDekunuts_SetupEmerge(this);
        this->waitTimer = 0;
    } else {
        this->waitTimer++;
    }
}

void EnSyatekiDekunuts_SetupEmerge(EnSyatekiDekunuts* this) {
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_NUTS_UP);
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, EN_SYATEKI_DEKUNUTS_ANIM_UP);
    this->actor.shape.rot.y = this->actor.yawTowardsPlayer;
    this->actor.world.rot.y = this->actor.yawTowardsPlayer;
    this->actionFunc = EnSyatekiDekunuts_Emerge;
}

/**
 * Waits until the animation for coming out of the ground is done playing, then makes the
 * Deku Scrubs look around. If the headdress should be flipped up, then this will also
 * adjust the headdress's rotation.
 */
void EnSyatekiDekunuts_Emerge(EnSyatekiDekunuts* this, PlayState* play) {
    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        EnSyatekiDekunuts_SetupLookAround(this);
    }

    if (this->headdressType == EN_SYATEKI_DEKUNUTS_HEADDRESS_TYPE_FLIPPED_UP) {
        Math_SmoothStepToS(&this->headdressRotZ, -0x8000, 5, 0x1000, 0x100);
    }

    this->timer++;
}

void EnSyatekiDekunuts_SetupLookAround(EnSyatekiDekunuts* this) {
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, EN_SYATEKI_DEKUNUTS_ANIM_LOOK_AROUND);
    if (EN_SYATEKI_DEKUNUTS_GET_TYPE(&this->actor) != EN_SYATEKI_DEKUNUTS_TYPE_BONUS) {
        this->actionFunc = EnSyatekiDekunuts_LookAround;
    } else {
        this->actionFunc = EnSyatekiDekunuts_BonusLookAround;
    }
}

/**
 * Looks around back and forth until the timer reaches the time to burrow or until the game ends.
 * No matter which occurs, the Deku Scrubs burrow underground afterwards.
 */
void EnSyatekiDekunuts_LookAround(EnSyatekiDekunuts* this, PlayState* play) {
    EnSyatekiMan* syatekiMan = (EnSyatekiMan*)this->actor.parent;

    if ((this->timeToBurrow < this->timer) || (syatekiMan->shootingGameState != SG_GAME_STATE_RUNNING)) {
        EnSyatekiDekunuts_SetupBurrow(this);
    }

    this->timer++;
}

/**
 * Looks around back and forth until the game ends, then burrow underground afterwards.
 */
void EnSyatekiDekunuts_BonusLookAround(EnSyatekiDekunuts* this, PlayState* play) {
    EnSyatekiMan* syatekiMan = (EnSyatekiMan*)this->actor.parent;

    // There are some cases where the minigame timer can reach 0, but the shooting game state is
    // still SG_GAME_STATE_RUNNING. This check just makes absolutely sure that once the game is
    // over, these Deku Scrubs will burrow.
    if ((gSaveContext.timerCurTimes[TIMER_ID_MINIGAME_1] <= SECONDS_TO_TIMER(0)) ||
        (syatekiMan->shootingGameState != SG_GAME_STATE_RUNNING)) {
        EnSyatekiDekunuts_SetupBurrow(this);
    }

    if (this->timer <= 10) {
        this->timer++;
    }
}

void EnSyatekiDekunuts_SetupBurrow(EnSyatekiDekunuts* this) {
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, EN_SYATEKI_DEKUNUTS_ANIM_BURROW);
    this->actionFunc = EnSyatekiDekunuts_Burrow;
}

/**
 * Burrow underground. After 160 frames have passed since the Deku Scrub first emerged *and*
 * after the burrowing animation is complete, this sets up the Deku Scrub to emerge again.
 */
void EnSyatekiDekunuts_Burrow(EnSyatekiDekunuts* this, PlayState* play) {
    EnSyatekiMan* syatekiMan = (EnSyatekiMan*)this->actor.parent;

    if (syatekiMan->shootingGameState == SG_GAME_STATE_RUNNING) {
        if ((this->timer > 160) && Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
            this->timer = 0;
            EnSyatekiDekunuts_SetupWaitToEmerge(this);
        } else {
            this->timer++;
        }
    } else {
        EnSyatekiDekunuts_SetupGameEnd(this);
    }
}

void EnSyatekiDekunuts_SetupGameEnd(EnSyatekiDekunuts* this) {
    this->actionFunc = EnSyatekiDekunuts_GameEnd;
}

/**
 * Waits 20 frames, then resets the Deku Scrub back to its initial state.
 */
void EnSyatekiDekunuts_GameEnd(EnSyatekiDekunuts* this, PlayState* play) {
    if (this->waitTimer > 20) {
        EnSyatekiDekunuts_SetupWaitForSpawn(this);
        this->waitTimer = 0;
    } else {
        this->waitTimer++;
    }
}

void EnSyatekiDekunuts_SetupDead(EnSyatekiDekunuts* this, PlayState* play) {
    static Vec3f sVelocity = { 0.0f, 20.0f, 0.0f };
    static Vec3f sAccel = { 0.0f, 0.0f, 0.0f };
    EnSyatekiMan* syatekiMan = (EnSyatekiMan*)this->actor.parent;

    if (EN_SYATEKI_DEKUNUTS_GET_TYPE(&this->actor) == EN_SYATEKI_DEKUNUTS_TYPE_BONUS) {
        EffectSsExtra_Spawn(play, &this->actor.world.pos, &sVelocity, &sAccel, 5, 2);
        syatekiMan->score += 100;
        syatekiMan->perGameVar2.bonusDekuScrubHitCounter++;
    } else {
        EffectSsExtra_Spawn(play, &this->actor.world.pos, &sVelocity, &sAccel, 5, 0);
        syatekiMan->score += 30;
        syatekiMan->dekuScrubHitCounter++;
    }

    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_NUTS_DAMAGE);
    this->isAlive = false;
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, EN_SYATEKI_DEKUNUTS_ANIM_DAMAGE);
    this->timer = 160;
    this->actionFunc = EnSyatekiDekunuts_Dead;
}

void EnSyatekiDekunuts_Dead(EnSyatekiDekunuts* this, PlayState* play) {
    static Color_RGBA8 sPrimColor = { 255, 255, 255, 255 };
    static Color_RGBA8 sEnvColor = { 150, 150, 150, 0 };
    EnSyatekiMan* syatekiMan = (EnSyatekiMan*)this->actor.parent;

    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        if (this->timer == 160) {
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, EN_SYATEKI_DEKUNUTS_ANIM_DIE);
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_NUTS_DEAD);
            this->timer--;
        } else if (this->timer < 160) {
            Vec3f pos;

            pos.x = this->actor.world.pos.x;
            pos.y = this->actor.world.pos.y + 18.0f;
            pos.z = this->actor.world.pos.z;
            EffectSsDeadDb_Spawn(play, &pos, &gZeroVec3f, &gZeroVec3f, &sPrimColor, &sEnvColor, 200, 0, 13);
            SoundSource_PlaySfxAtFixedWorldPos(play, &this->actor.world.pos, 30, NA_SE_EN_EXTINCT);
            pos.y = this->actor.world.pos.y + 10.0f;
            EffectSsHahen_SpawnBurst(play, &pos, 3.0f, 0, 12, 3, 15, HAHEN_OBJECT_DEFAULT, 10, NULL);

            if (EN_SYATEKI_DEKUNUTS_GET_TYPE(&this->actor) != EN_SYATEKI_DEKUNUTS_TYPE_BONUS) {
                syatekiMan->dekuScrubFlags &= ~(1 << this->index);
            }

            EnSyatekiDekunuts_SetupWaitForSpawn(this);
        }
    } else if (this->timer < 160) {
        this->timer--;
    }
}

void EnSyatekiDekunuts_Update(Actor* thisx, PlayState* play) {
    s32 pad;
    EnSyatekiDekunuts* this = THIS;

    this->actionFunc(this, play);

    if ((this->actionFunc != EnSyatekiDekunuts_WaitForSpawn) && (this->timer < this->timeToBurrow) &&
        (this->timer > 10)) {
        if ((this->collider.base.acFlags & AC_HIT) && (this->isAlive == true)) {
            if (EN_SYATEKI_DEKUNUTS_GET_TYPE(&this->actor) == EN_SYATEKI_DEKUNUTS_TYPE_BONUS) {
                Audio_PlayFanfare(NA_BGM_GET_ITEM | 0x900);
            } else {
                play_sound(NA_SE_SY_TRE_BOX_APPEAR);
            }

            this->collider.base.acFlags &= ~AC_HIT;
            EnSyatekiDekunuts_SetupDead(this, play);
        }

        Collider_UpdateCylinder(&this->actor, &this->collider);
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.base);
    } else {
        this->collider.base.acFlags &= ~AC_HIT;
    }

    SkelAnime_Update(&this->skelAnime);
}

s32 EnSyatekiDekunuts_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                                       Actor* thisx) {
    EnSyatekiDekunuts* this = THIS;

    if ((limbIndex == DEKU_SCRUB_LIMB_HEADDRESS) &&
        (this->headdressType == EN_SYATEKI_DEKUNUTS_HEADDRESS_TYPE_FLIPPED_UP)) {
        rot->z += this->headdressRotZ;
    }

    return false;
}

void EnSyatekiDekunuts_Draw(Actor* thisx, PlayState* play) {
    EnSyatekiDekunuts* this = THIS;
    Vec3f flowerPos;
    s32 i;

    if (this->actionFunc != EnSyatekiDekunuts_WaitForSpawn) {
        SkelAnime_DrawOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable,
                          EnSyatekiDekunuts_OverrideLimbDraw, NULL, &this->actor);
    }

    if (this->shouldDrawFlowers == true) {
        for (i = 0; i < this->flowerCount; i++) {
            flowerPos.x = this->flowerPos[i].x;
            flowerPos.y = this->flowerPos[i].y;
            flowerPos.z = this->flowerPos[i].z;

            OPEN_DISPS(play->state.gfxCtx);

            func_8012C28C(play->state.gfxCtx);
            Matrix_Translate(flowerPos.x, flowerPos.y, flowerPos.z, MTXMODE_NEW);
            Matrix_Scale(0.02f, 0.02f, 0.02f, MTXMODE_APPLY);
            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_OPA_DISP++, gDekuScrubFlowerDL);

            CLOSE_DISPS(play->state.gfxCtx);
        }
    }
}
