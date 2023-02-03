/*
 * File: z_obj_mine.c
 * Overlay: ovl_Obj_Mine
 * Description: Spike metal mine
 */

#include "z_obj_mine.h"
#include "overlays/actors/ovl_En_Bom/z_en_bom.h"
#include "assets/objects/object_ny/object_ny.h"

#define FLAGS 0x00000000

#define THIS ((ObjMine*)thisx)

#define LINK_SIZE 12.0f
#define ATTACH_OFFSET 10.0f
#define AIR_RADIUS 24.0f
#define WATER_RADIUS 36.0f
#define BOMB_SPAWN_OFFSET 15.0f

#define RAND_PLUSMINUS(limit) (Rand_ZeroOne()*(2.0f * (limit)) - (limit))
#define RAND_PLUSMINUSALT(limit) ((Rand_ZeroOne() - 0.5f) * (2.0f * limit))

void ObjMine_Init(Actor* thisx, PlayState* play);
void ObjMine_Destroy(Actor* thisx, PlayState* play);
void ObjMine_Path_Update(Actor* thisx, PlayState* play);
void ObjMine_Path_Draw(Actor* thisx, PlayState* play);

void ObjMine_Path_SetupStationary(ObjMine* this);
void ObjMine_Path_Stationary(ObjMine* this, PlayState* play);
void ObjMine_Path_SetupMove(ObjMine* this);
void ObjMine_Path_Move(ObjMine* this, PlayState* play);
void ObjMine_Explode(ObjMine* this, PlayState* play);
void ObjMine_Air_SetupChained(ObjMine* this);
void ObjMine_Air_Chained(ObjMine* this, PlayState* play);
void ObjMine_Air_SetupStationary(ObjMine* this);
void ObjMine_Air_Stationary(ObjMine* this, PlayState* play);
void ObjMine_Water_SetupChained(ObjMine* this);
void ObjMine_Water_Chained(ObjMine* this, PlayState* play);
void ObjMine_Water_SetupStationary(ObjMine* this);
void ObjMine_Water_Stationary(ObjMine* this, PlayState* play);

void ObjMine_AirWater_Update(Actor* thisx, PlayState* play);
void ObjMine_DrawExplosion(Actor* thisx, PlayState* play);
void ObjMine_Air_Draw(Actor* thisx, PlayState* play);
void ObjMine_Water_Draw(Actor* thisx, PlayState* play);

ActorInit Obj_Mine_InitVars = {
    ACTOR_OBJ_MINE,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_NY,
    sizeof(ObjMine),
    (ActorFunc)ObjMine_Init,
    (ActorFunc)ObjMine_Destroy,
    (ActorFunc)ObjMine_Path_Update,
    (ActorFunc)ObjMine_Path_Draw,
};

static ColliderJntSphElementInit sJntSphElementsInit[1] = {
    {
        {
            ELEMTYPE_UNK2,
            { 0x00000000, 0x00, 0x00 },
            { 0x01CBFFBE, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 0, { { 0, 0, 0 }, 30 }, 100 },
    },
};

static ColliderJntSphInit sJntSphInit = {
    {
        COLTYPE_METAL,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_PLAYER | OC1_TYPE_1,
        OC2_TYPE_1,
        COLSHAPE_JNTSPH,
    },
    ARRAY_COUNT(sJntSphElementsInit),
    sJntSphElementsInit,
};

static f32 sPathSpeeds[] = {
    1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f,
};

static ObjMineMtxF3 sStandardBasis = {
    { 1.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.0f, 1.0f },
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 1300, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 150, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 100, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_STOP),
};

void ObjMine_Path_MoveToWaypoint(ObjMine* this, s32 index) {
    Math_Vec3s_ToVec3f(&this->actor.world.pos, &this->waypoints[index]);
}

s32 ObjMine_GetUnitVec3f(Vec3f* src, Vec3f* dst) {
    f32 mag = Math3D_Vec3fMagnitude(src);

    if (mag < 0.001f) {
        return false;
    }

    dst->x = src->x * (1.0f / mag);
    dst->y = src->y * (1.0f / mag);
    dst->z = src->z * (1.0f / mag);
    return true;
}

s32 ObjMine_GetUnitVec3fNorm(Vec3f* src, Vec3f* dst, f32* norm, f32* invNorm) {
    f32 magnitude = Math3D_Vec3fMagnitude(src);

    if (magnitude < 0.001f) {
        return false;
    }

    dst->x = src->x * (1.0f / magnitude);
    dst->y = src->y * (1.0f / magnitude);
    dst->z = src->z * (1.0f / magnitude);
    *norm = magnitude;
    *invNorm = 1.0f / magnitude;

    return true;
}

void ObjMine_Path_SpawnBomb(ObjMine* this, PlayState* play) {
    EnBom* bomb = (EnBom*)Actor_Spawn(&play->actorCtx, play, ACTOR_EN_BOM, this->actor.world.pos.x,
                                      this->actor.world.pos.y - 15.0f, this->actor.world.pos.z, 0, 0, 0, ENBOM_0);

    if (bomb != NULL) {
        bomb->timer = 0;
    }
}

void ObjMine_AirWater_SpawnBomb(ObjMine* this, PlayState* play) {
    f32 x = this->collider.elements[0].dim.worldSphere.center.x;
    f32 y = this->collider.elements[0].dim.worldSphere.center.y - 15.0f;
    f32 z = this->collider.elements[0].dim.worldSphere.center.z;

    EnBom* bomb = (EnBom*)Actor_Spawn(&play->actorCtx, play, ACTOR_EN_BOM, x, y, z, 0, 0, 0, ENBOM_0);

    if (bomb != NULL) {
        bomb->timer = 0;
    }
}

s32 ObjMine_AirWater_CheckOC(ObjMine* this) {
    if (this->collider.base.ocFlags2 & OC2_HIT_PLAYER) {
        return true;
    }

    if ((this->collider.base.ocFlags1 & OC1_HIT)) {
        Actor* hitActor = this->collider.base.oc;

        if ((hitActor->id == ACTOR_OBJ_MINE) && (hitActor->room == this->actor.room)) {
            return true;
        }
    }

    return false;
}

void ObjMine_Air_CheckAC(ObjMine* this, s16* hitAngle, s16* hitTorque) {
    s32 pad[2];
    Vec3s* centerPos3s = &this->collider.elements[0].dim.worldSphere.center;
    Vec3f centerPos;
    s16 yawToAttack;
    Actor* attackActor = this->collider.base.ac;

    Math_Vec3s_ToVec3f(&centerPos, centerPos3s);
    yawToAttack = Math_Vec3f_Yaw(&attackActor->world.pos, &centerPos);

    // dmgFlag check is (DMG_DEKU_BUBBLE | DMG_FIRE_ARROW | DMG_ICE_ARROW | DMG_FIRE_ARROW | DMG_NORMAL_ARROW)
    if (this->collider.elements[0].info.acHitInfo->toucher.dmgFlags & 0x13820) {
        *hitAngle = attackActor->shape.rot.y;
        *hitTorque = attackActor->shape.rot.y - yawToAttack;
    } else {
        Vec3f hitPos;
        Vec3s* hitPos3s = &this->collider.elements[0].info.bumper.hitPos;

        Math_Vec3s_ToVec3f(&hitPos, hitPos3s);
        *hitAngle = Actor_YawBetweenActors(attackActor, &this->actor);
        *hitTorque = Math_Vec3f_Yaw(&attackActor->world.pos, &hitPos) - yawToAttack;
    }
}

void ObjMine_Water_CheckAC(ObjMine* this, Vec3f* knockbackDir) {
    Actor* attackActor = this->collider.base.ac;

    // dmgFlag check is (DMG_DEKU_BUBBLE | DMG_LIGHT_ARROW | DMG_ICE_ARROW | DMG_FIRE_ARROW | DMG_NORMAL_ARROW)
    if ((this->collider.elements[0].info.acHitInfo->toucher.dmgFlags & 0x13820)) {
        Matrix_Push();
        Matrix_RotateYS(attackActor->shape.rot.y, MTXMODE_NEW);
        Matrix_RotateXS(attackActor->shape.rot.x, MTXMODE_APPLY);
        Matrix_MultVecZ(1.0f, knockbackDir);
        Matrix_Pop();
    } else {
        Vec3f posDiff;
        Sphere16* sphere = &this->collider.elements[0].dim.worldSphere;

        posDiff.x = sphere->center.x - attackActor->world.pos.x;
        posDiff.y = sphere->center.y - attackActor->world.pos.y;
        posDiff.z = sphere->center.z - attackActor->world.pos.z;

        if (!ObjMine_GetUnitVec3f(&posDiff, knockbackDir)) {
            Math_Vec3f_Copy(knockbackDir, &sStandardBasis.y);
        }
    }
}

void ObjMine_AirWater_Noop(ObjMine* this) {
}

void ObjMine_ReplaceTranslation(Vec3f* translation) {
    MtxF* matrix = Matrix_GetCurrent();

    matrix->mf[3][0] = translation->x;
    matrix->mf[3][1] = translation->y;
    matrix->mf[3][2] = translation->z;
}

void ObjMine_ReplaceRotation(ObjMineMtxF3* rotation) {
    MtxF* matrix = Matrix_GetCurrent();

    matrix->mf[0][0] = rotation->x.x;
    matrix->mf[0][1] = rotation->x.y;
    matrix->mf[0][2] = rotation->x.z;
    matrix->mf[0][3] = 0.0f;

    matrix->mf[1][0] = rotation->y.x;
    matrix->mf[1][1] = rotation->y.y;
    matrix->mf[1][2] = rotation->y.z;
    matrix->mf[1][3] = 0.0f;

    matrix->mf[2][0] = rotation->z.x;
    matrix->mf[2][1] = rotation->z.y;
    matrix->mf[2][2] = rotation->z.z;
    matrix->mf[2][3] = 0.0f;

    matrix->mf[3][0] = 0.0f;
    matrix->mf[3][1] = 0.0f;
    matrix->mf[3][2] = 0.0f;
    matrix->mf[3][3] = 1.0f;
}

s32 ObjMine_StepUntilParallel(Vec3f* value, Vec3f* target, f32 angleStep) {
    Vec3f perpVec;
    Vec3f prevValue;
    Vec3f perpNormal;
    f32 cosAngle = Math3D_Parallel(value, target);

    if (cos_rad(angleStep) <= cosAngle) {
        Math_Vec3f_Copy(value, target);
        return true;
    }

    Matrix_Push();
    Math_Vec3f_Copy(&prevValue, value);
    Math3D_CrossProduct(value, target, &perpVec);
    if (ObjMine_GetUnitVec3f(&perpVec, &perpNormal)) {
        Matrix_RotateAxisS(RADF_TO_BINANG(angleStep), &perpNormal, MTXMODE_NEW);
        Matrix_MultVec3f(&prevValue, value);
    } else {
        Matrix_RotateXFNew(angleStep);
        Matrix_MultVec3f(&prevValue, value);
    }

    Matrix_Pop();
    return false;
}

void ObjMine_UpdateCollider(ObjMine* this) {
    this->collider.elements[0].dim.worldSphere.center.x = this->actor.world.pos.x;
    this->collider.elements[0].dim.worldSphere.center.y = this->actor.world.pos.y;
    this->collider.elements[0].dim.worldSphere.center.z = this->actor.world.pos.z;
}

void ObjMine_Air_InitChain(ObjMine* this, s32 linkCount) {
    f32 linkCountF = linkCount;
    ObjMineAirChain* airChain = &this->chain.air;
    ObjMineAirLink* airLink;
    s32 i;
    f32 wallCheckRadius = this->actor.home.rot.z * 5.0f;

    airChain->basis.x.x = 1.0f;
    airChain->basis.y.y = 1.0f;
    airChain->basis.z.z = 1.0f;
    airChain->translation.y = 1.0f;

    if (linkCount > 0) {
        airChain->restore = -sqrtf(0.001984f / linkCountF); // approx 1/504 = 1/8 * 1/63
        airChain->drag =  0.95f + (0.00031746097f * linkCountF); // approx 1/3150 = 1/50 * 1/63
    }

    airChain->wobble = 0.0002f;

    for (i = 0, airLink = airChain->links; i < linkCount; i++, airLink++) {
        airLink->twist = 0x4000;
    }

    if (wallCheckRadius < 0.0f) {
        airChain->wallCheckDist = -1.0f;
    } else if (wallCheckRadius <= 20.0f + 1.0f) {
        airChain->wallCheckDist = 0.0f;
    } else {
        airChain->wallCheckDist = SQ(wallCheckRadius - 20.0f);
    }
}

void ObjMine_Air_SetCollider(ObjMine* this, s32 linkCount) {
    Matrix_Translate(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, MTXMODE_NEW);
    Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
    Collider_UpdateSpheres(0, &this->collider);
}

void ObjMine_Air_SetBasis(ObjMine* this) {
    ObjMineAirChain* airChain = &this->chain.air;
    Vec3f tempVec;

    tempVec.x = -airChain->xDiff;
    tempVec.y = 1.0f;
    tempVec.z = -airChain->zDiff;

    ObjMine_GetUnitVec3f(&tempVec, &airChain->basis.y);
    Math3D_CrossProduct(&sStandardBasis.x, &airChain->basis.y, &tempVec);
    ObjMine_GetUnitVec3f(&tempVec, &airChain->basis.z);
    Math3D_CrossProduct(&airChain->basis.y, &airChain->basis.z, &tempVec);
    ObjMine_GetUnitVec3f(&tempVec, &airChain->basis.x);
}

void ObjMine_Air_SetWorld(ObjMine* this) {
    s32 linkCount = OBJMINE_GET_LINK_COUNT(&this->actor);
    f32 chainLength = 10.0f + (linkCount * 12.0f);

    this->actor.world.pos.x = (this->chain.air.basis.y.x * -chainLength) + this->actor.home.pos.x;
    this->actor.world.pos.y = (this->chain.air.basis.y.y * -chainLength) + this->actor.home.pos.y;
    this->actor.world.pos.z = (this->chain.air.basis.y.z * -chainLength) + this->actor.home.pos.z;
}

void ObjMine_Air_SetChain3034(ObjMine* this) {
    s32 linkCount = OBJMINE_GET_LINK_COUNT(&this->actor);
    f32 invLength = 1.0f / (10.0f + (linkCount * 12.0f));
    f32 dx = this->actor.world.pos.x - this->actor.home.pos.x;
    f32 dz = this->actor.world.pos.z - this->actor.home.pos.z;

    this->chain.air.xDiff = dx * invLength;
    this->chain.air.zDiff = dz * invLength;
}

void ObjMine_Water_InitChain(ObjMine* this, s32 linkCount) {
    ObjMineWaterChain* waterChain = &this->chain.water;
    ObjMineWaterLink* waterLink;
    s32 i;
    f32 wallCheckRadius = this->actor.home.rot.z * 5.0f;
    f32 linkY;
    f32 wobbleVel;

    waterChain->drag = 0.9f;
    waterChain->wobble = 0.003f;

    waterChain->wobblePhaseVel = RANDU_BITS(13);
    waterChain->restoreX = -0.0002f;
    waterChain->restoreY = -0.0002f;

    wobbleVel = waterChain->wobble * 6.0f;
    linkY = this->actor.home.pos.y;

    for (i = 0, waterLink = waterChain->links; i < linkCount; i++, waterLink++) {
        linkY += 12.0f;
        waterLink->basis.x.x = 1.0f;
        waterLink->basis.y.y = 1.0f;
        waterLink->basis.z.z = 1.0f;
        waterLink->pos.x = this->actor.home.pos.x;
        waterLink->pos.y = linkY;
        waterLink->pos.z = this->actor.home.pos.z;
        waterLink->vel.x = (Rand_ZeroOne() - 0.5f) * wobbleVel;
        waterLink->vel.y = (Rand_ZeroOne() - 0.5f) * wobbleVel;
        waterLink->vel.z = (Rand_ZeroOne() - 0.5f) * wobbleVel;
    }
    waterChain->maxY = linkY;
    
    waterChain->restY = waterChain->maxY * 0.97f;
    linkY -= 18.0f;

    if (waterChain->restY < linkY) {
        waterChain->restY = linkY;
    }

    if (wallCheckRadius < 0.0f) {
        waterChain->wallCheckDist = -1.0f;
    } else if (wallCheckRadius <= 36.0f + 1.0f) {
        waterChain->wallCheckDist = 0.0f;
    } else {
        waterChain->wallCheckDist = SQ(wallCheckRadius - 36.0f);
    }
}

void ObjMine_Water_InitCollider(ObjMine* this, s32 linkCount) {
    Matrix_Translate(this->actor.home.pos.x, this->actor.home.pos.y + (linkCount * 12.0f) + 10.0f,
                             this->actor.home.pos.z, MTXMODE_NEW);
    Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
    Collider_UpdateSpheres(0, &this->collider);
}

void ObjMine_Water_SetWorld(ObjMine* this) {
    s32 pad;
    s32 linkCount = OBJMINE_GET_LINK_COUNT(&this->actor);
    ObjMineWaterChain* waterChain = &this->chain.water;
    
    if (linkCount == 0) {
        this->actor.world.pos.y = this->actor.home.pos.y + 12.0f + 10.0f;
    } else {
        ObjMineWaterLink* lastLink = &waterChain->links[linkCount - 1];
        Vec3f mineOffset;

        Math_Vec3f_ScaleAndStore(&lastLink->basis.y, 10.0f, &mineOffset);
        Math_Vec3f_Sum(&lastLink->pos, &mineOffset, &this->actor.world.pos);
    }
}

void ObjMine_Water_WallCheck(ObjMine* this, PlayState* play) {
    s32 pad;
    ObjMineWaterChain* waterChain = &this->chain.water;
    
    waterChain->touchWall = false;
    if (waterChain->wallCheckDist > -1e-6f) {
        if (waterChain->wallCheckDist <= Math3D_XZDistanceSquared(this->actor.home.pos.x, this->actor.home.pos.z,
                                                        this->actor.world.pos.x, this->actor.world.pos.z)) {
            Vec3f centerPos;
            Vec3f offsetPos;
            Vec3f dummyResult;
            Vec3f xzDistFromHome;
            Vec3f xzDirFromHome;
            CollisionPoly* dummyPoly;
            s32 dummyBgId;
            f32 dummyNorm;
            f32 dummyInvNorm;

            xzDistFromHome.x = this->actor.world.pos.x - this->actor.home.pos.x;
            xzDistFromHome.y = 0.0f;
            xzDistFromHome.z = this->actor.world.pos.z - this->actor.home.pos.z;

            if (ObjMine_GetUnitVec3fNorm(&xzDistFromHome, &xzDirFromHome, &dummyNorm, &dummyInvNorm)) {

                offsetPos.x = this->actor.world.pos.x + (xzDirFromHome.x * 36.0f);
                offsetPos.y = this->actor.world.pos.y;
                offsetPos.z = this->actor.world.pos.z + (xzDirFromHome.z * 36.0f);

                centerPos.x = this->actor.home.pos.x;
                centerPos.y = this->actor.world.pos.y;
                centerPos.z = this->actor.home.pos.z;

                if (BgCheck_EntityLineTest1(&play->colCtx, &centerPos, &offsetPos, &dummyResult, &dummyPoly, true, false, false, true, &dummyBgId)) {
                    waterChain->touchWall = true;
                    waterChain->wallEjectX = xzDirFromHome.x * -0.2f;
                    waterChain->wallEjectZ = xzDirFromHome.z * -0.2f;
                }
            }
        }
    }
}

#if 0
// Probably equivalent, but nightmare loop unrolls.
void ObjMine_Water_ApplyForces(ObjMine *this) {
    static Vec3f sLinkAccel[0x40]; 
    ObjMineWaterChain *waterChain = &this->chain.water;
    ObjMineWaterLink *waterLink;
    s32 i;
    s16 wobblePhase;
    s32 linkCount = OBJMINE_GET_LINK_COUNT(&this->actor);
    f32 inverseCount = 1.0f / (f32) linkCount;
    f32 restoreY = (waterChain->links[linkCount - 1].pos.y - waterChain->restY) * waterChain->restoreY;
    Vec3f tension;
    f32 scaledKnockback;

    for(i = 0, waterLink = waterChain->links, wobblePhase = 0; i < linkCount; i++, waterLink++, wobblePhase += waterChain->wobblePhaseVel) {
        Math_Vec3f_Copy(&sLinkAccel[i], &waterLink->accel);
        if (waterLink->pos.y <= this->actor.home.pos.y) {
            waterLink->accel.y = waterChain->restoreY * -96.0f;
        } else if (restoreY > 0.0f) {
            waterLink->accel.y = (i + 1) * inverseCount * (restoreY / 0.3f);
        } else {
            waterLink->accel.y = restoreY;
        }
        waterLink->accel.x = (waterLink->pos.x - this->actor.home.pos.x) * waterChain->restoreX;
        waterLink->accel.z = (waterLink->pos.z - this->actor.home.pos.z) * waterChain->restoreX;
        waterLink->accel.x += waterChain->wobbleXZ * Math_SinS(wobblePhase);
        waterLink->accel.y += waterChain->wobbleY;
        waterLink->accel.z += waterChain->wobbleXZ * Math_CosS(wobblePhase);
    }
    if (waterChain->knockback > 0.0001f) {
        for(i = 0, waterLink = waterChain->links; i < linkCount; i++, waterLink++) {
            scaledKnockback = SQ((linkCount - i) * inverseCount);
            
            waterLink->accel.x += waterChain->knockbackDir.x * scaledKnockback;
            waterLink->accel.y += waterChain->knockbackDir.y * scaledKnockback;
            waterLink->accel.z += waterChain->knockbackDir.z * scaledKnockback;
        }
    }
    if (waterChain->touchWall) {
        for(i = 0, waterLink = waterChain->links; i < linkCount; i++, waterLink++) {
            waterLink->accel.x += waterChain->wallEjectX;
            waterLink->accel.z += waterChain->wallEjectZ;
        }
    }

    for(i = 0, waterLink = waterChain->links; i < linkCount; i++, waterLink++) {             
        Math_Vec3f_Copy(&tension, &gZeroVec3f);
        if(i - 2 >= 0) {
            tension.x += sLinkAccel[i - 2].x * 0.075f;
            tension.y += sLinkAccel[i - 2].y * 0.075f;
            tension.z += sLinkAccel[i - 2].z * 0.075f;
        }
        if(i - 1 >= 0) {
            tension.x += sLinkAccel[i - 1].x * 0.15f;
            tension.y += sLinkAccel[i - 1].y * 0.15f;
            tension.z += sLinkAccel[i - 1].z * 0.15f;
        }
            tension.x += sLinkAccel[i].x * 0.3f;
            tension.y += sLinkAccel[i].y * 0.3f;
            tension.z += sLinkAccel[i].z * 0.3f;
        if(i + 1 < linkCount) {
            tension.x += sLinkAccel[i + 1].x * 0.15f;
            tension.y += sLinkAccel[i + 1].y * 0.15f;
            tension.z += sLinkAccel[i + 1].z * 0.15f;
        }
        if(i + 2 < linkCount) {
            tension.x += sLinkAccel[i + 2].x * 0.075f;
            tension.y += sLinkAccel[i + 2].y * 0.075f;
            tension.z += sLinkAccel[i + 2].z * 0.075f;
        }
        waterLink->accel.x += tension.x;
        waterLink->accel.y += tension.y;
        waterLink->accel.z += tension.z;
    }

}
#else
Vec3f D_80A849D0[0x40];
void ObjMine_Water_ApplyForces(ObjMine* this);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/ObjMine_Water_ApplyForces.s")
#endif

void ObjMine_Water_UpdateLinks(ObjMine* this) {
    s32 pad;
    ObjMineMtxF3 newBasis;
    s32 linkCount = OBJMINE_GET_LINK_COUNT(&this->actor);
    ObjMineWaterChain* waterChain = &this->chain.water;
    ObjMineWaterLink* waterLink;
    s32 i;
    Vec3f* lastBasisX;
    Vec3f tempVec;
    Vec3f diffDir;
    Vec3f unusedLinkPos;
    Vec3f lastLinkPos;
    s32 changeBasis;
    f32 diffNorm;
    f32 dummyInvNorm;
    Vec3f* tempBasisX;

    lastLinkPos.x = this->actor.home.pos.x;
    lastLinkPos.y = this->actor.home.pos.y + 6.0f;
    lastLinkPos.z = this->actor.home.pos.z;

    for (i = 0, lastBasisX = NULL, waterLink = waterChain->links; i < linkCount; i++, lastBasisX = &waterLink->basis.x, waterLink++) {
        changeBasis = false;

        waterLink->vel.x += waterLink->accel.x;
        waterLink->vel.y += waterLink->accel.y;
        waterLink->vel.z += waterLink->accel.z;

        Math_Vec3f_Scale(&waterLink->vel, waterChain->drag);
        Math_Vec3f_Copy(&unusedLinkPos, &waterLink->pos);

        waterLink->pos.x += waterLink->vel.x;
        waterLink->pos.y += waterLink->vel.y;
        waterLink->pos.z += waterLink->vel.z;

        if ((waterLink->pos.y <= this->actor.home.pos.y) && (waterLink->vel.y < 0.0f)) {
            waterLink->vel.y *= 0.1f;
        }

        Math_Vec3f_Diff(&waterLink->pos, &lastLinkPos, &tempVec);

        if (ObjMine_GetUnitVec3fNorm(&tempVec, &diffDir, &diffNorm, &dummyInvNorm) && (diffNorm > 4.0f)) {
            Math_Vec3f_Copy(&newBasis.y, &waterLink->basis.y);
            ObjMine_StepUntilParallel(&newBasis.y, &diffDir, M_PI / 30);
            tempBasisX = (lastBasisX == NULL) ? &sStandardBasis.x : lastBasisX;

            Math3D_CrossProduct(tempBasisX, &newBasis.y, &tempVec);

            if (ObjMine_GetUnitVec3f(&tempVec, &newBasis.z)) {
                Math3D_CrossProduct(&newBasis.y, &newBasis.z, &tempVec);
                if (ObjMine_GetUnitVec3f(&tempVec, &newBasis.x)) {
                    changeBasis = true;
                }
            }
        }

        if (changeBasis) {
            Math_Vec3f_Copy(&waterLink->basis.x, &newBasis.x);
            Math_Vec3f_Copy(&waterLink->basis.y, &newBasis.y);
            Math_Vec3f_Copy(&waterLink->basis.z, &newBasis.z);
        } else {
            diffNorm = 4.0f;
        }

        if (diffNorm >= 6.0f) {
            waterLink->pos.x = lastLinkPos.x + (waterLink->basis.y.x * 6.0f);
            waterLink->pos.y = lastLinkPos.y + (waterLink->basis.y.y * 6.0f);
            waterLink->pos.z = lastLinkPos.z + (waterLink->basis.y.z * 6.0f);
        } else {
            waterLink->pos.x = lastLinkPos.x + (waterLink->basis.y.x * diffNorm);
            waterLink->pos.y = lastLinkPos.y + (waterLink->basis.y.y * diffNorm);
            waterLink->pos.z = lastLinkPos.z + (waterLink->basis.y.z * diffNorm);
        }

        lastLinkPos.x = waterLink->pos.x + (waterLink->basis.y.x * 6.0f);
        lastLinkPos.y = waterLink->pos.y + (waterLink->basis.y.y * 6.0f);
        lastLinkPos.z = waterLink->pos.z + (waterLink->basis.y.z * 6.0f);
    }
}

void ObjMine_Water_UpdateChain(ObjMine* this, PlayState* play) {
    ObjMine_Water_WallCheck(this, play);
    ObjMine_Water_ApplyForces(this); // ObjMine_Water_ApplyForces
    ObjMine_Water_UpdateLinks(this);
}

void ObjMine_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    ObjMine* this = THIS;
    s32 pathIndex = OBJMINE_GET_PATH(&this->actor);
    Path* path;
    s32 dummyBgId;
    s32 type = OBJMINE_GET_TYPE(&this->actor);

    Actor_ProcessInitChain(&this->actor, sInitChain);

    this->actor.shape.rot.z = 0;
    this->actor.world.rot.z = 0;
    
    Collider_InitJntSph(play, &this->collider);
    Collider_SetJntSph(play, &this->collider, &this->actor, &sJntSphInit, this->colliderElements);

    if (type == OBJMINE_TYPE_PATH) {
        ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 45.0f);
        this->actor.shape.shadowAlpha = 140;
        this->pathSpeed = sPathSpeeds[OBJMINE_GET_PATH_SPEED(&this->actor)];
        if (pathIndex == 0xFF) {
            ObjMine_Path_SetupStationary(this);
        } else {
            path = &play->setupPathList[pathIndex];

            this->waypointIndex = 0;
            this->waypointCount = path->count - 1;
            this->waypoints = (Vec3s*)Lib_SegmentedToVirtual(path->points);

            ObjMine_Path_MoveToWaypoint(this, this->waypointIndex);
            ObjMine_Path_SetupMove(this);
        }
        Matrix_SetTranslateRotateYXZ(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z,
                                              &this->actor.shape.rot);
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
        Collider_UpdateSpheres(0, &this->collider);
        this->actor.floorHeight = BgCheck_EntityRaycastFloor5(&play->colCtx, &this->actor.floorPoly, &dummyBgId,
                                                              &this->actor, &this->actor.world.pos);
    } else {
        s32 linkCount = OBJMINE_GET_LINK_COUNT(&this->actor);

        this->actor.update = ObjMine_AirWater_Update;
        this->actor.uncullZoneScale = 150.0f + (linkCount * 21.0f);
        this->actor.uncullZoneDownward = 150.0f + (linkCount * 21.0f);
        ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 45.0f);
        this->actor.shape.shadowAlpha = 140;

        if (type == OBJMINE_TYPE_AIR) {
            this->actor.draw = ObjMine_Air_Draw;
            ObjMine_Air_InitChain(this, linkCount);
            this->actor.world.pos.y = -10.0f - (linkCount * 12.0f) + this->actor.home.pos.y;
            ObjMine_Air_SetCollider(this, linkCount);
            func_800B4AEC(play, &this->actor, 0.0f);
            if (linkCount == 0) {
                ObjMine_Air_SetupStationary(this);
            } else {
                ObjMine_Air_SetupChained(this);
            }
        } else {
            this->actor.draw = ObjMine_Water_Draw;
            ObjMine_Water_InitChain(this, linkCount);
            this->actor.world.pos.y =  10.0f + (linkCount * 12.0f) + this->actor.home.pos.y;
            ObjMine_Water_InitCollider(this, linkCount);
            if (linkCount == 0) {
                ObjMine_Water_SetupStationary(this);
            } else {
                ObjMine_Water_SetupChained(this);
            }
        }
    }
}

void ObjMine_Destroy(Actor* thisx, PlayState* play) {
    ObjMine* this = THIS;

    Collider_DestroyJntSph(play, &this->collider);
}

void ObjMine_Path_SetupStationary(ObjMine* this) {
    this->actionFunc = ObjMine_Path_Stationary;
}

void ObjMine_Path_Stationary(ObjMine* this, PlayState* play) {
}

void ObjMine_Path_SetupMove(ObjMine* this) {
    this->actor.flags |= ACTOR_FLAG_10;
    this->actionFunc = ObjMine_Path_Move;
}

void ObjMine_Path_Move(ObjMine* this, PlayState* play) {
    Actor* thisx = &this->actor; // pos and velocity need this, though it can replace all `this->actor`s and match
    Vec3f nextWaypoint;
    f32 speed;
    f32 step;
    f32 target;
    s32 dummyBgVec;    

    Math_Vec3s_ToVec3f(&nextWaypoint, &this->waypoints[this->waypointIndex + 1]);
    Math_Vec3f_Diff(&nextWaypoint, &thisx->world.pos, &thisx->velocity);
    speed = Math3D_Vec3fMagnitude(&thisx->velocity);
    if ((speed < (this->pathSpeed * 8.0f)) && (this->pathSpeed > 2.0f)) {
        target = 2.0f + ((this->pathSpeed - 2.0f) * 0.1f);
        step = this->pathSpeed * 0.03f;
    } else {
        target = this->pathSpeed;
        step = this->pathSpeed * 0.16f;
    }
    Math_StepToF(&this->actor.speedXZ, target, step);
    if ((this->actor.speedXZ + 0.05f) < speed) {
        Math_Vec3f_Scale(&thisx->velocity, this->actor.speedXZ / speed);
        this->actor.world.pos.x += thisx->velocity.x;
        this->actor.world.pos.y += thisx->velocity.y;
        this->actor.world.pos.z += thisx->velocity.z;
    } else {
        this->actor.speedXZ *= 0.4f;
        this->waypointIndex++;
        if (this->waypointIndex >= this->waypointCount) {
            this->waypointIndex = 0;
        }
        ObjMine_Path_MoveToWaypoint(this, this->waypointIndex);
    }
    this->actor.floorHeight = BgCheck_EntityRaycastFloor5(&play->colCtx, &this->actor.floorPoly, &dummyBgVec, &this->actor, &thisx->world.pos);
    if (this->actor.flags & ACTOR_FLAG_40) {
        Vec3f rotAxis;
        Vec3f yhatCrossV;
        MtxF rotMtxF;

        Math3D_CrossProduct(&sStandardBasis.y, &thisx->velocity, &yhatCrossV);
        if (ObjMine_GetUnitVec3f(&yhatCrossV, &rotAxis)) {
            Matrix_RotateAxisF(this->actor.speedXZ / 32.0f, &rotAxis, MTXMODE_NEW);
            Matrix_RotateYS(this->actor.shape.rot.y, MTXMODE_APPLY);
            Matrix_RotateXS(this->actor.shape.rot.x, MTXMODE_APPLY);
            Matrix_RotateZS(this->actor.shape.rot.z, MTXMODE_APPLY);
            Matrix_Get(&rotMtxF);
            Matrix_MtxFToYXZRot(&rotMtxF, &this->actor.shape.rot, false);
        }
    }
}

void ObjMine_SetupExplode(ObjMine* this) {
    this->actor.flags |= ACTOR_FLAG_10;
    this->actor.draw = ObjMine_DrawExplosion;
    this->actor.shape.shadowDraw = NULL;
    this->actor.scale.x = 0.02f;
    this->actor.scale.y = 0.02f;
    this->actor.scale.z = 0.02f;
    this->actionFunc = ObjMine_Explode;
}

void ObjMine_Explode(ObjMine* this, PlayState* play) {
    this->actor.scale.x *= 1.8f;
    if (this->actor.scale.x > 30.0f * 0.001f * CUBE(1.8f)) {
        Actor_Kill(&this->actor);
    } else {
        this->actor.scale.y = this->actor.scale.x;
        this->actor.scale.z = this->actor.scale.x;
    }
}

void ObjMine_Air_SetupChained(ObjMine* this) {
    this->actionFunc = ObjMine_Air_Chained;
}

void ObjMine_Air_Chained(ObjMine* this, PlayState* play) {
    s32 pad;
    s32 linkCount = OBJMINE_GET_LINK_COUNT(&this->actor);
    ObjMineAirChain* airChain = &this->chain.air;
    ObjMineAirLink* airLink;
    s32 i;
    f32 xAccel;
    f32 zAccel;
    f32 torque;
    s16 twistDiff;

    Math_Vec3f_Copy(&airChain->translation, &airChain->basis.y);
    if (ObjMine_AirWater_CheckOC(this)) {
        ObjMine_AirWater_SpawnBomb(this, play);
        ObjMine_AirWater_Noop(this);
        ObjMine_SetupExplode(this);
        return;
    }

    if (this->collider.base.acFlags & AC_HIT) { // initial knockback calc
        s16 torqueAngle;
        f32 torque;
        f32 torqueDiff;
        
        this->collider.base.acFlags &= ~AC_HIT;
        airChain->knockback = 0.04f;
        ObjMine_Air_CheckAC(this, &airChain->knockbackAngle, &torqueAngle);
        torque = Math_SinS(torqueAngle) * 150.0f;
        torqueDiff = -(torque / linkCount);

        for (i = 0, airLink = airChain->links; i < linkCount; i++, airLink++) {
            airLink->spin += (s16)torque;
            airLink->spin = CLAMP(airLink->spin, -800, 800);
            torque -= torqueDiff;
        }
    }

    if (airChain->knockback > 0.0001f) { // residual knockback calc
        xAccel = Math_SinS(airChain->knockbackAngle) * airChain->knockback;
        zAccel = Math_CosS(airChain->knockbackAngle) * airChain->knockback;
        airChain->xVel += xAccel;
        airChain->zVel += zAccel;
        Math_StepToF(&airChain->knockback, 0.0f, 0.02f);
    }

    if (RANDU_BITS(5) == 0) { // wobble
        airChain->wobbleSize = Rand_ZeroOne() * airChain->wobble;
        airChain->wobblePhase = RANDU_BITS(16);
    }

    xAccel = Math_SinS(airChain->wobblePhase) * airChain->wobbleSize;
    zAccel = Math_CosS(airChain->wobblePhase) * airChain->wobbleSize;
    airChain->xVel += xAccel;
    airChain->zVel += zAccel;

    airChain->xVel += airChain->xDiff * airChain->restore;
    airChain->zVel += airChain->zDiff * airChain->restore;

    airChain->xVel *= airChain->drag;
    airChain->zVel *= airChain->drag;

    airChain->xDiff += airChain->xVel;
    airChain->zDiff += airChain->zVel;

    airChain->xDiff = CLAMP(airChain->xDiff, -5.0f, 5.0f);
    airChain->zDiff = CLAMP(airChain->zDiff, -5.0f, 5.0f);

    ObjMine_Air_SetBasis(this);
    ObjMine_Air_SetWorld(this);

    if (airChain->wallCheckDist > -1e-6f) {
        // Vec3f* world = &this->actor.world.pos;
        // Vec3f* home = &this->actor.home.pos;

        if (airChain->wallCheckDist <= Math3D_XZDistanceSquared(this->actor.world.pos.x, this->actor.world.pos.z, this->actor.home.pos.x, this->actor.home.pos.z)) {

            Actor_UpdateBgCheckInfo(play, &this->actor, 0.0f, 20.0f, 0.0f, 1);

            if ((this->actor.bgCheckFlags & 8) && (this->actor.wallPoly != NULL)) {
                Vec3f xzDir;
                Vec3f reflectedDir;
                Vec3f wallNormal;
                Vec3f xzVel;
                f32 xzSpeed;
                f32 dummyInvNorm;

                xzVel.x = airChain->xVel;
                xzVel.y = 0.0f;
                xzVel.z = airChain->zVel;

                if (ObjMine_GetUnitVec3fNorm(&xzVel, &xzDir, &xzSpeed, &dummyInvNorm)) {
                    wallNormal.x = COLPOLY_GET_NORMAL(this->actor.wallPoly->normal.x);
                    wallNormal.y = COLPOLY_GET_NORMAL(this->actor.wallPoly->normal.y);
                    wallNormal.z = COLPOLY_GET_NORMAL(this->actor.wallPoly->normal.z);

                    func_80179F64(&xzDir, &wallNormal, &reflectedDir);

                    xzSpeed /= 2.0f;
                    airChain->xVel = reflectedDir.x * xzSpeed;
                    airChain->zVel = reflectedDir.z * xzSpeed;
                } else {
                    airChain->xVel *= -0.1f;
                    airChain->zVel *= -0.1f;
                }
                ObjMine_Air_SetChain3034(this);
                ObjMine_Air_SetBasis(this);
                ObjMine_Air_SetWorld(this);
            }
        }
    }

    for (i = 0, airLink = airChain->links; i < linkCount; i++, airLink++) {
        twistDiff = airLink->twist - 0x4000;
        torque = airLink->spin + (twistDiff * -0.05f) + RAND_PLUSMINUS(15.0f);
        torque *= 0.995f;
        airLink->spin = torque;
        airLink->twist += airLink->spin;
    }

    func_800B4AEC(play, &this->actor, 0.0f);
    ObjMine_UpdateCollider(this);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.base);
}

void ObjMine_Air_SetupStationary(ObjMine* this) {
    this->actionFunc = ObjMine_Air_Stationary;
}

void ObjMine_Air_Stationary(ObjMine* this, PlayState* play) {
    if (ObjMine_AirWater_CheckOC(this)) {
        ObjMine_AirWater_SpawnBomb(this, play);
        ObjMine_AirWater_Noop(this);
        ObjMine_SetupExplode(this);
        return;
    }

    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.base);
}

void ObjMine_Water_SetupChained(ObjMine* this) {
    this->actionFunc = ObjMine_Water_Chained;
}

void ObjMine_Water_Chained(ObjMine* this, PlayState* play) {
    ObjMineWaterChain* waterChain = &this->chain.water;

    if (ObjMine_AirWater_CheckOC(this)) {
        ObjMine_AirWater_SpawnBomb(this, play);
        ObjMine_AirWater_Noop(this);
        ObjMine_SetupExplode(this);
        return;
    }

    if (this->collider.base.acFlags & AC_HIT) {
        this->collider.base.acFlags &= ~AC_HIT;
        ObjMine_Water_CheckAC(this, &waterChain->knockbackDir);
        waterChain->knockback = 7.0f;
        Math_Vec3f_Scale(&waterChain->knockbackDir, 7.0f);
    }

    if (waterChain->knockback > 0.0001f) {
        waterChain->knockback = Math_Vec3f_StepTo(&waterChain->knockbackDir, &gZeroVec3f, 2.8f);
    }

    waterChain->drag = 0.9f;
    waterChain->restoreX = -0.0002f;
    waterChain->restoreY = -0.0002f;
    waterChain->wobble = 0.003f;

    if (RANDU_BITS(5) == 0) {
        s16 randAngle = RANDU_BITS(16);

        waterChain->wobbleXZ = Math_SinS(randAngle) * 1.8f * waterChain->wobble;
        waterChain->wobbleY = Math_CosS(randAngle) * 0.2f * waterChain->wobble;
        waterChain->wobblePhaseVel = RANDU_BITS(13); 
    }

    ObjMine_Water_UpdateChain(this, play);
    ObjMine_Water_SetWorld(this);
    ObjMine_UpdateCollider(this);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.base);
}

void ObjMine_Water_SetupStationary(ObjMine* this) {
    this->actionFunc = ObjMine_Water_Stationary;
}

void ObjMine_Water_Stationary(ObjMine* this, PlayState* play) {
    if (ObjMine_AirWater_CheckOC(this)) {
        ObjMine_AirWater_SpawnBomb(this, play);
        ObjMine_AirWater_Noop(this);
        ObjMine_SetupExplode(this);
        return;
    }

    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.base);
    
}

void ObjMine_Path_Update(Actor* thisx, PlayState* play) {
    s32 pad;
    ObjMine* this = THIS;

    if ((this->collider.base.ocFlags2 & OC2_HIT_PLAYER) || (this->collider.base.acFlags & AC_HIT)) {
        ObjMine_Path_SpawnBomb(this, play);
        ObjMine_SetupExplode(this);
    }

    this->actionFunc(this, play);

    if (this->actor.update != NULL) {
        this->collider.base.ocFlags1 &= ~OC1_HIT;
        this->collider.base.acFlags &= ~AC_HIT;
        this->collider.base.ocFlags2 &= ~OC2_HIT_PLAYER;
        if ((this->actor.flags & ACTOR_FLAG_40) && (this->actionFunc != ObjMine_Explode)) {
            CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
            CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.base);
        }
    }
}

void ObjMine_AirWater_Update(Actor* thisx, PlayState* play) {
    ObjMine* this = THIS;

    this->actionFunc(this, play);
}

void ObjMine_Path_Draw(Actor* thisx, PlayState* play) {
    s32 pad;
    ObjMine* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    if (this->actionFunc == ObjMine_Path_Move) {
        Collider_UpdateSpheres(0, &this->collider);
    }

    func_800B8050(&this->actor, play, true);
    func_8012C28C(play->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetRenderMode(POLY_OPA_DISP++, G_RM_PASS, G_RM_AA_ZB_OPA_SURF2);
    gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 255);
    gSPDisplayList(POLY_OPA_DISP++, object_ny_DL_002068);
    gSPDisplayList(POLY_OPA_DISP++, object_ny_DL_002188);

    CLOSE_DISPS(play->state.gfxCtx);
}

void ObjMine_DrawExplosion(Actor* thisx, PlayState* play) {
    s32 pad; // This could be thisx recast or playstate recast.

    OPEN_DISPS(play->state.gfxCtx);

    func_800B8118(thisx, play, true);
    func_8012C2DC(play->state.gfxCtx);

    gDPSetRenderMode(POLY_XLU_DISP++, G_RM_PASS, G_RM_AA_ZB_XLU_SURF2);
    gDPSetEnvColor(POLY_XLU_DISP++, 0, 0, 0, 75);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, object_ny_DL_002068);

    CLOSE_DISPS(play->state.gfxCtx);
}

void ObjMine_Air_Draw(Actor* thisx, PlayState* play) {
    s32 pad;
    ObjMine* this = THIS;
    s32 linkCount = OBJMINE_GET_LINK_COUNT(&this->actor);
    ObjMineAirChain* airChain = &this->chain.air;
    ObjMineAirLink* airLink;
    s32 i;
    Vec3f linkPos;
    Vec3f linkOffset;
    Gfx* gfx;

    func_800B8050(&this->actor, play, true);

    OPEN_DISPS(play->state.gfxCtx);
    gfx = POLY_OPA_DISP;

    gSPDisplayList(gfx++, &sSetupDL[6 * 25]);
    gSPMatrix(gfx++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfx++, object_ny_DL_000030);

    ObjMine_ReplaceRotation(&airChain->basis);
    Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
    if (linkCount != 0) {
        Math_Vec3f_ScaleAndStore(&airChain->basis.y, -6.0f, &linkOffset);
        linkPos.x = this->actor.home.pos.x - linkOffset.x;
        linkPos.y = this->actor.home.pos.y - 6.0f - linkOffset.y;
        linkPos.z = this->actor.home.pos.z - linkOffset.z;

        Math_Vec3f_ScaleAndStore(&airChain->basis.y, -12.0f, &linkOffset);
        for (i = 0, airLink = airChain->links; i < linkCount; i++, airLink++) {
            Matrix_RotateYS(airLink->twist, MTXMODE_APPLY);
            linkPos.x += linkOffset.x;
            linkPos.y += linkOffset.y;
            linkPos.z += linkOffset.z;
            ObjMine_ReplaceTranslation(&linkPos);

            gSPMatrix(gfx++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(gfx++, object_ny_DL_000030);
        }
    }

    Matrix_RotateXS(0x2000, MTXMODE_APPLY);
    ObjMine_ReplaceTranslation(&this->actor.world.pos);

    gSPMatrix(gfx++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPPipeSync(gfx++);
    gDPSetRenderMode(gfx++, G_RM_PASS, G_RM_AA_ZB_OPA_SURF2);
    gDPSetEnvColor(gfx++, 0, 0, 0, 255);
    gSPDisplayList(gfx++, object_ny_DL_002068);
    gSPDisplayList(gfx++, object_ny_DL_002188);

    POLY_OPA_DISP = gfx;

    CLOSE_DISPS(play->state.gfxCtx);
}

void ObjMine_Water_Draw(Actor* thisx, PlayState* play) {
    s32 pad;
    ObjMine* this = THIS;
    s32 linkCount = OBJMINE_GET_LINK_COUNT(&this->actor);
    ObjMineWaterChain* waterChain = &this->chain.water;
    ObjMineWaterLink* waterLink;
    s32 i;
    Gfx* gfx;

    func_800B8050(&this->actor, play, true);

    OPEN_DISPS(play->state.gfxCtx);
    gfx = POLY_OPA_DISP;

    gSPDisplayList(gfx++, &sSetupDL[6 * 25]);
    gSPMatrix(gfx++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfx++, object_ny_DL_000030);

    for (i = 0, waterLink = waterChain->links; i < linkCount; i++, waterLink++) {
        ObjMine_ReplaceRotation(&waterLink->basis);
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
        if ((i % 2) == 0) {
            Matrix_RotateYS(0x4000, MTXMODE_APPLY);
        }
        ObjMine_ReplaceTranslation(&waterLink->pos);

        gSPMatrix(gfx++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(gfx++, object_ny_DL_000030);
    }

    Matrix_RotateXS(0x2000, MTXMODE_APPLY);
    ObjMine_ReplaceTranslation(&this->actor.world.pos);

    gSPMatrix(gfx++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPPipeSync(gfx++);
    gDPSetRenderMode(gfx++, G_RM_PASS, G_RM_AA_ZB_OPA_SURF2);
    gDPSetEnvColor(gfx++, 0, 0, 0, 255);
    gSPDisplayList(gfx++, object_ny_DL_002068);
    gSPDisplayList(gfx++, object_ny_DL_002188);

    POLY_OPA_DISP = gfx;

    CLOSE_DISPS(play->state.gfxCtx);
}
