#include <ultra64.h>
#include <global.h>

// This file comes after z_bgcheck.c and contains functions to manage actors attached to Bg Actors.
// Perhaps it is called something like z_bgcheck_attach.c
// The functions will use the BgCheck2 prefix for now.

void BgCheck2_UpdateActorPosition(BgCheckContext* bgCtxt, s32 index, Actor* actor) {
    z_Matrix prevMatrix;
    z_Matrix prevMatrixInv;
    z_Matrix currMatrix;
    Vector3f newPos;
    Vector3f posWithInv;

    if (BgCheck_IsActorMeshIndexValid(index) == 0) return;

    Matrix_MakeTranslationRotationYXZScale(&prevMatrix,
        bgCtxt->dyna.actorMeshes[index].prevParams.scale.x,
        bgCtxt->dyna.actorMeshes[index].prevParams.scale.y,
        bgCtxt->dyna.actorMeshes[index].prevParams.scale.z,
        bgCtxt->dyna.actorMeshes[index].prevParams.rotation.x,
        bgCtxt->dyna.actorMeshes[index].prevParams.rotation.y,
        bgCtxt->dyna.actorMeshes[index].prevParams.rotation.z,
        bgCtxt->dyna.actorMeshes[index].prevParams.pos.x,
        bgCtxt->dyna.actorMeshes[index].prevParams.pos.y,
        bgCtxt->dyna.actorMeshes[index].prevParams.pos.z);

    if (invert_matrix(&prevMatrix, &prevMatrixInv) == 2) return;

    Matrix_MakeTranslationRotationYXZScale(&currMatrix,
        bgCtxt->dyna.actorMeshes[index].currParams.scale.x,
        bgCtxt->dyna.actorMeshes[index].currParams.scale.y,
        bgCtxt->dyna.actorMeshes[index].currParams.scale.z,
        bgCtxt->dyna.actorMeshes[index].currParams.rotation.x,
        bgCtxt->dyna.actorMeshes[index].currParams.rotation.y,
        bgCtxt->dyna.actorMeshes[index].currParams.rotation.z,
        bgCtxt->dyna.actorMeshes[index].currParams.pos.x,
        bgCtxt->dyna.actorMeshes[index].currParams.pos.y,
        bgCtxt->dyna.actorMeshes[index].currParams.pos.z);

    Matrix_MultiplyByVectorXYZ(&prevMatrixInv, &actor->unk24.pos, &posWithInv);
    Matrix_MultiplyByVectorXYZ(&currMatrix, &posWithInv, &newPos);

    actor->unk24.pos = newPos;
}

void BgCheck2_UpdateActorYRotation(BgCheckContext* bgCtxt, s32 index, Actor* actor) {
    s16 angleChange;

    if (BgCheck_IsActorMeshIndexValid(index) == 0) return;

    angleChange = bgCtxt->dyna.actorMeshes[index].currParams.rotation.y - bgCtxt->dyna.actorMeshes[index].prevParams.rotation.y;

    if (actor->id == 0) {
        ((ActorPlayer*)actor)->unkAD4 += angleChange;
    }

    actor->postDrawParams.rotation.y += angleChange;
    actor->unk24.rot.y += angleChange;
}

void BgCheck2_AttachToMesh(BgCheckContext* bgCtxt, Actor* actor, s32 index) {
    BgActor *meshActor;

    if (BgCheck_IsActorMeshIndexValid(index) == 0) return;

    meshActor = BgCheck_GetActorOfMesh(bgCtxt,index);
    if (meshActor != NULL) {
        func_800CAE88(meshActor);

        if ((actor->flags & 0x4000000) == 0x4000000) {
            func_800CAF24(meshActor);
        }
        if ((actor->flags & 0x20000) == 0x20000) {
            func_800CAF38(meshActor);
        }
    }
}

u32 BgCheck2_UpdateActorAttachedToMesh(BgCheckContext* bgCtxt, s32 index, Actor* actor) {
    u32 wasUpdated = 0;
    BgActor *meshActor;

    if (BgCheck_IsActorMeshIndexValid(index) == 0) return 0;

    if (((bgCtxt->dyna.meshParams[index] & 2) != 0) || ((bgCtxt->dyna.meshParams[index] & 1) == 0)) return 0;

    meshActor = BgCheck_GetActorOfMesh(bgCtxt,index);

    if (meshActor == NULL) return 0;

    if ((meshActor->unk154 & 1) != 0) {
        BgCheck2_UpdateActorPosition(bgCtxt,index,actor);
        wasUpdated = 1;
    }

    if ((meshActor->unk154 & 2) != 0) {
        BgCheck2_UpdateActorYRotation(bgCtxt,index,actor);
        wasUpdated = 1;
    }

    return wasUpdated;
}

