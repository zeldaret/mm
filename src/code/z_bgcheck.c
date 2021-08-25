#include "global.h"

void BgCheck_PolygonLinkedListNodeInit(SSNode* node, s16* polyIndex, u16 next) {
    node->polyId = *polyIndex;
    node->next = next;
}

void BgCheck_PolygonLinkedListResetHead(u16* head) {
    *head = 0xFFFF;
}

void BgCheck_ScenePolygonListsNodeInsert(SSNodeList* list, u16* head, s16* polyIndex) {
    u16 index;

    index = BgCheck_ScenePolygonListsReserveNode(list);
    BgCheck_PolygonLinkedListNodeInit(&list->tbl[index], polyIndex, *head);
    *head = index;
}

void BgCheck_PolygonLinkedListNodeInsert(DynaSSNodeList* list, u16* head, s16* polyIndex) {
    u16 index;

    index = BgCheck_AllocPolygonLinkedListNode(list);
    BgCheck_PolygonLinkedListNodeInit(&list->tbl[index], polyIndex, *head);
    *head = index;
}

void BgCheck_PolygonLinkedListInit(GlobalContext* globalCtx, DynaSSNodeList* list) {
    list->tbl = NULL;
    list->count = 0;
}

void BgCheck_PolygonLinkedListAlloc(GlobalContext* globalCtx, DynaSSNodeList* list, u32 numNodes) {
    list->tbl = (SSNode*)THA_AllocEndAlign(&globalCtx->state.heap, numNodes << 2, 0xfffffffe);
    list->max = numNodes;
    list->count = 0;
}

void BgCheck_PolygonLinkedListReset(DynaSSNodeList* list) {
    list->count = 0;
}

u16 BgCheck_AllocPolygonLinkedListNode(DynaSSNodeList* list) {
    u16 index;

    index = list->count++;
    if (list->max <= index) {
        return 0xffff;
    }

    return index;
}

void BgCheck_CreateVec3fFromVertex(Vec3s* vertex, Vec3f* vector) {
    vector->x = vertex->x;
    vector->y = vertex->y;
    vector->z = vertex->z;
}

void BgCheck_CreateVertexFromVec3f(Vec3s* vertex, Vec3f* vector) {
    vertex->x = vector->x;
    vertex->y = vector->y;
    vertex->z = vector->z;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800BFD84.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800BFDEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_PolygonGetMinY.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_PolygonGetNormal.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C0094.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C01B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_CreateTriNormFromPolygon.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C02C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C0340.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C0474.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C0668.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C06A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C074C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C07F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_PolygonCollidesWithSphere.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_ScenePolygonListsInsertSorted.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/BgCheck_ScenePolygonListsInsert.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C0E74.s")

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

// BgCheck_EntitySphVsWall3
#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C4D3C.s")

// BgCheck_EntitySphVsWall4
#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C4DA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C4E10.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_bgcheck/func_800C4F38.s")

// BgCheck_EntityCheckCeiling
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
