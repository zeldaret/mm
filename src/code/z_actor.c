#include <ultra64.h>
#include <global.h>

//From OOT
#define ABS(x) ((x) < 0 ? -(x) : (x))
#define DECR(x) ((x) == 0 ? 0 : ((x) -= 1))

GLOBAL_ASM("asm/non_matchings/z_actor//Actor_PrintLists.asm")

void Actor_SetDrawParams(ActorShape* iParm1, f32 yDisplacement, actor_shadow_draw_func func, f32 scale) {
    iParm1->yDisplacement = yDisplacement;
    iParm1->shadowDrawFunc = func;
    iParm1->scale = scale;
    iParm1->alphaScale = 255;
}

GLOBAL_ASM("asm/non_matchings/z_actor//Actor_PostDraw.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B3FC0.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B4024.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B4088.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B40B8.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B40E0.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B42F8.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B4A98.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B4AEC.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B4B50.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B4EDC.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B4F40.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B4F78.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B5040.asm")

void Actor_TargetContextInit(TargetContext* targetCtxt, Actor* actor, GlobalContext* ctxt) {
    targetCtxt->unk90 = NULL;
    targetCtxt->unk8C = NULL;
    targetCtxt->unk3C = NULL;
    targetCtxt->unk38 = NULL;
    targetCtxt->unk4B = 0;
    targetCtxt->unk4C = 0;
    targetCtxt->unk40 = 0;
    func_800B5040(targetCtxt, actor, actor->type, ctxt);
    func_800B4F78(targetCtxt, actor->type, ctxt);
}

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B5208.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B5814.asm")

u32 Actor_GetSwitchFlag(GlobalContext* ctxt, s32 flag) {
    if (flag >= 0 && flag < 0x80) {
        return ctxt->actorCtx.switchFlags[(flag & -0x20) >> 5] & (1 << (flag & 0x1F));
    }
    return 0;
}

void Actor_SetSwitchFlag(GlobalContext* ctxt, s32 flag){
    if (flag >= 0 && flag < 0x80) {
        ctxt->actorCtx.switchFlags[(flag & -0x20) >> 5] |= 1 << (flag & 0x1F);
    }
}

void Actor_UnsetSwitchFlag(GlobalContext* ctxt, s32 flag) {
    if (flag >= 0 && flag < 0x80) {
        ctxt->actorCtx.switchFlags[(flag & -0x20) >> 5] &= ~(1 << (flag & 0x1F));
    }
}

u32 Actor_GetChestFlag(GlobalContext* ctxt, u32 flag) {
    return ctxt->actorCtx.chestFlags & (1 << flag);
}

void Actor_SetChestFlag(GlobalContext* ctxt, u32 flag) {
    ctxt->actorCtx.chestFlags |= (1 << flag);
}

void Actor_SetAllChestFlag(GlobalContext* ctxt, u32 flag) {
    ctxt->actorCtx.chestFlags = flag;
}

u32 Actor_GetAllChestFlag(GlobalContext* ctxt) {
    return ctxt->actorCtx.chestFlags;
}

u32 Actor_GetRoomCleared(GlobalContext* ctxt, u32 roomNumber) {
    return ctxt->actorCtx.clearedRooms & (1 << roomNumber);
}

void Actor_SetRoomCleared(GlobalContext* ctxt, u32 roomNumber) {
    ctxt->actorCtx.clearedRooms |= (1 << roomNumber);
}

void Actor_UnsetRoomCleared(GlobalContext* ctxt, u32 roomNumber) {
    ctxt->actorCtx.clearedRooms &= ~(1 << roomNumber);
}

u32 Actor_GetRoomClearedTemp(GlobalContext* ctxt, u32 roomNumber) {
    return ctxt->actorCtx.clearedRoomsTemp & (1 << roomNumber);
}

void Actor_SetRoomClearedTemp(GlobalContext* ctxt, u32 roomNumber) {
    ctxt->actorCtx.clearedRoomsTemp |= (1 << roomNumber);
}

void Actor_UnsetRoomClearedTemp(GlobalContext* ctxt, u32 roomNumber) {
    ctxt->actorCtx.clearedRoomsTemp &= ~(1 << roomNumber);
}

u32 Actor_GetCollectibleFlag(GlobalContext* ctxt, s32 index) {
    if (index > 0 && index < 0x80) {
        return ctxt->actorCtx.collectibleFlags[(index & -0x20) >> 5] & (1 << (index & 0x1F));
    }
    return 0;
}

void Actor_SetCollectibleFlag(GlobalContext* ctxt, s32 index) {
    if (index > 0 && index < 0x80) {
        ctxt->actorCtx.collectibleFlags[(index & -0x20) >> 5] |= 1 << (index & 0x1F);
    }
}

void Actor_TitleCardContextInit(GlobalContext* ctxt, TitleCardContext* titleCtxt) {
    titleCtxt->fadeOutDelay = 0;
    titleCtxt->fadeInDelay = 0;
    titleCtxt->color = 0;
    titleCtxt->alpha = 0;
}

void Actor_TitleCardCreate(GlobalContext* ctxt, TitleCardContext* titleCtxt, u32 texture, s16 param_4, s16 param_5, u8 param_6, u8 param_7) {
    titleCtxt->texture = texture;
    titleCtxt->unk4 = param_4;
    titleCtxt->unk6 = param_5;
    titleCtxt->unk8 = param_6;
    titleCtxt->unk9 = param_7;
    titleCtxt->fadeOutDelay = 80;
    titleCtxt->fadeInDelay = 0;
}

GLOBAL_ASM("asm/non_matchings/z_actor//Actor_Nop800B5E50.asm")

void Actor_TitleCardUpdate(GlobalContext* ctxt, TitleCardContext* titleCtxt) {
    if (DECR(titleCtxt->fadeInDelay) == 0) {
        if (DECR(titleCtxt->fadeOutDelay) == 0) {
            Lib_StepTowardsCheck_s(&titleCtxt->alpha, 0, 30);
            Lib_StepTowardsCheck_s(&titleCtxt->color, 0, 70);
        } else {
            Lib_StepTowardsCheck_s(&titleCtxt->alpha, 255, 10);
            Lib_StepTowardsCheck_s(&titleCtxt->color, 255, 20);
        }
    }
}

GLOBAL_ASM("asm/non_matchings/z_actor//Actor_TitleCardDraw.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B6434.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B645C.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B6468.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B6474.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B648C.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B64FC.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B6584.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B6608.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B6680.asm")

void Actor_MarkForDeath(Actor* actor) {
    actor->draw = NULL;
    actor->update = NULL;
    actor->flags &= ~0x1;
}

void Actor_InitCurrPosition(Actor* actor) {
    actor->currPosRot = actor->initPosRot;
}

void Actor_SetHeight(Actor* actor, f32 height) {
    actor->topPosRot.pos.x = actor->currPosRot.pos.x;
    actor->topPosRot.pos.y = actor->currPosRot.pos.y + height;
    actor->topPosRot.pos.z = actor->currPosRot.pos.z;
    actor->topPosRot.rot.x = actor->currPosRot.rot.x;
    actor->topPosRot.rot.y = actor->currPosRot.rot.y;
    actor->topPosRot.rot.z = actor->currPosRot.rot.z;
}

void Actor_SetRotationFromDrawRotation(Actor* actor) {
    actor->currPosRot.rot = actor->shape.rot;
}

void Actor_InitDrawRotation(Actor* actor) {
    actor->shape.rot = actor->currPosRot.rot;
}

void Actor_SetScale(Actor* actor, f32 scale) {
    actor->scale.z = scale;
    actor->scale.y = scale;
    actor->scale.x = scale;
}

void Actor_SetObjectSegment(GlobalContext* ctxt, Actor* actor) {
    // TODO: Segment number enum
    gRspSegmentPhysAddrs[6] = PHYSICAL_TO_VIRTUAL(ctxt->sceneContext.objects[actor->objBankIndex].vramAddr);
}

#ifdef NON_MATCHING
void Actor_InitToDefaultValues(Actor* actor, GlobalContext* ctxt) {
    Actor_InitCurrPosition(actor);
    Actor_InitDrawRotation(actor);
    Actor_SetHeight(actor, 0);
    Math_Vec3f_Copy(&actor->lastPos, &actor->currPosRot.pos);
    Actor_SetScale(actor, 0.01);
    actor->unk1F = 3;
    actor->minYVelocity = -20.0f;

    actor->meshAttachedTo = 0x32;

    actor->sqrdDistToLink = D_801DCA54;
    func_800E7494(&actor->unkA0);
    actor->unkFC = 1000.0f;
    actor->unk100 = 350.0f;
    actor->unk104 = 700.0f;

    actor->naviMsgId = 255;

    Actor_Setshape(&actor->shape, 0, 0, 0);
    if (Scene_IsObjectLoaded(&ctxt->sceneContext, actor->objBankIndex) != 0) {
        Actor_SetObjectSegment(ctxt, actor);
        actor->init(actor, ctxt);
        actor->init = NULL;
    }
}
#else
GLOBAL_ASM("asm/non_matchings/z_actor//Actor_InitToDefaultValues.asm")
#endif

void Actor_FiniActor(Actor* actor, GlobalContext* ctxt) {
    if (actor->init == NULL) {
        if (actor->destroy != NULL) {
            actor->destroy(actor, ctxt);
            actor->destroy = NULL;
        }
    }
}

void Actor_SetMovementScale(s32 scale) {
    actorMovementScale = scale * 0.5f;
}

#ifdef NON_MATCHING
void Actor_ApplyMovement(Actor* actor) {
    actor->currPosRot.pos.x += ((actor->velocity.x * actorMovementScale) + actor->unkA0.displacement.x);
    actor->currPosRot.pos.y += ((actor->velocity.y * actorMovementScale) + actor->unkA0.displacement.y);
    actor->currPosRot.pos.z += ((actor->velocity.z * actorMovementScale) + actor->unkA0.displacement.z);
}
#else
GLOBAL_ASM("asm/non_matchings/z_actor//Actor_ApplyMovement.asm")
#endif

#ifdef NON_MATCHING
void Actor_SetVelocityYRotationAndGravity(Actor* actor) {
    actor->velocity.x = actor->speedXZ * Math_Sins(actor->currPosRot.rot.x);
    actor->velocity.y = actor->velocity.y + actor->gravity;
    actor->velocity.z = actor->speedXZ * Math_Coss(actor->currPosRot.rot.x);

    if (actor->velocity.y < actor->minYVelocity) {
        actor->velocity.y = actor->minYVelocity;
    }
}
#else
GLOBAL_ASM("asm/non_matchings/z_actor//Actor_SetVelocityYRotationAndGravity.asm")
#endif

void Actor_SetVelocityAndMoveYRotationAndGravity(Actor* actor) {
    Actor_SetVelocityYRotationAndGravity(actor);
    Actor_ApplyMovement(actor);
}

void Actor_SetVelocityXYRotation(Actor* actor) {
    f32 velX =  Math_Coss(actor->currPosRot.rot.x) * actor->speedXZ;
    actor->velocity.x = Math_Sins(actor->currPosRot.rot.y) * velX;
    actor->velocity.y = Math_Sins(actor->currPosRot.rot.x) * actor->speedXZ;
    actor->velocity.z = Math_Coss(actor->currPosRot.rot.y) * velX;
}

void Actor_SetVelocityAndMoveXYRotation(Actor* actor) {
    Actor_SetVelocityXYRotation(actor);
    Actor_ApplyMovement(actor);
}

void Actor_SetVelocityXYRotationReverse(Actor* actor) {
    f32 velX =  Math_Coss(-actor->currPosRot.rot.x) * actor->speedXZ;
    actor->velocity.x = Math_Sins(actor->currPosRot.rot.y) * velX;
    actor->velocity.y = Math_Sins(-actor->currPosRot.rot.x) * actor->speedXZ;
    actor->velocity.z = Math_Coss(actor->currPosRot.rot.y) * velX;
}

void Actor_SetVelocityAndMoveXYRotationReverse(Actor* actor) {
    Actor_SetVelocityXYRotationReverse(actor);
    Actor_ApplyMovement(actor);
}

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B6C04.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B6C58.asm")

s16 Actor_YawBetweenActors(Actor* from, Actor* to) {
    return Math_Vec3f_Yaw(&from->currPosRot.pos, &to->currPosRot.pos);
}

s16 Actor_YawBetweenActorsTop(Actor* from, Actor* to) {
    return Math_Vec3f_Yaw(&from->topPosRot.pos, &to->topPosRot.pos);
}

s16 Actor_YawToPoint(Actor* actor, Vec3f* point) {
    return Math_Vec3f_Yaw(&actor->currPosRot.pos, point);
}

s16 Actor_PitchBetweenActors(Actor* from, Actor* to) {
    return Math_Vec3f_Pitch(&from->currPosRot.pos, &to->currPosRot.pos);
}

s16 Actor_PitchBetweenActorsTop(Actor* from, Actor* to) {
    return Math_Vec3f_Pitch(&from->topPosRot.pos, &to->topPosRot.pos);
}

s16 Actor_PitchToPoint(Actor* actor, Vec3f* point) {
    return Math_Vec3f_Pitch(&actor->currPosRot.pos, point);
}

f32 Actor_DistanceBetweenActors(Actor* actor1, Actor* actor2) {
    return Math_Vec3f_DistXYZ(&actor1->currPosRot.pos, &actor2->currPosRot.pos);
}

f32 Actor_DistanceToPoint(Actor* actor, Vec3f* point) {
    return Math_Vec3f_DistXYZ(&actor->currPosRot.pos, point);
}

f32 Actor_XZDistanceBetweenActors(Actor* actor1, Actor* actor2) {
    return Math_Vec3f_DistXZ(&actor1->currPosRot.pos, &actor2->currPosRot.pos);
}

f32 Actor_XZDistanceToPoint(Actor* actor, Vec3f* point) {
    return Math_Vec3f_DistXZ(&actor->currPosRot.pos, point);
}

void Actor_CalcOffsetOrientedToDrawRotation(Actor* actor, Vec3f* offset, Vec3f* point) {
    f32 cos_rot_y;
    f32 sin_rot_y;
    f32 imm_x;
    f32 imm_z;
    
    cos_rot_y = Math_Coss(actor->shape.rot.y);
    sin_rot_y = Math_Sins(actor->shape.rot.y);
    imm_x = point->x - actor->currPosRot.pos.x;
    imm_z = point->z - actor->currPosRot.pos.z;
    offset->x = ((imm_x * cos_rot_y) - (imm_z * sin_rot_y));
    offset->z = ((imm_z * cos_rot_y) + (imm_x * sin_rot_y));
    offset->y = point->y - actor->currPosRot.pos.y;
}

f32 Actor_YDistance(Actor* actor1, Actor* actor2) {
    return actor2->currPosRot.pos.y - actor1->currPosRot.pos.y;
}

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B6F20.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B6FC8.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B7090.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B7118.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B7128.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B715C.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B7170.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B71DC.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B7200.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B722C.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B724C.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B7298.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B72E0.asm")

void func_800B72F8(DynaPolyActor* dpactor, f32 a1, s16 a2) {
    dpactor->unk150 = a2;
    dpactor->unk148 += a1;
}

GLOBAL_ASM("asm/non_matchings/z_actor//Actor_IsLinkFacingActor.asm")

s32 Actor_IsActorFacedByActor(Actor* actor, Actor* other, s16 tolerance) {
    s16 angle;
    s16 dist;

    angle = Actor_YawBetweenActors(actor, other) + 0x8000;
    dist = angle - other->shape.rot.y;
    if (ABS(dist) < tolerance) {
        return 1;
    }
    return 0;
}

s32 Actor_IsActorFacingLink(Actor* actor, s16 angle) {
    s16 dist;

    dist = actor->rotTowardsLinkY - actor->shape.rot.y;
    if (ABS(dist) < angle) {
        return 1;
    }
    return 0;
}

s32 Actor_IsActorFacingActor(Actor* actor, Actor* other, s16 tolerance) {
    s16 dist;

    dist = Actor_YawBetweenActors(actor, other) - actor->shape.rot.y;
    if (ABS(dist) < tolerance) {
        return 1;
    }
    return 0;
}

GLOBAL_ASM("asm/non_matchings/z_actor//Actor_IsActorFacingLinkAndWithinRange.asm")

s32 Actor_IsActorFacingActorAndWithinRange(Actor* actor, Actor* other, f32 range, s16 tolerance) {
    s16 dist;

    if (Actor_DistanceBetweenActors(actor, other) < range) {
        dist = Actor_YawBetweenActors(actor, other) - actor->shape.rot.y;
        if (ABS(dist) < tolerance) {
            return 1;
        }
    }
    return 0;
}

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B75A0.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B761C.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B7678.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B78B8.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B7E04.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B7FE0.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8018.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8050.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8118.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B81E0.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8214.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8248.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B82EC.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B83BC.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B83F8.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B84D0.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8500.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B85E0.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8614.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B863C.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B867C.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B86C8.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8708.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8718.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B874C.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8804.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B882C.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B886C.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8898.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8934.asm")

u32 Actor_HasParent(Actor* actor, GlobalContext* ctxt) {
    if (actor->parent != NULL) {
        return 1;
    } else {
        return 0;
    }
}

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8A1C.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8B84.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8BB0.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8BD0.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8BFC.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8C20.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8C50.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8C78.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8C9C.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8CEC.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8D10.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8D50.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8D98.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8DD4.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8E1C.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8E58.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8EC8.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8EF4.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8F98.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8FC0.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8FE8.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B9010.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B9038.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B9084.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B9098.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B90AC.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B90F4.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B9120.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//Actor_Init.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B9334.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//Actor_UpdateActor.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//Actor_UpdateAll.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//Actor_DrawActor.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B9D1C.asm")

void Actor_DrawAllSetup(GlobalContext* ctxt) {
    ctxt->actorCtx.undrawnActorCount = 0;
    ctxt->actorCtx.unkB = 0;
}

GLOBAL_ASM("asm/non_matchings/z_actor//Actor_RecordUndrawnActor.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B9E84.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800B9EF4.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BA2D8.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BA2FC.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//Actor_DrawAll.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BA6FC.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BA798.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BA8B8.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BA9B4.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//Actor_InsertIntoTypeList.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//Actor_RemoveFromTypeList.asm")

void Actor_FreeOverlay(ActorOverlay* entry) {
    void* ramAddr;

    if (entry->nbLoaded == 0) {
        ramAddr = entry->loadedRamAddr;
        if (ramAddr != NULL) {
            //Bit 1 - always loaded
            if ((entry->allocType & 2) == 0) {
                //Bit 0 - don't alloc memory
                if ((entry->allocType & 1) != 0) {
                    entry->loadedRamAddr = NULL;
                } else {
                    zelda_free(ramAddr);
                    entry->loadedRamAddr = NULL;
                }
            }
        }
    }
}

GLOBAL_ASM("asm/non_matchings/z_actor//Actor_Spawn.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//Actor_LoadOverlay.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//Actor_SpawnWithParentAndCutscene.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//Actor_SpawnWithParent.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//Actor_SpawnTransitionActors.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BB2D0.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BB498.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BB59C.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BB604.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BB8EC.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BBA88.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BBAC0.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BBB74.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BBC20.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BBCEC.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BBDAC.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BBFB0.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BC154.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BC188.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BC1B4.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BC270.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BC444.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BC4EC.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BC5B8.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BC5EC.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BC620.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BC770.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BC7D8.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BC848.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BC8B8.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BCB50.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BCB70.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BCBF4.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BCC68.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BCCDC.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BD2B4.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BD384.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BD6E4.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BD888.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BD9A0.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BD9E0.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BDAA0.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BDB6C.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BDC5C.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BDCF4.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BDFB0.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BDFC0.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BE03C.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BE0B8.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BE184.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BE22C.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BE258.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BE2B8.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BE33C.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BE3D0.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BE504.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BE568.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BE5CC.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BE63C.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BE680.asm")

GLOBAL_ASM("asm/non_matchings/z_actor//func_800BF7CC.asm")
