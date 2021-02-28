#include <ultra64.h>
#include <global.h>

f32 Collision_GetDamageAndEffectOnBumper(Collider *toucher, ColliderInfo *toucherBody, Collider *bumper, ColliderInfo *bumperBody, u32 *effect) {
    static f32 damageMultipliers[] = { 
        0.0f, 1.0f, 2.0f, 0.5f, 0.25f, 3.0f, 4.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    };
    u32 collidesWith;
    s32 i;
    f32 damage;

    *effect = 0;

    damage = Collision_GetToucherDamage(toucher, toucherBody, bumper, bumperBody);
    if (bumper->actor->colChkInfo.damageChart != NULL) {
        collidesWith = toucherBody->toucher.dmgFlags;

        for (i = 0; i != 32; i++) {
            if (collidesWith == 1) {
                break;
            }
            collidesWith >>= 1;
        }

        damage *= damageMultipliers[bumper->actor->colChkInfo.damageChart->attack[i] & 0xF];
        *effect = (bumper->actor->colChkInfo.damageChart->attack[i] >> 4) & 0xF;
    }
    return damage;
}

f32 func_800E04BC(f32 damage, ColliderInfo *bumperBody) {
    f32 finalDamage = damage - bumperBody->bumper.defense;

    return finalDamage;
}

s32 Collision_GetToucherDamage(Collider *toucher, ColliderInfo *toucherBody, Collider *bumper, ColliderInfo *bumperBody) {
    if (toucher->actor != NULL && toucher->actor->id == ACTOR_EN_BOM && 
        bumper->actor != NULL && bumper->actor->id == ACTOR_PLAYER) {
        return 8;
    }
    return toucherBody->toucher.damage;
}

s32 Collision_InitCommonDefault(GlobalContext *ctxt, Collider *shape) {
    static Collider defaultColCommon = {
        NULL, NULL, NULL, NULL, 0x00, 0x00, 0x00, 0x00, 0x03, COLSHAPE_NONE,
    };

    *shape = defaultColCommon;
    return 1;
}

s32 Collision_FiniCommon(GlobalContext *ctxt, Collider *shape) {
    return 1;
}

s32 func_800E0594(GlobalContext *ctxt, Collider *shape, ColliderInitToActor *init) {
    shape->actor = init->actor;
    shape->atFlags = init->atFlags;
    shape->acFlags = init->acFlags;
    shape->ocFlags1 = init->ocFlags1;
    shape->ocFlags2 = 0x10;
    shape->shape = init->shape;
    return 1;
}

s32 func_800E05D4(GlobalContext* ctxt, Collider* shape, Actor* actor, ColliderInitType1* init) {
    shape->actor = actor;
    shape->colType = init->colType;
    shape->atFlags = init->atFlags;
    shape->acFlags = init->acFlags;
    shape->ocFlags1 = init->ocFlags1;
    shape->ocFlags2 = 0x10;
    shape->shape = init->shape;
    return 1;
}

s32 Collision_InitCommonWithData(GlobalContext *ctxt, Collider *shape, Actor *actor, ColliderInit *init) {
    shape->actor = actor;
    shape->colType = init->colType;
    shape->atFlags = init->atFlags;
    shape->acFlags = init->acFlags;
    shape->ocFlags1 = init->ocFlags1;
    shape->ocFlags2 = init->ocFlags2;
    shape->shape = init->shape;
    return 1;
}

void Collision_ResetCommonForAT(GlobalContext *ctxt, Collider *shape) {
    shape->at = NULL;
    shape->atFlags &= ~6;
}

void Collision_ResetCommonForAC(GlobalContext *ctxt, Collider *shape) {
    shape->ac = NULL;
    shape->acFlags &= ~0x82;
}

void Collision_ResetCommonForOT(GlobalContext *ctxt, Collider *shape) {
    shape->oc = NULL;
    shape->ocFlags1 &= ~2;
    shape->ocFlags2 &= ~1;
}

s32 Collision_InitTouchDefault(GlobalContext *ctxt, ColliderTouch *touch) {
    static ColliderTouch defaultColTouch = {
        0, 0, 0,
    };

    *touch = defaultColTouch;
    return 1;
}

s32 Collision_FiniTouch(GlobalContext *ctxt, ColliderTouch *touch) {
    return 1;
}

s32 Collision_InitTouchWithData(GlobalContext *ctxt, ColliderTouch *touch, ColliderTouchInit *init) {
    touch->dmgFlags = init->dmgFlags;
    touch->effect = init->effect;
    touch->damage = init->damage;
    return 1;
}

void Collision_nop800E0720(GlobalContext* ctxt, ColliderInfo* body) {

}

s32 Collision_InitBumpDefault(GlobalContext *ctxt, ColliderBump *bump) {
    static ColliderBump defaultColBump = {
        0xF7CFFFFF, 0, 0, { 0, 0, 0 },
    };

    *bump = defaultColBump;
    return 1;
}

s32 Collision_FiniBump(GlobalContext* ctxt, ColliderBump* bump) {
    return 1;
}

s32 Collision_InitBumpWithData(GlobalContext *ctxt, ColliderBump *bump, ColliderBumpInit *init) {
    bump->dmgFlags = init->dmgFlags;
    bump->effect = init->effect;
    bump->defense = init->defense;
    return 1;
}

s32 Collision_InitBodyDefault(GlobalContext *ctxt, ColliderInfo *body) {
    static ColliderInfo defaultColBodyInfo = {
        { 0, 0, 0 },    { 0xF7CFFFFF, 0, 0, { 0, 0, 0 } },
        ELEMTYPE_UNK0, 0x00,
        0x00,          0x00,
        NULL,          NULL, 
        NULL,          NULL,
    };

    *body = defaultColBodyInfo;
    Collision_InitTouchDefault(ctxt, &body->toucher);
    Collision_InitBumpDefault(ctxt, &body->bumper);
    return 1;
}

s32 Collision_FiniBody(GlobalContext *ctxt, ColliderInfo *body) {
    Collision_FiniTouch(ctxt, &body->toucher);
    Collision_FiniBump(ctxt, &body->bumper);
    return 1;
}

s32 Collision_InitBodyWithData(GlobalContext *ctxt, ColliderInfo *body, ColliderInfoInit *init) {
    body->elemType = init->elemType;
    Collision_InitTouchWithData(ctxt, &body->toucher, &init->toucher);
    Collision_InitBumpWithData(ctxt, &body->bumper, &init->bumper);
    body->toucherFlags = init->toucherFlags;
    body->bumperFlags = init->bumperFlags;
    body->ocElemFlags = init->ocElemFlags;
    return 1;
}

void Collision_ResetBodyForAT(GlobalContext *ctxt, ColliderInfo *body) {
    body->atHit = NULL;
    body->atHitInfo = NULL;
    body->toucherFlags &= ~2;
    body->toucherFlags &= ~0x40;
    Collision_nop800E0720(ctxt, body);
}

void Collision_ResetBodyForAC(GlobalContext *ctxt, ColliderInfo *body) {
    body->bumper.hitPos.x = body->bumper.hitPos.y = body->bumper.hitPos.z = 0;
    body->bumperFlags &= ~2;
    body->bumperFlags &= ~0x80;
    body->acHit = NULL;
    body->acHitInfo = NULL;
}

void Collision_ResetBodyForOT(GlobalContext *ctxt, ColliderInfo *body) {
    body->ocElemFlags &= ~2;
}

s32 Collision_InitSphereParamsDefault(GlobalContext *ctxt, ColliderJntSphElementDim *params) {
    static ColliderJntSphElementDim defaultColSphereInfo = {
        { { 0, 0, 0 }, 0, }, { { 0, 0, 0 }, 0, }, 0.0f, 0,
    };

    *params = defaultColSphereInfo;
    return 1;
}

s32 Collision_FiniSphereParams(GlobalContext *ctxt, ColliderJntSphElementDim *params) {
    return 1;
}

s32 Collision_InitSphereParamsWithData(GlobalContext *ctxt, ColliderJntSphElementDim *params, ColliderJntSphElementDimInit *init) {
    params->limb = init->limb;
    params->modelSphere = init->modelSphere;
    params->scale = init->scale * 0.01f;
    return 1;
}

s32 Collision_InitSphereGroupElemDefault(GlobalContext *pzParm1, ColliderJntSphElement *elem) {
    Collision_InitBodyDefault(pzParm1, &elem->info);
    Collision_InitSphereParamsDefault(pzParm1, &elem->dim);
    return 1;
}

s32 Collision_FiniSphereGroupElem(GlobalContext *ctxt, ColliderJntSphElement *elem) {
    Collision_FiniBody(ctxt, &elem->info);
    Collision_FiniSphereParams(ctxt, &elem->dim);
    return 1;
}

s32 Collision_InitSphereGroupElemWithData(GlobalContext *ctxt, ColliderJntSphElement *elem, ColliderJntSphElementInit *init) {
    Collision_InitBodyWithData(ctxt, &elem->info, &init->info);
    Collision_InitSphereParamsWithData(ctxt, &elem->dim, &init->dim);
    return 1;
}

s32 Collision_ResetSphereGroupElemForAT(GlobalContext *ctxt, ColliderJntSphElement *elem) {
    Collision_ResetBodyForAT(ctxt, &elem->info);
    return 1;
}

s32 Collision_ResetSphereGroupElemForAC(GlobalContext *ctxt, ColliderJntSphElement *elem) {
    Collision_ResetBodyForAC(ctxt, &elem->info);
    return 1;
}

s32 Collision_ResetSphereGroupElemForOT(GlobalContext *ctxt, ColliderJntSphElement *elem) {
    Collision_ResetBodyForOT(ctxt, &elem->info);
    return 1;
}

s32 Collision_InitSphereGroupDefault(GlobalContext *ctxt, ColliderJntSph *sphereGroup) {
    Collision_InitCommonDefault(ctxt, &sphereGroup->base);
    sphereGroup->count = 0;
    sphereGroup->elements = NULL;
    return 1;
}

// free jnt sph
s32 func_800E0B78(GlobalContext *ctxt, ColliderJntSph *sphereGroup) {
    ColliderJntSphElement *sphElem;

    Collision_FiniCommon(ctxt, &sphereGroup->base);
    for (sphElem = &sphereGroup->elements[0]; sphElem < &sphereGroup->elements[sphereGroup->count]; sphElem++) {
        Collision_FiniSphereGroupElem(ctxt, sphElem);
    }

    sphereGroup->count = 0;
    if (sphereGroup->elements != NULL) {
        zelda_free(sphereGroup->elements);
    }
    sphereGroup->elements = NULL;
    return 1;
}

s32 Collision_FiniSphereGroup(GlobalContext* ctxt, ColliderJntSph* sphereGroup) {
    ColliderJntSphElement* sphElem;

    Collision_FiniCommon(ctxt, &sphereGroup->base);

    for (sphElem = &sphereGroup->elements[0]; sphElem < &sphereGroup->elements[sphereGroup->count]; sphElem++) {
        Collision_FiniSphereGroupElem(ctxt, sphElem);
    }
    sphereGroup->count = 0;
    sphereGroup->elements = NULL;
    return 1;
}

s32 func_800E0CA8(GlobalContext *ctxt, ColliderJntSph *sphereGroup, ColliderJntSphInitToActor *init) {
    ColliderJntSphElement *sphElem;
    ColliderJntSphElementInit *initElem;

    func_800E0594(ctxt, &sphereGroup->base, &init->base);
    sphereGroup->count = init->count;
    sphereGroup->elements = zelda_malloc(init->count * sizeof(ColliderJntSphElement));

    if (sphereGroup->elements == NULL) {
        sphereGroup->count = 0;
        return 0;
    }

    for (sphElem = &sphereGroup->elements[0], initElem = &init->elements[0]; sphElem < &sphereGroup->elements[sphereGroup->count]; sphElem++, initElem++) {
        Collision_InitSphereGroupElemDefault(ctxt, sphElem);
        Collision_InitSphereGroupElemWithData(ctxt, sphElem, initElem);
    }
    return 1;
}

s32 func_800E0D84(GlobalContext *ctxt, ColliderJntSph *sphereGroup, Actor *actor, ColliderJntSphInitType1 *init) {
    ColliderJntSphElement *sphElem;
    ColliderJntSphElementInit *initElem;

    func_800E05D4(ctxt, &sphereGroup->base, actor, &init->base);
    sphereGroup->count = init->count;
    sphereGroup->elements = zelda_malloc(init->count * sizeof(ColliderJntSphElement));

    if (sphereGroup->elements == NULL) {
        sphereGroup->count = 0;
        return 0;
    }

    for (sphElem = &sphereGroup->elements[0], initElem = &init->elements[0]; sphElem < &sphereGroup->elements[sphereGroup->count]; sphElem++, initElem++) {
        Collision_InitSphereGroupElemDefault(ctxt, sphElem);
        Collision_InitSphereGroupElemWithData(ctxt, sphElem, initElem);
    }
    return 1;
}

s32 Collision_InitSphereGroupWithData(GlobalContext *ctxt, ColliderJntSph *sphereGroup, Actor *actor, ColliderJntSphInit *init, ColliderJntSphElement *spheres) {
    ColliderJntSphElement* sphElem;
    ColliderJntSphElementInit* sphElemInit;

    Collision_InitCommonWithData(ctxt, &sphereGroup->base, actor, &init->base);
    sphereGroup->count = init->count;
    sphereGroup->elements = spheres;

    for (sphElem = &sphereGroup->elements[0], sphElemInit = &init->elements[0]; sphElem < &sphereGroup->elements[sphereGroup->count]; sphElem++, sphElemInit++) {
        Collision_InitSphereGroupElemDefault(ctxt, sphElem);
        Collision_InitSphereGroupElemWithData(ctxt, sphElem, sphElemInit);
    }

    return 1;
}

s32 Collision_InitSphereGroup(GlobalContext *ctxt, ColliderJntSph *sphereGroup, Actor *actor, ColliderJntSphInit *init, ColliderJntSphElement *spheres) {
    Collision_InitSphereGroupDefault(ctxt, sphereGroup);
    Collision_InitSphereGroupWithData(ctxt, sphereGroup, actor, init, spheres);
    return 0;
}

s32 Collision_ResetSphereGroupForAT(GlobalContext *ctxt, Collider *collider) {
    ColliderJntSphElement *sphElem;
    ColliderJntSph* spheres = (ColliderJntSph*)collider;

    Collision_ResetCommonForAT(ctxt, &spheres->base);

    for (sphElem = &spheres->elements[0]; sphElem < &spheres->elements[spheres->count]; sphElem++) {
        Collision_ResetSphereGroupElemForAT(ctxt, sphElem);
    }
    return 1;
}

s32 Collision_ResetSphereGroupForAC(GlobalContext *ctxt, Collider *collider) {
    ColliderJntSphElement *sphElem;
    ColliderJntSph* spheres = (ColliderJntSph*)collider;

    Collision_ResetCommonForAC(ctxt, &spheres->base);

    for (sphElem = &spheres->elements[0]; sphElem < &spheres->elements[spheres->count]; sphElem++) {
        Collision_ResetSphereGroupElemForAC(ctxt, sphElem);
    }
    return 1;
}

s32 Collision_ResetSphereGroupForOT(GlobalContext *ctxt, Collider *collider) {
    ColliderJntSphElement *sphElem;
    ColliderJntSph* spheres = (ColliderJntSph*)collider;

    Collision_ResetCommonForOT(ctxt, &spheres->base);

    for (sphElem = &spheres->elements[0]; sphElem < &spheres->elements[spheres->count]; sphElem++) {
        Collision_ResetSphereGroupElemForOT(ctxt, sphElem);
    }
    return 1;
}

s32 Collision_InitCylinderParamsDefault(GlobalContext* ctxt, Cylinder16* params) {
    static Cylinder16 defaultColCylinderInfo = {
        0, 0, 0, { 0, 0, 0 },
    };

    *params = defaultColCylinderInfo;
    return 1;
}

s32 Collision_FiniCylinderParams(GlobalContext* ctxt, Cylinder16* params) {
    return 1;
}

s32 Collision_InitCylinderParamsWithData(GlobalContext *ctxt, Cylinder16 *info, Cylinder16 *init) {
    *info = *init;
    return 1;
}

s32 Collision_InitCylinderDefault(GlobalContext *ctxt, ColliderCylinder *cylinder) {
    Collision_InitCommonDefault(ctxt, &cylinder->base);
    Collision_InitBodyDefault(ctxt, &cylinder->info);
    Collision_InitCylinderParamsDefault(ctxt, &cylinder->dim);
    return 1;
}

s32 Collision_FiniCylinder(GlobalContext *ctxt, ColliderCylinder *cylinder) {
    Collision_FiniCommon(ctxt, &cylinder->base);
    Collision_FiniBody(ctxt, &cylinder->info);
    Collision_FiniCylinderParams(ctxt, &cylinder->dim);
    return 1;
}

s32 func_800E123C(GlobalContext* ctxt, ColliderCylinder* cylinder, ColliderCylinderInitToActor* init) {
    func_800E0594(ctxt, &cylinder->base, &init->base);
    Collision_InitBodyWithData(ctxt, &cylinder->info, &init->info);
    Collision_InitCylinderParamsWithData(ctxt, &cylinder->dim, &init->dim);
    return 1;
}

s32 func_800E12A4(GlobalContext *ctxt, ColliderCylinder *cylinder, Actor *actor, ColliderCylinderInitType1 *init) {
    func_800E05D4(ctxt, &cylinder->base, actor, &init->base);
    Collision_InitBodyWithData(ctxt, &cylinder->info, &init->info);
    Collision_InitCylinderParamsWithData(ctxt, &cylinder->dim, &init->dim);
    return 1;
}

s32 Collision_InitCylinderWithData(GlobalContext *ctxt, ColliderCylinder *cylinder, Actor *actor, ColliderCylinderInit *init) {
    Collision_InitCommonWithData(ctxt, &cylinder->base, actor, &init->base);
    Collision_InitBodyWithData(ctxt, &cylinder->info, &init->info);
    Collision_InitCylinderParamsWithData(ctxt, &cylinder->dim, &init->dim);
    return 1;
}

s32 Collision_InitCylinder(GlobalContext *ctxt, ColliderCylinder *cylinder, Actor *actor, ColliderCylinderInit *init) {
    Collision_InitCylinderDefault(ctxt, cylinder);
    Collision_InitCylinderWithData(ctxt, cylinder, actor, init);
    return 1;
}

s32 Collision_ResetCylinderForAT(GlobalContext *ctxt, Collider* collider) {
    ColliderCylinder *cylinder = (ColliderCylinder*)collider;

    Collision_ResetCommonForAT(ctxt, &cylinder->base);
    Collision_ResetBodyForAT(ctxt, &cylinder->info);
    return 1;
}

s32 Collision_ResetCylinderForAC(GlobalContext *ctxt, Collider* collider) {
    ColliderCylinder *cylinder = (ColliderCylinder*)collider;

    Collision_ResetCommonForAC(ctxt, &cylinder->base);
    Collision_ResetBodyForAC(ctxt, &cylinder->info);
    return 1;
}

s32 Collision_ReseCylinderForOT(GlobalContext *ctxt, Collider* collider) {
    ColliderCylinder *cylinder = (ColliderCylinder*)collider;

    Collision_ResetCommonForOT(ctxt, &cylinder->base);
    Collision_ResetBodyForOT(ctxt, &cylinder->info);
    return 1;
}

s32 Collision_InitTriParamsDefault(GlobalContext *ctxt, TriNorm *coords) {
    static TriNorm defaultColTriParams = {
        {
            { 0.0f, 0.0f, 0.0f },
            { 0.0f, 0.0f, 0.0f },
            { 0.0f, 0.0f, 0.0f },
        },
        {
            { 0.0f, 0.0f, 0.0f },
            0.0f,
        },
    };

    *coords = defaultColTriParams;
    return 1;
}

s32 Collision_FiniTriParams(GlobalContext* ctxt, TriNorm* params) {
    return 1;
}

s32 Collision_InitTriParamsWithData(GlobalContext *ctxt, TriNorm *params, ColliderTrisElementDimInit *init) {
    Vec3f* destVtx;
    Vec3f* srcVtx;
    f32 nx;
    f32 ny;
    f32 nz;
    f32 originDist;

    for (destVtx = params->vtx, srcVtx = init->vtx; destVtx < &params->vtx[3]; destVtx++, srcVtx++) {
        *destVtx = *srcVtx;
    }

    Math3D_UnitNormalVector(&init->vtx[0], &init->vtx[1], &init->vtx[2], &nx, &ny, &nz, &originDist);

    params->plane.normal.x = nx;
    params->plane.normal.y = ny;
    params->plane.normal.z = nz;
    params->plane.originDist = originDist;
    return 1;
}

s32 Collision_InitTriDefault(GlobalContext *ctxt, ColliderTrisElement *elem) {
    Collision_InitBodyDefault(ctxt, &elem->info);
    Collision_InitTriParamsDefault(ctxt, &elem->dim);
    return 1;
}

s32 Collision_FiniTri(GlobalContext *ctxt, ColliderTrisElement *elem) {
    Collision_FiniBody(ctxt, &elem->info);
    Collision_FiniTriParams(ctxt, &elem->dim);
    return 1;
}

s32 Collision_InitTriWithData(GlobalContext *ctxt, ColliderTrisElement *elem, ColliderTrisElementInit *init) {
    Collision_InitBodyWithData(ctxt, &elem->info, &init->info);
    Collision_InitTriParamsWithData(ctxt, &elem->dim, &init->dim);
    return 1;
}

s32 Collision_ResetTriForAT(GlobalContext *ctxt, ColliderTrisElement *tri) {
    Collision_ResetBodyForAT(ctxt, &tri->info);
    return 1;
}

s32 Collision_ResetTriForAC(GlobalContext *ctxt, ColliderTrisElement *tri) {
    Collision_ResetBodyForAC(ctxt, &tri->info);
    return 1;
}

// Collision_ResetTriForOT
s32 func_800E16AC(GlobalContext *ctxt, ColliderTrisElement *tri) {
    Collision_ResetBodyForOT(ctxt, &tri->info);
    return 1;
}

s32 Collision_InitTriGroupDefault(GlobalContext *ctxt, ColliderTris *triGroup) {
    Collision_InitCommonDefault(ctxt, &triGroup->base);
    triGroup->count = 0;
    triGroup->elements = NULL;
    return 1;
}

s32 func_800E16FC(GlobalContext *ctxt, ColliderTris *triGroup) {
    ColliderTrisElement *triElem;

    Collision_FiniCommon(ctxt, &triGroup->base);
    
    for (triElem = &triGroup->elements[0]; triElem < &triGroup->elements[triGroup->count]; triElem++) {
        Collision_FiniTri(ctxt, triElem);
    }

    triGroup->count = 0;
    if (triGroup->elements != NULL) {
        zelda_free(triGroup->elements);
    }
    triGroup->elements = NULL;

    return 1;
}

s32 Collision_FiniTriGroup(GlobalContext *ctxt, ColliderTris *triGroup) {
    ColliderTrisElement* triElem;

    Collision_FiniCommon(ctxt, &triGroup->base);

    for (triElem = &triGroup->elements[0]; triElem < &triGroup->elements[triGroup->count]; triElem++) {
        Collision_FiniTri(ctxt, triElem);
    }
    triGroup->count = 0;
    triGroup->elements = NULL;
    return 1;
}

s32 func_800E1858(GlobalContext *ctxt, ColliderTris *triGroup, Actor *actor, ColliderTrisInitType1 *init) {
    ColliderTrisElement *triElem;
    ColliderTrisElementInit *triElemInit;

    func_800E05D4(ctxt, &triGroup->base, actor, &init->base);
    triGroup->count = init->count;
    triGroup->elements = zelda_malloc(triGroup->count * sizeof(ColliderTrisElement));

    if (triGroup->elements == NULL) {
        triGroup->count = 0;
        return 0;
    }

    for (triElem = &triGroup->elements[0], triElemInit = &init->elements[0]; triElem < &triGroup->elements[triGroup->count]; triElem++, triElemInit++) {
        Collision_InitTriDefault(ctxt, triElem);
        Collision_InitTriWithData(ctxt, triElem, triElemInit);
    }

    return 1;
}

s32 Collision_InitTriGroupWithData(GlobalContext *ctxt, ColliderTris *triGroup, Actor *actor, ColliderTrisInit *init, ColliderTrisElement *tris) {
    ColliderTrisElement *triElem;
    ColliderTrisElementInit *triElemInit;

    Collision_InitCommonWithData(ctxt, &triGroup->base, actor, &init->base);
    triGroup->count = init->count;
    triGroup->elements = tris;

    for (triElem = &triGroup->elements[0], triElemInit = &init->elements[0]; triElem < &triGroup->elements[triGroup->count]; triElem++, triElemInit++) {
        Collision_InitTriDefault(ctxt, triElem);
        Collision_InitTriWithData(ctxt, triElem, triElemInit);
    }

    return 1;
}

s32 Collision_InitTriGroup(GlobalContext *ctxt, ColliderTris *triGroup, Actor *actor, ColliderTrisInit *init, ColliderTrisElement *tris) {
    Collision_InitTriGroupDefault(ctxt, triGroup);
    Collision_InitTriGroupWithData(ctxt, triGroup, actor, init, tris);
    return 0;
}

s32 Collision_ResetTriGroupForAT(GlobalContext *ctxt, Collider *collider) {
    ColliderTrisElement *triElem;
    ColliderTris* tris = (ColliderTris*)collider;

    Collision_ResetCommonForAT(ctxt, &tris->base);

    for (triElem = &tris->elements[0]; triElem < &tris->elements[tris->count]; triElem++) {
        Collision_ResetTriForAT(ctxt, triElem);
    }
    return 1;
}

s32 Collision_ResetTriGroupForAC(GlobalContext *ctxt, Collider *collider) {
    ColliderTrisElement *triElem;
    ColliderTris* tris = (ColliderTris*)collider;

    Collision_ResetCommonForAC(ctxt, &tris->base);

    for (triElem = &tris->elements[0]; triElem < &tris->elements[tris->count]; triElem++) {
        Collision_ResetTriForAC(ctxt, triElem);
    }
    return 1;
}

s32 Collision_ResetTriGroupForOT(GlobalContext *ctxt, Collider *collider) {
    ColliderTrisElement *triElem;
    ColliderTris* tris = (ColliderTris*)collider;

    Collision_ResetCommonForOT(ctxt, &tris->base);

    for (triElem = &tris->elements[0]; triElem < &tris->elements[tris->count]; triElem++) {
        func_800E16AC(ctxt, triElem);
    }
    return 1;
}

s32 Collision_InitQuadParamsDefault(GlobalContext *ctxt, ColliderQuadDim *params) {
    static ColliderQuadDim defaultColQuadParams = {
        {
            { 0.0f, 0.0f, 0.0f },
            { 0.0f, 0.0f, 0.0f },
            { 0.0f, 0.0f, 0.0f },
            { 0.0f, 0.0f, 0.0f },
        },
        { 0, 0, 0 },
        { 0, 0, 0 },
        1.0E38f,
    };

    *params = defaultColQuadParams;
    return 1;
}

s32 Collision_FiniQuadParams(GlobalContext* ctxt, ColliderQuadDim* params) {
    return 1;
}

s32 Collision_ResetQuadParamsForAT(GlobalContext *ctxt, ColliderQuadDim *params) {
    params->acDist = 1.0E38f;
    return 1;
}

void Collision_QuadCalcMidpoints(ColliderQuadDim *params) {
    params->dcMid.x = (params->quad[3].x + params->quad[2].x) * 0.5f;
    params->dcMid.y = (params->quad[3].y + params->quad[2].y) * 0.5f;
    params->dcMid.z = (params->quad[3].z + params->quad[2].z) * 0.5f;
    params->baMid.x = (params->quad[1].x + params->quad[0].x) * 0.5f;
    params->baMid.y = (params->quad[1].y + params->quad[0].y) * 0.5f;
    params->baMid.z = (params->quad[1].z + params->quad[0].z) * 0.5f;
}

s32 Collision_InitQuadParamsWithData(GlobalContext *ctxt, ColliderQuadDim *params, ColliderQuadDimInit *init) {
    params->quad[0] = init->quad[0];
    params->quad[1] = init->quad[1];
    params->quad[2] = init->quad[2];
    params->quad[3] = init->quad[3];

    Collision_QuadCalcMidpoints(params);
    return 1;
}

s32 Collision_InitQuadDefault(GlobalContext *ctxt, ColliderQuad *quad) {
    Collision_InitCommonDefault(ctxt, &quad->base);
    Collision_InitBodyDefault(ctxt, &quad->info);
    Collision_InitQuadParamsDefault(ctxt, &quad->dim);
    return 1;
}

s32 Collision_FiniQuad(GlobalContext *ctxt, ColliderQuad *quad) {
    Collision_FiniCommon(ctxt, &quad->base);
    Collision_FiniBody(ctxt, &quad->info);
    Collision_FiniQuadParams(ctxt, &quad->dim);
    return 1;
}

s32 func_800E1EB8(GlobalContext *ctxt, ColliderQuad *quad, Actor *actor, ColliderQuadInitType1 *init) {
    func_800E05D4(ctxt, &quad->base, actor, &init->base);
    Collision_InitBodyWithData(ctxt, &quad->info, &init->info);
    Collision_InitQuadParamsWithData(ctxt, &quad->dim, &init->dim);
    return 1;
}

s32 Collision_InitQuadWithData(GlobalContext *ctxt, ColliderQuad *quad, Actor *actor, ColliderQuadInit *init) {
    Collision_InitCommonWithData(ctxt, &quad->base, actor, &init->base);
    Collision_InitBodyWithData(ctxt, &quad->info, &init->info);
    Collision_InitQuadParamsWithData(ctxt, &quad->dim, &init->dim);
    return 1;
}

s32 Collision_InitQuad(GlobalContext *ctxt, ColliderQuad *quad, Actor *actor, ColliderQuadInit *init) {
    Collision_InitQuadDefault(ctxt, quad);
    Collision_InitQuadWithData(ctxt, quad, actor, init);
    return 0;
}

s32 Collision_ResetQuadForAT(GlobalContext *ctxt, Collider *collider) {
    ColliderQuad *quad = (ColliderQuad*)collider;

    Collision_ResetCommonForAT(ctxt, &quad->base);
    Collision_ResetBodyForAT(ctxt, &quad->info);
    Collision_ResetQuadParamsForAT(ctxt, &quad->dim);
    return 1;
}

s32 Collision_ResetQuadForAC(GlobalContext *ctxt, Collider *collider) {
    ColliderQuad *quad = (ColliderQuad*)collider;

    Collision_ResetCommonForAC(ctxt, &quad->base);
    Collision_ResetBodyForAC(ctxt, &quad->info);
    return 1;
}

s32 Collision_ResetQuadForOT(GlobalContext *ctxt, Collider *collider) {
    ColliderQuad *quad = (ColliderQuad*)collider;

    Collision_ResetCommonForOT(ctxt, &quad->base);
    Collision_ResetBodyForOT(ctxt, &quad->info);
    return 1;
}

s32 func_800E20A4(GlobalContext *ctxt, ColliderQuad *quad, Vec3f *a2) {
    f32 dstSq;
    Vec3f sp20;

    if (!(quad->info.toucherFlags & 4)) {
        return 1;
    }
    Math_Vec3s_ToVec3f(&sp20, &quad->dim.dcMid);
    dstSq = Math3D_DistanceSquared(&sp20, a2);

    if (dstSq < quad->dim.acDist) {
        quad->dim.acDist = dstSq;
    
        if (quad->info.atHit != NULL) {
            Collision_ResetCommonForAC(ctxt, quad->info.atHit);
        }
        if (quad->info.atHitInfo != NULL) {
            Collision_ResetBodyForAC(ctxt, quad->info.atHitInfo);
        }
        return 1;
    } else {
        return 0;
    }
}


s32 Collision_InitSphereDefault(GlobalContext *ctxt, ColliderSphere *sphere) {
    Collision_InitCommonDefault(ctxt, &sphere->base);
    Collision_InitBodyDefault(ctxt, &sphere->info);
    Collision_InitSphereParamsDefault(ctxt, &sphere->dim);
    return 1;
}

s32 Collision_FiniSphere(GlobalContext *pzParm1, ColliderSphere *sphere) {
    Collision_FiniCommon(pzParm1, &sphere->base);
    Collision_FiniBody(pzParm1, &sphere->info);
    Collision_FiniSphereParams(pzParm1, &sphere->dim);
    return 1;
}

s32 Collision_InitSphereWithData(GlobalContext *ctxt, ColliderSphere *sphere, Actor *actor, ColliderSphereInit *init) {
    Collision_InitCommonWithData(ctxt, &sphere->base, actor, &init->base);
    Collision_InitBodyWithData(ctxt, &sphere->info, &init->info);
    Collision_InitSphereParamsWithData(ctxt, &sphere->dim, &init->dim);
    return 1;
}

s32 Collision_InitSphere(GlobalContext *ctxt, ColliderSphere *sphere, Actor *actor, ColliderSphereInit *init) {
    Collision_InitSphereDefault(ctxt, sphere);
    Collision_InitSphereWithData(ctxt, sphere, actor, init);
    return 0;
}

s32 Collision_ResetSphereForAT(GlobalContext *ctxt, Collider *collider) {
    ColliderSphere *sphere = (ColliderSphere*)collider;

    Collision_ResetCommonForAT(ctxt, &sphere->base);
    Collision_ResetBodyForAT(ctxt, &sphere->info);
    return 1;
}

s32 Collision_ResetSphereForAC(GlobalContext *ctxt, Collider *collider) {
    ColliderSphere *sphere = (ColliderSphere*)collider;

    Collision_ResetCommonForAC(ctxt, &sphere->base);
    Collision_ResetBodyForAC(ctxt, &sphere->info);
    return 1;
}

s32 Collision_ResetSphereForOT(GlobalContext *ctxt, Collider *collider) {
    ColliderSphere *sphere = (ColliderSphere*)collider;

    Collision_ResetCommonForOT(ctxt, &sphere->base);
    Collision_ResetBodyForOT(ctxt, &sphere->info);
    return 1;
}

// Collision_InitLineDefault
s32 func_800E2368(GlobalContext* ctxt, OcLine* line) {
    static Vec3f D_801BA32C = { 0.0f, 0.0f, 0.0f };

    Math_Vec3f_Copy(&line->line.a, &D_801BA32C);
    Math_Vec3f_Copy(&line->line.b, &D_801BA32C);
    return 1;
}

s32 func_800E23B0(GlobalContext* ctxt, OcLine* line) {
    return 1;
}

s32 func_800E23C4(GlobalContext* ctxt, OcLine* line, Vec3f* a, Vec3f* b) {
    Math_Vec3f_Copy(&line->line.a, a);
    Math_Vec3f_Copy(&line->line.b, b);
    return 1;
}

s32 func_800E2408(GlobalContext* ctxt, OcLine* line, OcLine* init) {
    line->ocFlags = init->ocFlags;
    func_800E23C4(ctxt, line, &init->line.a, &init->line.b);
    return 1;
}

// Collision_ResetLineForOC
s32 func_800E2434(GlobalContext *ctxt, OcLine* line) {
    line->ocFlags &= ~1;
    return 1;
}

void Collision_Init(GlobalContext *ctxt, CollisionCheckContext *colCtxt) {
    colCtxt->flags = 0;
    Collision_Reset(ctxt, colCtxt);
}

void Collision_Fini(GlobalContext *ctxt, CollisionCheckContext *colCtxt) {
}

void Collision_Reset(GlobalContext* ctxt, CollisionCheckContext* colCtxt) {
    Collider** col;
    OcLine** line;

    if (colCtxt->flags & 1) {
        return;
    }

    colCtxt->colATCount = 0;
    colCtxt->colACCount = 0;
    colCtxt->colOCCount = 0;
    colCtxt->colLineCount = 0;

    for (col = &colCtxt->colAT[0]; col < &colCtxt->colAT[ARRAY_COUNT(colCtxt->colAT)]; col++) {
        *col = NULL;
    }

    for (col = &colCtxt->colAC[0]; col < &colCtxt->colAC[ARRAY_COUNT(colCtxt->colAC)]; col++) {
        *col = NULL;
    }

    for (col = &colCtxt->colOC[0]; col < &colCtxt->colOC[ARRAY_COUNT(colCtxt->colOC)]; col++) {
        *col = NULL;
    }

    for (line = &colCtxt->colLine[0]; line < &colCtxt->colLine[ARRAY_COUNT(colCtxt->colLine)]; line++) {
        *line = NULL;
    }
}

void Collision_EnableEditMode(GlobalContext *ctxt, CollisionCheckContext *colCtxt) {
    colCtxt->flags |= 1;
}

void Collision_EnableAppendMode(GlobalContext *ctxt, CollisionCheckContext *colCtxt) {
    colCtxt->flags &= ~1;
}

ColChkResetFunc collisionAddATFuncs[] = {
    Collision_ResetSphereGroupForAT,
    Collision_ResetCylinderForAT,
    Collision_ResetTriGroupForAT,
    Collision_ResetQuadForAT,
    Collision_ResetSphereForAT,
};

s32 Collision_AddAT(GlobalContext *ctxt, CollisionCheckContext *colCtxt, Collider *shape) {
    s32 index;

    if (func_8016A01C(ctxt)) {
        return -1;
    }
    collisionAddATFuncs[shape->shape](ctxt, shape);

    if (shape->actor != NULL && shape->actor->update == NULL) {
        return -1;
    }
    if (colCtxt->colATCount >= ARRAY_COUNT(colCtxt->colAT)) {
        return -1;
    }
    if (colCtxt->flags & 1) {
        return -1;
    }
    index = colCtxt->colATCount;

    colCtxt->colAT[colCtxt->colATCount] = shape;
    colCtxt->colATCount++;

    return index;
}

s32 Collision_AddIndexAT(GlobalContext *ctxt, CollisionCheckContext *colCtxt, Collider *shape, s32 index) {
    if (func_8016A01C(ctxt)) {
        return -1;
    }
    collisionAddATFuncs[shape->shape](ctxt, shape);

    if (shape->actor != NULL && shape->actor->update == NULL) {
        return -1;
    }
    if (colCtxt->flags & 1) {
        if (index >= colCtxt->colATCount) {
            return -1;
        }
        colCtxt->colAT[index] = shape;
    } else {
        if (colCtxt->colATCount >= ARRAY_COUNT(colCtxt->colAT)) {
            return -1;
        }
        index = colCtxt->colATCount;

        colCtxt->colAT[colCtxt->colATCount] = shape;
        colCtxt->colATCount++;
    }
    return index;
}

ColChkResetFunc collisionAddACFuncs[] = {
    Collision_ResetSphereGroupForAC,
    Collision_ResetCylinderForAC,
    Collision_ResetTriGroupForAC,
    Collision_ResetQuadForAC,
    Collision_ResetSphereForAC,
};

s32 Collision_AddAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, Collider *shape) {
    s32 index;

    if (func_8016A01C(ctxt)) {
        return -1;
    }
    collisionAddACFuncs[shape->shape](ctxt, shape);

    if (shape->actor != NULL && shape->actor->update == NULL) {
        return -1;
    }
    if (colCtxt->colACCount >= ARRAY_COUNT(colCtxt->colAC)) {
        return -1;
    }
    if (colCtxt->flags & 1) {
        return -1;
    }
    index = colCtxt->colACCount;

    colCtxt->colAC[colCtxt->colACCount] = shape;
    colCtxt->colACCount++;

    return index;
}

// TODO fix capitalization
s32 collision_AddIndexAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, Collider *shape, s32 index) {
    if (func_8016A01C(ctxt)) {
        return -1;
    }
    collisionAddACFuncs[shape->shape](ctxt, shape);

    if (shape->actor != NULL && shape->actor->update == NULL) {
        return -1;
    }
    if (colCtxt->flags & 1) {
        if (index >= colCtxt->colACCount) {
            return -1;
        }
        colCtxt->colAC[index] = shape;
    } else {
        if (colCtxt->colACCount >= ARRAY_COUNT(colCtxt->colAC)) {
            return -1;
        }
        index = colCtxt->colACCount;

        colCtxt->colAC[colCtxt->colACCount] = shape;
        colCtxt->colACCount++;
    }
    return index;
}

ColChkResetFunc collisionAddOTFuncs[] = {
    Collision_ResetSphereGroupForOT,
    Collision_ReseCylinderForOT,
    Collision_ResetTriGroupForOT,
    Collision_ResetQuadForOT,
    Collision_ResetSphereForOT,
};

s32 Collision_AddOT(GlobalContext* ctxt, CollisionCheckContext* colCtxt, Collider* shape) {
    s32 index;

    if (func_8016A01C(ctxt)) {
        return -1;
    }
    collisionAddOTFuncs[shape->shape](ctxt, shape);

    if (shape->actor != NULL && shape->actor->update == NULL) {
        return -1;
    }
    if (colCtxt->colOCCount >= ARRAY_COUNT(colCtxt->colOC)) {
        return -1;
    }
    if (colCtxt->flags & 1) {
        return -1;
    }
    index = colCtxt->colOCCount;

    colCtxt->colOC[colCtxt->colOCCount] = shape;
    colCtxt->colOCCount++;

    return index;
}

s32 Collision_AddIndexOT(GlobalContext *ctxt, CollisionCheckContext *colCtxt, Collider *shape, s32 index) {
    if (func_8016A01C(ctxt)) {
        return -1;
    }
    collisionAddOTFuncs[shape->shape](ctxt, shape);

    if (shape->actor != NULL && shape->actor->update == NULL) {
        return -1;
    }
    if (colCtxt->flags & 1) {
        if (index >= colCtxt->colOCCount) {
            return -1;
        }
        //! @bug should be colOC
        colCtxt->colAT[index] = shape;
    } else {
        if (colCtxt->colOCCount >= ARRAY_COUNT(colCtxt->colOC)) {
            return -1;
        }
        index = colCtxt->colOCCount;

        colCtxt->colOC[colCtxt->colOCCount] = shape;
        colCtxt->colOCCount++;
    }
    return index;
}

// Collision_AddOCLine
s32 Collision_AddGroup4(GlobalContext *ctxt, CollisionCheckContext *colCtxt, OcLine *line) {
    s32 index;

    if (func_8016A01C(ctxt)) {
        return -1;
    }

    func_800E2434(ctxt, line);

    if (colCtxt->colLineCount >= ARRAY_COUNT(colCtxt->colLine)) {
        return -1;
    }
    index = colCtxt->colLineCount;

    colCtxt->colLine[colCtxt->colLineCount] = line;
    colCtxt->colLineCount++;

    return index;
}

s32 Collision_CantBeToucherAC(ColliderInfo *iParm1) {
    if (!(iParm1->toucherFlags & 1)) {
        return 1;
    } else {
        return 0;
    }
}

s32 Collision_CantBeBumperAC(ColliderInfo *iParm1) {
    if (!(iParm1->bumperFlags & 1)) {
        return 1;
    } else {
        return 0;
    }
}

s32 Collision_ToucherIsExcluded(ColliderInfo *toucher, ColliderInfo *bumper) {
    if (!(toucher->toucher.dmgFlags & bumper->bumper.dmgFlags)) {
        return 1;
    } else {
        return 0;
    }
}

void func_800E2C08(GlobalContext* ctxt, Collider* shape, Vec3f* v) {
}

#ifdef NON_MATCHING
// needs in-function static bss
void func_800E2C1C(GlobalContext *ctxt, Collider *shape, Vec3f *v) {
    static EffSparkParams D_801EEC00;
    s32 effectIndex;

    D_801EEC00.position.x = v->x;
    D_801EEC00.position.x = v->y;
    D_801EEC00.position.x = v->z;
    D_801EEC00.particleFactor1 = 5;
    D_801EEC00.particleFactor2 = 5;
    D_801EEC00.colorStart[0].red = 10;
    D_801EEC00.colorStart[0].green = 10;
    D_801EEC00.colorStart[0].blue = 200;
    D_801EEC00.colorStart[0].alpha = 255;
    D_801EEC00.colorStart[1].red = 0;
    D_801EEC00.colorStart[1].green = 0;
    D_801EEC00.colorStart[1].blue = 128;
    D_801EEC00.colorStart[1].alpha = 255;
    D_801EEC00.colorStart[2].red = 0;
    D_801EEC00.colorStart[2].green = 0;
    D_801EEC00.colorStart[2].blue = 128;
    D_801EEC00.colorStart[2].alpha = 255;
    D_801EEC00.colorStart[3].red = 0;
    D_801EEC00.colorStart[3].green = 0;
    D_801EEC00.colorStart[3].blue = 128;
    D_801EEC00.colorStart[3].alpha = 255;
    D_801EEC00.colorEnd[0].red = 0;
    D_801EEC00.colorEnd[0].green = 0;
    D_801EEC00.colorEnd[0].blue = 32;
    D_801EEC00.colorEnd[0].alpha = 0;
    D_801EEC00.colorEnd[1].red = 0;
    D_801EEC00.colorEnd[1].green = 0;
    D_801EEC00.colorEnd[1].blue = 32;
    D_801EEC00.colorEnd[1].alpha = 0;
    D_801EEC00.colorEnd[2].red = 0;
    D_801EEC00.colorEnd[2].green = 0;
    D_801EEC00.colorEnd[2].blue = 64;
    D_801EEC00.colorEnd[2].alpha = 0;
    D_801EEC00.colorEnd[3].red = 0;
    D_801EEC00.colorEnd[3].green = 0;
    D_801EEC00.colorEnd[3].blue = 64;
    D_801EEC00.colorEnd[3].alpha = 0;
    D_801EEC00.age = 0;
    D_801EEC00.duration = 16;
    D_801EEC00.velocity = 8.0f;
    D_801EEC00.gravity = -1.0f;

    Effect_Add(ctxt, &effectIndex, 0, 0, 1, &D_801EEC00);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E2C1C.asm")
#endif

#ifdef NON_MATCHING
// needs in-function static bss
void func_800E2D88(GlobalContext *ctxt, Collider *shape, Vec3f *v) {
    static EffSparkParams D_801EF0C8;
    s32 effectIndex;

    D_801EF0C8.position.x = v->x;
    D_801EF0C8.position.x = v->y;
    D_801EF0C8.position.x = v->z;
    D_801EF0C8.particleFactor1 = 5;
    D_801EF0C8.particleFactor2 = 5;
    D_801EF0C8.colorStart[0].red = 10;
    D_801EF0C8.colorStart[0].green = 200;
    D_801EF0C8.colorStart[0].blue = 10;
    D_801EF0C8.colorStart[0].alpha = 255;
    D_801EF0C8.colorStart[1].red = 0;
    D_801EF0C8.colorStart[1].green = 128;
    D_801EF0C8.colorStart[1].blue = 0;
    D_801EF0C8.colorStart[1].alpha = 255;
    D_801EF0C8.colorStart[2].red = 0;
    D_801EF0C8.colorStart[2].green = 128;
    D_801EF0C8.colorStart[2].blue = 0;
    D_801EF0C8.colorStart[2].alpha = 255;
    D_801EF0C8.colorStart[3].red = 0;
    D_801EF0C8.colorStart[3].green = 128;
    D_801EF0C8.colorStart[3].blue = 0;
    D_801EF0C8.colorStart[3].alpha = 255;
    D_801EF0C8.colorEnd[0].red = 0;
    D_801EF0C8.colorEnd[0].green = 32;
    D_801EF0C8.colorEnd[0].blue = 0;
    D_801EF0C8.colorEnd[0].alpha = 0;
    D_801EF0C8.colorEnd[1].red = 0;
    D_801EF0C8.colorEnd[1].green = 32;
    D_801EF0C8.colorEnd[1].blue = 0;
    D_801EF0C8.colorEnd[1].alpha = 0;
    D_801EF0C8.colorEnd[2].red = 0;
    D_801EF0C8.colorEnd[2].green = 64;
    D_801EF0C8.colorEnd[2].blue = 0;
    D_801EF0C8.colorEnd[2].alpha = 0;
    D_801EF0C8.colorEnd[3].red = 0;
    D_801EF0C8.colorEnd[3].green = 64;
    D_801EF0C8.colorEnd[3].blue = 0;
    D_801EF0C8.colorEnd[3].alpha = 0;
    D_801EF0C8.age = 0;
    D_801EF0C8.duration = 16;
    D_801EF0C8.velocity = 8.0f;
    D_801EF0C8.gravity = -1.0f;
    Effect_Add(ctxt, &effectIndex, 0, 0, 1, &D_801EF0C8);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E2D88.asm")
#endif

void func_800E2EF4(GlobalContext *ctxt, Collider *shape, Vec3f *v) {
    func_800B249C(ctxt, v);
    func_800E8478(ctxt, v);
}

void func_800E2F30(GlobalContext *ctxt, Collider *shape, Vec3f *v) {
    func_800E8318(ctxt, v);
}

void func_800E2F54(GlobalContext *ctxt, Collider *shape, Vec3f *v) {
    func_800E8318(ctxt, v);
}

void func_800E2F78(GlobalContext* ctxt, ColliderInfo* toucherBody, Collider* bumper, Vec3f* hitPos) {
    s32 flags = toucherBody->toucherFlags & 0x18;

    if (flags == 0 && bumper->colType != 9) {
        func_800B2684(ctxt, 0, hitPos);
        if (bumper->actor == NULL) {
            play_sound(0x1806);
        } else {
            func_8019F1C0(&bumper->actor->projectedPos, 0x1806);
        }
    } else if (flags == 0) {
        func_800B2684(ctxt, 3, hitPos);
        if (bumper->actor == NULL) {
            func_800E8668(ctxt, hitPos);
        } else {
            func_800E8690(ctxt, hitPos, &bumper->actor->projectedPos);
        }
    } else if (flags == 8) {
        func_800B2684(ctxt, 0, hitPos);
        if (bumper->actor == NULL) {
            play_sound(0x1806);
        } else {
            func_8019F1C0(&bumper->actor->projectedPos, 0x1806);
        }
    } else if (flags == 0x10) {
        func_800B2684(ctxt, 1, hitPos);
        if (bumper->actor == NULL) {
            play_sound(0x1837);
        } else {
            func_8019F1C0(&bumper->actor->projectedPos, 0x1837);
        }
    }
}

s32 func_800E30C8(Collider* toucher, ColliderInfo* bumperBody) {
    if (toucher->actor != NULL && toucher->actor->type == ACTORTYPE_PLAYER) {
        if (bumperBody->elemType == ELEMTYPE_UNK0) {
            func_8019F1C0(&toucher->actor->projectedPos, 0x1811);
        } else if (bumperBody->elemType == ELEMTYPE_UNK1) {
            func_8019F1C0(&toucher->actor->projectedPos, 0x1824);
        } else if (bumperBody->elemType == ELEMTYPE_UNK2) {
            func_8019F1C0(&toucher->actor->projectedPos, 0);
        } else if (bumperBody->elemType == ELEMTYPE_UNK3) {
            func_8019F1C0(&toucher->actor->projectedPos, 0);
        }
    }
    return 1;
}

ColChkBloodFunc D_801BA374[] = {
    func_800E2C08,
    func_800E2C1C,
    func_800E2D88,
    func_800E2EF4,
    func_800E2F30,
    func_800E2F54,
};

HitInfo D_801BA38C[] = {
    { BLOOD_BLUE,  HIT_WHITE },
    { BLOOD_NONE,  HIT_DUST },
    { BLOOD_GREEN, HIT_DUST },
    { BLOOD_NONE,  HIT_WHITE },
    { BLOOD_WATER, HIT_NONE },
    { BLOOD_NONE,  HIT_RED },
    { BLOOD_GREEN, HIT_WHITE },
    { BLOOD_RED,   HIT_WHITE },
    { BLOOD_BLUE,  HIT_RED },
    { BLOOD_NONE,  HIT_SOLID },
    { BLOOD_NONE,  HIT_NONE },
    { BLOOD_NONE,  HIT_SOLID },
    { BLOOD_NONE,  HIT_SOLID },
    { BLOOD_NONE,  HIT_WOOD },
};

void func_800E3168(GlobalContext *ctxt, Collider *toucher, ColliderInfo *toucherBody, Collider *bumper, ColliderInfo *bumperBody, Vec3f *param_6) {
    if (bumperBody->bumperFlags & 0x40) {
        return;
    }

    if (!(toucherBody->toucherFlags & 0x20) && (toucherBody->toucherFlags & 0x40)) {
        return;
    }

    if (bumper->actor != NULL) {
        D_801BA374[D_801BA38C[bumper->colType].blood](ctxt, bumper, param_6);
    }
    if (bumper->actor != NULL) {
        if (D_801BA38C[bumper->colType].effect == 3) {
            func_800E2F78(ctxt, toucherBody, bumper, param_6);
        } else if (D_801BA38C[bumper->colType].effect == 4) {
            if (toucher->actor == NULL) {
                func_800E85D4(ctxt, param_6);
                play_sound(0x1837);
            } else {
                func_800E86E0(ctxt, param_6, &toucher->actor->projectedPos);
            }
        } else if (D_801BA38C[bumper->colType].effect != 5) {
            func_800B2684(ctxt, D_801BA38C[bumper->colType].effect, param_6);
            if (!(bumperBody->bumperFlags & 0x20)) {
                func_800E30C8(toucher, bumperBody);
            }
        }
    } else {
        func_800B2684(ctxt, 0, param_6);
        if (bumper->actor == NULL) {
            play_sound(0x1806);
        } else {
            func_8019F1C0(&bumper->actor->projectedPos, 0x1806);
        }
    }
}

void func_800E3304(Collider *toucher, Collider *bumper) {
    toucher->atFlags |= 4;
    bumper->acFlags |= 0x80;
}

s32 Collision_HandleCollisionATWithAC(GlobalContext *ctxt, Collider *toucher, ColliderInfo *toucherBody, Vec3f *toucherLoc, Collider *bumper, ColliderInfo *bumperBody, Vec3f *bumperLoc, Vec3f *param_8) {
    f32 damage;
    u32 effect;

    if (Collision_GetToucherDamage(toucher, toucherBody, bumper, bumperBody) != 0) {
        damage = Collision_GetDamageAndEffectOnBumper(toucher, toucherBody, bumper, bumperBody, &effect);
        if (damage < 1.0f) {
            if (effect == 0) {
                return 0;
            }
        } else if (func_800E04BC(damage, bumperBody) < 1.0f && effect == 0) {
            return 0;
        }
    }
    if ((bumper->acFlags & 4) && toucher->actor != NULL && bumper->actor != NULL) {
        func_800E3304(toucher, bumper);
    }
    if (!(bumperBody->bumperFlags & 8)) {
        toucher->atFlags |= 2;
        toucher->at = bumper->actor;
        toucherBody->atHit = bumper;
        toucherBody->toucherFlags |= 2;
        toucherBody->atHitInfo = bumperBody;
        if (!(toucherBody->bumperFlags & 2)) {
            toucherBody->bumper.hitPos.x = param_8->x;
            toucherBody->bumper.hitPos.y = param_8->y;
            toucherBody->bumper.hitPos.z = param_8->z;
        }
        if (toucher->actor != NULL) {
            toucher->actor->colChkInfo.atHitEffect = bumperBody->bumper.effect;
        }
    }
    if (!(toucherBody->ocElemFlags & 4)) {
        bumper->acFlags |= 2;
        bumper->ac = toucher->actor;
        bumperBody->acHit = toucher;
        bumperBody->acHitInfo = toucherBody;
        bumperBody->bumperFlags |= 2;
        if (bumper->actor != NULL) {
            bumper->actor->colChkInfo.acHitEffect = toucherBody->toucher.effect;
        }
        bumperBody->bumper.hitPos.x = param_8->x;
        bumperBody->bumper.hitPos.y = param_8->y;
        bumperBody->bumper.hitPos.z = param_8->z;
    }
    if (!(toucherBody->toucherFlags & 0x20) &&  bumper->colType != 9 && bumper->colType != 0xB && bumper->colType != 0xC) {
        bumperBody->bumperFlags |= 0x80;
    } else {
        func_800E3168(ctxt, toucher, toucherBody, bumper, bumperBody, param_8);
        toucherBody->toucherFlags |= 0x40;
    }
    return 1;
}

void Collision_TriCalcAvgPoint(ColliderTrisElement *tri, Vec3f *avg) {
    f32 temp_f0 = 1.0f / 3.0f;

    avg->x = (tri->dim.vtx[0].x + tri->dim.vtx[1].x + tri->dim.vtx[2].x) * temp_f0;
    avg->y = (tri->dim.vtx[0].y + tri->dim.vtx[1].y + tri->dim.vtx[2].y) * temp_f0;
    avg->z = (tri->dim.vtx[0].z + tri->dim.vtx[1].z + tri->dim.vtx[2].z) * temp_f0;
}

void collision_quad_cal_avg_point(ColliderQuad *quad, Vec3f *avg) {
    avg->x = (quad->dim.quad[0].x + (quad->dim.quad[1].x + (quad->dim.quad[3].x + quad->dim.quad[2].x))) / 4.0f;
    avg->y = (quad->dim.quad[0].y + (quad->dim.quad[1].y + (quad->dim.quad[3].y + quad->dim.quad[2].y))) / 4.0f;
    avg->z = (quad->dim.quad[0].z + (quad->dim.quad[1].z + (quad->dim.quad[3].z + quad->dim.quad[2].z))) / 4.0f;
}

void Collision_SphereGroupWithSphereGroupAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, Collider *toucher, Collider *bumpee) {
    ColliderJntSph* at = (ColliderJntSph*)toucher;
    ColliderJntSphElement* sphElem;
    ColliderJntSph* ac = (ColliderJntSph*)bumpee;
    ColliderJntSphElement* sphElem2;
    f32 sp8C;
    f32 sp88;

    if (at->count > 0 && at->elements != NULL && ac->count > 0 && ac->elements != NULL) {
        for (sphElem = &at->elements[0]; sphElem < &at->elements[at->count]; sphElem++) {
            if (Collision_CantBeToucherAC(&sphElem->info)) {
                continue;
            }

            for (sphElem2 = &ac->elements[0]; sphElem2 < &ac->elements[ac->count]; sphElem2++) {
                if (Collision_CantBeBumperAC(&sphElem2->info)) {
                    continue;
                }
                if (Collision_ToucherIsExcluded(&sphElem->info, &sphElem2->info)) {
                    continue;
                }

                if (Math3D_ColSphereSphereIntersectAndDistance(&sphElem->dim.worldSphere, &sphElem2->dim.worldSphere, &sp8C, &sp88) != 0) {
                    f32 temp_f0;
                    Vec3f sp78;
                    Vec3f sp6C;
                    Vec3f sp60;

                    Math_Vec3s_ToVec3f(&sp6C, &sphElem->dim.worldSphere.center);
                    Math_Vec3s_ToVec3f(&sp60, &sphElem2->dim.worldSphere.center);

                    if (!(fabsf(sp88) < 0.008f)) {
                        temp_f0 = sphElem2->dim.worldSphere.radius / sp88;
                        sp78.x = ((sp6C.x - sp60.x) * temp_f0) + sp60.x;
                        sp78.y = ((sp6C.y - sp60.y) * temp_f0) + sp60.y;
                        sp78.z = ((sp6C.z - sp60.z) * temp_f0) + sp60.z;
                    } else {
                        Math_Vec3f_Copy(&sp78, &sp6C);
                    }

                    Collision_HandleCollisionATWithAC(ctxt, &at->base, &sphElem->info, &sp6C, &ac->base, &sphElem2->info, &sp60, &sp78);

                    if (!(ac->base.ocFlags2 & 0x40)) {
                        return;
                    }
                }
            }
        }
    }
}

void Collision_SphereGroupWithCylinderAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, Collider *toucher, Collider *bumpee) {
    ColliderJntSph* at = (ColliderJntSph*)toucher;
    ColliderJntSphElement *sphElem;
    ColliderCylinder* ac = (ColliderCylinder*)bumpee;
    f32 sp80;
    f32 sp7C;

    if (at->count > 0 && at->elements != NULL && ac->dim.radius > 0 && ac->dim.height > 0) {
        if (Collision_CantBeBumperAC(&ac->info)) {
            return;
        }
        for (sphElem = &at->elements[0]; sphElem < &at->elements[at->count]; sphElem++) {
            if (Collision_CantBeToucherAC(&sphElem->info)) {
                continue;
            }
            if (Collision_ToucherIsExcluded(&sphElem->info, &ac->info)) {
                continue;
            }
            if (Math3D_ColSphereCylinderDistanceAndAmount(&sphElem->dim.worldSphere, &ac->dim, &sp80, &sp7C)) {
                Vec3f sp70;
                Vec3f sp64;
                Vec3f sp58;
                f32 temp_f0;

                Math_Vec3s_ToVec3f(&sp64, &sphElem->dim.worldSphere.center);
                Math_Vec3s_ToVec3f(&sp58, &ac->dim.pos);
                if (!(fabsf(sp7C) < 0.008f)) {
                    temp_f0 = ac->dim.radius / sp7C;
                    if (temp_f0 <= 1.0f) {
                        sp70.x = ((sp64.x - sp58.x) * temp_f0) + sp58.x;
                        sp70.y = ((sp64.y - sp58.y) * temp_f0) + sp58.y;
                        sp70.z = ((sp64.z - sp58.z) * temp_f0) + sp58.z;
                    } else {
                        Math_Vec3f_Copy(&sp70, &sp64);
                    }
                } else {
                    Math_Vec3f_Copy(&sp70, &sp64);
                }
                Collision_HandleCollisionATWithAC(ctxt, &at->base, &sphElem->info, &sp64, &ac->base, &ac->info, &sp58, &sp70);
                return;
            }
        }
    }
}

void Collision_SphereGroupWithTriGroupAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, Collider *toucher, Collider *bumpee) {
    ColliderJntSph *at = (ColliderJntSph*)toucher;
    ColliderJntSphElement *sphElem;
    ColliderTris *ac = (ColliderTris*)bumpee;
    ColliderTrisElement *triElem;
    Vec3f sp6C;

    if (at->count > 0 && at->elements != NULL && ac->count > 0 && ac->elements != NULL) {
        for (sphElem = &at->elements[0]; sphElem < &at->elements[at->count]; sphElem++) {
            if (Collision_CantBeToucherAC(&sphElem->info)) {
                continue;
            }
            for (triElem = ac->elements; triElem < &ac->elements[ac->count]; triElem++) {
                if (Collision_CantBeBumperAC(&triElem->info)) {
                    continue;
                }
                if (Collision_ToucherIsExcluded(&sphElem->info, &triElem->info)) {
                    continue;
                }
                if (Math3D_ColSphereTri(&sphElem->dim.worldSphere, &triElem->dim, &sp6C) != 0) {
                    Vec3f sp60;
                    Vec3f sp54;

                    Math_Vec3s_ToVec3f(&sp60, &sphElem->dim.worldSphere.center);
                    Collision_TriCalcAvgPoint(triElem, &sp54);
                    Collision_HandleCollisionATWithAC(ctxt, &at->base, &sphElem->info, &sp60, &ac->base, &triElem->info, &sp54, &sp6C);
                    return;
                }
            }
        }
    }
}

void Collision_SphereGroupWithQuadAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, Collider *toucher, Collider *bumpee) {
    ColliderJntSph* at = (ColliderJntSph*)toucher;
    ColliderQuad *ac = (ColliderQuad*)bumpee;
    Vec3f sp74;
    ColliderJntSphElement *sphElem;

    if (at->count > 0 && at->elements != NULL) {
        if (Collision_CantBeBumperAC(&ac->info)) {
            return;
        }
        Math3D_TriSetCoords(&D_801EF590, &ac->dim.quad[2], &ac->dim.quad[3], &ac->dim.quad[1]);
        Math3D_TriSetCoords(&D_801EF5C8, &ac->dim.quad[1], &ac->dim.quad[0], &ac->dim.quad[2]);

        for (sphElem = &at->elements[0]; sphElem < &at->elements[at->count]; sphElem++) {
            if (Collision_CantBeToucherAC(&sphElem->info)) {
                continue;
            }
            if (Collision_ToucherIsExcluded(&sphElem->info, &ac->info)) {
                continue;
            }
            if (Math3D_ColSphereTri(&sphElem->dim.worldSphere, &D_801EF590, &sp74) != 0 || 
                Math3D_ColSphereTri(&sphElem->dim.worldSphere, &D_801EF5C8, &sp74) != 0) {
                Vec3f sp64;
                Vec3f sp58;

                Math_Vec3s_ToVec3f(&sp64, &sphElem->dim.worldSphere.center);
                collision_quad_cal_avg_point(ac, &sp58);
                Collision_HandleCollisionATWithAC(ctxt, &at->base, &sphElem->info, &sp64, &ac->base, &ac->info, &sp58, &sp74);
                return;
            }
        }
    }
}

void Collision_SphereGroupWithSphereAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, Collider *toucher, Collider *bumpee) {
    ColliderJntSph* at = (ColliderJntSph*)toucher;
    ColliderSphere* ac = (ColliderSphere*)bumpee;
    ColliderJntSphElement *sphElem;
    f32 sp90;
    f32 sp8C;

    if (at->count > 0 && at->elements != NULL) {
        if (Collision_CantBeBumperAC(&ac->info)) {
            return;
        }
        for (sphElem = &at->elements[0]; sphElem < &at->elements[at->count]; sphElem++) {
            if (Collision_CantBeToucherAC(&sphElem->info)) {
                continue;
            }
            if (Collision_ToucherIsExcluded(&sphElem->info, &ac->info)) {
                continue;
            }
            if (Math3D_ColSphereSphereIntersectAndDistance(&sphElem->dim.worldSphere, &ac->dim.worldSphere, &sp90, &sp8C) != 0) {
                f32 temp_f0;
                Vec3f sp7C;
                Vec3f sp70;
                Vec3f sp64;

                Math_Vec3s_ToVec3f(&sp70, &sphElem->dim.worldSphere.center);
                Math_Vec3s_ToVec3f(&sp64, &ac->dim.worldSphere.center);
                if (!(fabsf(sp8C) < 0.008f)) {
                    temp_f0 = ac->dim.worldSphere.radius / sp8C;
                    sp7C.x = ((sp70.x - sp64.x) * temp_f0) + sp64.x;
                    sp7C.y = ((sp70.y - sp64.y) * temp_f0) + sp64.y;
                    sp7C.z = ((sp70.z - sp64.z) * temp_f0) + sp64.z;
                } else {
                    Math_Vec3f_Copy(&sp7C, &sp70);
                }
                Collision_HandleCollisionATWithAC(ctxt, &at->base, &sphElem->info, &sp70, &ac->base, &ac->info, &sp64, &sp7C);
            }
        }
    }
}

void Collision_CylinderWithSphereGroupAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, Collider *toucher, Collider *bumpee) {
    ColliderCylinder* at = (ColliderCylinder*)toucher;
    ColliderJntSph* ac = (ColliderJntSph*)bumpee;
    f32 sp9C;
    f32 sp98;
    f32 temp_f0;
    Vec3f sp88;
    Vec3f sp7C;
    Vec3f sp70;
    Sphere16 *temp_s0; // TODO remove
    ColliderJntSphElement *sphElem;

    if (ac->count > 0 && ac->elements != NULL && at->dim.radius > 0 && at->dim.height > 0) {
        if (Collision_CantBeToucherAC(&at->info)) {
            return;
        }
        for (sphElem = &ac->elements[0]; sphElem < &ac->elements[ac->count]; sphElem++) {
            if (Collision_CantBeBumperAC(&sphElem->info)) {
                continue;
            }
            if (Collision_ToucherIsExcluded(&at->info, &sphElem->info)) {
                continue;
            }
            if (Math3D_ColSphereCylinderDistanceAndAmount(&sphElem->dim.worldSphere, &at->dim, &sp9C, &sp98) != 0) {

                Math_Vec3s_ToVec3f(&sp7C, &at->dim.pos);
                Math_Vec3s_ToVec3f(&sp70, &sphElem->dim.worldSphere.center);
                if (!(fabsf(sp98) < 0.008f)) {
                    temp_f0 = sphElem->dim.worldSphere.radius / sp98;
                    if (temp_f0 <= 1.0f) {
                        sp88.x = ((sp7C.x - sp70.x) * temp_f0) + sp70.x;
                        sp88.y = ((sp7C.y - sp70.y) * temp_f0) + sp70.y;
                        sp88.z = ((sp7C.z - sp70.z) * temp_f0) + sp70.z;
                    } else {
                        Math_Vec3f_Copy(&sp88, &sp7C);
                    }
                } else {
                    Math_Vec3f_Copy(&sp88, &sp7C);
                }
                Collision_HandleCollisionATWithAC(ctxt, &at->base, &at->info, &sp7C, &ac->base, &sphElem->info, &sp70, &sp88);
                if (!(ac->base.ocFlags2 & 0x40)) {
                    break;
                }
            }
        }
    }
}

void Collision_CylinderWithCylinderAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, Collider *toucher, Collider *bumpee) {
    ColliderCylinder* at = (ColliderCylinder*)toucher;
    ColliderCylinder* ac = (ColliderCylinder*)bumpee;
    f32 sp6C;
    f32 sp68;
    Vec3f sp5C;

    if (at->dim.radius > 0 && at->dim.height > 0 && ac->dim.radius > 0 && ac->dim.height > 0) {
        if (Collision_CantBeBumperAC(&ac->info)) {
            return;
        }
        if (Collision_CantBeToucherAC(&at->info)) {
            return;
        }
        if (Collision_ToucherIsExcluded(&at->info, &ac->info)) {
            return;
        }

        if (Math3D_ColCylinderCylinderAmountAndDistance(&at->dim, &ac->dim, &sp6C, &sp68) != 0) {
            Vec3f sp50;
            Vec3f sp44;

            Math_Vec3s_ToVec3f(&sp50, &at->dim.pos);
            Math_Vec3s_ToVec3f(&sp44, &ac->dim.pos);
            if (!(fabsf(sp68) < 0.008f)) {
                f32 temp_f12 = ac->dim.radius / sp68;
                f32 tmp;

                sp5C.y = (f32)at->dim.pos.y + at->dim.yShift + at->dim.height * 0.5f;
                tmp = (f32)ac->dim.pos.y + ac->dim.yShift;

                if (sp5C.y < tmp) {
                    sp5C.y = tmp;
                } else {
                    tmp += ac->dim.height;
                    if (sp5C.y > tmp) {
                        sp5C.y = tmp;
                    }
                }
                sp5C.x = ((f32)at->dim.pos.x - ac->dim.pos.x) * temp_f12 + ac->dim.pos.x;
                sp5C.z = ((f32)at->dim.pos.z - ac->dim.pos.z) * temp_f12 + ac->dim.pos.z;
            } else {
                Math_Vec3s_ToVec3f(&sp5C, &ac->dim.pos);
            }
            Collision_HandleCollisionATWithAC(ctxt, &at->base, &at->info, &sp50, &ac->base, &ac->info, &sp44, &sp5C);
        }
    }
}

void Collision_CylinderWithTriGroupAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, Collider *toucher, Collider *bumpee) {
    ColliderCylinder* at = (ColliderCylinder*)toucher;
    ColliderTris* ac = (ColliderTris*)bumpee;
    ColliderTrisElement *triElem;
    Vec3f sp60;

    if (at->dim.radius > 0 && at->dim.height > 0 && ac->count > 0 && ac->elements != NULL) {
        if (Collision_CantBeToucherAC(&at->info)) {
            return;
        }
        
        for (triElem = &ac->elements[0]; triElem < &ac->elements[ac->count]; triElem++) {
            if (Collision_CantBeBumperAC(&triElem->info)) {
                continue;
            }
            if (Collision_ToucherIsExcluded(&at->info, &triElem->info)) {
                continue;
            }

            if (Math3D_ColCylinderTri(&at->dim, &triElem->dim, &sp60) != 0) {
                Vec3f sp54;
                Vec3f sp48;

                Math_Vec3s_ToVec3f(&sp54, &at->dim.pos);
                Collision_TriCalcAvgPoint(triElem, &sp48);
                Collision_HandleCollisionATWithAC(ctxt, &at->base, &at->info, &sp54, &ac->base, &triElem->info, &sp48, &sp60);
                return;
            }
        }
    }
}

void Collision_CylinderWithQuadAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, Collider *toucher, Collider *bumpee) {
    ColliderCylinder* at = (ColliderCylinder*)toucher;
    ColliderQuad* ac = (ColliderQuad*)bumpee;
    Vec3f sp64;
    Vec3f sp58;
    Vec3f sp4C;
    Vec3f sp40;

    if (at->dim.height > 0 && at->dim.radius > 0) {
        if (Collision_CantBeToucherAC(&at->info)) {
            return;
        }
        if (Collision_CantBeBumperAC(&ac->info)) {
            return;
        }
        if (Collision_ToucherIsExcluded(&at->info, &ac->info)) {
            return;
        }

        Math3D_TriSetCoords(&D_801EF600, &ac->dim.quad[2], &ac->dim.quad[3], &ac->dim.quad[1]);
        Math3D_TriSetCoords(&D_801EF638, &ac->dim.quad[1], &ac->dim.quad[0], &ac->dim.quad[2]);
        if (Math3D_ColCylinderTri(&at->dim, &D_801EF600, &D_801EDE00) != 0) {
            Math_Vec3s_ToVec3f(&sp64, &at->dim.pos);
            collision_quad_cal_avg_point(ac, &sp58);
            Collision_HandleCollisionATWithAC(ctxt, &at->base, &at->info, &sp64, &ac->base, &ac->info, &sp58, &D_801EDE00);
        } else if (Math3D_ColCylinderTri(&at->dim, &D_801EF638, &D_801EDE00) != 0) {
            Math_Vec3s_ToVec3f(&sp4C, &at->dim.pos);
            collision_quad_cal_avg_point(ac, &sp40);
            Collision_HandleCollisionATWithAC(ctxt, &at->base, &at->info, &sp4C, &ac->base, &ac->info, &sp40, &D_801EDE00);
        }
    }
}

void Collision_CylinderWithSphereAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, Collider *toucher, Collider *bumpee) {
    ColliderCylinder* at = (ColliderCylinder*)toucher;
    ColliderSphere* ac = (ColliderSphere*)bumpee;
    f32 sp6C;
    f32 sp68;

    if (at->dim.radius > 0 && at->dim.height > 0) {
        if (Collision_CantBeToucherAC(&at->info)) {
            return;
        }
        if (Collision_CantBeBumperAC(&ac->info)) {
            return;
        }
        if (Collision_ToucherIsExcluded(&at->info, &ac->info)) {
            return;
        }

        if (Math3D_ColSphereCylinderDistanceAndAmount(&ac->dim.worldSphere, &at->dim, &sp6C, &sp68) != 0) {
            Vec3f sp5C;
            Vec3f sp50;
            Vec3f sp44;
            f32 temp_f0;

            Math_Vec3s_ToVec3f(&sp50, &at->dim.pos);
            Math_Vec3s_ToVec3f(&sp44, &ac->dim.worldSphere.center);

            if (!(fabsf(sp68) < 0.008f)) {
                temp_f0 = ac->dim.worldSphere.radius / sp68;
                if (temp_f0 <= 1.0f) {
                    sp5C.x = ((sp50.x - sp44.x) * temp_f0) + sp44.x;
                    sp5C.y = ((sp50.y - sp44.y) * temp_f0) + sp44.y;
                    sp5C.z = ((sp50.z - sp44.z) * temp_f0) + sp44.z;
                } else {
                    Math_Vec3f_Copy(&sp5C, &sp50);
                }
            } else {
                Math_Vec3f_Copy(&sp5C, &sp50);
            }
            Collision_HandleCollisionATWithAC(ctxt, &at->base, &at->info, &sp50, &ac->base, &ac->info, &sp44, &sp5C);
        }
    }
}

void Collision_TriGroupWithSphereGroupAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, Collider *toucher, Collider *bumpee) {
    ColliderTris* at = (ColliderTris*)toucher;
    ColliderJntSphElement *sphElem;
    ColliderJntSph* ac = (ColliderJntSph*)bumpee;
    ColliderTrisElement *triElem;
    Vec3f sp74;

    if (ac->count > 0 && ac->elements != 0 && at->count > 0 && at->elements != 0) {
        for (sphElem = &ac->elements[0]; sphElem < &ac->elements[ac->count]; sphElem++) {
            if (Collision_CantBeBumperAC(&sphElem->info)) {
                continue;
            }
            for (triElem = &at->elements[0]; triElem < &at->elements[at->count]; triElem++) {
                if (Collision_CantBeToucherAC(&triElem->info)) {
                    continue;
                }
                if (Collision_ToucherIsExcluded(&triElem->info, &sphElem->info)) {
                    continue;
                }
                if (Math3D_ColSphereTri(&sphElem->dim.worldSphere, &triElem->dim, &sp74)) {
                    Vec3f sp68;
                    Vec3f sp5C;

                    Math_Vec3s_ToVec3f(&sp5C, &sphElem->dim.worldSphere.center);
                    Collision_TriCalcAvgPoint(triElem, &sp68);
                    Collision_HandleCollisionATWithAC(ctxt, &at->base, &triElem->info, &sp68, &ac->base, &sphElem->info, &sp5C, &sp74);

                    if (!(ac->base.ocFlags2 & 0x40)) {
                        return;
                    }
                }
            }
        }
    }
}

void Collision_TriGroupWithCylinderAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, Collider *toucher, Collider *bumpee) {
    ColliderTris* at = (ColliderTris*)toucher;
    ColliderCylinder* ac = (ColliderCylinder*)bumpee;
    ColliderTrisElement *triElem;

    if (ac->dim.radius > 0 && ac->dim.height > 0 && at->count > 0 && at->elements != NULL) {
        if (Collision_CantBeBumperAC(&ac->info)) {
            return;
        }
        for (triElem = &at->elements[0]; triElem < &at->elements[at->count]; triElem++) {
            if (Collision_CantBeToucherAC(&triElem->info)) {
                continue;
            }
            if (Collision_ToucherIsExcluded(&triElem->info, &ac->info)) {
                continue;
            }
            if (Math3D_ColCylinderTri(&ac->dim, &triElem->dim, &D_801EDE10) != 0) {
                Vec3f sp58;
                Vec3f sp4C;

                Collision_TriCalcAvgPoint(triElem, &sp58);
                Math_Vec3s_ToVec3f(&sp4C, &ac->dim.pos);
                Collision_HandleCollisionATWithAC(ctxt, &at->base, &triElem->info, &sp58, &ac->base, &ac->info, &sp4C, &D_801EDE10);
                return;
            }
        }
    }
}

void Collision_TriGroupWithTriGroupAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, Collider *toucher, Collider *bumpee) {
    ColliderTris* at = (ColliderTris*)toucher;
    ColliderTrisElement *triElem;
    ColliderTris* ac = (ColliderTris*)bumpee;
    ColliderTrisElement *triElem2;

    if (ac->count > 0 && ac->elements != NULL && at->count > 0 && at->elements != NULL) {
        for (triElem = &ac->elements[0]; triElem < &ac->elements[ac->count]; triElem++) {
            if (Collision_CantBeBumperAC(&triElem->info)) {
                continue;
            }
            for (triElem2 = &at->elements[0]; triElem2 < &at->elements[at->count]; triElem2++) {
                if (Collision_CantBeToucherAC(&triElem2->info)) {
                    continue;
                }
                if (Collision_ToucherIsExcluded(&triElem2->info, &triElem->info)) {
                    continue;
                }
                if (Math3d_ColTriTri(&triElem2->dim, &triElem->dim, &D_801EDE20) != 0) {
                    Vec3f sp5C;
                    Vec3f sp50;

                    Collision_TriCalcAvgPoint(triElem2, &sp5C);
                    Collision_TriCalcAvgPoint(triElem, &sp50);
                    Collision_HandleCollisionATWithAC(ctxt, &at->base, &triElem2->info, &sp5C, &ac->base, &triElem->info, &sp50, &D_801EDE20);
                    return;
                }
            }
        }
    }
}

void Collision_TriGroupWithQuad(GlobalContext *ctxt, CollisionCheckContext *colCtxt, Collider *toucher, Collider *bumpee) {
    ColliderTris* at = (ColliderTris*)toucher;
    ColliderQuad* ac = (ColliderQuad*)bumpee;
    ColliderTrisElement *triElem;

    if (at->count > 0 && at->elements != NULL) {
        if (Collision_CantBeBumperAC(&ac->info)) {
            return;
        }

        Math3D_TriSetCoords(&D_801EDE40, &ac->dim.quad[2], &ac->dim.quad[3], &ac->dim.quad[1]);
        Math3D_TriSetCoords(&D_801EDE78, &ac->dim.quad[1], &ac->dim.quad[0], &ac->dim.quad[2]);

        for (triElem = &at->elements[0]; triElem < &at->elements[at->count]; triElem++) {
            if (Collision_CantBeToucherAC(&triElem->info)) {
                continue;
            }
            if (Collision_ToucherIsExcluded(&triElem->info, &ac->info)) {
                continue;
            }
            if (Math3d_ColTriTri(&D_801EDE40, &triElem->dim, &D_801EDE30) != 0 ||
                Math3d_ColTriTri(&D_801EDE78, &triElem->dim, &D_801EDE30) != 0) {
                Vec3f sp68;
                Vec3f sp5C;

                Collision_TriCalcAvgPoint(triElem, &sp68);
                collision_quad_cal_avg_point(ac, &sp5C);
                Collision_HandleCollisionATWithAC(ctxt, &at->base, &triElem->info, &sp68, &ac->base, &ac->info, &sp5C, &D_801EDE30);
                return;
            }
        }
    }
}

void Collision_TriGroupWithSphereAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, Collider *toucher, Collider *bumpee) {
    ColliderTris* at = (ColliderTris*)toucher;
    ColliderTrisElement *triElem;
    ColliderSphere* ac = (ColliderSphere*)bumpee;
    Vec3f sp70;

    if (at->count > 0 && at->elements != NULL) {
        if (Collision_CantBeBumperAC(&ac->info)) {
            return;
        }
        for (triElem = &at->elements[0]; triElem < &at->elements[at->count]; triElem++) {
            if (Collision_CantBeToucherAC(&triElem->info)) {
                continue;
            }
            if (Collision_ToucherIsExcluded(&triElem->info, &ac->info)) {
                continue;
            }
            if (Math3D_ColSphereTri(&ac->dim.worldSphere, &triElem->dim, &sp70) != 0) {
                Vec3f sp64;
                Vec3f sp58;

                Math_Vec3s_ToVec3f(&sp58, &ac->dim.worldSphere.center);
                Collision_TriCalcAvgPoint(triElem, &sp64);
                Collision_HandleCollisionATWithAC(ctxt, &at->base, &triElem->info, &sp64, &ac->base, &ac->info, &sp58, &sp70);
            }
        }
    }
}

void Collision_QuadWithSphereGroupAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, Collider *toucher, Collider *bumpee) {
    ColliderJntSphElement *sphElem;
    Vec3f sp80;
    ColliderQuad* at = (ColliderQuad*)toucher;
    ColliderJntSph* ac = (ColliderJntSph*)bumpee;

    if (ac->count > 0 && ac->elements != NULL) {
        if (Collision_CantBeToucherAC(&at->info)) {
            return;
        }
        Math3D_TriSetCoords(&D_801EDEC8, &at->dim.quad[2], &at->dim.quad[3], &at->dim.quad[1]);
        Math3D_TriSetCoords(&D_801EDF00, &at->dim.quad[2], &at->dim.quad[1], &at->dim.quad[0]);

        for (sphElem = &ac->elements[0]; sphElem < &ac->elements[ac->count]; sphElem++) {
            if (Collision_CantBeBumperAC(&sphElem->info)) {
                continue;
            }
            if (Collision_ToucherIsExcluded(&at->info, &sphElem->info)) {
                continue;
            }
            if (Math3D_ColSphereTri(&sphElem->dim.worldSphere, &D_801EDEC8, &sp80) != 0 || Math3D_ColSphereTri(&sphElem->dim.worldSphere, &D_801EDF00, &sp80) != 0) {
                Vec3f sp6C;
                Vec3f sp60;

                if (!func_800E20A4(ctxt, at, &sp80)) {
                    continue;
                }
                Math_Vec3s_ToVec3f(&sp60, &sphElem->dim.worldSphere.center);
                collision_quad_cal_avg_point(at, &sp6C);
                Collision_HandleCollisionATWithAC(ctxt, &at->base, &at->info, &sp6C, &ac->base, &sphElem->info, &sp60, &sp80);

                if (!(ac->base.ocFlags2 & 0x40)) {
                    break;
                }
            }
        }
    }
}

void Collision_QuadWithCylinderAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, Collider *toucher, Collider *bumpee) {
    ColliderQuad* at = (ColliderQuad*)toucher;
    ColliderCylinder* ac = (ColliderCylinder*)bumpee;

    if (ac->dim.height > 0 && ac->dim.radius > 0) {
        if (Collision_CantBeBumperAC(&ac->info)) {
            return;
        }
        if (Collision_CantBeToucherAC(&at->info)) {
            return;
        }
        if (Collision_ToucherIsExcluded(&at->info, &ac->info)) {
            return;
        }

        Math3D_TriSetCoords(&D_801EDF58, &at->dim.quad[2], &at->dim.quad[3], &at->dim.quad[1]);
        Math3D_TriSetCoords(&D_801EDF90, &at->dim.quad[2], &at->dim.quad[1], &at->dim.quad[0]);

        if (Math3D_ColCylinderTri(&ac->dim, &D_801EDF58, &D_801EDFE0) != 0) {
            if (func_800E20A4(ctxt, at, &D_801EDFE0)) {
                Vec3f sp64;
                Vec3f sp58;

                collision_quad_cal_avg_point(at, &sp64);
                Math_Vec3s_ToVec3f(&sp58, &ac->dim.pos);
                Collision_HandleCollisionATWithAC(ctxt, &at->base, &at->info, &sp64, &ac->base, &ac->info, &sp58, &D_801EDFE0);
                return;
            }
        }
        if (Math3D_ColCylinderTri(&ac->dim, &D_801EDF90, &D_801EDFE0) != 0) {
            if (func_800E20A4(ctxt, at, &D_801EDFE0)) {
                Vec3f sp4C;
                Vec3f sp40;

                collision_quad_cal_avg_point(at, &sp4C);
                Math_Vec3s_ToVec3f(&sp40, &ac->dim.pos);
                Collision_HandleCollisionATWithAC(ctxt, &at->base, &at->info, &sp4C, &ac->base, &ac->info, &sp40, &D_801EDFE0);
            }
        }
    }
}

void Collision_QuadWithTriGroupAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, Collider *toucher, Collider *bumpee) {
    ColliderQuad* at = (ColliderQuad*)toucher;
    ColliderTris* ac = (ColliderTris*)bumpee;
    ColliderTrisElement *triElem;

    if (ac->count > 0 && ac->elements != NULL) {
        if (Collision_CantBeToucherAC(&at->info)) {
            return;
        }

        Math3D_TriSetCoords(&D_801EE000, &at->dim.quad[2], &at->dim.quad[3], &at->dim.quad[1]);
        Math3D_TriSetCoords(&D_801EE038, &at->dim.quad[1], &at->dim.quad[0], &at->dim.quad[2]);

        for (triElem = &ac->elements[0]; triElem < &ac->elements[ac->count]; triElem++) {
            if (Collision_CantBeBumperAC(&triElem->info)) {
                continue;
            }
            if (Collision_ToucherIsExcluded(&at->info, &triElem->info)) {
                continue;
            }

            if ((Math3d_ColTriTri(&D_801EE000, &triElem->dim, &D_801EDFF0) != 0) || 
                (Math3d_ColTriTri(&D_801EE038, &triElem->dim, &D_801EDFF0) != 0)) {
                if (func_800E20A4(ctxt, at, &D_801EDFF0)) {
                    Vec3f sp68;
                    Vec3f sp5C;

                    Collision_TriCalcAvgPoint(triElem, &sp5C);
                    collision_quad_cal_avg_point(at, &sp68);
                    Collision_HandleCollisionATWithAC(ctxt, &at->base, &at->info, &sp68, &ac->base, &triElem->info, &sp5C, &D_801EDFF0);
                    return;
                }
            }
        }
    }
}

void Collision_QuadWithQuadAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, Collider *toucher, Collider *bumpee) {
    ColliderQuad* at = (ColliderQuad*)toucher;
    ColliderQuad* ac = (ColliderQuad*)bumpee;
    s32 i;
    s32 j;

    if (Collision_CantBeToucherAC(&at->info)) {
        return;
    }
    if (Collision_CantBeBumperAC(&ac->info)) {
        return;
    }
    if (Collision_ToucherIsExcluded(&at->info, &ac->info)) {
        return;
    }

    Math3D_TriSetCoords(&D_801EE0E8[0], &at->dim.quad[2], &at->dim.quad[3], &at->dim.quad[1]);
    Math3D_TriSetCoords(&D_801EE0E8[1], &at->dim.quad[2], &at->dim.quad[1], &at->dim.quad[0]);
    Math3D_TriSetCoords(&D_801EE070[0], &ac->dim.quad[2], &ac->dim.quad[3], &ac->dim.quad[1]);
    Math3D_TriSetCoords(&D_801EE070[1], &ac->dim.quad[2], &ac->dim.quad[1], &ac->dim.quad[0]);

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            if (Math3d_ColTriTri(&D_801EE0E8[j], &D_801EE070[i], &D_801EE0D8) != 0 && func_800E20A4(ctxt, at, &D_801EE0D8) != 0) {
                Vec3f sp64;
                Vec3f sp58;

                collision_quad_cal_avg_point(at, &sp64);
                collision_quad_cal_avg_point(ac, &sp58);
                Collision_HandleCollisionATWithAC(ctxt, &at->base, &at->info, &sp64, &ac->base, &ac->info, &sp58, &D_801EE0D8);
                return;
            }
        }
    }
}

void Collision_QuadWithSphereAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, Collider *toucher, Collider *bumpee) {
    ColliderQuad* at = (ColliderQuad*)toucher;
    Vec3f sp60;
    ColliderSphere* ac = (ColliderSphere*)bumpee;

    if (Collision_CantBeToucherAC(&at->info)) {
        return;
    }
    if (Collision_CantBeBumperAC(&ac->info) || Collision_ToucherIsExcluded(&at->info, &ac->info)) {
        return;
    }

    Math3D_TriSetCoords(&D_801EE150, &at->dim.quad[2], &at->dim.quad[3], &at->dim.quad[1]);
    Math3D_TriSetCoords(&D_801EE188, &at->dim.quad[2], &at->dim.quad[1], &at->dim.quad[0]);

    if ((Math3D_ColSphereTri(&ac->dim.worldSphere, &D_801EE150, &sp60) != 0) || 
        (Math3D_ColSphereTri(&ac->dim.worldSphere, &D_801EE188, &sp60) != 0)) {
        if (func_800E20A4(ctxt, at, &sp60)) {
            Vec3f sp50;
            Vec3f sp44;

            Math_Vec3s_ToVec3f(&sp44, &ac->dim.worldSphere.center);
            collision_quad_cal_avg_point(at, &sp50);
            Collision_HandleCollisionATWithAC(ctxt, &at->base, &at->info, &sp50, &ac->base, &ac->info, &sp44, &sp60);
        }
    }
}

void Collision_SphereWithSphereGroupAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, Collider *toucher, Collider *bumpee) {
    ColliderSphere* at = (ColliderSphere*)toucher;
    ColliderJntSph* ac = (ColliderJntSph*)bumpee;
    ColliderJntSphElement *sphElem;
    f32 sp90;
    f32 sp8C;

    if (ac->count > 0 && ac->elements != NULL) {
        if (Collision_CantBeToucherAC(&at->info)) {
            return;
        }

        for (sphElem = &ac->elements[0]; sphElem < &ac->elements[ac->count]; sphElem++) {
            if (Collision_CantBeBumperAC(&sphElem->info)) {
                continue;
            }
            if (Collision_ToucherIsExcluded(&at->info, &sphElem->info)) {
                continue;
            }

            if (Math3D_ColSphereSphereIntersectAndDistance(&at->dim.worldSphere, &sphElem->dim.worldSphere, &sp90, &sp8C) != 0) {
                f32 temp_f0;
                Vec3f sp7C;
                Vec3f sp70;
                Vec3f sp64;

                Math_Vec3s_ToVec3f(&sp70, &at->dim.worldSphere.center);
                Math_Vec3s_ToVec3f(&sp64, &sphElem->dim.worldSphere.center);
                if (!(fabsf(sp8C) < 0.008f)) {
                    temp_f0 = sphElem->dim.worldSphere.radius / sp8C;
                    sp7C.x = (sp70.x - sp64.x) * temp_f0 + sp64.x;
                    sp7C.y = (sp70.y - sp64.y) * temp_f0 + sp64.y;
                    sp7C.z = (sp70.z - sp64.z) * temp_f0 + sp64.z;
                } else {
                    Math_Vec3f_Copy(&sp7C, &sp70);
                }
                Collision_HandleCollisionATWithAC(ctxt, &at->base, &at->info, &sp70, &ac->base, &sphElem->info, &sp64, &sp7C);
            }
        }
    }
}

void Collision_SphereWithCylinderAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, Collider *toucher, Collider *bumpee) {
    ColliderCylinder* ac = (ColliderCylinder*)bumpee;
    ColliderSphere* at = (ColliderSphere*)toucher;
    f32 sp6C;
    f32 sp68;

    if (Collision_CantBeToucherAC(&at->info)) {
        return;
    }
    if (Collision_CantBeBumperAC(&ac->info)) {
        return;
    }
    if (Collision_ToucherIsExcluded(&at->info, &ac->info)) {
        return;
    }

    if (Math3D_ColSphereCylinderDistanceAndAmount(&at->dim.worldSphere, &ac->dim, &sp6C, &sp68) != 0) {
        Vec3f sp5C;
        Vec3f sp50;
        Vec3f sp44;

        Math_Vec3s_ToVec3f(&sp50, &at->dim.worldSphere.center);
        Math_Vec3s_ToVec3f(&sp44, &ac->dim.pos);

        if (!(fabsf(sp68) < 0.008f)) {
            f32 temp_f0 = ac->dim.radius / sp68;

            if (temp_f0 <= 1.0f) {
                sp5C.x = (sp50.x - sp44.x) * temp_f0 + sp44.x;
                sp5C.y = (sp50.y - sp44.y) * temp_f0 + sp44.y;
                sp5C.z = (sp50.z - sp44.z) * temp_f0 + sp44.z;
            } else {
                Math_Vec3f_Copy(&sp5C, &sp50);
            }
        } else {
            Math_Vec3f_Copy(&sp5C, &sp50);
        }
        Collision_HandleCollisionATWithAC(ctxt, &at->base, &at->info, &sp50, &ac->base, &ac->info, &sp44, &sp5C);
    }

    if (at) {}
}

void Collision_SphereWithTriGroupAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, Collider *toucher, Collider *bumpee) {
    ColliderSphere* at = (ColliderSphere*)toucher;
    ColliderTris* ac = (ColliderTris*)bumpee;
    ColliderTrisElement *triElem;
    Vec3f sp68;

    if (Collision_CantBeToucherAC(&at->info)) {
        return;
    }

    for (triElem = &ac->elements[0]; triElem < &ac->elements[ac->count]; triElem++) {
        if (Collision_CantBeBumperAC(&triElem->info)) {
            continue;
        }
        if (Collision_ToucherIsExcluded(&at->info, &triElem->info)) {
            continue;
        }
        if (Math3D_ColSphereTri(&at->dim.worldSphere, &triElem->dim, &sp68) != 0) {
            Vec3f sp5C;
            Vec3f sp50;

            Math_Vec3s_ToVec3f(&sp5C, &at->dim.worldSphere.center);
            Collision_TriCalcAvgPoint(triElem, &sp50);
            Collision_HandleCollisionATWithAC(ctxt, &at->base, &at->info, &sp5C, &ac->base, &triElem->info, &sp50, &sp68);
            return;
        }
    }
}

void Collision_SphereWithQuadAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, Collider *toucher, Collider *bumpee) {
    ColliderSphere* at = (ColliderSphere*)toucher;
    Vec3f sp60;
    ColliderQuad* ac = (ColliderQuad*)bumpee;

    if (Collision_CantBeToucherAC(&at->info)) {
        return;
    }
    if (Collision_CantBeBumperAC(&ac->info) || Collision_ToucherIsExcluded(&at->info, &ac->info)) {
        return;
    }

    Math3D_TriSetCoords(&D_801EE6C8, &ac->dim.quad[2], &ac->dim.quad[3], &ac->dim.quad[1]);
    Math3D_TriSetCoords(&D_801EE700, &ac->dim.quad[1], &ac->dim.quad[0], &ac->dim.quad[2]);

    if (Math3D_ColSphereTri(&at->dim.worldSphere, &D_801EE6C8, &sp60) != 0 || 
        Math3D_ColSphereTri(&at->dim.worldSphere, &D_801EE700, &sp60) != 0) {
        Vec3f sp50;
        Vec3f sp44;

        Math_Vec3s_ToVec3f(&sp50, &at->dim.worldSphere.center);
        collision_quad_cal_avg_point(ac, &sp44);
        Collision_HandleCollisionATWithAC(ctxt, &at->base, &at->info, &sp50, &ac->base, &ac->info, &sp44, &sp60);
    }
}

void Collision_SphereWithSphereAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, Collider *toucher, Collider *bumpee) {
    ColliderSphere* at = (ColliderSphere*)toucher;
    ColliderSphere* ac = (ColliderSphere*)bumpee;
    f32 sp6C;
    f32 sp68;

    if (Collision_CantBeToucherAC(&at->info)) {
        return;
    }
    if (Collision_CantBeBumperAC(&ac->info)) {
        return;
    }
    if (Collision_ToucherIsExcluded(&at->info, &ac->info)) {
        return;
    }

    if (Math3D_ColSphereSphereIntersectAndDistance(&at->dim.worldSphere, &ac->dim.worldSphere, &sp6C, &sp68) != 0) {
        f32 temp_f0;
        Vec3f sp58;
        Vec3f sp4C;
        Vec3f sp40;

        Math_Vec3s_ToVec3f(&sp4C, &at->dim.worldSphere.center);
        Math_Vec3s_ToVec3f(&sp40, &ac->dim.worldSphere.center);
        if (!(fabsf(sp68) < 0.008f)) {
            temp_f0 = ac->dim.worldSphere.radius / sp68;
            sp58.x = (sp4C.x - sp40.x) * temp_f0 + sp40.x;
            sp58.y = (sp4C.y - sp40.y) * temp_f0 + sp40.y;
            sp58.z = (sp4C.z - sp40.z) * temp_f0 + sp40.z;
        } else {
            Math_Vec3f_Copy(&sp58, &sp4C);
        }
        Collision_HandleCollisionATWithAC(ctxt, &at->base, &at->info, &sp4C, &ac->base, &ac->info, &sp40, &sp58);
    }
}

void func_800E60C0(GlobalContext *ctxt, CollisionCheckContext *colCtxt, Collider *shape) {
    ColliderJntSph *sphereGroup = (ColliderJntSph*)shape;
    ColliderJntSphElement *sphElem;

    for (sphElem = &sphereGroup->elements[0]; sphElem < &sphereGroup->elements[sphereGroup->count]; sphElem++) {
        if ((sphElem->info.bumperFlags & 0x80) && sphElem->info.acHitInfo != 0 && !(sphElem->info.acHitInfo->toucherFlags & 0x40)) {
            Vec3f sp24;

            Math_Vec3s_ToVec3f(&sp24, &sphElem->info.bumper.hitPos);
            func_800E3168(ctxt, sphElem->info.acHit, sphElem->info.acHitInfo, &sphereGroup->base, &sphElem->info, &sp24);
            sphElem->info.acHitInfo->toucherFlags |= 0x40;
            return;
        }
    }
}

void func_800E61A0(GlobalContext *ctxt, CollisionCheckContext *colCtxt, Collider *shape) {
    ColliderCylinder *cylinder = (ColliderCylinder*)shape;

    if ((cylinder->info.bumperFlags & 0x80) && cylinder->info.acHitInfo != 0 && !(cylinder->info.acHitInfo->toucherFlags & 0x40)) {
        Vec3f sp28;

        Math_Vec3s_ToVec3f(&sp28, &cylinder->info.bumper.hitPos);
        func_800E3168(ctxt, cylinder->info.acHit, cylinder->info.acHitInfo, &cylinder->base, &cylinder->info, &sp28);
        cylinder->info.acHitInfo->toucherFlags |= 0x40;
    }
}

void func_800E6238(GlobalContext *ctxt, CollisionCheckContext *colCtxt, Collider *shape) {
    ColliderTris *triGroup = (ColliderTris*)shape;
    ColliderTrisElement *triElem;

    for (triElem = &triGroup->elements[0]; triElem < &triGroup->elements[triGroup->count]; triElem++) {
        if ((triElem->info.bumperFlags & 0x80) && triElem->info.acHitInfo != 0 && !(triElem->info.acHitInfo->toucherFlags & 0x40)) {
            Vec3f sp24;

            Math_Vec3s_ToVec3f(&sp24, &triElem->info.bumper.hitPos);
            func_800E3168(ctxt, triElem->info.acHit, triElem->info.acHitInfo, &triGroup->base, &triElem->info, &sp24);
            triElem->info.acHitInfo->toucherFlags |= 0x40;
            return;
        }
    }
}

void func_800E6320(GlobalContext *ctxt, CollisionCheckContext *colCtxt, Collider *shape) {
    ColliderQuad *quad = (ColliderQuad*)shape;

    if ((quad->info.bumperFlags & 0x80) && quad->info.acHitInfo != 0 && !(quad->info.acHitInfo->toucherFlags & 0x40)) {
        Vec3f sp28;

        Math_Vec3s_ToVec3f(&sp28, &quad->info.bumper.hitPos);
        func_800E3168(ctxt, quad->info.acHit, quad->info.acHitInfo, &quad->base, &quad->info, &sp28);
        quad->info.acHitInfo->toucherFlags |= 0x40;
    }
}

void func_800E63B8(GlobalContext *ctxt, CollisionCheckContext *colCtxt, Collider *shape) {
    ColliderSphere* sphere = (ColliderSphere*)shape;

    if ((sphere->info.bumperFlags & 0x80) && sphere->info.acHitInfo != 0 && !(sphere->info.acHitInfo->toucherFlags & 0x40)) {
        Vec3f sp28;

        Math_Vec3s_ToVec3f(&sp28, &sphere->info.bumper.hitPos);
        func_800E3168(ctxt, sphere->info.acHit, sphere->info.acHitInfo, &sphere->base, &sphere->info, &sp28);
        sphere->info.acHitInfo->toucherFlags |= 0x40;
    }
}

ColChkApplyFunc D_801BA3A8[] = {
    func_800E60C0,
    func_800E61A0,
    func_800E6238,
    func_800E6320,
    func_800E63B8,
};

void func_800E6450(GlobalContext *ctxt, CollisionCheckContext *colCtxt) {
    Collider **col;

    for (col = &colCtxt->colAC[0]; col < &colCtxt->colAC[colCtxt->colACCount]; col++) {
        Collider* colAC = *col;

        if (colAC != NULL && (colAC->acFlags & 1)) {
            if (colAC->actor != NULL && colAC->actor->update == NULL) {
                continue;
            }
            D_801BA3A8[colAC->shape](ctxt, colCtxt, colAC);
        }
    }
}

ColChkVsFunc collisionFuncTableATwithAC[5][5] = {
    { Collision_SphereGroupWithSphereGroupAC, Collision_SphereGroupWithCylinderAC, Collision_SphereGroupWithTriGroupAC, Collision_SphereGroupWithQuadAC, Collision_SphereGroupWithSphereAC },
    { Collision_CylinderWithSphereGroupAC, Collision_CylinderWithCylinderAC, Collision_CylinderWithTriGroupAC, Collision_CylinderWithQuadAC, Collision_CylinderWithSphereAC },
    { Collision_TriGroupWithSphereGroupAC, Collision_TriGroupWithCylinderAC, Collision_TriGroupWithTriGroupAC, Collision_TriGroupWithQuad, Collision_TriGroupWithSphereAC },
    { Collision_QuadWithSphereGroupAC, Collision_QuadWithCylinderAC, Collision_QuadWithTriGroupAC, Collision_QuadWithQuadAC, Collision_QuadWithSphereAC },
    { Collision_SphereWithSphereGroupAC, Collision_SphereWithCylinderAC, Collision_SphereWithTriGroupAC, Collision_SphereWithQuadAC, Collision_SphereWithSphereAC },
};

void Collision_CollideWithAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, Collider *colObj) {
    Collider **col;

    for (col = &colCtxt->colAC[0]; col < &colCtxt->colAC[colCtxt->colACCount]; col++) {
        Collider* colAC = *col;

        if (colAC != NULL && (colAC->acFlags & 1)) {
            if (colAC->actor != NULL && colAC->actor->update == NULL) {
                continue;
            }
            if ((colAC->acFlags & colObj->atFlags & 0x38) && colObj != colAC) {
                if (!(colObj->atFlags & 0x40) && colObj->actor != NULL && colAC->actor == colObj->actor) {
                    continue;
                }
                collisionFuncTableATwithAC[colObj->shape][colAC->shape](ctxt, colCtxt, colObj, colAC);
            }
        }
    }
}

void Collision_DoATWithAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt) {
    Collider **col;

    if (colCtxt->colATCount == 0 || colCtxt->colACCount == 0) {
        return;
    }

    for (col = &colCtxt->colAT[0]; col < &colCtxt->colAT[colCtxt->colATCount]; col++) {
        Collider* colAC = *col;

        if (colAC != NULL && (colAC->atFlags & 1)) {
            if (colAC->actor != NULL && colAC->actor->update == NULL) {
                continue;
            }
            Collision_CollideWithAC(ctxt, colCtxt, colAC);
        }
    }

    func_800E6450(ctxt, colCtxt);
}

s32 func_800E6724(u8 mass) {
    if (mass == 0xFF) {
        return 0;
    }
    if (mass == 0xFE) {
        return 1;
    }
    return 2;
}

void Collision_HandleCollisionOTWithOT(GlobalContext *ctxt, Collider *toucher, ColliderInfo *toucherBody, 
                                Vec3f *toucherLoc, Collider *bumper, ColliderInfo *bumperBody, Vec3f *bumperLoc, f32 param_8) {
    f32 pad;
    f32 leftDispRatio;
    f32 rightDispRatio;
    f32 xzDist;
    f32 leftMass;
    f32 rightMass;
    f32 totalMass;
    f32 inverseTotalMass;
    f32 xDelta;
    f32 zDelta;
    Actor *toucherActor = toucher->actor;
    Actor *bumperActor = bumper->actor;
    s32 leftMassType;
    s32 rightMassType;

    toucher->ocFlags1 |= 2;
    toucher->oc = bumperActor;
    toucherBody->ocElemFlags |= 2;
    if (bumper->ocFlags2 & 8) {
        toucher->ocFlags2 |= 1;
    }

    bumper->ocFlags1 |= 2;
    bumper->oc = toucherActor;
    bumperBody->ocElemFlags |= 2;
    if (toucher->ocFlags2 & 8) {
        bumper->ocFlags2 |= 1;
    }

    if (toucherActor == NULL || bumperActor == NULL || (toucher->ocFlags1 & 4) || (bumper->ocFlags1 & 4)) {
        return;
    }

    rightMassType = func_800E6724(toucherActor->colChkInfo.mass);
    leftMassType = func_800E6724(bumperActor->colChkInfo.mass);
    leftMass = toucherActor->colChkInfo.mass;
    rightMass = bumperActor->colChkInfo.mass;
    totalMass = leftMass + rightMass;

    if (fabsf(totalMass) < 0.008f) {
        leftMass = rightMass = 1.0f;
        totalMass = 2.0f;
    }
    xDelta = bumperLoc->x - toucherLoc->x;
    zDelta = bumperLoc->z - toucherLoc->z;

    xzDist = sqrtf(SQ(xDelta) + SQ(zDelta));

    if (rightMassType == 0) {
        if (leftMassType == 0) {
            return;
        } else {
            leftDispRatio = 0;
            rightDispRatio = 1;
        }
    } else if (rightMassType == 1) {
        if (leftMassType == 0) {
            leftDispRatio = 1;
            rightDispRatio = 0;
        } else if (leftMassType == 1) {
            leftDispRatio = 0.5f;
            rightDispRatio = 0.5f;
        } else {
            leftDispRatio = 0;
            rightDispRatio = 1;
        }
    } else {
        if (leftMassType == 2) {
            inverseTotalMass = 1.0f / totalMass;
            leftDispRatio = rightMass * inverseTotalMass;
            rightDispRatio = leftMass * inverseTotalMass;
        } else {
            leftDispRatio = 1;
            rightDispRatio = 0;
        }
    }

    if (!(fabsf(xzDist) < 0.008f)) {
        xDelta *= param_8 / xzDist;
        zDelta *= param_8 / xzDist;
        toucherActor->colChkInfo.displacement.x += -xDelta * leftDispRatio;
        toucherActor->colChkInfo.displacement.z += -zDelta * leftDispRatio;
        bumperActor->colChkInfo.displacement.x += xDelta * rightDispRatio;
        bumperActor->colChkInfo.displacement.z += zDelta * rightDispRatio;
    } else if (param_8 != 0.0f) {
        toucherActor->colChkInfo.displacement.x += -param_8 * leftDispRatio;
        bumperActor->colChkInfo.displacement.x += param_8 * rightDispRatio;
    } else {
        toucherActor->colChkInfo.displacement.x += -leftDispRatio;
        bumperActor->colChkInfo.displacement.x += rightDispRatio;
    }
}

void Collision_SphereGroupWithSphereGroupOT(GlobalContext *ctxt, CollisionCheckContext *colCtxt, Collider *toucher, Collider *bumpee) {
    ColliderJntSph* left = (ColliderJntSph*)toucher;
    ColliderJntSph* right = (ColliderJntSph*)bumpee;
    ColliderJntSphElement *sphElem;
    ColliderJntSphElement *sphElem2;
    f32 sp74;

    if (left->count > 0 && left->elements != NULL && right->count > 0 && right->elements != NULL && 
        (left->base.ocFlags1 & 1) && (right->base.ocFlags1 & 1)) {

        for (sphElem = &left->elements[0]; sphElem < &left->elements[left->count]; sphElem++) {
            if (!(sphElem->info.ocElemFlags & 1)) {
                continue;
            }
            for (sphElem2 = &right->elements[0]; sphElem2 < &right->elements[right->count]; sphElem2++) {
                if (!(sphElem2->info.ocElemFlags & 1)) {
                    continue;
                }
                if (Math3D_ColSphereSphereIntersect(&sphElem->dim.worldSphere, &sphElem2->dim.worldSphere, &sp74) != 0) {
                    Vec3f sp68;
                    Vec3f sp5C;

                    Math_Vec3s_ToVec3f(&sp68, &sphElem->dim.worldSphere.center);
                    Math_Vec3s_ToVec3f(&sp5C, &sphElem2->dim.worldSphere.center);
                    Collision_HandleCollisionOTWithOT(ctxt, &left->base, &sphElem->info, &sp68, &right->base, &sphElem2->info, &sp5C, sp74);
                }
            }
        }
    }
}

void Collision_SphereGroupWithCylinderOT(GlobalContext *ctxt, CollisionCheckContext *colCtxt, Collider *toucher, Collider *bumpee) {
    ColliderJntSph* left = (ColliderJntSph*)toucher;
    ColliderCylinder* right = (ColliderCylinder*)bumpee;
    ColliderJntSphElement *sphElem;
    f32 sp78;

    if (left->count > 0 && left->elements != NULL && 
        (left->base.ocFlags1 & 1) && (right->base.ocFlags1 & 1) && (right->info.ocElemFlags & 1)) {

        for (sphElem = &left->elements[0]; sphElem < &left->elements[left->count]; sphElem++) {
            if (!(sphElem->info.ocElemFlags & 1)) {
                continue;
            }
            if (Math3D_ColSphereCylinderDistance(&sphElem->dim.worldSphere, &right->dim, &sp78) != 0) {
                Vec3f sp6C;
                Vec3f sp60;

                Math_Vec3s_ToVec3f(&sp6C, &sphElem->dim.worldSphere.center);
                Math_Vec3s_ToVec3f(&sp60, &right->dim.pos);
                Collision_HandleCollisionOTWithOT(ctxt, &left->base, &sphElem->info, &sp6C, &right->base, &right->info, &sp60, sp78);
            }
        }
    }
}

void Collision_SphereGroupWithSphereOT(GlobalContext *ctxt, CollisionCheckContext *colCtxt, Collider *toucher, Collider *bumpee) {
    ColliderJntSph* left = (ColliderJntSph*)toucher;
    ColliderSphere* right = (ColliderSphere*)bumpee;
    ColliderJntSphElement *sphElem;
    f32 sp78;

    if (left->count > 0 && left->elements != NULL && 
        (left->base.ocFlags1 & 1) && (right->base.ocFlags1 & 1) && (right->info.ocElemFlags & 1)) {

        for (sphElem = &left->elements[0]; sphElem < &left->elements[left->count]; sphElem++) {
            if (!(sphElem->info.ocElemFlags & 1)) {
                continue;
            }
            if (Math3D_ColSphereSphereIntersect(&sphElem->dim.worldSphere, &right->dim.worldSphere, &sp78) != 0) {
                Vec3f sp6C;
                Vec3f sp60;

                Math_Vec3s_ToVec3f(&sp6C, &sphElem->dim.worldSphere.center);
                Math_Vec3s_ToVec3f(&sp60, &right->dim.worldSphere.center);
                Collision_HandleCollisionOTWithOT(ctxt, &left->base, &sphElem->info, &sp6C, &right->base, &right->info, &sp60, sp78);
            }
        }
    }
}

void Collision_CylinderWithSphereGroupOT(GlobalContext *ctxt, CollisionCheckContext *colCtxt, Collider *toucher, Collider *bumpee) {
    Collision_SphereGroupWithCylinderOT(ctxt, colCtxt, bumpee, toucher);
}

void Collision_CylinderWithCylinderOT(GlobalContext *ctxt, CollisionCheckContext *colCtxt, Collider *toucher, Collider *bumpee) {
    ColliderCylinder* left = (ColliderCylinder*)toucher;
    ColliderCylinder* right = (ColliderCylinder*)bumpee;
    f32 sp4C;

    if ((left->base.ocFlags1 & 1) && (right->base.ocFlags1 & 1) && (left->info.ocElemFlags & 1) && (right->info.ocElemFlags & 1)) {
        if (Math3D_ColCylinderCylinderAmount(&left->dim, &right->dim, &sp4C) != 0) {
            Vec3f sp40;
            Vec3f sp34;

            Math_Vec3s_ToVec3f(&sp40, &left->dim.pos);
            Math_Vec3s_ToVec3f(&sp34, &right->dim.pos);
            Collision_HandleCollisionOTWithOT(ctxt, &left->base, &left->info, &sp40, &right->base, &right->info, &sp34, sp4C);
        }
    }
}

void Collision_CylinderWithSphereOT(GlobalContext *ctxt, CollisionCheckContext *colCtxt, Collider *toucher, Collider *bumpee) {
    ColliderCylinder* left = (ColliderCylinder*)toucher;
    ColliderSphere* right = (ColliderSphere*)bumpee;
    f32 sp4C;

    if ((left->base.ocFlags1 & 1) && (left->info.ocElemFlags & 1) && (right->base.ocFlags1 & 1) && (right->info.ocElemFlags & 1)) {
        if (Math3D_ColSphereCylinderDistance(&right->dim.worldSphere, &left->dim,  &sp4C) != 0) {
            Vec3f sp40;
            Vec3f sp34;

            Math_Vec3s_ToVec3f(&sp40, &left->dim.pos);
            Math_Vec3s_ToVec3f(&sp34, &right->dim.worldSphere.center);
            Collision_HandleCollisionOTWithOT(ctxt, &left->base, &left->info, &sp40, &right->base, &right->info, &sp34, sp4C);
        }
    }
}

void Collision_SphereWithSphereGroupOT(GlobalContext *ctxt, CollisionCheckContext *colCtxt, Collider *toucher, Collider *bumpee) {
    Collision_SphereGroupWithSphereOT(ctxt, colCtxt, bumpee, toucher);
}

void Collision_SphereWithCylinderOT(GlobalContext *ctxt, CollisionCheckContext *colCtxt, Collider *toucher, Collider *bumpee) {
    Collision_CylinderWithSphereOT(ctxt, colCtxt, bumpee, toucher);
}

void Collision_SphereWithSphereOT(GlobalContext *ctxt, CollisionCheckContext *colCtxt, Collider *toucher, Collider *bumpee) {
    ColliderSphere* left = (ColliderSphere*)toucher;
    ColliderSphere* right = (ColliderSphere*)bumpee;
    f32 sp54;

    if ((left->base.ocFlags1 & 1) && (left->info.ocElemFlags & 1) && (right->base.ocFlags1 & 1) && (right->info.ocElemFlags & 1)) {
        if (Math3D_ColSphereSphereIntersect(&left->dim.worldSphere, &right->dim.worldSphere,  &sp54) != 0) {
            Vec3f sp48;
            Vec3f sp3C;

            Math_Vec3s_ToVec3f(&sp48, &left->dim.worldSphere.center);
            Math_Vec3s_ToVec3f(&sp3C, &right->dim.worldSphere.center);
            Collision_HandleCollisionOTWithOT(ctxt, &left->base, &left->info, &sp48, &right->base, &right->info, &sp3C, sp54);
        }
    }
}

s32 func_800E7264(Collider *iParm1) {
    if (!(iParm1->ocFlags1 & 1)) {
        return 1;
    } else {
        return 0;
    }
}

s32 func_800E7288(Collider *piParm1, Collider *piParm2) {
    if (!(piParm1->ocFlags1 & piParm2->ocFlags2 & 0x38) || !(piParm1->ocFlags2 & piParm2->ocFlags1 & 0x38) || 
        ((piParm1->ocFlags2 & 2) && (piParm2->ocFlags2 & 4)) ||
        ((piParm2->ocFlags2 & 2) && (piParm1->ocFlags2 & 4))) {
        return 1;
    }
    if (piParm1->actor == piParm2->actor) {
        return 1;
    }
    return 0;
}

ColChkVsFunc collisionFuncTableOTwithOT[5][5] = {
    { Collision_SphereGroupWithSphereGroupOT, Collision_SphereGroupWithCylinderOT, NULL, NULL, Collision_SphereGroupWithSphereOT },
    { Collision_CylinderWithSphereGroupOT, Collision_CylinderWithCylinderOT, NULL, NULL, Collision_CylinderWithSphereOT },
    { NULL, NULL, NULL, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL },
    { Collision_SphereWithSphereGroupOT, Collision_SphereWithCylinderOT, NULL, NULL, Collision_SphereWithSphereOT },
};

void Collision_DoOTWithOT(GlobalContext *ctxt, CollisionCheckContext *colCtxt) {
    Collider** left;
    Collider** right;
    ColChkVsFunc vsFunc;

    for (left = colCtxt->colOC; left < colCtxt->colOC + colCtxt->colOCCount; left++) {
        if (*left == NULL || func_800E7264(*left)) {
            continue;
        }
        for (right = left + 1; right < colCtxt->colOC + colCtxt->colOCCount; right++) {
            if (*right == NULL || func_800E7264(*right) || func_800E7288(*left, *right)) {
                continue;
            }
            vsFunc = collisionFuncTableOTwithOT[(*left)->shape][(*right)->shape];
            if (vsFunc == NULL) {
                continue;
            }
            vsFunc(ctxt, colCtxt, *left, *right);
        }
    }
}

void func_800E7494(CollisionCheckInfo *info) {
    static CollisionCheckInfo D_801BA484 = {
        NULL,
        { 0.0f, 0.0f, 0.0f },
        0x000A,
        0x000A,
        0x0000,
        0xFF,
        0x08,
        0x00,
        0x00,
        0x00,
        0x00,
    };

    *info = D_801BA484;
}

void func_800E74DC(CollisionCheckInfo *info) {
    info->damage = 0;
    info->damageEffect = 0;
    info->atHitEffect = 0;
    info->acHitEffect = 0;
    info->displacement.x = info->displacement.y = info->displacement.z = 0.0f;
}

void func_800E7508(CollisionCheckInfo* info, CollisionCheckInfoInit *init) {
    info->health = init->health;
    info->cylRadius = init->cylRadius;
    info->cylHeight = init->cylHeight;
    info->mass = init->mass;
}

void func_800E7530(CollisionCheckInfo *info, DamageTable *damageChart, CollisionCheckInfoInit *init) {
    info->health = init->health;
    info->damageChart = damageChart;
    info->cylRadius = init->cylRadius;
    info->cylHeight = init->cylHeight;
    info->mass = init->mass;
}

void func_800E755C(CollisionCheckInfo *info, DamageTable *damageChart, CollisionCheckInfoInit2 *init) {
    info->health = init->health;
    info->damageChart = damageChart;
    info->cylRadius = init->cylRadius;
    info->cylHeight = init->cylHeight;
    info->cylYShift = init->cylYShift;
    info->mass = init->mass;
}

void func_800E7590(CollisionCheckInfo *info, s32 index, CollisionCheckInfoInit2 *init) {
    func_800E755C(info, func_800E03A0(index), init);
}

void func_800E75C8(GlobalContext *ctxt, CollisionCheckContext *colCtxt, Collider *bumper, ColliderInfo *info) {
    f32 damage;
    f32 finalDamage = 0.0f;
    s32 pad;
    Collider* toucher;
    ColliderInfo* toucherBody;
    s32 pad1;
    u32 effect;

    if ((bumper->actor == NULL) || !(bumper->acFlags & 2)) {
        return;
    }
    if (!(info->bumperFlags & 2) || (info->bumperFlags & 0x10)) {
        return;
    }

    toucher = info->acHit;
    toucherBody = info->acHitInfo;

    if (toucher != NULL && toucherBody != NULL && bumper != NULL && info != NULL) {
        damage = Collision_GetDamageAndEffectOnBumper(toucher, toucherBody, bumper, info, &effect);

        if (Collision_GetToucherDamage(toucher, toucherBody, bumper, info) != 0) {
            if (damage < 1.0f) {
                finalDamage = 0.0f;
                if (effect == 0) {
                    return;
                }
            } else {
                finalDamage = func_800E04BC(damage, info);
                if (finalDamage < 1.0f && effect == 0) {
                    return;
                }
            }
        }
        if (bumper->actor->colChkInfo.damageChart != NULL) {
            bumper->actor->colChkInfo.damageEffect = effect;
        }
        if (!(bumper->acFlags & 4) || ((bumper->acFlags & 4) && toucherBody->toucher.dmgFlags == 0x20000000)) {
            if (bumper->actor->colChkInfo.damage < finalDamage) {
                bumper->actor->colChkInfo.damage = finalDamage;
            }
        }
    }
}

void func_800E77EC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, Collider* shape) {
    ColliderJntSph *sphereGroup = (ColliderJntSph*)shape;
    s32 i;

    if (sphereGroup->count > 0 && sphereGroup->elements != NULL) {
        for (i = 0; i < sphereGroup->count; i++) {
            func_800E75C8(ctxt, colCtxt, &sphereGroup->base, &sphereGroup->elements[i].info);
        }
    }
}

void func_800E7894(GlobalContext *ctxt, CollisionCheckContext *colCtxt, Collider* shape) {
    ColliderCylinder *cylinder = (ColliderCylinder*)shape;

    func_800E75C8(ctxt, colCtxt, &cylinder->base, &cylinder->info);
}

void func_800E78B4(GlobalContext *ctxt, CollisionCheckContext *colCtxt, Collider *shape) {
    ColliderTris *triGroup = (ColliderTris*)shape;
    s32 i;

    // unlike sphere groups above, tri groups are not guarded against
    //  triGroup->elements being NULL
    for (i = 0; i < triGroup->count; i++) {
        func_800E75C8(ctxt, colCtxt, &triGroup->base, &triGroup->elements[i].info);
    }
}

void func_800E7948(GlobalContext *ctxt, CollisionCheckContext *colCtxt, Collider *shape) {
    ColliderQuad *quad = (ColliderQuad*)shape;

    func_800E75C8(ctxt, colCtxt, &quad->base, &quad->info);
}

void func_800E7968(GlobalContext *ctxt, CollisionCheckContext *colCtxt, Collider *shape) {
    ColliderSphere *sphere = (ColliderSphere*)shape;

    func_800E75C8(ctxt, colCtxt, &sphere->base, &sphere->info);
}

ColChkApplyFunc D_801BA4A0[] = {
    func_800E77EC,
    func_800E7894,
    func_800E78B4,
    func_800E7948,
    func_800E7968,
};

void func_800E7988(GlobalContext *ctxt, CollisionCheckContext *colCtxt) {
    s32 i;

    for (i = 0; i < colCtxt->colACCount; i++) {
        Collider* col = colCtxt->colAC[i];

        if (col == NULL) {
            continue;
        }
        if (col->acFlags & 0x40) {
            continue;
        }
        D_801BA4A0[col->shape](ctxt, colCtxt, col);
    }
}

s32 func_800E7A48(GlobalContext *globalCtx, CollisionCheckContext *colChkCtx, Collider *shape, Vec3f *a, Vec3f *b) {
    ColliderJntSph *sphereGroup = (ColliderJntSph*)shape;
    s32 i;

    for (i = 0; i < sphereGroup->count; i++) {
        ColliderJntSphElement* sphElem = &sphereGroup->elements[i];

        if (!(sphElem->info.ocElemFlags & 1)) {
            continue;
        }

        D_801EDEB0.a = *a;
        D_801EDEB0.b = *b;
        if (Math3D_ColSphereLineSeg(&sphElem->dim.worldSphere, &D_801EDEB0) != 0) {
            return 1;
        }
    }
    return 0;
}

s32 func_800E7B54(GlobalContext *globalCtx, CollisionCheckContext *colChkCtx, Collider *shape, Vec3f *a, Vec3f *b) {
    ColliderCylinder *cylinder = (ColliderCylinder*)shape;

    if (!(cylinder->info.ocElemFlags & 1)) {
        return 0;
    }

    if (func_8017E350(&cylinder->dim, a, b, &D_801EDF38, &D_801EDF48) != 0) {
        return 1;
    }

    return 0;
}

s32 func_800E7BCC(GlobalContext *globalCtx, CollisionCheckContext *colChkCtx, Collider *shape, Vec3f *a, Vec3f *b) {
    ColliderSphere *sphere = (ColliderSphere*)shape;

    if (!(sphere->info.ocElemFlags & 1)) {
        return 0;
    }

    D_801EDFC8.a = *a;
    D_801EDFC8.b = *b;
    if (Math3D_ColSphereLineSeg(&sphere->dim.worldSphere, &D_801EDFC8) != 0) {
        return 1;
    }

    return 0;
}

ColChkLineFunc D_801BA4B4[] = {
    func_800E7A48,
    func_800E7B54,
    NULL,
    NULL,
    func_800E7BCC,
};

s32 func_800E7C64(GlobalContext *globalCtx, CollisionCheckContext *colChkCtx, Vec3f *a, Vec3f *b, Actor **exclusions, s32 numExclusions) {
    ColChkLineFunc lineCheck;
    Collider** col;
    s32 i;
    s32 exclude;
    s32 result = 0;

    for (col = colChkCtx->colOC; col < &colChkCtx->colOC[colChkCtx->colOCCount]; col++) {
        if (func_800E7264(*col)) {
            continue;
        }

        exclude = 0;
        for (i = 0; i < numExclusions; i++) {
            if ((*col)->actor == exclusions[i]) {
                exclude = 1;
                break;
            }
        }
        if (exclude) {
            continue;
        }

        lineCheck = D_801BA4B4[(*col)->shape];
        if (lineCheck == NULL) {
            continue;
        }

        result = lineCheck(globalCtx, colChkCtx, (*col), a, b);
        if (result) {
            break;
        }
    }
    return result;
}

s32 func_800E7DA8(GlobalContext *ctxt, CollisionCheckContext *colCtxt, Vec3f *a, Vec3f *b) {
    return func_800E7C64(ctxt, colCtxt, a, b, NULL, 0);
}

s32 func_800E7DCC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, Vec3f *a, Vec3f *b, Actor **exclusions, s32 numExclusions) {
    return func_800E7C64(ctxt, colCtxt, a, b, exclusions, numExclusions);
}

void Collision_CylinderMoveToActor(Actor *actor, ColliderCylinder *cylinder) {
    cylinder->dim.pos.x = actor->currPosRot.pos.x;
    cylinder->dim.pos.y = actor->currPosRot.pos.y;
    cylinder->dim.pos.z = actor->currPosRot.pos.z;
}

void Collision_CylinderSetLoc(ColliderCylinder *cylinder, Vec3s *pos) {
    cylinder->dim.pos.x = pos->x;
    cylinder->dim.pos.y = pos->y;
    cylinder->dim.pos.z = pos->z;
}

void Collision_QuadSetCoords(ColliderQuad *quad, Vec3f *a, Vec3f *b, Vec3f *c, Vec3f *d) {
    Math_Vec3f_Copy(&quad->dim.quad[2], c);
    Math_Vec3f_Copy(&quad->dim.quad[3], d);
    Math_Vec3f_Copy(&quad->dim.quad[0], a);
    Math_Vec3f_Copy(&quad->dim.quad[1], b);
    Collision_QuadCalcMidpoints(&quad->dim);
}

void Collision_TriGroupSetCoordsAtIndex(ColliderTris *tris, s32 index, Vec3f *a, Vec3f *b, Vec3f *c) {
    ColliderTrisElement* tri = &tris->elements[index];
    f32 nx;
    f32 ny;
    f32 nz;
    f32 originDist;

    Math_Vec3f_Copy(&tri->dim.vtx[0], a);
    Math_Vec3f_Copy(&tri->dim.vtx[1], b);
    Math_Vec3f_Copy(&tri->dim.vtx[2], c);
    Math3D_UnitNormalVector(a, b, c, &nx, &ny, &nz, &originDist);
    tri->dim.plane.normal.x = nx;
    tri->dim.plane.normal.y = ny;
    tri->dim.plane.normal.z = nz;
    tri->dim.plane.originDist = originDist;
}

void Collision_InitTriParamsAtIndex(GlobalContext *ctxt, ColliderTris *tris, s32 index, ColliderTrisElementDimInit *init) {
    ColliderTrisElement* tri = &tris->elements[index];

    Collision_InitTriParamsWithData(ctxt, &tri->dim, init);
}

#ifdef NON_MATCHING
// needs in-function static bss
void func_800E7FDC(s32 limb, ColliderJntSph *sphereGroup) {
    static Vec3f D_801EE1C0;
    static Vec3f D_801EE1D0;
    s32 i;

    for (i = 0; i < sphereGroup->count; i++) {
        if (limb == sphereGroup->elements[i].dim.limb) {
            D_801EE1C0.x = sphereGroup->elements[i].dim.modelSphere.center.x;
            D_801EE1C0.y = sphereGroup->elements[i].dim.modelSphere.center.y;
            D_801EE1C0.z = sphereGroup->elements[i].dim.modelSphere.center.z;
            SysMatrix_MultiplyVector3fByState(&D_801EE1C0, &D_801EE1D0);
            sphereGroup->elements[i].dim.worldSphere.center.x = D_801EE1D0.x;
            sphereGroup->elements[i].dim.worldSphere.center.y = D_801EE1D0.y;
            sphereGroup->elements[i].dim.worldSphere.center.z = D_801EE1D0.z;
            sphereGroup->elements[i].dim.worldSphere.radius = sphereGroup->elements[i].dim.modelSphere.radius * sphereGroup->elements[i].dim.scale;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E7FDC.asm")
#endif

void func_800E8160(ColliderJntSph *sphereGroup, s32 index, Actor *actor) {
    if (index < sphereGroup->count) {
        sphereGroup->elements[index].dim.worldSphere.center.x = sphereGroup->elements[index].dim.modelSphere.center.x + actor->currPosRot.pos.x;
        sphereGroup->elements[index].dim.worldSphere.center.y = sphereGroup->elements[index].dim.modelSphere.center.y + actor->currPosRot.pos.y;
        sphereGroup->elements[index].dim.worldSphere.center.z = sphereGroup->elements[index].dim.modelSphere.center.z + actor->currPosRot.pos.z;
        sphereGroup->elements[index].dim.worldSphere.radius = sphereGroup->elements[index].dim.modelSphere.radius * sphereGroup->elements[index].dim.scale;
    }
}

#ifdef NON_MATCHING
// needs in-function static bss
void func_800E823C(s32 limb, ColliderSphere *sphere) {
    static Vec3f D_801EE1E0;
    static Vec3f D_801EE1F0;

    if (limb == sphere->dim.limb) {
        D_801EE1E0.x = sphere->dim.modelSphere.center.x;
        D_801EE1E0.y = sphere->dim.modelSphere.center.y;
        D_801EE1E0.z = sphere->dim.modelSphere.center.z;
        SysMatrix_MultiplyVector3fByState(&D_801EE1E0, &D_801EE1F0);
        sphere->dim.worldSphere.center.x = D_801EE1F0.x;
        sphere->dim.worldSphere.center.y = D_801EE1F0.y;
        sphere->dim.worldSphere.center.z = D_801EE1F0.z;
        sphere->dim.worldSphere.radius = sphere->dim.modelSphere.radius * sphere->dim.scale;
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E823C.asm")
#endif

#ifdef NON_MATCHING
// needs in-function static bss
void func_800E8318(GlobalContext* ctxt, Vec3f* v) {
    static EffSparkParams D_801EE200;
    s32 effectIndex;

    D_801EE200.position.x = v->x;
    D_801EE200.position.x = v->y;
    D_801EE200.position.x = v->z;
    D_801EE200.particleFactor1 = 5;
    D_801EE200.particleFactor2 = 5;
    D_801EE200.colorStart[0].red = 128;
    D_801EE200.colorStart[0].green = 0;
    D_801EE200.colorStart[0].blue = 64;
    D_801EE200.colorStart[0].alpha = 255;
    D_801EE200.colorStart[1].red = 128;
    D_801EE200.colorStart[1].green = 0;
    D_801EE200.colorStart[1].blue = 64;
    D_801EE200.colorStart[1].alpha = 255;
    D_801EE200.colorStart[2].red = 255;
    D_801EE200.colorStart[2].green = 128;
    D_801EE200.colorStart[2].blue = 0;
    D_801EE200.colorStart[2].alpha = 255;
    D_801EE200.colorStart[3].red = 255;
    D_801EE200.colorStart[3].green = 128;
    D_801EE200.colorStart[3].blue = 0;
    D_801EE200.colorStart[3].alpha = 255;
    D_801EE200.colorEnd[0].red = 64;
    D_801EE200.colorEnd[0].green = 0;
    D_801EE200.colorEnd[0].blue = 32;
    D_801EE200.colorEnd[0].alpha = 0;
    D_801EE200.colorEnd[1].red = 64;
    D_801EE200.colorEnd[1].green = 0;
    D_801EE200.colorEnd[1].blue = 32;
    D_801EE200.colorEnd[1].alpha = 0;
    D_801EE200.colorEnd[2].red = 128;
    D_801EE200.colorEnd[2].green = 0;
    D_801EE200.colorEnd[2].blue = 64;
    D_801EE200.colorEnd[2].alpha = 0;
    D_801EE200.colorEnd[3].red = 128;
    D_801EE200.colorEnd[3].green = 0;
    D_801EE200.colorEnd[3].blue = 64;
    D_801EE200.colorEnd[3].alpha = 0;
    D_801EE200.age = 0;
    D_801EE200.duration = 16;
    D_801EE200.velocity = 8.0f;
    D_801EE200.gravity = -1.0f;

    Effect_Add(ctxt, &effectIndex, 0, 0, 1, &D_801EE200);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E8318.asm")
#endif

#ifdef NON_MATCHING
// needs in-function static bss
void func_800E8478(GlobalContext *ctxt, Vec3f *v) {
    static EffSparkParams D_801EE738;
    s32 effectIndex;

    D_801EE738.position.x = v->x;
    D_801EE738.position.x = v->y;
    D_801EE738.position.x = v->z;
    D_801EE738.particleFactor1 = 5;
    D_801EE738.particleFactor2 = 5;
    D_801EE738.colorStart[0].red = 255;
    D_801EE738.colorStart[0].green = 255;
    D_801EE738.colorStart[0].blue = 255;
    D_801EE738.colorStart[0].alpha = 255;
    D_801EE738.colorStart[1].red = 100;
    D_801EE738.colorStart[1].green = 100;
    D_801EE738.colorStart[1].blue = 100;
    D_801EE738.colorStart[1].alpha = 100;
    D_801EE738.colorStart[2].red = 100;
    D_801EE738.colorStart[2].green = 100;
    D_801EE738.colorStart[2].blue = 100;
    D_801EE738.colorStart[2].alpha = 100;
    D_801EE738.colorStart[3].red = 100;
    D_801EE738.colorStart[3].green = 100;
    D_801EE738.colorStart[3].blue = 100;
    D_801EE738.colorStart[3].alpha = 100;
    D_801EE738.colorEnd[0].red = 50;
    D_801EE738.colorEnd[0].green = 50;
    D_801EE738.colorEnd[0].blue = 50;
    D_801EE738.colorEnd[0].alpha = 50;
    D_801EE738.colorEnd[1].red = 50;
    D_801EE738.colorEnd[1].green = 50;
    D_801EE738.colorEnd[1].blue = 50;
    D_801EE738.colorEnd[1].alpha = 50;
    D_801EE738.colorEnd[2].red = 50;
    D_801EE738.colorEnd[2].green = 50;
    D_801EE738.colorEnd[2].blue = 50;
    D_801EE738.colorEnd[2].alpha = 50;
    D_801EE738.colorEnd[3].red = 0;
    D_801EE738.colorEnd[3].green = 0;
    D_801EE738.colorEnd[3].blue = 0;
    D_801EE738.colorEnd[3].alpha = 0;
    D_801EE738.age = 0;
    D_801EE738.duration = 16;
    D_801EE738.velocity = 8.0f;
    D_801EE738.gravity = -1.0f;

    Effect_Add(ctxt, &effectIndex, 0, 0, 1, &D_801EE738);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E8478.asm")
#endif

void func_800E85D4(GlobalContext *ctxt, Vec3f *v) {
    static EffShieldParticleInit D_801BA4C8 = {
        16,
        { 0, 0, 0 },
        { 0, 200, 255, 255 },
        { 255, 255, 255, 255 },
        { 255, 255, 128, 255 },
        { 255, 255, 0, 255 },
        { 255, 64, 0, 200 },
        { 255, 0, 0, 255 },
        2.1f, 35.0f, 30.0f,
        8,
        {
            0, 0, 0,
            0, 128, 255, 0,
            300,
        },
        1,
    };
    s32 effectIndex;

    D_801BA4C8.position.x = v->x;
    D_801BA4C8.position.y = v->y;
    D_801BA4C8.position.z = v->z;
    D_801BA4C8.lightParams.posX = D_801BA4C8.position.x;
    D_801BA4C8.lightParams.posY = D_801BA4C8.position.y;
    D_801BA4C8.lightParams.posZ = D_801BA4C8.position.z;

    Effect_Add(ctxt, &effectIndex, 3, 0, 1, &D_801BA4C8);
}

void func_800E8668(GlobalContext *ctxt, Vec3f *v) {
    func_800E85D4(ctxt, v);
    play_sound(0x1808);
}

void func_800E8690(GlobalContext *ctxt, Vec3f *v, Vec3f *pos) {
    func_800E85D4(ctxt, v);
    func_8019F1C0(pos, 0x1808);
}

void func_800E86C0(GlobalContext *ctxt, Vec3f *v) {
    func_800E8668(ctxt, v);
}

void func_800E86E0(GlobalContext *ctxt, Vec3f *v, Vec3f *pos) {
    static EffShieldParticleInit D_801BA508 = {
        16,
        { 0, 0, 0 },
        { 0, 200, 255, 255 },
        { 255, 255, 255, 255 },
        { 255, 255, 128, 255 },
        { 255, 255, 0, 255 },
        { 255, 64, 0, 200 },
        { 255, 0, 0, 255 },
        2.1f, 35.0f, 30.0f,
        8,
        {
            0, 0, 0, 
            0, 128, 255, 0,
            300, 
        },
        0,
    };
    s32 effectIndex;

    D_801BA508.position.x = v->x;
    D_801BA508.position.y = v->y;
    D_801BA508.position.z = v->z;
    D_801BA508.lightParams.posX = D_801BA508.position.x;
    D_801BA508.lightParams.posY = D_801BA508.position.y;
    D_801BA508.lightParams.posZ = D_801BA508.position.z;

    Effect_Add(ctxt, &effectIndex, 3, 0, 1, &D_801BA508);
    func_8019F1C0(pos, 0x1837);
}

s32 func_800E8784(f32 radius, f32 height, f32 offset, Vec3f* actorPos, Vec3f* itemPos, Vec3f* itemProjPos, Vec3f* out1, Vec3f* out2) {
    Vec3f actorToItem;
    Vec3f actorToItemProj;
    Vec3f itemStep;
    f32 frac1 = 0.0f;
    f32 frac2 = 0.0f;
    u32 intersect2;
    u32 intersect1;
    u32 test1;
    u32 test2;
    f32 radSqDiff;
    f32 actorDotItemXZ;
    f32 zero = 0.0f;
    f32 closeDist;
    s32 pad1;
    s32 pad2;

    actorToItem.x = itemPos->x - actorPos->x;
    actorToItem.y = itemPos->y - actorPos->y - offset;
    actorToItem.z = itemPos->z - actorPos->z;

    actorToItemProj.x = itemProjPos->x - actorPos->x;
    actorToItemProj.y = itemProjPos->y - actorPos->y - offset;
    actorToItemProj.z = itemProjPos->z - actorPos->z;

    itemStep.x = actorToItemProj.x - actorToItem.x;
    itemStep.y = actorToItemProj.y - actorToItem.y;
    itemStep.z = actorToItemProj.z - actorToItem.z;

    if ((actorToItem.y > 0.0f) && (actorToItem.y < height) && (sqrtf(SQXZ(actorToItem)) < radius)) {
        return 3;
    }

    if ((actorToItemProj.y > 0.0f) && (actorToItemProj.y < height) && (sqrtf(SQXZ(actorToItemProj)) < radius)) {
        return 3;
    }
    radSqDiff = SQXZ(actorToItem) - SQ(radius);
    if (!(fabsf(SQXZ(itemStep)) < 0.008f)) {
        actorDotItemXZ = DOTXZ(2.0f * itemStep, actorToItem);
        if (SQ(actorDotItemXZ) < (4.0f * SQXZ(itemStep) * radSqDiff)) {
            return 0;
        }
        if (SQ(actorDotItemXZ) - (4.0f * SQXZ(itemStep) * radSqDiff) > zero) {
            intersect1 = intersect2 = 1;
        } else {
            intersect1 = 1;
            intersect2 = 0;
        }
        closeDist = sqrtf(SQ(actorDotItemXZ) - (4.0f * SQXZ(itemStep) * radSqDiff));
        if (intersect1 != 0) {
            frac1 = (closeDist - actorDotItemXZ) / (2.0f * SQXZ(itemStep));
        }
        if (intersect2 != 0) {
            frac2 = (-actorDotItemXZ - closeDist) / (2.0f * SQXZ(itemStep));
        }
    } else if (!(fabsf(DOTXZ(2.0f * itemStep, actorToItem)) < 0.008f)) {
        intersect1 = 1;
        intersect2 = 0;
        frac1 = -radSqDiff / DOTXZ(2.0f * itemStep, actorToItem);
    } else {
        if (radSqDiff <= 0.0f) {
            test1 = (0.0f < actorToItem.y) && (actorToItem.y < height);
            test2 = (0.0f < actorToItemProj.y) && (actorToItemProj.y < height);

            if (test1 && test2) {
                *out1 = actorToItem;
                *out2 = actorToItemProj;
                return 2;
            }
            if (test1) {
                *out1 = actorToItem;
                return 1;
            }
            if (test2) {
                *out1 = actorToItemProj;
                return 1;
            }
        }
        return 0;
    }

    if (intersect2 == 0) {
        if (frac1 < 0.0f || 1.0f < frac1) {
            return 0;
        }
    } else {
        test1 = (frac1 < 0.0f || 1.0f < frac1);
        test2 = (frac2 < 0.0f || 1.0f < frac2);

        if (test1 && test2) {
            return 0;
        }
        if (test1) {
            intersect1 = 0;
        }
        if (test2) {
            intersect2 = 0;
        }
    }

    if ((intersect1 != 0) &&
        ((frac1 * itemStep.y + actorToItem.y < 0.0f) || (height < frac1 * itemStep.y + actorToItem.y))) {
        intersect1 = 0;
    }
    if ((intersect2 != 0) &&
        ((frac2 * itemStep.y + actorToItem.y < 0.0f) || (height < frac2 * itemStep.y + actorToItem.y))) {
        intersect2 = 0;
    }
    if (intersect1 == 0 && intersect2 == 0) {
        return 0;
    } else if ((intersect1 != 0) && (intersect2 != 0)) {
        out1->x = frac1 * itemStep.x + actorToItem.x + actorPos->x;
        out1->y = frac1 * itemStep.y + actorToItem.y + actorPos->y;
        out1->z = frac1 * itemStep.z + actorToItem.z + actorPos->z;
        out2->x = frac2 * itemStep.x + actorToItem.x + actorPos->x;
        out2->y = frac2 * itemStep.y + actorToItem.y + actorPos->y;
        out2->z = frac2 * itemStep.z + actorToItem.z + actorPos->z;
        return 2;
    } else if (intersect1 != 0) {
        out1->x = frac1 * itemStep.x + actorToItem.x + actorPos->x;
        out1->y = frac1 * itemStep.y + actorToItem.y + actorPos->y;
        out1->z = frac1 * itemStep.z + actorToItem.z + actorPos->z;
        return 1;
    } else if (intersect2 != 0) {
        out1->x = frac2 * itemStep.x + actorToItem.x + actorPos->x;
        out1->y = frac2 * itemStep.y + actorToItem.y + actorPos->y;
        out1->z = frac2 * itemStep.z + actorToItem.z + actorPos->z;
        return 1;
    }
    return 1;
}
