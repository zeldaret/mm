#include <ultra64.h>
#include <global.h>

f32 Collision_GetDamageAndEffectOnBumper(ColCommon *toucher, ColBodyInfo *toucherBody, ColCommon *bumper, ColBodyInfo *bumperBody, u32 *effect) {
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

        damage *= gDamageMultipliers[bumper->actor->unkA0.damageChart->attack[i] & 0xF];
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
    *shape = defaultColCommon;
    return 1;
}

s32 Collision_FiniCommon(GlobalContext *ctxt, ColCommon *shape) {
    return 1;
}

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E0594.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E05D4.asm")

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
    *params = defaultColSphereInfo;
    return 1;
}

s32 Collision_FiniSphereParams(GlobalContext *ctxt, ColSphereParams *params) {
    return 1;
}

s32 Collision_InitSphereParamsWithData(GlobalContext *ctxt, ColSphereParams *params, ColSphereParamsInit *init) {
    params->unk14 = init->unk0;
    params->unk0 = init->unk1;
    params->unk10 = init->unkA * D_801DD5C0; // rodata
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

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E0B78.asm")

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

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E0CA8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E0D84.asm")

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

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E123C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E12A4.asm")

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

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E16FC.asm")

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

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E1858.asm")

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
    *params = defaultColQuadParams;
    return 1;
}

s32 Collision_FiniQuadParams(GlobalContext* ctxt, ColQuadParams* params) {
    return 1;
}

s32 Collision_ResetQuadParamsForAT(GlobalContext *ctxt, ColQuadParams *params) {
    params->unk3C = D_801DD5C4; // rodata
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

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E1EB8.asm")

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

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E2368.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E23B0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E23C4.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E2408.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E2434.asm")

void Collision_Init(GlobalContext *ctxt, CollisionCheckContext *colCtxt) {
    colCtxt->flags = 0;
    Collision_Reset(ctxt, colCtxt);
}

void Collision_Fini(GlobalContext *ctxt, CollisionCheckContext *colCtxt) {
}

void Collision_Reset(GlobalContext* ctxt, CollisionCheckContext* colCtxt) {
    ColCommon** col;

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

    for (col = &colCtxt->group4[0]; col < &colCtxt->group4[ARRAY_COUNT(colCtxt->group4)]; col++) {
        *col = NULL;
    }
}

void Collision_EnableEditMode(GlobalContext *ctxt, CollisionCheckContext *colCtxt) {
    colCtxt->flags |= 1;
}

void Collision_EnableAppendMode(GlobalContext *ctxt, CollisionCheckContext *colCtxt) {
    colCtxt->flags &= ~1;
}

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

s32 Collision_AddGroup4(GlobalContext *ctxt, CollisionCheckContext *colCtxt, ColCommon *shape) {
    s32 index;

    if (func_8016A01C(ctxt)) {
        return -1;
    }

    func_800E2434(ctxt, shape);

    if (colCtxt->group4Length >= ARRAY_COUNT(colCtxt->group4)) {
        return -1;
    }
    index = colCtxt->group4Length;

    colCtxt->group4[colCtxt->group4Length] = shape;
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

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E2C08.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E2C1C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E2D88.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E2EF4.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E2F30.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E2F54.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E2F78.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E30C8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E3168.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E3304.asm")

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
            toucher->actor->unkA0.impactEffect = bumperBody->bumper.unk4;
        }
    }
    if (!(toucherBody->unk17 & 4)) {
        bumper->flagsAC |= 2;
        bumper->collisionAC = toucher->actor;
        bumperBody->unk1C = toucher;
        bumperBody->unk24 = toucherBody;
        bumperBody->unk16 |= 2;
        if (bumper->actor != NULL) {
            bumper->actor->unkA0.unk1B = toucherBody->toucher.unk4;
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

#ifdef NON_MATCHING
// needs rodata
void Collision_TriCalcAvgPoint(ColTri *tri, Vec3f *avg) {
    f32 temp_f0 = D_801DD5C8; // rodata

    avg->x = (tri->params.vtx[0].x + tri->params.vtx[1].x + tri->params.vtx[2].x) * temp_f0;
    avg->y = (tri->params.vtx[0].y + tri->params.vtx[1].y + tri->params.vtx[2].y) * temp_f0;
    avg->z = (tri->params.vtx[0].z + tri->params.vtx[1].z + tri->params.vtx[2].z) * temp_f0;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_TriCalcAvgPoint.asm")
#endif

void collision_quad_cal_avg_point(ColQuad *quad, Vec3f *avg) {
    avg->x = (quad->params.quad[0].x + (quad->params.quad[1].x + (quad->params.quad[3].x + quad->params.quad[2].x))) / 4.0f;
    avg->y = (quad->params.quad[0].y + (quad->params.quad[1].y + (quad->params.quad[3].y + quad->params.quad[2].y))) / 4.0f;
    avg->z = (quad->params.quad[0].z + (quad->params.quad[1].z + (quad->params.quad[3].z + quad->params.quad[2].z))) / 4.0f;
}

#ifdef NON_MATCHING
// needs rodata
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

                    if (!(fabsf(sp88) < 0.008f)) { // D_801DD5CC rodata
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
#else
#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_SphereGroupWithSphereGroupAC.asm")
#endif

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
                if (!(fabsf(sp7C) < D_801DD5D0)) { // rodata
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

#ifdef NON_MATCHING
// needs rodata
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
                if (!(fabsf(sp8C) < D_801DD5D4)) { // rodata
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
#else
#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_SphereGroupWithSphereAC.asm")
#endif

#ifdef NON_MATCHING
// needs rodata
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
                if (!(fabsf(sp98) < D_801DD5D8)) { // rodata
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
#else
#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_CylinderWithSphereGroupAC.asm")
#endif

#ifdef NON_MATCHING
// Single float register diff, single stack diff
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
            if (!(fabsf(sp68) < minCylinderIntersectAmount)) {
                f32 temp_f12 = ac->params.radius / sp68;

                sp5C.y = (f32)at->params.loc.y + at->params.yOffset + at->params.height * 0.5f;

                if (sp5C.y < (f32)ac->params.loc.y + ac->params.yOffset) {
                    sp5C.y = (f32)ac->params.loc.y + ac->params.yOffset;
                } else if (sp5C.y > (f32)ac->params.loc.y + ac->params.yOffset + ac->params.height) {
                    sp5C.y = (f32)ac->params.loc.y + ac->params.yOffset + ac->params.height;
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
#else
#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_CylinderWithCylinderAC.asm")
#endif

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

            if (!(fabsf(sp68) < D_801DD5E0)) {
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

#ifdef NON_MATCHING
// needs rodata
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
                if (!(fabsf(sp8C) < D_801DD5E4)) { // rodata
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
#else
#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_SphereWithSphereGroupAC.asm")
#endif

#ifdef NON_MATCHING
// likely needs .data migration
void Collision_SphereWithCylinderAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, ColCommon *toucher, ColCommon *bumpee) {
    ColSphere* at = (ColSphere*)toucher;
    ColCylinder* ac = (ColCylinder*)bumpee;
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
        f32 temp_f0;

        Math_Vec3s_ToVec3f(&sp50, &at->params.colInfo.loc);
        Math_Vec3s_ToVec3f(&sp44, &ac->params.loc);

        if (!(fabsf(sp68) < D_801DD5E8)) { // rodata
            temp_f0 = ac->params.radius / sp68;
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
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/Collision_SphereWithCylinderAC.asm")
#endif

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
        if (!(fabsf(sp68) < D_801DD5EC)) { // rodata
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

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E60C0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E61A0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E6238.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E6320.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E63B8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E6450.asm")

void Collision_CollideWithAC(GlobalContext *ctxt, CollisionCheckContext *colCtxt, ColCommon *colObj) {
    ColCommon **col;

    for (col = &colCtxt->ACgroup[0]; col < &colCtxt->ACgroup[colCtxt->ACgroupLength]; col++) {
        ColCommon* colAC = *col;

        if (colAC != NULL && (colAC->flagsAC & 1)) {
            if ((colAC->actor != NULL) && (colAC->actor->update == NULL)) {
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

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E6724.asm")

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

    if (fabsf(totalMass) < D_801DD5F0) { // rodata
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

    if (!(fabsf(xzDist) < D_801DD5F4)) { // rodata
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

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E7264.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E7288.asm")

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
#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E7494.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E74DC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E7508.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E7530.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E755C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E7590.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E75C8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E77EC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E7894.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E78B4.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E7948.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E7968.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E7988.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E7A48.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E7B54.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E7BCC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E7C64.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E7DA8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E7DCC.asm")

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

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E7FDC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E8160.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E823C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E8318.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E8478.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E85D4.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E8668.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E8690.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E86C0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E86E0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_collision_check/func_800E8784.asm")
