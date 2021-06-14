#include <ultra64.h>
#include <global.h>

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

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800BFD84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800BFDEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/BgCheck_PolygonGetMinY.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/BgCheck_PolygonGetNormal.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C0094.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C01B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/BgCheck_CreateTriNormFromPolygon.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C02C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C0340.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C0474.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C0668.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C06A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C074C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C07F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/BgCheck_PolygonCollidesWithSphere.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/BgCheck_ScenePolygonListsInsertSorted.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/BgCheck_ScenePolygonListsInsert.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C0E74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C10FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C1238.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C12A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C1B68.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C1D7C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C2008.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C20F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C2310.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C2460.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C2514.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C25E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/BgCheck_GetPolyMinSubdivisions.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/BgCheck_GetPolyMaxSubdivisions.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/BgCheck_GetPolyMinMaxSubdivisions.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C2BE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/BgCheck_SplitScenePolygonsIntoSubdivisions.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/BgCheck_GetIsDefaultSpecialScene.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/BgCheck_GetSpecialSceneMaxMemory.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/BgCheck_CalcSubdivisionSize.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/BgCheck_GetSpecialSceneMaxObjects.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/BgCheck_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C3C00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C3C14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/BgCheck_GetActorMeshHeader.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C3C94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C3D50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C3F40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C3FA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C4000.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C4058.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C40B4.asm")

f32 func_800C411C(CollisionContext* colCtx, CollisionPoly** arg1, s32* arg2, Actor* actor, Vec3f* pos) {
    return func_800C3D50(0, colCtx, 2, arg1, arg2, pos, actor, 28, 1.0f, 0);
}

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C4188.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C41E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C4240.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C42A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C4314.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C43CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C4488.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C44F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C455C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C45C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C4C74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C4CD8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C4D3C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C4DA4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C4E10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C4F38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C4F84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C4FD4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C5464.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C54AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C5538.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C55C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C5650.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C56E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C576C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C57F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C583C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C58C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C5954.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C5A20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C5A64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/BgCheck_ScenePolygonListsInit.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/BgCheck_ScenePolygonListsAlloc.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C5B80.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/BgCheck_ScenePolygonListsReserveNode.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/BgCheck_ActorMeshParamsInit.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/BgCheck_SetActorMeshParams.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/BgCheck_AreActorMeshParamsEqual.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/BgCheck_ActorMeshPolyListsHeadsInit.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/BgCheck_ActorMeshPolyListsInit.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/BgCheck_ActorMeshVerticesIndexInit.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/BgCheck_ActorMeshWaterboxesIndexInit.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/BgCheck_ActorMeshInit.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/BgCheck_ActorMeshInitFromActor.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/BgCheck_HasActorMeshChanged.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/BgCheck_PolygonsInit.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/BgCheck_PolygonsAlloc.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/BgCheck_VerticesInit.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/BgCheck_VerticesListAlloc.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/BgCheck_WaterboxListInit.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/BgCheck_WaterboxListAlloc.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/BgCheck_ActorMeshUpdateParams.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/BgCheck_IsActorMeshIndexValid.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/BgCheck_DynaInit.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/BgCheck_DynaAlloc.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/BgCheck_AddActorMesh.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/BgCheck_GetActorOfMesh.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C62BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C6314.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C636C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C63C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C641C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C6474.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/BgCheck_RemoveActorMesh.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C6554.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/BgCheck_CalcWaterboxDimensions.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/BgCheck_AddActorMeshToLists.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/BgCheck_ResetFlagsIfLoadedActor.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/BgCheck_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C756C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/BgCheck_UpdateAllActorMeshes.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C76EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C7974.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C7E40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C8580.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C87D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C8A60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C8BD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C8DC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C8EEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C90AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C921C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C9380.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/BgCheck_RelocateMeshHeaderPointers.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/BgCheck_RelocateMeshHeader.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/BgCheck_RelocateAllMeshHeaders.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C9640.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/BgCheck_GetPolygonAttributes.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C9704.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C9728.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C9770.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C97F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C9844.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C98CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C9924.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C99AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C99D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C99FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C9A24.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C9A4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C9A7C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C9AB0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C9AE4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C9B18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C9B40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C9B68.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C9B90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C9BB8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C9BDC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C9C24.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C9C74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C9C9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C9CC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C9CEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C9D14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C9D50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C9D8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C9DDC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C9E18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C9E40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C9E88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800C9EBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800CA1AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800CA1E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800CA22C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800CA568.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800CA634.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800CA648.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800CA6B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800CA6D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800CA6F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800CA9D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_bgcheck/func_800CAA14.asm")
