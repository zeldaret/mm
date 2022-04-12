/*
 * File: z_en_elforg.c
 * Overlay: ovl_En_Elforg
 * Description: Stray Fairy
 */

#include "z_en_elforg.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((EnElforg*)thisx)

void EnElforg_Init(Actor* thisx, GlobalContext* globalCtx);
void EnElforg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnElforg_Update(Actor* thisx, GlobalContext* globalCtx);
void EnElforg_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnElforg_TrappedByBubble(EnElforg* this, GlobalContext* globalCtx);
void EnElforg_TurnInFairy(EnElforg* this, GlobalContext* globalCtx);
void EnElforg_FreeFloatingFairyFountain(EnElforg* this, GlobalContext* globalCtx);
void EnElforg_FreeFloating(EnElforg* this, GlobalContext* globalCtx);
void EnElforg_SetupTrappedByEnemy(EnElforg* this, GlobalContext* globalCtx);
void EnElforg_HiddenByCollider(EnElforg* this, GlobalContext* globalCtx);

const ActorInit En_Elforg_InitVars = {
    ACTOR_EN_ELFORG,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnElforg),
    (ActorFunc)EnElforg_Init,
    (ActorFunc)EnElforg_Destroy,
    (ActorFunc)EnElforg_Update,
    (ActorFunc)EnElforg_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_PLAYER,
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
    { 16, 32, 0, { 0, 0, 0 } },
};

void EnElforg_InitializeParams(EnElforg* this) {
    this->actor.speedXZ = 1.0f;
    this->targetSpeedXZ = 1.0f;
    this->actor.velocity.y = 0.0f;
    this->actor.world.rot.y = randPlusMinusPoint5Scaled(0x10000);
    this->timer = 0;
    this->secondaryTimer = Rand_ZeroFloat(100.0f);
    this->actor.shape.yOffset = 0.0f;
    this->skelAnime.curFrame = (s32)Rand_ZeroFloat(5.0f);
}

void EnElforg_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnElforg* this = THIS;

    Actor_SetScale(&this->actor, 0.01f);
    this->flags = 0;
    this->direction = 0;
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &gStrayFairySkel, &gStrayFairyFlyingAnim, this->jointTable,
                       this->jointTable, STRAY_FAIRY_LIMB_MAX);
    this->skelAnime.playSpeed = 1.0f;
    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 0.0f);
    this->actor.shape.shadowAlpha = 255;

    switch (STRAY_FAIRY_TYPE(&this->actor)) {
        case STRAY_FAIRY_TYPE_CLOCK_TOWN:
            if (gSaveContext.save.weekEventReg[8] & 0x80) {
                Actor_MarkForDeath(&this->actor);
                return;
            }
            break;
        case STRAY_FAIRY_TYPE_COLLECTIBLE:
            if (Flags_GetCollectible(globalCtx, STRAY_FAIRY_FLAG(&this->actor))) {
                Actor_MarkForDeath(&this->actor);
                return;
            }
            break;
        default:
            if (Flags_GetSwitch(globalCtx, STRAY_FAIRY_FLAG(&this->actor))) {
                Actor_MarkForDeath(&this->actor);
                return;
            }
            break;
        case STRAY_FAIRY_TYPE_FAIRY_FOUNTAIN:
        case STRAY_FAIRY_TYPE_BUBBLE:
        case STRAY_FAIRY_TYPE_CHEST:
        case STRAY_FAIRY_TYPE_TURN_IN_TO_FAIRY_FOUNTAIN:
            break;
    }

    if (func_8010A074(globalCtx)) {
        this->area = gSaveContext.unk_48C8 + 1;
    } else {
        // Needs to be thisx in order to match
        this->area = STRAY_FAIRY_GET_PARAM_1C0(thisx) >> 6;
    }

    switch (STRAY_FAIRY_TYPE(&this->actor)) {
        case STRAY_FAIRY_TYPE_FAIRY_FOUNTAIN:
            EnElforg_InitializeParams(this);
            this->actionFunc = EnElforg_FreeFloatingFairyFountain;
            this->targetSpeedXZ = Rand_ZeroFloat(2.0f) + 1.0f;
            this->targetDistanceFromHome = Rand_ZeroFloat(100.0f) + 50.0f;
            break;
        case STRAY_FAIRY_TYPE_TURN_IN_TO_FAIRY_FOUNTAIN:
            EnElforg_InitializeParams(this);
            this->actionFunc = EnElforg_TurnInFairy;
            this->secondaryTimer = 60;
            break;
        case STRAY_FAIRY_TYPE_BUBBLE:
            this->timer = 0;
            this->actionFunc = EnElforg_TrappedByBubble;
            break;
        case STRAY_FAIRY_TYPE_ENEMY:
            this->actionFunc = EnElforg_SetupTrappedByEnemy;
            EnElforg_SetupTrappedByEnemy(this, globalCtx);
            this->actor.draw = NULL;
            break;
        case STRAY_FAIRY_TYPE_COLLIDER:
            this->actionFunc = EnElforg_HiddenByCollider;
            this->actor.draw = NULL;
            Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
            Collider_UpdateCylinder(&this->actor, &this->collider);
            break;
        default:
            EnElforg_InitializeParams(this);
            this->actionFunc = EnElforg_FreeFloating;
            break;
    }

    this->actor.shape.rot.y = 0;
}

void EnElforg_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnElforg* this = THIS;

    if (STRAY_FAIRY_TYPE(&this->actor) == STRAY_FAIRY_TYPE_COLLIDER) {
        Collider_DestroyCylinder(globalCtx, &this->collider);
    }
}

void EnElforg_SpawnSparkles(EnElforg* this, GlobalContext* globalCtx, s32 life) {
    static Vec3f sVelocity = { 0.0f, -0.05f, 0.0f };
    static Vec3f sAcceleration = { 0.0f, -0.025f, 0.0f };
    static Color_RGBA8 sPrimColors[] = {
        { 255, 235, 220, 255 }, { 255, 220, 220, 255 }, { 220, 255, 220, 255 },
        { 220, 220, 255, 255 }, { 255, 255, 200, 255 },
    };
    static Color_RGBA8 sEnvColors[] = {
        { 255, 150, 0, 255 }, { 255, 0, 0, 255 }, { 0, 255, 0, 255 }, { 0, 0, 255, 255 }, { 255, 255, 0, 255 },
    };
    Vec3f pos;
    s32 pad;
    s32 index;

    pos.x = randPlusMinusPoint5Scaled(6.0f) + this->actor.world.pos.x;
    pos.y = (Rand_ZeroOne() * 6.0f) + this->actor.world.pos.y + (this->actor.shape.yOffset * this->actor.scale.y);
    pos.z = randPlusMinusPoint5Scaled(6.0f) + this->actor.world.pos.z;
    index = (this->area < STRAY_FAIRY_AREA_CLOCK_TOWN || this->area >= STRAY_FAIRY_AREA_MAX)
                ? STRAY_FAIRY_AREA_CLOCK_TOWN
                : this->area;
    EffectSsKiraKira_SpawnDispersed(globalCtx, &pos, &sVelocity, &sAcceleration, &sPrimColors[index],
                                    &sEnvColors[index], 1000, life);
}

void EnElforg_ApproachTargetYPosition(EnElforg* this, Vec3f* targetPos) {
    f32 yDifference = targetPos->y - this->actor.world.pos.y;

    if (fabsf(yDifference) < this->actor.speedXZ) {
        this->actor.world.pos.y = targetPos->y;
    } else if (yDifference > 0.0f) {
        this->actor.world.pos.y += this->actor.speedXZ;
    } else {
        this->actor.world.pos.y -= this->actor.speedXZ;
    }
}

void EnElforg_ApproachTargetSpeedXZ(EnElforg* this) {
    if (this->actor.speedXZ > this->targetSpeedXZ) {
        this->actor.speedXZ *= 0.9f;
    } else if (this->actor.speedXZ < (this->targetSpeedXZ - 0.1f)) {
        this->actor.speedXZ += 0.1f;
    } else {
        this->actor.speedXZ = this->targetSpeedXZ;
    }
}

void EnElforg_MoveToTargetFairyFountain(EnElforg* this, Vec3f* homePos) {
    s32 pad[2];
    f32 xzDistance;
    f32 zDifference;
    f32 xDifference;
    s16 angleAdjustment;
    s16 targetAngle;

    this->actor.shape.yOffset += 100.0f * Math_SinS(this->timer << 9);
    EnElforg_ApproachTargetYPosition(this, homePos);
    xDifference = this->actor.world.pos.x - homePos->x;
    zDifference = this->actor.world.pos.z - homePos->z;
    targetAngle = Math_FAtan2F(-zDifference, -xDifference);
    xzDistance = sqrtf(SQ(xDifference) + SQ(zDifference));
    if ((this->targetDistanceFromHome + 10.0f) < xzDistance) {
        angleAdjustment = 0x1000;
    } else if ((this->targetDistanceFromHome - 10.0f) > xzDistance) {
        angleAdjustment = 0x6000;
    } else {
        angleAdjustment = 0x4000;
    }
    targetAngle += angleAdjustment;
    Math_SmoothStepToS(&this->actor.world.rot.y, targetAngle, 2, 4000, 1000);
    EnElforg_ApproachTargetSpeedXZ(this);
    Actor_MoveWithGravity(&this->actor);
}

/**
 * Adjust's the Stray Fairy's speed, rotation, and y-position to bring it
 * closer to targetPos. Since it doesn't directly point the fairy towards
 * its target, it can take strange paths or even "orbit" the target.
 */
void EnElforg_MoveToTarget(EnElforg* this, Vec3f* targetPos) {
    s16 targetAngle;

    this->actor.shape.yOffset += 100.0f * Math_SinS(this->timer << 9);
    EnElforg_ApproachTargetYPosition(this, targetPos);
    targetAngle = Math_FAtan2F(-(this->actor.world.pos.z - targetPos->z), -(this->actor.world.pos.x - targetPos->x));
    if (this->targetSpeedXZ > 2.0f) {
        Math_SmoothStepToS(&this->actor.world.rot.y, targetAngle, 2, 0x400, 0x100);
    } else {
        // If the speed is below a threshold, deliberately mess up the target
        // angle so the fairy "orbits" the target instead of reaching it.
        targetAngle += 0x2000;
        Math_SmoothStepToS(&this->actor.world.rot.y, targetAngle, 10, 0x200, 0x80);
    }
    EnElforg_ApproachTargetSpeedXZ(this);
    Actor_MoveWithGravity(&this->actor);
}

void func_80ACCBB8(EnElforg* this, GlobalContext* globalCtx) {
    globalCtx->actorCtx.unk5 |= 8;
}

void EnElforg_TrappedByBubble(EnElforg* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    if ((this->actor.parent == NULL) || (this->actor.parent->update == NULL)) {
        EnElforg_InitializeParams(this);
        this->actionFunc = EnElforg_FreeFloating;
    } else {
        this->actor.shape.yOffset += 10.0f * Math_SinS(this->timer << 9);
        this->actor.world.pos = this->actor.parent->world.pos;
        this->actor.world.pos.y += 12.0f;
    }
    func_80ACCBB8(this, globalCtx);
}

void EnElforg_TurnInFairy(EnElforg* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    f32 xzDistToPlayer;
    s16 rotationTemp;
    s16 newAngle;
    s32 pad;

    // This code makes the fairy briefly circle the player before
    // flying towards the fountain's center.
    SkelAnime_Update(&this->skelAnime);
    this->actor.shape.yOffset *= 0.9f;
    this->actor.speedXZ = 5.0f;
    EnElforg_ApproachTargetYPosition(this, &player->bodyPartsPos[0]);
    xzDistToPlayer = this->actor.xzDistToPlayer;
    if (xzDistToPlayer < 0.0f) {
        xzDistToPlayer = 10.0f;
    }
    newAngle = 0x28000 / xzDistToPlayer;
    Math_SmoothStepToF(&xzDistToPlayer, 40.0f, 0.2f, 100.0f, 1.0f);
    rotationTemp = this->actor.yawTowardsPlayer - newAngle;
    this->actor.world.pos.x = player->actor.world.pos.x - (Math_SinS(rotationTemp) * xzDistToPlayer);
    this->actor.world.pos.z = player->actor.world.pos.z - (Math_CosS(rotationTemp) * xzDistToPlayer);
    EnElforg_SpawnSparkles(this, globalCtx, 16);

    if (this->secondaryTimer > 0) {
        this->secondaryTimer--;
    } else {
        this->actor.world.rot.y = rotationTemp + 0x4000;
        this->timer = 0;
        this->secondaryTimer = Rand_ZeroFloat(100.0f);
        this->actor.shape.yOffset = 0.0f;
        this->targetSpeedXZ = 3.0f;
        this->targetDistanceFromHome = 50.0f;
        this->actionFunc = EnElforg_FreeFloatingFairyFountain;
        this->flags &= ~STRAY_FAIRY_FLAG_CIRCLES_QUICKLY_IN_FOUNTAIN;
    }
}

void EnElforg_QuicklyCircleFairyFountain(EnElforg* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    EnElforg_MoveToTargetFairyFountain(this, &this->actor.home.pos);
    if (this->secondaryTimer <= 30) {
        this->actionFunc = EnElforg_TurnInFairy;
    }
    this->secondaryTimer--;
}

void EnElforg_FreeFloatingFairyFountain(EnElforg* this, GlobalContext* globalCtx) {
    s32 pad;

    if (this->flags & STRAY_FAIRY_FLAG_MOVES_QUICKLY_TO_HOME) {
        // This happens when "turning in" the last batch of Stray Fairies to
        // a Fairy Fountain. The ones being "turned in" will fly very
        // quickly to the center of the fountain.
        if (this->targetSpeedXZ < 8.0f) {
            this->targetSpeedXZ += 0.1f;
        }
        if (this->targetDistanceFromHome > 0.0f) {
            this->targetDistanceFromHome -= 2.0f;
        }
    } else if ((this->timer & 127) == 127) {
        if (Math_Vec3f_DistXZ(&this->actor.world.pos, &this->actor.home.pos) > 150.0f) {
            this->targetSpeedXZ = 5.0f;
        } else {
            this->targetSpeedXZ = Rand_ZeroFloat(2.0f) + 1.0f;
        }
        this->targetDistanceFromHome = Rand_ZeroFloat(100.0f) + 50.0f;
    }
    SkelAnime_Update(&this->skelAnime);
    EnElforg_MoveToTargetFairyFountain(this, &this->actor.home.pos);
    if (this->flags & STRAY_FAIRY_FLAG_CIRCLES_QUICKLY_IN_FOUNTAIN) {
        // A small number of fairies will do this when the player walks into
        // the center of the fountain to be healed.
        this->actionFunc = EnElforg_QuicklyCircleFairyFountain;
    }
    if (this->flags & STRAY_FAIRY_FLAG_SPARKLES_AND_SHRINKS) {
        // This happens right before the Great Fairy appears once all
        // Stray Fairies are saved.
        if (this->actor.home.rot.x > 0) {
            EnElforg_SpawnSparkles(this, globalCtx, 10);
            this->actor.home.rot.x--;
        }
        Actor_SetScale(&this->actor, this->actor.scale.x * 0.9f);
        if (this->actor.scale.x < 0.001f) {
            Actor_MarkForDeath(&this->actor);
        }
    }
}

void EnElforg_CirclePlayer(EnElforg* this, GlobalContext* globalCtx) {
    s32 pad;
    Actor* playerActor = &GET_PLAYER(globalCtx)->actor;
    Player* player = GET_PLAYER(globalCtx);
    f32 distanceFromPlayer;

    if (gSaveContext.save.playerForm == PLAYER_FORM_GORON) {
        distanceFromPlayer = 40.0f;
    } else {
        distanceFromPlayer = 20.0f;
    }
    this->actor.world.pos.x = (Math_SinS(this->timer << 12) * distanceFromPlayer) + playerActor->world.pos.x;
    this->actor.world.pos.z = (Math_CosS(this->timer << 12) * distanceFromPlayer) + playerActor->world.pos.z;
    this->actor.world.pos.y = player->bodyPartsPos[0].y;
    EnElforg_SpawnSparkles(this, globalCtx, 16);
}

void EnElforg_FairyCollected(EnElforg* this, GlobalContext* globalCtx) {
    EnElforg_CirclePlayer(this, globalCtx);
    if (this->timer > 80) {
        Actor_MarkForDeath(&this->actor);
        return;
    }
    func_800B9010(&this->actor, NA_SE_PL_CHIBI_FAIRY_HEAL - SFX_FLAG);
}

void EnElforg_SetupFairyCollected(EnElforg* this, GlobalContext* globalCtx) {
    Actor* playerActor = &GET_PLAYER(globalCtx)->actor;
    Player* player = GET_PLAYER(globalCtx);

    this->actor.world.pos.x = playerActor->world.pos.x;
    this->actor.world.pos.y = player->bodyPartsPos[0].y;
    this->actor.world.pos.z = playerActor->world.pos.z;
    this->actionFunc = EnElforg_FairyCollected;
    this->timer = 0;
    this->secondaryTimer = 0;
    this->actor.shape.yOffset = 0.0f;
}

void EnElforg_ClockTownFairyCollected(EnElforg* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    EnElforg_CirclePlayer(this, globalCtx);
    player->actor.freezeTimer = 100;
    player->stateFlags1 |= 0x20000000;
    if (Actor_TextboxIsClosing(&this->actor, globalCtx)) {
        player->actor.freezeTimer = 0;
        player->stateFlags1 &= ~0x20000000;
        Actor_MarkForDeath(&this->actor);
        gSaveContext.save.weekEventReg[8] |= 0x80;
        ActorCutscene_Stop(0x7C);
    } else {
        func_800B9010(&this->actor, NA_SE_PL_CHIBI_FAIRY_HEAL - SFX_FLAG);
        if (ActorCutscene_GetCurrentIndex() != 0x7C) {
            if (ActorCutscene_GetCanPlayNext(0x7C)) {
                ActorCutscene_Start(0x7C, &this->actor);
            } else {
                ActorCutscene_SetIntentToPlay(0x7C);
            }
        }
    }
}

void EnElforg_FreeFloating(EnElforg* this, GlobalContext* globalCtx) {
    Vec3f pos;
    f32 scaledYDistance;
    Player* player = GET_PLAYER(globalCtx);

    SkelAnime_Update(&this->skelAnime);
    if (Player_GetMask(globalCtx) == PLAYER_MASK_GREAT_FAIRY) {
        pos = player->bodyPartsPos[0];
        this->targetSpeedXZ = 5.0f;
        EnElforg_MoveToTarget(this, &pos);
    } else {
        this->targetSpeedXZ = 1.0f;
        EnElforg_MoveToTarget(this, &this->actor.home.pos);
    }

    scaledYDistance = this->actor.playerHeightRel - (this->actor.shape.yOffset * this->actor.scale.y);
    if (!Player_InCsMode(&globalCtx->state)) {
        if ((this->actor.xzDistToPlayer < 30.0f) && (scaledYDistance < 12.0f) && (scaledYDistance > -68.0f)) {
            EnElforg_SetupFairyCollected(this, globalCtx);
            func_80115908(globalCtx, 48);
            switch (STRAY_FAIRY_TYPE(&this->actor)) {
                case STRAY_FAIRY_TYPE_COLLECTIBLE:
                    Flags_SetCollectible(globalCtx, STRAY_FAIRY_FLAG(&this->actor));
                    break;
                case STRAY_FAIRY_TYPE_CHEST:
                    Flags_SetTreasure(globalCtx, STRAY_FAIRY_FLAG(&this->actor));
                    break;
                default:
                    Flags_SetSwitch(globalCtx, STRAY_FAIRY_FLAG(&this->actor));
                    break;
            }

            if (STRAY_FAIRY_TYPE(&this->actor) == STRAY_FAIRY_TYPE_CLOCK_TOWN) {
                player->actor.freezeTimer = 100;
                player->stateFlags1 |= 0x20000000;
                Message_StartTextbox(globalCtx, 0x579, NULL);
                this->actionFunc = EnElforg_ClockTownFairyCollected;
                ActorCutscene_SetIntentToPlay(0x7C);
                return;
            }

            if (func_8010A074(globalCtx)) {
                gSaveContext.save.inventory.strayFairies[gSaveContext.unk_48C8]++;
                Message_StartTextbox(globalCtx, 0x11, NULL);
                if (gSaveContext.save.inventory.strayFairies[(void)0, gSaveContext.unk_48C8] >= 15) {
                    func_801A3098(NA_BGM_GET_ITEM | 0x900);
                }
            }
        }

        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 20.0f, 20.0f, 20.0f, 7);
        func_80ACCBB8(this, globalCtx);
        if (Player_GetMask(globalCtx) == PLAYER_MASK_GREAT_FAIRY) {
            if (!(this->flags & STRAY_FAIRY_FLAG_GREAT_FAIRYS_MASK_EQUIPPED)) {
                play_sound(NA_SE_SY_FAIRY_MASK_SUCCESS);
            }
            this->flags |= STRAY_FAIRY_FLAG_GREAT_FAIRYS_MASK_EQUIPPED;
        } else {
            this->flags &= ~STRAY_FAIRY_FLAG_GREAT_FAIRYS_MASK_EQUIPPED;
        }
    }
}

/**
 * This finds the enemy that is "holding" the Stray Fairy hostage. When
 * this enemy is killed, the Stray Fairy will spawn. This function only
 * works if the enemy and the Stray Fairy have the exact same home
 * coordinates when the Stray Fairy first spawns.
 */
Actor* EnElforg_GetHoldingEnemy(EnElforg* this, GlobalContext* globalCtx) {
    Actor* enemy;

    for (enemy = globalCtx->actorCtx.actorLists[ACTORCAT_ENEMY].first; enemy != NULL; enemy = enemy->next) {
        if ((enemy->home.pos.x == this->actor.home.pos.x) && (enemy->home.pos.y == this->actor.home.pos.y) &&
            (enemy->home.pos.z == this->actor.home.pos.z)) {
            return enemy;
        }
    }
    return NULL;
}

void EnElforg_TrappedByEnemy(EnElforg* this, GlobalContext* globalCtx) {
    f32 posTemp;

    if (this->enemy->update == NULL) {
        EnElforg_InitializeParams(this);
        this->actionFunc = EnElforg_FreeFloating;
        this->actor.draw = EnElforg_Draw;
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_CHIBI_FAIRY_SAVED);
    } else {
        // The enemy is still alive, so have the Stray Fairy
        // track the enemy in case it's moving around.
        posTemp = this->enemy->world.pos.x;
        this->actor.world.pos.x = posTemp;
        this->actor.home.pos.x = posTemp;
        posTemp = this->enemy->world.pos.y + 30.0f;
        this->actor.world.pos.y = posTemp;
        this->actor.home.pos.y = posTemp;
        posTemp = this->enemy->world.pos.z;
        this->actor.world.pos.z = posTemp;
        this->actor.home.pos.z = posTemp;
    }
    func_80ACCBB8(this, globalCtx);
}

void EnElforg_SetupTrappedByEnemy(EnElforg* this, GlobalContext* globalCtx) {
    Actor* enemy = EnElforg_GetHoldingEnemy(this, globalCtx);

    if (enemy != NULL && enemy->update != NULL) {
        this->actionFunc = EnElforg_TrappedByEnemy;
        this->enemy = enemy;
    }
}

void EnElforg_HiddenByCollider(EnElforg* this, GlobalContext* globalCtx) {
    if (this->collider.base.acFlags & AC_HIT) {
        EnElforg_InitializeParams(this);
        this->actionFunc = EnElforg_FreeFloating;
        this->actor.draw = EnElforg_Draw;
        this->actor.world.pos.y += 40.0f;
        this->actor.home.pos.y += 40.0f;
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_CHIBI_FAIRY_SAVED);
    } else {
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }
    func_80ACCBB8(this, globalCtx);
}

void EnElforg_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnElforg* this = THIS;

    this->actionFunc(this, globalCtx);

    if (this->timer == 0 && this->secondaryTimer > 0) {
        this->secondaryTimer--;
    } else {
        this->timer++;
    }

    if (this->direction < 0) {
        this->direction++;
        if (this->direction == 0) {
            this->direction = Rand_ZeroFloat(20.0f) + 20.0f;
        }
    } else if (this->direction > 0) {
        this->direction--;
    } else {
        this->direction = -Rand_ZeroFloat(20.0f) - 20.0f;
    }
}

s32 EnElforg_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                              Actor* thisx, Gfx** gfx) {
    EnElforg* this = THIS;

    if (this->direction < 0) {
        if (limbIndex == STRAY_FAIRY_LIMB_LEFT_FACING_HEAD) {
            *dList = NULL;
        }
    } else if (limbIndex == STRAY_FAIRY_LIMB_RIGHT_FACING_HEAD) {
        *dList = NULL;
    }

    return false;
}

void EnElforg_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnElforg* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C2DC(globalCtx->state.gfxCtx);
    switch (this->area) {
        case STRAY_FAIRY_AREA_WOODFALL:
            AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(gStrayFairyWoodfallTexAnim));
            break;
        case STRAY_FAIRY_AREA_SNOWHEAD:
            AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(gStrayFairySnowheadTexAnim));
            break;
        case STRAY_FAIRY_AREA_GREAT_BAY:
            AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(gStrayFairyGreatBayTexAnim));
            break;
        case STRAY_FAIRY_AREA_STONE_TOWER:
            AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(gStrayFairyStoneTowerTexAnim));
            break;
        default:
            AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(gStrayFairyClockTownTexAnim));
            break;
    }
    Matrix_InsertMatrix(&globalCtx->billboardMtxF, MTXMODE_APPLY);

    POLY_XLU_DISP =
        SkelAnime_DrawFlex(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                           EnElforg_OverrideLimbDraw, NULL, &this->actor, POLY_XLU_DISP);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
