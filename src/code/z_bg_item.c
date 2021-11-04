#include "global.h"

#define DYNAPOLY_STATE_NONE 0
#define DYNAPOLY_STATE_RIDING_FALLING 1 << 0
#define DYNAPOLY_STATE_RIDING_MOVING 1 << 1
#define DYNAPOLY_STATE_RIDING_ROTATING 1 << 2
#define DYNAPOLY_STATE_SWITCH_PRESSED 1 << 3
#define DYNAPOLY_STATE_HEAVY_SWITCH_PRESSED 1 << 4

void DynaPoly_Init(DynaPolyActor* dynaActor, s32 flags) {
    dynaActor->bgId = -1;
    dynaActor->pushForce = 0.0f;
    dynaActor->unk14C = 0.0f;
    dynaActor->flags = flags;
    dynaActor->stateFlags = DYNAPOLY_STATE_NONE;
}

void DynaPoly_LoadMesh(GlobalContext* globalCtx, DynaPolyActor* dynaActor, CollisionHeader* meshHeader) {
    CollisionHeader* header = NULL;
    BgCheck_RelocateMeshHeader(meshHeader, &header);
    dynaActor->bgId = BgCheck_AddActorMesh(globalCtx, &globalCtx->colCtx.dyna, dynaActor, header);
}

void DynaPoly_ResetState(DynaPolyActor* dynaActor) {
    dynaActor->stateFlags = DYNAPOLY_STATE_NONE;
}

void DynaPoly_SetRidingFallingState(DynaPolyActor* dynaActor) {
    dynaActor->stateFlags |= DYNAPOLY_STATE_RIDING_FALLING;
}

void DynaPoly_SetRidingMovingState(DynaPolyActor* dynaActor) {
    dynaActor->stateFlags |= DYNAPOLY_STATE_RIDING_MOVING;
}

void DynaPoly_SetRidingMovingStateByIndex(CollisionContext* colCtx, s32 index) {
    DynaPolyActor* dynaActor = BgCheck_GetActorOfMesh(colCtx, index);
    if (dynaActor != NULL) {
        DynaPoly_SetRidingMovingState(dynaActor);
    }
}

void DynaPoly_SetRidingRotatingState(DynaPolyActor* dynaActor) {
    dynaActor->stateFlags |= DYNAPOLY_STATE_RIDING_ROTATING;
}

void DynaPoly_SetRidingRotatingStateByIndex(CollisionContext* colCtx, s32 index) {
    DynaPolyActor* dynaActor = BgCheck_GetActorOfMesh(colCtx, index);
    if (dynaActor != NULL) {
        DynaPoly_SetRidingRotatingState(dynaActor);
    }
}

void DynaPoly_SetSwitchPressedState(DynaPolyActor* dynaActor) {
    dynaActor->stateFlags |= DYNAPOLY_STATE_SWITCH_PRESSED;
}

void DynaPoly_SetHeavySwitchPressedState(DynaPolyActor* dynaActor) {
    dynaActor->stateFlags |= DYNAPOLY_STATE_HEAVY_SWITCH_PRESSED;
}

s32 DynaPoly_IsInRidingFallingState(DynaPolyActor* dynaActor) {
    if (dynaActor->stateFlags & DYNAPOLY_STATE_RIDING_FALLING) {
        return 1;
    } else {
        return 0;
    }
}

s32 DynaPoly_IsInRidingMovingState(DynaPolyActor* dynaActor) {
    if (dynaActor->stateFlags & DYNAPOLY_STATE_RIDING_MOVING) {
        return 1;
    } else {
        return 0;
    }
}

s32 DynaPoly_IsInRidingRotatingState(DynaPolyActor* dynaActor) {
    if (dynaActor->stateFlags & DYNAPOLY_STATE_RIDING_ROTATING) {
        return 1;
    } else {
        return 0;
    }
}

s32 DynaPoly_IsInSwitchPressedState(DynaPolyActor* dynaActor) {
    if (dynaActor->stateFlags & DYNAPOLY_STATE_SWITCH_PRESSED) {
        return 1;
    } else {
        return 0;
    }
}

s32 DynaPoly_IsInHeavySwitchPressedState(DynaPolyActor* dynaActor) {
    if (dynaActor->stateFlags & DYNAPOLY_STATE_HEAVY_SWITCH_PRESSED) {
        return 1;
    } else {
        return 0;
    }
}

s32 DynaPoly_ValidateMove(GlobalContext* globalCtx, DynaPolyActor* dynaActor, s16 startRadius, s16 endRadius,
                          s16 startHeight) {
    Vec3f startPos;
    Vec3f endPos;
    Vec3f intersectionPos;
    f32 sin = Math_SinS(dynaActor->yRotation);
    f32 cos = Math_CosS(dynaActor->yRotation);
    s32 bgId;
    CollisionPoly* poly;
    f32 adjustedStartRadius;
    f32 adjustedEndRadius;
    f32 sign = (0.0f <= dynaActor->pushForce) ? 1.0f : -1.0f;

    adjustedStartRadius = (f32)startRadius - 0.1f;
    startPos.x = dynaActor->actor.world.pos.x + (adjustedStartRadius * cos);
    startPos.y = dynaActor->actor.world.pos.y + startHeight;
    startPos.z = dynaActor->actor.world.pos.z - (adjustedStartRadius * sin);

    adjustedEndRadius = (f32)endRadius - 0.1f;
    endPos.x = sign * adjustedEndRadius * sin + startPos.x;
    endPos.y = startPos.y;
    endPos.z = sign * adjustedEndRadius * cos + startPos.z;

    if (func_800C56E0(&globalCtx->colCtx, &startPos, &endPos, &intersectionPos, &poly, true, false, false, true, &bgId,
                      &dynaActor->actor, 0.0f)) {
        return false;
    }
    startPos.x = (dynaActor->actor.world.pos.x * 2.0f) - startPos.x;
    startPos.z = (dynaActor->actor.world.pos.z * 2.0f) - startPos.z;
    endPos.x = sign * adjustedEndRadius * sin + startPos.x;
    endPos.z = sign * adjustedEndRadius * cos + startPos.z;
    if (func_800C56E0(&globalCtx->colCtx, &startPos, &endPos, &intersectionPos, &poly, true, false, false, true, &bgId,
                      &dynaActor->actor, 0.0f)) {
        return false;
    }
    return true;
}
