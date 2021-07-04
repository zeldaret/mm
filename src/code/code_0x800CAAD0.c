#include <ultra64.h>
#include <global.h>

// This file comes after z_bgcheck.c and contains functions to manage actors attached to Bg Actors.
// Perhaps it is called something like z_bgcheck_attach.c
// The functions will use the BgCheck2 prefix for now.

void BgCheck2_UpdateActorPosition(CollisionContext* colCtx, s32 index, Actor* actor) {
    MtxF prevMatrix;
    MtxF prevMatrixInv;
    MtxF currMatrix;
    Vec3f newPos;
    Vec3f posWithInv;

    if (BgCheck_IsActorMeshIndexValid(index) == 0) {
        return;
    }

    SkinMatrix_SetScaleRotateYRPTranslate(
        &prevMatrix, colCtx->dyna.bgActors[index].prevTransform.scale.x,
        colCtx->dyna.bgActors[index].prevTransform.scale.y, colCtx->dyna.bgActors[index].prevTransform.scale.z,
        colCtx->dyna.bgActors[index].prevTransform.rot.x, colCtx->dyna.bgActors[index].prevTransform.rot.y,
        colCtx->dyna.bgActors[index].prevTransform.rot.z, colCtx->dyna.bgActors[index].prevTransform.pos.x,
        colCtx->dyna.bgActors[index].prevTransform.pos.y, colCtx->dyna.bgActors[index].prevTransform.pos.z);

    if (SkinMatrix_Invert(&prevMatrix, &prevMatrixInv) == 2) {
        return;
    }

    SkinMatrix_SetScaleRotateYRPTranslate(
        &currMatrix, colCtx->dyna.bgActors[index].curTransform.scale.x,
        colCtx->dyna.bgActors[index].curTransform.scale.y, colCtx->dyna.bgActors[index].curTransform.scale.z,
        colCtx->dyna.bgActors[index].curTransform.rot.x, colCtx->dyna.bgActors[index].curTransform.rot.y,
        colCtx->dyna.bgActors[index].curTransform.rot.z, colCtx->dyna.bgActors[index].curTransform.pos.x,
        colCtx->dyna.bgActors[index].curTransform.pos.y, colCtx->dyna.bgActors[index].curTransform.pos.z);

    SkinMatrix_Vec3fMtxFMultXYZ(&prevMatrixInv, &actor->world.pos, &posWithInv);
    SkinMatrix_Vec3fMtxFMultXYZ(&currMatrix, &posWithInv, &newPos);

    actor->world.pos = newPos;
}

void BgCheck2_UpdateActorYRotation(CollisionContext* colCtx, s32 index, Actor* actor) {
    s16 angleChange;

    if (BgCheck_IsActorMeshIndexValid(index) == 0) {
        return;
    }

    angleChange = colCtx->dyna.bgActors[index].curTransform.rot.y - colCtx->dyna.bgActors[index].prevTransform.rot.y;

    if (actor->id == 0) {
        ((Player*)actor)->currentYaw += angleChange;
    }

    actor->shape.rot.y += angleChange;
    actor->world.rot.y += angleChange;
}

void BgCheck2_AttachToMesh(CollisionContext* colCtx, Actor* actor, s32 index) {
    DynaPolyActor* meshActor;

    if (BgCheck_IsActorMeshIndexValid(index) == 0) {
        return;
    }

    meshActor = BgCheck_GetActorOfMesh(colCtx, index);
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

u32 BgCheck2_UpdateActorAttachedToMesh(CollisionContext* colCtx, s32 index, Actor* actor) {
    u32 wasUpdated = 0;
    DynaPolyActor* meshActor;

    if (BgCheck_IsActorMeshIndexValid(index) == 0) {
        return 0;
    }

    if (((colCtx->dyna.bgActorFlags[index] & 2) != 0) || ((colCtx->dyna.bgActorFlags[index] & 1) == 0)) {
        return 0;
    }

    meshActor = BgCheck_GetActorOfMesh(colCtx, index);

    if (meshActor == NULL) {
        return 0;
    }

    if ((meshActor->unk154 & 1) != 0) {
        BgCheck2_UpdateActorPosition(colCtx, index, actor);
        wasUpdated = 1;
    }

    if ((meshActor->unk154 & 2) != 0) {
        BgCheck2_UpdateActorYRotation(colCtx, index, actor);
        wasUpdated = 1;
    }

    return wasUpdated;
}
