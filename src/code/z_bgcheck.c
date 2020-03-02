#include <ultra64.h>
#include <global.h>

void BgCheck_PolygonLinkedListNodeInit(BgPolygonLinkedListNode* node, s16* polyIndex, u16 next) {
    node->polyIndex = *polyIndex;
    node->next = next;
}

void BgCheck_PolygonLinkedListResetHead(u16* head) {
    *head = 0xFFFF;
}

void BgCheck_ScenePolygonListsNodeInsert(BgScenePolygonLists* list, u16* head, s16* polyIndex) {
    u16 index;

    index = BgCheck_ScenePolygonListsReserveNode(list);
    BgCheck_PolygonLinkedListNodeInit(&list->nodes[index], polyIndex, *head);
    *head = index;
}

void BgCheck_PolygonLinkedListNodeInsert(BgPolygonLinkedList* list, u16* head, s16* polyIndex) {
    u16 index;

    index = BgCheck_AllocPolygonLinkedListNode(list);
    BgCheck_PolygonLinkedListNodeInit(&list->nodes[index], polyIndex, *head);
    *head = index;
}

void BgCheck_PolygonLinkedListInit(GlobalContext* ctxt, BgPolygonLinkedList* list) {
    list->nodes = NULL;
    list->nextFreeNode = 0;
}

void BgCheck_PolygonLinkedListAlloc(GlobalContext* ctxt, BgPolygonLinkedList* list, u32 numNodes) {
    list->nodes = (BgPolygonLinkedListNode*)GameStateHeap_AllocFromEndAligned(&ctxt->common.heap, numNodes << 2, 0xfffffffe);
    list->maxNodes = numNodes;
    list->nextFreeNode = 0;
}

void BgCheck_PolygonLinkedListReset(BgPolygonLinkedList* list) {
    list->nextFreeNode = 0;
}

u16 BgCheck_AllocPolygonLinkedListNode(BgPolygonLinkedList* list) {
    u16 index;

    index = list->nextFreeNode++;
    if (list->maxNodes <= index) {
        return 0xffff;
    }

    return index;
}

void BgCheck_CreateVec3fFromVertex(BgVertex* vertex, Vector3f* vector) {
    vector->x = vertex->pos.x;
    vector->y = vertex->pos.y;
    vector->z = vertex->pos.z;
}

void BgCheck_CreateVertexFromVec3f(BgVertex* vertex, Vector3f* vector) {
    vertex->pos.x = vector->x;
    vertex->pos.y = vector->y;
    vertex->pos.z = vector->z;
}

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800BFD84.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800BFDEC.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/BgCheck_PolygonGetMinY.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C003C.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C0094.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C01B8.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/BgCheck_CreateColTriParamsFromPolygon.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C02C0.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C0340.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C0474.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C0668.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C06A8.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C074C.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C07F0.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C0AF0.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/BgCheck_ScenePolygonListsInsertSorted.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/BgCheck_ScenePolygonListsInsert.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C0E74.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C10FC.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C1238.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C12A4.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C1B68.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C1D7C.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C2008.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C20F4.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C2310.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C2460.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C2514.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C25E0.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/BgCheck_GetPolyMinSubdivisions.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/BgCheck_GetPolyMaxSubdivisions.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/BgCheck_GetPolyMinMaxSubdivisions.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C2BE0.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/BgCheck_SplitScenePolygonsIntoSubdivisions.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/BgCheck_GetIsDefaultSpecialScene.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/BgCheck_GetSpecialSceneMaxMemory.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/BgCheck_CalcSubdivisionSize.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/BgCheck_GetSpecialSceneMaxObjects.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/BgCheck_Init.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C3C00.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C3C14.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/BgCheck_GetActorMeshHeader.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C3C94.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C3D50.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C3F40.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C3FA0.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C4000.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C4058.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C40B4.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C411C.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C4188.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C41E4.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C4240.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C42A8.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C4314.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C43CC.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C4488.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C44F0.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C455C.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C45C4.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C4C74.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C4CD8.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C4D3C.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C4DA4.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C4E10.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C4F38.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C4F84.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C4FD4.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C5464.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C54AC.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C5538.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C55C4.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C5650.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C56E0.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C576C.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C57F8.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C583C.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C58C8.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C5954.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C5A20.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C5A64.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/BgCheck_ScenePolygonListsInit.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/BgCheck_ScenePolygonListsAlloc.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C5B80.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/BgCheck_ScenePolygonListsReserveNode.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/BgCheck_ActorMeshParamsInit.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/BgCheck_SetActorMeshParams.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/BgCheck_AreActorMeshParamsEqual.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/BgCheck_ActorMeshPolyListsHeadsInit.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/BgCheck_ActorMeshPolyListsInit.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/BgCheck_ActorMeshVerticesIndexInit.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/BgCheck_ActorMeshWaterboxesIndexInit.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/BgCheck_ActorMeshInit.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/BgCheck_ActorMeshInitFromActor.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/BgCheck_HasActorMeshChanged.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/BgCheck_PolygonsInit.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/BgCheck_PolygonsAlloc.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/BgCheck_VerticesInit.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/BgCheck_VerticesListAlloc.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/BgCheck_WaterboxListInit.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/BgCheck_WaterboxListAlloc.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/BgCheck_ActorMeshUpdateParams.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/BgCheck_IsActorMeshIndexValid.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/BgCheck_DynaInit.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/BgCheck_DynaAlloc.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/BgCheck_AddActorMesh.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/BgCheck_GetActorOfMesh.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C62BC.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C6314.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C636C.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C63C4.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C641C.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C6474.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/BgCheck_RemoveActorMesh.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C6554.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/BgCheck_CalcWaterboxDimensions.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/BgCheck_AddActorMeshToLists.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/BgCheck_ResetFlagsIfLoadedActor.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/BgCheck_Update.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C756C.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/BgCheck_UpdateAllActorMeshes.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C76EC.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C7974.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C7E40.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C8580.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C87D0.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C8A60.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C8BD0.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C8DC0.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C8EEC.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C90AC.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C921C.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C9380.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/BgCheck_RelocateMeshHeaderPointers.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/BgCheck_RelocateMeshHeader.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/BgCheck_RelocateAllMeshHeaders.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C9640.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/BgCheck_GetPolygonAttributes.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C9704.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C9728.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C9770.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C97F8.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C9844.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C98CC.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C9924.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C99AC.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C99D4.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C99FC.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C9A24.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C9A4C.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C9A7C.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C9AB0.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C9AE4.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C9B18.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C9B40.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C9B68.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C9B90.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C9BB8.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C9BDC.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C9C24.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C9C74.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C9C9C.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C9CC4.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C9CEC.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C9D14.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C9D50.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C9D8C.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C9DDC.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C9E18.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C9E40.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C9E88.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800C9EBC.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800CA1AC.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800CA1E8.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800CA22C.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800CA568.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800CA634.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800CA648.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800CA6B8.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800CA6D8.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800CA6F0.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800CA9D0.asm")

GLOBAL_ASM("./asm/non_matchings/z_bgcheck/func_800CAA14.asm")

