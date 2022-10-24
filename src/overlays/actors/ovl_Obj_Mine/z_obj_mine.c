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
    f32 temp_f0 = Math3D_Vec3fMagnitude(src);

    if (temp_f0 < 0.001f) {
        return false;
    }

    dst->x = src->x * (1.0f / temp_f0);
    dst->y = src->y * (1.0f / temp_f0);
    dst->z = src->z * (1.0f / temp_f0);
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

void ObjMine_Air_CheckAC(ObjMine* this, s16* arg1, s16* arg2) {
    s32 pad[2];
    Vec3s* centerPos3s = &this->collider.elements[0].dim.worldSphere.center;
    Vec3f centerPos;
    s16 sp3E;
    Actor* attackActor = this->collider.base.ac;

    Math_Vec3s_ToVec3f(&centerPos, centerPos3s);
    sp3E = Math_Vec3f_Yaw(&attackActor->world.pos, &centerPos);

    // dmgFlag check is (DMG_DEKU_BUBBLE | DMG_FIRE_ARROW | DMG_ICE_ARROW | DMG_FIRE_ARROW | DMG_NORMAL_ARROW)
    if (this->collider.elements[0].info.acHitInfo->toucher.dmgFlags & 0x13820) {
        *arg1 = attackActor->shape.rot.y;
        *arg2 = attackActor->shape.rot.y - sp3E;
    } else {
        Vec3f hitPos;
        Vec3s* hitPos3s = &this->collider.elements[0].info.bumper.hitPos;

        Math_Vec3s_ToVec3f(&hitPos, hitPos3s);
        *arg1 = Actor_YawBetweenActors(attackActor, &this->actor);
        *arg2 = Math_Vec3f_Yaw(&attackActor->world.pos, &hitPos) - sp3E;
    }
}

void ObjMine_Water_CheckAC(ObjMine* this, Vec3f* arg1) {
    Actor* attackActor = this->collider.base.ac;

    // dmgFlag check is (DMG_DEKU_BUBBLE | DMG_FIRE_ARROW | DMG_ICE_ARROW | DMG_FIRE_ARROW | DMG_NORMAL_ARROW)
    if ((this->collider.elements[0].info.acHitInfo->toucher.dmgFlags & 0x13820)) {
        Matrix_Push();
        Matrix_RotateYS(attackActor->shape.rot.y, MTXMODE_NEW);
        Matrix_RotateXS(attackActor->shape.rot.x, MTXMODE_APPLY);
        Matrix_MultVecZ(1.0f, arg1);
        Matrix_Pop();
    } else {
        Vec3f sp20;
        Sphere16* sphere = &this->collider.elements[0].dim.worldSphere;

        sp20.x = sphere->center.x - attackActor->world.pos.x;
        sp20.y = sphere->center.y - attackActor->world.pos.y;
        sp20.z = sphere->center.z - attackActor->world.pos.z;
        if (!ObjMine_GetUnitVec3f(&sp20, arg1)) {
            Math_Vec3f_Copy(arg1, &sStandardBasis.y);
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
    Vec3f sp3C;
    Vec3f sp30;
    Vec3f sp24;
    f32 sp20 = Math3D_Parallel(value, target);

    if (cos_rad(angleStep) <= sp20) {
        Math_Vec3f_Copy(value, target);
        return true;
    }

    Matrix_Push();
    Math_Vec3f_Copy(&sp30, value);
    Math3D_CrossProduct(value, target, &sp3C);
    if (ObjMine_GetUnitVec3f(&sp3C, &sp24)) {
        Matrix_RotateAxisS(RADF_TO_BINANG(angleStep), &sp24, MTXMODE_NEW);
        Matrix_MultVec3f(&sp30, value);
    } else {
        Matrix_RotateXFNew(angleStep);
        Matrix_MultVec3f(&sp30, value);
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
    f32 arg1f = linkCount;
    ObjMineAirChain* chain1 = &this->chain.air;
    ObjMineAirLink* link1;
    s32 i;
    f32 temp_f12 = this->actor.home.rot.z * 5.0f;

    chain1->basis.x.x = 1.0f;
    chain1->basis.y.y = 1.0f;
    chain1->basis.z.z = 1.0f;
    chain1->unk_24.y = 1.0f;

    if (linkCount > 0) {
        chain1->unk_40 = -sqrtf(0.001984f / arg1f); // approx 1/504 = 1/8 * 1/63
        chain1->unk_44 =  0.95f + (0.00031746097f * arg1f); // approx 1/3150 = 1/50 * 1/63
    }

    chain1->unk_58 = 0.0002f;

    for (i = 0, link1 = chain1->links; i < linkCount; i++, link1++) {
        link1->unk_00 = 0x4000;
    }

    if (temp_f12 < 0.0f) {
        chain1->unk_5C = -1.0f;
    } else if (temp_f12 <= 21.0f) {
        chain1->unk_5C = 0.0f;
    } else {
        chain1->unk_5C = SQ(temp_f12 - 20.0f);
    }
}

void ObjMine_Air_SetCollider(ObjMine* this, s32 linkCount) {
    Matrix_Translate(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, MTXMODE_NEW);
    Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
    Collider_UpdateSpheres(0, &this->collider);
}

void ObjMine_Air_SetBasis(ObjMine* this) {
    ObjMineAirChain* chain1 = &this->chain.air;
    Vec3f sp28;

    sp28.x = -chain1->unk_30;
    sp28.y = 1.0f;
    sp28.z = -chain1->unk_34;

    ObjMine_GetUnitVec3f(&sp28, &chain1->basis.y);
    Math3D_CrossProduct(&sStandardBasis.x, &chain1->basis.y, &sp28);
    ObjMine_GetUnitVec3f(&sp28, &chain1->basis.z);
    Math3D_CrossProduct(&chain1->basis.y, &chain1->basis.z, &sp28);
    ObjMine_GetUnitVec3f(&sp28, &chain1->basis.x);
}

void ObjMine_Air_SetWorld(ObjMine* this) {
    s32 linkCount = OBJMINE_GET_LINK_COUNT(&this->actor);
    f32 temp_f0 = 10.0f + (linkCount * 12.0f);

    this->actor.world.pos.x = (this->chain.air.basis.y.x * -temp_f0) + this->actor.home.pos.x;
    this->actor.world.pos.y = (this->chain.air.basis.y.y * -temp_f0) + this->actor.home.pos.y;
    this->actor.world.pos.z = (this->chain.air.basis.y.z * -temp_f0) + this->actor.home.pos.z;
}

void ObjMine_Air_SetChain3034(ObjMine* this) {
    s32 linkCount = OBJMINE_GET_LINK_COUNT(&this->actor);
    f32 temp_f0 = 1.0f / (10.0f + (linkCount * 12.0f));
    f32 dx = this->actor.world.pos.x - this->actor.home.pos.x;
    f32 dz = this->actor.world.pos.z - this->actor.home.pos.z;

    this->chain.air.unk_30 = dx * temp_f0;
    this->chain.air.unk_34 = dz * temp_f0;
}

void ObjMine_Water_InitChain(ObjMine* this, s32 linkCount) {
    ObjMineWaterChain* chain2 = &this->chain.water;
    ObjMineWaterLink* link2;
    s32 i;
    f32 sp58 = this->actor.home.rot.z * 5.0f;
    f32 temp_f24;
    f32 temp_f26;

    chain2->unk_00 = 0.9f;
    chain2->unk_1C = 0.003f;

    chain2->unk_20 = RANDU_BITS(13);
    chain2->unk_24 = -0.0002f;
    chain2->unk_30 = -0.0002f;

    temp_f26 = chain2->unk_1C * 6.0f;
    temp_f24 = this->actor.home.pos.y;

    for (i = 0, link2 = chain2->links; i < linkCount; i++, link2++) {
        temp_f24 += 12.0f;
        link2->basis.x.x = 1.0f;
        link2->basis.y.y = 1.0f;
        link2->basis.z.z = 1.0f;
        link2->unk_24.x = this->actor.home.pos.x;
        link2->unk_24.y = temp_f24;
        link2->unk_24.z = this->actor.home.pos.z;
        link2->unk_30.x = (Rand_ZeroOne() - 0.5f) * temp_f26;
        link2->unk_30.y = (Rand_ZeroOne() - 0.5f) * temp_f26;
        link2->unk_30.z = (Rand_ZeroOne() - 0.5f) * temp_f26;
    }

    chain2->unk_28 = temp_f24;
    chain2->unk_2C = temp_f24 * 0.97f;
    temp_f24 -= 18.0f;

    if (chain2->unk_2C < temp_f24) {
        chain2->unk_2C = temp_f24;
    }

    if (sp58 < 0.0f) {
        chain2->unk_34 = -1.0f;
    } else if (sp58 <= 37.0f) {
        chain2->unk_34 = 0.0f;
    } else {
        chain2->unk_34 = SQ(sp58 - 36.0f);
    }
}

void ObjMine_Water_SetCollider(ObjMine* this, s32 linkCount) {
    Matrix_Translate(this->actor.home.pos.x, this->actor.home.pos.y + (linkCount * 12.0f) + 10.0f,
                             this->actor.home.pos.z, MTXMODE_NEW);
    Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
    Collider_UpdateSpheres(0, &this->collider);
}

void ObjMine_Water_SetWorld(ObjMine* this) {
    s32 pad;
    s32 linkCount = OBJMINE_GET_LINK_COUNT(&this->actor);
    ObjMineWaterChain* chain2 = &this->chain.water;
    
    if (linkCount == 0) {
        this->actor.world.pos.y = this->actor.home.pos.y + 12.0f + 10.0f;
    } else {
        ObjMineWaterLink* link2 = &chain2->links[linkCount - 1];
        Vec3f sp1C;

        Math_Vec3f_ScaleAndStore(&link2->basis.y, 10.0f, &sp1C);
        Math_Vec3f_Sum(&link2->unk_24, &sp1C, &this->actor.world.pos);
    }
}

void func_80A81E7C(ObjMine* this, PlayState* play) {
    s32 pad;
    ObjMineWaterChain* chain2 = &this->chain.water;
    
    chain2->unk_40 = false;
    if ((-0.000001f < chain2->unk_34) && (chain2->unk_34 <= Math3D_XZDistanceSquared(this->actor.home.pos.x, this->actor.home.pos.z,
                                                        this->actor.world.pos.x, this->actor.world.pos.z))) {
        Vec3f sp7C;
        Vec3f sp70;
        Vec3f sp64;
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

            sp70.x = this->actor.world.pos.x + (xzDirFromHome.x * 36.0f);
            sp70.y = this->actor.world.pos.y;
            sp70.z = this->actor.world.pos.z + (xzDirFromHome.z * 36.0f);

            sp7C.x = this->actor.home.pos.x;
            sp7C.y = this->actor.world.pos.y;
            sp7C.z = this->actor.home.pos.z;

            if (BgCheck_EntityLineTest1(&play->colCtx, &sp7C, &sp70, &sp64, &dummyPoly, 1, 0, 0, 1, &dummyBgId)) {
                chain2->unk_40 = true;
                chain2->unk_38 = xzDirFromHome.x * -0.2f;
                chain2->unk_3C = xzDirFromHome.z * -0.2f;
            }
        }
    }
}

#ifdef NON_MATCHING
// Probably equivalent, but nightmare loop unrolls.
void func_80A81FFC(ObjMine *this) {
    static Vec3f D_80A849D0[0x40]; 
    ObjMineWaterChain *chain2 = &this->chain.water;
    ObjMineWaterLink *link2;
    s32 i;
    s16 var_s3;
    s32 linkCount = OBJMINE_GET_LINK_COUNT(&this->actor);
    f32 invLinkCount = 1.0f / (f32) linkCount;
    f32 temp_fs0 = (chain2->links[linkCount - 1].unk_24.y - chain2->unk_2C) * chain2->unk_30;
    Vec3f sp90;
    f32 temp_ft4;

    for(i = 0, link2 = chain2->links, var_s3 = 0; i < linkCount; i++, link2++, var_s3 += chain2->unk_20) {
        Math_Vec3f_Copy(&D_80A849D0[i], &link2->unk_3C);
        if (link2->unk_24.y <= this->actor.home.pos.y) {
            link2->unk_3C.y = chain2->unk_30 * -96.0f;
        } else if (temp_fs0 > 0.0f) {
            link2->unk_3C.y = (i + 1) * invLinkCount * (temp_fs0 / 0.3f);
        } else {
            link2->unk_3C.y = temp_fs0;
        }
        link2->unk_3C.x = (link2->unk_24.x - this->actor.home.pos.x) * chain2->unk_24;
        link2->unk_3C.z = (link2->unk_24.z - this->actor.home.pos.z) * chain2->unk_24;
        link2->unk_3C.x += chain2->unk_14 * Math_SinS(var_s3);
        link2->unk_3C.y += chain2->unk_18;
        link2->unk_3C.z += chain2->unk_14 * Math_CosS(var_s3);
    }
    if (chain2->unk_10 > 0.0001f) {
        for(i = 0, link2 = chain2->links; i < linkCount; i++, link2++) {
            temp_ft4 = SQ((linkCount - i) * invLinkCount);
            
            link2->unk_3C.x += chain2->unk_04.x * temp_ft4;
            link2->unk_3C.y += chain2->unk_04.y * temp_ft4;
            link2->unk_3C.z += chain2->unk_04.z * temp_ft4;
        }
    }
    if (chain2->unk_40) {
        for(i = 0, link2 = chain2->links; i < linkCount; i++, link2++) {
            link2->unk_3C.x += chain2->unk_38;
            link2->unk_3C.z += chain2->unk_3C;
        }
    }

    for(i = 0, link2 = chain2->links; i < linkCount; i++, link2++) {             
        Math_Vec3f_Copy(&sp90, &gZeroVec3f);
        if(i - 2 >= 0) {
            sp90.x += D_80A849D0[i - 2].x * 0.075f;
            sp90.y += D_80A849D0[i - 2].y * 0.075f;
            sp90.z += D_80A849D0[i - 2].z * 0.075f;
        }
        if(i - 1 >= 0) {
            sp90.x += D_80A849D0[i - 1].x * 0.15f;
            sp90.y += D_80A849D0[i - 1].y * 0.15f;
            sp90.z += D_80A849D0[i - 1].z * 0.15f;
        }
            sp90.x += D_80A849D0[i].x * 0.3f;
            sp90.y += D_80A849D0[i].y * 0.3f;
            sp90.z += D_80A849D0[i].z * 0.3f;
        if(i + 1 < linkCount) {
            sp90.x += D_80A849D0[i + 1].x * 0.15f;
            sp90.y += D_80A849D0[i + 1].y * 0.15f;
            sp90.z += D_80A849D0[i + 1].z * 0.15f;
        }
        if(i + 2 < linkCount) {
            sp90.x += D_80A849D0[i + 2].x * 0.075f;
            sp90.y += D_80A849D0[i + 2].y * 0.075f;
            sp90.z += D_80A849D0[i + 2].z * 0.075f;
        }
        link2->unk_3C.x += sp90.x;
        link2->unk_3C.y += sp90.y;
        link2->unk_3C.z += sp90.z;
    }

}
#else
Vec3f D_80A849D0[0x40];
void func_80A81FFC(ObjMine* this);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A81FFC.s")
#endif

void func_80A828A8(ObjMine* this) {
    s32 pad;
    Vec3f spE0;
    Vec3f spD4;
    Vec3f spC8;
    s32 spC4 = OBJMINE_GET_LINK_COUNT(&this->actor);
    ObjMineWaterChain* chain2 = &this->chain.water;
    ObjMineWaterLink* link2;
    s32 i;
    Vec3f* phi_s3;
    Vec3f spA8;
    Vec3f sp9C;
    Vec3f sp90;
    Vec3f sp84;
    s32 phi_s5;
    f32 sp7C;
    f32 sp78;
    Vec3f* phi_x;

    sp84.x = this->actor.home.pos.x;
    sp84.y = this->actor.home.pos.y + 6.0f;
    sp84.z = this->actor.home.pos.z;

    for (i = 0, phi_s3 = NULL, link2 = chain2->links; i < spC4; i++, phi_s3 = &link2->basis.x, link2++) {
        phi_s5 = false;

        link2->unk_30.x += link2->unk_3C.x;
        link2->unk_30.y += link2->unk_3C.y;
        link2->unk_30.z += link2->unk_3C.z;

        Math_Vec3f_Scale(&link2->unk_30, chain2->unk_00);
        Math_Vec3f_Copy(&sp90, &link2->unk_24);

        link2->unk_24.x += link2->unk_30.x;
        link2->unk_24.y += link2->unk_30.y;
        link2->unk_24.z += link2->unk_30.z;

        if ((link2->unk_24.y <= this->actor.home.pos.y) && (link2->unk_30.y < 0.0f)) {
            link2->unk_30.y *= 0.1f;
        }

        Math_Vec3f_Diff(&link2->unk_24, &sp84, &spA8);

        if (ObjMine_GetUnitVec3fNorm(&spA8, &sp9C, &sp7C, &sp78) && (sp7C > 4.0f)) {
            Math_Vec3f_Copy(&spD4, &link2->basis.y);
            ObjMine_StepUntilParallel(&spD4, &sp9C, M_PI / 30);
            phi_x = (phi_s3 == NULL) ? &sStandardBasis.x : phi_s3;

            Math3D_CrossProduct(phi_x, &spD4, &spA8);

            if (ObjMine_GetUnitVec3f(&spA8, &spE0)) {
                Math3D_CrossProduct(&spD4, &spE0, &spA8);
                if (ObjMine_GetUnitVec3f(&spA8, &spC8)) {
                    phi_s5 = true;
                }
            }
        }

        if (phi_s5) {
            Math_Vec3f_Copy(&link2->basis.x, &spC8);
            Math_Vec3f_Copy(&link2->basis.y, &spD4);
            Math_Vec3f_Copy(&link2->basis.z, &spE0);
        } else {
            sp7C = 4.0f;
        }

        if (sp7C >= 6.0f) {
            link2->unk_24.x = sp84.x + (link2->basis.y.x * 6.0f);
            link2->unk_24.y = sp84.y + (link2->basis.y.y * 6.0f);
            link2->unk_24.z = sp84.z + (link2->basis.y.z * 6.0f);
        } else {
            link2->unk_24.x = sp84.x + (link2->basis.y.x * sp7C);
            link2->unk_24.y = sp84.y + (link2->basis.y.y * sp7C);
            link2->unk_24.z = sp84.z + (link2->basis.y.z * sp7C);
        }

        sp84.x = link2->unk_24.x + (link2->basis.y.x * 6.0f);
        sp84.y = link2->unk_24.y + (link2->basis.y.y * 6.0f);
        sp84.z = link2->unk_24.z + (link2->basis.y.z * 6.0f);
    }
}

void ObjMine_Water_UpdateChain(ObjMine* this, PlayState* play) {
    func_80A81E7C(this, play);
    func_80A81FFC(this);
    func_80A828A8(this);
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
            ObjMine_Water_SetCollider(this, linkCount);
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
    ObjMineAirChain* chain1 = &this->chain.air;
    ObjMineAirLink* link1;
    s32 i;
    f32 sp90;
    f32 sp8C;
    f32 sp88;
    s16 sp86;
    s16 sp84;

    Math_Vec3f_Copy(&chain1->unk_24, &chain1->basis.y);
    if (ObjMine_AirWater_CheckOC(this)) {
        ObjMine_AirWater_SpawnBomb(this, play);
        ObjMine_AirWater_Noop(this);
        ObjMine_SetupExplode(this);
        return;
    }

    if (this->collider.base.acFlags & AC_HIT) {
        this->collider.base.acFlags &= ~AC_HIT;
        chain1->unk_48 = 0.04f;
        ObjMine_Air_CheckAC(this, &chain1->unk_4C, &sp84);
        sp88 = sp8C = Math_SinS(sp84) * 150.0f;
        sp8C = -(sp8C / linkCount);

        for (i = 0, link1 = chain1->links; i < linkCount; i++, link1++) {
            link1->unk_02 += (s16)sp88;
            link1->unk_02 = CLAMP(link1->unk_02, -800, 800);
            sp88 -= sp8C;
        }
    }

    if (chain1->unk_48 > 0.0001f) {
        sp90 = Math_SinS(chain1->unk_4C) * chain1->unk_48;
        sp8C = Math_CosS(chain1->unk_4C) * chain1->unk_48;
        chain1->unk_38 += sp90;
        chain1->unk_3C += sp8C;
        Math_StepToF(&chain1->unk_48, 0.0f, 0.02f);
    }

    if (RANDU_BITS(5) == 0) {
        chain1->unk_50 = Rand_ZeroOne() * chain1->unk_58;
        chain1->unk_54 = RANDU_BITS(16);
    }

    sp90 = Math_SinS(chain1->unk_54) * chain1->unk_50;
    sp8C = Math_CosS(chain1->unk_54) * chain1->unk_50;
    chain1->unk_38 += sp90;
    chain1->unk_3C += sp8C;

    chain1->unk_38 += chain1->unk_30 * chain1->unk_40;
    chain1->unk_3C += chain1->unk_34 * chain1->unk_40;

    chain1->unk_38 *= chain1->unk_44;
    chain1->unk_3C *= chain1->unk_44;

    chain1->unk_30 += chain1->unk_38;
    chain1->unk_34 += chain1->unk_3C;

    chain1->unk_30 = CLAMP(chain1->unk_30, -5.0f, 5.0f);
    chain1->unk_34 = CLAMP(chain1->unk_34, -5.0f, 5.0f);

    ObjMine_Air_SetBasis(this);
    ObjMine_Air_SetWorld(this);

    if (chain1->unk_5C > -0.000001f) {
        Vec3f* world = &this->actor.world.pos;
        Vec3f* home = &this->actor.home.pos;

        if (chain1->unk_5C <= Math3D_XZDistanceSquared(world->x, world->z, home->x, home->z)) {

            Actor_UpdateBgCheckInfo(play, &this->actor, 0.0f, 20.0f, 0.0f, 1);

            if ((this->actor.bgCheckFlags & 8) && (this->actor.wallPoly != NULL)) {
                Vec3f sp70;
                Vec3f sp64;
                Vec3f sp58;
                Vec3f sp4C;
                f32 sp48;
                f32 sp44;

                sp4C.x = chain1->unk_38;
                sp4C.y = 0.0f;
                sp4C.z = chain1->unk_3C;

                if (ObjMine_GetUnitVec3fNorm(&sp4C, &sp70, &sp48, &sp44)) {
                    sp58.x = COLPOLY_GET_NORMAL(this->actor.wallPoly->normal.x);
                    sp58.y = COLPOLY_GET_NORMAL(this->actor.wallPoly->normal.y);
                    sp58.z = COLPOLY_GET_NORMAL(this->actor.wallPoly->normal.z);

                    func_80179F64(&sp70, &sp58, &sp64);

                    sp48 *= 0.5f;
                    chain1->unk_38 = sp64.x * sp48;
                    chain1->unk_3C = sp64.z * sp48;
                } else {
                    chain1->unk_38 *= -0.1f;
                    chain1->unk_3C *= -0.1f;
                }
                ObjMine_Air_SetChain3034(this);
                ObjMine_Air_SetBasis(this);
                ObjMine_Air_SetWorld(this);
            }
        }
    }

    for (i = 0, link1 = chain1->links; i < linkCount; i++, link1++) {
        sp86 = link1->unk_00 - 0x4000;
        sp88 = link1->unk_02 + (sp86 * -0.05f) + ((Rand_ZeroOne() * 30.0f) - 15.0f);
        sp88 *= 0.995f;
        link1->unk_02 = sp88;
        link1->unk_00 += link1->unk_02;
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
    ObjMineWaterChain* chain2 = &this->chain.water;

    if (ObjMine_AirWater_CheckOC(this)) {
        ObjMine_AirWater_SpawnBomb(this, play);
        ObjMine_AirWater_Noop(this);
        ObjMine_SetupExplode(this);
        return;
    }

    if (this->collider.base.acFlags & AC_HIT) {
        this->collider.base.acFlags &= ~AC_HIT;
        ObjMine_Water_CheckAC(this, &chain2->unk_04);
        chain2->unk_10 = 7.0f;
        Math_Vec3f_Scale(&chain2->unk_04, 7.0f);
    }

    if (chain2->unk_10 > 0.0001f) {
        chain2->unk_10 = Math_Vec3f_StepTo(&chain2->unk_04, &gZeroVec3f, 2.8f);
    }

    chain2->unk_00 = 0.9f;
    chain2->unk_24 = -0.0002f;
    chain2->unk_30 = -0.0002f;
    chain2->unk_1C = 0.003f;

    if (RANDU_BITS(5) == 0) {
        s16 randAngle = RANDU_BITS(16);

        chain2->unk_14 = Math_SinS(randAngle) * 1.8f * chain2->unk_1C;
        chain2->unk_18 = Math_CosS(randAngle) * 0.2f * chain2->unk_1C;
        chain2->unk_20 = RANDU_BITS(13);
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

    func_800B8050(&this->actor, play, 1);
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

    func_800B8118(thisx, play, 1);
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
    ObjMineAirChain* chain1 = &this->chain.air;
    ObjMineAirLink* link1;
    s32 i;
    Vec3f sp94;
    Vec3f sp88;
    Gfx* gfx;

    func_800B8050(&this->actor, play, 1);

    OPEN_DISPS(play->state.gfxCtx);
    gfx = POLY_OPA_DISP;

    gSPDisplayList(gfx++, &sSetupDL[6 * 25]);
    gSPMatrix(gfx++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfx++, object_ny_DL_000030);

    ObjMine_ReplaceRotation(&chain1->basis);
    Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
    if (linkCount != 0) {
        Math_Vec3f_ScaleAndStore(&chain1->basis.y, -6.0f, &sp88);
        sp94.x = this->actor.home.pos.x - sp88.x;
        sp94.y = this->actor.home.pos.y - 6.0f - sp88.y;
        sp94.z = this->actor.home.pos.z - sp88.z;
        Math_Vec3f_ScaleAndStore(&chain1->basis.y, -12.0f, &sp88);

        for (i = 0, link1 = chain1->links; i < linkCount; i++, link1++) {
            Matrix_RotateYS(link1->unk_00, MTXMODE_APPLY);
            sp94.x += sp88.x;
            sp94.y += sp88.y;
            sp94.z += sp88.z;
            ObjMine_ReplaceTranslation(&sp94);

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
    ObjMineWaterChain* chain2 = &this->chain.water;
    ObjMineWaterLink* link2;
    s32 i;
    Gfx* gfx;

    func_800B8050(&this->actor, play, 1);

    OPEN_DISPS(play->state.gfxCtx);
    gfx = POLY_OPA_DISP;

    gSPDisplayList(gfx++, &sSetupDL[6 * 25]);
    gSPMatrix(gfx++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfx++, object_ny_DL_000030);

    for (i = 0, link2 = chain2->links; i < linkCount; i++, link2++) {
        ObjMine_ReplaceRotation(&link2->basis);
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
        if ((i % 2) == 0) {
            Matrix_RotateYS(0x4000, MTXMODE_APPLY);
        }
        ObjMine_ReplaceTranslation(&link2->unk_24);

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
