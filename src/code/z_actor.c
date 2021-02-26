#include <ultra64.h>
#include <global.h>

// From OOT
#define ABS(x) ((x) < 0 ? -(x) : (x))
#define DECR(x) ((x) == 0 ? 0 : ((x) -= 1))

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//Actor_PrintLists.asm")

void Actor_SetDrawParams(ActorShape* actorShape, f32 yOffset, ActorShadowFunc func, f32 scale) {
    actorShape->yOffset = yOffset;
    actorShape->shadowDraw = func;
    actorShape->shadowScale = scale;
    actorShape->shadowAlpha = 255;
}

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//Actor_PostDraw.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B3FC0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B4024.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B4088.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B40B8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B40E0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B42F8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B4A98.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B4AEC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B4B50.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B4EDC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B4F40.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B4F78.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B5040.asm")

void Actor_TargetContextInit(TargetContext* targetCtxt, Actor* actor, GlobalContext* ctxt) {
    targetCtxt->unk90 = NULL;
    targetCtxt->unk8C = NULL;
    targetCtxt->unk3C = NULL;
    targetCtxt->unk38 = NULL;
    targetCtxt->unk4B = 0;
    targetCtxt->unk4C = 0;
    targetCtxt->unk40 = 0;
    func_800B5040(targetCtxt, actor, actor->category, ctxt);
    func_800B4F78(targetCtxt, actor->category, ctxt);
}

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B5208.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B5814.asm")

u32 Actor_GetSwitchFlag(GlobalContext* ctxt, s32 flag) {
    if (flag >= 0 && flag < 0x80) {
        return ctxt->actorCtx.switchFlags[(flag & -0x20) >> 5] & (1 << (flag & 0x1F));
    }
    return 0;
}

void Actor_SetSwitchFlag(GlobalContext* ctxt, s32 flag) {
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

void Actor_TitleCardCreate(GlobalContext* ctxt, TitleCardContext* titleCtxt, u32 texture, s16 param_4, s16 param_5,
                           u8 param_6, u8 param_7) {
    titleCtxt->texture = texture;
    titleCtxt->unk4 = param_4;
    titleCtxt->unk6 = param_5;
    titleCtxt->unk8 = param_6;
    titleCtxt->unk9 = param_7;
    titleCtxt->fadeOutDelay = 80;
    titleCtxt->fadeInDelay = 0;
}

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//Actor_Nop800B5E50.asm")

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

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//Actor_TitleCardDraw.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B6434.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B6468.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B6474.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B648C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B64FC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B6584.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B6608.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B6680.asm")

void Actor_MarkForDeath(Actor* actor) {
    actor->draw = NULL;
    actor->update = NULL;
    actor->flags &= ~0x1;
}

void Actor_InitCurrPosition(Actor* actor) {
    actor->world = actor->home;
}

void Actor_SetHeight(Actor* actor, f32 height) {
    actor->focus.pos.x = actor->world.pos.x;
    actor->focus.pos.y = actor->world.pos.y + height;
    actor->focus.pos.z = actor->world.pos.z;
    actor->focus.rot.x = actor->world.rot.x;
    actor->focus.rot.y = actor->world.rot.y;
    actor->focus.rot.z = actor->world.rot.z;
}

void Actor_SetRotationFromDrawRotation(Actor* actor) {
    actor->world.rot = actor->shape.rot;
}

void Actor_InitDrawRotation(Actor* actor) {
    actor->shape.rot = actor->world.rot;
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
    Math_Vec3f_Copy(&actor->prevPos, &actor->world.pos);
    Actor_SetScale(actor, 0.01);
    actor->targetMode = 3;
    actor->minYVelocity = -20.0f;

    actor->meshAttachedTo = 0x32;

    actor->sqrdDistToLink = D_801DCA54;
    func_800E7494(&actor->colChkInfo);
    actor->uncullZoneForward = 1000.0f;
    actor->uncullZoneScale = 350.0f;
    actor->uncullZoneDownward = 700.0f;

    actor->naviMsgId = 255;

    Actor_Setshape(&actor->shape, 0, 0, 0);
    if (Scene_IsObjectLoaded(&ctxt->sceneContext, actor->objBankIndex) != 0) {
        Actor_SetObjectSegment(ctxt, actor);
        actor->init(actor, ctxt);
        actor->init = NULL;
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/z_actor//Actor_InitToDefaultValues.asm")
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
    actor->world.pos.x += ((actor->velocity.x * actorMovementScale) + actor->colChkInfo.displacement.x);
    actor->world.pos.y += ((actor->velocity.y * actorMovementScale) + actor->colChkInfo.displacement.y);
    actor->world.pos.z += ((actor->velocity.z * actorMovementScale) + actor->colChkInfo.displacement.z);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/z_actor//Actor_ApplyMovement.asm")
#endif

#ifdef NON_MATCHING
void Actor_SetVelocityYRotationAndGravity(Actor* actor) {
    actor->velocity.x = actor->speedXZ * Math_Sins(actor->world.rot.x);
    actor->velocity.y = actor->velocity.y + actor->gravity;
    actor->velocity.z = actor->speedXZ * Math_Coss(actor->world.rot.x);

    if (actor->velocity.y < actor->minYVelocity) {
        actor->velocity.y = actor->minYVelocity;
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/z_actor//Actor_SetVelocityYRotationAndGravity.asm")
#endif

void Actor_SetVelocityAndMoveYRotationAndGravity(Actor* actor) {
    Actor_SetVelocityYRotationAndGravity(actor);
    Actor_ApplyMovement(actor);
}

void Actor_SetVelocityXYRotation(Actor* actor) {
    f32 velX = Math_Coss(actor->world.rot.x) * actor->speedXZ;
    actor->velocity.x = Math_Sins(actor->world.rot.y) * velX;
    actor->velocity.y = Math_Sins(actor->world.rot.x) * actor->speedXZ;
    actor->velocity.z = Math_Coss(actor->world.rot.y) * velX;
}

void Actor_SetVelocityAndMoveXYRotation(Actor* actor) {
    Actor_SetVelocityXYRotation(actor);
    Actor_ApplyMovement(actor);
}

void Actor_SetVelocityXYRotationReverse(Actor* actor) {
    f32 velX = Math_Coss(-actor->world.rot.x) * actor->speedXZ;
    actor->velocity.x = Math_Sins(actor->world.rot.y) * velX;
    actor->velocity.y = Math_Sins(-actor->world.rot.x) * actor->speedXZ;
    actor->velocity.z = Math_Coss(actor->world.rot.y) * velX;
}

void Actor_SetVelocityAndMoveXYRotationReverse(Actor* actor) {
    Actor_SetVelocityXYRotationReverse(actor);
    Actor_ApplyMovement(actor);
}

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B6C04.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B6C58.asm")

s16 Actor_YawBetweenActors(Actor* from, Actor* to) {
    return Math_Vec3f_Yaw(&from->world.pos, &to->world.pos);
}

s16 Actor_YawBetweenActorsTop(Actor* from, Actor* to) {
    return Math_Vec3f_Yaw(&from->focus.pos, &to->focus.pos);
}

s16 Actor_YawToPoint(Actor* actor, Vec3f* point) {
    return Math_Vec3f_Yaw(&actor->world.pos, point);
}

s16 Actor_PitchBetweenActors(Actor* from, Actor* to) {
    return Math_Vec3f_Pitch(&from->world.pos, &to->world.pos);
}

s16 Actor_PitchBetweenActorsTop(Actor* from, Actor* to) {
    return Math_Vec3f_Pitch(&from->focus.pos, &to->focus.pos);
}

s16 Actor_PitchToPoint(Actor* actor, Vec3f* point) {
    return Math_Vec3f_Pitch(&actor->world.pos, point);
}

f32 Actor_DistanceBetweenActors(Actor* actor1, Actor* actor2) {
    return Math_Vec3f_DistXYZ(&actor1->world.pos, &actor2->world.pos);
}

f32 Actor_DistanceToPoint(Actor* actor, Vec3f* point) {
    return Math_Vec3f_DistXYZ(&actor->world.pos, point);
}

f32 Actor_XZDistanceBetweenActors(Actor* actor1, Actor* actor2) {
    return Math_Vec3f_DistXZ(&actor1->world.pos, &actor2->world.pos);
}

f32 Actor_XZDistanceToPoint(Actor* actor, Vec3f* point) {
    return Math_Vec3f_DistXZ(&actor->world.pos, point);
}

void Actor_CalcOffsetOrientedToDrawRotation(Actor* actor, Vec3f* offset, Vec3f* point) {
    f32 cos_rot_y;
    f32 sin_rot_y;
    f32 imm_x;
    f32 imm_z;

    cos_rot_y = Math_Coss(actor->shape.rot.y);
    sin_rot_y = Math_Sins(actor->shape.rot.y);
    imm_x = point->x - actor->world.pos.x;
    imm_z = point->z - actor->world.pos.z;
    offset->x = ((imm_x * cos_rot_y) - (imm_z * sin_rot_y));
    offset->z = ((imm_z * cos_rot_y) + (imm_x * sin_rot_y));
    offset->y = point->y - actor->world.pos.y;
}

f32 Actor_YDistance(Actor* actor1, Actor* actor2) {
    return actor2->world.pos.y - actor1->world.pos.y;
}

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B6F20.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B6FC8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B7090.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B7118.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B7128.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B715C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B7170.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B71DC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B7200.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B722C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B724C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B7298.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B72E0.asm")

void func_800B72F8(DynaPolyActor* dpactor, f32 a1, s16 a2) {
    dpactor->unk150 = a2;
    dpactor->unk148 += a1;
}

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//Actor_IsLinkFacingActor.asm")

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

    dist = actor->yawTowardsPlayer - actor->shape.rot.y;
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

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//Actor_IsActorFacingLinkAndWithinRange.asm")

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

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B75A0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B761C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B7678.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B78B8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B7E04.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B7FE0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8018.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8050.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8118.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B81E0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8214.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8248.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B82EC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B83BC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B83F8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B84D0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8500.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B85E0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8614.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B863C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B867C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B86C8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8708.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8718.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B874C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8804.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B882C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B886C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8898.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8934.asm")

u32 Actor_HasParent(Actor* actor, GlobalContext* ctxt) {
    if (actor->parent != NULL) {
        return 1;
    } else {
        return 0;
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8A1C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8B84.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8BB0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8BD0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8BFC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8C20.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8C50.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8C78.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8C9C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8CEC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8D10.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8D50.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8D98.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8DD4.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8E1C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8E58.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8EC8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8EF4.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8F98.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8FC0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B8FE8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B9010.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B9038.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B9084.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B9098.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B90AC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B90F4.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B9120.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//Actor_Init.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B9334.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//Actor_UpdateActor.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//Actor_UpdateAll.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//Actor_DrawActor.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B9D1C.asm")

void Actor_DrawAllSetup(GlobalContext* ctxt) {
    ctxt->actorCtx.undrawnActorCount = 0;
    ctxt->actorCtx.unkB = 0;
}

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//Actor_RecordUndrawnActor.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B9E84.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800B9EF4.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BA2D8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BA2FC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//Actor_DrawAll.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BA6FC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BA798.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BA8B8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BA9B4.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//Actor_InsertIntoTypeList.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//Actor_RemoveFromTypeList.asm")

void Actor_FreeOverlay(ActorOverlay* entry) {
    void* ramAddr;

    if (entry->nbLoaded == 0) {
        ramAddr = entry->loadedRamAddr;
        if (ramAddr != NULL) {
            // Bit 1 - always loaded
            if ((entry->allocType & 2) == 0) {
                // Bit 0 - don't alloc memory
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

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//Actor_Spawn.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//Actor_LoadOverlay.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//Actor_SpawnWithParentAndCutscene.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//Actor_SpawnWithParent.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//Actor_SpawnTransitionActors.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BB2D0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BB498.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BB59C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BB604.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BB8EC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BBA88.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BBAC0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BBB74.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BBC20.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BBCEC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BBDAC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BBFB0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BC154.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BC188.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BC1B4.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BC270.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BC444.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BC4EC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BC5B8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BC5EC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BC620.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BC770.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BC7D8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BC848.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BC8B8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BCB50.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BCB70.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BCBF4.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BCC68.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BCCDC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BD2B4.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BD384.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BD6B8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BD6E4.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BD888.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BD9A0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BD9E0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BDAA0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BDB6C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BDC5C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BDCF4.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BDFB0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BDFC0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BE03C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BE0B8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BE184.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BE22C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BE258.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BE2B8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BE33C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BE3D0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BE504.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BE568.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BE5CC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BE63C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BE680.asm")

#pragma GLOBAL_ASM("asm/non_matchings/z_actor//func_800BF7CC.asm")
