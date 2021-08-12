#include "global.h"

//SSNode_SetValue
void BgCheck_PolygonLinkedListNodeInit(SSNode* node, s16* polyIndex, u16 next) {
    node->polyId = *polyIndex;
    node->next = next;
}

//SSList_SetNull
void BgCheck_PolygonLinkedListResetHead(u16* head) {
    *head = SS_NULL;
}

//SSNodeList_SetSSListHead
void BgCheck_ScenePolygonListsNodeInsert(SSNodeList* list, SSList* ssList, s16* polyIndex) {
    u16 index;

    index = BgCheck_ScenePolygonListsReserveNode(list);
    BgCheck_PolygonLinkedListNodeInit(&list->tbl[index], polyIndex, ssList->head);
    ssList->head = index;
}

//DynaSSNodeList_SetSSListHead
void BgCheck_PolygonLinkedListNodeInsert(DynaSSNodeList* list, SSList* ssList, s16* polyIndex) {
    u16 index;

    index = BgCheck_AllocPolygonLinkedListNode(list);
    BgCheck_PolygonLinkedListNodeInit(&list->nodes[index], polyIndex, ssList->head);
    ssList->head = index;
}

//DynaSSNodeList_Initialize
void BgCheck_PolygonLinkedListInit(GlobalContext* globalCtx, DynaSSNodeList* list) {
    list->nodes = NULL;
    list->count = 0;
}

//DynaSSNodeList_Alloc
void BgCheck_PolygonLinkedListAlloc(GlobalContext* globalCtx, DynaSSNodeList* list, u32 numNodes) {
    list->nodes = (SSNode*)THA_AllocEndAlign(&globalCtx->state.heap, numNodes * sizeof(SSNode), -2);
    list->maxNodes = numNodes;
    list->count = 0;
}

//DynaSSNodeList_ResetCount
void BgCheck_PolygonLinkedListReset(DynaSSNodeList* list) {
    list->count = 0;
}

//DynaSSNodeList_GetNextNodeIdx
u16 BgCheck_AllocPolygonLinkedListNode(DynaSSNodeList* list) {
    u16 index;

    index = list->count++;
    if (list->maxNodes <= index) {
        return SS_NULL;
    }

    return index;
}

//BgCheck_Vec3sToVec3f
void BgCheck_CreateVec3fFromVertex(BgVertex* vertex, Vec3f* vector) {
    vector->x = vertex->pos.x;
    vector->y = vertex->pos.y;
    vector->z = vertex->pos.z;
}

//BgCheck_Vec3fToVec3s
void BgCheck_CreateVertexFromVec3f(BgVertex* vertex, Vec3f* vector) {
    vertex->pos.x = vector->x;
    vertex->pos.y = vector->y;
    vertex->pos.z = vector->z;
}

//#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800BFD84.s")
f32 func_800BFD84(CollisionPoly *polygon, f32 param_2, f32 param_3) {
    return ((COLPOLY_GET_NORMAL(polygon->normal.x * param_2 + polygon->normal.z * param_3)) + (f32) polygon->dist) / ((f32) -(s32) polygon->normal.y * COLPOLY_NORMAL_FRAC);
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800BFDEC.s")

//#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_PolygonGetMinY.s")
//CollisionPoly_GetMinY
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

//#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_PolygonGetNormal.s")
//CollisionPoly_GetNormalF
void BgCheck_PolygonGetNormal(CollisionPoly* poly, f32* nx, f32* ny, f32* nz) {
    *nx = COLPOLY_GET_NORMAL(poly->normal.x);
    *ny = COLPOLY_GET_NORMAL(poly->normal.y);
    *nz = COLPOLY_GET_NORMAL(poly->normal.z);
}

//#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C0094.s")
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

//#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C01B8.s")
//CollisionPoly_GetPointDistanceFromPlane
f32 func_800C01B8(CollisionPoly* poly, Vec3f* point) {
    return (poly->normal.x * point->x + poly->normal.y * point->y + poly->normal.z * point->z) * COLPOLY_NORMAL_FRAC +
        poly->dist;
}

//#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_CreateTriNormFromPolygon.s")
//CollisionPoly_GetVertices
void BgCheck_CreateTriNormFromPolygon(CollisionPoly* poly, Vec3s* vtxList, Vec3f* dest) {
    BgCheck_CreateVec3fFromVertex(&vtxList[COLPOLY_VTX_INDEX(poly->flags_vIA)], &dest[0]);
    BgCheck_CreateVec3fFromVertex(&vtxList[COLPOLY_VTX_INDEX(poly->flags_vIB)], &dest[1]);
    BgCheck_CreateVec3fFromVertex(&vtxList[poly->vIC], &dest[2]);
}

//#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C02C0.s")
//CollisionPoly_GetVerticesByBgId
void func_800C02C0(CollisionPoly* poly, s32 bgId, CollisionContext* colCtx, Vec3f* dest) {
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

s32 func_8017BE30(Vec3f* a, Vec3f* b, Vec3f* c, f32 nx, f32 ny, f32 nz, f32 dist, f32 z, f32 x, f32* yIntersect, f32 chkDist);

//#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C0340.s")
extern Vec3f D_801ED9F0[3]; //polyVerts
//CollisionPoly_CheckYIntersectApprox1
s32 func_800C0340(CollisionPoly* poly, Vec3s* vtxList, f32 x, f32 z, f32* yIntersect, f32 chkDist) {
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

    return func_8017BE30(&D_801ED9F0[0], &D_801ED9F0[1], &D_801ED9F0[2], nx, ny, nz, poly->dist, z,
        x, yIntersect, chkDist);
}

#define CollisionPoly_CheckYIntersect func_800C0474
s32 CollisionPoly_CheckYIntersect(CollisionPoly* poly, Vec3s* vtxList, f32 x, f32 z, f32* yIntersect, f32 chkDist);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C0474.s")

//#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C0668.s")
//CollisionPoly_CheckYIntersectApprox2
void func_800C0668(CollisionPoly* poly, Vec3s* vtxList, f32 x, f32 z, f32* yIntersect) {
    func_800C0340(poly, vtxList, x, z, yIntersect, 1.0f);
}

s32 func_8017C850(Vec3f* a, Vec3f* b, Vec3f* c, f32 nx, f32 ny, f32 nz, f32 dist, f32 y, f32 z, f32* xIntersect);

extern Vec3f D_801EDA80[3]; //polyVerts
//#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C06A8.s")
//CollisionPoly_CheckXIntersectApprox
s32 func_800C06A8(CollisionPoly* poly, Vec3s* vtxList, f32 y, f32 z, f32* xIntersect) {
    f32 nx;
    f32 ny;
    f32 nz;

    BgCheck_CreateTriNormFromPolygon(poly, vtxList, D_801EDA80);
    BgCheck_PolygonGetNormal(poly, &nx, &ny, &nz);
    return func_8017C850(&D_801EDA80[0], &D_801EDA80[1], &D_801EDA80[2], nx, ny, nz, poly->dist, y, z,
        xIntersect);
}

s32 func_8017CEF0(Vec3f* a, Vec3f* b, Vec3f* c, f32 nx, f32 ny, f32 nz, f32 dist, f32 x, f32 y, f32* zIntersect);
extern Vec3f D_801EDB48[3]; //polyVerts
//#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C074C.s")
//CollisionPoly_CheckZIntersectApprox
s32 func_800C074C(CollisionPoly* poly, Vec3s* vtxList, f32 x, f32 y, f32* zIntersect) {
    f32 nx;
    f32 ny;
    f32 nz;

    BgCheck_CreateTriNormFromPolygon(poly, vtxList, D_801EDB48);
    BgCheck_PolygonGetNormal(poly, &nx, &ny, &nz);
    return func_8017CEF0(&D_801EDB48[0], &D_801EDB48[1], &D_801EDB48[2], nx, ny, nz, poly->dist, x, y,
        zIntersect);
}

typedef struct {
    CollisionPoly* poly;
    Vec3s* vtxList;
    Vec3f* posA;
    Vec3f* posB;
    Vec3f* planeIntersect;
    s32 chkOneFace;
    f32 chkDist;
} func_800C07F0_args;

s32 func_8017C540(Vec3f* v0, Vec3f* v1, Vec3f* v2, f32 y, f32 z, f32 unk, f32 chkDist, f32 nx); //Math3D_TriChkPointParaXDist
s32 func_8017BAD0(Vec3f* v0, Vec3f* v1, Vec3f* v2, f32 y, f32 z, f32 unk, f32 chkDist, f32 ny); //Math3D_TriChkPointParaYDist
s32 func_8017CB7C(Vec3f* v0, Vec3f* v1, Vec3f* v2, f32 y, f32 z, f32 unk, f32 chkDist, f32 nz); //Math3D_TriChkLineSegParaZDist

//CollisionPoly_LineVsPoly
#ifdef NON_MATCHING
//#define polyVerts D_801EDB70
//#define plane D_801EDB98
s32 func_800C07F0(func_800C07F0_args* a0) {
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
        func_8017C540(
            &polyVerts[0],
            &polyVerts[1],
            &polyVerts[2],
            a0->planeIntersect->y,
            a0->planeIntersect->z,
            0.0f,
            a0->chkDist,
            plane.normal.x))
        || (fabsf(plane.normal.y) > 0.5f &&
            func_8017BAD0(
                &polyVerts[0],
                &polyVerts[1],
                &polyVerts[2],
                a0->planeIntersect->z,
                a0->planeIntersect->x,
                0.0f,
                a0->chkDist,
                plane.normal.y))
        || (fabsf(plane.normal.z) > 0.5f &&
            func_8017CB7C(
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

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_PolygonCollidesWithSphere.s")

//CollisionPoly_SphVsPoly
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


// NON_MATCHING
/**
 * Add poly to StaticLookup table
 * Table is sorted by poly's smallest y vertex component
 * `ssList` is the list to append a new poly to
 * `polyList` is the CollisionPoly lookup list
 * `vtxList` is the vertex lookup list
 * `polyId` is the index of the poly in polyList to insert into the lookup table
 */
#define StaticLookup_AddPolyToSSList BgCheck_ScenePolygonListsInsertSorted
#ifdef NON_MATCHING
void BgCheck_ScenePolygonListsInsertSorted(CollisionContext* colCtx, SSList* ssList, CollisionPoly* polyList, Vec3s* vtxList,
    s16 polyId) {
    SSNode* curNode;
    SSNode* nextNode;
    s32 polyYMin;
    u16 newNodeId;
    s16 curPolyId;

    // if list is null
    if (ssList->head == SS_NULL) {
        BgCheck_ScenePolygonListsNodeInsert(&colCtx->polyNodes, ssList, &polyId);
        return;
    }

    polyYMin = BgCheck_PolygonGetMinY(&polyList[polyId], vtxList);

    curNode = &colCtx->polyNodes.tbl[ssList->head];
    curPolyId = curNode->polyId;

    // if the poly being inserted has a lower y than the first poly
    if (polyYMin < vtxList[COLPOLY_VTX_INDEX(polyList[curPolyId].flags_vIA)].y &&
        polyYMin < vtxList[COLPOLY_VTX_INDEX(polyList[curPolyId].flags_vIB)].y &&
        polyYMin < vtxList[polyList[curPolyId].vIC].y) {
        BgCheck_ScenePolygonListsNodeInsert(&colCtx->polyNodes, ssList, &polyId);
        return;
    }
    while (true) {
        // if at the end of the list
        if (curNode->next == SS_NULL) {
            newNodeId = BgCheck_ScenePolygonListsReserveNode(&colCtx->polyNodes);
            BgCheck_PolygonLinkedListNodeInit(&colCtx->polyNodes.tbl[newNodeId], &polyId, SS_NULL);
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
            BgCheck_PolygonLinkedListNodeInit(&colCtx->polyNodes.tbl[newNodeId], &polyId, curNode->next);
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
//StaticLookup_AddPoly
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

typedef struct {
    u16 unk0;
    u8 unk2;
} struct_func_800C0E74;

#define BgCheck_RaycastFloorStaticList func_800C0E74
/**
 * Locates the closest static poly directly underneath `pos`, starting at list `ssList`
 * returns yIntersect of the closest poly, or `yIntersectMin`
 * stores the pointer of the closest poly to `outPoly`
 * if (flags & 1), ignore polys with a normal.y < 0 (from vertical walls to ceilings)
 */
f32 BgCheck_RaycastFloorStaticList(CollisionContext* colCtx, u16 xpFlags, SSList* ssList, CollisionPoly** outPoly,
    Vec3f* pos, f32 yIntersectMin, f32 chkDist, s32 flags, struct_func_800C0E74* arg8, s32 arg9) {
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
            || ( COLPOLY_VIA_FLAG_TEST(colPoly->flags_vIB, 4)
                && ( (arg8 != NULL && arg8->unk2 != 2) || (arg8 == NULL && xpFlags != 1))))
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

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C10FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C1238.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C12A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C1B68.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C1D7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C2008.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C20F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C2310.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C2460.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C2514.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C25E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_GetPolyMinSubdivisions.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_GetPolyMaxSubdivisions.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_GetPolyMinMaxSubdivisions.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C2BE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_SplitScenePolygonsIntoSubdivisions.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_GetIsDefaultSpecialScene.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_GetSpecialSceneMaxMemory.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_CalcSubdivisionSize.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_GetSpecialSceneMaxObjects.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C3C00.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C3C14.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_GetActorMeshHeader.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C3C94.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C3D50.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C3F40.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C3FA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C4000.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C4058.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C40B4.s")

f32 func_800C411C(CollisionContext* colCtx, CollisionPoly** arg1, s32* arg2, Actor* actor, Vec3f* pos) {
    return func_800C3D50(0, colCtx, 2, arg1, arg2, pos, actor, 28, 1.0f, 0);
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C4188.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C41E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C4240.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C42A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C4314.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C43CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C4488.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C44F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C455C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C45C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C4C74.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C4CD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C4D3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C4DA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C4E10.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C4F38.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C4F84.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C4FD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C5464.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C54AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C5538.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C55C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C5650.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C56E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C576C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C57F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C583C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C58C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C5954.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C5A20.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C5A64.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_ScenePolygonListsInit.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_ScenePolygonListsAlloc.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C5B80.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_ScenePolygonListsReserveNode.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_ActorMeshParamsInit.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_SetActorMeshParams.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_AreActorMeshParamsEqual.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_ActorMeshPolyListsHeadsInit.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_ActorMeshPolyListsInit.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_ActorMeshVerticesIndexInit.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_ActorMeshWaterboxesIndexInit.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_ActorMeshInit.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_ActorMeshInitFromActor.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_HasActorMeshChanged.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_PolygonsInit.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_PolygonsAlloc.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_VerticesInit.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_VerticesListAlloc.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_WaterboxListInit.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_WaterboxListAlloc.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_ActorMeshUpdateParams.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_IsActorMeshIndexValid.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_DynaInit.s")

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
