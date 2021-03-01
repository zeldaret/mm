#include <ultra64.h>
#include <global.h>

// This file comes after z_bgcheck.c and contains functions to manage actors attached to Bg Actors.
// Perhaps it is called something like z_bgcheck_attach.c
// The functions will use the BgCheck2 prefix for now.

void BgCheck2_UpdateActorPosition(CollisionContext* bgCtxt, s32 index, Actor* actor) {
    z_Matrix prevMatrix;
    z_Matrix prevMatrixInv;
    z_Matrix currMatrix;
    Vec3f newPos;
    Vec3f posWithInv;

    if (BgCheck_IsActorMeshIndexValid(index) == 0) return;

    Matrix_MakeTranslationRotationYXZScale(&prevMatrix,
        bgCtxt->dyna.actorMeshArr[index].prevParams.scale.x,
        bgCtxt->dyna.actorMeshArr[index].prevParams.scale.y,
        bgCtxt->dyna.actorMeshArr[index].prevParams.scale.z,
        bgCtxt->dyna.actorMeshArr[index].prevParams.rotation.x,
        bgCtxt->dyna.actorMeshArr[index].prevParams.rotation.y,
        bgCtxt->dyna.actorMeshArr[index].prevParams.rotation.z,
        bgCtxt->dyna.actorMeshArr[index].prevParams.pos.x,
        bgCtxt->dyna.actorMeshArr[index].prevParams.pos.y,
        bgCtxt->dyna.actorMeshArr[index].prevParams.pos.z);

    if (Matrix_Invert(&prevMatrix, &prevMatrixInv) == 2) return;

    Matrix_MakeTranslationRotationYXZScale(&currMatrix,
        bgCtxt->dyna.actorMeshArr[index].currParams.scale.x,
        bgCtxt->dyna.actorMeshArr[index].currParams.scale.y,
        bgCtxt->dyna.actorMeshArr[index].currParams.scale.z,
        bgCtxt->dyna.actorMeshArr[index].currParams.rotation.x,
        bgCtxt->dyna.actorMeshArr[index].currParams.rotation.y,
        bgCtxt->dyna.actorMeshArr[index].currParams.rotation.z,
        bgCtxt->dyna.actorMeshArr[index].currParams.pos.x,
        bgCtxt->dyna.actorMeshArr[index].currParams.pos.y,
        bgCtxt->dyna.actorMeshArr[index].currParams.pos.z);

    Matrix_MultiplyByVectorXYZ(&prevMatrixInv, &actor->world.pos, &posWithInv);
    Matrix_MultiplyByVectorXYZ(&currMatrix, &posWithInv, &newPos);

    actor->world.pos = newPos;
}

void BgCheck2_UpdateActorYRotation(CollisionContext* bgCtxt, s32 index, Actor* actor) {
    s16 angleChange;

    if (BgCheck_IsActorMeshIndexValid(index) == 0) return;

    angleChange = bgCtxt->dyna.actorMeshArr[index].currParams.rotation.y - bgCtxt->dyna.actorMeshArr[index].prevParams.rotation.y;

    if (actor->id == 0) {
        ((ActorPlayer*)actor)->unkAD4 += angleChange;
    }

    actor->shape.rot.y += angleChange;
    actor->world.rot.y += angleChange;
}

void BgCheck2_AttachToMesh(CollisionContext* bgCtxt, Actor* actor, s32 index) {
    DynaPolyActor *meshActor;

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

u32 BgCheck2_UpdateActorAttachedToMesh(CollisionContext* bgCtxt, s32 index, Actor* actor) {
    u32 wasUpdated = 0;
    DynaPolyActor *meshActor;

    if (BgCheck_IsActorMeshIndexValid(index) == 0) return 0;

    if (((bgCtxt->dyna.flags[index] & 2) != 0) || ((bgCtxt->dyna.flags[index] & 1) == 0)) return 0;

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

