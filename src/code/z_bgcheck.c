#include "global.h"
#include "vt.h"

// sys_math3d.c

#define Math3D_PointRelativeToCubeFaces func_8017A954
#define Math3D_PointRelativeToCubeEdges func_8017AA0C
#define Math3D_PointRelativeToCubeVertices func_8017ABBC
#define Math3D_LineVsCube func_8017AD38
#define Math3D_Vec3fDistSq Math3D_DistanceSquared
#define Math3D_DistPlaneToPos Math3D_NormalizedSignedDistanceFromPlane

#define Math3D_TriChkPointParaYDist func_8017BAD0
s32 Math3D_TriChkPointParaYDist(Vec3f* v0, Vec3f* v1, Vec3f* v2, f32 y, f32 z, f32 unk, f32 chkDist, f32 ny);

#define Math3D_TriChkPointParaYIntersectDist func_8017BE30
s32 Math3D_TriChkPointParaYIntersectDist(Vec3f* a, Vec3f* b, Vec3f* c, f32 nx, f32 ny, f32 nz, f32 dist, f32 z, f32 x, f32* yIntersect, f32 chkDist);

#define Math3D_TriChkLineSegParaYIntersect func_8017C008
s32 Math3D_TriChkLineSegParaYIntersect(Vec3f* v0, Vec3f* v1, Vec3f* v2, f32 nx, f32 ny, f32 nz, f32 originDist, f32 z,
    f32 x, f32* yIntersect, f32 y0, f32 y1);

#define Math3D_TriChkPointParaXDist func_8017C540
s32 Math3D_TriChkPointParaXDist(Vec3f* v0, Vec3f* v1, Vec3f* v2, f32 y, f32 z, f32 unk, f32 chkDist, f32 nx);

#define Math3D_TriChkPointParaXIntersect func_8017C850
s32 Math3D_TriChkPointParaXIntersect(Vec3f* a, Vec3f* b, Vec3f* c, f32 nx, f32 ny, f32 nz, f32 dist, f32 y, f32 z, f32* xIntersect);

#define Math3D_TriChkLineSegParaXIntersect func_8017C980
s32 Math3D_TriChkLineSegParaXIntersect(Vec3f* v0, Vec3f* v1, Vec3f* v2, f32 nx, f32 ny, f32 nz, f32 originDist, f32 y,
    f32 z, f32* xIntersect, f32 x0, f32 x1);

#define Math3D_TriChkLineSegParaZDist func_8017CB7C
s32 Math3D_TriChkLineSegParaZDist(Vec3f* v0, Vec3f* v1, Vec3f* v2, f32 y, f32 z, f32 unk, f32 chkDist, f32 nz);

#define Math3D_TriChkPointParaZIntersect func_8017CEF0
s32 Math3D_TriChkPointParaZIntersect(Vec3f* a, Vec3f* b, Vec3f* c, f32 nx, f32 ny, f32 nz, f32 dist, f32 x, f32 y, f32* zIntersect);

#define Math3D_TriChkLineSegParaZIntersect func_8017D020
s32 Math3D_TriChkLineSegParaZIntersect(Vec3f* v0, Vec3f* v1, Vec3f* v2, f32 nx, f32 ny, f32 nz, f32 originDist, f32 x,
    f32 y, f32* zIntersect, f32 z0, f32 z1);

// idk
#define LogUtils_HungupThread Fault_AddHungupAndCrash

#define SSNodeList_Initialize BgCheck_ScenePolygonListsInit
#define SSNodeList_Alloc BgCheck_ScenePolygonListsAlloc
#define DynaPoly_Init BgCheck_DynaInit
#define DynaPoly_Alloc BgCheck_DynaAlloc

#define BgCheck_GetStaticLookupIndicesFromPos func_800C25E0
void BgCheck_GetStaticLookupIndicesFromPos(CollisionContext* colCtx, Vec3f* pos, Vec3i* sector);

#define BgCheck_PosInStaticBoundingBox func_800C3C94
#define BgCheck_GetNearestStaticLookup func_800C2460
#define func_80041EC8 func_800C9B68
#define BgCheck_RaycastFloorDyna func_800C7974
f32 BgCheck_RaycastFloorDyna(DynaRaycast* dynaRaycast);

#define BgCheck_SphVsDynaWall func_800C8580
s32 BgCheck_SphVsDynaWall(CollisionContext* colCtx, u16 xpFlags, f32* outX, f32* outZ, Vec3f* pos, f32 radius,
    CollisionPoly** outPoly, s32* outBgId, Actor* actor);

#define BgCheck_CheckLineImpl func_800C4FD4
s32 BgCheck_CheckLineImpl(CollisionContext* colCtx, u16 xpFlags1, u16 xpFlags2, Vec3f* posA, Vec3f* posB,
    Vec3f* posResult, CollisionPoly** outPoly, s32* outBgId, Actor* actor, f32 chkDist,
    u32 bccFlags);

#define BgCheck_CheckDynaCeiling func_800C8A60
s32 BgCheck_CheckDynaCeiling(CollisionContext* colCtx, u16 xpFlags, f32* outY, Vec3f* pos, f32 chkDist,
    CollisionPoly** outPoly, s32* outBgId, Actor* actor);

#define BgCheck_ResetPolyCheckTbl func_800C9640

#define BgCheck_CheckLineAgainstDyna func_800C8EEC
s32 BgCheck_CheckLineAgainstDyna(CollisionContext* colCtx, u16 xpFlags, Vec3f* posA, Vec3f* posB, Vec3f* posResult,
    CollisionPoly** outPoly, f32* distSq, s32* outBgId, Actor* actor, f32 chkDist,
    s32 bccFlags);

#define BgCheck_AnyLineTest2 func_800C583C

#define BgCheck_SphVsFirstDynaPoly func_800C9380
s32 BgCheck_SphVsFirstDynaPoly(CollisionContext* colCtx, u16 xpFlags, CollisionPoly** outPoly, s32* outBgId,
    Vec3f* center, f32 radius, Actor* actor, u16 bciFlags);

//***********************************************************

#define SSNode_SetValue BgCheck_PolygonLinkedListNodeInit
void SSNode_SetValue(SSNode* node, s16* polyIndex, u16 next) {
    node->polyId = *polyIndex;
    node->next = next;
}

#define SSList_SetNull BgCheck_PolygonLinkedListResetHead
void SSList_SetNull(u16* head) {
    *head = SS_NULL;
}

#define SSNodeList_SetSSListHead BgCheck_ScenePolygonListsNodeInsert
void SSNodeList_SetSSListHead(SSNodeList* list, SSList* ssList, s16* polyIndex) {
    u16 index;

    index = BgCheck_ScenePolygonListsReserveNode(list);
    SSNode_SetValue(&list->tbl[index], polyIndex, ssList->head);
    ssList->head = index;
}

#define DynaSSNodeList_SetSSListHead BgCheck_PolygonLinkedListNodeInsert
void BgCheck_PolygonLinkedListNodeInsert(DynaSSNodeList* list, SSList* ssList, s16* polyIndex) {
    u16 index;

    index = BgCheck_AllocPolygonLinkedListNode(list);
    SSNode_SetValue(&list->nodes[index], polyIndex, ssList->head);
    ssList->head = index;
}

#define DynaSSNodeList_Initialize BgCheck_PolygonLinkedListInit
void DynaSSNodeList_Initialize(GlobalContext* globalCtx, DynaSSNodeList* list) {
    list->nodes = NULL;
    list->count = 0;
}

#define DynaSSNodeList_Alloc BgCheck_PolygonLinkedListAlloc
void DynaSSNodeList_Alloc(GlobalContext* globalCtx, DynaSSNodeList* list, u32 numNodes) {
    list->nodes = (SSNode*)THA_AllocEndAlign(&globalCtx->state.heap, numNodes * sizeof(SSNode), -2);
    list->maxNodes = numNodes;
    list->count = 0;
}

#define DynaSSNodeList_ResetCount BgCheck_PolygonLinkedListReset
void DynaSSNodeList_ResetCount(DynaSSNodeList* list) {
    list->count = 0;
}

#define DynaSSNodeList_GetNextNodeIdx BgCheck_AllocPolygonLinkedListNode
u16 DynaSSNodeList_GetNextNodeIdx(DynaSSNodeList* list) {
    u16 index;

    index = list->count++;
    if (list->maxNodes <= index) {
        return SS_NULL;
    }

    return index;
}

#define BgCheck_Vec3sToVec3f BgCheck_CreateVec3fFromVertex
void BgCheck_Vec3sToVec3f(BgVertex* vertex, Vec3f* vector) {
    vector->x = vertex->pos.x;
    vector->y = vertex->pos.y;
    vector->z = vertex->pos.z;
}

#define BgCheck_Vec3fToVec3s BgCheck_CreateVertexFromVec3f
void BgCheck_Vec3fToVec3s(BgVertex* vertex, Vec3f* vector) {
    vertex->pos.x = vector->x;
    vertex->pos.y = vector->y;
    vertex->pos.z = vector->z;
}

f32 func_800BFD84(CollisionPoly *polygon, f32 param_2, f32 param_3) {
    return ((COLPOLY_GET_NORMAL(polygon->normal.x * param_2 + polygon->normal.z * param_3)) + (f32) polygon->dist) / ((f32) -(s32) polygon->normal.y * COLPOLY_NORMAL_FRAC);
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800BFDEC.s")

#define CollisionPoly_GetMinY BgCheck_PolygonGetMinY
s16 BgCheck_PolygonGetMinY(CollisionPoly* poly, BgVertex* vertices) {
    s16 phi_a3;

    s32 a;
    s32 b;
    s32 c;

    a = COLPOLY_VTX_INDEX(poly->flags_vIA);
    b = COLPOLY_VTX_INDEX(poly->flags_vIB);
    c = poly->vIC;

    phi_a3 = vertices[a].pos.y;
    if (vertices[b].pos.y < phi_a3) {
        phi_a3 = vertices[b].pos.y;
    }
    if (phi_a3 < vertices[c].pos.y) {
        return phi_a3;
    }
    return vertices[c].pos.y;
}

#define CollisionPoly_GetNormalF BgCheck_PolygonGetNormal
void BgCheck_PolygonGetNormal(CollisionPoly* poly, f32* nx, f32* ny, f32* nz) {
    *nx = COLPOLY_GET_NORMAL(poly->normal.x);
    *ny = COLPOLY_GET_NORMAL(poly->normal.y);
    *nz = COLPOLY_GET_NORMAL(poly->normal.z);
}

/**
 * Compute transform matrix mapping +y (up) to the collision poly's normal
 */
//func_80038A28
void func_800C0094(CollisionPoly* poly, f32 tx, f32 ty, f32 tz, MtxF* dest) {
    f32 nx;
    f32 ny;
    f32 nz;
    s32 pad;
    f32 z_f14;
    f32 phi_f14;
    f32 phi_f12;
    f32 inv_z_f14;

    if (poly == NULL) {
        return;
    }
    BgCheck_PolygonGetNormal(poly, &nx, &ny, &nz);

    z_f14 = sqrtf(SQ(ny) + SQ(nz));
    if (!IS_ZERO(z_f14)) {
        inv_z_f14 = 1.0f / z_f14;
        phi_f14 = ny * inv_z_f14;
        phi_f12 = nz * inv_z_f14;
    }
    else {
        phi_f14 = 1.0f;
        phi_f12 = 0.0f;
    }
    dest->xx = z_f14;
    dest->xy = (-nx) * phi_f14;
    dest->xz = (-nx) * phi_f12;
    dest->yx = nx;
    dest->yy = ny;
    dest->yz = nz;
    dest->zx = 0.0f;
    dest->zy = -phi_f12;
    dest->zz = phi_f14;
    dest->wx = tx;
    dest->wy = ty;
    dest->wz = tz;
    dest->xw = 0.0f;
    dest->yw = 0.0f;
    dest->zw = 0.0f;
    dest->ww = 1.0f;
}

#define CollisionPoly_GetPointDistanceFromPlane func_800C01B8
f32 func_800C01B8(CollisionPoly* poly, Vec3f* point) {
    return (poly->normal.x * point->x + poly->normal.y * point->y + poly->normal.z * point->z) * COLPOLY_NORMAL_FRAC +
        poly->dist;
}

#define CollisionPoly_GetVertices BgCheck_CreateTriNormFromPolygon
void CollisionPoly_GetVertices(CollisionPoly* poly, Vec3s* vtxList, Vec3f* dest) {
    BgCheck_Vec3sToVec3f(&vtxList[COLPOLY_VTX_INDEX(poly->flags_vIA)], &dest[0]);
    BgCheck_Vec3sToVec3f(&vtxList[COLPOLY_VTX_INDEX(poly->flags_vIB)], &dest[1]);
    BgCheck_Vec3sToVec3f(&vtxList[poly->vIC], &dest[2]);
}

#define CollisionPoly_GetVerticesByBgId func_800C02C0
void CollisionPoly_GetVerticesByBgId(CollisionPoly* poly, s32 bgId, CollisionContext* colCtx, Vec3f* dest) {
    Vec3s* vtxList;

    if (poly == NULL || bgId > BG_ACTOR_MAX || dest == NULL) {
        if (0) {
            //
        }

        if (dest != NULL) {
            // @bug: dest[2] x and y are not set to 0
            dest[0].x = dest[0].y = dest[0].z = dest[1].x = dest[1].y = dest[1].z = dest[2].z = 0.0f;
            return;
        }
    }
    else {
        if (bgId == BGCHECK_SCENE) {
            vtxList = colCtx->colHeader->vtxList;
        }
        else {
            vtxList = colCtx->dyna.vtxList;
        }
        BgCheck_CreateTriNormFromPolygon(poly, vtxList, dest);
    }
}

extern Vec3f D_801ED9F0[3]; //polyVerts
#define CollisionPoly_CheckYIntersectApprox1 func_800C0340
s32 CollisionPoly_CheckYIntersectApprox1(CollisionPoly* poly, Vec3s* vtxList, f32 x, f32 z, f32* yIntersect, f32 chkDist) {
    f32 nx;
    f32 ny;
    f32 nz;
    Vec3s* vA;
    Vec3s* vB;
    Vec3s* vC;

    vA = &vtxList[COLPOLY_VTX_INDEX(poly->flags_vIA)];
    Math_Vec3s_ToVec3f(&D_801ED9F0[0], vA);
    vB = &vtxList[COLPOLY_VTX_INDEX(poly->flags_vIB)];
    Math_Vec3s_ToVec3f(&D_801ED9F0[1], vB);
    vC = &vtxList[poly->vIC];
    Math_Vec3s_ToVec3f(&D_801ED9F0[2], vC);

    nx = COLPOLY_GET_NORMAL(poly->normal.x);
    ny = COLPOLY_GET_NORMAL(poly->normal.y);
    nz = COLPOLY_GET_NORMAL(poly->normal.z);

    return Math3D_TriChkPointParaYIntersectDist(&D_801ED9F0[0], &D_801ED9F0[1], &D_801ED9F0[2], nx, ny, nz, poly->dist, z,
        x, yIntersect, chkDist);
}

#define CollisionPoly_CheckYIntersect func_800C0474
s32 CollisionPoly_CheckYIntersect(CollisionPoly* poly, Vec3s* vtxList, f32 x, f32 z, f32* yIntersect, f32 chkDist);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C0474.s")

#define CollisionPoly_CheckYIntersectApprox2 func_800C0668
s32 CollisionPoly_CheckYIntersectApprox2(CollisionPoly* poly, Vec3s* vtxList, f32 x, f32 z, f32* yIntersect) {
    return CollisionPoly_CheckYIntersectApprox1(poly, vtxList, x, z, yIntersect, 1.0f);
}

extern Vec3f D_801EDA80[3]; //polyVerts
#define CollisionPoly_CheckXIntersectApprox func_800C06A8
s32 CollisionPoly_CheckXIntersectApprox(CollisionPoly* poly, Vec3s* vtxList, f32 y, f32 z, f32* xIntersect) {
    f32 nx;
    f32 ny;
    f32 nz;

    BgCheck_CreateTriNormFromPolygon(poly, vtxList, D_801EDA80);
    BgCheck_PolygonGetNormal(poly, &nx, &ny, &nz);
    return Math3D_TriChkPointParaXIntersect(&D_801EDA80[0], &D_801EDA80[1], &D_801EDA80[2], nx, ny, nz, poly->dist, y, z,
        xIntersect);
}

extern Vec3f D_801EDB48[3]; //polyVerts
#define CollisionPoly_CheckZIntersectApprox func_800C074C
s32 CollisionPoly_CheckZIntersectApprox(CollisionPoly* poly, Vec3s* vtxList, f32 x, f32 y, f32* zIntersect) {
    f32 nx;
    f32 ny;
    f32 nz;

    BgCheck_CreateTriNormFromPolygon(poly, vtxList, D_801EDB48);
    BgCheck_PolygonGetNormal(poly, &nx, &ny, &nz);
    return Math3D_TriChkPointParaZIntersect(&D_801EDB48[0], &D_801EDB48[1], &D_801EDB48[2], nx, ny, nz, poly->dist, x, y,
        zIntersect);
}

#define CollisionPoly_LineVsPoly func_800C07F0
s32 CollisionPoly_LineVsPoly(func_800C07F0_args* a0);
#ifdef NON_MATCHING
//#define polyVerts D_801EDB70
//#define plane D_801EDB98
s32 CollisionPoly_LineVsPoly(func_800C07F0_args* a0) {
    static Vec3f polyVerts[3];
    static Plane plane;
    f32 planeDistA;
    f32 planeDistB;
    f32 planeDistDelta;

    plane.originDist = a0->poly->dist;
    planeDistA =
        COLPOLY_GET_NORMAL(a0->poly->normal.x * a0->posA->x + a0->poly->normal.y * a0->posA->y + a0->poly->normal.z * a0->posA->z) +
        plane.originDist;
    planeDistB =
        COLPOLY_GET_NORMAL(a0->poly->normal.x * a0->posB->x + a0->poly->normal.y * a0->posB->y + a0->poly->normal.z * a0->posB->z) +
        plane.originDist;

    planeDistDelta = planeDistA - planeDistB;
    if ((planeDistA >= 0.0f && planeDistB >= 0.0f)
        || (planeDistA < 0.0f && planeDistB < 0.0f)
        || ((a0->chkOneFace != 0) && (planeDistA < 0.0f && planeDistB > 0.0f))
        || IS_ZERO(planeDistDelta)) {
        return false;
    }

    BgCheck_PolygonGetNormal(a0->poly, &plane.normal.x, &plane.normal.y, &plane.normal.z);
    BgCheck_CreateTriNormFromPolygon(a0->poly, a0->vtxList, polyVerts);
    Math3D_Lerp(a0->posA, a0->posB, planeDistA / planeDistDelta, a0->planeIntersect);

    if ((fabsf(plane.normal.x) > 0.5f &&
        Math3D_TriChkPointParaXDist(
            &polyVerts[0],
            &polyVerts[1],
            &polyVerts[2],
            a0->planeIntersect->y,
            a0->planeIntersect->z,
            0.0f,
            a0->chkDist,
            plane.normal.x))
        || (fabsf(plane.normal.y) > 0.5f &&
            Math3D_TriChkPointParaYDist(
                &polyVerts[0],
                &polyVerts[1],
                &polyVerts[2],
                a0->planeIntersect->z,
                a0->planeIntersect->x,
                0.0f,
                a0->chkDist,
                plane.normal.y))
        || (fabsf(plane.normal.z) > 0.5f &&
            Math3D_TriChkLineSegParaZDist(
                &polyVerts[0],
                &polyVerts[1],
                &polyVerts[2],
                a0->planeIntersect->x,
                a0->planeIntersect->y,
                0.0f,
                a0->chkDist,
                plane.normal.z))) {
        return true;
    }
    return false;
}
#undef polyVerts
#undef plane 
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C07F0.s")
#endif

#define CollisionPoly_SphVsPoly BgCheck_PolygonCollidesWithSphere
#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_PolygonCollidesWithSphere.s")
//OK
//s32 BgCheck_PolygonCollidesWithSphere(CollisionPoly* poly, Vec3s* vtxList, Vec3f* center, f32 radius) {
//    static Sphere16 sphere; //D_801EDBA8
//    static TriNorm tri; //D_801EDBB0
//    Vec3f intersect;
//
//    BgCheck_CreateTriNormFromPolygon(poly, vtxList, tri.vtx);
//    BgCheck_PolygonGetNormal(poly, &tri.plane.normal.x, &tri.plane.normal.y, &tri.plane.normal.z);
//    tri.plane.originDist = poly->dist;
//    sphere.center.x = center->x;
//    sphere.center.y = center->y;
//    sphere.center.z = center->z;
//    sphere.radius = radius;
//    return Math3D_ColSphereTri(&sphere, &tri, &intersect);
//}

#define StaticLookup_AddPolyToSSList BgCheck_ScenePolygonListsInsertSorted
#ifdef NON_MATCHING
/**
 * Add poly to StaticLookup table
 * Table is sorted by poly's smallest y vertex component
 * `ssList` is the list to append a new poly to
 * `polyList` is the CollisionPoly lookup list
 * `vtxList` is the vertex lookup list
 * `polyId` is the index of the poly in polyList to insert into the lookup table
 */
void BgCheck_ScenePolygonListsInsertSorted(CollisionContext* colCtx, SSList* ssList, CollisionPoly* polyList, Vec3s* vtxList,
    s16 polyId) {
    SSNode* curNode;
    SSNode* nextNode;
    s32 polyYMin;
    u16 newNodeId;
    s16 curPolyId;

    // if list is null
    if (ssList->head == SS_NULL) {
        SSNodeList_SetSSListHead(&colCtx->polyNodes, ssList, &polyId);
        return;
    }

    polyYMin = BgCheck_PolygonGetMinY(&polyList[polyId], vtxList);

    curNode = &colCtx->polyNodes.tbl[ssList->head];
    curPolyId = curNode->polyId;

    // if the poly being inserted has a lower y than the first poly
    if (polyYMin < vtxList[COLPOLY_VTX_INDEX(polyList[curPolyId].flags_vIA)].y &&
        polyYMin < vtxList[COLPOLY_VTX_INDEX(polyList[curPolyId].flags_vIB)].y &&
        polyYMin < vtxList[polyList[curPolyId].vIC].y) {
        SSNodeList_SetSSListHead(&colCtx->polyNodes, ssList, &polyId);
        return;
    }
    while (true) {
        // if at the end of the list
        if (curNode->next == SS_NULL) {
            newNodeId = BgCheck_ScenePolygonListsReserveNode(&colCtx->polyNodes);
            SSNode_SetValue(&colCtx->polyNodes.tbl[newNodeId], &polyId, SS_NULL);
            curNode->next = newNodeId;
            return;
        }

        nextNode = &colCtx->polyNodes.tbl[curNode->next];
        curPolyId = nextNode->polyId;

        // if the poly being inserted is lower than the next poly
        if (polyYMin < vtxList[COLPOLY_VTX_INDEX(polyList[curPolyId].flags_vIA)].y &&
            polyYMin < vtxList[COLPOLY_VTX_INDEX(polyList[curPolyId].flags_vIB)].y &&
            polyYMin < vtxList[polyList[curPolyId].vIC].y) {
            newNodeId = BgCheck_ScenePolygonListsReserveNode(&colCtx->polyNodes);
            SSNode_SetValue(&colCtx->polyNodes.tbl[newNodeId], &polyId, curNode->next);
            curNode->next = newNodeId;
            return;
        }
        curNode = nextNode;
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_ScenePolygonListsInsertSorted.s")
#endif 

/**
 * Add CollisionPoly to StaticLookup list
 */
#define StaticLookup_AddPoly BgCheck_ScenePolygonListsInsert
void BgCheck_ScenePolygonListsInsert(StaticLookup* lookup, CollisionContext* colCtx, CollisionPoly* polyList, Vec3s* vtxList,
    s16 index) {
    if (polyList[index].normal.y > COLPOLY_SNORMAL(0.5f)) {
        StaticLookup_AddPolyToSSList(colCtx, &lookup->floor, polyList, vtxList, index);
    }
    else if (polyList[index].normal.y < COLPOLY_SNORMAL(-0.8f)) {
        StaticLookup_AddPolyToSSList(colCtx, &lookup->ceiling, polyList, vtxList, index);
    }
    else {
        StaticLookup_AddPolyToSSList(colCtx, &lookup->wall, polyList, vtxList, index);
    }
}

#define BgCheck_RaycastFloorStaticList func_800C0E74
/**
 * Locates the closest static poly directly underneath `pos`, starting at list `ssList`
 * returns yIntersect of the closest poly, or `yIntersectMin`
 * stores the pointer of the closest poly to `outPoly`
 * if (flags & 1), ignore polys with a normal.y < 0 (from vertical walls to ceilings)
 */
f32 BgCheck_RaycastFloorStaticList(CollisionContext* colCtx, u16 xpFlags, SSList* ssList, CollisionPoly** outPoly,
    Vec3f* pos, f32 yIntersectMin, f32 chkDist, s32 flags, Actor* actor, s32 arg9) {
    SSNode* curNode;
    s32 polyId;
    f32 result;
    f32 yIntersect;
    CollisionPoly* colPoly;
    s32 pad;

    result = yIntersectMin;
    if (ssList->head == SS_NULL) {
        return result;
    }

    curNode = &colCtx->polyNodes.tbl[ssList->head];

    while (true) {
        polyId = curNode->polyId;
        colPoly = &colCtx->colHeader->polyList[polyId];

        if ( (flags & 1) && (colPoly->normal.y < 0)
            || ( (arg9 & 0x20) && ((colCtx->colHeader->surfaceTypeList[colPoly->type].data[0] >> 0x1E) & 1))
            || COLPOLY_VIA_FLAG_TEST(colPoly->flags_vIA, xpFlags)
            || (COLPOLY_VIA_FLAG_TEST(colPoly->flags_vIB, 4)
                && ( (actor != NULL && actor->category != ACTORCAT_PLAYER) || (actor == NULL && xpFlags != 1))))
        {
            if (curNode->next == SS_NULL) {
                break;
            }
            curNode = &colCtx->polyNodes.tbl[curNode->next];
            continue;
        }

        if (pos->y < colCtx->colHeader->vtxList[COLPOLY_VTX_INDEX(colPoly->flags_vIA)].y &&
            pos->y < colCtx->colHeader->vtxList[COLPOLY_VTX_INDEX(colPoly->flags_vIB)].y &&
            pos->y < colCtx->colHeader->vtxList[colPoly->vIC].y) {
            break;
        }

        if (CollisionPoly_CheckYIntersect(colPoly, colCtx->colHeader->vtxList, pos->x,
            pos->z, &yIntersect, chkDist)) {
            // if poly is closer to pos without going over
            if (yIntersect < pos->y && result < yIntersect) {
                result = yIntersect;
                *outPoly = colPoly;
            }
        }

        if (curNode->next == SS_NULL) {
            break;
        }
        curNode = &colCtx->polyNodes.tbl[curNode->next];
    }
    return result;
}

#define BgCheck_RaycastFloorStatic func_800C10FC
/**
 * Locates the closest static poly directly underneath `pos` within `lookup`.
 * returns yIntersect of the closest poly, or `yIntersectMin`
 * stores the pointer of the closest poly to `outPoly`
 */
f32 BgCheck_RaycastFloorStatic(StaticLookup* lookup, CollisionContext* colCtx, u16 xpFlags, CollisionPoly** poly, Vec3f* pos, u32 arg5, f32 chkDist, f32 yIntersectMin, Actor* actor) {
    s32 flag; // skip polys with normal.y < 0
    f32 yIntersect = yIntersectMin;

    if (arg5 & 4) {
        yIntersect = BgCheck_RaycastFloorStaticList(colCtx, xpFlags, &lookup->floor, poly, pos, yIntersect, chkDist, 0, actor, arg5);
    }

    if ((arg5 & 2) || (arg5 & 8)) {
        flag = 0;
        if (arg5 & 0x10) {
            flag = 1;
        }
        yIntersect =
            BgCheck_RaycastFloorStaticList(colCtx, xpFlags, &lookup->wall, poly, pos, yIntersect, chkDist, flag, actor, arg5);
    }

    if (arg5 & 1) {
        flag = 0;
        if (arg5 & 0x10) {
            flag = 1;
        }
        yIntersect =
            BgCheck_RaycastFloorStaticList(colCtx, xpFlags, &lookup->ceiling, poly, pos, yIntersect, chkDist, flag, actor, arg5);
    }

    return yIntersect;
}

#define BgCheck_ComputeWallDisplacement func_800C1238
/**
 * Compute wall displacement on `posX` and `posZ`
 * sets `wallPolyPtr` to `poly` if `wallPolyPtr` is NULL
 * returns true if `wallPolyPtr` was changed
 * `invXZlength` is 1 / sqrt( sq(poly.normal.x) + sq(poly.normal.z) )
 */
s32 BgCheck_ComputeWallDisplacement(CollisionContext* colCtx, CollisionPoly* poly, f32* posX, f32* posZ, f32 nx, f32 ny,
    f32 nz, f32 invXZlength, f32 planeDist, f32 radius, CollisionPoly** wallPolyPtr) {
    f32 displacement = (radius - planeDist) * invXZlength;

    *posX += displacement * nx;
    *posZ += displacement * nz;

    if (*wallPolyPtr == NULL) {
        *wallPolyPtr = poly;
        return true;
    }
    else
    {
        return false;
    }
}

#define BgCheck_SphVsStaticWall func_800C12A4
/**
 * Performs collision detection on static poly walls within `lookup` on sphere `pos`, `radius`
 * returns true if a collision was detected
 * `outX` `outZ` return the displaced x,z coordinates,
 * `outPoly` returns the pointer to the nearest poly collided with, or NULL
 */
s32 BgCheck_SphVsStaticWall(StaticLookup* lookup, CollisionContext* colCtx, u16 xpFlags, f32* outX, f32* outZ,
    Vec3f* pos, f32 radius, CollisionPoly** outPoly, Actor* actor) {
    Vec3f resultPos;
    f32 zTemp;
    f32 xTemp;
    f32 planeDist;
    f32 intersect;
    s32 result;
    CollisionPoly* curPoly;
    CollisionPoly* polyList;
    SSNode* curNode;
    f32 invNormalXZ;
    Vec3s* vtxA;
    Vec3s* vtxB;
    Vec3s* vtxC;
    s32 polyId;
    f32 normalXZ;
    f32 nx;
    f32 ny;
    f32 nz;
    Vec3s* vtxList;
    u16 pad;
    f32 temp_f16;

    f32 zMin;
    f32 zMax;
    f32 xMin;
    f32 xMax;

    result = false;
    if (lookup->wall.head == SS_NULL) {
        return result;
    }
    resultPos = *pos;

    polyList = colCtx->colHeader->polyList;
    vtxList = colCtx->colHeader->vtxList;
    curNode = &colCtx->polyNodes.tbl[lookup->wall.head];

    while (true) {
        polyId = curNode->polyId;
        curPoly = &polyList[polyId];
        vtxA = &vtxList[COLPOLY_VTX_INDEX(curPoly->flags_vIA)];
        vtxB = &vtxList[COLPOLY_VTX_INDEX(curPoly->flags_vIB)];
        vtxC = &vtxList[curPoly->vIC];

        if (pos->y < vtxA->y &&
            pos->y < vtxB->y && pos->y < vtxC->y) {
            break;
        }

        nx = COLPOLY_GET_NORMAL(curPoly->normal.x);
        ny = COLPOLY_GET_NORMAL(curPoly->normal.y);
        nz = COLPOLY_GET_NORMAL(curPoly->normal.z);
        normalXZ = sqrtf(SQ(nx) + SQ(nz));
        planeDist = Math3D_DistPlaneToPos(nx, ny, nz, curPoly->dist, &resultPos);
        if (radius < fabsf(planeDist) 
            || COLPOLY_VIA_FLAG_TEST(curPoly->flags_vIA, xpFlags)
            || (COLPOLY_VIA_FLAG_TEST(curPoly->flags_vIB, 4)
                && ((actor != NULL && actor->category != ACTORCAT_PLAYER) || (actor == NULL && xpFlags != 1)))) {
            if (curNode->next == SS_NULL) {
                break;
            }
            else {
                curNode = &colCtx->polyNodes.tbl[curNode->next];
                continue;
            }
        }

        //ASSERT(!IS_ZERO(normalXZ), "!IS_ZERO(ac_size)", "../z_bgcheck.c", __LINE__);

        invNormalXZ = 1.0f / normalXZ;
        temp_f16 = fabsf(nz) * invNormalXZ;
        if (temp_f16 < 0.4f) {
            if (curNode->next == SS_NULL) {
                break;
            }
            else {
                curNode = &colCtx->polyNodes.tbl[curNode->next];
                continue;
            }
        }

        // compute curPoly zMin/zMax
        zTemp = vtxA->z;
        zMax = zMin = zTemp;
        zTemp = vtxB->z;

        if (zTemp < zMin) {
            zMin = zTemp;
        }
        else if (zMax < zTemp) {
            zMax = zTemp;
        }
        zTemp = vtxC->z;
        if (zTemp < zMin) {
            zMin = zTemp;
        }
        else if (zTemp > zMax) {
            zMax = zTemp;
        }

        zMin -= radius;
        zMax += radius;

        if (resultPos.z < zMin || resultPos.z > zMax) {
            if (curNode->next == SS_NULL) {
                break;
            }
            else {
                curNode = &colCtx->polyNodes.tbl[curNode->next];
                continue;
            }
        }
        if (CollisionPoly_CheckZIntersectApprox(curPoly, vtxList, resultPos.x, pos->y, &intersect)) {
            f32 test = intersect - resultPos.z;
            if (fabsf(test) <= radius / temp_f16) {
                if ((test) * nz <= 4.0f) {
                    if (BgCheck_ComputeWallDisplacement(colCtx, curPoly, &resultPos.x, &resultPos.z, nx, ny, nz,
                        invNormalXZ, planeDist, radius, outPoly))
                    {
                        result = true;
                    }
                }
            }
        }
        if (curNode->next == SS_NULL) {
            break;
        }
        else {
            curNode = &colCtx->polyNodes.tbl[curNode->next];
        }
    }

    curNode = &colCtx->polyNodes.tbl[lookup->wall.head];

    while (true) {
        polyId = curNode->polyId;
        curPoly = &polyList[polyId];
        vtxA = &vtxList[COLPOLY_VTX_INDEX(curPoly->flags_vIA)];
        vtxB = &vtxList[COLPOLY_VTX_INDEX(curPoly->flags_vIB)];
        vtxC = &vtxList[curPoly->vIC];

        if (pos->y < vtxA->y && pos->y < vtxB->y && pos->y < vtxC->y) {
            break;
        }

        nx = COLPOLY_GET_NORMAL(curPoly->normal.x);
        ny = COLPOLY_GET_NORMAL(curPoly->normal.y);
        nz = COLPOLY_GET_NORMAL(curPoly->normal.z);
        normalXZ = sqrtf(SQ(nx) + SQ(nz));
        planeDist = Math3D_DistPlaneToPos(nx, ny, nz, curPoly->dist, &resultPos);
        if (radius < fabsf(planeDist) 
            || COLPOLY_VIA_FLAG_TEST(curPoly->flags_vIA, xpFlags)
            || (COLPOLY_VIA_FLAG_TEST(curPoly->flags_vIB, 4)
                && ((actor != NULL && actor->category != ACTORCAT_PLAYER) || (actor == NULL && xpFlags != 1)))) {
            if (curNode->next == SS_NULL) {
                break;
            }
            else {
                curNode = &colCtx->polyNodes.tbl[curNode->next];
                continue;
            }
        }

        //ASSERT(!IS_ZERO(normalXZ), "!IS_ZERO(ac_size)", "../z_bgcheck.c", __LINE__);

        invNormalXZ = 1.0f / normalXZ;
        temp_f16 = fabsf(nx) * invNormalXZ;
        if (temp_f16 < 0.4f) {
            if (curNode->next == SS_NULL) {
                break;
            }
            else {
                curNode = &colCtx->polyNodes.tbl[curNode->next];
                continue;
            }
        }

        // compute curPoly xMin/xMax
        xTemp = vtxA->x;
        xMax = xMin = xTemp;
        xTemp = vtxB->x;

        if (xTemp < xMin) {
            xMin = xTemp;
        }
        else if (xMax < xTemp) {
            xMax = xTemp;
        }
        xTemp = vtxC->x;
        if (xTemp < xMin) {
            xMin = xTemp;
        }
        else if (xMax < xTemp) {
            xMax = xTemp;
        }

        xMin -= radius;
        xMax += radius;

        if (resultPos.x < xMin || xMax < resultPos.x) {
            if (curNode->next == SS_NULL) {
                break;
            }
            else {
                curNode = &colCtx->polyNodes.tbl[curNode->next];
                continue;
            }
        }
        if (CollisionPoly_CheckXIntersectApprox(curPoly, vtxList, pos->y, resultPos.z, &intersect)) {
            f32 test = intersect - resultPos.x;
            if (fabsf(test) <= radius / temp_f16) {
                if ((test) * nx <= 4.0f) {
                    if (BgCheck_ComputeWallDisplacement(colCtx, curPoly, &resultPos.x, &resultPos.z, nx, ny, nz,
                        invNormalXZ, planeDist, radius, outPoly))
                    {
                        result = true;
                    }
                }
            }
        }
        if (curNode->next == SS_NULL) {
            break;
        }
        else {
            curNode = &colCtx->polyNodes.tbl[curNode->next];
            continue;
        }
    }

    *outX = resultPos.x;
    *outZ = resultPos.z;
    return result;
}

#define BgCheck_CheckStaticCeiling func_800C1B68
/**
 * Tests for collision with a static poly ceiling
 * returns true if a collision occurs, else false
 * `outPoly` returns the poly collided with
 * `outY` returns the y coordinate needed to not collide with `outPoly`
 */
s32 BgCheck_CheckStaticCeiling(StaticLookup* lookup, u16 xpFlags, CollisionContext* colCtx, f32* outY, Vec3f* pos,
    f32 checkHeight, CollisionPoly** outPoly, Actor* actor);
#ifdef NON_MATCHING
s32 BgCheck_CheckStaticCeiling(StaticLookup* lookup, u16 xpFlags, CollisionContext* colCtx, f32* outY, Vec3f* pos,
    f32 checkHeight, CollisionPoly** outPoly, Actor* actor) {
    s32 result = false;
    //u16 nextId;
    CollisionPoly* curPoly;
    CollisionPoly* polyList;
    f32 ceilingY;
    Vec3s* vtxList;
    SSNode* curNode;
    s32 curPolyId;

    if (lookup->ceiling.head == SS_NULL) {
        return result;
    }
    curNode = &colCtx->polyNodes.tbl[lookup->ceiling.head];
    polyList = colCtx->colHeader->polyList;
    vtxList = colCtx->colHeader->vtxList;

    *outY = pos->y;

    while (true) {
        curPolyId = curNode->polyId;
        curPoly = &polyList[curPolyId];
        if (COLPOLY_VIA_FLAG_TEST(colCtx->colHeader->polyList[curPolyId].flags_vIA, xpFlags)
            || ( 
                COLPOLY_VIA_FLAG_TEST(colCtx->colHeader->polyList[curPolyId].flags_vIB, 4) 
                && ((actor != NULL && actor->category != ACTORCAT_PLAYER) || (actor == NULL && xpFlags != 1 )))) {
            if (curNode->next == SS_NULL) {
                break;
            }
            else {
                curNode = &colCtx->polyNodes.tbl[curNode->next];
                continue;
            }
        }

        if (CollisionPoly_CheckYIntersectApprox2(curPoly, vtxList, pos->x, pos->z, &ceilingY)) {
            f32 intersectDist = ceilingY - *outY;
            f32 ny = COLPOLY_GET_NORMAL(curPoly->normal.y);

            if (intersectDist > 0 && intersectDist < checkHeight && intersectDist * ny <= 0) {
                *outY = ceilingY - checkHeight;
                *outPoly = curPoly;
                result = true;
            }
        }
        if (curNode->next == SS_NULL) {
            break;
        }
        else {
            curNode = &colCtx->polyNodes.tbl[curNode->next];
            continue;
        }
    }
    return result;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C1B68.s")
#endif 

#define BgCheck_CheckLineAgainstSSList func_800C1D7C
/**
 * Tests if line `posA` to `posB` intersects with a static poly in list `ssList`. Uses polyCheckTbl
 * returns true if such a poly exists, else false
 * `outPoly` returns the pointer of the poly intersected
 * `posB` and `outPos` returns the point of intersection with `outPoly`
 * `outDistSq` returns the squared distance from `posA` to the point of intersect
 */
s32 BgCheck_CheckLineAgainstSSList(struct_func_800C1D7C* arg0);
#ifdef NON_MATCHING
s32 BgCheck_CheckLineAgainstSSList(struct_func_800C1D7C* arg0) {
    
    CollisionContext* colCtx;
    s32 result;
    Vec3f polyIntersect; //sp7C

    SSNode* curNode;
    u8* checkedPoly;
    //CollisionPoly* polyList;
    f32 minY;
    f32 distSq;
    func_800C07F0_args test; //sp50
    s16 polyId;

    result = false;
    if (arg0->ssList->head == SS_NULL) {
        return result;
    }
    colCtx = arg0->colCtx;
    curNode = &colCtx->polyNodes.tbl[arg0->ssList->head];
    test.vtxList = colCtx->colHeader->vtxList;
    test.posA = arg0->posA;
    test.posB = arg0->posB;
    test.planeIntersect = &polyIntersect; //reorder maybe
    test.chkOneFace = arg0->bccFlags & BGCHECK_CHECK_ONE_FACE;
    test.chkDist = arg0->chkDist;

    while (true) {
        polyId = curNode->polyId;
        test.poly = &colCtx->colHeader->polyList[polyId];
        checkedPoly = &colCtx->polyNodes.polyCheckTbl[polyId];

        if (*checkedPoly == true || COLPOLY_VIA_FLAG_TEST(test.poly->flags_vIA, arg0->xpFlags1)
            || !(arg0->xpFlags2 == 0 || COLPOLY_VIA_FLAG_TEST(test.poly->flags_vIA, arg0->xpFlags2))
            || (COLPOLY_VIA_FLAG_TEST(test.poly->flags_vIB, 4) && ((arg0->actor != NULL && arg0->actor->category != ACTORCAT_PLAYER) || (arg0->actor == NULL && arg0->xpFlags1 != 1))))
        {
            if (curNode->next == SS_NULL) {
                break;
            }
            else {
                curNode = &arg0->colCtx->polyNodes.tbl[curNode->next];
                continue;
            }
        }
        *checkedPoly = true;
        minY = CollisionPoly_GetMinY(test.poly, (BgVertex*)test.vtxList);
        if (test.posA->y < minY && test.posB->y < minY) {
            break;
        }
        if (CollisionPoly_LineVsPoly(&test)) {
            distSq = Math3D_Vec3fDistSq(test.posA, test.planeIntersect);
            if (distSq < arg0->outDistSq) {
                arg0->outDistSq = distSq;
                *arg0->outPos = *test.planeIntersect;
                *arg0->posB = *test.planeIntersect;
                arg0->outPoly = test.poly;
                result = true;
            }
        }
        if (curNode->next == SS_NULL) {
            break;
        }
        curNode = &arg0->colCtx->polyNodes.tbl[curNode->next];
    }
    return result;
}
#else 
#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C1D7C.s")
#endif

#define BgCheck_CheckLineInSubdivision func_800C2008
/**
 * Tests if line `posA` to `posB` intersects with a static poly in `lookup`. Uses polyCheckTbl
 * returns true if such a poly exists, else false
 * `outPoly` returns the pointer of the poly intersected
 * `posB` and `outPos` returns the point of intersection with `outPoly`
 * `outDistSq` returns the squared distance from `posA` to the point of intersect
 */
s32 BgCheck_CheckLineInSubdivision(struct_func_800C1D7C* arg0) {
    s32 result = false;

    if ((arg0->bccFlags & BGCHECK_CHECK_FLOOR) && arg0->lookup->floor.head != SS_NULL) {
        arg0->ssList = &arg0->lookup->floor;
        if (BgCheck_CheckLineAgainstSSList(arg0)) {
            result = true;
        }
    }

    if ((arg0->bccFlags & BGCHECK_CHECK_WALL) && arg0->lookup->wall.head != SS_NULL) {
        arg0->ssList = &arg0->lookup->wall;
        if (BgCheck_CheckLineAgainstSSList(arg0)) {
            result = true;
        }
    }

    if ((arg0->bccFlags & BGCHECK_CHECK_CEILING) && arg0->lookup->ceiling.head != SS_NULL) {
        arg0->ssList = &arg0->lookup->ceiling;
        if (BgCheck_CheckLineAgainstSSList(arg0)) {
            result = true;
        }
    }
    return result;
}

#define BgCheck_SphVsFirstStaticPolyList func_800C20F4
/**
 * Get first static poly intersecting sphere `center` `radius` from list `node`
 * returns true if any poly intersects the sphere, else returns false
 * `outPoly` returns the pointer of the first poly found that intersects
 */
s32 BgCheck_SphVsFirstStaticPolyList(SSNode* node, u16 xpFlags, CollisionContext* colCtx, Vec3f* center, f32 radius,
    CollisionPoly** outPoly, Actor* actor);
#ifdef NON_MATCHING
s32 BgCheck_SphVsFirstStaticPolyList(SSNode* node, u16 xpFlags, CollisionContext* colCtx, Vec3f* center, f32 radius,
    CollisionPoly** outPoly, Actor* actor) {
    Vec3s* vtxList;
    CollisionPoly* polyList;
    CollisionPoly* curPoly;
    u16 nextId;
    s16 curPolyId;
    s32 pad;

    polyList = colCtx->colHeader->polyList;
    vtxList = colCtx->colHeader->vtxList;

    while (true) {
        curPolyId = node->polyId;
        curPoly = &polyList[curPolyId];
        if (COLPOLY_VIA_FLAG_TEST(colCtx->colHeader->polyList[curPolyId].flags_vIA, xpFlags)
            || (COLPOLY_VIA_FLAG_TEST(colCtx->colHeader->polyList[curPolyId].flags_vIB, 4)
                && ((actor != NULL && actor->category != ACTORCAT_PLAYER) || (actor == NULL && xpFlags != 1)))) {
            if (node->next != SS_NULL) {
                node = &colCtx->polyNodes.tbl[node->next];
                continue;
            }
            break;
        }

        if (center->y + radius < vtxList[COLPOLY_VTX_INDEX(curPoly->flags_vIA)].y &&
            center->y + radius < vtxList[COLPOLY_VTX_INDEX(curPoly->flags_vIB)].y &&
            center->y + radius < vtxList[curPoly->vIC].y) {
            break;
        }

        if (CollisionPoly_SphVsPoly(curPoly, vtxList, center, radius)) {
            *outPoly = curPoly;
            return true;
        }
        if (node->next != SS_NULL) {
            node = &colCtx->polyNodes.tbl[node->next];
            continue;
        }
        break;
    }
    return false;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C20F4.s")
#endif

#define BgCheck_SphVsFirstStaticPoly func_800C2310
/**
 * Get first static poly intersecting sphere `center` `radius` within `lookup`
 * returns true if any poly intersects the sphere, else false
 * `outPoly` returns the first poly found that intersects
 */
s32 BgCheck_SphVsFirstStaticPoly(StaticLookup* lookup, u16 xpFlags, CollisionContext* colCtx, Vec3f* center, f32 radius,
    CollisionPoly** outPoly, u16 bciFlags, Actor* actor) {
    if (lookup->floor.head != SS_NULL && !(bciFlags & BGCHECK_IGNORE_FLOOR) &&
        BgCheck_SphVsFirstStaticPolyList(&colCtx->polyNodes.tbl[lookup->floor.head], xpFlags, colCtx, center, radius,
            outPoly, actor)) {
        return true;
    }

    if (lookup->wall.head != SS_NULL && !(bciFlags & BGCHECK_IGNORE_WALL) &&
        BgCheck_SphVsFirstStaticPolyList(&colCtx->polyNodes.tbl[lookup->wall.head], xpFlags, colCtx, center, radius,
            outPoly, actor)) {
        return true;
    }

    if (lookup->ceiling.head != SS_NULL && !(bciFlags & BGCHECK_IGNORE_CEILING) &&
        BgCheck_SphVsFirstStaticPolyList(&colCtx->polyNodes.tbl[lookup->ceiling.head], xpFlags, colCtx, center, radius,
            outPoly, actor)) {
        return true;
    }

    return false;
}

/**
 * Get StaticLookup from `pos`
 * Does not return NULL
 */
StaticLookup* BgCheck_GetNearestStaticLookup(CollisionContext* colCtx, StaticLookup* lookupTbl, Vec3f* pos) {
    Vec3i sector;
    s32 subdivAmountX;

    BgCheck_GetStaticLookupIndicesFromPos(colCtx, pos, &sector);
    subdivAmountX = colCtx->subdivAmount.x;
    return (sector.z * subdivAmountX) * colCtx->subdivAmount.y + lookupTbl + sector.x + sector.y * subdivAmountX;
}

#define BgCheck_GetStaticLookup func_800C2514

/**
 * Get StaticLookup from `pos`
 * Returns NULL if just outside the mesh bounding box
 */
StaticLookup* BgCheck_GetStaticLookup(CollisionContext* colCtx, StaticLookup* lookupTbl, Vec3f* pos) {
    Vec3i sector;
    s32 subdivAmountX;

    if (!BgCheck_PosInStaticBoundingBox(colCtx, pos)) {
        return NULL;
    }
    BgCheck_GetStaticLookupIndicesFromPos(colCtx, pos, &sector);
    subdivAmountX = colCtx->subdivAmount.x;
    return (sector.z * subdivAmountX) * colCtx->subdivAmount.y + lookupTbl + sector.x + sector.y * subdivAmountX;
}

/**
 * Get StaticLookup subdivision indices from `pos`
 * `sector` returns the subdivision x,y,z indices containing or is nearest to `pos`
 */
void BgCheck_GetStaticLookupIndicesFromPos(CollisionContext* colCtx, Vec3f* pos, Vec3i* sector) {
    sector->x = (pos->x - colCtx->minBounds.x) * colCtx->subdivLengthInv.x;
    sector->y = (pos->y - colCtx->minBounds.y) * colCtx->subdivLengthInv.y;
    sector->z = (pos->z - colCtx->minBounds.z) * colCtx->subdivLengthInv.z;

    if (sector->x < 0) {
        sector->x = 0;
    }
    else if (sector->x >= colCtx->subdivAmount.x) {
        sector->x = colCtx->subdivAmount.x - 1;
    }

    if (sector->y < 0) {
        sector->y = 0;
    }
    else if (sector->y >= colCtx->subdivAmount.y) {
        sector->y = colCtx->subdivAmount.y - 1;
    }

    if (sector->z < 0) {
        sector->z = 0;
    }
    else if (sector->z >= colCtx->subdivAmount.z) {
        sector->z = colCtx->subdivAmount.z - 1;
    }
}

/**
 * Get negative bias subdivision indices
 * decrements indices if `pos` is within BGCHECK_SUBDIV_OVERLAP units of the negative subdivision boundary
 * `sx`, `sy`, `sz` returns the subdivision x, y, z indices
 */
#define BgCheck_GetSubdivisionMinBounds BgCheck_GetPolyMinSubdivisions
void BgCheck_GetSubdivisionMinBounds(CollisionContext* colCtx, Vec3f* pos, s32* sx, s32* sy, s32* sz) {
    f32 dx = pos->x - colCtx->minBounds.x;
    f32 dy = pos->y - colCtx->minBounds.y;
    f32 dz = pos->z - colCtx->minBounds.z;
    *sx = dx * colCtx->subdivLengthInv.x;
    *sy = dy * colCtx->subdivLengthInv.y;
    *sz = dz * colCtx->subdivLengthInv.z;

    if (((s32)dx % (s32)colCtx->subdivLength.x < BGCHECK_SUBDIV_OVERLAP) && (*sx > 0)) {
        *sx -= 1;
    }

    if (((s32)dy % (s32)colCtx->subdivLength.y < BGCHECK_SUBDIV_OVERLAP) && (*sy > 0)) {
        *sy -= 1;
    }

    if (((s32)dz % (s32)colCtx->subdivLength.z < BGCHECK_SUBDIV_OVERLAP) && (*sz > 0)) {
        *sz -= 1;
    }
}

/**
 * Get positive bias subdivision indices
 * increments indicies if `pos` is within BGCHECK_SUBDIV_OVERLAP units of the postive subdivision boundary
 * `sx`, `sy`, `sz` returns the subdivision x, y, z indices
 */
#define BgCheck_GetSubdivisionMaxBounds BgCheck_GetPolyMaxSubdivisions
void BgCheck_GetSubdivisionMaxBounds(CollisionContext* colCtx, Vec3f* pos, s32* sx, s32* sy, s32* sz) {
    f32 dx = pos->x - colCtx->minBounds.x;
    f32 dy = pos->y - colCtx->minBounds.y;
    f32 dz = pos->z - colCtx->minBounds.z;
    *sx = dx * colCtx->subdivLengthInv.x;
    *sy = dy * colCtx->subdivLengthInv.y;
    *sz = dz * colCtx->subdivLengthInv.z;

    if (((s32)colCtx->subdivLength.x - BGCHECK_SUBDIV_OVERLAP < (s32)dx % (s32)colCtx->subdivLength.x) &&
        (*sx < colCtx->subdivAmount.x - 1)) {
        *sx += 1;
    }

    if (((s32)colCtx->subdivLength.y - BGCHECK_SUBDIV_OVERLAP < (s32)dy % (s32)colCtx->subdivLength.y) &&
        (*sy < colCtx->subdivAmount.y - 1)) {
        *sy += 1;
    }

    if (((s32)colCtx->subdivLength.z - BGCHECK_SUBDIV_OVERLAP < (s32)dz % (s32)colCtx->subdivLength.z) &&
        (*sz < colCtx->subdivAmount.z - 1)) {
        *sz += 1;
    }
}

/**
 * Calculate the subdivision index bounding box for CollisionPoly `polyId`
 * `subdivMinX`, `subdivMinY`, `subdivMinZ` returns the minimum subdivision x, y, z indices
 * `subdivMaxX`, `subdivMaxY`, `subdivMaxZ` returns the maximum subdivision x, y, z indices
 */
#define BgCheck_GetPolySubdivisionBounds BgCheck_GetPolyMinMaxSubdivisions
void BgCheck_GetPolySubdivisionBounds(CollisionContext* colCtx, Vec3s* vtxList, CollisionPoly* polyList,
    s32* subdivMinX, s32* subdivMinY, s32* subdivMinZ, s32* subdivMaxX,
    s32* subdivMaxY, s32* subdivMaxZ, s16 polyId) {
    u16* vtxDataTemp;
    Vec3f minVtx;
    Vec3f maxVtx;

    f32 x;
    f32 y;
    f32 z;

    Vec3s* vtx;
    s16 vtxId = COLPOLY_VTX_INDEX(polyList[polyId].vtxData[0]);

    Math_Vec3s_ToVec3f(&maxVtx, &vtxList[vtxId]);
    Math_Vec3f_Copy(&minVtx, &maxVtx);

    for (vtxDataTemp = polyList[polyId].vtxData + 1; vtxDataTemp < polyList[polyId].vtxData + 3; vtxDataTemp++) {
        vtxId = COLPOLY_VTX_INDEX(*vtxDataTemp);
        vtx = &vtxList[vtxId];
        x = vtx->x;
        y = vtx->y;
        z = vtx->z;

        if (minVtx.x > x) {
            minVtx.x = x;
        }
        else if (maxVtx.x < x) {
            maxVtx.x = x;
        }

        if (minVtx.y > y) {
            minVtx.y = y;
        }
        else if (maxVtx.y < y) {
            maxVtx.y = y;
        }

        if (minVtx.z > z) {
            minVtx.z = z;
        }
        else if (maxVtx.z < z) {
            maxVtx.z = z;
        }
    }
    BgCheck_GetSubdivisionMinBounds(colCtx, &minVtx, subdivMinX, subdivMinY, subdivMinZ);
    BgCheck_GetSubdivisionMaxBounds(colCtx, &maxVtx, subdivMaxX, subdivMaxY, subdivMaxZ);
}

#define BgCheck_PolyIntersectsSubdivision func_800C2BE0
/**
 * Test if poly `polyList`[`polyId`] intersects cube `min` `max`
 * returns true if the poly intersects the cube, else false
 */
s32 BgCheck_PolyIntersectsSubdivision(Vec3f* min, Vec3f* max, CollisionPoly* polyList, Vec3s* vtxList, s16 polyId) {
    f32 intersect;
    Vec3f va2;
    Vec3f vb2;
    Vec3f vc2;
    CollisionPoly* poly;
    f32 nx;
    f32 ny;
    f32 nz;
    f32 dist;
    Vec3f va;
    Vec3f vb;
    Vec3f vc;
    s32 flags[3];

    flags[0] = flags[1] = 0;
    poly = &polyList[polyId];

    BgCheck_Vec3sToVec3f(&vtxList[COLPOLY_VTX_INDEX(poly->flags_vIA)], &va);
    flags[0] = Math3D_PointRelativeToCubeFaces(&va, min, max);
    if (flags[0] == 0) {
        return true;
    }

    BgCheck_Vec3sToVec3f(&vtxList[COLPOLY_VTX_INDEX(poly->flags_vIB)], &vb);
    flags[1] = Math3D_PointRelativeToCubeFaces(&vb, min, max);
    if (flags[1] == 0) {
        return true;
    }

    BgCheck_Vec3sToVec3f(&vtxList[poly->vIC], &vc);
    flags[2] = Math3D_PointRelativeToCubeFaces(&vc, min, max);
    if (flags[2] == 0) {
        return true;
    }

    if (flags[0] & flags[1] & flags[2]) {
        return false;
    }

    flags[0] |= Math3D_PointRelativeToCubeEdges(&va, min, max) << 8;
    flags[1] |= Math3D_PointRelativeToCubeEdges(&vb, min, max) << 8;
    flags[2] |= Math3D_PointRelativeToCubeEdges(&vc, min, max) << 8;
    if (flags[0] & flags[1] & flags[2]) {
        return false;
    }

    flags[0] |= Math3D_PointRelativeToCubeVertices(&va, min, max) << 0x18;
    flags[1] |= Math3D_PointRelativeToCubeVertices(&vb, min, max) << 0x18;
    flags[2] |= Math3D_PointRelativeToCubeVertices(&vc, min, max) << 0x18;
    if (flags[0] & flags[1] & flags[2]) {
        return false;
    }

    CollisionPoly_GetNormalF(poly, &nx, &ny, &nz);
    dist = poly->dist;

    if (Math3D_TriChkLineSegParaYIntersect(&va, &vb, &vc, nx, ny, nz, dist, min->z, min->x, &intersect, min->y,
        max->y) ||
        Math3D_TriChkLineSegParaYIntersect(&va, &vb, &vc, nx, ny, nz, dist, max->z, min->x, &intersect, min->y,
            max->y) ||
        Math3D_TriChkLineSegParaYIntersect(&va, &vb, &vc, nx, ny, nz, dist, min->z, max->x, &intersect, min->y,
            max->y) ||
        Math3D_TriChkLineSegParaYIntersect(&va, &vb, &vc, nx, ny, nz, dist, max->z, max->x, &intersect, min->y,
            max->y)) {
        return true;
    }
    if (Math3D_TriChkLineSegParaZIntersect(&va, &vb, &vc, nx, ny, nz, dist, min->x, min->y, &intersect, min->z,
        max->z) ||
        Math3D_TriChkLineSegParaZIntersect(&va, &vb, &vc, nx, ny, nz, dist, min->x, max->y, &intersect, min->z,
            max->z) ||
        Math3D_TriChkLineSegParaZIntersect(&va, &vb, &vc, nx, ny, nz, dist, max->x, min->y, &intersect, min->z,
            max->z) ||
        Math3D_TriChkLineSegParaZIntersect(&va, &vb, &vc, nx, ny, nz, dist, max->x, max->y, &intersect, min->z,
            max->z)) {
        return true;
    }
    if (Math3D_TriChkLineSegParaXIntersect(&va, &vb, &vc, nx, ny, nz, dist, min->y, min->z, &intersect, min->x,
        max->x) ||
        Math3D_TriChkLineSegParaXIntersect(&va, &vb, &vc, nx, ny, nz, dist, min->y, max->z, &intersect, min->x,
            max->x) ||
        Math3D_TriChkLineSegParaXIntersect(&va, &vb, &vc, nx, ny, nz, dist, max->y, min->z, &intersect, min->x,
            max->x) ||
        Math3D_TriChkLineSegParaXIntersect(&va, &vb, &vc, nx, ny, nz, dist, max->y, max->z, &intersect, min->x,
            max->x)) {
        return true;
    }

    BgCheck_Vec3sToVec3f(&vtxList[COLPOLY_VTX_INDEX(poly->flags_vIA)], &va2);
    BgCheck_Vec3sToVec3f(&vtxList[COLPOLY_VTX_INDEX(poly->flags_vIB)], &vb2);
    BgCheck_Vec3sToVec3f(&vtxList[poly->vIC], &vc2);
    if (Math3D_LineVsCube(min, max, &va2, &vb2) || Math3D_LineVsCube(min, max, &vb2, &vc2) ||
        Math3D_LineVsCube(min, max, &vc2, &va2)) {
        return true;
    }
    return false;
}

#define BgCheck_InitializeStaticLookup BgCheck_SplitScenePolygonsIntoSubdivisions
/**
 * Initialize StaticLookup Table
 * returns size of table, in bytes
 */
u32 BgCheck_InitializeStaticLookup(CollisionContext* colCtx, GlobalContext* globalCtx, StaticLookup* lookupTbl) {
    Vec3s* vtxList;
    CollisionPoly* polyList;
    s32 polyMax;
    s32 polyIdx;
    s32 sx;
    s32 sy;
    s32 sz;
    // subdivMin indices
    s32 sxMin;
    s32 syMin;
    s32 szMin;
    // subdivMax indices
    s32 sxMax;
    s32 syMax;
    s32 szMax;
    // subdiv min/max bounds for adding a poly
    Vec3f curSubdivMin;
    Vec3f curSubdivMax;
    CollisionHeader* colHeader = colCtx->colHeader;
    s32 pad[2];
    StaticLookup* spA4;
    StaticLookup* phi_fp;
    StaticLookup* phi_s0;
    s32 sp98;
    f32 subdivLengthX;
    f32 subdivLengthY;
    f32 subdivLengthZ;

    for (spA4 = lookupTbl;
        spA4 < (colCtx->subdivAmount.x * colCtx->subdivAmount.y * colCtx->subdivAmount.z + lookupTbl); spA4++) {
        spA4->floor.head = SS_NULL;
        spA4->wall.head = SS_NULL;
        spA4->ceiling.head = SS_NULL;
    }

    polyMax = colHeader->numPolygons;
    vtxList = colHeader->vtxList;
    polyList = colHeader->polyList;
    sp98 = colCtx->subdivAmount.x * colCtx->subdivAmount.y;
    subdivLengthX = colCtx->subdivLength.x + (2 * BGCHECK_SUBDIV_OVERLAP);
    subdivLengthY = colCtx->subdivLength.y + (2 * BGCHECK_SUBDIV_OVERLAP);
    subdivLengthZ = colCtx->subdivLength.z + (2 * BGCHECK_SUBDIV_OVERLAP);

    for (polyIdx = 0; polyIdx < polyMax; polyIdx++) {
        BgCheck_GetPolySubdivisionBounds(colCtx, vtxList, polyList, &sxMin, &syMin, &szMin, &sxMax, &syMax, &szMax,
            polyIdx);
        spA4 = szMin * sp98 + lookupTbl;
        curSubdivMin.z = (colCtx->subdivLength.z * szMin + colCtx->minBounds.z) - BGCHECK_SUBDIV_OVERLAP;
        curSubdivMax.z = curSubdivMin.z + subdivLengthZ;

        for (sz = szMin; sz < szMax + 1; sz++) {
            phi_fp = (colCtx->subdivAmount.x * syMin) + spA4;
            curSubdivMin.y = (colCtx->subdivLength.y * syMin + colCtx->minBounds.y) - BGCHECK_SUBDIV_OVERLAP;
            curSubdivMax.y = curSubdivMin.y + subdivLengthY;

            for (sy = syMin; sy < syMax + 1; sy++) {
                phi_s0 = sxMin + phi_fp;
                curSubdivMin.x = (colCtx->subdivLength.x * sxMin + colCtx->minBounds.x) - BGCHECK_SUBDIV_OVERLAP;
                curSubdivMax.x = curSubdivMin.x + subdivLengthX;

                for (sx = sxMin; sx < sxMax + 1; sx++) {
                    if (BgCheck_PolyIntersectsSubdivision(&curSubdivMin, &curSubdivMax, polyList, vtxList, polyIdx)) {
                        StaticLookup_AddPoly(phi_s0, colCtx, polyList, vtxList, polyIdx);
                    }
                    curSubdivMin.x += colCtx->subdivLength.x;
                    curSubdivMax.x += colCtx->subdivLength.x;
                    phi_s0++;
                }
                curSubdivMin.y += colCtx->subdivLength.y;
                curSubdivMax.y += colCtx->subdivLength.y;
                phi_fp += colCtx->subdivAmount.x;
            }
            curSubdivMin.z += colCtx->subdivLength.z;
            curSubdivMax.z += colCtx->subdivLength.z;
            spA4 += sp98;
        }
    }
    return colCtx->polyNodes.count * sizeof(SSNode);
}

#define BgCheck_IsSpotScene BgCheck_GetIsDefaultSpecialScene
/**
 * Is current scene a SPOT scene
 */
s32 BgCheck_IsSpotScene(GlobalContext* globalCtx);
#ifdef NON_MATCHING
//OK, needs data migration
s32 BgCheck_IsSpotScene(GlobalContext* globalCtx) {
    static s16 spotScenes[] = {
        SCENE_F01,
    };
    s16* i;

    for (i = spotScenes; i < spotScenes + ARRAY_COUNT(spotScenes); i++) {
        if (globalCtx->sceneNum == *i) {
            return true;
        }
    }
    return false;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_GetIsDefaultSpecialScene.s")
#endif

typedef struct {
    s16 sceneId;
    u32 memSize;
} BgCheckSceneMemEntry;

#define BgCheck_TryGetCustomMemsize BgCheck_GetSpecialSceneMaxMemory
/**
 * Get custom scene memSize
 */
s32 BgCheck_TryGetCustomMemsize(s32 sceneId, u32* memSize);
#ifdef NON_MATCHING
// OK
s32 BgCheck_TryGetCustomMemsize(s32 sceneId, u32* memSize) {
    static BgCheckSceneMemEntry sceneMemList[] = {
        { SCENE_00KEIKOKU, 0xC800 },
    };
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sceneMemList); i++) {
        if (sceneId == sceneMemList[i].sceneId) {
            *memSize = sceneMemList[i].memSize;
            return true;
        }
    }
    return false;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_GetSpecialSceneMaxMemory.s")
#endif

/**
 * Compute subdivLength for scene mesh lookup, for a single dimension
 */
#define BgCheck_SetSubdivisionDimension BgCheck_CalcSubdivisionSize
void BgCheck_SetSubdivisionDimension(f32 min, s32 subdivAmount, f32* max, f32* subdivLength, f32* subdivLengthInv) {
    f32 length = (*max - min);

    *subdivLength = (s32)(length / subdivAmount) + 1;
    *subdivLength = CLAMP_MIN(*subdivLength, BGCHECK_SUBDIV_MIN);
    *subdivLengthInv = 1.0f / *subdivLength;

    *max = *subdivLength * subdivAmount + min;
}

//BgSpecialSceneMaxObjects customDynapolyMem[] = { //bgSpecialSceneMaxObjects
//    { SCENE_21MITURINMAE, 1000, 600, 512}
//};

s32 BgCheck_GetSpecialSceneMaxObjects(GlobalContext* globalCtx, u32* maxNodes, u32* maxPolygons, u32* maxVertices) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(bgSpecialSceneMaxObjects); i++)
    {
        if (globalCtx->sceneNum == bgSpecialSceneMaxObjects[i].sceneId)
        {
            *maxNodes = bgSpecialSceneMaxObjects[i].maxNodes;
            *maxPolygons = bgSpecialSceneMaxObjects[i].maxPolygons;
            *maxVertices = bgSpecialSceneMaxObjects[i].maxVertices;
            return true;
        }
    }
    return false;
}

#define BgCheck_Allocate BgCheck_Init
/**
 * Allocate CollisionContext
 */
void BgCheck_Allocate(CollisionContext* colCtx, GlobalContext* globalCtx, CollisionHeader* colHeader);
#ifdef NON_MATCHING
void BgCheck_Allocate(CollisionContext* colCtx, GlobalContext* globalCtx, CollisionHeader* colHeader) {
#define sceneSubdivisionList bgSpecialSceneMeshSubdivisions
    //static BgCheckSceneSubdivisionEntry sceneSubdivisionList[] = {
    //    { SCENE_HAKADAN, { 23, 7, 14 }, -1 },
    //    { SCENE_BMORI1, { 38, 1, 38 }, -1 },
    //};
    u32 tblMax;
    u32 memSize;
    u32 lookupTblMemSize;
    SSNodeList* nodeList;
    s32 useCustomSubdivisions;
    u32 customMemSize;
    s32 customNodeListMax;
    s32 i;

    customNodeListMax = -1;
    colCtx->colHeader = colHeader;
    colCtx->unk141C = 0;

    if (BgCheck_IsSpotScene(globalCtx)) {
        colCtx->memSize = 0xF000;
        colCtx->dyna.polyNodesMax = 1000;
        colCtx->dyna.polyListMax = 512;
        colCtx->dyna.vtxListMax = 512;
        colCtx->subdivAmount.x = 16;
        colCtx->subdivAmount.y = 4;
        colCtx->subdivAmount.z = 16;
    }
    else {
        if (BgCheck_TryGetCustomMemsize(globalCtx->sceneNum, &customMemSize)) {
            colCtx->memSize = customMemSize;
        }
        else {
            colCtx->memSize = 0x23000;
        }
        // /* BGCheck Normal Size %dbyte  */\n
        //osSyncPrintf("/* BGCheck ノーマルサイズ %dbyte  */\n", colCtx->memSize);
        colCtx->dyna.polyNodesMax = 1000;
        colCtx->dyna.polyListMax = 544;
        colCtx->dyna.vtxListMax = 512;
        BgCheck_GetSpecialSceneMaxObjects(globalCtx,
            &colCtx->dyna.polyNodesMax,
            &colCtx->dyna.polyListMax,
            &colCtx->dyna.vtxListMax);
        useCustomSubdivisions = false;

        for (i = 0; i < ARRAY_COUNT(sceneSubdivisionList); i++) {
            if (globalCtx->sceneNum == sceneSubdivisionList[i].sceneId) {
                colCtx->subdivAmount.x = sceneSubdivisionList[i].subdivAmount.x;
                colCtx->subdivAmount.y = sceneSubdivisionList[i].subdivAmount.y;
                colCtx->subdivAmount.z = sceneSubdivisionList[i].subdivAmount.z;
                useCustomSubdivisions = true;
                customNodeListMax = sceneSubdivisionList[i].nodeListMax;
            }
        }
        if (useCustomSubdivisions == false) {
            colCtx->subdivAmount.x = 16;
            colCtx->subdivAmount.y = 4;
            colCtx->subdivAmount.z = 16;
        }
    }
    colCtx->lookupTbl = THA_AllocEndAlign(
        &globalCtx->state.heap,
        colCtx->subdivAmount.x * sizeof(StaticLookup) * colCtx->subdivAmount.y * colCtx->subdivAmount.z, ~1);
    if (colCtx->lookupTbl == NULL) {
        LogUtils_HungupThread("../z_bgcheck.c", 3955);
    }
    colCtx->minBounds.x = colCtx->colHeader->minBounds.x;
    colCtx->minBounds.y = colCtx->colHeader->minBounds.y;
    colCtx->minBounds.z = colCtx->colHeader->minBounds.z;
    colCtx->maxBounds.x = colCtx->colHeader->maxBounds.x;
    colCtx->maxBounds.y = colCtx->colHeader->maxBounds.y;
    colCtx->maxBounds.z = colCtx->colHeader->maxBounds.z;
    BgCheck_SetSubdivisionDimension(colCtx->minBounds.x, colCtx->subdivAmount.x, &colCtx->maxBounds.x,
        &colCtx->subdivLength.x, &colCtx->subdivLengthInv.x);
    BgCheck_SetSubdivisionDimension(colCtx->minBounds.y, colCtx->subdivAmount.y, &colCtx->maxBounds.y,
        &colCtx->subdivLength.y, &colCtx->subdivLengthInv.y);
    BgCheck_SetSubdivisionDimension(colCtx->minBounds.z, colCtx->subdivAmount.z, &colCtx->maxBounds.z,
        &colCtx->subdivLength.z, &colCtx->subdivLengthInv.z);
    memSize = colCtx->subdivAmount.x * sizeof(StaticLookup) * colCtx->subdivAmount.y * colCtx->subdivAmount.z +
        colCtx->colHeader->numPolygons * sizeof(u8) + colCtx->dyna.polyNodesMax * sizeof(SSNode) +
        colCtx->dyna.polyListMax * sizeof(CollisionPoly) + colCtx->dyna.vtxListMax * sizeof(Vec3s) +
        sizeof(CollisionContext);
    if (customNodeListMax > 0) {
        // tblMax is set without checking if customNodeListMax will result in a memory overflow
        // this is a non-issue as long as sceneSubdivisionList.nodeListMax is -1
        tblMax = customNodeListMax;
    }
    else {
        if (colCtx->memSize < memSize) {
            LogUtils_HungupThread("../z_bgcheck.c", 4011);
        }
        tblMax = (colCtx->memSize - memSize) / sizeof(SSNode);
    }

    SSNodeList_Initialize(&colCtx->polyNodes);
    SSNodeList_Alloc(globalCtx, &colCtx->polyNodes, tblMax, colCtx->colHeader->numPolygons);

    lookupTblMemSize = BgCheck_InitializeStaticLookup(colCtx, globalCtx, colCtx->lookupTbl);
    //osSyncPrintf(VT_FGCOL(GREEN));
    //osSyncPrintf("/*---結局 BG使用サイズ %dbyte---*/\n", memSize + lookupTblMemSize);
    //osSyncPrintf(VT_RST);

    DynaPoly_Init(globalCtx, &colCtx->dyna);
    DynaPoly_Alloc(globalCtx, &colCtx->dyna);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_Init.s")
#endif 

void func_800C3C00(CollisionContext* colCtx, u32 param_2) {
    colCtx->unk141C |= param_2;
}

void func_800C3C14(CollisionContext* colCtx, u32 param_2) {
    colCtx->unk141C &= ~param_2;
}

#define BgCheck_GetCollisionHeader BgCheck_GetActorMeshHeader
/**
 * Get CollisionHeader
 * original name: T_BGCheck_getBGDataInfo
 */
CollisionHeader* BgCheck_GetCollisionHeader(CollisionContext* colCtx, s32 bgId) {
    if (bgId == BGCHECK_SCENE) {
        return colCtx->colHeader;
    }
    if (bgId < 0 || bgId > BG_ACTOR_MAX) {
        return NULL;
    }
    if (!(colCtx->dyna.bgActorFlags[bgId] & 1)) {
        return NULL;
    }
    return colCtx->dyna.bgActors[bgId].colHeader;
}

/**
 * Test if pos is near collision boundaries
 */
s32 BgCheck_PosInStaticBoundingBox(CollisionContext* colCtx, Vec3f* pos) {
    if (pos->x < (colCtx->minBounds.x - BGCHECK_SUBDIV_OVERLAP) ||
        (colCtx->maxBounds.x + BGCHECK_SUBDIV_OVERLAP) < pos->x ||
        pos->y < (colCtx->minBounds.y - BGCHECK_SUBDIV_OVERLAP) ||
        (colCtx->maxBounds.y + BGCHECK_SUBDIV_OVERLAP) < pos->y ||
        pos->z < (colCtx->minBounds.z - BGCHECK_SUBDIV_OVERLAP) ||
        (colCtx->maxBounds.z + BGCHECK_SUBDIV_OVERLAP) < pos->z) {
        return false;
    }
    return true;
}

#define BgCheck_RaycastFloorImpl func_800C3D50
/**
 * Raycast Toward Floor
 * returns the yIntersect of the nearest poly found directly below `pos`, or BGCHECK_Y_MIN if no floor detected
 * returns the poly found in `outPoly`, and the bgId of the entity in `outBgId`
 */
f32 BgCheck_RaycastFloorImpl(GlobalContext* globalCtx, CollisionContext* colCtx, u16 xpFlags, CollisionPoly** outPoly,
    s32* outBgId, Vec3f* pos, Actor* actor, u32 arg7, f32 chkDist, s32 arg9) {
    f32 yIntersectDyna;
    f32 yIntersect;
    StaticLookup* lookupTbl;
    Vec3f checkPos;
    StaticLookup* lookup;
    DynaRaycast dynaRaycast;

    *outBgId = BGCHECK_SCENE;
    *outPoly = NULL;
    lookupTbl = colCtx->lookupTbl;
    yIntersect = BGCHECK_Y_MIN;
    checkPos = *pos;

    while (true) {
        if (checkPos.y < colCtx->minBounds.y) {
            break;
        }
        lookup = BgCheck_GetStaticLookup(colCtx, lookupTbl, &checkPos);
        if (lookup == NULL) {
            checkPos.y -= colCtx->subdivLength.y;
            continue;
        }
        yIntersect = BgCheck_RaycastFloorStatic(lookup, colCtx, xpFlags, outPoly, pos, arg7, chkDist, BGCHECK_Y_MIN, actor);
        if (yIntersect > BGCHECK_Y_MIN) {
            break;
        }
        checkPos.y -= colCtx->subdivLength.y;
    }
    if (!(arg9 & 1)) {
        dynaRaycast.globalCtx = globalCtx;
        dynaRaycast.colCtx = colCtx;
        dynaRaycast.xpFlags = xpFlags;
        dynaRaycast.resultPoly = outPoly;
        dynaRaycast.yIntersect = yIntersect;
        dynaRaycast.pos = pos;
        dynaRaycast.bgId = outBgId;
        dynaRaycast.unk1C = 50;
        dynaRaycast.actor = actor;
        dynaRaycast.unk_20 = arg7;
        dynaRaycast.chkDist = chkDist;

        yIntersectDyna = BgCheck_RaycastFloorDyna(&dynaRaycast);
        if (yIntersect < yIntersectDyna) {
            yIntersect = yIntersectDyna;
        }
    }

    if (yIntersect != BGCHECK_Y_MIN && func_80041EC8(colCtx, *outPoly, *outBgId)) {
        yIntersect -= 1.0f;
    }
    return yIntersect;
}

#define BgCheck_CameraRaycastFloor1 func_800C3F40
/**
 * Public raycast toward floor
 * returns yIntersect of the poly found, or BGCHECK_Y_MIN if no poly detected
 */
f32 BgCheck_CameraRaycastFloor1(CollisionContext* colCtx, CollisionPoly** outPoly, Vec3f* pos) {
    s32 bgId;

    return BgCheck_RaycastFloorImpl(NULL, colCtx, COLPOLY_IGNORE_CAMERA, outPoly, &bgId, pos, NULL, 0x1C, 1.0f, 0);
}

#define BgCheck_EntityRaycastFloor1 func_800C3FA0
/**
 * Public raycast toward floor
 * returns yIntersect of the poly found, or BGCHECK_Y_MIN if no poly detected
 */
f32 BgCheck_EntityRaycastFloor1(CollisionContext* colCtx, CollisionPoly** outPoly, Vec3f* pos) {
    s32 bgId;

    return BgCheck_RaycastFloorImpl(NULL, colCtx, COLPOLY_IGNORE_ENTITY, outPoly, &bgId, pos, NULL, 0x1C, 1.0f, 0);
}

#define BgCheck_EntityRaycastFloor2 func_800C4000
/**
 * Public raycast toward floor
 * returns yIntersect of the poly found, or BGCHECK_Y_MIN if no poly detected
 */
f32 BgCheck_EntityRaycastFloor2(GlobalContext* globalCtx, CollisionContext* colCtx, CollisionPoly** outPoly,
    Vec3f* pos) {
    s32 bgId;

    return BgCheck_RaycastFloorImpl(globalCtx, colCtx, COLPOLY_IGNORE_ENTITY, outPoly, &bgId, pos, NULL, 0x1C, 1.0f, 0);
}

#define BgCheck_EntityRaycastFloor2_1 func_800C4058
/**
 * Public raycast toward floor
 * returns yIntersect of the poly found, or BGCHECK_Y_MIN if no poly detected
 */
f32 BgCheck_EntityRaycastFloor2_1(GlobalContext* globalCtx, CollisionContext* colCtx, CollisionPoly** outPoly,
    Vec3f* pos) {
    s32 bgId;

    return BgCheck_RaycastFloorImpl(globalCtx, colCtx, COLPOLY_IGNORE_ENTITY, outPoly, &bgId, pos, NULL, 0x1C, 1.0f, 1);
}

#define BgCheck_EntityRaycastFloor3 func_800C40B4
/**
 * Public raycast toward floor
 * returns yIntersect of the poly found, or BGCHECK_Y_MIN if no poly detected
 */
f32 BgCheck_EntityRaycastFloor3(CollisionContext* colCtx, CollisionPoly** outPoly, s32* bgId, Vec3f* pos) {
    return BgCheck_RaycastFloorImpl(NULL, colCtx, COLPOLY_IGNORE_ENTITY, outPoly, bgId, pos, NULL, 0x1C, 1.0f, 0);
}

#define BgCheck_EntityRaycastFloor5 func_800C411C
/**
 * Public raycast toward floor
 * returns yIntersect of the poly found, or BGCHECK_Y_MIN if no poly detected
 */
f32 BgCheck_EntityRaycastFloor5(CollisionContext* colCtx, CollisionPoly** outPoly, s32* outBgId, Actor* actor, Vec3f* pos) {
    return BgCheck_RaycastFloorImpl(NULL, colCtx, COLPOLY_IGNORE_ENTITY, outPoly, outBgId, pos, actor, 0x1C, 1.0f, 0);
}

#define BgCheck_EntityRaycastFloor5_2 func_800C4188
/**
 * Public raycast toward floor
 * returns yIntersect of the poly found, or BGCHECK_Y_MIN if no poly detected
 */
f32 BgCheck_EntityRaycastFloor5_2(GlobalContext* globalCtx, CollisionContext* colCtx, CollisionPoly** outPoly, s32* bgId,
    Actor* actor, Vec3f* pos) {
    return BgCheck_RaycastFloorImpl(globalCtx, colCtx, COLPOLY_IGNORE_ENTITY, outPoly, bgId, pos, actor, 0x1C, 1.0f, 0);
}

#define BgCheck_EntityRaycastFloor5_3 func_800C41E4
/**
 * Public raycast toward floor
 * returns yIntersect of the poly found, or BGCHECK_Y_MIN if no poly detected
 */
f32 BgCheck_EntityRaycastFloor5_3(GlobalContext* globalCtx, CollisionContext* colCtx, CollisionPoly** outPoly, s32* bgId,
    Actor* actor, Vec3f* pos) {
    return BgCheck_RaycastFloorImpl(globalCtx, colCtx, COLPOLY_IGNORE_ENTITY, outPoly, bgId, pos, actor, 0x3C, 1.0f, 0);
}

#define BgCheck_EntityRaycastFloor6 func_800C4240
/**
 * Public raycast toward floor
 * returns yIntersect of the poly found, or BGCHECK_Y_MIN if no poly detected
 */
f32 BgCheck_EntityRaycastFloor6(CollisionContext* colCtx, CollisionPoly** outPoly, s32* bgId, Actor* actor, Vec3f* pos,
    f32 chkDist) {
    return BgCheck_RaycastFloorImpl(NULL, colCtx, COLPOLY_IGNORE_ENTITY, outPoly, bgId, pos, actor, 0x1C, chkDist, 0);
}

#define BgCheck_EntityRaycastFloor7 func_800C42A8
/**
 * Public raycast toward floor
 * returns yIntersect of the poly found, or BGCHECK_Y_MIN if no poly detected
 */
f32 BgCheck_EntityRaycastFloor7(CollisionContext* colCtx, CollisionPoly** outPoly, s32* bgId, Actor* actor,
    Vec3f* pos) {
    return BgCheck_RaycastFloorImpl(NULL, colCtx, COLPOLY_IGNORE_ENTITY, outPoly, bgId, pos, actor, 0x06, 1.0f, 0);
}

#define BgCheck_AnyRaycastFloor1 func_800C4314
/**
 * Public raycast toward floor
 * returns yIntersect of the poly found, or BGCHECK_Y_MIN if no poly detected
 */
f32 BgCheck_AnyRaycastFloor1(CollisionContext* colCtx, CollisionPoly* outPoly, Vec3f* pos) {
    CollisionPoly* tempPoly;
    f32 result;
    s32 bgId;

    result = BgCheck_RaycastFloorImpl(NULL, colCtx, COLPOLY_IGNORE_NONE, &tempPoly, &bgId, pos, NULL, 0x1C, 1.0f, 0);

    if (tempPoly != NULL) {
        *outPoly = *tempPoly;
    }
    return result;
}

#define BgCheck_AnyRaycastFloor2 func_800C43CC
/**
 * Public raycast toward floor
 * returns yIntersect of the poly found, or BGCHECK_Y_MIN if no poly detected
 */
f32 BgCheck_AnyRaycastFloor2(CollisionContext* colCtx, CollisionPoly* outPoly, s32* bgId, Vec3f* pos) {
    CollisionPoly* tempPoly;
    f32 result = BgCheck_RaycastFloorImpl(NULL, colCtx, COLPOLY_IGNORE_NONE, &tempPoly, bgId, pos, NULL, 0x1C, 1.0f, 0);

    if (tempPoly != NULL) {
        *outPoly = *tempPoly;
    }
    return result;
}

#define BgCheck_CameraRaycastFloor2 func_800C4488
/**
 * Public raycast toward floor
 * returns yIntersect of the poly found, or BGCHECK_Y_MIN if no poly detected
 */
f32 BgCheck_CameraRaycastFloor2(CollisionContext* colCtx, CollisionPoly** outPoly, s32* bgId, Vec3f* pos) {
    return BgCheck_RaycastFloorImpl(NULL, colCtx, COLPOLY_IGNORE_CAMERA, outPoly, bgId, pos, NULL, 0x06, 1.0f, 0);
}

#define BgCheck_EntityRaycastFloor8 func_800C44F0
/**
 * Public raycast toward floor
 * returns yIntersect of the poly found, or BGCHECK_Y_MIN if no poly detected
 */
f32 BgCheck_EntityRaycastFloor8(CollisionContext* colCtx, CollisionPoly** outPoly, s32* bgId, Actor* actor,
    Vec3f* pos) {
    return BgCheck_RaycastFloorImpl(NULL, colCtx, COLPOLY_IGNORE_ENTITY, outPoly, bgId, pos, actor, 0x02, 1.0f, 0);
}

#define BgCheck_EntityRaycastFloor9 func_800C455C
/**
 * Public raycast toward floor
 * returns yIntersect of the poly found, or BGCHECK_Y_MIN if no poly detected
 */
f32 BgCheck_EntityRaycastFloor9(CollisionContext* colCtx, CollisionPoly** outPoly, s32* bgId, Vec3f* pos) {
    return BgCheck_RaycastFloorImpl(NULL, colCtx, COLPOLY_IGNORE_ENTITY, outPoly, bgId, pos, NULL, 0x06, 1.0f, 0);
}

#define BgCheck_CheckWallImpl func_800C45C4
s32 BgCheck_CheckWallImpl(CollisionContext* colCtx, u16 xpFlags, Vec3f* posResult, Vec3f* posNext, Vec3f* posPrev,
    f32 radius, CollisionPoly** outPoly, s32* outBgId, Actor* actor, f32 checkHeight, u8 argA);
#ifdef NON_MATCHING
/**
 * Tests if moving from `posPrev` to `posNext` will collide with a "wall"
 * `radius` is used to form a sphere for collision detection purposes
 * `checkHeight` is the positive height above posNext to perform certain checks
 * returns true if a collision is detected, else false
 * `outPoly` returns the closest poly detected, while `outBgId` returns the poly owner
 */
s32 BgCheck_CheckWallImpl(CollisionContext* colCtx, u16 xpFlags, Vec3f* posResult, Vec3f* posNext, Vec3f* posPrev,
    f32 radius, CollisionPoly** outPoly, s32* outBgId, Actor* actor, f32 checkHeight, u8 argA) {
    StaticLookup* lookupTbl;
    f32 temp_f0;
    s32 result;
    CollisionPoly* poly;
    f32 dx, dy, dz; // change between posPrev to posNext
    Vec3f sphCenter;
    s32 dynaPolyCollision;
    Vec3f posIntersect;
    s32 bgId;
    f32 temp_f0_2;
    f32 f32temp;
    f32 nx2, nz2;
    Vec3f checkLineNext;
    Vec3f checkLinePrev;
    f32 n2XZDist;
    f32 n3XZDist;
    f32 nx3, nz3;
    s32 bccFlags;
    Vec3f posIntersect2;
    s32 bgId2;
    f32 nx, ny, nz; // unit normal of polygon

    result = false;
    *outBgId = BGCHECK_SCENE;
    *outPoly = NULL;
    lookupTbl = colCtx->lookupTbl;
    *posResult = *posNext;
    dx = posNext->x - posPrev->x;
    dy = posNext->y - posPrev->y;
    dz = posNext->z - posPrev->z;

    // if there's movement on the xz plane, and argA flag is 0,
    if ((dx != 0.0f || dz != 0.0f) && (argA & 1) == 0) {
        if ((checkHeight + dy) < 5.0f) {
            //! @bug checkHeight is not applied to posPrev/posNext
            result = BgCheck_CheckLineImpl(colCtx, xpFlags, COLPOLY_IGNORE_NONE, posPrev, posNext, &posIntersect, &poly,
                &bgId, actor, 1.0f, BGCHECK_CHECK_ALL & ~BGCHECK_CHECK_CEILING);
            if (result) {
                ny = COLPOLY_GET_NORMAL(poly->normal.y);
                // if poly is floor, push result underneath the floor
                if (ny > 0.5f) {
                    posResult->x = posIntersect.x;
                    if (checkHeight > 1.0f) {
                        posResult->y = posIntersect.y - 1.0f;
                    }
                    else {
                        posResult->y = posIntersect.y - checkHeight;
                    }
                    posResult->z = posIntersect.z;
                    if (actor != NULL)
                    {
                        actor->bgCheckFlags |= 0x1000;
                    }
                }
                // poly is wall
                else {
                    nx = COLPOLY_GET_NORMAL(poly->normal.x);
                    nz = COLPOLY_GET_NORMAL(poly->normal.z);
                    posResult->x = radius * nx + posIntersect.x;
                    posResult->y = radius * ny + posIntersect.y;
                    posResult->z = radius * nz + posIntersect.z;
                }
                *outPoly = poly;
                *outBgId = bgId;
            }
        }
        else {
            // if the radius is less than the distance travelled on the xz plane, also test for floor collisions
            bccFlags = SQ(radius) < (SQ(dx) + SQ(dz))
                ? (BGCHECK_CHECK_ALL & ~BGCHECK_CHECK_CEILING)
                : (BGCHECK_CHECK_ALL & ~BGCHECK_CHECK_FLOOR & ~BGCHECK_CHECK_CEILING);

            // perform a straight line test to see if a line at posNext.y + checkHeight from posPrev.xz to posNext.xz
            // passes through any wall and possibly floor polys
            checkLineNext = *posNext;
            checkLineNext.y += checkHeight;
            checkLinePrev = *posPrev;
            checkLinePrev.y = checkLineNext.y;
            result = BgCheck_CheckLineImpl(colCtx, xpFlags, COLPOLY_IGNORE_NONE, &checkLinePrev, &checkLineNext,
                &posIntersect, &poly, &bgId, actor, 1.0f, bccFlags);

            if (result) {
                nx2 = COLPOLY_GET_NORMAL(poly->normal.x);
                nz2 = COLPOLY_GET_NORMAL(poly->normal.z);
                n2XZDist = sqrtf(SQ(nx2) + SQ(nz2));

                // if poly is not a "flat" floor or "flat" ceiling
                if (!IS_ZERO(n2XZDist)) {
                    // normalize nx,nz and multiply each by the radius to go back to the other side of the wall
                    f32temp = 1.0f / n2XZDist;
                    temp_f0 = radius * f32temp;
                    posResult->x = temp_f0 * nx2 + posIntersect.x;
                    posResult->z = temp_f0 * nz2 + posIntersect.z;
                    *outPoly = poly;
                    *outBgId = bgId;
                    result = true;
                    if (COLPOLY_GET_NORMAL(poly->normal.y) > 0.5f) {
                        if (actor != NULL) {
                            actor->bgCheckFlags |= 0x1000;
                        }
                    }
                }
                else
                {
                    result = false;
                }
            }
        }
    }

    sphCenter = *posResult;
    dynaPolyCollision = false;
    sphCenter.y += checkHeight;
    // test if sphere (sphCenter, radius) collides with a dynamic wall, displacing the x/z coordinates
    if (BgCheck_SphVsDynaWall(colCtx, xpFlags, &posResult->x, &posResult->z, &sphCenter, radius, outPoly, outBgId,
        actor)) {
        result = true;
        dynaPolyCollision = true;
        sphCenter = *posResult;
        sphCenter.y += checkHeight;
    }
    // test if sphere (sphCenter, radius) collides with a static wall, displacing the x/z coordinates
    if (BgCheck_PosInStaticBoundingBox(colCtx, posNext) &&
        // possible bug? if the sphere's radius is smaller than the distance to a subdivision boundary, some static
        // polys will be missed
        BgCheck_SphVsStaticWall(BgCheck_GetNearestStaticLookup(colCtx, lookupTbl, posResult), colCtx, xpFlags,
            &posResult->x, &posResult->z, &sphCenter, radius, outPoly, actor)) {
        *outBgId = BGCHECK_SCENE;
        result = true;
    }
    // if a collision with a dyna poly was detected
    if (dynaPolyCollision || *outBgId != BGCHECK_SCENE) {
        if (BgCheck_CheckLineImpl(colCtx, xpFlags, COLPOLY_IGNORE_NONE, posPrev, posResult, &posIntersect2, &poly,
            &bgId2, actor, 1.0f, BGCHECK_CHECK_ONE_FACE | BGCHECK_CHECK_WALL)) {
            nx3 = COLPOLY_GET_NORMAL(poly->normal.x);
            nz3 = COLPOLY_GET_NORMAL(poly->normal.z);
            n3XZDist = sqrtf(SQ(nx3) + SQ(nz3));

            // if poly is not a "flat" floor or "flat" ceiling
            if (!IS_ZERO(n3XZDist)) {
                // normalize nx,nz and multiply each by the radius to go back to the other side of the wall
                f32temp = 1.0f / n3XZDist;
                temp_f0_2 = radius * f32temp;
                posResult->x = temp_f0_2 * nx3 + posIntersect2.x;
                posResult->z = temp_f0_2 * nz3 + posIntersect2.z;
                *outPoly = poly;
                *outBgId = bgId2;
                result = true;
            }
        }
    }
    return result;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C45C4.s")
#endif 

#define BgCheck_EntitySphVsWall1 func_800C4C74
/**
 * Public. Tests if moving from `posPrev` to `posNext` will collide with a "wall"
 * `radius` is used to form a sphere for collision detection purposes
 * `checkHeight` is the positive height above posNext to perform certain checks
 * returns true if a collision is detected, else false
 * `outPoly` returns the closest poly detected
 */
s32 BgCheck_EntitySphVsWall1(CollisionContext* colCtx, Vec3f* posResult, Vec3f* posNext, Vec3f* posPrev, f32 radius,
    CollisionPoly** outPoly, f32 checkHeight) {
    s32 bgId;

    return BgCheck_CheckWallImpl(colCtx, COLPOLY_IGNORE_ENTITY, posResult, posNext, posPrev, radius, outPoly, &bgId,
        NULL, checkHeight, 0);
}

#define BgCheck_EntitySphVsWall2 func_800C4CD8
/**
 * Public. Tests if moving from `posPrev` to `posNext` will collide with a "wall"
 * `radius` is used to form a sphere for collision detection purposes
 * `checkHeight` is the positive height above posNext to perform certain checks
 * returns true if a collision is detected, else false
 * `outPoly` returns the closest poly detected, while `outBgId` returns the poly owner
 */
s32 BgCheck_EntitySphVsWall2(CollisionContext* colCtx, Vec3f* posResult, Vec3f* posNext, Vec3f* posPrev, f32 radius,
    CollisionPoly** outPoly, s32* outBgId, f32 checkHeight) {
    return BgCheck_CheckWallImpl(colCtx, COLPOLY_IGNORE_ENTITY, posResult, posNext, posPrev, radius, outPoly, outBgId,
        NULL, checkHeight, 0);
}

#define BgCheck_EntitySphVsWall3 func_800C4D3C
/**
 * Public. Tests if *moving from `posPrev` to `posNext` will collide with a "wall"
 * `radius` is used to form a sphere for collision detection purposes
 * `checkHeight` is the positive height above posNext to perform certain checks
 * `actor` is the actor performing the check, allowing it to be skipped
 * returns true if a collision is detected, else false
 * `outPoly` returns the closest poly detected, while `outBgId` returns the poly owner
 */
s32 BgCheck_EntitySphVsWall3(CollisionContext* colCtx, Vec3f* posResult, Vec3f* posNext, Vec3f* posPrev, f32 radius,
    CollisionPoly** outPoly, s32* outBgId, Actor* actor, f32 checkHeight) {
    return BgCheck_CheckWallImpl(colCtx, COLPOLY_IGNORE_ENTITY, posResult, posNext, posPrev, radius, outPoly, outBgId,
        actor, checkHeight, 0);
}

#define BgCheck_EntitySphVsWall4 func_800C4DA4
/**
 * Public. Tests if moving from `posPrev` to `posNext` will collide with a "wall"
 * Skips a check that occurs only when moving on the xz plane
 * `radius` is used to form a sphere for collision detection purposes
 * `checkHeight` is the positive height above posNext to perform certain checks
 * `actor` is the actor performing the check, allowing it to be skipped
 * returns true if a collision is detected, else false
 * `outPoly` returns the closest poly detected, while `outBgId` returns the poly owner
 */
s32 BgCheck_EntitySphVsWall4(CollisionContext* colCtx, Vec3f* posResult, Vec3f* posNext, Vec3f* posPrev, f32 radius,
    CollisionPoly** outPoly, s32* outBgId, Actor* actor, f32 checkHeight) {
    return BgCheck_CheckWallImpl(colCtx, COLPOLY_IGNORE_ENTITY, posResult, posNext, posPrev, radius, outPoly, outBgId,
        actor, checkHeight, 1);
}

#define BgCheck_CheckCeilingImpl func_800C4E10
/**
 * Tests for collision with a ceiling poly
 * `checkHeight` should be a positive value
 * returns true if a collision occurs, else false
 * `outPoly` returns the poly collided with, while `outBgId` returns the owner of the poly
 * `outY` returns the y coordinate of pos needed to not collide with `outPoly`
 */
s32 BgCheck_CheckCeilingImpl(CollisionContext* colCtx, u16 xpFlags, f32* outY, Vec3f* pos, f32 checkHeight,
    CollisionPoly** outPoly, s32* outBgId, Actor* actor) {
    StaticLookup* lookupTbl;
    StaticLookup* lookup;
    s32 result;
    Vec3f posTemp;
    f32 tempY;

    *outBgId = BGCHECK_SCENE;
    *outY = pos->y;
    lookupTbl = colCtx->lookupTbl;
    if (!BgCheck_PosInStaticBoundingBox(colCtx, pos)) {
        return false;
    }

    lookup = BgCheck_GetNearestStaticLookup(colCtx, lookupTbl, pos);
    result = BgCheck_CheckStaticCeiling(lookup, xpFlags, colCtx, outY, pos, checkHeight, outPoly, actor);

    posTemp = *pos;
    posTemp.y = *outY;
    tempY = *outY;

    if (BgCheck_CheckDynaCeiling(colCtx, xpFlags, &tempY, &posTemp, checkHeight, outPoly, outBgId, actor)) {
        *outY = tempY;
        result = true;
    }
    return result;
}

#define BgCheck_AnyCheckCeiling func_800C4F38
/**
 * Tests for collision with any ceiling poly
 * `checkHeight` must be a positive value
 * returns true if a collision occurs, else false
 * `outY` returns the displaced y coordinate needed to not collide with the poly
 */
s32 BgCheck_AnyCheckCeiling(CollisionContext* colCtx, f32* outY, Vec3f* pos, f32 checkHeight) {
    CollisionPoly* poly;
    s32 bgId;

    return BgCheck_CheckCeilingImpl(colCtx, COLPOLY_IGNORE_NONE, outY, pos, checkHeight, &poly, &bgId, NULL);
}

#define BgCheck_EntityCheckCeiling func_800C4F84
/**
 * Tests for collision with any entity solid ceiling poly
 * `checkHeight` must be a positive value
 * returns true if a collision occurs, else false
 * `outY` returns the displaced y coordinate needed to not collide with the poly
 */
s32 BgCheck_EntityCheckCeiling(CollisionContext* colCtx, f32* outY, Vec3f* pos, f32 checkHeight,
    CollisionPoly** outPoly, s32* outBgId, Actor* actor) {
    return BgCheck_CheckCeilingImpl(colCtx, COLPOLY_IGNORE_ENTITY, outY, pos, checkHeight, outPoly, outBgId, actor);
}

#ifdef NON_MATCHING
/**
 * Tests if a line from `posA` to `posB` intersects with a poly
 * returns true if it does, else false
 * `posB`? `posResult` returns the point of intersection
 * `outPoly` returns the pointer to the intersected poly, while `outBgId` returns the entity the poly belongs to
 */
s32 BgCheck_CheckLineImpl(CollisionContext* colCtx, u16 xpFlags1, u16 xpFlags2, Vec3f* posA, Vec3f* posB,
    Vec3f* posResult, CollisionPoly** outPoly, s32* outBgId, Actor* actor, f32 chkDist,
    u32 bccFlags) {
    StaticLookup* lookupTbl;
    StaticLookup* iLookup;
    s32 subdivMin[3];
    s32 subdivMax[3];
    s32 i;
    s32 result;
    //f32 distSq;
    Vec3f posBTemp;
    struct_func_800C1D7C bup;
    Vec3f sectorMin;
    Vec3f sectorMax;
    s32 k;
    StaticLookup* lookup;
    s32 j;
    StaticLookup* jLookup;
    s32 temp_lo;
    s32 pad[2];

    lookupTbl = colCtx->lookupTbl;
    posBTemp = *posB;

    *outBgId = BGCHECK_SCENE;

    BgCheck_ResetPolyCheckTbl(&colCtx->polyNodes, colCtx->colHeader->numPolygons);
    BgCheck_GetStaticLookupIndicesFromPos(colCtx, posA, &subdivMin);
    BgCheck_GetStaticLookupIndicesFromPos(colCtx, &posBTemp, &subdivMax);
    *posResult = *posB;
    bup.outDistSq = 1.0e38f;
    *outPoly = NULL;
    bup.colCtx = colCtx;
    bup.xpFlags2 = xpFlags2;
    bup.posA = posA;
    bup.posB = &posBTemp;
    bup.outPoly = *outPoly;
    bup.xpFlags1 = xpFlags1;
    bup.outPos = posResult;
    bup.chkDist = chkDist;
    bup.bccFlags = bccFlags;
    bup.actor = actor;
    result = false;

    if (subdivMin[0] != subdivMax[0] || subdivMin[1] != subdivMax[1] || subdivMin[2] != subdivMax[2]) {
        for (i = 0; i < 3; i++) {
            if (subdivMax[i] < subdivMin[i]) {
                j = subdivMax[i];
                subdivMax[i] = subdivMin[i];
                subdivMin[i] = j;
            }
        }
        temp_lo = colCtx->subdivAmount.x * colCtx->subdivAmount.y;
        iLookup = lookupTbl + subdivMin[2] * temp_lo;
        sectorMin.z = subdivMin[2] * colCtx->subdivLength.z + colCtx->minBounds.z;
        sectorMax.z = colCtx->subdivLength.z + sectorMin.z;

        for (i = subdivMin[2]; i < subdivMax[2] + 1; i++) {
            jLookup = iLookup + subdivMin[1] * colCtx->subdivAmount.x;
            sectorMin.y = subdivMin[1] * colCtx->subdivLength.y + colCtx->minBounds.y;
            sectorMax.y = colCtx->subdivLength.y + sectorMin.y;

            for (j = subdivMin[1]; j < subdivMax[1] + 1; j++) {
                lookup = jLookup + subdivMin[0];
                sectorMin.x = subdivMin[0] * colCtx->subdivLength.x + colCtx->minBounds.x;
                sectorMax.x = colCtx->subdivLength.x + sectorMin.x;

                for (k = subdivMin[0]; k < subdivMax[0] + 1; k++) {

                    if (Math3D_LineVsCube(&sectorMin, &sectorMax, posA, &posBTemp))
                    {
                        bup.lookup = lookup;

                        if (BgCheck_CheckLineInSubdivision(&bup)) {
                            result = true;
                        }
                    }

                    lookup++;
                    sectorMin.x += colCtx->subdivLength.x;
                    sectorMax.x += colCtx->subdivLength.x;
                }

                jLookup += colCtx->subdivAmount.x;
                sectorMin.y += colCtx->subdivLength.y;
                sectorMax.y += colCtx->subdivLength.y;
            }

            iLookup += temp_lo;
            sectorMin.z += colCtx->subdivLength.z;
            sectorMax.z += colCtx->subdivLength.z;
        }
    }
    else if (BgCheck_PosInStaticBoundingBox(colCtx, posA) == false) {
        return false;
    }
    else {
        bup.lookup = BgCheck_GetNearestStaticLookup(colCtx, lookupTbl, posA);
        result =
            BgCheck_CheckLineInSubdivision(&bup);
        if (result) {
            bup.outDistSq = Math3D_Vec3fDistSq(posResult, posA);
        }
    }
    if ((bccFlags & BGCHECK_CHECK_DYNA) &&
        BgCheck_CheckLineAgainstDyna(colCtx, xpFlags1, posA, &posBTemp, posResult, outPoly, &bup.outDistSq, outBgId, actor,
            chkDist, bccFlags)) {
        result = true;
    }
    return result;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C4FD4.s")
#endif

#define BgCheck_GetBccFlags func_800C5464
/**
 * Get bccFlags
 */
u32 BgCheck_GetBccFlags(s32 chkWall, s32 chkFloor, s32 chkCeil, s32 chkOneFace, s32 chkDyna) {
    u32 result = 0;

    if (chkWall) {
        result = BGCHECK_CHECK_WALL;
    }
    if (chkFloor) {
        result |= BGCHECK_CHECK_FLOOR;
    }
    if (chkCeil) {
        result |= BGCHECK_CHECK_CEILING;
    }
    if (chkOneFace) {
        result |= BGCHECK_CHECK_ONE_FACE;
    }
    if (chkDyna) {
        result |= BGCHECK_CHECK_DYNA;
    }
    return result;
}

#define BgCheck_CameraLineTest1 func_800C54AC
/**
 * Public. Tests if a line from `posA` to `posB` intersects with a poly
 * returns true if it does, else false
 */
s32 BgCheck_CameraLineTest1(CollisionContext* colCtx, Vec3f* posA, Vec3f* posB, Vec3f* posResult,
    CollisionPoly** outPoly, s32 chkWall, s32 chkFloor, s32 chkCeil, s32 chkOneFace,
    s32* bgId) {
    return BgCheck_CheckLineImpl(colCtx, COLPOLY_IGNORE_CAMERA, COLPOLY_IGNORE_NONE, posA, posB, posResult, outPoly,
        bgId, NULL, 1.0f, BgCheck_GetBccFlags(chkWall, chkFloor, chkCeil, chkOneFace, true));
}

#define BgCheck_CameraLineTest2 func_800C5538
/**
 * Public. Tests if a line from `posA` to `posB` intersects with a poly
 * returns true if it does, else false
 */
s32 BgCheck_CameraLineTest2(CollisionContext* colCtx, Vec3f* posA, Vec3f* posB, Vec3f* posResult,
    CollisionPoly** outPoly, s32 chkWall, s32 chkFloor, s32 chkCeil, s32 chkOneFace,
    s32* bgId) {
    return BgCheck_CheckLineImpl(colCtx, COLPOLY_IGNORE_NONE, COLPOLY_IGNORE_CAMERA, posA, posB, posResult, outPoly,
        bgId, NULL, 1.0f, BgCheck_GetBccFlags(chkWall, chkFloor, chkCeil, chkOneFace, true));
}

#define BgCheck_EntityLineTest1 func_800C55C4
/**
 * Public. Tests if a line from `posA` to `posB` intersects with a poly
 * returns true if it does, else false
 */
s32 BgCheck_EntityLineTest1(CollisionContext* colCtx, Vec3f* posA, Vec3f* posB, Vec3f* posResult,
    CollisionPoly** outPoly, s32 chkWall, s32 chkFloor, s32 chkCeil, s32 chkOneFace,
    s32* bgId) {
    return BgCheck_CheckLineImpl(colCtx, COLPOLY_IGNORE_ENTITY, COLPOLY_IGNORE_NONE, posA, posB, posResult, outPoly,
        bgId, NULL, 1.0f, BgCheck_GetBccFlags(chkWall, chkFloor, chkCeil, chkOneFace, true));
}

#define BgCheck_EntityLineTest2 func_800C5650
/**
 * Public. Tests if a line from `posA` to `posB` intersects with a poly
 * returns true if it does, else false
 */
s32 BgCheck_EntityLineTest2(CollisionContext* colCtx, Vec3f* posA, Vec3f* posB, Vec3f* posResult,
    CollisionPoly** outPoly, s32 chkWall, s32 chkFloor, s32 chkCeil, s32 chkOneFace, s32* bgId,
    Actor* actor) {
    return BgCheck_CheckLineImpl(colCtx, COLPOLY_IGNORE_ENTITY, COLPOLY_IGNORE_NONE, posA, posB, posResult, outPoly,
        bgId, actor, 1.0f, BgCheck_GetBccFlags(chkWall, chkFloor, chkCeil, chkOneFace, true));
}

#define BgCheck_EntityLineTest3 func_800C56E0
/**
 * Public. Tests if a line from `posA` to `posB` intersects with a poly
 * returns true if it does, else false
 */
s32 BgCheck_EntityLineTest3(CollisionContext* colCtx, Vec3f* posA, Vec3f* posB, Vec3f* posResult,
    CollisionPoly** outPoly, s32 chkWall, s32 chkFloor, s32 chkCeil, s32 chkOneFace, s32* bgId,
    Actor* actor, f32 chkDist) {
    return BgCheck_CheckLineImpl(colCtx, COLPOLY_IGNORE_ENTITY, COLPOLY_IGNORE_NONE, posA, posB, posResult, outPoly,
        bgId, actor, chkDist,
        BgCheck_GetBccFlags(chkWall, chkFloor, chkCeil, chkOneFace, true));
}

#define BgCheck_ProjectileLineTest func_800C576C
/**
 * Public. Tests if a line from `posA` to `posB` intersects with a poly
 * returns true if it does, else false
 */
s32 BgCheck_ProjectileLineTest(CollisionContext* colCtx, Vec3f* posA, Vec3f* posB, Vec3f* posResult,
    CollisionPoly** outPoly, s32 chkWall, s32 chkFloor, s32 chkCeil, s32 chkOneFace,
    s32* bgId) {
    return BgCheck_CheckLineImpl(colCtx, COLPOLY_IGNORE_PROJECTILES, COLPOLY_IGNORE_NONE, posA, posB, posResult,
        outPoly, bgId, NULL, 1.0f,
        BgCheck_GetBccFlags(chkWall, chkFloor, chkCeil, chkOneFace, true));
}

#define BgCheck_AnyLineTest1 func_800C57F8
/**
 * Public. Tests if a line from `posA` to `posB` intersects with a poly
 * returns true if it does, else false
 */
s32 BgCheck_AnyLineTest1(CollisionContext* colCtx, Vec3f* posA, Vec3f* posB, Vec3f* posResult, CollisionPoly** outPoly,
    s32 chkOneFace) {
    return BgCheck_AnyLineTest2(colCtx, posA, posB, posResult, outPoly, true, true, true, chkOneFace);
}

/**
 * Public. Tests if a line from `posA` to `posB` intersects with a poly
 * returns true if it does, else false
 */
s32 BgCheck_AnyLineTest2(CollisionContext* colCtx, Vec3f* posA, Vec3f* posB, Vec3f* posResult, CollisionPoly** outPoly,
    s32 chkWall, s32 chkFloor, s32 chkCeil, s32 chkOneFace) {
    s32 bgId;

    return BgCheck_CheckLineImpl(colCtx, COLPOLY_IGNORE_NONE, COLPOLY_IGNORE_NONE, posA, posB, posResult, outPoly,
        &bgId, NULL, 1.0f, BgCheck_GetBccFlags(chkWall, chkFloor, chkCeil, chkOneFace, true));
}

#define BgCheck_AnyLineTest3 func_800C58C8
/**
 * Public. Tests if a line from `posA` to `posB` intersects with a poly
 * returns true if it does, else false
 */
s32 BgCheck_AnyLineTest3(CollisionContext* colCtx, Vec3f* posA, Vec3f* posB, Vec3f* posResult, CollisionPoly** outPoly,
    s32 chkWall, s32 chkFloor, s32 chkCeil, s32 chkOneFace, s32* bgId) {
    return BgCheck_CheckLineImpl(colCtx, COLPOLY_IGNORE_NONE, COLPOLY_IGNORE_NONE, posA, posB, posResult, outPoly, bgId,
        NULL, 1.0f, BgCheck_GetBccFlags(chkWall, chkFloor, chkCeil, chkOneFace, true));
}

#define BgCheck_SphVsFirstPolyImpl func_800C5954
/**
 * Get first poly intersecting sphere `center` `radius`
 * ignores `actor` dyna poly
 * returns true if any poly intersects the sphere, else false
 * `outPoly` returns the pointer of the first poly found that intersects
 * `outBgId` returns the bgId of the entity that owns `outPoly`
 */
s32 BgCheck_SphVsFirstPolyImpl(CollisionContext* colCtx, u16 xpFlags, CollisionPoly** outPoly, s32* outBgId,
    Vec3f* center, f32 radius, Actor* actor, u16 bciFlags) {
    StaticLookup* lookup;

    *outBgId = BGCHECK_SCENE;
    lookup = BgCheck_GetStaticLookup(colCtx, colCtx->lookupTbl, center);
    if (lookup == NULL) {
        return false;
    }
    else if (BgCheck_SphVsFirstStaticPoly(lookup, xpFlags, colCtx, center, radius, outPoly, bciFlags, actor) ||
        BgCheck_SphVsFirstDynaPoly(colCtx, xpFlags, outPoly, outBgId, center, radius, actor, bciFlags)) {
        return true;
    }
    return false;
}

#define BgCheck_SphVsFirstPoly func_800C5A20
/**
 * Public get first poly intersecting sphere `center` `radius`
 */
s32 BgCheck_SphVsFirstPoly(CollisionContext* colCtx, Vec3f* center, f32 radius) {
    CollisionPoly* poly;
    s32 bgId;

    return BgCheck_SphVsFirstPolyImpl(colCtx, COLPOLY_IGNORE_NONE, &poly, &bgId, center, radius, NULL,
        BGCHECK_IGNORE_NONE);
}

#define BgCheck_SphVsFirstWall func_800C5A64
/**
 * Public get first wall poly intersecting sphere `center` `radius`
 */
s32 BgCheck_SphVsFirstWall(CollisionContext* colCtx, Vec3f* center, f32 radius) {
    CollisionPoly* poly;
    s32 bgId;

    return BgCheck_SphVsFirstPolyImpl(colCtx, COLPOLY_IGNORE_NONE, &poly, &bgId, center, radius, NULL,
        BGCHECK_IGNORE_FLOOR | BGCHECK_IGNORE_CEILING);
}

/**
 * Init SSNodeList
 */
void SSNodeList_Initialize(SSNodeList* this) {
    this->max = 0;
    this->count = 0;
    this->tbl = NULL;
    this->polyCheckTbl = NULL;
}

/**
 * Allocate SSNodeList
 * tblMax is the number of SSNode records to allocate
 * numPolys is the number of polygons defined within the CollisionHeader
 */
void SSNodeList_Alloc(GlobalContext* globalCtx, SSNodeList* this, s32 tblMax, s32 numPolys) {
    this->max = tblMax;
    this->count = 0;
    this->tbl = THA_AllocEndAlign(&globalCtx->state.heap, tblMax * sizeof(SSNode), -2);
    this->polyCheckTbl = THA_AllocEndAlign16(&globalCtx->state.heap, numPolys * sizeof(u8));

    if (this->polyCheckTbl == NULL) {
        sprintf(D_801ED950, "this->polygon_check == NULL(game_alloc() MemoryAllocationError.)\n");
        sprintf(D_801ED9A0, "short_slist_node_size = %d/polygon_num = %d\n", tblMax, numPolys);
        Fault_AddHungupAndCrashImpl(D_801ED950, D_801ED9A0);
    }
}

#define SSNodeList_GetNextNode func_800C5B80
/**
 * Get next SSNodeList SSNode
 */
SSNode* SSNodeList_GetNextNode(SSNodeList* this) {
    SSNode* result = &this->tbl[this->count];

    this->count++;
    if (!(this->count < this->max)) {
        return NULL;
    }
    return result;
}

#define SSNodeList_GetNextNodeIdx BgCheck_ScenePolygonListsReserveNode
/**
 * Get next SSNodeList SSNode index
 */
u16 SSNodeList_GetNextNodeIdx(SSNodeList* this) {
    u16 new_index = this->count++;

    return new_index;
}

#define ScaleRotPos_Initialize BgCheck_ActorMeshParamsInit
/**
 * Initialize ScaleRotPos
 */
void ScaleRotPos_Initialize(ScaleRotPos* srp) {
    srp->scale.x = srp->scale.y = srp->scale.z = 1;
    srp->rot.x = 0;
    srp->rot.y = 0;
    srp->rot.z = 0;
    srp->pos.x = srp->pos.y = srp->pos.z = 0;
}

#define ScaleRotPos_SetValue BgCheck_SetActorMeshParams
/**
 * Set ScaleRotPos
 */
void ScaleRotPos_SetValue(ScaleRotPos* srp, Vec3f* scale, Vec3s* rot, Vec3f* pos) {
    srp->scale = *scale;
    srp->rot = *rot;
    srp->pos = *pos;
}

#define ScaleRotPos_Equals BgCheck_AreActorMeshParamsEqual
/**
 * ScaleRotPos equality test
 */
s32 ScaleRotPos_Equals(ScaleRotPos* a, ScaleRotPos* b) {
    if (a->scale.x != b->scale.x || a->scale.y != b->scale.y || a->scale.z != b->scale.z || a->rot.x != b->rot.x ||
        a->rot.y != b->rot.y || a->rot.z != b->rot.z || a->pos.x != b->pos.x || a->pos.y != b->pos.y ||
        a->pos.z != b->pos.z) {
        return false;
    }
    return true;
}

#define DynaLookup_ResetLists BgCheck_ActorMeshPolyListsHeadsInit
/**
 * Reset DynaLookup lists
 */
void DynaLookup_ResetLists(DynaLookup* dynaLookup) {
    SSList_SetNull(&dynaLookup->ceiling);
    SSList_SetNull(&dynaLookup->wall);
    SSList_SetNull(&dynaLookup->floor);
}

#define DynaLookup_Reset BgCheck_ActorMeshPolyListsInit
/**
 * Reset DynaLookup
 */
void DynaLookup_Reset(DynaLookup* dynaLookup) {
    dynaLookup->polyStartIndex = 0;
    DynaLookup_ResetLists(dynaLookup);
}

#define DynaLookup_ResetVtxStartIndex BgCheck_ActorMeshVerticesIndexInit
/**
 * Reset vtxStartIndex
 */
void DynaLookup_ResetVtxStartIndex(u16* vtxStartIndex) {
    *vtxStartIndex = 0;
}

#define DynaLookup_ResetWaterBoxStartIndex BgCheck_ActorMeshWaterboxesIndexInit
/**
 * Reset waterBoxStartIndex
 */
void DynaLookup_ResetWaterBoxStartIndex(u16* waterBoxStartIndex) {
    *waterBoxStartIndex = 0;
}

#define BgActor_Initialize BgCheck_ActorMeshInit
/**
 * Initialize BgActor
 */
void BgActor_Initialize(GlobalContext* globalCtx, BgActor* bgActor) {
    bgActor->actor = NULL;
    bgActor->colHeader = NULL;
    ScaleRotPos_Initialize(&bgActor->prevTransform);
    ScaleRotPos_Initialize(&bgActor->curTransform);
    DynaLookup_Reset(&bgActor->dynaLookup);
    DynaLookup_ResetVtxStartIndex(&bgActor->vtxStartIndex);
    DynaLookup_ResetWaterBoxStartIndex(&bgActor->waterboxesStartIndex);
    bgActor->boundingSphere.center.x = bgActor->boundingSphere.center.y = bgActor->boundingSphere.center.z = 0;
    bgActor->boundingSphere.radius = 0;
}

#define BgActor_SetActor BgCheck_ActorMeshInitFromActor
/**
 * setActor internal
 */
void BgActor_SetActor(BgActor* bgActor, Actor* actor, CollisionHeader* colHeader) {
    bgActor->actor = actor;
    bgActor->colHeader = colHeader;
    bgActor->prevTransform.scale = actor->scale;
    bgActor->prevTransform.rot = actor->shape.rot;
    bgActor->prevTransform.rot.x--;
    bgActor->prevTransform.pos = actor->world.pos;
    bgActor->curTransform.scale = actor->scale;
    bgActor->curTransform.rot = actor->shape.rot;
    bgActor->curTransform.pos = actor->world.pos;
}

#define BgActor_IsTransformUnchanged BgCheck_HasActorMeshChanged
/**
 * Test if the BgActor transform is the same
 */
s32 BgActor_IsTransformUnchanged(BgActor* bgActor) {
    return ScaleRotPos_Equals(&bgActor->prevTransform, &bgActor->curTransform);
}

#define DynaPoly_NullPolyList BgCheck_PolygonsInit
/**
 * NULL polyList
 */
void DynaPoly_NullPolyList(CollisionPoly** polyList) {
    *polyList = NULL;
}

#define DynaPoly_AllocPolyList BgCheck_PolygonsAlloc
/**
 * Allocate dyna.polyList
 */
void DynaPoly_AllocPolyList(GlobalContext* globalCtx, CollisionPoly** polyList, s32 numPolys) {
    *polyList = THA_AllocEndAlign(&globalCtx->state.heap, numPolys * sizeof(CollisionPoly), -2);
}

#define DynaPoly_NullVtxList BgCheck_VerticesInit
/**
 * NULL vtxList
 */
void DynaPoly_NullVtxList(Vec3s** vtxList) {
    *vtxList = NULL;
}

#define DynaPoly_AllocVtxList BgCheck_VerticesListAlloc
/**
 * Allocate dyna.vtxList
 */
void DynaPoly_AllocVtxList(GlobalContext* globalCtx, Vec3s** vtxList, s32 numVtx) {
    *vtxList = THA_AllocEndAlign(&globalCtx->state.heap, numVtx * sizeof(Vec3s), -2);
    //ASSERT(*vtxList != NULL, "ptbl->pbuf != NULL", "../z_bgcheck.c", 6277);
}

#define DynaPoly_InitWaterBoxList BgCheck_WaterboxListInit
/**
* Init dyna.waterBoxList
*/
void DynaPoly_InitWaterBoxList(DynaSSWaterboxList* waterBoxList){
    waterBoxList->unk0 = 0;
    waterBoxList->boxes = NULL;
}

#define DynaPoly_AllocWaterBoxList BgCheck_WaterboxListAlloc
/**
 * Allocate dyna.waterBoxList
 */
void DynaPoly_AllocWaterBoxList(GlobalContext* globalCtx, DynaSSWaterboxList* waterBoxList, s32 numWaterBoxes) {
    waterBoxList->boxes = THA_AllocEndAlign(&globalCtx->state.heap, numWaterBoxes * sizeof(WaterBox), -2);
}

#define DynaPoly_SetBgActorPrevTransform BgCheck_ActorMeshUpdateParams
/**
 * Update BgActor's prevTransform
 */
void DynaPoly_SetBgActorPrevTransform(GlobalContext* globalCtx, BgActor* bgActor) {
    bgActor->prevTransform = bgActor->curTransform;
}

#define DynaPoly_IsBgIdBgActor BgCheck_IsActorMeshIndexValid
/**
 * Is BgActor Id
 */
s32 DynaPoly_IsBgIdBgActor(s32 bgId) {
    if (bgId < 0 || bgId >= BG_ACTOR_MAX) {
        return false;
    }
    return true;
}

/**
 * Init DynaCollisionContext
 */
void DynaPoly_Init(GlobalContext* globalCtx, DynaCollisionContext* dyna) {
    dyna->bitFlag = DYNAPOLY_INVALIDATE_LOOKUP;
    DynaPoly_NullPolyList(&dyna->polyList);
    DynaPoly_NullVtxList(&dyna->vtxList);
    DynaPoly_InitWaterBoxList(&dyna->waterboxes);
    DynaSSNodeList_Initialize(globalCtx, &dyna->polyNodes);
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_DynaAlloc.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_AddActorMesh.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_GetActorOfMesh.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C62BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C6314.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C636C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C63C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C641C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C6474.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_RemoveActorMesh.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C6554.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_CalcWaterboxDimensions.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_AddActorMeshToLists.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_ResetFlagsIfLoadedActor.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C756C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_UpdateAllActorMeshes.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C76EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C7974.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C7E40.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C8580.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C87D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C8A60.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C8BD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C8DC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C8EEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C90AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C921C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C9380.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_RelocateMeshHeaderPointers.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_RelocateMeshHeader.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_RelocateAllMeshHeaders.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C9640.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_GetPolygonAttributes.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C9704.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C9728.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C9770.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C97F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C9844.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C98CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C9924.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C99AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C99D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C99FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C9A24.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C9A4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C9A7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C9AB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C9AE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C9B18.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C9B40.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C9B68.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C9B90.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C9BB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C9BDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C9C24.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C9C74.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C9C9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C9CC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C9CEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C9D14.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C9D50.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C9D8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C9DDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C9E18.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C9E40.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C9E88.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C9EBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800CA1AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800CA1E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800CA22C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800CA568.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800CA634.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800CA648.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800CA6B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800CA6D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800CA6F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800CA9D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800CAA14.s")
