/*
 * File: z_en_ruppecrow.c
 * Overlay: ovl_En_Ruppecrow
 * Description: Guay Circling Clock Town
 */

#include "z_en_ruppecrow.h"

#define FLAGS 0x00004030

#define THIS ((EnRuppecrow*)thisx)

void EnRuppecrow_Init(Actor* thisx, GlobalContext* globalCtx);
void EnRuppecrow_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnRuppecrow_Update(Actor* thisx, GlobalContext* globalCtx);
void EnRuppecrow_Draw(Actor* thisx, GlobalContext* globalCtx);
void EnRuppecrow_HandleSong(EnRuppecrow*, GlobalContext*);
s32 EnRuppecrow_UpdateCollision(EnRuppecrow*, GlobalContext*);
void EnRuppecrow_DespawnRupees(EnRuppecrow*);
void EnRuppecrow_HandleDamage(EnRuppecrow*, GlobalContext*);
void EnRuppecrow_HandleDeath(EnRuppecrow*);
void EnRuppecrow_FallToDespawn(EnRuppecrow*, GlobalContext*);
void func_80BE2728(EnRuppecrow*, GlobalContext*);
void EnRuppecrow_UpdatePosition(EnRuppecrow*, GlobalContext*);
s32 EnRuppecrow_DidPlayMatchingSong(GlobalContext*);
void EnRuppecrow_HandleSongCutscene(EnRuppecrow*, GlobalContext*);
s32 EnRuppecrow_ReachedNextPoint_Clockwise(EnRuppecrow*, Path*, s32);
s32 EnRuppecrow_ReachedNextPoint_CounterClockwise(EnRuppecrow*, Path*, s32);
f32 EnRuppecrow_GetOrientationToNextPoint(Path*, s32, PosRot*, Vec3s*);
s32 EnRuppecrow_CanSpawnBlueRupees(GlobalContext*);
void EnRuppecrow_SpawnRupee(EnRuppecrow*, GlobalContext*);
void EnRuppecrow_FlyWhileDroppingRupees(EnRuppecrow*, GlobalContext*);
void EnRuppecrow_UpdateSpeed(EnRuppecrow*, GlobalContext*);
void EnRuppecrow_FlyToDespawn(EnRuppecrow*, GlobalContext*);

extern AnimationHeader D_060000F0;
extern FlexSkeletonHeader D_060010C0;

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
    UNK_TYPE pad;

    this->collider.elements->dim.worldSphere.center.x = this->actor.world.pos.x;
    this->collider.elements->dim.worldSphere.center.y =
        sJntSphInit.elements->dim.modelSphere.center.y + this->actor.world.pos.y;
    this->collider.elements->dim.worldSphere.center.z = this->actor.world.pos.z;

    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 12.0f, 25.0f, 50.0f, 0x07);

    return true;
}

s32 EnRuppecrow_ReachedNextPoint_Clockwise(EnRuppecrow* this, Path* path, s32 index) {
    Vec3s* points;
    s32 pathCount;
    s32 pathIndex;
    s32 result;
    f32 y;
    f32 x;
    Vec3f vec;
    Vec3f point;

    pathIndex = index;
    points = Lib_SegmentedToVirtual(path->points);
    pathCount = path->count;
    result = false;

    Math_Vec3s_ToVec3f(&point, &points[pathIndex]);

    if (pathIndex == 0) {
        y = points[1].x - points[0].x;
        x = points[1].z - points[0].z;
    } else {
        if (pathIndex == (pathCount - 1)) {
            y = points[pathCount - 1].x - points[pathCount - 2].x;
            x = points[pathCount - 1].z - points[pathCount - 2].z;
        } else {
            y = points[pathIndex + 1].x - points[pathIndex - 1].x;
            x = points[pathIndex + 1].z - points[pathIndex - 1].z;
        }
    }

    func_8017B7F8(&point, (func_80086B30(y, x) * 10430.378f), &vec.z, &vec.y, &vec.x);
    if (((this->actor.world.pos.x * vec.z) + (vec.y * this->actor.world.pos.z) + vec.x) > 0.0f) {
        result = true;
    }

    return result;
}

s32 EnRuppecrow_ReachedNextPoint_CounterClockwise(EnRuppecrow* this, Path* path, s32 index) {
    Vec3s* points;
    s32 pathCount;
    s32 pathIndex;
    s32 result;
    f32 y;
    f32 x;
    Vec3f vec;
    Vec3f point;

    pathIndex = index;
    points = Lib_SegmentedToVirtual(path->points);
    pathCount = path->count;
    result = false;

    Math_Vec3s_ToVec3f(&point, &points[pathIndex]);

    if (pathIndex == 0) {
        y = points[0].x - points[1].x;
        x = points[0].z - points[1].z;
    } else {
        if (pathIndex == (pathCount - 1)) {
            y = points[pathCount - 2].x - points[pathCount - 1].x;
            x = points[pathCount - 2].z - points[pathCount - 1].z;
        } else {
            y = points[pathIndex - 1].x - points[pathIndex + 1].x;
            x = points[pathIndex - 1].z - points[pathIndex + 1].z;
        }
    }

    func_8017B7F8(&point, (func_80086B30(y, x) * 10430.378f), &vec.z, &vec.y, &vec.x);
    if (((this->actor.world.pos.x * vec.z) + (vec.y * this->actor.world.pos.z) + vec.x) > 0.0f) {
        result = true;
    }

    return result;
}

f32 EnRuppecrow_GetOrientationToNextPoint(Path* path, s32 arg1, PosRot* world, Vec3s* orientation) {
    Vec3s* points;
    Vec3f point;

    if (path != NULL) {
        points = Lib_SegmentedToVirtual(path->points);
        points = &points[arg1];
        point.x = points->x;
        point.y = points->y;
        point.z = points->z;
    }

    orientation->y = Math_Vec3f_Yaw(&world->pos, &point);
    orientation->x = Math_Vec3f_Pitch(&world->pos, &point);

    return point.y - world->pos.y;
}

void func_80BE2728(EnRuppecrow* this, GlobalContext* globalCtx) {
    if (this->currentEffect == EN_RUPPECROW_EFFECT_ICE) {
        this->currentEffect = EN_RUPPECROW_EFFECT_NONE;
        this->unk_2C8.x = 0.0f;
        func_800BF7CC(globalCtx, &this->actor, this->limbPos, 0x4, 0x2, 0.2f, 0.2f);
    }
}

s32 EnRuppecrow_CanSpawnBlueRupees(GlobalContext* globalCtx) {
    Player* player;

    player = GET_PLAYER(globalCtx);
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

void EnRuppecrow_DespawnRupees(EnRuppecrow* this) {
    EnItem00* rupee;
    s16 rupeeIndex;

    for (rupeeIndex = 0; rupeeIndex < EN_RUPPECROW_RUPEE_COUNT; rupeeIndex++) {
        rupee = this->rupees[rupeeIndex];
        if (rupee != NULL && rupee->unk152 == 0) {
            Actor_MarkForDeath(&rupee->actor);
        }
    }
}

void EnRuppecrow_SpawnRupee(EnRuppecrow* this, GlobalContext* globalCtx) {
    Player* player;
    f32 xOffset;
    EnItem00* rupee;
    s16 rupeeIndex;

    player = GET_PLAYER(globalCtx);
    rupeeIndex = this->rupeeIndex;

    if (!(player->stateFlags3 & 0x1000)) {
        xOffset = this->rupeeIndex & 1 ? 10.0f : -10.0f;
    } else {
        xOffset = 0.0f;
    }

    if (EnRuppecrow_CanSpawnBlueRupees(globalCtx) && (this->rupeeIndex % 5) == 4) {
        if (this->rupeeIndex == 19) {
            rupee = (EnItem00*)Actor_Spawn(&globalCtx->actorCtx, globalCtx, 0xE, this->actor.world.pos.x + xOffset,
                                           this->actor.world.pos.y, this->actor.world.pos.z, 0x0, 0x0, 0x0,
                                           ITEM00_RUPEE_RED);
            this->rupees[rupeeIndex] = rupee;
            this->rupees[rupeeIndex]->actor.gravity = -5.0f;
            this->rupees[rupeeIndex]->actor.velocity.y = 0.0f;
            Audio_PlayActorSound2(&this->actor, NA_SE_EV_RUPY_FALL);
            rupee = this->rupees[rupeeIndex];
            rupee->unk152 = 60;
            this->rupees[rupeeIndex]->actor.flags |= 0x10;
        } else {
            rupee = (EnItem00*)Actor_Spawn(&globalCtx->actorCtx, globalCtx, 0xE, this->actor.world.pos.x + xOffset,
                                           this->actor.world.pos.y, this->actor.world.pos.z, 0x0, 0x0, 0x0,
                                           ITEM00_RUPEE_BLUE);
            this->rupees[rupeeIndex] = rupee;
            this->rupees[rupeeIndex]->actor.gravity = -5.0f;
            this->rupees[rupeeIndex]->actor.velocity.y = 0.0f;
            Audio_PlayActorSound2(&this->actor, NA_SE_EV_RUPY_FALL);
            rupee = this->rupees[rupeeIndex];
            rupee->unk152 = 60;
            this->rupees[rupeeIndex]->actor.flags |= 0x10;
        }
    } else if (this->rupeeIndex == 19) {
        rupee =
            (EnItem00*)Actor_Spawn(&globalCtx->actorCtx, globalCtx, 0xE, this->actor.world.pos.x + xOffset,
                                   this->actor.world.pos.y, this->actor.world.pos.z, 0x0, 0x0, 0x0, ITEM00_RUPEE_RED);
        this->rupees[rupeeIndex] = rupee;
        this->rupees[rupeeIndex]->actor.gravity = -5.0f;
        this->rupees[rupeeIndex]->actor.velocity.y = 0.0f;
        Audio_PlayActorSound2(&this->actor, NA_SE_EV_RUPY_FALL);
        rupee = this->rupees[rupeeIndex];
        rupee->unk152 = 60;
        this->rupees[rupeeIndex]->actor.flags |= 0x10;
    } else {
        rupee =
            (EnItem00*)Actor_Spawn(&globalCtx->actorCtx, globalCtx, 0xE, this->actor.world.pos.x + xOffset,
                                   this->actor.world.pos.y, this->actor.world.pos.z, 0x0, 0x0, 0x0, ITEM00_RUPEE_GREEN);
        this->rupees[rupeeIndex] = rupee;
        this->rupees[rupeeIndex]->actor.gravity = -5.0f;
        this->rupees[rupeeIndex]->actor.velocity.y = 0.0f;
        Audio_PlayActorSound2(&this->actor, NA_SE_EV_RUPY_FALL);
        rupee = this->rupees[rupeeIndex];
        rupee->unk152 = 60;
        this->rupees[rupeeIndex]->actor.flags |= 0x10;
    }

    this->rupeeIndex++;
}

void EnRuppecrow_UpdatePosition(EnRuppecrow* this, GlobalContext* globalCtx) {
    Vec3s orientation;

    EnRuppecrow_GetOrientationToNextPoint(this->path, this->pathIndex, &this->actor.world, &orientation);
    if (this->actor.bgCheckFlags & 0x8) {
        orientation.y = this->actor.wallYaw;
    }

    Math_SmoothStepToS(&this->actor.world.rot.y, orientation.y, 0x4, 0x3E8, 0x1);
    this->actor.shape.rot.y = this->actor.world.rot.y;
    Math_SmoothStepToS(&this->actor.world.rot.x, -orientation.x, 0x4, 0x3E8, 0x1);

    if (this->isGoingCounterClockwise & 1) {
        if (EnRuppecrow_ReachedNextPoint_CounterClockwise(this, this->path, this->pathIndex)) {
            if (this->pathIndex <= 0) {
                this->pathIndex = this->path->count - 1;
            } else {
                this->pathIndex--;
            }

            if (this->actionFunc == &EnRuppecrow_FlyWhileDroppingRupees &&
                (!EnRuppecrow_CanSpawnBlueRupees(globalCtx) || (this->pathIndex % -2) == 0)) {
                EnRuppecrow_SpawnRupee(this, globalCtx);
            }
        }
    } else if (EnRuppecrow_ReachedNextPoint_Clockwise(this, this->path, this->pathIndex)) {
        if (this->pathIndex >= this->path->count - 1) {
            this->pathIndex = 0;
        } else {
            this->pathIndex++;
        }

        if (this->actionFunc == &EnRuppecrow_FlyWhileDroppingRupees &&
            (!EnRuppecrow_CanSpawnBlueRupees(globalCtx) || (this->pathIndex % -2) == 0)) {
            EnRuppecrow_SpawnRupee(this, globalCtx);
        }
    }
}

s32 EnRuppecrow_DidPlayMatchingSong(GlobalContext* globalCtx) {
    Player* player;

    player = GET_PLAYER(globalCtx);
    if (globalCtx->msgCtx.unk1202A == 0x3) {
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
    Player* player;

    player = GET_PLAYER(globalCtx);
    switch (player->transformation) {
        case PLAYER_FORM_DEKU:
            this->speedModifier = 7.0f;
            break;
        case PLAYER_FORM_GORON:
            this->speedModifier = (player->stateFlags3 & 0x1000) ? 19.0f : 7.0f;
            break;
        case PLAYER_FORM_ZORA:
            this->speedModifier = 7.0f;
            break;
        case PLAYER_FORM_HUMAN:
            this->speedModifier = (player->stateFlags1 & 0x800000) ? 16.0f : 7.0f;
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
    Animation_Change(&this->skelAnime, &D_060000F0, 0.4f, 0.0f, 0.0f, 0x1, -3.0f);

    this->actor.shape.yOffset = 0.0f;
    this->actor.targetArrowOffset = 0.0f;
    this->actor.bgCheckFlags &= 0xFFFE;

    scale = this->actor.scale.x * 100.0f;
    this->actor.world.pos.y += 20.0f * scale;

    Audio_PlayActorSound2(&this->actor, NA_SE_EN_KAICHO_DEAD);

    this->unk_2C8.y = 0.5f;
    if (this->actor.colChkInfo.damageEffect == 0x3) {
        this->currentEffect = EN_RUPPECROW_EFFECT_ICE;
        this->unk_2C8.x = 1.0f;
        this->unk_2C8.z = 0.75f;
    } else if (this->actor.colChkInfo.damageEffect == 0x4) {
        this->currentEffect = EN_RUPPECROW_EFFECT_LIGHT;
        this->unk_2C8.x = 5.0f;
    } else if (this->actor.colChkInfo.damageEffect == 0x2) {
        this->currentEffect = EN_RUPPECROW_EFFECT_NONE;
        this->unk_2C8.x = 5.0f;
    }

    func_800BCB70(&this->actor, 0x4000, 0xFF, 0x0, 0x28);
    if (this->actor.flags & 0x8000) {
        this->actor.speedXZ = 0.0f;
    }

    this->collider.base.acFlags &= ~AC_ON;
    this->actor.flags |= 0x10;
    this->actionFunc = EnRuppecrow_FallToDespawn;
}

void EnRuppecrow_HandleDamage(EnRuppecrow* this, GlobalContext* globalCtx) {
    if (this->collider.base.acFlags & AC_HIT) {
        this->collider.base.acFlags &= ~AC_HIT;
        func_800BE258(&this->actor, this->collider.elements);

        if (this->actor.colChkInfo.damageEffect != 0x1) {
            this->actor.colChkInfo.health = 0;
            this->actor.flags &= ~0x1;
            Enemy_StartFinishingBlow(globalCtx, &this->actor);
            EnRuppecrow_HandleDeath(this);
        }
    }
}

void EnRuppecrow_HandleSong(EnRuppecrow* this, GlobalContext* globalCtx) {
    Player* player;

    player = GET_PLAYER(globalCtx);
    EnRuppecrow_UpdatePosition(this, globalCtx);
    if (this->actor.xzDistToPlayer < 1000.0f && EnRuppecrow_DidPlayMatchingSong(globalCtx)) {
        // If Link is in front, the guay will turn around and go the other way
        if (Actor_IsActorFacingLink(&this->actor, 0x4000)) {
            this->isGoingCounterClockwise |= 1;
            if (this->pathIndex > 0) {
                this->pathIndex--;
            } else {
                this->pathIndex = this->path->count - 1;
            }
        }

        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
        this->actionFunc = EnRuppecrow_HandleSongCutscene;
    }

    if (((s32)player->stateFlags2 * 0x10) < 0) {
        Math_ApproachF(&this->actor.speedXZ, 0.0f, 0.1f, 1.0f);
    } else {
        Math_ApproachF(&this->actor.speedXZ, 6.0f, 0.1f, 0.1f);
    }

    Actor_SetVelocityAndMoveXYRotation(&this->actor);
    EN_RUPPECROW_OSCILLATE_Y_OFFSET(this, 0x1000, 500.0f);

    if (EN_RUPPECROW_SHOULD_CRY(globalCtx)) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_KAICHO_CRY);
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

    Actor_SetVelocityAndMoveXYRotation(&this->actor);
}

void EnRuppecrow_FlyWhileDroppingRupees(EnRuppecrow* this, GlobalContext* globalCtx) {
    EnRuppecrow_UpdatePosition(this, globalCtx);

    if (this->rupeeIndex >= EN_RUPPECROW_RUPEE_COUNT) {
        // Finished spawning rupees; fly up and then despawn
        this->speedModifier = 6.0f;
        this->actor.gravity = 0.0f;

        Math_ApproachF(&this->actor.speedXZ, 6.0f, 0.2f, 0.5f);
        Math_ApproachF(&this->actor.velocity.y, 3.0f, 0.2f, 0.5f);

        this->actionFunc = EnRuppecrow_FlyToDespawn;
        this->skelAnime.playSpeed = 1.0f;
        Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
    } else {
        if (ActorCutscene_GetCurrentIndex() != this->actor.cutscene) {
            EnRuppecrow_UpdateSpeed(this, globalCtx);
            Math_ApproachF(&this->actor.speedXZ, this->speedModifier, 0.2f, 0.5f);
        }

        Actor_SetVelocityAndMoveXYRotation(&this->actor);
        EN_RUPPECROW_OSCILLATE_Y_OFFSET(this, 0x1000, 500.0f);

        if (EN_RUPPECROW_SHOULD_CRY(globalCtx)) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_KAICHO_CRY);
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
        EN_RUPPECROW_OSCILLATE_Y_OFFSET(this, 0x800, 500.0f);
        Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);

        if (EN_RUPPECROW_SHOULD_CRY(globalCtx)) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_KAICHO_CRY);
        }
    }
}

void EnRuppecrow_FallToDespawn(EnRuppecrow* this, GlobalContext* globalCtx) {
    Math_StepToF(&this->actor.speedXZ, 0.0f, 0.5f);

    if (this->currentEffect != EN_RUPPECROW_EFFECT_ICE) {
        Math_StepToF(&this->unk_2C8.x, 0.0f, 0.05f);
        this->unk_2C8.y = (this->unk_2C8.x + 1.0f) * 0.25f;
        this->unk_2C8.y = CLAMP_MAX(this->unk_2C8.y, 0.5f);
    } else if (Math_StepToF(&this->unk_2C8.z, 0.5f, 0.0125f) == 0) {
        func_800B9010(&this->actor, NA_SE_EV_ICE_FREEZE - SFX_FLAG);
    }

    this->actor.colorFilterTimer = 40;
    if (!(this->actor.flags & 0x8000)) {
        if (this->currentEffect != EN_RUPPECROW_EFFECT_ICE) {
            Math_ScaledStepToS(&this->actor.shape.rot.x, 0x4000, 0x200);
            this->actor.shape.rot.z += 0x1780;
        }

        if (this->actor.bgCheckFlags & 0x1 || this->actor.floorHeight == -32000.0f) {
            func_80BE2728(this, globalCtx);
            func_800B3030(globalCtx, &this->actor.world.pos, &D_801D15B0, &D_801D15B0, (this->actor.scale.x * 10000.0f),
                          0x0, 0x0);

            Audio_PlaySoundAtPosition(globalCtx, &this->actor.world.pos, 0xB, NA_SE_EN_EXTINCT);
            Actor_MarkForDeath(&this->actor);
            return;
        }
    }

    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
}

void EnRuppecrow_Init(Actor* thisx, GlobalContext* globalCtx2) {
    EnRuppecrow* this = THIS;
    GlobalContext* globalCtx = globalCtx2;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &D_060010C0, &D_060000F0, this->joinTable, this->morphTable, 9);
    ActorShape_Init(&this->actor.shape, 2000.0f, func_800B3FC0, 20.0f);

    Collider_InitJntSph(globalCtx, &this->collider);
    Collider_InitAndSetJntSph(globalCtx, &this->collider, &this->actor, &sJntSphInit, &this->colliderElement);
    this->collider.elements->dim.worldSphere.radius = sJntSphInit.elements->dim.modelSphere.radius;
    CollisionCheck_SetInfo(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);

    Actor_SetScale(&this->actor, 0.01f);
    this->actor.flags |= 0x2000000;

    this->path = func_8013D648(globalCtx, (this->actor.params & 0xFC00) >> 0xA, 0x3F);
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

    EnRuppecrow_HandleDamage(this, globalCtx);
    this->actionFunc(this, globalCtx);
    EnRuppecrow_DespawnRupees(this);
    this->actor.focus.pos = this->actor.world.pos;
    SkelAnime_Update(&this->skelAnime);
    EnRuppecrow_UpdateCollision(this, globalCtx);
}

void EnRuppecrow_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnRuppecrow* this = THIS;

    func_8012C28C(globalCtx->state.gfxCtx);
    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                          (s32)this->skelAnime.dListCount, NULL, NULL, &this->actor);
}
