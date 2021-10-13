/*
 * File: z_en_elforg.c
 * Overlay: ovl_En_Elforg
 * Description: Stray Fairy
 */

#include "z_en_elforg.h"

#define FLAGS 0x00000010

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
void EnElforg_TrappedByCollider(EnElforg* this, GlobalContext* globalCtx);

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

void EnElforg_InitializeSpeedAndRotation(EnElforg* this) {
    this->actor.speedXZ = 1.0f;
    this->targetSpeedXZ = 1.0f;
    this->actor.velocity.y = 0.0f;
    this->actor.world.rot.y = randPlusMinusPoint5Scaled(65536.0f);
    this->timer = 0;
    this->fairyFountainTimer = Rand_ZeroFloat(100.0f);
    this->actor.shape.yOffset = 0.0f;
    this->skelAnime.animCurrentFrame = (s32)Rand_ZeroFloat(5.0f);
}

void EnElforg_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnElforg* this = THIS;

    Actor_SetScale(&this->actor, 0.01f);
    this->unk_214 = 0;
    this->direction = 0;
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_0402CA98, &D_0402B494, this->jointTable, this->jointTable, 10);
    this->skelAnime.animPlaybackSpeed = 1.0f;
    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 0.0f);
    this->actor.shape.shadowAlpha = 0xFF;

    switch (STRAY_FAIRY_TYPE(&this->actor)) {
        case STRAY_FAIRY_TYPE_CLOCK_TOWN:
            if ((gSaveContext.weekEventReg[8] & 0x80) != 0) {
                Actor_MarkForDeath(&this->actor);
                return;
            }
            break;
        case STRAY_FAIRY_TYPE_COLLECTIBLE:
            if (Actor_GetCollectibleFlag(globalCtx, STRAY_FAIRY_FLAG(&this->actor))) {
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
            EnElforg_InitializeSpeedAndRotation(this);
            this->actionFunc = EnElforg_FreeFloatingFairyFountain;
            this->targetSpeedXZ = Rand_ZeroFloat(2.0f) + 1.0f;
            this->unk_228 = Rand_ZeroFloat(100.0f) + 50.0f;
            break;
        case STRAY_FAIRY_TYPE_TURN_IN_TO_FAIRY_FOUNTAIN:
            EnElforg_InitializeSpeedAndRotation(this);
            this->actionFunc = EnElforg_TurnInFairy;
            this->fairyFountainTimer = 60;
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
        case STRAY_FAIRY_TYPE_UNKNOWN_5:
            this->actionFunc = EnElforg_TrappedByCollider;
            this->actor.draw = NULL;
            Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
            Collider_UpdateCylinder(&this->actor, &this->collider);
            break;
        default:
            EnElforg_InitializeSpeedAndRotation(this);
            this->actionFunc = EnElforg_FreeFloating;
            break;
    }

    this->actor.shape.rot.y = 0;
}

void EnElforg_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnElforg* this = THIS;

    if (STRAY_FAIRY_TYPE(&this->actor) == STRAY_FAIRY_TYPE_UNKNOWN_5) {
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

void EnElforg_AdjustYPositionRelativeToTarget(EnElforg* this, Vec3f* targetPos) {
    f32 yDifference;

    yDifference = targetPos->y - this->actor.world.pos.y;
    if (fabsf(yDifference) < this->actor.speedXZ) {
        this->actor.world.pos.y = targetPos->y;
    } else if (yDifference > 0.0f) {
        this->actor.world.pos.y = this->actor.world.pos.y + this->actor.speedXZ;
    } else {
        this->actor.world.pos.y = this->actor.world.pos.y - this->actor.speedXZ;
    }
}

void EnElforg_SetSpeedXZ(EnElforg* this) {
    if (this->actor.speedXZ > this->targetSpeedXZ) {
        this->actor.speedXZ *= 0.9f;
    } else if (this->actor.speedXZ < (this->targetSpeedXZ - 0.1f)) {
        this->actor.speedXZ += 0.1f;
    } else {
        this->actor.speedXZ = this->targetSpeedXZ;
    }
}

void EnElforg_MoveToTargetFairyFountain(EnElforg* this, Vec3f* pos) {
    s32 pad[2];
    f32 xzDistance;
    f32 zDifference;
    f32 xDifference;
    s16 phi_v0;
    s16 targetAngle;

    this->actor.shape.yOffset += 100.0f * Math_SinS(this->timer << 9);
    EnElforg_AdjustYPositionRelativeToTarget(this, pos);
    xDifference = this->actor.world.pos.x - pos->x;
    zDifference = this->actor.world.pos.z - pos->z;
    targetAngle = Math_FAtan2F(-zDifference, -xDifference);
    xzDistance = sqrtf(SQ(xDifference) + SQ(zDifference));
    if ((this->unk_228 + 10.0f) < xzDistance) {
        phi_v0 = 0x1000;
    } else if ((this->unk_228 - 10.0f) > xzDistance) {
        phi_v0 = 0x6000;
    } else {
        phi_v0 = 0x4000;
    }
    targetAngle += phi_v0;
    Math_SmoothStepToS(&this->actor.world.rot.y, targetAngle, 2, 4000, 1000);
    EnElforg_SetSpeedXZ(this);
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
}

void EnElforg_MoveToTarget(EnElforg* this, Vec3f* targetPos) {
    s16 targetAngle;

    this->actor.shape.yOffset += 100.0f * Math_SinS(this->timer << 9);
    EnElforg_AdjustYPositionRelativeToTarget(this, targetPos);
    targetAngle = Math_FAtan2F(-(this->actor.world.pos.z - targetPos->z), -(this->actor.world.pos.x - targetPos->x));
    if (this->targetSpeedXZ > 2.0f) {
        Math_SmoothStepToS(&this->actor.world.rot.y, targetAngle, 2, 0x400, 0x100);
    } else {
        targetAngle += 0x2000;
        Math_SmoothStepToS(&this->actor.world.rot.y, targetAngle, 10, 0x200, 0x80);
    }
    EnElforg_SetSpeedXZ(this);
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
}

void func_80ACCBB8(EnElforg* this, GlobalContext* globalCtx) {
    globalCtx->actorCtx.unk5 |= 8;
}

void EnElforg_TrappedByBubble(EnElforg* this, GlobalContext* globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    if ((this->actor.parent == NULL) || (this->actor.parent->update == NULL)) {
        EnElforg_InitializeSpeedAndRotation(this);
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
    s16 sp34;
    s32 pad;

    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    this->actor.shape.yOffset *= 0.9f;
    this->actor.speedXZ = 5.0f;
    EnElforg_AdjustYPositionRelativeToTarget(this, &player->bodyPartsPos[0]);
    xzDistToPlayer = this->actor.xzDistToPlayer;
    if (xzDistToPlayer < 0.0f) {
        xzDistToPlayer = 10.0f;
    }
    sp34 = 163840.0f / xzDistToPlayer;
    Math_SmoothStepToF(&xzDistToPlayer, 40.0f, 0.2f, 100.0f, 1.0f);
    rotationTemp = this->actor.yawTowardsPlayer - sp34;
    this->actor.world.pos.x = player->actor.world.pos.x - (Math_SinS(rotationTemp) * xzDistToPlayer);
    this->actor.world.pos.z = player->actor.world.pos.z - (Math_CosS(rotationTemp) * xzDistToPlayer);
    EnElforg_SpawnSparkles(this, globalCtx, 16);

    if (this->fairyFountainTimer > 0) {
        this->fairyFountainTimer--;
    } else {
        this->actor.world.rot.y = rotationTemp + 0x4000;
        this->timer = 0;
        this->fairyFountainTimer = Rand_ZeroFloat(100.0f);
        this->actor.shape.yOffset = 0.0f;
        this->targetSpeedXZ = 3.0f;
        this->unk_228 = 50.0f;
        this->actionFunc = EnElforg_FreeFloatingFairyFountain;
        this->unk_214 &= 0xFFFB;
    }
}

void EnElforg_CirclePlayerFairyFountain(EnElforg* this, GlobalContext* globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    EnElforg_MoveToTargetFairyFountain(this, &this->actor.home.pos);
    if (this->fairyFountainTimer < 31) {
        this->actionFunc = EnElforg_TurnInFairy;
    }
    this->fairyFountainTimer--;
}

void EnElforg_FreeFloatingFairyFountain(EnElforg* this, GlobalContext* globalCtx) {
    s32 pad;

    if (this->unk_214 & 1) {
        if (this->targetSpeedXZ < 8.0f) {
            this->targetSpeedXZ += 0.1f;
        }
        if (this->unk_228 > 0.0f) {
            this->unk_228 -= 2.0f;
        }
    } else if ((this->timer & 0x7F) == 0x7F) {
        if (Math_Vec3f_DistXZ(&this->actor.world.pos, &this->actor.home.pos) > 150.0f) {
            this->targetSpeedXZ = 5.0f;
        } else {
            this->targetSpeedXZ = Rand_ZeroFloat(2.0f) + 1.0f;
        }
        this->unk_228 = Rand_ZeroFloat(100.0f) + 50.0f;
    }
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    EnElforg_MoveToTargetFairyFountain(this, &this->actor.home.pos);
    if (this->unk_214 & 4) {
        this->actionFunc = EnElforg_CirclePlayerFairyFountain;
    }
    if (this->unk_214 & 2) {
        if (this->actor.home.rot.x > 0) {
            EnElforg_SpawnSparkles(this, globalCtx, 10);
            this->actor.home.rot.x += -1;
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
    f32 phi_f2;

    if (gSaveContext.playerForm == PLAYER_FORM_GORON) {
        phi_f2 = 40.0f;
    } else {
        phi_f2 = 20.0f;
    }
    this->actor.world.pos.x = (Math_SinS(this->timer << 0xC) * phi_f2) + playerActor->world.pos.x;
    this->actor.world.pos.z = (Math_CosS(this->timer << 0xC) * phi_f2) + playerActor->world.pos.z;
    this->actor.world.pos.y = player->bodyPartsPos[0].y;
    EnElforg_SpawnSparkles(this, globalCtx, 16);
}

void EnElforg_FairyCollected(EnElforg* this, GlobalContext* globalCtx) {
    EnElforg_CirclePlayer(this, globalCtx);
    if (this->timer >= 81) {
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
    this->fairyFountainTimer = 0;
    this->actor.shape.yOffset = 0.0f;
}

void EnElforg_ClockTownFairyCollected(EnElforg* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    EnElforg_CirclePlayer(this, globalCtx);
    player->actor.freezeTimer = 100;
    player->stateFlags1 |= 0x20000000;
    if (func_800B867C(&this->actor, globalCtx)) {
        player->actor.freezeTimer = 0;
        player->stateFlags1 &= 0xDFFFFFFF;
        Actor_MarkForDeath(&this->actor);
        gSaveContext.weekEventReg[8] |= 0x80;
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
    f32 temp_f0;
    Player* player = GET_PLAYER(globalCtx);

    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    if (Player_GetMask(globalCtx) == PLAYER_MASK_GREAT_FAIRYS_MASK) {
        pos = player->bodyPartsPos[0];
        this->targetSpeedXZ = 5.0f;
        EnElforg_MoveToTarget(this, &pos);
    } else {
        this->targetSpeedXZ = 1.0f;
        EnElforg_MoveToTarget(this, &this->actor.home.pos);
    }
    temp_f0 = this->actor.yDistToPlayer - (this->actor.shape.yOffset * this->actor.scale.y);
    if (func_801233E4(globalCtx) == 0) {
        if ((this->actor.xzDistToPlayer < 30.0f) && (temp_f0 < 12.0f) && (temp_f0 > -68.0f)) {
            EnElforg_SetupFairyCollected(this, globalCtx);
            func_80115908(globalCtx, 0x30);
            switch (STRAY_FAIRY_TYPE(&this->actor)) {
                case STRAY_FAIRY_TYPE_COLLECTIBLE:
                    Actor_SetCollectibleFlag(globalCtx, STRAY_FAIRY_FLAG(&this->actor));
                    break;
                case STRAY_FAIRY_TYPE_CHEST:
                    Actor_SetChestFlag(globalCtx, STRAY_FAIRY_FLAG(&this->actor));
                    break;
                default:
                    Actor_SetSwitchFlag(globalCtx, STRAY_FAIRY_FLAG(&this->actor));
                    break;
            }
            if (STRAY_FAIRY_TYPE(&this->actor) == STRAY_FAIRY_TYPE_CLOCK_TOWN) {
                player->actor.freezeTimer = 100;
                player->stateFlags1 |= 0x20000000;
                func_801518B0(globalCtx, 0x579, NULL);
                this->actionFunc = EnElforg_ClockTownFairyCollected;
                ActorCutscene_SetIntentToPlay(0x7C);
                return;
            }
            if (func_8010A074(globalCtx)) {
                gSaveContext.inventory.strayFairies[gSaveContext.unk_48C8]++;
                func_801518B0(globalCtx, 0x11, NULL);
                if (gSaveContext.inventory.strayFairies[(void)0, gSaveContext.unk_48C8] >= 15) {
                    func_801A3098(0x922);
                }
            }
        }
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 20.0f, 20.0f, 20.0f, 7);
        func_80ACCBB8(this, globalCtx);
        if (Player_GetMask(globalCtx) == PLAYER_MASK_GREAT_FAIRYS_MASK) {
            if ((this->unk_214 & 8) == 0) {
                play_sound(NA_SE_SY_FAIRY_MASK_SUCCESS);
            }
            this->unk_214 |= 8;
        } else {
            this->unk_214 &= 0xFFF7;
        }
    }
}

Actor* EnElforg_GetEnemy(EnElforg* this, GlobalContext* globalCtx) {
    Actor* enemy;

    for (enemy = globalCtx->actorCtx.actorList[ACTORCAT_ENEMY].first; enemy != NULL; enemy = enemy->next) {
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
        EnElforg_InitializeSpeedAndRotation(this);
        this->actionFunc = EnElforg_FreeFloating;
        this->actor.draw = EnElforg_Draw;
        Audio_PlayActorSound2(&this->actor, NA_SE_EV_CHIBI_FAIRY_SAVED);
    } else {
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
    Actor* enemy = EnElforg_GetEnemy(this, globalCtx);

    if (enemy != NULL && enemy->update != NULL) {
        this->actionFunc = EnElforg_TrappedByEnemy;
        this->enemy = enemy;
    }
}

void EnElforg_TrappedByCollider(EnElforg* this, GlobalContext* globalCtx) {
    if (this->collider.base.acFlags & AC_HIT) {
        EnElforg_InitializeSpeedAndRotation(this);
        this->actionFunc = EnElforg_FreeFloating;
        this->actor.draw = EnElforg_Draw;
        this->actor.world.pos.y += 40.0f;
        this->actor.home.pos.y += 40.0f;
        Audio_PlayActorSound2(&this->actor, NA_SE_EV_CHIBI_FAIRY_SAVED);
    } else {
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }
    func_80ACCBB8(this, globalCtx);
}

void EnElforg_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnElforg* this = THIS;

    this->actionFunc(this, globalCtx);

    if (this->timer == 0 && this->fairyFountainTimer > 0) {
        this->fairyFountainTimer--;
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
        if (limbIndex == 9) {
            *dList = NULL;
        }
    } else if (limbIndex == 1) {
        *dList = NULL;
    }
    return 0;
}

void EnElforg_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnElforg* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C2DC(globalCtx->state.gfxCtx);
    switch (this->area) {
        case STRAY_FAIRY_AREA_WOODFALL:
            AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(&D_0402C908));
            break;
        case STRAY_FAIRY_AREA_SNOWHEAD:
            AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(&D_0402C890));
            break;
        case STRAY_FAIRY_AREA_GREAT_BAY:
            AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(&D_0402C980));
            break;
        case STRAY_FAIRY_AREA_STONE_TOWER:
            AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(&D_0402C9F8));
            break;
        default:
            AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(&D_0402C818));
            break;
    }
    SysMatrix_InsertMatrix(&globalCtx->mf_187FC, 1);

    POLY_XLU_DISP =
        SkelAnime_DrawSV2(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount,
                          EnElforg_OverrideLimbDraw, NULL, &this->actor, POLY_XLU_DISP);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
