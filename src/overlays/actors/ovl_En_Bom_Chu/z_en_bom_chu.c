/*
 * File: z_en_bom_chu.c
 * Overlay: ovl_En_Bom_Chu
 * Description: Bombchus
 */

#include "z_en_bom_chu.h"
#include "overlays/actors/ovl_En_Bom/z_en_bom.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((EnBomChu*)thisx)

#define BOMBCHU_SCALE 0.01f

void EnBomChu_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBomChu_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBomChu_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBomChu_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnBomChu_WaitForRelease(EnBomChu* this, GlobalContext* globalCtx);
void EnBomChu_SetupMove(EnBomChu* this);
void EnBomChu_Move(EnBomChu* this, GlobalContext* globalCtx);
void EnBomChu_Explode(EnBomChu* this, GlobalContext* globalCtx);
void EnBomChu_WaitForDeath(EnBomChu* this, GlobalContext* globalCtx);

const ActorInit En_Bom_Chu_InitVars = {
    ACTOR_EN_BOM_CHU,
    ACTORCAT_EXPLOSIVES,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnBomChu),
    (ActorFunc)EnBomChu_Init,
    (ActorFunc)EnBomChu_Destroy,
    (ActorFunc)EnBomChu_Update,
    (ActorFunc)EnBomChu_Draw,
};

static ColliderSphereInit sSphereInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_1 | OC1_TYPE_2,
        OC2_TYPE_2,
        COLSHAPE_SPHERE,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 1, { { 0, 0, 0 }, 13 }, 100 },
};

static InitChainEntry sInitChain[] = {
    ICHAIN_U8(targetMode, 2, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 1000 * BOMBCHU_SCALE, ICHAIN_STOP),
};

static EffectBlureInit2 sBlureInit = {
    0, 0, 0, { 250, 0, 0, 250 }, { 200, 0, 0, 130 }, { 150, 0, 0, 100 }, { 100, 0, 0, 50 }, 16,
    0, 0, 0, { 0, 0, 0, 0 },     { 0, 0, 0, 0 },
};

void EnBomChu_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnBomChu* this = THIS;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    Collider_InitAndSetSphere(globalCtx, &this->collider, &this->actor, &sSphereInit);
    this->collider.dim.worldSphere.radius = sSphereInit.dim.modelSphere.radius;

    Effect_Add(globalCtx, &this->blure1Index, EFFECT_BLURE2, 0, 0, &sBlureInit);
    Effect_Add(globalCtx, &this->blure2Index, EFFECT_BLURE2, 0, 0, &sBlureInit);

    this->timer = 120;
    this->actor.room = -1;
    this->shouldTimerCountDown = true;
    this->unk_174 = 0.0f;
    this->actionFunc = EnBomChu_WaitForRelease;
}

void EnBomChu_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnBomChu* this = THIS;

    Effect_Destroy(globalCtx, this->blure1Index);
    Effect_Destroy(globalCtx, this->blure2Index);
    Collider_DestroySphere(globalCtx, &this->collider);
}

/**
 * Returns true if floorPoly is valid for the Bombchu to move on, false otherwise.
 */
s32 EnBomChu_UpdateFloorPoly(EnBomChu* this, CollisionPoly* floorPoly, GlobalContext* globalCtx) {
    Vec3f normal;
    Vec3f vec;
    f32 angle;
    f32 magnitude;
    f32 normDotUp;

    this->actor.floorPoly = floorPoly;

    // This NULL check means if the player releases a Bombchu with no collision
    // below them, the game will not crash, unlike OoT.
    if (floorPoly != NULL) {
        normal.x = COLPOLY_GET_NORMAL(floorPoly->normal.x);
        normal.y = COLPOLY_GET_NORMAL(floorPoly->normal.y);
        normal.z = COLPOLY_GET_NORMAL(floorPoly->normal.z);
    } else {
        EnBomChu_Explode(this, globalCtx);
        return false;
    }

    normDotUp = DOTXYZ(normal, this->axisUp);

    if (fabsf(normDotUp) >= 0.999f) {
        return false;
    }

    angle = func_80086C48(normDotUp);
    if (angle < 0.001f) {
        return false;
    }

    Math3D_CrossProduct(&this->axisUp, &normal, &vec);

    magnitude = Math3D_Vec3fMagnitude(&vec);

    if (magnitude < 0.001f) {
        EnBomChu_Explode(this, globalCtx);
        return false;
    }

    Math_Vec3f_Scale(&vec, 1.0f / magnitude);
    Matrix_InsertRotationAroundUnitVector_f(angle, &vec, MTXMODE_NEW);
    Matrix_MultiplyVector3fByState(&this->axisLeft, &vec);
    Math_Vec3f_Copy(&this->axisLeft, &vec);
    Math3D_CrossProduct(&this->axisLeft, &normal, &this->axisForwards);

    magnitude = Math3D_Vec3fMagnitude(&this->axisForwards);
    if (magnitude < 0.001f) {
        EnBomChu_Explode(this, globalCtx);
        return false;
    }

    Math_Vec3f_Scale(&this->axisForwards, 1.0f / magnitude);
    Math_Vec3f_Copy(&this->axisUp, &normal);
    return true;
}

void EnBomChu_UpdateRotation(EnBomChu* this) {
    MtxF mf;

    mf.xx = this->axisLeft.x;
    mf.xy = this->axisLeft.y;
    mf.xz = this->axisLeft.z;

    mf.yx = this->axisUp.x;
    mf.yy = this->axisUp.y;
    mf.yz = this->axisUp.z;

    mf.zx = this->axisForwards.x;
    mf.zy = this->axisForwards.y;
    mf.zz = this->axisForwards.z;

    func_8018219C(&mf, &this->actor.world.rot, 0);
    this->actor.world.rot.x = -this->actor.world.rot.x;
}

void EnBomChu_WaitForRelease(EnBomChu* this, GlobalContext* globalCtx) {
    Player* player;

    if (this->timer == 0) {
        EnBomChu_Explode(this, globalCtx);
    } else if (Actor_HasNoParent(&this->actor, globalCtx)) {
        player = GET_PLAYER(globalCtx);
        Math_Vec3f_Copy(&this->actor.world.pos, &player->actor.world.pos);
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 4);

        this->actor.shape.rot.y = player->actor.shape.rot.y;
        this->actor.flags |= ACTOR_FLAG_1;
        func_800B8EF4(globalCtx, &this->actor);

        this->isMoving = true;
        this->actor.speedXZ = 8.0f;
        this->movingSpeed = 8.0f;
        EnBomChu_SetupMove(this);
    }
}

s32 EnBomChu_IsOnCollisionPoly(GlobalContext* globalCtx, Vec3f* posA, Vec3f* posB, Vec3f* posResult,
                               CollisionPoly** poly, s32* bgId) {
    if ((BgCheck_EntityLineTest1(&globalCtx->colCtx, posA, posB, posResult, poly, true, true, true, true, bgId)) &&
        (!(func_800C9A4C(&globalCtx->colCtx, *poly, *bgId) & 0x30))) {
        return true;
    }

    return false;
}

void EnBomChu_SetupMove(EnBomChu* this) {
    func_800BE3D0(&this->actor, this->actor.shape.rot.y, &this->actor.shape.rot);

    Matrix_RotateY(this->actor.shape.rot.y, MTXMODE_NEW);
    Matrix_InsertXRotation_s(this->actor.shape.rot.x, MTXMODE_APPLY);
    Matrix_InsertZRotation_s(this->actor.shape.rot.z, MTXMODE_APPLY);

    Matrix_GetStateTranslationAndScaledY(1.0f, &this->axisUp);
    Matrix_GetStateTranslationAndScaledZ(1.0f, &this->axisForwards);
    Matrix_GetStateTranslationAndScaledX(1.0f, &this->axisLeft);

    this->actor.world.rot.x = -this->actor.shape.rot.x;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actor.world.rot.z = this->actor.shape.rot.z;
    this->actionFunc = EnBomChu_Move;
}

void EnBomChu_Move(EnBomChu* this, GlobalContext* globalCtx) {
    CollisionPoly* polySide = NULL;
    CollisionPoly* polyUpDown = NULL;
    s32 bgIdSide;
    s32 bgIdUpDown;
    s32 i;
    s32 isFloorPolyValid;
    f32 lineLength;
    Vec3f posA;
    Vec3f posB;
    Vec3f posSide;
    Vec3f posUpDown;

    bgIdUpDown = bgIdSide = BGCHECK_SCENE;
    isFloorPolyValid = false;

    this->actor.speedXZ = this->movingSpeed;
    lineLength = 2.0f * this->movingSpeed;

    if ((this->timer == 0) || (this->collider.base.acFlags & AC_HIT) || (this->collider.base.ocFlags1 & OC1_HIT)) {
        EnBomChu_Explode(this, globalCtx);
        return;
    }

    posA.x = this->actor.world.pos.x + (this->axisUp.x * 2.0f);
    posA.y = this->actor.world.pos.y + (this->axisUp.y * 2.0f);
    posA.z = this->actor.world.pos.z + (this->axisUp.z * 2.0f);

    posB.x = this->actor.world.pos.x - (this->axisUp.x * 4.0f);
    posB.y = this->actor.world.pos.y - (this->axisUp.y * 4.0f);
    posB.z = this->actor.world.pos.z - (this->axisUp.z * 4.0f);

    if (EnBomChu_IsOnCollisionPoly(globalCtx, &posA, &posB, &posUpDown, &polyUpDown, &bgIdUpDown)) {
        // forwards
        posB.x = (this->axisForwards.x * lineLength) + posA.x;
        posB.y = (this->axisForwards.y * lineLength) + posA.y;
        posB.z = (this->axisForwards.z * lineLength) + posA.z;

        if (EnBomChu_IsOnCollisionPoly(globalCtx, &posA, &posB, &posSide, &polySide, &bgIdSide)) {
            isFloorPolyValid = EnBomChu_UpdateFloorPoly(this, polySide, globalCtx);
            Math_Vec3f_Copy(&this->actor.world.pos, &posSide);
            this->actor.floorBgId = bgIdSide;
            this->actor.speedXZ = 0.0f;
        } else {
            if (this->actor.floorPoly != polyUpDown) {
                isFloorPolyValid = EnBomChu_UpdateFloorPoly(this, polyUpDown, globalCtx);
            }

            Math_Vec3f_Copy(&this->actor.world.pos, &posUpDown);
            this->actor.floorBgId = bgIdUpDown;
        }
    } else {
        this->actor.speedXZ = 0.0f;
        lineLength *= 3.0f;
        Math_Vec3f_Copy(&posA, &posB);

        for (i = 0; i < 3; i++) {
            if (i == 0) {
                // backwards
                posB.x = posA.x - (this->axisForwards.x * lineLength);
                posB.y = posA.y - (this->axisForwards.y * lineLength);
                posB.z = posA.z - (this->axisForwards.z * lineLength);
            } else if (i == 1) {
                // left
                posB.x = posA.x + (this->axisLeft.x * lineLength);
                posB.y = posA.y + (this->axisLeft.y * lineLength);
                posB.z = posA.z + (this->axisLeft.z * lineLength);
            } else {
                // right
                posB.x = posA.x - (this->axisLeft.x * lineLength);
                posB.y = posA.y - (this->axisLeft.y * lineLength);
                posB.z = posA.z - (this->axisLeft.z * lineLength);
            }

            if (EnBomChu_IsOnCollisionPoly(globalCtx, &posA, &posB, &posSide, &polySide, &bgIdSide)) {
                isFloorPolyValid = EnBomChu_UpdateFloorPoly(this, polySide, globalCtx);
                Math_Vec3f_Copy(&this->actor.world.pos, &posSide);
                this->actor.floorBgId = bgIdSide;
                break;
            }
        }

        if (i == 3) {
            // no collision nearby
            EnBomChu_Explode(this, globalCtx);
        }
    }

    if (isFloorPolyValid) {
        EnBomChu_UpdateRotation(this);
        this->actor.shape.rot.x = -this->actor.world.rot.x;
        this->actor.shape.rot.y = this->actor.world.rot.y;
        this->actor.shape.rot.z = this->actor.world.rot.z;
    }

    if (this->isMoving) {
        func_800B8F98(&this->actor, NA_SE_IT_BOMBCHU_MOVE - SFX_FLAG);
    }

    if (this->actor.speedXZ != 0.0f) {
        this->movingSpeed = this->actor.speedXZ;
    }
}

void EnBomChu_Explode(EnBomChu* this, GlobalContext* globalCtx) {
    EnBom* bomb;
    s32 i;

    bomb = (EnBom*)Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_BOM, this->actor.world.pos.x,
                               this->actor.world.pos.y, this->actor.world.pos.z, 0, 0, 0, 0);

    this->shouldTimerCountDown = true;
    this->isMoving = false;

    if (bomb != NULL) {
        bomb->timer = 0;
    }

    this->timer = 1;
    this->actor.speedXZ = 0.0f;

    if (this->actor.depthInWater > 0.0f) {
        for (i = 0; i < 40; i++) {
            EffectSsBubble_Spawn(globalCtx, &this->actor.world.pos, 1.0f, 5.0f, 30.0f, 0.25f);
        }
    }

    this->actor.draw = NULL;
    this->actionFunc = EnBomChu_WaitForDeath;
}

void EnBomChu_WaitForDeath(EnBomChu* this, GlobalContext* globalCtx) {
    if (this->timer == 0) {
        Actor_MarkForDeath(&this->actor);
    }
}

/**
 * Transform coordinates from actor coordinate space to world space, according to current orientation.
 * `offset` is expected to already be at world scale.
 */
void EnBomChu_ActorCoordsToWorld(EnBomChu* this, Vec3f* offset, Vec3f* pos) {
    f32 x = offset->x + this->visualJitter;

    pos->x = this->actor.world.pos.x + (this->axisLeft.x * x) + (this->axisUp.x * offset->y) +
             (this->axisForwards.x * offset->z);
    pos->y = this->actor.world.pos.y + (this->axisLeft.y * x) + (this->axisUp.y * offset->y) +
             (this->axisForwards.y * offset->z);
    pos->z = this->actor.world.pos.z + (this->axisLeft.z * x) + (this->axisUp.z * offset->y) +
             (this->axisForwards.z * offset->z);
}

void EnBomChu_SpawnRipplesAndSplashes(EnBomChu* this, GlobalContext* globalCtx, f32 y, s32 spawnExtraRipples) {
    s32 pad;
    Vec3f pos;

    pos.x = this->actor.world.pos.x;
    pos.y = y;
    pos.z = this->actor.world.pos.z;

    EffectSsGRipple_Spawn(globalCtx, &pos, 70, 500, 0);

    if (spawnExtraRipples) {
        EffectSsGRipple_Spawn(globalCtx, &pos, 70, 500, 4);
        EffectSsGRipple_Spawn(globalCtx, &pos, 70, 500, 8);
    } else {
        pos.x -= this->axisForwards.x * 10.0f;
        pos.z -= this->axisForwards.z * 10.0f;
    }

    pos.y += 5.0f;
    EffectSsGSplash_Spawn(globalCtx, &pos, NULL, NULL, 1, 450);
}

void EnBomChu_HandleNonSceneCollision(EnBomChu* this, GlobalContext* globalCtx) {
    Vec3f originalWorldPos;
    Vec3f posA;
    Vec3f posB;
    Vec3f originalAxisUp;
    s16 yaw;
    f32 sin;
    f32 cos;
    f32 tempX;
    CollisionPoly* poly = NULL;
    s32 bgId = BGCHECK_SCENE;
    s32 isFloorPolyValid;

    Math_Vec3f_Copy(&originalWorldPos, &this->actor.world.pos);
    Math_Vec3f_Copy(&originalAxisUp, &this->axisUp);
    yaw = this->actor.shape.rot.y;
    BgCheck2_UpdateActorAttachedToMesh(&globalCtx->colCtx, this->actor.floorBgId, &this->actor);

    if (yaw != this->actor.shape.rot.y) {
        yaw = this->actor.shape.rot.y - yaw;

        sin = Math_SinS(yaw);
        cos = Math_CosS(yaw);

        tempX = this->axisForwards.x;
        this->axisForwards.x = (sin * this->axisForwards.z) + (cos * tempX);
        this->axisForwards.z = (cos * this->axisForwards.z) - (sin * tempX);

        tempX = this->axisUp.x;
        this->axisUp.x = (sin * this->axisUp.z) + (cos * tempX);
        this->axisUp.z = (cos * this->axisUp.z) - (sin * tempX);

        tempX = this->axisLeft.x;
        this->axisLeft.x = (sin * this->axisLeft.z) + (cos * tempX);
        this->axisLeft.z = (cos * this->axisLeft.z) - (sin * tempX);
    }

    posA.x = originalWorldPos.x + (2.0f * originalAxisUp.x);
    posA.y = originalWorldPos.y + (2.0f * originalAxisUp.y);
    posA.z = originalWorldPos.z + (2.0f * originalAxisUp.z);

    posB.x = this->actor.world.pos.x + (2.0f * this->axisUp.x);
    posB.y = this->actor.world.pos.y + (2.0f * this->axisUp.y);
    posB.z = this->actor.world.pos.z + (2.0f * this->axisUp.z);

    if (EnBomChu_IsOnCollisionPoly(globalCtx, &posA, &posB, &originalWorldPos, &poly, &bgId)) {
        isFloorPolyValid = EnBomChu_UpdateFloorPoly(this, poly, globalCtx);
        Math_Vec3f_Copy(&this->actor.world.pos, &originalWorldPos);
        this->actor.floorBgId = bgId;
        this->actor.speedXZ = 0.0f;

        if (isFloorPolyValid) {
            EnBomChu_UpdateRotation(this);
            this->actor.shape.rot.x = -this->actor.world.rot.x;
            this->actor.shape.rot.y = this->actor.world.rot.y;
            this->actor.shape.rot.z = this->actor.world.rot.z;
        }
    }
}

void EnBomChu_Update(Actor* thisx, GlobalContext* globalCtx) {
    static Vec3f sBlureP1Offset = { 0.0f, 7.0f, -6.0f };
    static Vec3f sBlureP2LeftOffset = { 12.0f, 0.0f, -5.0f };
    static Vec3f sBlureP2RightOffset = { -12.0f, 0.0f, -5.0f };
    s32 pad;
    EnBomChu* this = THIS;
    Vec3f blureP1;
    Vec3f blureP2;
    WaterBox* waterBox;
    f32 waterY;

    if (this->actor.floorBgId != BGCHECK_SCENE) {
        EnBomChu_HandleNonSceneCollision(this, globalCtx);
    }

    if (this->shouldTimerCountDown) {
        this->timer--;
    }

    this->actionFunc(this, globalCtx);

    if ((this->actionFunc != EnBomChu_WaitForDeath) &&
        (SurfaceType_IsWallDamage(&globalCtx->colCtx, this->actor.floorPoly, this->actor.floorBgId))) {
        EnBomChu_Explode(this, globalCtx);
        return;
    }

    Actor_MoveWithoutGravity(&this->actor);

    this->collider.dim.worldSphere.center.x = this->actor.world.pos.x;
    this->collider.dim.worldSphere.center.y = this->actor.world.pos.y;
    this->collider.dim.worldSphere.center.z = this->actor.world.pos.z;

    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    if (this->actionFunc != EnBomChu_WaitForRelease) {
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }

    this->actor.focus.pos.x = this->actor.world.pos.x + (20.0f * this->axisUp.x);
    this->actor.focus.pos.y = this->actor.world.pos.y + (20.0f * this->axisUp.y);
    this->actor.focus.pos.z = this->actor.world.pos.z + (20.0f * this->axisUp.z);

    if (this->isMoving) {
        this->visualJitter =
            (5.0f + (Rand_ZeroOne() * 3.0f)) * Math_SinS((((s32)(Rand_ZeroOne() * 512.0f) + 0x3000) * this->timer));
        EnBomChu_ActorCoordsToWorld(this, &sBlureP1Offset, &blureP1);

        EnBomChu_ActorCoordsToWorld(this, &sBlureP2LeftOffset, &blureP2);
        EffectBlure_AddVertex(Effect_GetByIndex(this->blure1Index), &blureP1, &blureP2);

        EnBomChu_ActorCoordsToWorld(this, &sBlureP2RightOffset, &blureP2);
        EffectBlure_AddVertex(Effect_GetByIndex(this->blure2Index), &blureP1, &blureP2);

        waterY = this->actor.world.pos.y;

        if (WaterBox_GetSurface1(globalCtx, &globalCtx->colCtx, this->actor.world.pos.x, this->actor.world.pos.z,
                                 &waterY, &waterBox)) {
            this->actor.depthInWater = waterY - this->actor.world.pos.y;

            if (this->actor.depthInWater < 0.0f) {
                if (this->actor.bgCheckFlags & 0x20) {
                    EnBomChu_SpawnRipplesAndSplashes(this, globalCtx, waterY, true);
                }

                this->actor.bgCheckFlags &= ~0x20;
                return;
            }

            if (!(this->actor.bgCheckFlags & 0x20) && (this->timer != 120)) {
                EnBomChu_SpawnRipplesAndSplashes(this, globalCtx, waterY, true);
            } else {
                EffectSsBubble_Spawn(globalCtx, &this->actor.world.pos, 0.0f, 3.0f, 15.0f, 0.25f);
            }

            this->actor.bgCheckFlags |= 0x20;
        } else {
            this->actor.bgCheckFlags &= ~0x20;
            this->actor.depthInWater = BGCHECK_Y_MIN;
        }
    }
}

void EnBomChu_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnBomChu* this = THIS;
    f32 colorIntensity;
    s32 blinkHalfPeriod;
    s32 blinkTime;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);
    func_800B8050(&this->actor, globalCtx, 0);

    if (this->timer >= 40) {
        blinkTime = this->timer % 20;
        blinkHalfPeriod = 10;
    } else if (this->timer >= 10) {
        blinkTime = this->timer % 10;
        blinkHalfPeriod = 5;
    } else {
        blinkTime = this->timer & 1;
        blinkHalfPeriod = 1;
    }

    if (blinkTime > blinkHalfPeriod) {
        blinkTime = 2 * blinkHalfPeriod - blinkTime;
    }

    colorIntensity = blinkTime / (f32)blinkHalfPeriod;
    gDPSetEnvColor(POLY_OPA_DISP++, (s32)(colorIntensity * 209.0f) + 9, (s32)(colorIntensity * 34.0f) + 9,
                   (s32)(colorIntensity * -35.0f) + 35, 255);
    Matrix_InsertTranslation(this->visualJitter * (1.0f / BOMBCHU_SCALE), 0.0f, 0.0f, MTXMODE_APPLY);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, gBombchuDL);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
