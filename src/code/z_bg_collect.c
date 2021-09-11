#include "global.h"

void BgCheck2_UpdateActorPosition(CollisionContext* colCtx, s32 bgId, Actor* actor) {
    MtxF prevMatrix;
    MtxF prevMatrixInv;
    MtxF currMatrix;
    Vec3f newPos;
    Vec3f posWithInv;

    if (DynaPoly_IsBgIdBgActor(bgId) == false) {
        return;
    }

    SkinMatrix_SetScaleRotateYRPTranslate(
        &prevMatrix, colCtx->dyna.bgActors[bgId].prevTransform.scale.x,
        colCtx->dyna.bgActors[bgId].prevTransform.scale.y, colCtx->dyna.bgActors[bgId].prevTransform.scale.z,
        colCtx->dyna.bgActors[bgId].prevTransform.rot.x, colCtx->dyna.bgActors[bgId].prevTransform.rot.y,
        colCtx->dyna.bgActors[bgId].prevTransform.rot.z, colCtx->dyna.bgActors[bgId].prevTransform.pos.x,
        colCtx->dyna.bgActors[bgId].prevTransform.pos.y, colCtx->dyna.bgActors[bgId].prevTransform.pos.z);

    if (SkinMatrix_Invert(&prevMatrix, &prevMatrixInv) == 2) {
        return;
    }

    SkinMatrix_SetScaleRotateYRPTranslate(
        &currMatrix, colCtx->dyna.bgActors[bgId].curTransform.scale.x,
        colCtx->dyna.bgActors[bgId].curTransform.scale.y, colCtx->dyna.bgActors[bgId].curTransform.scale.z,
        colCtx->dyna.bgActors[bgId].curTransform.rot.x, colCtx->dyna.bgActors[bgId].curTransform.rot.y,
        colCtx->dyna.bgActors[bgId].curTransform.rot.z, colCtx->dyna.bgActors[bgId].curTransform.pos.x,
        colCtx->dyna.bgActors[bgId].curTransform.pos.y, colCtx->dyna.bgActors[bgId].curTransform.pos.z);

    SkinMatrix_Vec3fMtxFMultXYZ(&prevMatrixInv, &actor->world.pos, &posWithInv);
    SkinMatrix_Vec3fMtxFMultXYZ(&currMatrix, &posWithInv, &newPos);

    actor->world.pos = newPos;
}

void BgCheck2_UpdateActorYRotation(CollisionContext* colCtx, s32 bgId, Actor* actor) {
    s16 angleChange;

    if (DynaPoly_IsBgIdBgActor(bgId) == false) {
        return;
    }

    angleChange = colCtx->dyna.bgActors[bgId].curTransform.rot.y - colCtx->dyna.bgActors[bgId].prevTransform.rot.y;

    if (actor->id == 0) {
        ((Player*)actor)->currentYaw += angleChange;
    }

    actor->shape.rot.y += angleChange;
    actor->world.rot.y += angleChange;
}

void BgCheck2_AttachToMesh(CollisionContext* colCtx, Actor* actor, s32 bgId) {
    DynaPolyActor* meshActor;

    if (DynaPoly_IsBgIdBgActor(bgId) == false) {
        return;
    }

    meshActor = DynaPoly_GetActor(colCtx, bgId);
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

u32 BgCheck2_UpdateActorAttachedToMesh(CollisionContext* colCtx, s32 bgId, Actor* actor) {
    u32 wasUpdated = 0;
    DynaPolyActor* meshActor;

    if (DynaPoly_IsBgIdBgActor(bgId) == false) {
        return 0;
    }

    if ((colCtx->dyna.bgActorFlags[bgId] & 2) || !(colCtx->dyna.bgActorFlags[bgId] & 1)) {
        return 0;
    }

    meshActor = DynaPoly_GetActor(colCtx, bgId);

    if (meshActor == NULL) {
        return 0;
    }

    if ((meshActor->unk154 & 1) != 0) {
        BgCheck2_UpdateActorPosition(colCtx, bgId, actor);
        wasUpdated = 1;
    }

    if ((meshActor->unk154 & 2) != 0) {
        BgCheck2_UpdateActorYRotation(colCtx, bgId, actor);
        wasUpdated = 1;
    }

    return wasUpdated;
}
