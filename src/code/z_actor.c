#include "global.h"

void Actor_PrintLists(ActorContext* actorCtx) {
    ActorListEntry* actorList = &actorCtx->actorList[0];
    Actor* actor;
    s32 i;

    FaultDrawer_SetCharPad(-2, 0);
    FaultDrawer_Printf("actor\n", gMaxActorId);
    FaultDrawer_Printf("No. Actor   Name Part SegName\n");

    for (i = 0; i < ARRAY_COUNT(actorCtx->actorList); i++) {
        actor = actorList[i].first;

        while (actor != NULL) {
            FaultDrawer_Printf("%3d %08x %04x %3d %s\n", i, actor, actor->id, actor->category, "");
            actor = actor->next;
        }
    }
}

void ActorShape_Init(ActorShape* actorShape, f32 yOffset, ActorShadowFunc shadowDraw, f32 shadowScale) {
    actorShape->yOffset = yOffset;
    actorShape->shadowDraw = shadowDraw;
    actorShape->shadowScale = shadowScale;
    actorShape->shadowAlpha = 255;
}

#ifdef NON_MATCHING
void ActorShadow_Draw(Actor* actor, Lights* lights, GlobalContext* globalCtx, Gfx* dlist, Color_RGBA8* color) {
    if (actor->floorPoly != NULL) {
        f32 dy = actor->world.pos.y - actor->floorHeight;

        if (dy >= -50.0f && dy < 500.0f) {
            f32 shadowScale;
            MtxF mtx;

            OPEN_DISPS(globalCtx->state.gfxCtx);

            POLY_OPA_DISP = Gfx_CallSetupDL(POLY_OPA_DISP, 0x2C);

            gDPSetCombineLERP(POLY_OPA_DISP++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0,
                              COMBINED);

            dy = CLAMP(dy, 0.0f, 150.0f);
            shadowScale = 1.0f - (dy * 0.0028571428f);

            if (color != NULL) {
                gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, color->r, color->g, color->b,
                                (u8)(actor->shape.shadowAlpha * shadowScale));
            } else {
                gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 0, 0, 0, (u8)(actor->shape.shadowAlpha * shadowScale));
            }

            func_800C0094(actor->floorPoly, actor->world.pos.x, actor->floorHeight, actor->world.pos.z, &mtx);
            SysMatrix_SetCurrentState(&mtx);

            if (dlist != D_04076BC0) {
                Matrix_RotateY((f32)actor->shape.rot.y * (M_PI / 32768), MTXMODE_APPLY);
            }

            shadowScale = 1.0f - (dy * 0.0028571428f);
            shadowScale *= actor->shape.shadowScale;
            Matrix_Scale(shadowScale * actor->scale.x, 1.0f, shadowScale * actor->scale.z, MTXMODE_APPLY);

            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_MODELVIEW | G_MTX_LOAD);
            gSPDisplayList(POLY_OPA_DISP++, dlist);

            CLOSE_DISPS(globalCtx->state.gfxCtx);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/ActorShadow_Draw.s")
#endif

/* ActorShadow_DrawCircle */
void func_800B3FC0(Actor* actor, Lights* lights, GlobalContext* globalCtx) {
    if (actor->bgCheckFlags & 0x400) {
        func_800B4AEC(globalCtx, actor, 50.0f);
    }

    ActorShadow_Draw(actor, lights, globalCtx, D_04076BC0, NULL);
}

/* ActorShadow_DrawSquare */
void func_800B4024(Actor* actor, Lights* lights, GlobalContext* globalCtx) {
    if (actor->bgCheckFlags & 0x400) {
        func_800B4AEC(globalCtx, actor, 50.0f);
    }

    ActorShadow_Draw(actor, lights, globalCtx, D_04075A40, NULL);
}

/* ActorShadow_DrawWhiteCircle */
void func_800B4088(Actor* actor, Lights* lights, GlobalContext* globalCtx) {
    ActorShadow_Draw(actor, lights, globalCtx, D_04076BC0, &D_801AEC80);
}

/* ActorShadow_DrawHorse */
void func_800B40B8(Actor* actor, Lights* lights, GlobalContext* globalCtx) {
    ActorShadow_Draw(actor, lights, globalCtx, D_04077480, NULL);
}

/* ActorShadow_DrawFoot */
#ifdef NON_MATCHING
void func_800B40E0(GlobalContext* globalCtx, Light* light, MtxF* arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    s32 pad1;
    s16 sp58;
    s32 pad2[2];

    OPEN_DISPS(globalCtx->state.gfxCtx);

    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 0, 0, 0,
                    (u32)(((arg3 * 1.3e-05f) > 1.0f ? 1.0f : (arg3 * 1.3e-05f)) * arg4) & 0xFF);

    sp58 = Math_FAtan2F(light->l.dir[0], light->l.dir[2]);
    arg6 *= (4.5f - (light->l.dir[1] * 0.035f));
    arg6 = (arg6 < 1.0f) ? 1.0f : arg6;
    SysMatrix_SetCurrentState(arg2);
    Matrix_RotateY(sp58, MTXMODE_APPLY);
    Matrix_Scale(arg5, 1.0f, arg5 * arg6, MTXMODE_APPLY);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_MODELVIEW | G_MTX_LOAD);
    gSPDisplayList(POLY_OPA_DISP++, D_04075B30);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B40E0.s")
#endif

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B42F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B4A98.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B4AEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B4B50.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B4EDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B4F40.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B4F78.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B5040.s")

void Actor_TargetContextInit(TargetContext* targetCtx, Actor* actor, GlobalContext* globalCtx) {
    targetCtx->unk90 = NULL;
    targetCtx->unk8C = NULL;
    targetCtx->unk3C = NULL;
    targetCtx->unk38 = NULL;
    targetCtx->unk4B = 0;
    targetCtx->unk4C = 0;
    targetCtx->unk40 = 0;
    func_800B5040(targetCtx, actor, actor->category, globalCtx);
    func_800B4F78(targetCtx, actor->category, globalCtx);
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B5208.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B5814.s")

u32 Flags_GetSwitch(GlobalContext* globalCtx, s32 flag) {
    if (flag >= 0 && flag < 0x80) {
        return globalCtx->actorCtx.switchFlags[(flag & -0x20) >> 5] & (1 << (flag & 0x1F));
    }
    return 0;
}

void Actor_SetSwitchFlag(GlobalContext* globalCtx, s32 flag) {
    if (flag >= 0 && flag < 0x80) {
        globalCtx->actorCtx.switchFlags[(flag & -0x20) >> 5] |= 1 << (flag & 0x1F);
    }
}

void Actor_UnsetSwitchFlag(GlobalContext* globalCtx, s32 flag) {
    if (flag >= 0 && flag < 0x80) {
        globalCtx->actorCtx.switchFlags[(flag & -0x20) >> 5] &= ~(1 << (flag & 0x1F));
    }
}

u32 Actor_GetChestFlag(GlobalContext* globalCtx, u32 flag) {
    return globalCtx->actorCtx.chestFlags & (1 << flag);
}

void Actor_SetChestFlag(GlobalContext* globalCtx, u32 flag) {
    globalCtx->actorCtx.chestFlags |= (1 << flag);
}

void Actor_SetAllChestFlag(GlobalContext* globalCtx, u32 flag) {
    globalCtx->actorCtx.chestFlags = flag;
}

u32 Actor_GetAllChestFlag(GlobalContext* globalCtx) {
    return globalCtx->actorCtx.chestFlags;
}

u32 Actor_GetRoomCleared(GlobalContext* globalCtx, u32 roomNumber) {
    return globalCtx->actorCtx.clearedRooms & (1 << roomNumber);
}

void Actor_SetRoomCleared(GlobalContext* globalCtx, u32 roomNumber) {
    globalCtx->actorCtx.clearedRooms |= (1 << roomNumber);
}

void Actor_UnsetRoomCleared(GlobalContext* globalCtx, u32 roomNumber) {
    globalCtx->actorCtx.clearedRooms &= ~(1 << roomNumber);
}

u32 Actor_GetRoomClearedTemp(GlobalContext* globalCtx, u32 roomNumber) {
    return globalCtx->actorCtx.clearedRoomsTemp & (1 << roomNumber);
}

void Actor_SetRoomClearedTemp(GlobalContext* globalCtx, u32 roomNumber) {
    globalCtx->actorCtx.clearedRoomsTemp |= (1 << roomNumber);
}

void Actor_UnsetRoomClearedTemp(GlobalContext* globalCtx, u32 roomNumber) {
    globalCtx->actorCtx.clearedRoomsTemp &= ~(1 << roomNumber);
}

u32 Actor_GetCollectibleFlag(GlobalContext* globalCtx, s32 index) {
    if (index > 0 && index < 0x80) {
        return globalCtx->actorCtx.collectibleFlags[(index & -0x20) >> 5] & (1 << (index & 0x1F));
    }
    return 0;
}

void Actor_SetCollectibleFlag(GlobalContext* globalCtx, s32 index) {
    if (index > 0 && index < 0x80) {
        globalCtx->actorCtx.collectibleFlags[(index & -0x20) >> 5] |= 1 << (index & 0x1F);
    }
}

void Actor_TitleCardContextInit(GlobalContext* globalCtx, TitleCardContext* titleCardCtx) {
    titleCardCtx->fadeOutDelay = 0;
    titleCardCtx->fadeInDelay = 0;
    titleCardCtx->color = 0;
    titleCardCtx->alpha = 0;
}

void Actor_TitleCardCreate(GlobalContext* globalCtx, TitleCardContext* titleCardCtx, u32 texture, s16 param_4,
                           s16 param_5, u8 param_6, u8 param_7) {
    titleCardCtx->texture = texture;
    titleCardCtx->unk4 = param_4;
    titleCardCtx->unk6 = param_5;
    titleCardCtx->unk8 = param_6;
    titleCardCtx->unk9 = param_7;
    titleCardCtx->fadeOutDelay = 80;
    titleCardCtx->fadeInDelay = 0;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/Actor_Nop800B5E50.s")

void Actor_TitleCardUpdate(GlobalContext* globalCtx, TitleCardContext* titleCardCtx) {
    if (DECR(titleCardCtx->fadeInDelay) == 0) {
        if (DECR(titleCardCtx->fadeOutDelay) == 0) {
            Math_StepToS(&titleCardCtx->alpha, 0, 30);
            Math_StepToS(&titleCardCtx->color, 0, 70);
        } else {
            Math_StepToS(&titleCardCtx->alpha, 255, 10);
            Math_StepToS(&titleCardCtx->color, 255, 20);
        }
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/Actor_TitleCardDraw.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B6434.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B6468.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B6474.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B648C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B64FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B6584.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B6608.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B6680.s")

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

void Actor_SetObjectSegment(GlobalContext* globalCtx, Actor* actor) {
    // TODO: Segment number enum
    gSegments[6] = PHYSICAL_TO_VIRTUAL(globalCtx->objectCtx.status[actor->objBankIndex].segment);
}

#if 0
void Actor_InitToDefaultValues(Actor* actor, GlobalContext* globalCtx) {
    Actor_InitCurrPosition(actor);
    Actor_InitDrawRotation(actor);
    Actor_SetHeight(actor, 0);
    Math_Vec3f_Copy(&actor->prevPos, &actor->world.pos);
    Actor_SetScale(actor, 0.01);
    actor->targetMode = 3;
    actor->minYVelocity = -20.0f;

    actor->meshAttachedTo = 0x32;

    actor->sqrdDistToLink = D_801DCA54;
    CollisionCheck_InitInfo(&actor->colChkInfo);
    actor->uncullZoneForward = 1000.0f;
    actor->uncullZoneScale = 350.0f;
    actor->uncullZoneDownward = 700.0f;

    actor->naviMsgId = 255;

    Actor_Setshape(&actor->shape, 0, 0, 0);
    if (Object_IsLoaded(&globalCtx->objectCtx, actor->objBankIndex) != 0) {
        Actor_SetObjectSegment(globalCtx, actor);
        actor->init(actor, globalCtx);
        actor->init = NULL;
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/Actor_InitToDefaultValues.s")
#endif

void Actor_FiniActor(Actor* actor, GlobalContext* globalCtx) {
    if (actor->init == NULL) {
        if (actor->destroy != NULL) {
            actor->destroy(actor, globalCtx);
            actor->destroy = NULL;
        }
    }
}

void Actor_SetMovementScale(s32 scale) {
    actorMovementScale = scale * 0.5f;
}

void Actor_ApplyMovement(Actor* actor) {
    f32 speedRate = actorMovementScale;

    actor->world.pos.x += ((actor->velocity.x * speedRate) + actor->colChkInfo.displacement.x);
    actor->world.pos.y += ((actor->velocity.y * speedRate) + actor->colChkInfo.displacement.y);
    actor->world.pos.z += ((actor->velocity.z * speedRate) + actor->colChkInfo.displacement.z);
}

void Actor_SetVelocityYRotationAndGravity(Actor* actor) {
    actor->velocity.x = actor->speedXZ * Math_SinS(actor->world.rot.y);
    actor->velocity.z = actor->speedXZ * Math_CosS(actor->world.rot.y);
    actor->velocity.y += actor->gravity;

    if (actor->velocity.y < actor->minVelocityY) {
        actor->velocity.y = actor->minVelocityY;
    }
}

void Actor_SetVelocityAndMoveYRotationAndGravity(Actor* actor) {
    Actor_SetVelocityYRotationAndGravity(actor);
    Actor_ApplyMovement(actor);
}

void Actor_SetVelocityXYRotation(Actor* actor) {
    f32 velX = Math_CosS(actor->world.rot.x) * actor->speedXZ;
    actor->velocity.x = Math_SinS(actor->world.rot.y) * velX;
    actor->velocity.y = Math_SinS(actor->world.rot.x) * actor->speedXZ;
    actor->velocity.z = Math_CosS(actor->world.rot.y) * velX;
}

void Actor_SetVelocityAndMoveXYRotation(Actor* actor) {
    Actor_SetVelocityXYRotation(actor);
    Actor_ApplyMovement(actor);
}

void Actor_SetVelocityXYRotationReverse(Actor* actor) {
    f32 velX = Math_CosS(-actor->world.rot.x) * actor->speedXZ;
    actor->velocity.x = Math_SinS(actor->world.rot.y) * velX;
    actor->velocity.y = Math_SinS(-actor->world.rot.x) * actor->speedXZ;
    actor->velocity.z = Math_CosS(actor->world.rot.y) * velX;
}

void Actor_SetVelocityAndMoveXYRotationReverse(Actor* actor) {
    Actor_SetVelocityXYRotationReverse(actor);
    Actor_ApplyMovement(actor);
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B6C04.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B6C58.s")

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

    cos_rot_y = Math_CosS(actor->shape.rot.y);
    sin_rot_y = Math_SinS(actor->shape.rot.y);
    imm_x = point->x - actor->world.pos.x;
    imm_z = point->z - actor->world.pos.z;
    offset->x = ((imm_x * cos_rot_y) - (imm_z * sin_rot_y));
    offset->z = ((imm_z * cos_rot_y) + (imm_x * sin_rot_y));
    offset->y = point->y - actor->world.pos.y;
}

f32 Actor_YDistance(Actor* actor1, Actor* actor2) {
    return actor2->world.pos.y - actor1->world.pos.y;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B6F20.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B6FC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B7090.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B7118.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B7128.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B715C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B7170.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B71DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B7200.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B722C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B724C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B7298.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B72E0.s")

void func_800B72F8(DynaPolyActor* dpactor, f32 a1, s16 a2) {
    dpactor->unk150 = a2;
    dpactor->unk148 += a1;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/Actor_IsLinkFacingActor.s")

s32 Actor_IsActorFacedByActor(Actor* actor, Actor* other, s16 tolerance) {
    s16 angle;
    s16 dist;

    angle = BINANG_ROT180(Actor_YawBetweenActors(actor, other));
    dist = angle - other->shape.rot.y;
    if (ABS_ALT(dist) < tolerance) {
        return 1;
    }
    return 0;
}

s32 Actor_IsActorFacingLink(Actor* actor, s16 angle) {
    s16 dist;

    dist = actor->yawTowardsPlayer - actor->shape.rot.y;
    if (ABS_ALT(dist) < angle) {
        return 1;
    }
    return 0;
}

s32 Actor_IsActorFacingActor(Actor* actor, Actor* other, s16 tolerance) {
    s16 dist;

    dist = Actor_YawBetweenActors(actor, other) - actor->shape.rot.y;
    if (ABS_ALT(dist) < tolerance) {
        return 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/Actor_IsActorFacingLinkAndWithinRange.s")

s32 Actor_IsActorFacingActorAndWithinRange(Actor* actor, Actor* other, f32 range, s16 tolerance) {
    s16 dist;

    if (Actor_DistanceBetweenActors(actor, other) < range) {
        dist = Actor_YawBetweenActors(actor, other) - actor->shape.rot.y;
        if (ABS_ALT(dist) < tolerance) {
            return 1;
        }
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B75A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B761C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B7678.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/Actor_UpdateBgCheckInfo.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B7E04.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B7FE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B8018.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B8050.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B8118.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B81E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B8214.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B8248.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B82EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B83BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B83F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B84D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B8500.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B85E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B8614.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B863C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B867C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B86C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B8708.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B8718.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B874C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B8804.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B882C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B886C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B8898.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B8934.s")

u32 Actor_HasParent(Actor* actor, GlobalContext* globalCtx) {
    if (actor->parent != NULL) {
        return true;
    } else {
        return false;
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B8A1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B8B84.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B8BB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B8BD0.s")

s32 Actor_HasNoParent(Actor* actor, GlobalContext* globalCtx) {
    if (!actor->parent) {
        return true;
    } else {
        return false;
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B8C20.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B8C50.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B8C78.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B8C9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B8CEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B8D10.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B8D50.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B8D98.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B8DD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B8E1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B8E58.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/Audio_PlayActorSound2.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B8EF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B8F98.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B8FC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B8FE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B9010.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B9038.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B9084.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B9098.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B90AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B90F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B9120.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/Actor_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B9334.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/Actor_UpdateActor.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/Actor_UpdateAll.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/Actor_DrawActor.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B9D1C.s")

void Actor_DrawAllSetup(GlobalContext* globalCtx) {
    globalCtx->actorCtx.undrawnActorCount = 0;
    globalCtx->actorCtx.unkB = 0;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/Actor_RecordUndrawnActor.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B9E84.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B9EF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BA2D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BA2FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/Actor_DrawAll.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BA6FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BA798.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BA8B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BA9B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/Actor_InsertIntoTypeList.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/Actor_RemoveFromTypeList.s")

void Actor_FreeOverlay(ActorOverlay* entry) {
    void* ramAddr;

    if (entry->numLoaded == 0) {
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

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/Actor_Spawn.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/Actor_LoadOverlay.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/Actor_SpawnAsChildAndCutscene.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/Actor_SpawnAsChild.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/Actor_SpawnTransitionActors.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BB2D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BB498.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BB59C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BB604.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BB8EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BBA88.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BBAC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BBB74.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BBC20.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BBCEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BBDAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BBFB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BC154.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BC188.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BC1B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BC270.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BC444.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BC4EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BC5B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BC5EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BC620.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BC770.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BC7D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BC848.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BC8B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BCB50.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BCB70.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BCBF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BCC68.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BCCDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BD2B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BD384.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BD6B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BD6E4.s")

// This function is very similar to OoT's func_80034A14
#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BD888.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BD9A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BD9E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BDAA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BDB6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BDC5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BDCF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/Actor_Noop.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BDFC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BE03C.s")

Actor *func_800BE0B8(GlobalContext *globalCtx, Actor *inActor, s16 arg2, u8 arg3, f32 arg4) {
    Actor *actor = globalCtx->actorCtx.actorList[arg3].first;

    while (actor != NULL) {
        if (actor == inActor || ((arg2 != -1) && (arg2 != actor->id))) {
            actor = actor->next;
            continue;
        }

        if (Actor_DistanceBetweenActors(inActor, actor) <= arg4) {
            return actor;
        }

        actor = actor->next;
    }

    return NULL;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BE184.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BE22C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BE258.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BE2B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BE33C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BE3D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BE504.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BE568.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BE5CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BE63C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BE680.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BF7CC.s")
