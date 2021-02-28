#include <ultra64.h>
#include <global.h>

f32 Collision_GetDamageAndEffectOnBumper(ColCommon *toucher, ColBodyInfo *toucherBody, ColCommon *bumper, ColBodyInfo *bumperBody, u32 *effect) {
    static f32 damageMultipliers[] = { 
        0.0f, 1.0f, 2.0f, 0.5f, 0.25f, 3.0f, 4.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    };

    u32 collidesWith;
    s32 i;
    f32 damage;

    *effect = 0;

    damage = Collision_GetToucherDamage(toucher, toucherBody, bumper, bumperBody);
    if (bumper->actor->unkA0.damageChart != NULL) {
        collidesWith = toucherBody->toucher.collidesWith;

        for (i = 0; i != 32; i++) {
            if (collidesWith == 1) {
                break;
            }
            collidesWith >>= 1;
        }

        damage *= damageMultipliers[bumper->actor->unkA0.damageChart->attack[i] & 0xF];
        *effect = (bumper->actor->unkA0.damageChart->attack[i] >> 4) & 0xF;
    }
    return damage;
}

f32 func_800E04BC(f32 a0, ColBodyInfo *bumperBody) {
    f32 sub = a0 - bumperBody->bumper.unk5;

    return sub;
}

s32 Collision_GetToucherDamage(ColCommon *toucher, ColBodyInfo *toucherBody, ColCommon *bumper, ColBodyInfo *bumperBody) {
    if (toucher->actor != NULL && toucher->actor->id == ACTOR_EN_BOM && 
        bumper->actor != NULL && bumper->actor->id == ACTOR_PLAYER) {
        return 8;
    }
    return toucherBody->toucher.damage;
}

s32 Collision_InitCommonDefault(GlobalContext *ctxt, ColCommon *shape) {
    static ColCommon defaultColCommon = {
        NULL, NULL, NULL, NULL, 0x00, 0x00, 0x00, 0x00, 0x03, 0x05,
    };

    *shape = defaultColCommon;
    return 1;
}

s32 Collision_FiniCommon(GlobalContext *ctxt, ColCommon *shape) {
    return 1;
}

s32 func_800E0594(GlobalContext *ctxt, ColCommon *shape, ColInitToActor *init) {
    shape->actor = init->actor;
    shape->flagsAT = init->atFlags;
    shape->flagsAC = init->acFlags;
    shape->unk12 = init->ocFlags1;
    shape->unk13 = 0x10;
    shape->type = init->type;
    return 1;
}

s32 func_800E05D4(GlobalContext* ctxt, ColCommon* shape, Actor* actor, ColInitType1* init) {
    shape->actor = actor;
    shape->unk14 = init->colType;
    shape->flagsAT = init->atFlags;
    shape->flagsAC = init->acFlags;
    shape->unk12 = init->ocFlags1;
    shape->unk13 = 0x10;
    shape->type = init->shape;
    return 1;
}

s32 Collision_InitCommonWithData(GlobalContext *ctxt, ColCommon *shape, Actor *actor, ColCommonInit *init) {
    shape->actor = actor;
    shape->unk14 = init->unk0;
    shape->flagsAT = init->unk1;
    shape->flagsAC = init->unk2;
    shape->unk12 = init->unk3;
    shape->unk13 = init->unk4;
    shape->type = init->type;
    return 1;
}

void Collision_ResetCommonForAT(GlobalContext *ctxt, ColCommon *shape) {
    shape->collisionAT = NULL;
    shape->flagsAT = shape->flagsAT & ~6;
}

void Collision_ResetCommonForAC(GlobalContext *ctxt, ColCommon *shape) {
    shape->collisionAC = NULL;
    shape->flagsAC = shape->flagsAC & ~0x82;
}

void Collision_ResetCommonForOT(GlobalContext *ctxt, ColCommon *shape) {
    shape->collisionOT = NULL;
    shape->unk12 = shape->unk12 & ~2;
    shape->unk13 = shape->unk13 & ~1;
}

s32 Collision_InitTouchDefault(GlobalContext *ctxt, ColTouch *touch) {
    static ColTouch defaultColTouch = {
        0x00000000, 0x00, 0x00,
    };

    *touch = defaultColTouch;
    return 1;
}

s32 Collision_FiniTouch(GlobalContext *ctxt, ColTouch *touch) {
    return 1;
}

s32 Collision_InitTouchWithData(GlobalContext *ctxt, ColTouch *touch, ColTouchInit *init) {
    touch->collidesWith = init->unk0;
    touch->unk4 = init->unk4;
    touch->damage = init->unk5;
    return 1;
}

void Collision_nop800E0720(GlobalContext* ctxt, ColBodyInfo* body) {

}

s32 Collision_InitBumpDefault(GlobalContext *ctxt, ColBump *bump) {
    static ColBump defaultColBump = {
        0xF7CFFFFF, 0x00, 0x00,
        { 0, 0, 0 },
    };

    *bump = defaultColBump;
    return 1;
}

s32 Collision_FiniBump(GlobalContext* ctxt, ColBump* bump) {
    return 1;
}

s32 Collision_InitBumpWithData(GlobalContext *ctxt, ColBump *bump, ColBumpInit *init) {
    bump->collidesWith = init->unk0;
    bump->unk4 = init->unk4;
    bump->unk5 = init->unk5;
    return 1;
}

s32 Collision_InitBodyDefault(GlobalContext *ctxt, ColBodyInfo *body) {
    static ColBodyInfo defaultColBodyInfo = {
        {
            0x00000000, 0x00, 0x00,
        },
        {
            0xF7CFFFFF, 0x00, 0x00,
            { 0, 0, 0 },
        },
        0x00, 0x00, 0x00, 0x00,
        NULL, NULL, NULL, NULL,
    };

    *body = defaultColBodyInfo;

    Collision_InitTouchDefault(ctxt, &body->toucher);
    Collision_InitBumpDefault(ctxt, &body->bumper);
    return 1;
}

s32 Collision_FiniBody(GlobalContext *ctxt, ColBodyInfo *body) {
    Collision_FiniTouch(ctxt, &body->toucher);
    Collision_FiniBump(ctxt, &body->bumper);
    return 1;
}

s32 Collision_InitBodyWithData(GlobalContext *ctxt, ColBodyInfo *body, ColBodyInfoInit *init) {
    body->unk14 = init->unk0;
    Collision_InitTouchWithData(ctxt, &body->toucher, &init->unk4);
    Collision_InitBumpWithData(ctxt, &body->bumper, &init->unkC);
    body->unk15 = init->unk14;
    body->unk16 = init->unk15;
    body->unk17 = init->unk16;
    return 1;
}

void Collision_ResetBodyForAT(GlobalContext *ctxt, ColBodyInfo *body) {
    body->unk18 = NULL;
    body->unk20 = NULL;
    body->unk15 &= ~2;
    body->unk15 &= ~0x40;
    Collision_nop800E0720(ctxt, body);
}

void Collision_ResetBodyForAC(GlobalContext *ctxt, ColBodyInfo *body) {
    body->bumper.unk6.z = 0;
    body->unk16 &= ~2;
    body->unk16 &= ~0x80;
    body->unk1C = NULL;
    body->unk24 = NULL;
    body->bumper.unk6.y = body->bumper.unk6.z;
    body->bumper.unk6.x = body->bumper.unk6.z;
}

void Collision_ResetBodyForOT(GlobalContext *ctxt, ColBodyInfo *body) {
    body->unk17 &= ~2;
}

s32 Collision_InitSphereParamsDefault(GlobalContext *ctxt, ColSphereParams *params) {
    static ColSphereParams defaultColSphereInfo = {
        { { 0, 0, 0 }, 0, }, { { 0, 0, 0 }, 0, }, 0.0f, 0x00,
    };

    *params = defaultColSphereInfo;
    return 1;
}

s32 Collision_FiniSphereParams(GlobalContext *ctxt, ColSphereParams *params) {
    return 1;
}

s32 Collision_InitSphereParamsWithData(GlobalContext *ctxt, ColSphereParams *params, ColSphereParamsInit *init) {
    params->unk14 = init->unk0;
    params->unk0 = init->unk1;
    params->unk10 = init->unkA * 0.01f;
    return 1;
}

s32 Collision_InitSphereGroupElemDefault(GlobalContext *pzParm1, ColSphereGroupElement *elem) {
    Collision_InitBodyDefault(pzParm1, &elem->body);
    Collision_InitSphereParamsDefault(pzParm1, &elem->params);
    return 1;
}

s32 Collision_FiniSphereGroupElem(GlobalContext *ctxt, ColSphereGroupElement *elem) {
    Collision_FiniBody(ctxt, &elem->body);
    Collision_FiniSphereParams(ctxt, &elem->params);
    return 1;
}

s32 Collision_InitSphereGroupElemWithData(GlobalContext *ctxt, ColSphereGroupElement *elem, ColSphereGroupElementInit *init) {
    Collision_InitBodyWithData(ctxt, &elem->body, &init->body);
    Collision_InitSphereParamsWithData(ctxt, &elem->params, &init->params);
    return 1;
}

s32 Collision_ResetSphereGroupElemForAT(GlobalContext *ctxt, ColSphereGroupElement *elem) {
    Collision_ResetBodyForAT(ctxt, &elem->body);
    return 1;
}

s32 Collision_ResetSphereGroupElemForAC(GlobalContext *ctxt, ColSphereGroupElement *elem) {
    Collision_ResetBodyForAC(ctxt, &elem->body);
    return 1;
}

s32 Collision_ResetSphereGroupElemForOT(GlobalContext *ctxt, ColSphereGroupElement *elem) {
    Collision_ResetBodyForOT(ctxt, &elem->body);
    return 1;
}

s32 Collision_InitSphereGroupDefault(GlobalContext *ctxt, ColSphereGroup *sphereGroup) {
    Collision_InitCommonDefault(ctxt, &sphereGroup->base);
    sphereGroup->count = 0;
    sphereGroup->spheres = NULL;
    return 1;
}

// free jnt sph
s32 func_800E0B78(GlobalContext *ctxt, ColSphereGroup *sphereGroup) {
    ColSphereGroupElement *sphElem;

    Collision_FiniCommon(ctxt, &sphereGroup->base);
    for (sphElem = &sphereGroup->spheres[0]; sphElem < &sphereGroup->spheres[sphereGroup->count]; sphElem++) {
        Collision_FiniSphereGroupElem(ctxt, sphElem);
    }

    sphereGroup->count = 0;
    if (sphereGroup->spheres != NULL) {
        zelda_free(sphereGroup->spheres);
    }
    sphereGroup->spheres = NULL;
    return 1;
}

s32 Collision_FiniSphereGroup(GlobalContext* ctxt, ColSphereGroup* sphereGroup) {
    ColSphereGroupElement* sphElem;

    Collision_FiniCommon(ctxt, &sphereGroup->base);

    for (sphElem = &sphereGroup->spheres[0]; sphElem < &sphereGroup->spheres[sphereGroup->count]; sphElem++) {
        Collision_FiniSphereGroupElem(ctxt, sphElem);
    }
    sphereGroup->count = 0;
    sphereGroup->spheres = NULL;
    return 1;
}

s32 func_800E0CA8(GlobalContext *ctxt, ColSphereGroup *sphereGroup, ColSphereGroupInitToActor *init) {
    ColSphereGroupElement *sphElem;
    ColSphereGroupElementInit *initElem;

    func_800E0594(ctxt, &sphereGroup->base, &init->base);
    sphereGroup->count = init->count;
    sphereGroup->spheres = zelda_malloc(init->count * sizeof(ColSphereGroupElement));

    if (sphereGroup->spheres == NULL) {
        sphereGroup->count = 0;
        return 0;
    }

    for (sphElem = &sphereGroup->spheres[0], initElem = &init->init[0]; sphElem < &sphereGroup->spheres[sphereGroup->count]; sphElem++, initElem++) {
        Collision_InitSphereGroupElemDefault(ctxt, sphElem);
        Collision_InitSphereGroupElemWithData(ctxt, sphElem, initElem);
    }
    return 1;
}

s32 func_800E0D84(GlobalContext *ctxt, ColSphereGroup *sphereGroup, Actor *actor, ColSphereGroupInitType1 *init) {
    ColSphereGroupElement *sphElem;
    ColSphereGroupElementInit *initElem;

    func_800E05D4(ctxt, &sphereGroup->base, actor, &init->base);
    sphereGroup->count = init->count;
    sphereGroup->spheres = zelda_malloc(init->count * sizeof(ColSphereGroupElement));

    if (sphereGroup->spheres == NULL) {
        sphereGroup->count = 0;
        return 0;
    }

    for (sphElem = &sphereGroup->spheres[0], initElem = &init->init[0]; sphElem < &sphereGroup->spheres[sphereGroup->count]; sphElem++, initElem++) {
        Collision_InitSphereGroupElemDefault(ctxt, sphElem);
        Collision_InitSphereGroupElemWithData(ctxt, sphElem, initElem);
    }
    return 1;
}

s32 Collision_InitSphereGroupWithData(GlobalContext *ctxt, ColSphereGroup *sphereGroup, Actor *actor, ColSphereGroupInit *init, ColSphereGroupElement *spheres) {
    ColSphereGroupElement* sphElem;
    ColSphereGroupElementInit* sphElemInit;

    Collision_InitCommonWithData(ctxt, &sphereGroup->base, actor, &init->base);
    sphereGroup->count = init->count;
    sphereGroup->spheres = spheres;

    for (sphElem = &sphereGroup->spheres[0], sphElemInit = &init->init[0]; sphElem < &sphereGroup->spheres[sphereGroup->count]; sphElem++, sphElemInit++) {
        Collision_InitSphereGroupElemDefault(ctxt, sphElem);
        Collision_InitSphereGroupElemWithData(ctxt, sphElem, sphElemInit);
    }

    return 1;
}

s32 Collision_InitSphereGroup(GlobalContext *ctxt, ColSphereGroup *sphereGroup, Actor *actor, ColSphereGroupInit *init, ColSphereGroupElement *spheres) {
    Collision_InitSphereGroupDefault(ctxt, sphereGroup);
    Collision_InitSphereGroupWithData(ctxt, sphereGroup, actor, init, spheres);
    return 0;
}

s32 Collision_ResetSphereGroupForAT(GlobalContext *ctxt, ColCommon *collider) {
    ColSphereGroupElement *sphElem;
    ColSphereGroup* spheres = (ColSphereGroup*)collider;

    Collision_ResetCommonForAT(ctxt, &spheres->base);

    for (sphElem = &spheres->spheres[0]; sphElem < &spheres->spheres[spheres->count]; sphElem++) {
        Collision_ResetSphereGroupElemForAT(ctxt, sphElem);
    }
    return 1;
}

s32 Collision_ResetSphereGroupForAC(GlobalContext *ctxt, ColCommon *collider) {
    ColSphereGroupElement *sphElem;
    ColSphereGroup* spheres = (ColSphereGroup*)collider;

    Collision_ResetCommonForAC(ctxt, &spheres->base);

    for (sphElem = &spheres->spheres[0]; sphElem < &spheres->spheres[spheres->count]; sphElem++) {
        Collision_ResetSphereGroupElemForAC(ctxt, sphElem);
    }
    return 1;
}

s32 Collision_ResetSphereGroupForOT(GlobalContext *ctxt, ColCommon *collider) {
    ColSphereGroupElement *sphElem;
    ColSphereGroup* spheres = (ColSphereGroup*)collider;

    Collision_ResetCommonForOT(ctxt, &spheres->base);

    for (sphElem = &spheres->spheres[0]; sphElem < &spheres->spheres[spheres->count]; sphElem++) {
        Collision_ResetSphereGroupElemForOT(ctxt, sphElem);
    }
    return 1;
}

s32 Collision_InitCylinderParamsDefault(GlobalContext* ctxt, ColCylinderParams* params) {
    static ColCylinderParams defaultColCylinderInfo = {
        0, 0, 0, { 0, 0, 0 },
    };

    *params = defaultColCylinderInfo;
    return 1;
}

s32 Collision_FiniCylinderParams(GlobalContext* ctxt, ColCylinderParams* params) {
    return 1;
}

s32 Collision_InitCylinderParamsWithData(GlobalContext *ctxt, ColCylinderParams *info, ColCylinderParams *init) {
    *info = *init;
    return 1;
}

s32 Collision_InitCylinderDefault(GlobalContext *ctxt, ColCylinder *cylinder) {
    Collision_InitCommonDefault(ctxt, &cylinder->base);
    Collision_InitBodyDefault(ctxt, &cylinder->body);
    Collision_InitCylinderParamsDefault(ctxt, &cylinder->params);
    return 1;
}

s32 Collision_FiniCylinder(GlobalContext *ctxt, ColCylinder *cylinder) {
    Collision_FiniCommon(ctxt, &cylinder->base);
    Collision_FiniBody(ctxt, &cylinder->body);
    Collision_FiniCylinderParams(ctxt, &cylinder->params);
    return 1;
}

s32 func_800E123C(GlobalContext* ctxt, ColCylinder* cylinder, ColCylinderInitToActor* init) {
    func_800E0594(ctxt, &cylinder->base, &init->base);
    Collision_InitBodyWithData(ctxt, &cylinder->body, &init->body);
    Collision_InitCylinderParamsWithData(ctxt, &cylinder->params, &init->info);
    return 1;
}

s32 func_800E12A4(GlobalContext *ctxt, ColCylinder *cylinder, Actor *actor, ColCylinderInitType1 *init) {
    func_800E05D4(ctxt, &cylinder->base, actor, &init->base);
    Collision_InitBodyWithData(ctxt, &cylinder->body, &init->body);
    Collision_InitCylinderParamsWithData(ctxt, &cylinder->params, &init->info);
    return 1;
}

s32 Collision_InitCylinderWithData(GlobalContext *ctxt, ColCylinder *cylinder, Actor *actor, ColCylinderInit *init) {
    Collision_InitCommonWithData(ctxt, &cylinder->base, actor, &init->base);
    Collision_InitBodyWithData(ctxt, &cylinder->body, &init->body);
    Collision_InitCylinderParamsWithData(ctxt, &cylinder->params, &init->info);
    return 1;
}

s32 Collision_InitCylinder(GlobalContext *ctxt, ColCylinder *cylinder, Actor *actor, ColCylinderInit *init) {
    Collision_InitCylinderDefault(ctxt, cylinder);
    Collision_InitCylinderWithData(ctxt, cylinder, actor, init);
    return 1;
}

s32 Collision_ResetCylinderForAT(GlobalContext *ctxt, ColCylinder *cylinder) {
    Collision_ResetCommonForAT(ctxt, &cylinder->base);
    Collision_ResetBodyForAT(ctxt, &cylinder->body);
    return 1;
}

s32 Collision_ResetCylinderForAC(GlobalContext *ctxt, ColCylinder *cylinder) {
    Collision_ResetCommonForAC(ctxt, &cylinder->base);
    Collision_ResetBodyForAC(ctxt, &cylinder->body);
    return 1;
}

s32 Collision_ReseCylinderForOT(GlobalContext *ctxt, ColCylinder *cylinder) {
    Collision_ResetCommonForOT(ctxt, &cylinder->base);
    Collision_ResetBodyForOT(ctxt, &cylinder->body);
    return 1;
}

s32 Collision_InitTriParamsDefault(GlobalContext *ctxt, ColTriParams *coords) {
    static ColTriParams defaultColTriParams = {
        {
            { 0.0f, 0.0f, 0.0f },
            { 0.0f, 0.0f, 0.0f },
            { 0.0f, 0.0f, 0.0f },
        },
        { 0.0f, 0.0f, 0.0f },
        0.0f,
    };

    *coords = defaultColTriParams;
    return 1;
}

s32 Collision_FiniTriParams(GlobalContext* ctxt, ColTriParams* params) {
    return 1;
}

s32 Collision_InitTriParamsWithData(GlobalContext *ctxt, ColTriParams *params, ColTriParamsInit *init) {
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

    params->unitNormal.x = nx;
    params->unitNormal.y = ny;
    params->unitNormal.z = nz;
    params->unk30 = originDist;
    return 1;
}

s32 Collision_InitTriDefault(GlobalContext *ctxt, ColTri *elem) {
    Collision_InitBodyDefault(ctxt, &elem->body);
    Collision_InitTriParamsDefault(ctxt, &elem->params);
    return 1;
}

s32 Collision_FiniTri(GlobalContext *ctxt, ColTri *elem) {
    Collision_FiniBody(ctxt, &elem->body);
    Collision_FiniTriParams(ctxt, &elem->params);
    return 1;
}

s32 Collision_InitTriWithData(GlobalContext *ctxt, ColTri *elem, ColTriInit *init) {
    Collision_InitBodyWithData(ctxt, &elem->body, &init->body);
    Collision_InitTriParamsWithData(ctxt, &elem->params, &init->params);
    return 1;
}

s32 Collision_ResetTriForAT(GlobalContext *ctxt, ColTri *tri) {
    Collision_ResetBodyForAT(ctxt, &tri->body);
    return 1;
}

s32 Collision_ResetTriForAC(GlobalContext *ctxt, ColTri *tri) {
    Collision_ResetBodyForAC(ctxt, &tri->body);
    return 1;
}

// Collision_ResetTriForOT
s32 func_800E16AC(GlobalContext *ctxt, ColTri *tri) {
    Collision_ResetBodyForOT(ctxt, &tri->body);
    return 1;
}

s32 Collision_InitTriGroupDefault(GlobalContext *ctxt, ColTriGroup *triGroup) {
    Collision_InitCommonDefault(ctxt, &triGroup->base);
    triGroup->count = 0;
    triGroup->tris = NULL;
    return 1;
}

s32 func_800E16FC(GlobalContext *ctxt, ColTriGroup *triGroup) {
    ColTri *triElem;

    Collision_FiniCommon(ctxt, &triGroup->base);
    
    for (triElem = &triGroup->tris[0]; triElem < &triGroup->tris[triGroup->count]; triElem++) {
        Collision_FiniTri(ctxt, triElem);
    }

    triGroup->count = 0;
    if (triGroup->tris != NULL) {
        zelda_free(triGroup->tris);
    }
    triGroup->tris = NULL;

    return 1;
}

s32 Collision_FiniTriGroup(GlobalContext *ctxt, ColTriGroup *triGroup) {
    ColTri* triElem;

    Collision_FiniCommon(ctxt, &triGroup->base);

    for (triElem = &triGroup->tris[0]; triElem < &triGroup->tris[triGroup->count]; triElem++) {
        Collision_FiniTri(ctxt, triElem);
    }
    triGroup->count = 0;
    triGroup->tris = NULL;
    return 1;
}

s32 func_800E1858(GlobalContext *ctxt, ColTriGroup *triGroup, Actor *actor, ColTriGroupInitType1 *init) {
    ColTri *triElem;
    ColTriInit *triElemInit;

    func_800E05D4(ctxt, &triGroup->base, actor, &init->base);
    triGroup->count = init->count;
    triGroup->tris = zelda_malloc(triGroup->count * sizeof(ColTri));

    if (triGroup->tris == NULL) {
        triGroup->count = 0;
        return 0;
    }

    for (triElem = &triGroup->tris[0], triElemInit = &init->elemInit[0]; triElem < &triGroup->tris[triGroup->count]; triElem++, triElemInit++) {
        Collision_InitTriDefault(ctxt, triElem);
        Collision_InitTriWithData(ctxt, triElem, triElemInit);
    }

    return 1;
}

s32 Collision_InitTriGroupWithData(GlobalContext *ctxt, ColTriGroup *triGroup, Actor *actor, ColTriGroupInit *init, ColTri *tris) {
    ColTri *triElem;
    ColTriInit *triElemInit;

    Collision_InitCommonWithData(ctxt, &triGroup->base, actor, &init->base);
    triGroup->count = init->count;
    triGroup->tris = tris;

    for (triElem = &triGroup->tris[0], triElemInit = &init->elemInit[0]; triElem < &triGroup->tris[triGroup->count]; triElem++, triElemInit++) {
        Collision_InitTriDefault(ctxt, triElem);
        Collision_InitTriWithData(ctxt, triElem, triElemInit);
    }

    return 1;
}

s32 Collision_InitTriGroup(GlobalContext *ctxt, ColTriGroup *triGroup, Actor *actor, ColTriGroupInit *init, ColTri *tris) {
    Collision_InitTriGroupDefault(ctxt, triGroup);
    Collision_InitTriGroupWithData(ctxt, triGroup, actor, init, tris);
    return 0;
}

s32 Collision_ResetTriGroupForAT(GlobalContext *ctxt, ColCommon *collider) {
    ColTri *triElem;
    ColTriGroup* tris = (ColTriGroup*)collider;

    Collision_ResetCommonForAT(ctxt, &tris->base);

    for (triElem = &tris->tris[0]; triElem < &tris->tris[tris->count]; triElem++) {
        Collision_ResetTriForAT(ctxt, triElem);
    }
    return 1;
}

s32 Collision_ResetTriGroupForAC(GlobalContext *ctxt, ColCommon *collider) {
    ColTri *triElem;
    ColTriGroup* tris = (ColTriGroup*)collider;

    Collision_ResetCommonForAC(ctxt, &tris->base);

    for (triElem = &tris->tris[0]; triElem < &tris->tris[tris->count]; triElem++) {
        Collision_ResetTriForAC(ctxt, triElem);
    }
    return 1;
}

s32 Collision_ResetTriGroupForOT(GlobalContext *ctxt, ColCommon *collider) {
    ColTri *triElem;
    ColTriGroup* tris = (ColTriGroup*)collider;

    Collision_ResetCommonForOT(ctxt, &tris->base);

    for (triElem = &tris->tris[0]; triElem < &tris->tris[tris->count]; triElem++) {
        func_800E16AC(ctxt, triElem);
    }
    return 1;
}

s32 Collision_InitQuadParamsDefault(GlobalContext *ctxt, ColQuadParams *params) {
    static ColQuadParams defaultColQuadParams = {
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

s32 Collision_FiniQuadParams(GlobalContext* ctxt, ColQuadParams* params) {
    return 1;
}

s32 Collision_ResetQuadParamsForAT(GlobalContext *ctxt, ColQuadParams *params) {
    params->unk3C = 1.0E38f;
    return 1;
}

void Collision_QuadCalcMidpoints(ColQuadParams *params) {
    params->unk30.x = (params->quad[3].x + params->quad[2].x) * 0.5f;
    params->unk30.y = (params->quad[3].y + params->quad[2].y) * 0.5f;
    params->unk30.z = (params->quad[3].z + params->quad[2].z) * 0.5f;
    params->unk36.x = (params->quad[1].x + params->quad[0].x) * 0.5f;
    params->unk36.y = (params->quad[1].y + params->quad[0].y) * 0.5f;
    params->unk36.z = (params->quad[1].z + params->quad[0].z) * 0.5f;
}

s32 Collision_InitQuadParamsWithData(GlobalContext *ctxt, ColQuadParams *params, ColQuadParamsInit *init) {
    params->quad[0] = init->quad[0];
    params->quad[1] = init->quad[1];
    params->quad[2] = init->quad[2];
    params->quad[3] = init->quad[3];

    Collision_QuadCalcMidpoints(params);
    return 1;
}

s32 Collision_InitQuadDefault(GlobalContext *ctxt, ColQuad *quad) {
    Collision_InitCommonDefault(ctxt, &quad->base);
    Collision_InitBodyDefault(ctxt, &quad->body);
    Collision_InitQuadParamsDefault(ctxt, &quad->params);
    return 1;
}

s32 Collision_FiniQuad(GlobalContext *ctxt, ColQuad *quad) {
    Collision_FiniCommon(ctxt, &quad->base);
    Collision_FiniBody(ctxt, &quad->body);
    Collision_FiniQuadParams(ctxt, &quad->params);
    return 1;
}

s32 func_800E1EB8(GlobalContext *ctxt, ColQuad *quad, Actor *actor, ColQuadInitType1 *init) {
    func_800E05D4(ctxt, &quad->base, actor, &init->base);
    Collision_InitBodyWithData(ctxt, &quad->body, &init->body);
    Collision_InitQuadParamsWithData(ctxt, &quad->params, &init->params);
    return 1;
}

s32 Collision_InitQuadWithData(GlobalContext *ctxt, ColQuad *quad, Actor *actor, ColQuadInit *init) {
    Collision_InitCommonWithData(ctxt, &quad->base, actor, &init->base);
    Collision_InitBodyWithData(ctxt, &quad->body, &init->body);
    Collision_InitQuadParamsWithData(ctxt, &quad->params, &init->params);
    return 1;
}

s32 Collision_InitQuad(GlobalContext *ctxt, ColQuad *quad, Actor *actor, ColQuadInit *init) {
    Collision_InitQuadDefault(ctxt, quad);
    Collision_InitQuadWithData(ctxt, quad, actor, init);
    return 0;
}

s32 Collision_ResetQuadForAT(GlobalContext *ctxt, ColQuad *quad) {
    Collision_ResetCommonForAT(ctxt, &quad->base);
    Collision_ResetBodyForAT(ctxt, &quad->body);
    Collision_ResetQuadParamsForAT(ctxt, &quad->params);
    return 1;
}

s32 Collision_ResetQuadForAC(GlobalContext *ctxt, ColQuad *quad) {
    Collision_ResetCommonForAC(ctxt, &quad->base);
    Collision_ResetBodyForAC(ctxt, &quad->body);
    return 1;
}

s32 Collision_ResetQuadForOT(GlobalContext *ctxt, ColQuad *quad) {
    Collision_ResetCommonForOT(ctxt, &quad->base);
    Collision_ResetBodyForOT(ctxt, &quad->body);
    return 1;
}

s32 func_800E20A4(GlobalContext *ctxt, ColQuad *quad, Vec3f *a2) {
    f32 dstSq;
    Vec3f sp20;

    if (!(quad->body.unk15 & 4)) {
        return 1;
    }
    Math_Vec3s_ToVec3f(&sp20, &quad->params.unk30);
    dstSq = Math3D_DistanceSquared(&sp20, a2);

    if (dstSq < quad->params.unk3C) {
        quad->params.unk3C = dstSq;
    
        if (quad->body.unk18 != 0) {
            Collision_ResetCommonForAC(ctxt, quad->body.unk18);
        }
        if (quad->body.unk20 != 0) {
            Collision_ResetBodyForAC(ctxt, quad->body.unk20);
        }
        return 1;
    } else {
        return 0;
    }
}


s32 Collision_InitSphereDefault(GlobalContext *ctxt, ColSphere *sphere) {
    Collision_InitCommonDefault(ctxt, &sphere->base);
    Collision_InitBodyDefault(ctxt, &sphere->body);
    Collision_InitSphereParamsDefault(ctxt, &sphere->params);
    return 1;
}

s32 Collision_FiniSphere(GlobalContext *pzParm1, ColSphere *sphere) {
    Collision_FiniCommon(pzParm1, &sphere->base);
    Collision_FiniBody(pzParm1, &sphere->body);
    Collision_FiniSphereParams(pzParm1, &sphere->params);
    return 1;
}

s32 Collision_InitSphereWithData(GlobalContext *ctxt, ColSphere *sphere, Actor *actor, ColSphereInit *info) {
    Collision_InitCommonWithData(ctxt, &sphere->base, actor, &info->base);
    Collision_InitBodyWithData(ctxt, &sphere->body, &info->body);
    Collision_InitSphereParamsWithData(ctxt, &sphere->params, &info->info);
    return 1;
}

s32 Collision_InitSphere(GlobalContext *ctxt, ColSphere *sphere, Actor *actor, ColSphereInit *init) {
    Collision_InitSphereDefault(ctxt, sphere);
    Collision_InitSphereWithData(ctxt, sphere, actor, init);
    return 0;
}

s32 Collision_ResetSphereForAT(GlobalContext *ctxt, ColSphere *sphere) {
    Collision_ResetCommonForAT(ctxt, &sphere->base);
    Collision_ResetBodyForAT(ctxt, &sphere->body);
    return 1;
}

s32 Collision_ResetSphereForAC(GlobalContext *ctxt, ColSphere *sphere) {
    Collision_ResetCommonForAC(ctxt, &sphere->base);
    Collision_ResetBodyForAC(ctxt, &sphere->body);
    return 1;
}

s32 Collision_ResetSphereForOT(GlobalContext *ctxt, ColSphere *sphere) {
    Collision_ResetCommonForOT(ctxt, &sphere->base);
    Collision_ResetBodyForOT(ctxt, &sphere->body);
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
    ColCommon** col;
    OcLine** line;

    if (colCtxt->flags & 1) {
        return;
    }

    colCtxt->ATgroupLength = 0;
    colCtxt->ACgroupLength = 0;
    colCtxt->OTgroupLength = 0;
    colCtxt->group4Length = 0;

    for (col = &colCtxt->ATgroup[0]; col < &colCtxt->ATgroup[ARRAY_COUNT(colCtxt->ATgroup)]; col++) {
        *col = NULL;
    }

    for (col = &colCtxt->ACgroup[0]; col < &colCtxt->ACgroup[ARRAY_COUNT(colCtxt->ACgroup)]; col++) {
        *col = NULL;
    }

    for (col = &colCtxt->OTgroup[0]; col < &colCtxt->OTgroup[ARRAY_COUNT(colCtxt->OTgroup)]; col++) {
        *col = NULL;
    }

    for (line = &colCtxt->group4[0]; line < &colCtxt->group4[ARRAY_COUNT(colCtxt->group4)]; line++) {
        *line = NULL;
    }
}

void Collision_EnableEditMode(GlobalContext *ctxt, CollisionCheckContext *colCtxt) {
    colCtxt->flags |= 1;
}

void Collision_EnableAppendMode(GlobalContext *ctxt, CollisionCheckContext *colCtxt) {
    colCtxt->flags &= ~1;
}

collision_add_func collisionAddATFuncs[] = {
    Collision_ResetSphereGroupForAT,
    Collision_ResetCylinderForAT,
    Collision_ResetTriGroupForAT,
    Collision_ResetQuadForAT,
    Collision_ResetSphereForAT,
};

s32 Collision_AddAT(GlobalContext *ctxt, CollisionCheckContext *colCtxt, ColCommon *shape) {
    s32 index;

    if (func_8016A01C(ctxt)) {
        return -1;
    }
    collisionAddATFuncs[shape->type](ctxt, shape);

    if (shape->actor != NULL && shape->actor->update == NULL) {
        return -1;
    }
    if (colCtxt->ATgroupLength >= ARRAY_COUNT(colCtxt->ATgroup)) {
        return -1;
    }
    if (colCtxt->flags & 1) {
        return -1;
    }
    index = colCtxt->ATgroupLength;

    colCtxt->ATgroup[colCtxt->ATgroupLength] = shape;
    colCtxt->ATgroupLength++;

    return index;
}

s32 Collision_AddIndexAT(GlobalContext *ctxt, CollisionCheckContext *colCtxt, ColCommon *shape, s32 index) {
    if (func_8016A01C(ctxt)) {
        return -1;
    }
    collisionAddATFuncs[shape->type](ctxt, shape);

    if (shape->actor != NULL && shape->actor->update == NULL) {
        return -1;
    }
    if (colCtxt->flags & 1) {
        if (index >= colCtxt->ATgroupLength) {
            return -1;
        }
        colCtxt->ATgroup[index] = shape;
    } else {
        if (colCtxt->ATgroupLength >= ARRAY_COUNT(colCtxt->ATgroup)) {
            return -1;
        }
        index = colCtxt->ATgroupLength;

        colCtxt->ATgroup[colCtxt->ATgroupLength] = shape;
        colCtxt->ATgroupLength++;
    }
    return index;
}

collision_add_func collisionAddACFuncs[] = {
    Collision_ResetSphereGroupForAC,
    Collision_ResetCylinderForAC,
    Collision_ResetTriGroupForAC,
    Collision_ResetQuadForAC,
    Collision_ResetSphereForAC,
};

s32 Collision_AddAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, ColCommon *shape) {
    s32 index;

    if (func_8016A01C(ctxt)) {
        return -1;
    }
    collisionAddACFuncs[shape->type](ctxt, shape);

    if (shape->actor != NULL && shape->actor->update == NULL) {
        return -1;
    }
    if (colCtxt->ACgroupLength >= ARRAY_COUNT(colCtxt->ACgroup)) {
        return -1;
    }
    if (colCtxt->flags & 1) {
        return -1;
    }
    index = colCtxt->ACgroupLength;

    colCtxt->ACgroup[colCtxt->ACgroupLength] = shape;
    colCtxt->ACgroupLength++;

    return index;
}

// TODO fix capitalization
s32 collision_AddIndexAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, ColCommon *shape, s32 index) {
    if (func_8016A01C(ctxt)) {
        return -1;
    }
    collisionAddACFuncs[shape->type](ctxt, shape);

    if (shape->actor != NULL && shape->actor->update == NULL) {
        return -1;
    }
    if (colCtxt->flags & 1) {
        if (index >= colCtxt->ACgroupLength) {
            return -1;
        }
        colCtxt->ACgroup[index] = shape;
    } else {
        if (colCtxt->ACgroupLength >= ARRAY_COUNT(colCtxt->ACgroup)) {
            return -1;
        }
        index = colCtxt->ACgroupLength;

        colCtxt->ACgroup[colCtxt->ACgroupLength] = shape;
        colCtxt->ACgroupLength++;
    }
    return index;
}

collision_add_func collisionAddOTFuncs[] = {
    Collision_ResetSphereGroupForOT,
    Collision_ReseCylinderForOT,
    Collision_ResetTriGroupForOT,
    Collision_ResetQuadForOT,
    Collision_ResetSphereForOT,
};

s32 Collision_AddOT(GlobalContext* ctxt, CollisionCheckContext* colCtxt, ColCommon* shape) {
    s32 index;

    if (func_8016A01C(ctxt)) {
        return -1;
    }
    collisionAddOTFuncs[shape->type](ctxt, shape);

    if (shape->actor != NULL && shape->actor->update == NULL) {
        return -1;
    }
    if (colCtxt->OTgroupLength >= ARRAY_COUNT(colCtxt->OTgroup)) {
        return -1;
    }
    if (colCtxt->flags & 1) {
        return -1;
    }
    index = colCtxt->OTgroupLength;

    colCtxt->OTgroup[colCtxt->OTgroupLength] = shape;
    colCtxt->OTgroupLength++;

    return index;
}

s32 Collision_AddIndexOT(GlobalContext *ctxt, CollisionCheckContext *colCtxt, ColCommon *shape, s32 index) {
    if (func_8016A01C(ctxt)) {
        return -1;
    }
    collisionAddOTFuncs[shape->type](ctxt, shape);

    if (shape->actor != NULL && shape->actor->update == NULL) {
        return -1;
    }
    if (colCtxt->flags & 1) {
        if (index >= colCtxt->OTgroupLength) {
            return -1;
        }
        //! @bug should be OTgroup
        colCtxt->ATgroup[index] = shape;
    } else {
        if (colCtxt->OTgroupLength >= ARRAY_COUNT(colCtxt->OTgroup)) {
            return -1;
        }
        index = colCtxt->OTgroupLength;

        colCtxt->OTgroup[colCtxt->OTgroupLength] = shape;
        colCtxt->OTgroupLength++;
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

    if (colCtxt->group4Length >= ARRAY_COUNT(colCtxt->group4)) {
        return -1;
    }
    index = colCtxt->group4Length;

    colCtxt->group4[colCtxt->group4Length] = line;
    colCtxt->group4Length++;

    return index;
}

s32 Collision_CantBeToucherAC(ColBodyInfo *iParm1) {
    if (!(iParm1->unk15 & 1)) {
        return 1;
    } else {
        return 0;
    }
}

s32 Collision_CantBeBumperAC(ColBodyInfo *iParm1) {
    if (!(iParm1->unk16 & 1)) {
        return 1;
    } else {
        return 0;
    }
}

s32 Collision_ToucherIsExcluded(ColBodyInfo *toucher, ColBodyInfo *bumper) {
    if (!(toucher->toucher.collidesWith & bumper->bumper.collidesWith)) {
        return 1;
    } else {
        return 0;
    }
}

void func_800E2C08(GlobalContext* ctxt, ColCommon* shape, Vec3f* v) {
}

#ifdef NON_MATCHING
// needs in-function static bss
void func_800E2C1C(GlobalContext *ctxt, ColCommon *shape, Vec3f *v) {
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
void func_800E2D88(GlobalContext *ctxt, ColCommon *shape, Vec3f *v) {
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

void func_800E2EF4(GlobalContext *ctxt, ColCommon *shape, Vec3f *v) {
    func_800B249C(ctxt, v);
    func_800E8478(ctxt, v);
}

void func_800E2F30(GlobalContext *ctxt, ColCommon *shape, Vec3f *v) {
    func_800E8318(ctxt, v);
}

void func_800E2F54(GlobalContext *ctxt, ColCommon *shape, Vec3f *v) {
    func_800E8318(ctxt, v);
}

void func_800E2F78(GlobalContext* ctxt, ColBodyInfo* toucherBody, ColCommon* bumper, Vec3f* hitPos) {
    s32 flags = toucherBody->unk15 & 0x18;

    if (flags == 0 && bumper->unk14 != 9) {
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

s32 func_800E30C8(ColCommon* toucher, ColBodyInfo* bumperBody) {
    if (toucher->actor != 0 && toucher->actor->type == 2) {
        if (bumperBody->unk14 == 0) {
            func_8019F1C0(&toucher->actor->projectedPos, 0x1811);
        } else if (bumperBody->unk14 == 1) {
            func_8019F1C0(&toucher->actor->projectedPos, 0x1824);
        } else if (bumperBody->unk14 == 2) {
            func_8019F1C0(&toucher->actor->projectedPos, 0);
        } else if (bumperBody->unk14 == 3) {
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
    { 0x01, 0x00 },
    { 0x00, 0x01 },
    { 0x02, 0x01 },
    { 0x00, 0x00 },
    { 0x03, 0x05 },
    { 0x00, 0x02 },
    { 0x02, 0x00 },
    { 0x04, 0x00 },
    { 0x01, 0x02 },
    { 0x00, 0x03 },
    { 0x00, 0x05 },
    { 0x00, 0x03 },
    { 0x00, 0x03 },
    { 0x00, 0x04 },
};

void func_800E3168(GlobalContext *ctxt, ColCommon *toucher, ColBodyInfo *toucherBody, ColCommon *bumper, ColBodyInfo *bumperBody, Vec3f *param_6) {
    if (bumperBody->unk16 & 0x40) {
        return;
    }

    if (!(toucherBody->unk15 & 0x20) && (toucherBody->unk15 & 0x40)) {
        return;
    }

    if (bumper->actor != NULL) {
        D_801BA374[D_801BA38C[bumper->unk14].blood](ctxt, bumper, param_6);
    }
    if (bumper->actor != NULL) {
        if (D_801BA38C[bumper->unk14].effect == 3) {
            func_800E2F78(ctxt, toucherBody, bumper, param_6);
        } else if (D_801BA38C[bumper->unk14].effect == 4) {
            if (toucher->actor == NULL) {
                func_800E85D4(ctxt, param_6);
                play_sound(0x1837);
            } else {
                func_800E86E0(ctxt, param_6, &toucher->actor->projectedPos);
            }
        } else if (D_801BA38C[bumper->unk14].effect != 5) {
            func_800B2684(ctxt, D_801BA38C[bumper->unk14].effect, param_6);
            if (!(bumperBody->unk16 & 0x20)) {
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

void func_800E3304(ColCommon *toucher, ColCommon *bumper) {
    toucher->flagsAT |= 4;
    bumper->flagsAC |= 0x80;
}

s32 Collision_HandleCollisionATWithAC(GlobalContext *ctxt, ColCommon *toucher, ColBodyInfo *toucherBody, Vec3f *toucherLoc, ColCommon *bumper, ColBodyInfo *bumperBody, Vec3f *bumperLoc, Vec3f *param_8) {
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
    if ((bumper->flagsAC & 4) && toucher->actor != NULL && bumper->actor != NULL) {
        func_800E3304(toucher, bumper);
    }
    if (!(bumperBody->unk16 & 8)) {
        toucher->flagsAT |= 2;
        toucher->collisionAT = bumper->actor;
        toucherBody->unk18 = bumper;
        toucherBody->unk15 |= 2;
        toucherBody->unk20 = bumperBody;
        if (!(toucherBody->unk16 & 2)) {
            toucherBody->bumper.unk6.x = param_8->x;
            toucherBody->bumper.unk6.y = param_8->y;
            toucherBody->bumper.unk6.z = param_8->z;
        }
        if (toucher->actor != NULL) {
            toucher->actor->unkA0.atHitEffect = bumperBody->bumper.unk4;
        }
    }
    if (!(toucherBody->unk17 & 4)) {
        bumper->flagsAC |= 2;
        bumper->collisionAC = toucher->actor;
        bumperBody->unk1C = toucher;
        bumperBody->unk24 = toucherBody;
        bumperBody->unk16 |= 2;
        if (bumper->actor != NULL) {
            bumper->actor->unkA0.acHitEffect = toucherBody->toucher.unk4;
        }
        bumperBody->bumper.unk6.x = param_8->x;
        bumperBody->bumper.unk6.y = param_8->y;
        bumperBody->bumper.unk6.z = param_8->z;
    }
    if (!(toucherBody->unk15 & 0x20) &&  bumper->unk14 != 9 && bumper->unk14 != 0xB && bumper->unk14 != 0xC) {
        bumperBody->unk16 |= 0x80;
    } else {
        func_800E3168(ctxt, toucher, toucherBody, bumper, bumperBody, param_8);
        toucherBody->unk15 |= 0x40;
    }
    return 1;
}

void Collision_TriCalcAvgPoint(ColTri *tri, Vec3f *avg) {
    f32 temp_f0 = 1.0f / 3.0f;

    avg->x = (tri->params.vtx[0].x + tri->params.vtx[1].x + tri->params.vtx[2].x) * temp_f0;
    avg->y = (tri->params.vtx[0].y + tri->params.vtx[1].y + tri->params.vtx[2].y) * temp_f0;
    avg->z = (tri->params.vtx[0].z + tri->params.vtx[1].z + tri->params.vtx[2].z) * temp_f0;
}

void collision_quad_cal_avg_point(ColQuad *quad, Vec3f *avg) {
    avg->x = (quad->params.quad[0].x + (quad->params.quad[1].x + (quad->params.quad[3].x + quad->params.quad[2].x))) / 4.0f;
    avg->y = (quad->params.quad[0].y + (quad->params.quad[1].y + (quad->params.quad[3].y + quad->params.quad[2].y))) / 4.0f;
    avg->z = (quad->params.quad[0].z + (quad->params.quad[1].z + (quad->params.quad[3].z + quad->params.quad[2].z))) / 4.0f;
}

void Collision_SphereGroupWithSphereGroupAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, ColCommon *toucher, ColCommon *bumpee) {
    ColSphereGroup* at = (ColSphereGroup*)toucher;
    ColSphereGroupElement* sphElem;
    ColSphereGroup* ac = (ColSphereGroup*)bumpee;
    ColSphereGroupElement* sphElem2;
    f32 sp8C;
    f32 sp88;

    if (at->count > 0 && at->spheres != NULL && ac->count > 0 && ac->spheres != NULL) {
        for (sphElem = &at->spheres[0]; sphElem < &at->spheres[at->count]; sphElem++) {
            if (Collision_CantBeToucherAC(&sphElem->body)) {
                continue;
            }

            for (sphElem2 = &ac->spheres[0]; sphElem2 < &ac->spheres[ac->count]; sphElem2++) {
                if (Collision_CantBeBumperAC(&sphElem2->body)) {
                    continue;
                }
                if (Collision_ToucherIsExcluded(&sphElem->body, &sphElem2->body)) {
                    continue;
                }

                if (Math3D_ColSphereSphereIntersectAndDistance(&sphElem->params.colInfo, &sphElem2->params.colInfo, &sp8C, &sp88) != 0) {
                    f32 temp_f0;
                    Vec3f sp78;
                    Vec3f sp6C;
                    Vec3f sp60;

                    Math_Vec3s_ToVec3f(&sp6C, &sphElem->params.colInfo.loc);
                    Math_Vec3s_ToVec3f(&sp60, &sphElem2->params.colInfo.loc);

                    if (!(fabsf(sp88) < 0.008f)) {
                        temp_f0 = sphElem2->params.colInfo.radius / sp88;
                        sp78.x = ((sp6C.x - sp60.x) * temp_f0) + sp60.x;
                        sp78.y = ((sp6C.y - sp60.y) * temp_f0) + sp60.y;
                        sp78.z = ((sp6C.z - sp60.z) * temp_f0) + sp60.z;
                    } else {
                        Math_Vec3f_Copy(&sp78, &sp6C);
                    }

                    Collision_HandleCollisionATWithAC(ctxt, &at->base, &sphElem->body, &sp6C, &ac->base, &sphElem2->body, &sp60, &sp78);

                    if (!(ac->base.unk13 & 0x40)) {
                        return;
                    }
                }
            }
        }
    }
}

void Collision_SphereGroupWithCylinderAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, ColCommon *toucher, ColCommon *bumpee) {
    ColSphereGroup* at = (ColSphereGroup*)toucher;
    ColSphereGroupElement *sphElem;
    ColCylinder* ac = (ColCylinder*)bumpee;
    f32 sp80;
    f32 sp7C;

    if (at->count > 0 && at->spheres != NULL && ac->params.radius > 0 && ac->params.height > 0) {
        if (Collision_CantBeBumperAC(&ac->body)) {
            return;
        }
        for (sphElem = &at->spheres[0]; sphElem < &at->spheres[at->count]; sphElem++) {
            if (Collision_CantBeToucherAC(&sphElem->body)) {
                continue;
            }
            if (Collision_ToucherIsExcluded(&sphElem->body, &ac->body)) {
                continue;
            }
            if (Math3D_ColSphereCylinderDistanceAndAmount(&sphElem->params.colInfo, &ac->params, &sp80, &sp7C)) {
                Vec3f sp70;
                Vec3f sp64;
                Vec3f sp58;
                f32 temp_f0;

                Math_Vec3s_ToVec3f(&sp64, &sphElem->params.colInfo.loc);
                Math_Vec3s_ToVec3f(&sp58, &ac->params.loc);
                if (!(fabsf(sp7C) < 0.008f)) {
                    temp_f0 = ac->params.radius / sp7C;
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
                Collision_HandleCollisionATWithAC(ctxt, &at->base, &sphElem->body, &sp64, &ac->base, &ac->body, &sp58, &sp70);
                return;
            }
        }
    }
}

void Collision_SphereGroupWithTriGroupAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, ColCommon *toucher, ColCommon *bumpee) {
    ColSphereGroup *at = (ColSphereGroup*)toucher;
    ColSphereGroupElement *sphElem;
    ColTriGroup *ac = (ColTriGroup*)bumpee;
    ColTri *triElem;
    Vec3f sp6C;

    if (at->count > 0 && at->spheres != NULL && ac->count > 0 && ac->tris != NULL) {
        for (sphElem = &at->spheres[0]; sphElem < &at->spheres[at->count]; sphElem++) {
            if (Collision_CantBeToucherAC(&sphElem->body)) {
                continue;
            }
            for (triElem = ac->tris; triElem < &ac->tris[ac->count]; triElem++) {
                if (Collision_CantBeBumperAC(&triElem->body)) {
                    continue;
                }
                if (Collision_ToucherIsExcluded(&sphElem->body, &triElem->body)) {
                    continue;
                }
                if (Math3D_ColSphereTri(&sphElem->params.colInfo, &triElem->params, &sp6C) != 0) {
                    Vec3f sp60;
                    Vec3f sp54;

                    Math_Vec3s_ToVec3f(&sp60, &sphElem->params.colInfo.loc);
                    Collision_TriCalcAvgPoint(triElem, &sp54);
                    Collision_HandleCollisionATWithAC(ctxt, &at->base, &sphElem->body, &sp60, &ac->base, &triElem->body, &sp54, &sp6C);
                    return;
                }
            }
        }
    }
}

void Collision_SphereGroupWithQuadAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, ColCommon *toucher, ColCommon *bumpee) {
    ColSphereGroup* at = (ColSphereGroup*)toucher;
    ColQuad *ac = (ColQuad*)bumpee;
    Vec3f sp74;
    ColSphereGroupElement *sphElem;

    if (at->count > 0 && at->spheres != NULL) {
        if (Collision_CantBeBumperAC(&ac->body)) {
            return;
        }
        Math3D_TriSetCoords(&D_801EF590, &ac->params.quad[2], &ac->params.quad[3], &ac->params.quad[1]);
        Math3D_TriSetCoords(&D_801EF5C8, &ac->params.quad[1], &ac->params.quad[0], &ac->params.quad[2]);

        for (sphElem = &at->spheres[0]; sphElem < &at->spheres[at->count]; sphElem++) {
            if (Collision_CantBeToucherAC(&sphElem->body)) {
                continue;
            }
            if (Collision_ToucherIsExcluded(&sphElem->body, &ac->body)) {
                continue;
            }
            if (Math3D_ColSphereTri(&sphElem->params.colInfo, &D_801EF590, &sp74) != 0 || 
                Math3D_ColSphereTri(&sphElem->params.colInfo, &D_801EF5C8, &sp74) != 0) {
                Vec3f sp64;
                Vec3f sp58;

                Math_Vec3s_ToVec3f(&sp64, &sphElem->params.colInfo.loc);
                collision_quad_cal_avg_point(ac, &sp58);
                Collision_HandleCollisionATWithAC(ctxt, &at->base, &sphElem->body, &sp64, &ac->base, &ac->body, &sp58, &sp74);
                return;
            }
        }
    }
}

void Collision_SphereGroupWithSphereAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, ColCommon *toucher, ColCommon *bumpee) {
    ColSphereGroup* at = (ColSphereGroup*)toucher;
    ColSphere* ac = (ColSphere*)bumpee;
    ColSphereGroupElement *sphElem;
    f32 sp90;
    f32 sp8C;

    if (at->count > 0 && at->spheres != NULL) {
        if (Collision_CantBeBumperAC(&ac->body)) {
            return;
        }
        for (sphElem = &at->spheres[0]; sphElem < &at->spheres[at->count]; sphElem++) {
            if (Collision_CantBeToucherAC(&sphElem->body)) {
                continue;
            }
            if (Collision_ToucherIsExcluded(&sphElem->body, &ac->body)) {
                continue;
            }
            if (Math3D_ColSphereSphereIntersectAndDistance(&sphElem->params.colInfo, &ac->params.colInfo, &sp90, &sp8C) != 0) {
                f32 temp_f0;
                Vec3f sp7C;
                Vec3f sp70;
                Vec3f sp64;

                Math_Vec3s_ToVec3f(&sp70, &sphElem->params.colInfo.loc);
                Math_Vec3s_ToVec3f(&sp64, &ac->params.colInfo.loc);
                if (!(fabsf(sp8C) < 0.008f)) {
                    temp_f0 = ac->params.colInfo.radius / sp8C;
                    sp7C.x = ((sp70.x - sp64.x) * temp_f0) + sp64.x;
                    sp7C.y = ((sp70.y - sp64.y) * temp_f0) + sp64.y;
                    sp7C.z = ((sp70.z - sp64.z) * temp_f0) + sp64.z;
                } else {
                    Math_Vec3f_Copy(&sp7C, &sp70);
                }
                Collision_HandleCollisionATWithAC(ctxt, &at->base, &sphElem->body, &sp70, &ac->base, &ac->body, &sp64, &sp7C);
            }
        }
    }
}

void Collision_CylinderWithSphereGroupAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, ColCommon *toucher, ColCommon *bumpee) {
    ColCylinder* at = (ColCylinder*)toucher;
    ColSphereGroup* ac = (ColSphereGroup*)bumpee;
    f32 sp9C;
    f32 sp98;
    f32 temp_f0;
    Vec3f sp88;
    Vec3f sp7C;
    Vec3f sp70;
    ColSphereCollisionInfo *temp_s0;
    ColSphereGroupElement *sphElem;

    if (ac->count > 0 && ac->spheres != NULL && at->params.radius > 0 && at->params.height > 0) {
        if (Collision_CantBeToucherAC(&at->body)) {
            return;
        }
        for (sphElem = &ac->spheres[0]; sphElem < &ac->spheres[ac->count]; sphElem++) {
            if (Collision_CantBeBumperAC(&sphElem->body)) {
                continue;
            }
            if (Collision_ToucherIsExcluded(&at->body, &sphElem->body)) {
                continue;
            }
            if (Math3D_ColSphereCylinderDistanceAndAmount(&sphElem->params.colInfo, &at->params, &sp9C, &sp98) != 0) {

                Math_Vec3s_ToVec3f(&sp7C, &at->params.loc);
                Math_Vec3s_ToVec3f(&sp70, &sphElem->params.colInfo.loc);
                if (!(fabsf(sp98) < 0.008f)) {
                    temp_f0 = sphElem->params.colInfo.radius / sp98;
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
                Collision_HandleCollisionATWithAC(ctxt, &at->base, &at->body, &sp7C, &ac->base, &sphElem->body, &sp70, &sp88);
                if (!(ac->base.unk13 & 0x40)) {
                    break;
                }
            }
        }
    }
}

void Collision_CylinderWithCylinderAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, ColCommon *toucher, ColCommon *bumpee) {
    ColCylinder* at = (ColCylinder*)toucher;
    ColCylinder* ac = (ColCylinder*)bumpee;
    f32 sp6C;
    f32 sp68;
    Vec3f sp5C;

    if (at->params.radius > 0 && at->params.height > 0 && ac->params.radius > 0 && ac->params.height > 0) {
        if (Collision_CantBeBumperAC(&ac->body)) {
            return;
        }
        if (Collision_CantBeToucherAC(&at->body)) {
            return;
        }
        if (Collision_ToucherIsExcluded(&at->body, &ac->body)) {
            return;
        }

        if (Math3D_ColCylinderCylinderAmountAndDistance(&at->params, &ac->params, &sp6C, &sp68) != 0) {
            Vec3f sp50;
            Vec3f sp44;

            Math_Vec3s_ToVec3f(&sp50, &at->params.loc);
            Math_Vec3s_ToVec3f(&sp44, &ac->params.loc);
            if (!(fabsf(sp68) < 0.008f)) {
                f32 temp_f12 = ac->params.radius / sp68;
                f32 tmp;

                sp5C.y = (f32)at->params.loc.y + at->params.yOffset + at->params.height * 0.5f;
                tmp = (f32)ac->params.loc.y + ac->params.yOffset;

                if (sp5C.y < tmp) {
                    sp5C.y = tmp;
                } else {
                    tmp += ac->params.height;
                    if (sp5C.y > tmp) {
                        sp5C.y = tmp;
                    }
                }
                sp5C.x = ((f32)at->params.loc.x - ac->params.loc.x) * temp_f12 + ac->params.loc.x;
                sp5C.z = ((f32)at->params.loc.z - ac->params.loc.z) * temp_f12 + ac->params.loc.z;
            } else {
                Math_Vec3s_ToVec3f(&sp5C, &ac->params.loc);
            }
            Collision_HandleCollisionATWithAC(ctxt, &at->base, &at->body, &sp50, &ac->base, &ac->body, &sp44, &sp5C);
        }
    }
}

void Collision_CylinderWithTriGroupAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, ColCommon *toucher, ColCommon *bumpee) {
    ColCylinder* at = (ColCylinder*)toucher;
    ColTriGroup* ac = (ColTriGroup*)bumpee;
    ColTri *triElem;
    Vec3f sp60;

    if (at->params.radius > 0 && at->params.height > 0 && ac->count > 0 && ac->tris != 0) {
        if (Collision_CantBeToucherAC(&at->body)) {
            return;
        }
        
        for (triElem = &ac->tris[0]; triElem < &ac->tris[ac->count]; triElem++) {
            if (Collision_CantBeBumperAC(&triElem->body)) {
                continue;
            }
            if (Collision_ToucherIsExcluded(&at->body, &triElem->body)) {
                continue;
            }

            if (Math3D_ColCylinderTri(&at->params, &triElem->params, &sp60) != 0) {
                Vec3f sp54;
                Vec3f sp48;

                Math_Vec3s_ToVec3f(&sp54, &at->params.loc);
                Collision_TriCalcAvgPoint(triElem, &sp48);
                Collision_HandleCollisionATWithAC(ctxt, &at->base, &at->body, &sp54, &ac->base, &triElem->body, &sp48, &sp60);
                return;
            }
        }
    }
}

void Collision_CylinderWithQuadAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, ColCommon *toucher, ColCommon *bumpee) {
    ColCylinder* at = (ColCylinder*)toucher;
    ColQuad* ac = (ColQuad*)bumpee;
    Vec3f sp64;
    Vec3f sp58;
    Vec3f sp4C;
    Vec3f sp40;

    if (at->params.height > 0 && at->params.radius > 0) {
        if (Collision_CantBeToucherAC(&at->body)) {
            return;
        }
        if (Collision_CantBeBumperAC(&ac->body)) {
            return;
        }
        if (Collision_ToucherIsExcluded(&at->body, &ac->body)) {
            return;
        }

        Math3D_TriSetCoords(&D_801EF600, &ac->params.quad[2], &ac->params.quad[3], &ac->params.quad[1]);
        Math3D_TriSetCoords(&D_801EF638, &ac->params.quad[1], &ac->params.quad[0], &ac->params.quad[2]);
        if (Math3D_ColCylinderTri(&at->params, &D_801EF600, &D_801EDE00) != 0) {
            Math_Vec3s_ToVec3f(&sp64, &at->params.loc);
            collision_quad_cal_avg_point(ac, &sp58);
            Collision_HandleCollisionATWithAC(ctxt, &at->base, &at->body, &sp64, &ac->base, &ac->body, &sp58, &D_801EDE00);
        } else if (Math3D_ColCylinderTri(&at->params, &D_801EF638, &D_801EDE00) != 0) {
            Math_Vec3s_ToVec3f(&sp4C, &at->params.loc);
            collision_quad_cal_avg_point(ac, &sp40);
            Collision_HandleCollisionATWithAC(ctxt, &at->base, &at->body, &sp4C, &ac->base, &ac->body, &sp40, &D_801EDE00);
        }
    }
}

void Collision_CylinderWithSphereAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, ColCommon *toucher, ColCommon *bumpee) {
    ColCylinder* at = (ColCylinder*)toucher;
    ColSphere* ac = (ColSphere*)bumpee;
    f32 sp6C;
    f32 sp68;

    if (at->params.radius > 0 && at->params.height > 0) {
        if (Collision_CantBeToucherAC(&at->body)) {
            return;
        }
        if (Collision_CantBeBumperAC(&ac->body)) {
            return;
        }
        if (Collision_ToucherIsExcluded(&at->body, &ac->body)) {
            return;
        }

        if (Math3D_ColSphereCylinderDistanceAndAmount(&ac->params.colInfo, &at->params, &sp6C, &sp68) != 0) {
            Vec3f sp5C;
            Vec3f sp50;
            Vec3f sp44;
            f32 temp_f0;

            Math_Vec3s_ToVec3f(&sp50, &at->params.loc);
            Math_Vec3s_ToVec3f(&sp44, &ac->params.colInfo.loc);

            if (!(fabsf(sp68) < 0.008f)) {
                temp_f0 = ac->params.colInfo.radius / sp68;
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
            Collision_HandleCollisionATWithAC(ctxt, &at->base, &at->body, &sp50, &ac->base, &ac->body, &sp44, &sp5C);
        }
    }
}

void Collision_TriGroupWithSphereGroupAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, ColCommon *toucher, ColCommon *bumpee) {
    ColTriGroup* at = (ColTriGroup*)toucher;
    ColSphereGroupElement *sphElem;
    ColSphereGroup* ac = (ColSphereGroup*)bumpee;
    ColTri *triElem;
    Vec3f sp74;

    if (ac->count > 0 && ac->spheres != 0 && at->count > 0 && at->tris != 0) {
        for (sphElem = &ac->spheres[0]; sphElem < &ac->spheres[ac->count]; sphElem++) {
            if (Collision_CantBeBumperAC(&sphElem->body)) {
                continue;
            }
            for (triElem = &at->tris[0]; triElem < &at->tris[at->count]; triElem++) {
                if (Collision_CantBeToucherAC(&triElem->body)) {
                    continue;
                }
                if (Collision_ToucherIsExcluded(&triElem->body, &sphElem->body)) {
                    continue;
                }
                if (Math3D_ColSphereTri(&sphElem->params.colInfo, &triElem->params, &sp74)) {
                    Vec3f sp68;
                    Vec3f sp5C;

                    Math_Vec3s_ToVec3f(&sp5C, &sphElem->params.colInfo.loc);
                    Collision_TriCalcAvgPoint(triElem, &sp68);
                    Collision_HandleCollisionATWithAC(ctxt, &at->base, &triElem->body, &sp68, &ac->base, &sphElem->body, &sp5C, &sp74);

                    if (!(ac->base.unk13 & 0x40)) {
                        return;
                    }
                }
            }
        }
    }
}

void Collision_TriGroupWithCylinderAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, ColCommon *toucher, ColCommon *bumpee) {
    ColTriGroup* at = (ColTriGroup*)toucher;
    ColCylinder* ac = (ColCylinder*)bumpee;
    ColTri *triElem;

    if (ac->params.radius > 0 && ac->params.height > 0 && at->count > 0 && at->tris != NULL) {
        if (Collision_CantBeBumperAC(&ac->body)) {
            return;
        }
        for (triElem = &at->tris[0]; triElem < &at->tris[at->count]; triElem++) {
            if (Collision_CantBeToucherAC(&triElem->body)) {
                continue;
            }
            if (Collision_ToucherIsExcluded(&triElem->body, &ac->body)) {
                continue;
            }
            if (Math3D_ColCylinderTri(&ac->params, &triElem->params, &D_801EDE10) != 0) {
                Vec3f sp58;
                Vec3f sp4C;

                Collision_TriCalcAvgPoint(triElem, &sp58);
                Math_Vec3s_ToVec3f(&sp4C, &ac->params.loc);
                Collision_HandleCollisionATWithAC(ctxt, &at->base, &triElem->body, &sp58, &ac->base, &ac->body, &sp4C, &D_801EDE10);
                return;
            }
        }
    }
}

void Collision_TriGroupWithTriGroupAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, ColCommon *toucher, ColCommon *bumpee) {
    ColTriGroup* at = (ColTriGroup*)toucher;
    ColTri *triElem;
    ColTriGroup* ac = (ColTriGroup*)bumpee;
    ColTri *triElem2;

    if (ac->count > 0 && ac->tris != NULL && at->count > 0 && at->tris != NULL) {
        for (triElem = &ac->tris[0]; triElem < &ac->tris[ac->count]; triElem++) {
            if (Collision_CantBeBumperAC(&triElem->body)) {
                continue;
            }
            for (triElem2 = &at->tris[0]; triElem2 < &at->tris[at->count]; triElem2++) {
                if (Collision_CantBeToucherAC(&triElem2->body)) {
                    continue;
                }
                if (Collision_ToucherIsExcluded(&triElem2->body, &triElem->body)) {
                    continue;
                }
                if (Math3d_ColTriTri(&triElem2->params, &triElem->params, &D_801EDE20) != 0) {
                    Vec3f sp5C;
                    Vec3f sp50;

                    Collision_TriCalcAvgPoint(triElem2, &sp5C);
                    Collision_TriCalcAvgPoint(triElem, &sp50);
                    Collision_HandleCollisionATWithAC(ctxt, &at->base, &triElem2->body, &sp5C, &ac->base, &triElem->body, &sp50, &D_801EDE20);
                    return;
                }
            }
        }
    }
}

void Collision_TriGroupWithQuad(GlobalContext *ctxt, CollisionCheckContext *colCtxt, ColCommon *toucher, ColCommon *bumpee) {
    ColTriGroup* at = (ColTriGroup*)toucher;
    ColQuad* ac = (ColQuad*)bumpee;
    ColTri *triElem;

    if (at->count > 0 && at->tris != NULL) {
        if (Collision_CantBeBumperAC(&ac->body)) {
            return;
        }

        Math3D_TriSetCoords(&D_801EDE40, &ac->params.quad[2], &ac->params.quad[3], &ac->params.quad[1]);
        Math3D_TriSetCoords(&D_801EDE78, &ac->params.quad[1], &ac->params.quad[0], &ac->params.quad[2]);

        for (triElem = &at->tris[0]; triElem < &at->tris[at->count]; triElem++) {
            if (Collision_CantBeToucherAC(&triElem->body)) {
                continue;
            }
            if (Collision_ToucherIsExcluded(&triElem->body, &ac->body)) {
                continue;
            }
            if (Math3d_ColTriTri(&D_801EDE40, &triElem->params, &D_801EDE30) != 0 ||
                Math3d_ColTriTri(&D_801EDE78, &triElem->params, &D_801EDE30) != 0) {
                Vec3f sp68;
                Vec3f sp5C;

                Collision_TriCalcAvgPoint(triElem, &sp68);
                collision_quad_cal_avg_point(ac, &sp5C);
                Collision_HandleCollisionATWithAC(ctxt, &at->base, &triElem->body, &sp68, &ac->base, &ac->body, &sp5C, &D_801EDE30);
                return;
            }
        }
    }
}

void Collision_TriGroupWithSphereAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, ColCommon *toucher, ColCommon *bumpee) {
    ColTriGroup* at = (ColTriGroup*)toucher;
    ColTri *triElem;
    ColSphere* ac = (ColSphere*)bumpee;
    Vec3f sp70;

    if (at->count > 0 && at->tris != NULL) {
        if (Collision_CantBeBumperAC(&ac->body)) {
            return;
        }
        for (triElem = &at->tris[0]; triElem < &at->tris[at->count]; triElem++) {
            if (Collision_CantBeToucherAC(&triElem->body)) {
                continue;
            }
            if (Collision_ToucherIsExcluded(&triElem->body, &ac->body)) {
                continue;
            }
            if (Math3D_ColSphereTri(&ac->params.colInfo, &triElem->params, &sp70) != 0) {
                Vec3f sp64;
                Vec3f sp58;

                Math_Vec3s_ToVec3f(&sp58, &ac->params.colInfo.loc);
                Collision_TriCalcAvgPoint(triElem, &sp64);
                Collision_HandleCollisionATWithAC(ctxt, &at->base, &triElem->body, &sp64, &ac->base, &ac->body, &sp58, &sp70);
            }
        }
    }
}

void Collision_QuadWithSphereGroupAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, ColCommon *toucher, ColCommon *bumpee) {
    ColSphereGroupElement *sphElem;
    Vec3f sp80;
    ColQuad* at = (ColQuad*)toucher;
    ColSphereGroup* ac = (ColSphereGroup*)bumpee;

    if (ac->count > 0 && ac->spheres != NULL) {
        if (Collision_CantBeToucherAC(&at->body)) {
            return;
        }
        Math3D_TriSetCoords(&D_801EDEC8, &at->params.quad[2], &at->params.quad[3], &at->params.quad[1]);
        Math3D_TriSetCoords(&D_801EDF00, &at->params.quad[2], &at->params.quad[1], &at->params.quad[0]);

        for (sphElem = &ac->spheres[0]; sphElem < &ac->spheres[ac->count]; sphElem++) {
            if (Collision_CantBeBumperAC(&sphElem->body)) {
                continue;
            }
            if (Collision_ToucherIsExcluded(&at->body, &sphElem->body)) {
                continue;
            }
            if (Math3D_ColSphereTri(&sphElem->params.colInfo, &D_801EDEC8, &sp80) != 0 || Math3D_ColSphereTri(&sphElem->params.colInfo, &D_801EDF00, &sp80) != 0) {
                Vec3f sp6C;
                Vec3f sp60;

                if (!func_800E20A4(ctxt, at, &sp80)) {
                    continue;
                }
                Math_Vec3s_ToVec3f(&sp60, &sphElem->params.colInfo.loc);
                collision_quad_cal_avg_point(at, &sp6C);
                Collision_HandleCollisionATWithAC(ctxt, &at->base, &at->body, &sp6C, &ac->base, &sphElem->body, &sp60, &sp80);

                if (!(ac->base.unk13 & 0x40)) {
                    break;
                }
            }
        }
    }
}

void Collision_QuadWithCylinderAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, ColCommon *toucher, ColCommon *bumpee) {
    ColQuad* at = (ColQuad*)toucher;
    ColCylinder* ac = (ColCylinder*)bumpee;

    if (ac->params.height > 0 && ac->params.radius > 0) {
        if (Collision_CantBeBumperAC(&ac->body)) {
            return;
        }
        if (Collision_CantBeToucherAC(&at->body)) {
            return;
        }
        if (Collision_ToucherIsExcluded(&at->body, &ac->body)) {
            return;
        }

        Math3D_TriSetCoords(&D_801EDF58, &at->params.quad[2], &at->params.quad[3], &at->params.quad[1]);
        Math3D_TriSetCoords(&D_801EDF90, &at->params.quad[2], &at->params.quad[1], &at->params.quad[0]);

        if (Math3D_ColCylinderTri(&ac->params, &D_801EDF58, &D_801EDFE0) != 0) {
            if (func_800E20A4(ctxt, at, &D_801EDFE0)) {
                Vec3f sp64;
                Vec3f sp58;

                collision_quad_cal_avg_point(at, &sp64);
                Math_Vec3s_ToVec3f(&sp58, &ac->params.loc);
                Collision_HandleCollisionATWithAC(ctxt, &at->base, &at->body, &sp64, &ac->base, &ac->body, &sp58, &D_801EDFE0);
                return;
            }
        }
        if (Math3D_ColCylinderTri(&ac->params, &D_801EDF90, &D_801EDFE0) != 0) {
            if (func_800E20A4(ctxt, at, &D_801EDFE0)) {
                Vec3f sp4C;
                Vec3f sp40;

                collision_quad_cal_avg_point(at, &sp4C);
                Math_Vec3s_ToVec3f(&sp40, &ac->params.loc);
                Collision_HandleCollisionATWithAC(ctxt, &at->base, &at->body, &sp4C, &ac->base, &ac->body, &sp40, &D_801EDFE0);
            }
        }
    }
}

void Collision_QuadWithTriGroupAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, ColCommon *toucher, ColCommon *bumpee) {
    ColQuad* at = (ColQuad*)toucher;
    ColTriGroup* ac = (ColTriGroup*)bumpee;
    ColTri *triElem;

    if (ac->count > 0 && ac->tris != NULL) {
        if (Collision_CantBeToucherAC(&at->body)) {
            return;
        }

        Math3D_TriSetCoords(&D_801EE000, &at->params.quad[2], &at->params.quad[3], &at->params.quad[1]);
        Math3D_TriSetCoords(&D_801EE038, &at->params.quad[1], &at->params.quad[0], &at->params.quad[2]);

        for (triElem = &ac->tris[0]; triElem < &ac->tris[ac->count]; triElem++) {
            if (Collision_CantBeBumperAC(&triElem->body)) {
                continue;
            }
            if (Collision_ToucherIsExcluded(&at->body, &triElem->body)) {
                continue;
            }

            if ((Math3d_ColTriTri(&D_801EE000, &triElem->params, &D_801EDFF0) != 0) || 
                (Math3d_ColTriTri(&D_801EE038, &triElem->params, &D_801EDFF0) != 0)) {
                if (func_800E20A4(ctxt, at, &D_801EDFF0)) {
                    Vec3f sp68;
                    Vec3f sp5C;

                    Collision_TriCalcAvgPoint(triElem, &sp5C);
                    collision_quad_cal_avg_point(at, &sp68);
                    Collision_HandleCollisionATWithAC(ctxt, &at->base, &at->body, &sp68, &ac->base, &triElem->body, &sp5C, &D_801EDFF0);
                    return;
                }
            }
        }
    }
}

void Collision_QuadWithQuadAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, ColCommon *toucher, ColCommon *bumpee) {
    ColQuad* at = (ColQuad*)toucher;
    ColQuad* ac = (ColQuad*)bumpee;
    s32 i;
    s32 j;

    if (Collision_CantBeToucherAC(&at->body)) {
        return;
    }
    if (Collision_CantBeBumperAC(&ac->body)) {
        return;
    }
    if (Collision_ToucherIsExcluded(&at->body, &ac->body)) {
        return;
    }

    Math3D_TriSetCoords(&D_801EE0E8[0], &at->params.quad[2], &at->params.quad[3], &at->params.quad[1]);
    Math3D_TriSetCoords(&D_801EE0E8[1], &at->params.quad[2], &at->params.quad[1], &at->params.quad[0]);
    Math3D_TriSetCoords(&D_801EE070[0], &ac->params.quad[2], &ac->params.quad[3], &ac->params.quad[1]);
    Math3D_TriSetCoords(&D_801EE070[1], &ac->params.quad[2], &ac->params.quad[1], &ac->params.quad[0]);

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            if (Math3d_ColTriTri(&D_801EE0E8[j], &D_801EE070[i], &D_801EE0D8) != 0 && func_800E20A4(ctxt, at, &D_801EE0D8) != 0) {
                Vec3f sp64;
                Vec3f sp58;

                collision_quad_cal_avg_point(at, &sp64);
                collision_quad_cal_avg_point(ac, &sp58);
                Collision_HandleCollisionATWithAC(ctxt, &at->base, &at->body, &sp64, &ac->base, &ac->body, &sp58, &D_801EE0D8);
                return;
            }
        }
    }
}

void Collision_QuadWithSphereAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, ColCommon *toucher, ColCommon *bumpee) {
    ColQuad* at = (ColQuad*)toucher;
    Vec3f sp60;
    ColSphere* ac = (ColSphere*)bumpee;

    if (Collision_CantBeToucherAC(&at->body)) {
        return;
    }
    if (Collision_CantBeBumperAC(&ac->body) || Collision_ToucherIsExcluded(&at->body, &ac->body)) {
        return;
    }

    Math3D_TriSetCoords(&D_801EE150, &at->params.quad[2], &at->params.quad[3], &at->params.quad[1]);
    Math3D_TriSetCoords(&D_801EE188, &at->params.quad[2], &at->params.quad[1], &at->params.quad[0]);

    if ((Math3D_ColSphereTri(&ac->params.colInfo, &D_801EE150, &sp60) != 0) || 
        (Math3D_ColSphereTri(&ac->params.colInfo, &D_801EE188, &sp60) != 0)) {
        if (func_800E20A4(ctxt, at, &sp60)) {
            Vec3f sp50;
            Vec3f sp44;

            Math_Vec3s_ToVec3f(&sp44, &ac->params.colInfo.loc);
            collision_quad_cal_avg_point(at, &sp50);
            Collision_HandleCollisionATWithAC(ctxt, &at->base, &at->body, &sp50, &ac->base, &ac->body, &sp44, &sp60);
        }
    }
}

void Collision_SphereWithSphereGroupAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, ColCommon *toucher, ColCommon *bumpee) {
    ColSphere* at = (ColSphere*)toucher;
    ColSphereGroup* ac = (ColSphereGroup*)bumpee;
    ColSphereGroupElement *sphElem;
    f32 sp90;
    f32 sp8C;

    if (ac->count > 0 && ac->spheres != NULL) {
        if (Collision_CantBeToucherAC(&at->body)) {
            return;
        }

        for (sphElem = &ac->spheres[0]; sphElem < &ac->spheres[ac->count]; sphElem++) {
            if (Collision_CantBeBumperAC(&sphElem->body)) {
                continue;
            }
            if (Collision_ToucherIsExcluded(&at->body, &sphElem->body)) {
                continue;
            }

            if (Math3D_ColSphereSphereIntersectAndDistance(&at->params.colInfo, &sphElem->params.colInfo, &sp90, &sp8C) != 0) {
                f32 temp_f0;
                Vec3f sp7C;
                Vec3f sp70;
                Vec3f sp64;

                Math_Vec3s_ToVec3f(&sp70, &at->params.colInfo.loc);
                Math_Vec3s_ToVec3f(&sp64, &sphElem->params.colInfo.loc);
                if (!(fabsf(sp8C) < 0.008f)) {
                    temp_f0 = sphElem->params.colInfo.radius / sp8C;
                    sp7C.x = (sp70.x - sp64.x) * temp_f0 + sp64.x;
                    sp7C.y = (sp70.y - sp64.y) * temp_f0 + sp64.y;
                    sp7C.z = (sp70.z - sp64.z) * temp_f0 + sp64.z;
                } else {
                    Math_Vec3f_Copy(&sp7C, &sp70);
                }
                Collision_HandleCollisionATWithAC(ctxt, &at->base, &at->body, &sp70, &ac->base, &sphElem->body, &sp64, &sp7C);
            }
        }
    }
}

void Collision_SphereWithCylinderAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, ColCommon *toucher, ColCommon *bumpee) {
    ColCylinder* ac = (ColCylinder*)bumpee;
    ColSphere* at = (ColSphere*)toucher;
    f32 sp6C;
    f32 sp68;

    if (Collision_CantBeToucherAC(&at->body)) {
        return;
    }
    if (Collision_CantBeBumperAC(&ac->body)) {
        return;
    }
    if (Collision_ToucherIsExcluded(&at->body, &ac->body)) {
        return;
    }

    if (Math3D_ColSphereCylinderDistanceAndAmount(&at->params.colInfo, &ac->params, &sp6C, &sp68) != 0) {
        Vec3f sp5C;
        Vec3f sp50;
        Vec3f sp44;

        Math_Vec3s_ToVec3f(&sp50, &at->params.colInfo.loc);
        Math_Vec3s_ToVec3f(&sp44, &ac->params.loc);

        if (!(fabsf(sp68) < 0.008f)) {
            f32 temp_f0 = ac->params.radius / sp68;

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
        Collision_HandleCollisionATWithAC(ctxt, &at->base, &at->body, &sp50, &ac->base, &ac->body, &sp44, &sp5C);
    }

    if (at) {}
}

void Collision_SphereWithTriGroupAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, ColCommon *toucher, ColCommon *bumpee) {
    ColSphere* at = (ColSphere*)toucher;
    ColTriGroup* ac = (ColTriGroup*)bumpee;
    ColTri *triElem;
    Vec3f sp68;

    if (Collision_CantBeToucherAC(&at->body)) {
        return;
    }

    for (triElem = &ac->tris[0]; triElem < &ac->tris[ac->count]; triElem++) {
        if (Collision_CantBeBumperAC(&triElem->body)) {
            continue;
        }
        if (Collision_ToucherIsExcluded(&at->body, &triElem->body)) {
            continue;
        }
        if (Math3D_ColSphereTri(&at->params.colInfo, &triElem->params, &sp68) != 0) {
            Vec3f sp5C;
            Vec3f sp50;

            Math_Vec3s_ToVec3f(&sp5C, &at->params.colInfo.loc);
            Collision_TriCalcAvgPoint(triElem, &sp50);
            Collision_HandleCollisionATWithAC(ctxt, &at->base, &at->body, &sp5C, &ac->base, &triElem->body, &sp50, &sp68);
            return;
        }
    }
}

void Collision_SphereWithQuadAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, ColCommon *toucher, ColCommon *bumpee) {
    ColSphere* at = (ColSphere*)toucher;
    Vec3f sp60;
    ColQuad* ac = (ColQuad*)bumpee;

    if (Collision_CantBeToucherAC(&at->body)) {
        return;
    }
    if (Collision_CantBeBumperAC(&ac->body) || Collision_ToucherIsExcluded(&at->body, &ac->body)) {
        return;
    }

    Math3D_TriSetCoords(&D_801EE6C8, &ac->params.quad[2], &ac->params.quad[3], &ac->params.quad[1]);
    Math3D_TriSetCoords(&D_801EE700, &ac->params.quad[1], &ac->params.quad[0], &ac->params.quad[2]);

    if (Math3D_ColSphereTri(&at->params.colInfo, &D_801EE6C8, &sp60) != 0 || 
        Math3D_ColSphereTri(&at->params.colInfo, &D_801EE700, &sp60) != 0) {
        Vec3f sp50;
        Vec3f sp44;

        Math_Vec3s_ToVec3f(&sp50, &at->params.colInfo.loc);
        collision_quad_cal_avg_point(ac, &sp44);
        Collision_HandleCollisionATWithAC(ctxt, &at->base, &at->body, &sp50, &ac->base, &ac->body, &sp44, &sp60);
    }
}

void Collision_SphereWithSphereAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, ColCommon *toucher, ColCommon *bumpee) {
    ColSphere* at = (ColSphere*)toucher;
    ColSphere* ac = (ColSphere*)bumpee;
    f32 sp6C;
    f32 sp68;

    if (Collision_CantBeToucherAC(&at->body)) {
        return;
    }
    if (Collision_CantBeBumperAC(&ac->body)) {
        return;
    }
    if (Collision_ToucherIsExcluded(&at->body, &ac->body)) {
        return;
    }

    if (Math3D_ColSphereSphereIntersectAndDistance(&at->params.colInfo, &ac->params.colInfo, &sp6C, &sp68) != 0) {
        f32 temp_f0;
        Vec3f sp58;
        Vec3f sp4C;
        Vec3f sp40;

        Math_Vec3s_ToVec3f(&sp4C, &at->params.colInfo.loc);
        Math_Vec3s_ToVec3f(&sp40, &ac->params.colInfo.loc);
        if (!(fabsf(sp68) < 0.008f)) {
            temp_f0 = ac->params.colInfo.radius / sp68;
            sp58.x = (sp4C.x - sp40.x) * temp_f0 + sp40.x;
            sp58.y = (sp4C.y - sp40.y) * temp_f0 + sp40.y;
            sp58.z = (sp4C.z - sp40.z) * temp_f0 + sp40.z;
        } else {
            Math_Vec3f_Copy(&sp58, &sp4C);
        }
        Collision_HandleCollisionATWithAC(ctxt, &at->base, &at->body, &sp4C, &ac->base, &ac->body, &sp40, &sp58);
    }
}

void func_800E60C0(GlobalContext *ctxt, CollisionCheckContext *colCtxt, ColCommon *shape) {
    ColSphereGroup *sphereGroup = (ColSphereGroup*)shape;
    ColSphereGroupElement *sphElem;

    for (sphElem = &sphereGroup->spheres[0]; sphElem < &sphereGroup->spheres[sphereGroup->count]; sphElem++) {
        if ((sphElem->body.unk16 & 0x80) && sphElem->body.unk24 != 0 && !(sphElem->body.unk24->unk15 & 0x40)) {
            Vec3f sp24;

            Math_Vec3s_ToVec3f(&sp24, &sphElem->body.bumper.unk6);
            func_800E3168(ctxt, sphElem->body.unk1C, sphElem->body.unk24, &sphereGroup->base, &sphElem->body, &sp24);
            sphElem->body.unk24->unk15 |= 0x40;
            return;
        }
    }
}

void func_800E61A0(GlobalContext *ctxt, CollisionCheckContext *colCtxt, ColCommon *shape) {
    ColCylinder *cylinder = (ColCylinder*)shape;

    if ((cylinder->body.unk16 & 0x80) && cylinder->body.unk24 != 0 && !(cylinder->body.unk24->unk15 & 0x40)) {
        Vec3f sp28;

        Math_Vec3s_ToVec3f(&sp28, &cylinder->body.bumper.unk6);
        func_800E3168(ctxt, cylinder->body.unk1C, cylinder->body.unk24, &cylinder->base, &cylinder->body, &sp28);
        cylinder->body.unk24->unk15 |= 0x40;
    }
}

void func_800E6238(GlobalContext *ctxt, CollisionCheckContext *colCtxt, ColCommon *shape) {
    ColTriGroup *triGroup = (ColTriGroup*)shape;
    ColTri *triElem;

    for (triElem = &triGroup->tris[0]; triElem < &triGroup->tris[triGroup->count]; triElem++) {
        if ((triElem->body.unk16 & 0x80) && triElem->body.unk24 != 0 && !(triElem->body.unk24->unk15 & 0x40)) {
            Vec3f sp24;

            Math_Vec3s_ToVec3f(&sp24, &triElem->body.bumper.unk6);
            func_800E3168(ctxt, triElem->body.unk1C, triElem->body.unk24, &triGroup->base, &triElem->body, &sp24);
            triElem->body.unk24->unk15 |= 0x40;
            return;
        }
    }
}

void func_800E6320(GlobalContext *ctxt, CollisionCheckContext *colCtxt, ColCommon *shape) {
    ColQuad *quad = (ColQuad*)shape;

    if ((quad->body.unk16 & 0x80) && quad->body.unk24 != 0 && !(quad->body.unk24->unk15 & 0x40)) {
        Vec3f sp28;

        Math_Vec3s_ToVec3f(&sp28, &quad->body.bumper.unk6);
        func_800E3168(ctxt, quad->body.unk1C, quad->body.unk24, &quad->base, &quad->body, &sp28);
        quad->body.unk24->unk15 |= 0x40;
    }
}

void func_800E63B8(GlobalContext *ctxt, CollisionCheckContext *colCtxt, ColCommon *shape) {
    ColSphere* sphere = (ColSphere*)shape;

    if ((sphere->body.unk16 & 0x80) && sphere->body.unk24 != 0 && !(sphere->body.unk24->unk15 & 0x40)) {
        Vec3f sp28;

        Math_Vec3s_ToVec3f(&sp28, &sphere->body.bumper.unk6);
        func_800E3168(ctxt, sphere->body.unk1C, sphere->body.unk24, &sphere->base, &sphere->body, &sp28);
        sphere->body.unk24->unk15 |= 0x40;
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
    ColCommon **col;

    for (col = &colCtxt->ACgroup[0]; col < &colCtxt->ACgroup[colCtxt->ACgroupLength]; col++) {
        ColCommon* colAC = *col;

        if (colAC != NULL && (colAC->flagsAC & 1)) {
            if (colAC->actor != NULL && colAC->actor->update == NULL) {
                continue;
            }
            D_801BA3A8[colAC->type](ctxt, colCtxt, colAC);
        }
    }
}

collision_func collisionFuncTableATwithAC[5][5] = {
    { Collision_SphereGroupWithSphereGroupAC, Collision_SphereGroupWithCylinderAC, Collision_SphereGroupWithTriGroupAC, Collision_SphereGroupWithQuadAC, Collision_SphereGroupWithSphereAC },
    { Collision_CylinderWithSphereGroupAC, Collision_CylinderWithCylinderAC, Collision_CylinderWithTriGroupAC, Collision_CylinderWithQuadAC, Collision_CylinderWithSphereAC },
    { Collision_TriGroupWithSphereGroupAC, Collision_TriGroupWithCylinderAC, Collision_TriGroupWithTriGroupAC, Collision_TriGroupWithQuad, Collision_TriGroupWithSphereAC },
    { Collision_QuadWithSphereGroupAC, Collision_QuadWithCylinderAC, Collision_QuadWithTriGroupAC, Collision_QuadWithQuadAC, Collision_QuadWithSphereAC },
    { Collision_SphereWithSphereGroupAC, Collision_SphereWithCylinderAC, Collision_SphereWithTriGroupAC, Collision_SphereWithQuadAC, Collision_SphereWithSphereAC },
};

void Collision_CollideWithAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, ColCommon *colObj) {
    ColCommon **col;

    for (col = &colCtxt->ACgroup[0]; col < &colCtxt->ACgroup[colCtxt->ACgroupLength]; col++) {
        ColCommon* colAC = *col;

        if (colAC != NULL && (colAC->flagsAC & 1)) {
            if (colAC->actor != NULL && colAC->actor->update == NULL) {
                continue;
            }
            if ((colAC->flagsAC & colObj->flagsAT & 0x38) && colObj != colAC) {
                if (!(colObj->flagsAT & 0x40) && colObj->actor != NULL && colAC->actor == colObj->actor) {
                    continue;
                }
                collisionFuncTableATwithAC[colObj->type][colAC->type](ctxt, colCtxt, colObj, colAC);
            }
        }
    }
}

void Collision_DoATWithAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt) {
    ColCommon **col;

    if (colCtxt->ATgroupLength == 0 || colCtxt->ACgroupLength == 0) {
        return;
    }

    for (col = &colCtxt->ATgroup[0]; col < &colCtxt->ATgroup[colCtxt->ATgroupLength]; col++) {
        ColCommon* colAC = *col;

        if (colAC != NULL && (colAC->flagsAT & 1)) {
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

void Collision_HandleCollisionOTWithOT(GlobalContext *ctxt, ColCommon *toucher, ColBodyInfo *toucherBody, 
                                Vec3f *toucherLoc, ColCommon *bumper, ColBodyInfo *bumperBody, Vec3f *bumperLoc, f32 param_8) {
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

    toucher->unk12 |= 2;
    toucher->collisionOT = bumperActor;
    toucherBody->unk17 |= 2;
    if (bumper->unk13 & 8) {
        toucher->unk13 |= 1;
    }

    bumper->unk12 |= 2;
    bumper->collisionOT = toucherActor;
    bumperBody->unk17 |= 2;
    if (toucher->unk13 & 8) {
        bumper->unk13 |= 1;
    }

    if (toucherActor == NULL || bumperActor == NULL || (toucher->unk12 & 4) || (bumper->unk12 & 4)) {
        return;
    }

    rightMassType = func_800E6724(toucherActor->unkA0.mass);
    leftMassType = func_800E6724(bumperActor->unkA0.mass);
    leftMass = toucherActor->unkA0.mass;
    rightMass = bumperActor->unkA0.mass;
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
        toucherActor->unkA0.displacement.x += -xDelta * leftDispRatio;
        toucherActor->unkA0.displacement.z += -zDelta * leftDispRatio;
        bumperActor->unkA0.displacement.x += xDelta * rightDispRatio;
        bumperActor->unkA0.displacement.z += zDelta * rightDispRatio;
    } else if (param_8 != 0.0f) {
        toucherActor->unkA0.displacement.x += -param_8 * leftDispRatio;
        bumperActor->unkA0.displacement.x += param_8 * rightDispRatio;
    } else {
        toucherActor->unkA0.displacement.x += -leftDispRatio;
        bumperActor->unkA0.displacement.x += rightDispRatio;
    }
}

void Collision_SphereGroupWithSphereGroupOT(GlobalContext *ctxt, CollisionCheckContext *colCtxt, ColCommon *toucher, ColCommon *bumpee) {
    ColSphereGroup* left = (ColSphereGroup*)toucher;
    ColSphereGroup* right = (ColSphereGroup*)bumpee;
    ColSphereGroupElement *sphElem;
    ColSphereGroupElement *sphElem2;
    f32 sp74;

    if (left->count > 0 && left->spheres != NULL && right->count > 0 && right->spheres != NULL && 
        (left->base.unk12 & 1) && (right->base.unk12 & 1)) {

        for (sphElem = &left->spheres[0]; sphElem < &left->spheres[left->count]; sphElem++) {
            if (!(sphElem->body.unk17 & 1)) {
                continue;
            }
            for (sphElem2 = &right->spheres[0]; sphElem2 < &right->spheres[right->count]; sphElem2++) {
                if (!(sphElem2->body.unk17 & 1)) {
                    continue;
                }
                if (Math3D_ColSphereSphereIntersect(&sphElem->params.colInfo, &sphElem2->params.colInfo, &sp74) != 0) {
                    Vec3f sp68;
                    Vec3f sp5C;

                    Math_Vec3s_ToVec3f(&sp68, &sphElem->params.colInfo.loc);
                    Math_Vec3s_ToVec3f(&sp5C, &sphElem2->params.colInfo.loc);
                    Collision_HandleCollisionOTWithOT(ctxt, &left->base, &sphElem->body, &sp68, &right->base, &sphElem2->body, &sp5C, sp74);
                }
            }
        }
    }
}

void Collision_SphereGroupWithCylinderOT(GlobalContext *ctxt, CollisionCheckContext *colCtxt, ColCommon *toucher, ColCommon *bumpee) {
    ColSphereGroup* left = (ColSphereGroup*)toucher;
    ColCylinder* right = (ColCylinder*)bumpee;
    ColSphereGroupElement *sphElem;
    f32 sp78;

    if (left->count > 0 && left->spheres != NULL && 
        (left->base.unk12 & 1) && (right->base.unk12 & 1) && (right->body.unk17 & 1)) {

        for (sphElem = &left->spheres[0]; sphElem < &left->spheres[left->count]; sphElem++) {
            if (!(sphElem->body.unk17 & 1)) {
                continue;
            }
            if (Math3D_ColSphereCylinderDistance(&sphElem->params.colInfo, &right->params, &sp78) != 0) {
                Vec3f sp6C;
                Vec3f sp60;

                Math_Vec3s_ToVec3f(&sp6C, &sphElem->params.colInfo.loc);
                Math_Vec3s_ToVec3f(&sp60, &right->params.loc);
                Collision_HandleCollisionOTWithOT(ctxt, &left->base, &sphElem->body, &sp6C, &right->base, &right->body, &sp60, sp78);
            }
        }
    }
}

void Collision_SphereGroupWithSphereOT(GlobalContext *ctxt, CollisionCheckContext *colCtxt, ColCommon *toucher, ColCommon *bumpee) {
    ColSphereGroup* left = (ColSphereGroup*)toucher;
    ColSphere* right = (ColSphere*)bumpee;
    ColSphereGroupElement *sphElem;
    f32 sp78;

    if (left->count > 0 && left->spheres != NULL && 
        (left->base.unk12 & 1) && (right->base.unk12 & 1) && (right->body.unk17 & 1)) {

        for (sphElem = &left->spheres[0]; sphElem < &left->spheres[left->count]; sphElem++) {
            if (!(sphElem->body.unk17 & 1)) {
                continue;
            }
            if (Math3D_ColSphereSphereIntersect(&sphElem->params.colInfo, &right->params.colInfo, &sp78) != 0) {
                Vec3f sp6C;
                Vec3f sp60;

                Math_Vec3s_ToVec3f(&sp6C, &sphElem->params.colInfo.loc);
                Math_Vec3s_ToVec3f(&sp60, &right->params.colInfo.loc);
                Collision_HandleCollisionOTWithOT(ctxt, &left->base, &sphElem->body, &sp6C, &right->base, &right->body, &sp60, sp78);
            }
        }
    }
}

void Collision_CylinderWithSphereGroupOT(GlobalContext *ctxt, CollisionCheckContext *colCtxt, ColCommon *toucher, ColCommon *bumpee) {
    Collision_SphereGroupWithCylinderOT(ctxt, colCtxt, bumpee, toucher);
}

void Collision_CylinderWithCylinderOT(GlobalContext *ctxt, CollisionCheckContext *colCtxt, ColCommon *toucher, ColCommon *bumpee) {
    ColCylinder* left = (ColCylinder*)toucher;
    ColCylinder* right = (ColCylinder*)bumpee;
    f32 sp4C;

    if ((left->base.unk12 & 1) && (right->base.unk12 & 1) && (left->body.unk17 & 1) && (right->body.unk17 & 1)) {
        if (Math3D_ColCylinderCylinderAmount(&left->params, &right->params, (f32 *) &sp4C) != 0) {
            Vec3f sp40;
            Vec3f sp34;

            Math_Vec3s_ToVec3f(&sp40, &left->params.loc);
            Math_Vec3s_ToVec3f(&sp34, &right->params.loc);
            Collision_HandleCollisionOTWithOT(ctxt, &left->base, &left->body, &sp40, &right->base, &right->body, &sp34, sp4C);
        }
    }
}

void Collision_CylinderWithSphereOT(GlobalContext *ctxt, CollisionCheckContext *colCtxt, ColCommon *toucher, ColCommon *bumpee) {
    ColCylinder* left = (ColCylinder*)toucher;
    ColSphere* right = (ColSphere*)bumpee;
    f32 sp4C;

    if ((left->base.unk12 & 1) && (left->body.unk17 & 1) && (right->base.unk12 & 1) && (right->body.unk17 & 1)) {
        if (Math3D_ColSphereCylinderDistance(&right->params.colInfo, &left->params,  &sp4C) != 0) {
            Vec3f sp40;
            Vec3f sp34;

            Math_Vec3s_ToVec3f(&sp40, &left->params.loc);
            Math_Vec3s_ToVec3f(&sp34, &right->params.colInfo.loc);
            Collision_HandleCollisionOTWithOT(ctxt, &left->base, &left->body, &sp40, &right->base, &right->body, &sp34, sp4C);
        }
    }
}

void Collision_SphereWithSphereGroupOT(GlobalContext *ctxt, CollisionCheckContext *colCtxt, ColCommon *toucher, ColCommon *bumpee) {
    Collision_SphereGroupWithSphereOT(ctxt, colCtxt, bumpee, toucher);
}

void Collision_SphereWithCylinderOT(GlobalContext *ctxt, CollisionCheckContext *colCtxt, ColCommon *toucher, ColCommon *bumpee) {
    Collision_CylinderWithSphereOT(ctxt, colCtxt, bumpee, toucher);
}

void Collision_SphereWithSphereOT(GlobalContext *ctxt, CollisionCheckContext *colCtxt, ColCommon *toucher, ColCommon *bumpee) {
    ColSphere* left = (ColSphere*)toucher;
    ColSphere* right = (ColSphere*)bumpee;
    f32 sp54;

    if ((left->base.unk12 & 1) && (left->body.unk17 & 1) && (right->base.unk12 & 1) && (right->body.unk17 & 1)) {
        if (Math3D_ColSphereSphereIntersect(&left->params.colInfo, &right->params.colInfo,  &sp54) != 0) {
            Vec3f sp48;
            Vec3f sp3C;

            Math_Vec3s_ToVec3f(&sp48, &left->params.colInfo.loc);
            Math_Vec3s_ToVec3f(&sp3C, &right->params.colInfo.loc);
            Collision_HandleCollisionOTWithOT(ctxt, &left->base, &left->body, &sp48, &right->base, &right->body, &sp3C, sp54);
        }
    }
}

s32 func_800E7264(ColCommon *iParm1) {
    if (!(iParm1->unk12 & 1)) {
        return 1;
    } else {
        return 0;
    }
}

s32 func_800E7288(ColCommon *piParm1, ColCommon *piParm2) {
    if (!(piParm1->unk12 & piParm2->unk13 & 0x38) || !(piParm1->unk13 & piParm2->unk12 & 0x38) || 
        ((piParm1->unk13 & 2) && (piParm2->unk13 & 4)) ||
        ((piParm2->unk13 & 2) && (piParm1->unk13 & 4))) {
        return 1;
    }
    if (piParm1->actor == piParm2->actor) {
        return 1;
    }
    return 0;
}

collision_func collisionFuncTableOTwithOT[5][5] = {
    { Collision_SphereGroupWithSphereGroupOT, Collision_SphereGroupWithCylinderOT, NULL, NULL, Collision_SphereGroupWithSphereOT },
    { Collision_CylinderWithSphereGroupOT, Collision_CylinderWithCylinderOT, NULL, NULL, Collision_CylinderWithSphereOT },
    { NULL, NULL, NULL, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL },
    { Collision_SphereWithSphereGroupOT, Collision_SphereWithCylinderOT, NULL, NULL, Collision_SphereWithSphereOT },
};

void Collision_DoOTWithOT(GlobalContext *ctxt, CollisionCheckContext *colCtxt) {
    ColCommon** left;
    ColCommon** right;
    collision_func vsFunc;

    for (left = colCtxt->OTgroup; left < colCtxt->OTgroup + colCtxt->OTgroupLength; left++) {
        if (*left == NULL || func_800E7264(*left)) {
            continue;
        }
        for (right = left + 1; right < colCtxt->OTgroup + colCtxt->OTgroupLength; right++) {
            if (*right == NULL || func_800E7264(*right) || func_800E7288(*left, *right)) {
                continue;
            }
            vsFunc = collisionFuncTableOTwithOT[(*left)->type][(*right)->type];
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

void func_800E7530(CollisionCheckInfo *info, ActorDamageChart *damageChart, CollisionCheckInfoInit *init) {
    info->health = init->health;
    info->damageChart = damageChart;
    info->cylRadius = init->cylRadius;
    info->cylHeight = init->cylHeight;
    info->mass = init->mass;
}

void func_800E755C(CollisionCheckInfo *info, ActorDamageChart *damageChart, CollisionCheckInfoInit2 *init) {
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

void func_800E75C8(GlobalContext *ctxt, CollisionCheckContext *colCtxt, ColCommon *arg2, ColBodyInfo *arg3) {
    f32 sp3C;
    f32 damage = 0.0f;
    s32 pad;
    ColCommon* toucher;
    ColBodyInfo* toucherBody;
    s32 pad1;
    u32 effectId;

    if ((arg2->actor == NULL) || !(arg2->flagsAC & 2)) {
        return;
    }
    if (!(arg3->unk16 & 2) || (arg3->unk16 & 0x10)) {
        return;
    }

    toucher = arg3->unk1C;
    toucherBody = arg3->unk24;

    if (toucher != NULL && toucherBody != NULL && arg2 != NULL && arg3 != NULL) {
        sp3C = Collision_GetDamageAndEffectOnBumper(toucher, toucherBody, arg2, arg3, &effectId);

        if (Collision_GetToucherDamage(toucher, toucherBody, arg2, arg3) != 0) {
            if (sp3C < 1.0f) {
                damage = 0.0f;
                if (effectId == 0) {
                    return;
                }
            } else {
                damage = func_800E04BC(sp3C, arg3);
                if (damage < 1.0f && effectId == 0) {
                    return;
                }
            }
        }
        if (arg2->actor->unkA0.damageChart != NULL) {
            arg2->actor->unkA0.damageEffect = effectId;
        }
        if (!(arg2->flagsAC & 4) || ((arg2->flagsAC & 4) && toucherBody->toucher.collidesWith == 0x20000000)) {
            if (arg2->actor->unkA0.damage < damage) {
                arg2->actor->unkA0.damage = damage;
            }
        }
    }
}

void func_800E77EC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, ColCommon* shape) {
    ColSphereGroup *sphereGroup = (ColSphereGroup*)shape;
    s32 i;

    if (sphereGroup->count > 0 && sphereGroup->spheres != NULL) {
        for (i = 0; i < sphereGroup->count; i++) {
            func_800E75C8(ctxt, colCtxt, &sphereGroup->base, &sphereGroup->spheres[i].body);
        }
    }
}

void func_800E7894(GlobalContext *ctxt, CollisionCheckContext *colCtxt, ColCommon* shape) {
    ColCylinder *cylinder = (ColCylinder*)shape;

    func_800E75C8(ctxt, colCtxt, &cylinder->base, &cylinder->body);
}

void func_800E78B4(GlobalContext *ctxt, CollisionCheckContext *colCtxt, ColCommon *shape) {
    ColTriGroup *triGroup = (ColTriGroup*)shape;
    s32 i;

    // unlike sphere groups above, tri groups are not guarded against
    //  triGroup->tris being NULL
    for (i = 0; i < triGroup->count; i++) {
        func_800E75C8(ctxt, colCtxt, &triGroup->base, &triGroup->tris[i].body);
    }
}

void func_800E7948(GlobalContext *ctxt, CollisionCheckContext *colCtxt, ColCommon *shape) {
    ColQuad *quad = (ColQuad*)shape;

    func_800E75C8(ctxt, colCtxt, &quad->base, &quad->body);
}

void func_800E7968(GlobalContext *ctxt, CollisionCheckContext *colCtxt, ColCommon *shape) {
    ColSphere *sphere = (ColSphere*)shape;

    func_800E75C8(ctxt, colCtxt, &sphere->base, &sphere->body);
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

    for (i = 0; i < colCtxt->ACgroupLength; i++) {
        ColCommon* col = colCtxt->ACgroup[i];

        if (col == NULL) {
            continue;
        }
        if (col->flagsAC & 0x40) {
            continue;
        }
        D_801BA4A0[col->type](ctxt, colCtxt, col);
    }
}

s32 func_800E7A48(GlobalContext *globalCtx, CollisionCheckContext *colChkCtx, ColCommon *shape, Vec3f *a, Vec3f *b) {
    ColSphereGroup *sphereGroup = (ColSphereGroup*)shape;
    s32 i;

    for (i = 0; i < sphereGroup->count; i++) {
        ColSphereGroupElement* sphElem = &sphereGroup->spheres[i];

        if (!(sphElem->body.unk17 & 1)) {
            continue;
        }

        D_801EDEB0.a = *a;
        D_801EDEB0.b = *b;
        if (Math3D_ColSphereLineSeg(&sphElem->params.colInfo, &D_801EDEB0) != 0) {
            return 1;
        }
    }
    return 0;
}

s32 func_800E7B54(GlobalContext *globalCtx, CollisionCheckContext *colChkCtx, ColCommon *shape, Vec3f *a, Vec3f *b) {
    ColCylinder *cylinder = (ColCylinder*)shape;

    if (!(cylinder->body.unk17 & 1)) {
        return 0;
    }

    if (func_8017E350(&cylinder->params, a, b, &D_801EDF38, &D_801EDF48) != 0) {
        return 1;
    }

    return 0;
}

s32 func_800E7BCC(GlobalContext *globalCtx, CollisionCheckContext *colChkCtx, ColCommon *shape, Vec3f *a, Vec3f *b) {
    ColSphere *sphere = (ColSphere*)shape;

    if (!(sphere->body.unk17 & 1)) {
        return 0;
    }

    D_801EDFC8.a = *a;
    D_801EDFC8.b = *b;
    if (Math3D_ColSphereLineSeg(&sphere->params.colInfo, &D_801EDFC8) != 0) {
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
    ColCommon** col;
    s32 i;
    s32 exclude;
    s32 result = 0;

    for (col = colChkCtx->OTgroup; col < &colChkCtx->OTgroup[colChkCtx->OTgroupLength]; col++) {
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

        lineCheck = D_801BA4B4[(*col)->type];
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

void Collision_CylinderMoveToActor(Actor *actor, ColCylinder *cylinder) {
    cylinder->params.loc.x = actor->currPosRot.pos.x;
    cylinder->params.loc.y = actor->currPosRot.pos.y;
    cylinder->params.loc.z = actor->currPosRot.pos.z;
}

void Collision_CylinderSetLoc(ColCylinder *cylinder, Vec3s *loc) {
    cylinder->params.loc.x = loc->x;
    cylinder->params.loc.y = loc->y;
    cylinder->params.loc.z = loc->z;
}

void Collision_QuadSetCoords(ColQuad *quad, Vec3f *a, Vec3f *b, Vec3f *c, Vec3f *d) {
    Math_Vec3f_Copy(&quad->params.quad[2], c);
    Math_Vec3f_Copy(&quad->params.quad[3], d);
    Math_Vec3f_Copy(&quad->params.quad[0], a);
    Math_Vec3f_Copy(&quad->params.quad[1], b);
    Collision_QuadCalcMidpoints(&quad->params);
}

void Collision_TriGroupSetCoordsAtIndex(ColTriGroup *tris, s32 index, Vec3f *a, Vec3f *b, Vec3f *c) {
    ColTri* tri = &tris->tris[index];
    f32 nx;
    f32 ny;
    f32 nz;
    f32 originDist;

    Math_Vec3f_Copy(&tri->params.vtx[0], a);
    Math_Vec3f_Copy(&tri->params.vtx[1], b);
    Math_Vec3f_Copy(&tri->params.vtx[2], c);
    Math3D_UnitNormalVector(a, b, c, &nx, &ny, &nz, &originDist);
    tri->params.unitNormal.x = nx;
    tri->params.unitNormal.y = ny;
    tri->params.unitNormal.z = nz;
    tri->params.unk30 = originDist;
}

void Collision_InitTriParamsAtIndex(GlobalContext *ctxt, ColTriGroup *tris, s32 index, ColTriParamsInit *init) {
    ColTri* tri = &tris->tris[index];

    Collision_InitTriParamsWithData(ctxt, &tri->params, init);
}

#ifdef NON_MATCHING
// needs in-function static bss
void func_800E7FDC(s32 limb, ColSphereGroup *sphereGroup) {
    static Vec3f D_801EE1C0;
    static Vec3f D_801EE1D0;
    s32 i;

    for (i = 0; i < sphereGroup->count; i++) {
        if (limb == sphereGroup->spheres[i].params.unk14) {
            D_801EE1C0.x = sphereGroup->spheres[i].params.unk0.loc.x;
            D_801EE1C0.y = sphereGroup->spheres[i].params.unk0.loc.y;
            D_801EE1C0.z = sphereGroup->spheres[i].params.unk0.loc.z;
            SysMatrix_MultiplyVector3fByState(&D_801EE1C0, &D_801EE1D0);
            sphereGroup->spheres[i].params.colInfo.loc.x = D_801EE1D0.x;
            sphereGroup->spheres[i].params.colInfo.loc.y = D_801EE1D0.y;
            sphereGroup->spheres[i].params.colInfo.loc.z = D_801EE1D0.z;
            sphereGroup->spheres[i].params.colInfo.radius = sphereGroup->spheres[i].params.unk0.radius * sphereGroup->spheres[i].params.unk10;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E7FDC.asm")
#endif

void func_800E8160(ColSphereGroup *sphereGroup, s32 index, Actor *actor) {
    if (index < sphereGroup->count) {
        sphereGroup->spheres[index].params.colInfo.loc.x = sphereGroup->spheres[index].params.unk0.loc.x + actor->currPosRot.pos.x;
        sphereGroup->spheres[index].params.colInfo.loc.y = sphereGroup->spheres[index].params.unk0.loc.y + actor->currPosRot.pos.y;
        sphereGroup->spheres[index].params.colInfo.loc.z = sphereGroup->spheres[index].params.unk0.loc.z + actor->currPosRot.pos.z;
        sphereGroup->spheres[index].params.colInfo.radius = sphereGroup->spheres[index].params.unk0.radius * sphereGroup->spheres[index].params.unk10;
    }
}

#ifdef NON_MATCHING
// needs in-function static bss
void func_800E823C(s32 limb, ColSphere *sphere) {
    static Vec3f D_801EE1E0;
    static Vec3f D_801EE1F0;

    if (limb == sphere->params.unk14) {
        D_801EE1E0.x = sphere->params.unk0.loc.x;
        D_801EE1E0.y = sphere->params.unk0.loc.y;
        D_801EE1E0.z = sphere->params.unk0.loc.z;
        SysMatrix_MultiplyVector3fByState(&D_801EE1E0, &D_801EE1F0);
        sphere->params.colInfo.loc.x = D_801EE1F0.x;
        sphere->params.colInfo.loc.y = D_801EE1F0.y;
        sphere->params.colInfo.loc.z = D_801EE1F0.z;
        sphere->params.colInfo.radius = sphere->params.unk0.radius * sphere->params.unk10;
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
    static EffSparkParams D_801EE738
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
