/*
 * File: z_en_ruppecrow.c
 * Overlay: ovl_En_Ruppecrow
 * Description: Guay Circling Clock Town
 */

#include "z_en_ruppecrow.h"
#include "objects/object_crow/object_crow.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20 | ACTOR_FLAG_4000)

#define THIS ((EnRuppecrow*)thisx)

enum {
    ENRUPPECROW_EFFECT_NONE = 0,
    ENRUPPECROW_EFFECT_ICE = 10,
    ENRUPPECROW_EFFECT_LIGHT = 20,
};

void EnRuppecrow_Init(Actor* thisx, GlobalContext* globalCtx);
void EnRuppecrow_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnRuppecrow_Update(Actor* thisx, GlobalContext* globalCtx);
void EnRuppecrow_Draw(Actor* thisx, GlobalContext* globalCtx);
void EnRuppecrow_HandleSong(EnRuppecrow*, GlobalContext*);
s32 EnRuppecrow_UpdateCollision(EnRuppecrow*, GlobalContext*);
void EnRuppecrow_UpdateRupees(EnRuppecrow*);
void EnRuppecrow_UpdateDamage(EnRuppecrow*, GlobalContext*);
void EnRuppecrow_HandleDeath(EnRuppecrow*);
void EnRuppecrow_FallToDespawn(EnRuppecrow*, GlobalContext*);
void EnRuppecrow_ShatterIce(EnRuppecrow*, GlobalContext*);
void EnRuppecrow_UpdatePosition(EnRuppecrow*, GlobalContext*);
s32 EnRuppecrow_CheckPlayedMatchingSong(GlobalContext*);
void EnRuppecrow_HandleSongCutscene(EnRuppecrow*, GlobalContext*);
s32 EnRuppecrow_ReachedPointClockwise(EnRuppecrow*, Path*, s32);
s32 EnRuppecrow_ReachedPointCounterClockwise(EnRuppecrow*, Path*, s32);
f32 EnRuppecrow_GetPointDirection(Path*, s32, PosRot*, Vec3s*);
s32 EnRuppecrow_CanSpawnBlueRupees(GlobalContext*);
void EnRuppecrow_SpawnRupee(EnRuppecrow*, GlobalContext*);
void EnRuppecrow_FlyWhileDroppingRupees(EnRuppecrow*, GlobalContext*);
void EnRuppecrow_UpdateSpeed(EnRuppecrow*, GlobalContext*);
void EnRuppecrow_FlyToDespawn(EnRuppecrow*, GlobalContext*);

const ActorInit En_Ruppecrow_InitVars = {
    ACTOR_EN_RUPPECROW,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_CROW,
    sizeof(EnRuppecrow),
    (ActorFunc)EnRuppecrow_Init,
    (ActorFunc)EnRuppecrow_Destroy,
    (ActorFunc)EnRuppecrow_Update,
    (ActorFunc)EnRuppecrow_Draw,
};

static ColliderJntSphElementInit sJntSphElementsInit[1] = {
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 1, { { 0, 0, 0 }, 20 }, 100 },
    },
};

static ColliderJntSphInit sJntSphInit = {
    {
        COLTYPE_HIT3,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_JNTSPH,
    },
    1,
    sJntSphElementsInit,
};

static CollisionCheckInfoInit sColChkInfoInit = { 1, 15, 30, 30 };

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0x0),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(1, 0x0),
    /* Fire arrow     */ DMG_ENTRY(2, 0x2),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(1, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(2, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x1),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
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

static InitChainEntry sInitChain[] = {
    ICHAIN_F32_DIV1000(gravity, -500, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 2000, ICHAIN_STOP),
};

s32 EnRuppecrow_UpdateCollision(EnRuppecrow* this, GlobalContext* globalCtx) {
    s32 pad;

    this->collider.elements->dim.worldSphere.center.x = this->actor.world.pos.x;
    this->collider.elements->dim.worldSphere.center.y =
        sJntSphInit.elements->dim.modelSphere.center.y + this->actor.world.pos.y;
    this->collider.elements->dim.worldSphere.center.z = this->actor.world.pos.z;

    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 12.0f, 25.0f, 50.0f, 0x07);

    return true;
}

s32 EnRuppecrow_ReachedPointClockwise(EnRuppecrow* this, Path* path, s32 pointIndex) {
    Vec3s* points = Lib_SegmentedToVirtual(path->points);
    s32 pathCount = path->count;
    s32 currentPoint = pointIndex;
    s32 reached = false;
    f32 diffX;
    f32 diffZ;
    f32 px;
    f32 pz;
    f32 d;
    Vec3f point;

    Math_Vec3s_ToVec3f(&point, &points[currentPoint]);

    if (currentPoint == 0) {
        diffX = points[1].x - points[0].x;
        diffZ = points[1].z - points[0].z;
    } else {
        if (currentPoint == (pathCount - 1)) {
            diffX = points[pathCount - 1].x - points[pathCount - 2].x;
            diffZ = points[pathCount - 1].z - points[pathCount - 2].z;
        } else {
            diffX = points[currentPoint + 1].x - points[currentPoint - 1].x;
            diffZ = points[currentPoint + 1].z - points[currentPoint - 1].z;
        }
    }

    func_8017B7F8(&point, RADF_TO_BINANG(func_80086B30(diffX, diffZ)), &px, &pz, &d);
    if (((this->actor.world.pos.x * px) + (pz * this->actor.world.pos.z) + d) > 0.0f) {
        reached = true;
    }

    return reached;
}

s32 EnRuppecrow_ReachedPointCounterClockwise(EnRuppecrow* this, Path* path, s32 pointIndex) {
    Vec3s* points = Lib_SegmentedToVirtual(path->points);
    s32 pathCount = path->count;
    s32 currentPoint = pointIndex;
    s32 reached = false;
    f32 diffX;
    f32 diffZ;
    f32 px;
    f32 pz;
    f32 d;
    Vec3f point;

    Math_Vec3s_ToVec3f(&point, &points[currentPoint]);

    if (currentPoint == 0) {
        diffX = points[0].x - points[1].x;
        diffZ = points[0].z - points[1].z;
    } else {
        if (currentPoint == (pathCount - 1)) {
            diffX = points[pathCount - 2].x - points[pathCount - 1].x;
            diffZ = points[pathCount - 2].z - points[pathCount - 1].z;
        } else {
            diffX = points[currentPoint - 1].x - points[currentPoint + 1].x;
            diffZ = points[currentPoint - 1].z - points[currentPoint + 1].z;
        }
    }

    func_8017B7F8(&point, RADF_TO_BINANG(func_80086B30(diffX, diffZ)), &px, &pz, &d);
    if (((this->actor.world.pos.x * px) + (pz * this->actor.world.pos.z) + d) > 0.0f) {
        reached = true;
    }

    return reached;
}

f32 EnRuppecrow_GetPointDirection(Path* path, s32 pointIndex, PosRot* world, Vec3s* direction) {
    Vec3s* points;
    Vec3f point;

    if (path != NULL) {
        points = Lib_SegmentedToVirtual(path->points);
        points = &points[pointIndex];
        VEC_SET(point, points->x, points->y, points->z);
    }

    direction->y = Math_Vec3f_Yaw(&world->pos, &point);
    direction->x = Math_Vec3f_Pitch(&world->pos, &point);

    return point.y - world->pos.y;
}

void EnRuppecrow_ShatterIce(EnRuppecrow* this, GlobalContext* globalCtx) {
    if (this->currentEffect == ENRUPPECROW_EFFECT_ICE) {
        this->currentEffect = ENRUPPECROW_EFFECT_NONE;
        this->unk_2C8 = 0.0f;
        Actor_SpawnIceEffects(globalCtx, &this->actor, this->limbPos, ARRAY_COUNT(this->limbPos), 0x2, 0.2f, 0.2f);
    }
}

s32 EnRuppecrow_CanSpawnBlueRupees(GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    switch (player->transformation) {
        case PLAYER_FORM_DEKU:
            return false;
        case PLAYER_FORM_GORON:
            return true;
        case PLAYER_FORM_ZORA:
            return false;
        case PLAYER_FORM_HUMAN:
            if (player->stateFlags1 & 0x800000) {
                return true;
            } else {
                return false;
            }
    }

    return false;
}

void EnRuppecrow_UpdateRupees(EnRuppecrow* this) {
    EnItem00* rupee;
    s16 rupeeIndex;

    for (rupeeIndex = 0; rupeeIndex < ENRUPPECROW_RUPEE_COUNT; rupeeIndex++) {
        rupee = this->rupees[rupeeIndex];
        if (rupee != NULL && rupee->unk152 == 0) {
            Actor_MarkForDeath(&rupee->actor);
        }
    }
}

void EnRuppecrow_SpawnRupee(EnRuppecrow* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    f32 xOffset;
    EnItem00* rupee;
    s16 rupeeIndex = this->rupeeIndex;

    if (!(player->stateFlags3 & 0x1000)) {
        xOffset = (this->rupeeIndex & 1) ? 10.0f : -10.0f;
    } else {
        xOffset = 0.0f;
    }

    if (EnRuppecrow_CanSpawnBlueRupees(globalCtx) && (this->rupeeIndex % 5) == 4) {
        if (this->rupeeIndex == 19) {
            rupee = (EnItem00*)Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_ITEM00,
                                           this->actor.world.pos.x + xOffset, this->actor.world.pos.y,
                                           this->actor.world.pos.z, 0x0, 0x0, 0x0, ITEM00_RUPEE_RED);
            this->rupees[rupeeIndex] = rupee;
            this->rupees[rupeeIndex]->actor.gravity = -5.0f;
            this->rupees[rupeeIndex]->actor.velocity.y = 0.0f;
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_RUPY_FALL);
            rupee = this->rupees[rupeeIndex];
            rupee->unk152 = 60;
            this->rupees[rupeeIndex]->actor.flags |= ACTOR_FLAG_10;
        } else {
            rupee = (EnItem00*)Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_ITEM00,
                                           this->actor.world.pos.x + xOffset, this->actor.world.pos.y,
                                           this->actor.world.pos.z, 0x0, 0x0, 0x0, ITEM00_RUPEE_BLUE);
            this->rupees[rupeeIndex] = rupee;
            this->rupees[rupeeIndex]->actor.gravity = -5.0f;
            this->rupees[rupeeIndex]->actor.velocity.y = 0.0f;
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_RUPY_FALL);
            rupee = this->rupees[rupeeIndex];
            rupee->unk152 = 60;
            this->rupees[rupeeIndex]->actor.flags |= ACTOR_FLAG_10;
        }
    } else if (this->rupeeIndex == 19) {
        rupee =
            (EnItem00*)Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_ITEM00, this->actor.world.pos.x + xOffset,
                                   this->actor.world.pos.y, this->actor.world.pos.z, 0x0, 0x0, 0x0, ITEM00_RUPEE_RED);
        this->rupees[rupeeIndex] = rupee;
        this->rupees[rupeeIndex]->actor.gravity = -5.0f;
        this->rupees[rupeeIndex]->actor.velocity.y = 0.0f;
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_RUPY_FALL);
        rupee = this->rupees[rupeeIndex];
        rupee->unk152 = 60;
        this->rupees[rupeeIndex]->actor.flags |= ACTOR_FLAG_10;
    } else {
        rupee =
            (EnItem00*)Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_ITEM00, this->actor.world.pos.x + xOffset,
                                   this->actor.world.pos.y, this->actor.world.pos.z, 0x0, 0x0, 0x0, ITEM00_RUPEE_GREEN);
        this->rupees[rupeeIndex] = rupee;
        this->rupees[rupeeIndex]->actor.gravity = -5.0f;
        this->rupees[rupeeIndex]->actor.velocity.y = 0.0f;
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_RUPY_FALL);
        rupee = this->rupees[rupeeIndex];
        rupee->unk152 = 60;
        this->rupees[rupeeIndex]->actor.flags |= ACTOR_FLAG_10;
    }

    this->rupeeIndex++;
}

void EnRuppecrow_UpdatePosition(EnRuppecrow* this, GlobalContext* globalCtx) {
    Vec3s nextPointDirection;

    EnRuppecrow_GetPointDirection(this->path, this->currentPoint, &this->actor.world, &nextPointDirection);
    if (this->actor.bgCheckFlags & 0x8) {
        nextPointDirection.y = this->actor.wallYaw;
    }

    Math_SmoothStepToS(&this->actor.world.rot.y, nextPointDirection.y, 0x4, 0x3E8, 0x1);
    this->actor.shape.rot.y = this->actor.world.rot.y;
    Math_SmoothStepToS(&this->actor.world.rot.x, -nextPointDirection.x, 0x4, 0x3E8, 0x1);

    if (this->isGoingCounterClockwise & 1) {
        if (EnRuppecrow_ReachedPointCounterClockwise(this, this->path, this->currentPoint)) {
            if (this->currentPoint <= 0) {
                this->currentPoint = this->path->count - 1;
            } else {
                this->currentPoint--;
            }

            if (this->actionFunc == EnRuppecrow_FlyWhileDroppingRupees &&
                (!EnRuppecrow_CanSpawnBlueRupees(globalCtx) || (this->currentPoint % -2) == 0)) {
                EnRuppecrow_SpawnRupee(this, globalCtx);
            }
        }
    } else if (EnRuppecrow_ReachedPointClockwise(this, this->path, this->currentPoint)) {
        if (this->currentPoint >= this->path->count - 1) {
            this->currentPoint = 0;
        } else {
            this->currentPoint++;
        }

        if (this->actionFunc == EnRuppecrow_FlyWhileDroppingRupees &&
            (!EnRuppecrow_CanSpawnBlueRupees(globalCtx) || (this->currentPoint % -2) == 0)) {
            EnRuppecrow_SpawnRupee(this, globalCtx);
        }
    }
}

s32 EnRuppecrow_CheckPlayedMatchingSong(GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (globalCtx->msgCtx.ocarinaMode == 0x3) {
        switch (player->transformation) {
            case PLAYER_FORM_DEKU:
                if (globalCtx->msgCtx.unk1202E == OCARINA_SONG_SONATA) {
                    return true;
                }
                break;
            case PLAYER_FORM_GORON:
                if (globalCtx->msgCtx.unk1202E == OCARINA_SONG_GORON_LULLABY) {
                    return true;
                }
                break;
            case PLAYER_FORM_ZORA:
                if (globalCtx->msgCtx.unk1202E == OCARINA_SONG_NEW_WAVE) {
                    return true;
                }
                break;
            case PLAYER_FORM_HUMAN:
                if (globalCtx->msgCtx.unk1202E == OCARINA_SONG_SONATA) {
                    return true;
                } else if (globalCtx->msgCtx.unk1202E == OCARINA_SONG_GORON_LULLABY) {
                    return true;
                } else if (globalCtx->msgCtx.unk1202E == OCARINA_SONG_NEW_WAVE) {
                    return true;
                }
                break;
        }
    }

    return false;
}

void EnRuppecrow_UpdateSpeed(EnRuppecrow* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    switch (player->transformation) {
        case PLAYER_FORM_DEKU:
            this->speedModifier = 7.0f;
            break;
        case PLAYER_FORM_GORON:
            if (player->stateFlags3 & 0x1000) { // Goron Link is curled
                this->speedModifier = 19.0f;
            } else {
                this->speedModifier = 7.0f;
            }
            break;
        case PLAYER_FORM_ZORA:
            this->speedModifier = 7.0f;
            break;
        case PLAYER_FORM_HUMAN:
            if (player->stateFlags1 & 0x800000) {
                this->speedModifier = 16.0f;
            } else {
                this->speedModifier = 7.0f;
            }
            break;
    }

    this->skelAnime.playSpeed = this->speedModifier / 6.0f;
    if (this->actor.xzDistToPlayer > 800.0f) {
        this->speedModifier *= 0.5f;
    } else if (this->actor.xzDistToPlayer > 500.0f) {
        this->speedModifier *= 0.8f;
    } else if (this->actor.xzDistToPlayer < 150.0f) {
        this->speedModifier *= 1.2f;
    }
}

void EnRuppecrow_HandleDeath(EnRuppecrow* this) {
    f32 scale;

    this->actor.speedXZ *= Math_CosS(this->actor.world.rot.x);
    this->actor.velocity.y = 0.0f;
    Animation_Change(&this->skelAnime, &gGuayFlyAnim, 0.4f, 0.0f, 0.0f, 0x1, -3.0f);

    this->actor.shape.yOffset = 0.0f;
    this->actor.targetArrowOffset = 0.0f;
    this->actor.bgCheckFlags &= ~0x1;

    scale = this->actor.scale.x * 100.0f;
    this->actor.world.pos.y += 20.0f * scale;

    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_KAICHO_DEAD);

    this->unk_2CC = 0.5f;
    if (this->actor.colChkInfo.damageEffect == 0x3) {
        this->currentEffect = ENRUPPECROW_EFFECT_ICE;
        this->unk_2C8 = 1.0f;
        this->iceSfxTimer = 0.75f;
    } else if (this->actor.colChkInfo.damageEffect == 0x4) {
        this->currentEffect = ENRUPPECROW_EFFECT_LIGHT;
        this->unk_2C8 = 5.0f;
    } else if (this->actor.colChkInfo.damageEffect == 0x2) {
        this->currentEffect = ENRUPPECROW_EFFECT_NONE;
        this->unk_2C8 = 5.0f;
    }

    Actor_SetColorFilter(&this->actor, 0x4000, 0xFF, 0x0, 0x28);
    if (this->actor.flags & ACTOR_FLAG_8000) {
        this->actor.speedXZ = 0.0f;
    }

    this->collider.base.acFlags &= ~AC_ON;
    this->actor.flags |= ACTOR_FLAG_10;
    this->actionFunc = EnRuppecrow_FallToDespawn;
}

void EnRuppecrow_UpdateDamage(EnRuppecrow* this, GlobalContext* globalCtx) {
    if (this->collider.base.acFlags & AC_HIT) {
        this->collider.base.acFlags &= ~AC_HIT;
        Actor_SetDropFlag(&this->actor, &this->collider.elements->info);

        if (this->actor.colChkInfo.damageEffect != 0x1) {
            this->actor.colChkInfo.health = 0;
            this->actor.flags &= ~ACTOR_FLAG_1;
            Enemy_StartFinishingBlow(globalCtx, &this->actor);
            EnRuppecrow_HandleDeath(this);
        }
    }
}

void EnRuppecrow_HandleSong(EnRuppecrow* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    EnRuppecrow_UpdatePosition(this, globalCtx);
    if (this->actor.xzDistToPlayer < 1000.0f && EnRuppecrow_CheckPlayedMatchingSong(globalCtx)) {
        // If Link is in front, the guay will turn around and go the other way
        if (Actor_IsFacingPlayer(&this->actor, 0x4000)) {
            this->isGoingCounterClockwise |= 1;
            if (this->currentPoint > 0) {
                this->currentPoint--;
            } else {
                this->currentPoint = this->path->count - 1;
            }
        }

        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
        this->actionFunc = EnRuppecrow_HandleSongCutscene;
    }

    if (player->stateFlags2 & 0x8000000) {
        Math_ApproachF(&this->actor.speedXZ, 0.0f, 0.1f, 1.0f);
    } else {
        Math_ApproachF(&this->actor.speedXZ, 6.0f, 0.1f, 0.1f);
    }

    Actor_MoveWithoutGravity(&this->actor);
    this->yOffset += 0x1000;
    this->actor.shape.yOffset = Math_SinS(this->yOffset) * 500.0f;

    if ((globalCtx->state.frames % 43) == 0) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_KAICHO_CRY);
    }
}

void EnRuppecrow_HandleSongCutscene(EnRuppecrow* this, GlobalContext* globalCtx) {
    EnRuppecrow_UpdatePosition(this, globalCtx);

    if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
        ActorCutscene_Start(this->actor.cutscene, &this->actor);
        EnRuppecrow_UpdateSpeed(this, globalCtx);
        this->actionFunc = EnRuppecrow_FlyWhileDroppingRupees;
    } else {
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    }

    Actor_MoveWithoutGravity(&this->actor);
}

void EnRuppecrow_FlyWhileDroppingRupees(EnRuppecrow* this, GlobalContext* globalCtx) {
    EnRuppecrow_UpdatePosition(this, globalCtx);

    if (this->rupeeIndex >= ENRUPPECROW_RUPEE_COUNT) {
        // Finished spawning rupees; fly up and then despawn
        this->speedModifier = 6.0f;

        // Source of the "Termina Field Guay Glitch"; guay will no longer fall if killed after this point
        this->actor.gravity = 0.0f;

        Math_ApproachF(&this->actor.speedXZ, 6.0f, 0.2f, 0.5f);
        Math_ApproachF(&this->actor.velocity.y, 3.0f, 0.2f, 0.5f);

        this->actionFunc = EnRuppecrow_FlyToDespawn;
        this->skelAnime.playSpeed = 1.0f;
        Actor_MoveWithGravity(&this->actor);
    } else {
        if (ActorCutscene_GetCurrentIndex() != this->actor.cutscene) {
            EnRuppecrow_UpdateSpeed(this, globalCtx);
            Math_ApproachF(&this->actor.speedXZ, this->speedModifier, 0.2f, 0.5f);
        }

        Actor_MoveWithoutGravity(&this->actor);
        this->yOffset += 0x1000;
        this->actor.shape.yOffset = Math_SinS(this->yOffset) * 500.0f;

        if ((globalCtx->state.frames % 43) == 0) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_KAICHO_CRY);
        }
    }
}

void EnRuppecrow_FlyToDespawn(EnRuppecrow* this, GlobalContext* globalCtx) {
    if (this->actor.bgCheckFlags & 0x8) {
        this->actor.world.rot.y *= -0x1;
    }

    Math_ApproachF(&this->actor.speedXZ, this->speedModifier, 0.1f, 0.1f);
    Math_ApproachF(&this->actor.velocity.y, 3.0f, 0.2f, 0.5f);

    if (this->actor.world.pos.y > 1000.0f || this->actor.xzDistToPlayer > 2000.0f) {
        Actor_MarkForDeath(&this->actor);
    } else {
        this->yOffset += 0x800;
        this->actor.shape.yOffset = Math_SinS(this->yOffset) * 500.0f;

        Actor_MoveWithGravity(&this->actor);

        if ((globalCtx->state.frames % 43) == 0) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_KAICHO_CRY);
        }
    }
}

void EnRuppecrow_FallToDespawn(EnRuppecrow* this, GlobalContext* globalCtx) {
    Math_StepToF(&this->actor.speedXZ, 0.0f, 0.5f);

    if (this->currentEffect != ENRUPPECROW_EFFECT_ICE) {
        Math_StepToF(&this->unk_2C8, 0.0f, 0.05f);
        this->unk_2CC = (this->unk_2C8 + 1.0f) * 0.25f;
        this->unk_2CC = CLAMP_MAX(this->unk_2CC, 0.5f);
    } else if (!Math_StepToF(&this->iceSfxTimer, 0.5f, 0.0125f)) {
        func_800B9010(&this->actor, NA_SE_EV_ICE_FREEZE - SFX_FLAG);
    }

    this->actor.colorFilterTimer = 40;
    if (!(this->actor.flags & ACTOR_FLAG_8000)) {
        if (this->currentEffect != ENRUPPECROW_EFFECT_ICE) {
            Math_ScaledStepToS(&this->actor.shape.rot.x, 0x4000, 0x200);
            this->actor.shape.rot.z += 0x1780;
        }

        if (this->actor.bgCheckFlags & 0x1 || this->actor.floorHeight == BGCHECK_Y_MIN) {
            EnRuppecrow_ShatterIce(this, globalCtx);
            func_800B3030(globalCtx, &this->actor.world.pos, &gZeroVec3f, &gZeroVec3f, (this->actor.scale.x * 10000.0f),
                          0x0, 0x0);

            SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->actor.world.pos, 0xB, NA_SE_EN_EXTINCT);
            Actor_MarkForDeath(&this->actor);
            return;
        }
    }

    Actor_MoveWithGravity(&this->actor);
}

void EnRuppecrow_Init(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    EnRuppecrow* this = THIS;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &gGuaySkel, &gGuayFlyAnim, this->joinTable, this->morphTable,
                       OBJECT_CROW_LIMB_MAX);
    ActorShape_Init(&this->actor.shape, 2000.0f, ActorShadow_DrawCircle, 20.0f);

    Collider_InitJntSph(globalCtx, &this->collider);
    Collider_InitAndSetJntSph(globalCtx, &this->collider, &this->actor, &sJntSphInit, &this->colliderElement);
    this->collider.elements->dim.worldSphere.radius = sJntSphInit.elements->dim.modelSphere.radius;
    CollisionCheck_SetInfo(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);

    Actor_SetScale(&this->actor, 0.01f);
    this->actor.flags |= ACTOR_FLAG_2000000;

    this->path = SubS_GetPathByIndex(globalCtx, ENRUPPECROW_GET_PATH(&this->actor), 0x3F);
    if (this->path != NULL) {
        this->actionFunc = EnRuppecrow_HandleSong;
    } else {
        Actor_MarkForDeath(&this->actor);
    }
}

void EnRuppecrow_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnRuppecrow* this = THIS;

    Collider_DestroyJntSph(globalCtx, &this->collider);
}

void EnRuppecrow_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnRuppecrow* this = THIS;

    EnRuppecrow_UpdateDamage(this, globalCtx);
    this->actionFunc(this, globalCtx);
    EnRuppecrow_UpdateRupees(this);
    this->actor.focus.pos = this->actor.world.pos;
    SkelAnime_Update(&this->skelAnime);
    EnRuppecrow_UpdateCollision(this, globalCtx);
}

void EnRuppecrow_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnRuppecrow* this = THIS;

    func_8012C28C(globalCtx->state.gfxCtx);
    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          NULL, NULL, &this->actor);
}
