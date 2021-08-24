#include "global.h"
#include "overlays/actors/ovl_En_Horse/z_en_horse.h"

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
            if ((dy * 0.0028571428f) > 1.0f) {
                shadowScale = 0.0f;
            }

            if (color != NULL) {
                gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, color->r, color->g, color->b,
                                (u8)(actor->shape.shadowAlpha * shadowScale));
            } else {
                gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 0, 0, 0, (u8)(actor->shape.shadowAlpha * shadowScale));
            }

            func_800C0094(actor->floorPoly, actor->world.pos.x, actor->floorHeight, actor->world.pos.z, &mtx);
            SysMatrix_SetCurrentState(&mtx);

            if ((dlist != D_04076BC0) || (actor->scale.x != actor->scale.z)) {
                Matrix_RotateY(actor->shape.rot.y, MTXMODE_APPLY);
            }

            shadowScale *= actor->shape.shadowScale;
            Matrix_Scale(actor->scale.x * shadowScale, 1.0f, actor->scale.z * shadowScale, MTXMODE_APPLY);

            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_MODELVIEW | G_MTX_LOAD);
            gSPDisplayList(POLY_OPA_DISP++, dlist);

            CLOSE_DISPS(globalCtx->state.gfxCtx);
        }
    }
}

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

static Color_RGBA8 D_801AEC80 = { 255, 255, 255, 255 };

/* ActorShadow_DrawWhiteCircle */
void func_800B4088(Actor* actor, Lights* lights, GlobalContext* globalCtx) {
    ActorShadow_Draw(actor, lights, globalCtx, D_04076BC0, &D_801AEC80);
}

/* ActorShadow_DrawHorse */
void func_800B40B8(Actor* actor, Lights* lights, GlobalContext* globalCtx) {
    ActorShadow_Draw(actor, lights, globalCtx, D_04077480, NULL);
}

/* ActorShadow_DrawFoot */
void func_800B40E0(GlobalContext* globalCtx, Light* light, MtxF* arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    s32 pad;
    s16 sp58;
    f32 dir2;
    f32 dir0;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 0, 0, 0, (u8)(CLAMP_MAX(arg3 * 1.3e-05f, 1.0f) * arg4));

    dir0 = light->l.dir[0];
    dir2 = light->l.dir[2];
    sp58 = Math_FAtan2F(dir2, dir0);
    arg6 *= 4.5f - light->l.dir[1] * 0.035f;
    arg6 = CLAMP_MIN(arg6, 1.0f);
    SysMatrix_SetCurrentState(arg2);
    Matrix_RotateY(sp58, MTXMODE_APPLY);
    Matrix_Scale(arg5, 1.0f, arg5 * arg6, MTXMODE_APPLY);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_MODELVIEW | G_MTX_LOAD);
    gSPDisplayList(POLY_OPA_DISP++, D_04075B30);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

// ActorShadow_DrawFeet
#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B42F8.s")

// Actor_SetFeetPos
void func_800B4A98(Actor* actor, s32 limbIndex, s32 leftFootIndex, Vec3f* leftFootPos, s32 rightFootIndex,
                   Vec3f* rightFootPos) {
    if (limbIndex == leftFootIndex) {
        SysMatrix_MultiplyVector3fByState(leftFootPos, &actor->shape.feetPos[FOOT_LEFT]);
    } else if (limbIndex == rightFootIndex) {
        SysMatrix_MultiplyVector3fByState(rightFootPos, &actor->shape.feetPos[FOOT_RIGHT]);
    }
}

void func_800B4AEC(GlobalContext* globalCtx, Actor* actor, f32 param_3) {
    s32 floorBgId;
    f32 yPos = actor->world.pos.y;

    actor->world.pos.y += param_3;
    actor->floorHeight =
        func_800C4188(param_3, &globalCtx->colCtx, &actor->floorPoly, &floorBgId, actor, &actor->world.pos);
    actor->floorBgId = floorBgId;
    actor->world.pos.y = yPos;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B4B50.s")

void func_800B4EDC(GlobalContext* globalCtx, Vec3f* pzParm2, Vec3f* pzParm3, f32* pfParm4) {
    SkinMatrix_Vec3fMtxFMultXYZW(&globalCtx->projectionMatrix, pzParm2, pzParm3, pfParm4);
    if (*pfParm4 < 1.0f) {
        *pfParm4 = 1.0f;
    } else {
        *pfParm4 = 1.0f / *pfParm4;
    }
}

void func_800B4F40(TargetContext* targetCtx, s32 index, f32 x, f32 y, f32 z) {
    targetCtx->unk50[index].pos.x = x;
    targetCtx->unk50[index].pos.y = y;
    targetCtx->unk50[index].pos.z = z;
    targetCtx->unk50[index].unkC = targetCtx->unk44;
}

s801AEC84 D_801AEC84[13] = {
    { 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0 },
    { 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0 },
    { 0xFF, 0xFF, 0xE6, 0xFF, 0xDC, 0xA0, 0x50, 0 },
    { 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0 },
    { 0x96, 0x96, 0xFF, 0xFF, 0x96, 0x96, 0xFF, 0 },
    { 0xFF, 0xFF, 0, 0xFF, 0xC8, 0x9B, 0, 0 },
    { 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0 },
    { 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0 },
    { 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0 },
    { 0xFF, 0xFF, 0, 0xFF, 0xC8, 0x9B, 0, 0 },
    { 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0 },
    { 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0 },
    { 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0 },
};

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

void TitleCard_ContextInit(GlobalContext* globalCtx, TitleCardContext* titleCtx) {
    titleCtx->durationTimer = 0;
    titleCtx->delayTimer = 0;
    titleCtx->intensity = 0;
    titleCtx->alpha = 0;
}

void TitleCard_InitBossName(GlobalContext* globalCtx, TitleCardContext* titleCtx, u32 texture, s16 param_4, s16 param_5,
                            u8 param_6, u8 param_7) {
    titleCtx->texture = texture;
    titleCtx->x = param_4;
    titleCtx->y = param_5;
    titleCtx->width = param_6;
    titleCtx->height = param_7;
    titleCtx->durationTimer = 80;
    titleCtx->delayTimer = 0;
}

void TitleCard_InitPlaceName(GlobalContext* globalCtx, TitleCardContext* titleCtx, void* texture, s32 x, s32 y,
                             s32 width, s32 height, s32 delay) {
}

void TitleCard_Update(GlobalContext* globalCtx, TitleCardContext* titleCtx) {
    if (DECR(titleCtx->delayTimer) == 0) {
        if (DECR(titleCtx->durationTimer) == 0) {
            Math_StepToS(&titleCtx->alpha, 0, 30);
            Math_StepToS(&titleCtx->intensity, 0, 70);
        } else {
            Math_StepToS(&titleCtx->alpha, 255, 10);
            Math_StepToS(&titleCtx->intensity, 255, 20);
        }
    }
}

void TitleCard_Draw(GlobalContext* globalCtx, TitleCardContext* titleCtx) {
    s32 spCC;
    s32 spC8;
    s32 unk1;
    s32 spC0;
    s32 sp38;
    s32 spB8;
    s32 spB4;
    int new_var;

    if (titleCtx->alpha != 0) {
        spCC = titleCtx->width;
        spC8 = titleCtx->height;
        new_var = spCC * 2;
        spC0 = (titleCtx->x * 4) - new_var;
        spB8 = (titleCtx->y * 4) - (spC8 * 2);
        sp38 = spCC * 2;

        OPEN_DISPS(globalCtx->state.gfxCtx);

        spC8 = (spCC * spC8 > 0x1000) ? 0x1000 / spCC : spC8;
        spB4 = spB8 + (spC8 * 4);

        if (1) {} // Necessary to match

        OVERLAY_DISP = func_8012C014(OVERLAY_DISP);

        gDPSetPrimColor(OVERLAY_DISP++, 0, 0, (u8)titleCtx->intensity, (u8)titleCtx->intensity, (u8)titleCtx->intensity,
                        (u8)titleCtx->alpha);

        gDPLoadTextureBlock(OVERLAY_DISP++, (s32*)titleCtx->texture, G_IM_FMT_IA, G_IM_SIZ_8b, spCC, spC8, 0,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                            G_TX_NOLOD);

        gSPTextureRectangle(OVERLAY_DISP++, spC0, spB8, ((sp38 * 2) + spC0) - 4, spB8 + (spC8 * 4) - 1, G_TX_RENDERTILE,
                            0, 0, 1 << 10, 1 << 10);

        spC8 = titleCtx->height - spC8;

        if (spC8 > 0) {
            gDPLoadTextureBlock(OVERLAY_DISP++, (s32)titleCtx->texture + 0x1000, G_IM_FMT_IA, G_IM_SIZ_8b, spCC, spC8,
                                0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                G_TX_NOLOD, G_TX_NOLOD);

            gSPTextureRectangle(OVERLAY_DISP++, spC0, spB4, ((sp38 * 2) + spC0) - 4, spB4 + (spC8 * 4) - 1,
                                G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
        }

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}

s32 func_800B6434(GlobalContext* globalCtx, TitleCardContext* titleCtx) {
    if ((globalCtx->actorCtx.titleCtxt.delayTimer != 0) || (globalCtx->actorCtx.titleCtxt.alpha != 0)) {
        titleCtx->durationTimer = 0;
        titleCtx->delayTimer = 0;
        return false;
    }
    return true;
}

void func_800B6468(GlobalContext* globalCtx) {
    globalCtx->actorCtx.unk1F5 = 0;
}

void func_800B6474(GlobalContext* globalCtx) {
    if (globalCtx->actorCtx.unk1F5 != 0) {
        globalCtx->actorCtx.unk1F5--;
    }
}

s32 func_800B648C(GlobalContext* globalCtx, s32 arg1, s32 arg2, f32 arg3, Vec3f* arg4) {
    if ((globalCtx->actorCtx.unk1F5 != 0) && (arg3 < globalCtx->actorCtx.unk1F8)) {
        return 0;
    }

    globalCtx->actorCtx.unk1F4 = arg1;
    globalCtx->actorCtx.unk1F5 = arg2;
    globalCtx->actorCtx.unk1F8 = arg3;
    Math_Vec3f_Copy(&globalCtx->actorCtx.unk1FC, arg4);
    return 1;
}

f32 func_800B64FC(GlobalContext* globalCtx, f32 fParm2, Vec3f* pzParm3, u32* puParm4) {
    f32 temp_f8;

    if ((globalCtx->actorCtx.unk1F5 == 0) || (fParm2 == 0.0f)) {
        return -1.0f;
    }
    fParm2 = fParm2;
    temp_f8 = Math_Vec3f_DistXYZ(&globalCtx->actorCtx.unk1FC, pzParm3) / fParm2;
    *puParm4 = globalCtx->actorCtx.unk1F4;
    return globalCtx->actorCtx.unk1F8 - temp_f8;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B6584.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B6608.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B6680.s")

void Actor_MarkForDeath(Actor* actor) {
    actor->draw = NULL;
    actor->update = NULL;
    actor->flags &= ~0x1;
}

void Actor_SetWorldToHome(Actor* actor) {
    actor->world = actor->home;
}

void Actor_SetFocus(Actor* actor, f32 height) {
    actor->focus.pos.x = actor->world.pos.x;
    actor->focus.pos.y = actor->world.pos.y + height;
    actor->focus.pos.z = actor->world.pos.z;

    actor->focus.rot.x = actor->world.rot.x;
    actor->focus.rot.y = actor->world.rot.y;
    actor->focus.rot.z = actor->world.rot.z;
}

void Actor_SetWorldRotToShape(Actor* actor) {
    actor->world.rot = actor->shape.rot;
}

void Actor_SetShapeRotToWorld(Actor* actor) {
    actor->shape.rot = actor->world.rot;
}

void Actor_SetScale(Actor* actor, f32 scale) {
    actor->scale.z = scale;
    actor->scale.y = scale;
    actor->scale.x = scale;
}

void Actor_SetObjectDependency(GlobalContext* globalCtx, Actor* actor) {
    gSegments[6] = PHYSICAL_TO_VIRTUAL(globalCtx->objectCtx.status[actor->objBankIndex].segment);
}

void Actor_Init(Actor* actor, GlobalContext* globalCtx) {
    Actor_SetWorldToHome(actor);
    Actor_SetShapeRotToWorld(actor);
    Actor_SetFocus(actor, 0.0f);
    Math_Vec3f_Copy(&actor->prevPos, &actor->world.pos);
    Actor_SetScale(actor, 0.01f);
    actor->targetMode = 3;
    actor->minVelocityY = -20.0f;

    actor->xyzDistToPlayerSq = FLT_MAX;
    actor->uncullZoneForward = 1000.0f;
    actor->uncullZoneScale = 350.0f;
    actor->uncullZoneDownward = 700.0f;

    actor->hintId = 255;

    CollisionCheck_InitInfo(&actor->colChkInfo);
    actor->floorBgId = BGCHECK_SCENE;

    ActorShape_Init(&actor->shape, 0.0f, NULL, 0.0f);
    if (Object_IsLoaded(&globalCtx->objectCtx, actor->objBankIndex)) {
        Actor_SetObjectDependency(globalCtx, actor);
        actor->init(actor, globalCtx);
        actor->init = NULL;
    }
}

void Actor_Destroy(Actor* actor, GlobalContext* globalCtx) {
    if (actor->init == NULL) {
        if (actor->destroy != NULL) {
            actor->destroy(actor, globalCtx);
            actor->destroy = NULL;
        }
    }
}

f32 actorMovementScale = 1.0f;

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

void Actor_MoveForward(Actor* actor) {
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

void func_800B6C04(Actor* actor, f32 speed) {
    actor->speedXZ = Math_CosS(actor->world.rot.x) * speed;
    actor->velocity.y = -Math_SinS(actor->world.rot.x) * speed;
}

void func_800B6C58(Actor* actor, SkelAnime* skelAnime) {
    Vec3f pos;

    func_80137748(skelAnime, &pos, actor->shape.rot.y);
    actor->world.pos.x += pos.x * actor->scale.x;
    actor->world.pos.y += pos.y * actor->scale.y;
    actor->world.pos.z += pos.z * actor->scale.z;
}

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

f32 Actor_HeightDiff(Actor* actor1, Actor* actor2) {
    return actor2->world.pos.y - actor1->world.pos.y;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B6F20.s")

f32 Player_GetHeight(Player* player) {
    f32 offset;

    if (player->stateFlags1 & 0x800000) {
        offset = 32.0f;
    } else {
        offset = 0.0f;
    }

    switch (player->transformation) {
        default:
        case PLAYER_FORM_FIERCE_DEITY:
            return offset + 124.0f;
        case PLAYER_FORM_GORON:
            return offset + ((player->stateFlags3 & 0x1000) ? 34.0f : 80.0f);
        case PLAYER_FORM_ZORA:
            return offset + 68.0f;
        case PLAYER_FORM_DEKU:
            return offset + 36.0f;
        case PLAYER_FORM_HUMAN:
            return offset + 44.0f;
    }
}

// Player_GetRunSpeedLimit?
f32 func_800B7090(Player* player) {
    if (player->stateFlags1 & 0x800000) {
        return 15.0f;
    } else if (player->stateFlags1 & 0x8000000) {
        return (R_RUN_SPEED_LIMIT / 100.0f) * 0.6f;
    } else {
        return R_RUN_SPEED_LIMIT / 100.0f;
    }
}

s32 func_800B7118(Player* player) {
    return player->stateFlags1 & 8;
}

s32 func_800B7128(Player* player) {
    return func_800B7118(player) && player->unk_ACC;
}

s32 func_800B715C(GlobalContext* globalCtx) {
    Player* player = PLAYER;

    return player->stateFlags2 & 8;
}

void func_800B7170(GlobalContext* globalCtx, Player* player) {
    if ((globalCtx->roomCtx.currRoom.unk3 != 4) && (player->actor.id == ACTOR_PLAYER)) {
        EnHorse* rideActor = player->rideActor;

        if ((rideActor != NULL) && !(rideActor->unk_1EC & 0x10)) {
            func_800DFAC8(Play_GetCamera(globalCtx, 0), 4);
        }
    }
}

void Actor_MountHorse(GlobalContext* globalCtx, Player* player, Actor* horse) {
    player->rideActor = horse;
    player->stateFlags1 |= 0x800000;
    horse->child = &player->actor;
}

s32 func_800B7200(Player* player) {
    return (player->stateFlags1 & 0x20000080) || (player->csMode != 0);
}

void func_800B722C(GlobalContext* globalCtx, Player* player) {
    func_800F40A0(globalCtx, player);
}

s32 func_800B724C(GlobalContext* globalCtx, Actor* actor, u8 csMode) {
    Player* player = PLAYER;

    if ((player->csMode == 5) || ((csMode == 6) && (player->csMode == 0))) {
        return false;
    }

    player->csMode = csMode;
    player->unk_398 = actor;
    player->unk_3BA = 0;
    return true;
}

u32 func_800B7298(GlobalContext* globalCtx, Actor* actor, u8 arg2) {
    Player* player = PLAYER;

    if (func_800B724C(globalCtx, actor, arg2)) {
        player->unk_3BA = 1;
        return true;
    }
    return false;
}

void func_800B72E0(DynaPolyActor* dyna) {
    dyna->unk14C = 0.0f;
    dyna->unk148 = 0.0f;
}

void func_800B72F8(DynaPolyActor* dyna, f32 a1, s16 a2) {
    dyna->unk150 = a2;
    dyna->unk148 += a1;
}

s32 Actor_IsPlayerFacingActor(Actor* actor, s16 tolerance, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    s16 yawDiff = BINANG_ADD(actor->yawTowardsPlayer, 0x8000) - player->actor.shape.rot.y;

    if (ABS_ALT(yawDiff) < tolerance) {
        return true;
    }
    return false;
}

s32 Actor_IsActorFacedByActor(Actor* actor, Actor* other, s16 tolerance) {
    s16 angle = BINANG_ROT180(Actor_YawBetweenActors(actor, other));
    s16 dist;

    dist = angle - other->shape.rot.y;
    if (ABS_ALT(dist) < tolerance) {
        return true;
    }
    return false;
}

s32 Actor_IsActorFacingPlayer(Actor* actor, s16 angle) {
    s16 dist = actor->yawTowardsPlayer - actor->shape.rot.y;

    if (ABS_ALT(dist) < angle) {
        return true;
    }
    return false;
}

s32 Actor_IsActorFacingActor(Actor* actor, Actor* other, s16 tolerance) {
    s16 dist = Actor_YawBetweenActors(actor, other) - actor->shape.rot.y;

    if (ABS_ALT(dist) < tolerance) {
        return 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/Actor_IsActorFacingPlayerAndWithinRange.s")

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

void func_800B75A0(CollisionPoly* param_1, Vec3f* param_2, s16* param_3) {
    param_2->x = param_1->normal.x * (1.0f / 0x7FFF);
    param_2->y = param_1->normal.y * (1.0f / 0x7FFF);
    param_2->z = param_1->normal.z * (1.0f / 0x7FFF);
    *param_3 = Math_FAtan2F(param_2->z, param_2->x);
}

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

f32 D_801AECF0[22] = {
    4900.0f,   0.5f,        28900.0f,   0.6666667f, 78400.0f,   0.05f,       122500.0f, 0.6666667f,
    490000.0f, 0.6666667f,  1000000.0f, 0.6666667f, 10000.0f,   0.94905096f, 19600.0f,  0.85714287f,
    57600.0f,  0.41666666f, 78400.0f,   0.001f,     6250000.0f, 0.6666667f,
};

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B83BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B83F8.s")

s16 D_801AED48[] = {
    0x0101, 0x0141, 0x0111, 0x0151, 0x0105, 0x0145, 0x0115, 0x0155,
};

s32 Actor_IsTalking(Actor* actor, GlobalContext* globalCtx) {
    if (actor->flags & 0x100) {
        actor->flags &= ~0x100;
        return 1;
    }

    return 0;
}

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

void func_800B8898(GlobalContext* globalCtx, Actor* actor, s16* arg2, s16* arg3) {
    Vec3f sp1C;
    f32 sp18;

    func_800B4EDC(globalCtx, &actor->focus.pos, &sp1C, &sp18);
    *arg2 = (sp1C.x * sp18 * 160.0f) + 160.0f;
    *arg3 = (sp1C.y * sp18 * -120.0f) + 120.0f;
}

s32 func_800B8934(GlobalContext* globalCtx, Actor* actor) {
    Vec3f sp2C;
    f32 sp28;
    s32 pad[2];

    func_800B4EDC(globalCtx, &actor->focus.pos, &sp2C, &sp28);

    return (sp2C.x * sp28 >= -1.0f) && (sp2C.x * sp28 <= 1.0f) && (sp2C.y * sp28 >= -1.0f) && (sp2C.y * sp28 <= 1.0f);
}

u32 Actor_HasParent(Actor* actor, GlobalContext* globalCtx) {
    if (actor->parent != NULL) {
        return true;
    } else {
        return false;
    }
}

// Actor_PickUp
s32 func_800B8A1C(Actor* actor, GlobalContext* globalCtx, s32 getItemId, f32 xzRange, f32 yRange) {
    Player* player = PLAYER;

    if (!(player->stateFlags1 & 0x3C7080) && Player_GetExplosiveHeld(player) < 0) {
        if ((actor->xzDistToPlayer <= xzRange) && (fabsf(actor->yDistToPlayer) <= fabsf(yRange))) {
            if ((getItemId == GI_MASK_CIRCUS_LEADER || getItemId == GI_PENDANT_OF_MEMORIES ||
                 getItemId == GI_LAND_TITLE_DEED ||
                 (((player->heldActor != NULL) || (actor == player->targetActor)) &&
                  (getItemId > GI_NONE && getItemId < GI_MAX))) ||
                (!(player->stateFlags1 & 0x20000800))) {
                s16 yawDiff = actor->yawTowardsPlayer - player->actor.shape.rot.y;
                s32 absYawDiff = ABS_ALT(yawDiff);

                if ((getItemId != GI_NONE) || (player->getItemDirection < absYawDiff)) {
                    player->getItemId = getItemId;
                    player->interactRangeActor = actor;
                    player->getItemDirection = absYawDiff;

                    if (getItemId > GI_NONE && getItemId < GI_MAX) {
                        ActorCutscene_SetIntentToPlay(globalCtx->unk_1879C[1]);
                    }

                    return true;
                }
            }
        }
    }

    return false;
}

// Actor_PickUpNearby
s32 func_800B8B84(Actor* actor, GlobalContext* globalCtx, s32 getItemId) {
    return func_800B8A1C(actor, globalCtx, getItemId, 50.0f, 10.0f);
}

// Actor_HoldActor?
s32 func_800B8BB0(Actor* actor, GlobalContext* globalCtx) {
    return func_800B8B84(actor, globalCtx, GI_NONE);
}

// Actor_PickUpFar?
s32 func_800B8BD0(Actor* actor, GlobalContext* globalCtx, s32 getItemId) {
    return func_800B8A1C(actor, globalCtx, getItemId, 9999.9f, 9999.9f);
}

s32 Actor_HasNoParent(Actor* actor, GlobalContext* globalCtx) {
    if (!actor->parent) {
        return true;
    } else {
        return false;
    }
}

void func_800B8C20(Actor* actorA, Actor* actorB, GlobalContext* globalCtx) {
    Actor* parent = actorA->parent;

    if (parent->id == ACTOR_PLAYER) {
        Player* player = (Player*)parent;

        player->heldActor = actorB;
        player->interactRangeActor = actorB;
    }

    parent->child = actorB;
    actorB->parent = parent;
    actorA->parent = NULL;
}

void func_800B8C50(Actor* actor, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    if (actor->xyzDistToPlayerSq < player->unk_AA0) {
        player->unk_AA0 = actor->xyzDistToPlayerSq;
    }
}

s32 Actor_IsMounted(GlobalContext* globalCtx, Actor* horse) {
    if (horse->child != NULL) {
        return true;
    }
    return false;
}

s32 Actor_SetRideActor(GlobalContext* globalCtx, Actor* horse, s32 mountSide) {
    Player* player = PLAYER;

    if (!(player->stateFlags1 & 0x003C7880)) {
        player->rideActor = horse;
        player->mountSide = mountSide;
        ActorCutscene_SetIntentToPlay(0x7C);
        return true;
    }

    return false;
}

s32 Actor_NotMounted(GlobalContext* globalCtx, Actor* horse) {
    if (horse->child == NULL) {
        return true;
    }

    return false;
}

void func_800B8D10(GlobalContext* globalCtx, Actor* actor, f32 arg2, s16 arg3, f32 arg4, u32 arg5, u32 arg6) {
    Player* player = PLAYER;

    player->unk_B74 = arg6;
    player->unk_B75 = arg5;
    player->unk_B78 = arg2;
    player->unk_B76 = arg3;
    player->unk_B7C = arg4;
}

void func_800B8D50(GlobalContext* globalCtx, Actor* actor, f32 arg2, s16 yaw, f32 arg4, u32 arg5) {
    func_800B8D10(globalCtx, actor, arg2, yaw, arg4, 3, arg5);
}

void func_800B8D98(GlobalContext* globalCtx, Actor* actor, f32 arg2, s16 arg3, f32 arg4) {
    func_800B8D50(globalCtx, actor, arg2, arg3, arg4, 0);
}

void func_800B8DD4(GlobalContext* globalCtx, Actor* actor, f32 arg2, s16 arg3, f32 arg4, u32 arg5) {
    func_800B8D10(globalCtx, actor, arg2, arg3, arg4, 2, arg5);
}

void func_800B8E1C(GlobalContext* globalCtx, Actor* actor, f32 arg2, s16 arg3, f32 arg4) {
    func_800B8DD4(globalCtx, actor, arg2, arg3, arg4, 0);
}

#if 0
// The OoT version of this function (func_8002F7DC) takes Actor*, but there's a high chance it takes Player* here
void func_800B8E58(Actor* actor, u16 sfxId) {
    if (actor->unk_153 == 0x14) {
        func_8019F170(&actor->projectedPos, sfxId);
        return;
    }
    func_801A5CFC(sfxId, &actor->projectedPos, 4, &D_801DB4B0, &D_801DB4B0, &D_801DB4B8);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B8E58.s")
#endif

void Audio_PlayActorSound2(Actor* actor, u16 sfxId) {
    func_8019F1C0(&actor->projectedPos, sfxId);
}

void func_800B8EF4(GlobalContext* globalCtx, Actor* actor) {
    u32 sp1C;

    if (actor->bgCheckFlags & 0x20) {
        if (actor->yDistToWater < 20.0f) {
            sp1C = NA_SE_PL_WALK_WATER0 - SFX_FLAG;
        } else {
            sp1C = NA_SE_PL_WALK_WATER1 - SFX_FLAG;
        }
    } else {
        sp1C = func_800C9BDC(&globalCtx->colCtx, actor->floorPoly, actor->floorBgId);
    }

    func_8019F1C0(&actor->projectedPos, 0x282F);
    func_8019F1C0(&actor->projectedPos, sp1C + SFX_FLAG);
}

void func_800B8F98(Actor* actor, u16 sfxId) {
    actor->sfx = sfxId;
    actor->unk39 &= ~(0x10 | 0x08 | 0x04 | 0x02 | 0x01);
    actor->unk39 |= 0x02;
}

void func_800B8FC0(Actor* actor, u16 sfxId) {
    actor->sfx = sfxId;
    actor->unk39 &= ~(0x10 | 0x08 | 0x04 | 0x02 | 0x01);
    actor->unk39 |= 4;
}

void func_800B8FE8(Actor* actor, u16 sfxId) {
    actor->sfx = sfxId;
    actor->unk39 &= ~(0x10 | 0x08 | 0x04 | 0x02 | 0x01);
    actor->unk39 |= 0x08;
}

void func_800B9010(Actor* actor, u16 sfxId) {
    actor->sfx = sfxId;
    actor->unk39 &= ~(0x10 | 0x08 | 0x04 | 0x02 | 0x01);
    actor->unk39 |= 0x01;
}

void func_800B9038(Actor* actor, s32 arg1) {
    actor->unk39 &= ~(0x10 | 0x08 | 0x04 | 0x02 | 0x01);
    actor->unk39 |= 0x10;

    if (arg1 < 40) {
        actor->sfx = 3;
    } else if (arg1 < 100) {
        actor->sfx = 2;
    } else {
        actor->sfx = 1;
    }
}

void func_800B9084(Actor* actor) {
    actor->unk39 |= 0x20;
}

void func_800B9098(Actor* actor) {
    actor->unk39 |= 0x40;
}

s32 func_800B90AC(GlobalContext* globalCtx, Actor* actor, CollisionPoly* polygon, s32 index, s32 arg4) {
    if (func_800C99D4(&globalCtx->colCtx, polygon, index) == 8) {
        return 1;
    }
    return 0;
}

void func_800B90F4(GlobalContext* globalCtx) {
    if (globalCtx->actorCtx.unk3 != 0) {
        globalCtx->actorCtx.unk3 = 0;
        func_80115D5C(globalCtx);
    }
}

void func_800B9120(ActorContext* actorCtx) {
    s32 phi_v0 = CURRENT_DAY * 2;

    if (gSaveContext.time < CLOCK_TIME(6, 0) || gSaveContext.time > CLOCK_TIME(18, 0)) {
        phi_v0++;
    }
    actorCtx->unkC = (0x200 >> phi_v0);
}

// Actor_InitContext // OoT's func_800304DC
#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800b9170.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800B9334.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/Actor_UpdateActor.s")

s32 D_801AED58[] = {
    0x100002C2, 0x100002C2, 0x00000200, 0x100006C2, 0x00000282, 0x300002C2,
    0x10000282, 0x00000002, 0x300002C2, 0x100006C2, 0x00000002, 0x100002C2,
};

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/Actor_UpdateAll.s")

Color_RGBA8 actorDefaultHitColor = { 0x00, 0x00, 0x00, 0xFF };

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/Actor_Draw.s")

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

void Actor_InsertIntoTypeList(ActorContext* actorCtx, Actor* actor, u8 actorCategory) {
    Actor* phi_v0;
    Actor* phi_v1;

    actor->category = actorCategory;

    actorCtx->totalLoadedActors++;
    actorCtx->actorList[actorCategory].length++;
    phi_v1 = actorCtx->actorList[actorCategory].first;
    if (phi_v1 == NULL) {
        actorCtx->actorList[actorCategory].first = actor;
        return;
    }

    phi_v0 = phi_v1->next;
    while (phi_v0 != NULL) {
        phi_v1 = phi_v0;
        phi_v0 = phi_v0->next;
    }

    phi_v1->next = actor;
    actor->prev = phi_v1;
}

// Actor_RemoveFromCategory
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

Actor* Actor_Spawn(ActorContext* actorCtx, GlobalContext* globalCtx, s16 actorId, f32 posX, f32 posY, f32 posZ,
                   s16 rotX, s16 rotY, s16 rotZ, s32 params) {
    return Actor_SpawnAsChildAndCutscene(actorCtx, globalCtx, actorId, posX, posY, posZ, rotX, rotY, rotZ, params, -1,
                                         0x3FF, NULL);
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/Actor_LoadOverlay.s")

#ifdef NON_EQUIVALENT
// This probably *is* equivalent, but I haven't checked
Actor* Actor_SpawnAsChildAndCutscene(ActorContext* actorCtx, GlobalContext* globalCtx, s16 index, f32 x, f32 y, f32 z,
                                     s16 rotX, s16 rotY, s16 rotZ, s32 params, u32 cutscene, s32 param_12,
                                     Actor* parent) {
    s32 pad;
    Actor* actor;
    ActorInit* sp2C; // actorInit
    s32 sp28;        // objBankIndex
    // s32 pad2;
    u32 sp20;           // segmentAux
    ActorOverlay* sp1C; // overlayEntry

    if (actorCtx->totalLoadedActors >= 0xFF) {
        return NULL;
    }

    sp2C = Actor_LoadOverlay(actorCtx, index);
    if (sp2C == NULL) {
        return NULL;
    }

    sp28 = Object_GetIndex(&globalCtx->objectCtx, sp2C->objectId);
    if ((sp28 < 0) ||
        ((sp2C->type == ACTORCAT_ENEMY) && ((Actor_GetRoomCleared(globalCtx, globalCtx->roomCtx.currRoom.num) != 0)) &&
         (sp2C->id != ACTOR_BOSS_05))) {
        Actor_FreeOverlay(&gActorOverlayTable[index]);
        return NULL;
    }

    actor = zelda_malloc(sp2C->instanceSize);
    if (actor == NULL) {
        Actor_FreeOverlay(&gActorOverlayTable[index]);
        return NULL;
    }

    if (1) {}

    sp1C = &gActorOverlayTable[index];
    if (sp1C->vramStart != 0) {
        sp1C->numLoaded++;
    }

    if (1) {}

    bzero(actor, sp2C->instanceSize);
    actor->overlayEntry = sp1C;
    actor->id = sp2C->id;
    actor->flags = sp2C->flags;

    if (sp2C->id == ACTOR_EN_PART) {
        actor->objBankIndex = (s8)rotZ;
        rotZ = 0;
    } else {
        actor->objBankIndex = (s8)sp28;
    }

    actor->init = sp2C->init;
    actor->destroy = sp2C->destroy;
    actor->update = sp2C->update;
    actor->draw = sp2C->draw;

    if (parent != NULL) {
        actor->room = parent->room;
        actor->parent = parent;
        parent->child = actor;
    } else {
        actor->room = globalCtx->roomCtx.currRoom.num;
    }

    actor->home.pos.x = x;
    actor->home.pos.y = y;
    actor->home.pos.z = z;
    actor->home.rot.x = rotX;
    actor->home.rot.y = rotY;
    actor->home.rot.z = rotZ;
    actor->params = params;
    actor->cutscene = (cutscene & 0x7F);

    if (actor->cutscene == 0x7F) {
        actor->cutscene = -1;
    }

    if (param_12 != 0) {
        actor->unk20 = param_12;
    } else {
        actor->unk20 = 0x3FF;
    }

    Actor_InsertIntoTypeList(actorCtx, actor, sp2C->type);

    goto dummy_label_;
dummy_label_:;

    sp20 = gSegments[6];
    Actor_Init(actor, globalCtx);
    gSegments[6] = sp20;

    goto dummy_label_47816;
dummy_label_47816:;

    return actor;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/Actor_SpawnAsChildAndCutscene.s")
#endif

Actor* Actor_SpawnAsChild(ActorContext* actorCtx, Actor* parent, GlobalContext* globalCtx, s16 actorId, f32 posX,
                          f32 posY, f32 posZ, s16 rotX, s16 rotY, s16 rotZ, s32 params) {
    return Actor_SpawnAsChildAndCutscene(actorCtx, globalCtx, actorId, posX, posY, posZ, rotX, rotY, rotZ, params, -1,
                                         parent->unk20, parent);
}

#ifdef NON_MATCHING
void Actor_SpawnTransitionActors(GlobalContext* globalCtx, ActorContext* actorCtx) {
    TransitionActorEntry* phi_s0;
    s32 phi_s2;
    s16 phi_v1;

    phi_s0 = globalCtx->doorCtx.transitionActorList;
    phi_v1 = globalCtx->doorCtx.numTransitionActors;

    for (phi_s2 = 0; phi_s2 < phi_v1; phi_s2++) {
        if ((phi_s0->id >= 0) &&
            (((phi_s0->sides[0].room >= 0) && ((globalCtx->roomCtx.currRoom.num == phi_s0->sides[0].room) ||
                                               (globalCtx->roomCtx.prevRoom.num == phi_s0->sides[0].room))) ||
             ((phi_s0->sides[1].room >= 0) && ((globalCtx->roomCtx.currRoom.num == phi_s0->sides[1].room) ||
                                               (globalCtx->roomCtx.prevRoom.num == phi_s0->sides[1].room))))) {
            s16 rotY = (((phi_s0->rotY) >> 7) & 0x1FF) * 182.04445f;

            if (Actor_SpawnAsChildAndCutscene(actorCtx, globalCtx, phi_s0->id & 0x1FFF, phi_s0->pos.x, phi_s0->pos.y,
                                              phi_s0->pos.z, 0, rotY, 0, (phi_s2 << 0xA) + ((phi_s0->params) & 0x3FF),
                                              phi_s0->pos.x & 0x7F, 0x3FF, 0) != 0) {
                phi_s0->id = -phi_s0->id;
            }
            phi_v1 = globalCtx->doorCtx.numTransitionActors;
        }
        phi_s0 += 1;
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/Actor_SpawnTransitionActors.s")
#endif

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BB2D0.s")

Actor* Actor_Delete(ActorContext* actorCtx, Actor* actor, GlobalContext* globalCtx) {
    s32 pad;
    Player* player = PLAYER;
    Actor* newHead;
    ActorOverlay* overlayEntry = actor->overlayEntry;

    if ((player != NULL) && (actor == player->unk_730)) {
        func_80123DA4(player);
        Camera_ChangeMode(Play_GetCamera(globalCtx, Play_GetActiveCameraIndex(globalCtx)), 0);
    }

    if (actor == actorCtx->targetContext.unk38) {
        actorCtx->targetContext.unk38 = NULL;
    }

    if (actor == actorCtx->targetContext.unk8C) {
        actorCtx->targetContext.unk8C = NULL;
    }

    if (actor == actorCtx->targetContext.unk90) {
        actorCtx->targetContext.unk90 = NULL;
    }

    func_801A72CC(&actor->projectedPos);
    Actor_Destroy(actor, globalCtx);

    newHead = Actor_RemoveFromTypeList(globalCtx, actorCtx, actor);
    zelda_free(actor);

    if (overlayEntry->vramStart != 0) {
        overlayEntry->numLoaded--;
        Actor_FreeOverlay(overlayEntry);
    }

    return newHead;
}

s32 func_800BB59C(GlobalContext* globalCtx, Actor* actor) {
    s16 sp1E;
    s16 sp1C;

    func_800B8898(globalCtx, actor, &sp1E, &sp1C);

    return (sp1E > -20) && (sp1E < gScreenWidth + 20) && (sp1C > -160) && (sp1C < gScreenHeight + 160);
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BB604.s")

UNK_TYPE1 D_801AED8C[] = {
    0x09, 0x05, 0x01, 0x03, 0x04, 0x07, 0x0B, 0x00, 0x06, 0x08, 0x0A, 0x00,
};

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BB8EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BBA88.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BBAC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BBB74.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BBC20.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BBCEC.s")

Vec3f D_801AED98 = {
    0.0f,
    0.300000011921f,
    0.0f,
};

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BBDAC.s")

Vec3f D_801AEDA4 = {
    0.0f,
    0.300000011921f,
    0.0f,
};

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BBFB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BC154.s")

s32 D_801AEDB0[] = {
    0x00000800, 0x00000020, 0x00000020, 0x00000800, 0x00001000, 0x00002000, 0x00000001, 0x00010000, 0x00000001,
};

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

typedef struct {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ Gfx* unk_14;
    /* 0x18 */ Gfx* unk_18;
} struct_801AEDD4; // size = 0x1C

struct_801AEDD4 D_801AEDD4[] = {
    { 0.540000021458f, 6000.0f, 5000.0, 1.0f, 0.0f, 0x05000230, 0x05000140 },

    { 0.643999993801f, 12000.0f, 8000.0f, 1.0f, 0.0f, 0x06000530, 0x06000400 },

    { 0.6400000453f, 8500.0f, 8000.0f, 1.75f, 0.10000000149f, 0x05000230, 0x05000140 },
};

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BC8B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BCB50.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BCB70.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BCBF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BCC68.s")

#ifdef NON_MATCHING
// small regalloc and needs to import data
void func_800BCCDC(Vec3s* points, s32 pathcount, Vec3f* pos1, Vec3f* pos2, s32 parm5) {
    s32 spB4;
    s32 spB0;
    s32 spA8[2] = { 0, 0 };
    s32 spA0[2] = { 0, 0 };
    Vec3f sp94;
    Vec3f sp7C[2];
    Vec3f sp70;
    Vec3f sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp54[2];

    spB0 = 0;
    sp5C = 1.6e9f;

    for (spB4 = 0; spB4 < pathcount; spB4++) {
        sp60 = Math3D_XZDistanceSquared(pos1->x, pos1->z, points[spB4].x, points[spB4].z);
        if (sp60 < sp5C) {
            sp5C = sp60;
            spB0 = spB4;
        }
    }

    sp94.x = points[spB0].x;
    sp94.z = points[spB0].z;
    pos2->y = points[spB0].y;
    if (spB0 != 0) {
        sp64.x = (f32)points[spB0 - 1].x;
        sp64.z = (f32)points[spB0 - 1].z;
    } else if (parm5) {
        sp64.x = (f32)points[pathcount - 1].x;
        sp64.z = (f32)points[pathcount - 1].z;
    }

    if ((spB0 != 0) || (parm5)) {
        spA8[0] =
            Math3D_PointDistToLine2D(pos1->x, pos1->z, sp64.x, sp64.z, sp94.x, sp94.z, &sp7C[0].x, &sp7C[0].z, &sp60);
    }

    if (spB0 + 1 != pathcount) {
        sp70.x = (f32)points[spB0 + 1].x;
        sp70.z = (f32)points[spB0 + 1].z;
    } else if (parm5) {
        sp70.x = (f32)points->x;
        sp70.z = (f32)points->z;
    }

    if ((spB0 + 1 != pathcount) || (parm5)) {
        spA8[1] =
            Math3D_PointDistToLine2D(pos1->x, pos1->z, sp94.x, sp94.z, sp70.x, sp70.z, &sp7C[1].x, &sp7C[1].z, &sp60);
    }

    if (parm5) {
        s32 phi_s0_2;

        spA0[0] = ((sp64.x - pos1->x) * (sp94.z - pos1->z)) < ((sp64.z - pos1->z) * (sp94.x - pos1->x));
        spA0[1] = ((sp70.z - pos1->z) * (sp94.x - pos1->x)) < ((sp94.z - pos1->z) * (sp70.x - pos1->x));

        for (phi_s0_2 = 0; phi_s0_2 < ARRAY_COUNT(sp54); phi_s0_2++) {
            if ((spA8)[phi_s0_2] != 0) {
                sp54[phi_s0_2] = Math3D_XZDistanceSquared(pos1->x, pos1->z, sp7C[phi_s0_2].x, sp7C[phi_s0_2].z);
            } else {
                sp54[phi_s0_2] = 1.6e9f;
            }
        }
    }

    if ((parm5) && (((spA0[0] != 0) && (spA0[1] != 0)) || ((spA0[0] != 0) && (spA8[0] != 0) && (sp54[0] < sp54[1])) ||
                    ((spA0[1] != 0) && (spA8[1] != 0) && (sp54[1] < sp54[0])))) {
        pos2->x = pos1->x;
        pos2->z = pos1->z;
    } else if ((spA8[0] != 0) && (spA8[1] != 0)) {
        if ((spA0[0] == 0) && (spA0[1] == 0)) {
            if (Math3D_PointDistToLine2D(pos1->x, pos1->z, sp7C[0].x, sp7C[0].z, sp7C[1].x, sp7C[1].z, &pos2->x,
                                         &pos2->z, &sp60) == 0) {
                pos2->x = (sp7C[1].x + sp7C[0].x) * 0.5f;
                pos2->z = (sp7C[1].z + sp7C[0].z) * 0.5f;
            }
        } else if (sp54[1] < sp54[0]) {
            pos2->x = sp7C[1].x;
            pos2->z = sp7C[1].z;
        } else {
            pos2->x = sp7C[0].x;
            pos2->z = sp7C[0].z;
        }
    } else if (spA8[0] != 0) {
        pos2->x = sp7C[0].x;
        pos2->z = sp7C[0].z;
    } else if (spA8[1] != 0) {
        pos2->x = sp7C[1].x;
        pos2->z = sp7C[1].z;
    } else if ((parm5) && ((((sp64.x - pos1->x) * (sp70.z - pos1->z)) < ((sp64.z - pos1->z) * (sp70.x - pos1->x))))) {
        pos2->x = pos1->x;
        pos2->z = pos1->z;
    } else {
        pos2->x = sp94.x;
        pos2->z = sp94.z;
    }
}
#else
s32 D_801AEE28[] = { 0, 0 };

s32 D_801AEE30[] = { 0, 0 };
#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BCCDC.s")
#endif

// unused
s32 func_800BD2B4(GlobalContext* globalCtx, Actor* actor, s16* arg2, f32 arg3, u16 (*arg4)(GlobalContext*, Actor*),
                  s16 (*arg5)(GlobalContext*, Actor*)) {
    if (Actor_IsTalking(actor, globalCtx) != 0) {
        *arg2 = 1;
        return 1;
    } else if (*arg2 != 0) {
        *arg2 = arg5(globalCtx, actor);
        return 0;
    } else if (func_800B8934(globalCtx, actor) == 0) {
        return 0;
    } else if (func_800B8614(actor, globalCtx, arg3) == 0) {
        return 0;
    } else {
        actor->textId = arg4(globalCtx, actor);
        return 0;
    }
}

typedef struct {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ u8 unk_0C;
} struct_801AEE38_0; // size = 0x10

typedef struct {
    /* 0x00 */ struct_801AEE38_0 sub_00;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ s16 unk_14;
} struct_801AEE38; // size = 0x18

struct_801AEE38 D_801AEE38[] = {
    { { 0x1C20, 0xE390, 0x1C70, 0x1554, 0, 0, 0 }, 170.0f, 0x3FFC },
    { { 0x2AA8, 0xEAAC, 0x1554, 0x1554, 0xF8E4, 0xE38, 1 }, 170.0f, 0x3FFC },
    { { 0x31C4, 0xE390, 0xE38, 0xE38, 0xF1C8, 0x71C, 1 }, 170.0f, 0x3FFC },
    { { 0x1554, 0xF1C8, 0, 0x71C, 0xF8E4, 0, 1 }, 170.0f, 0x3FFC },
    { { 0x2AA8, 0xF8E4, 0x71C, 0xE38, 0xD558, 0x2AA8, 1 }, 170.0f, 0x3FFC },
    { { 0, 0xE390, 0x2AA8, 0x3FFC, 0xF1C8, 0xE38, 1 }, 170.0f, 0x3FFC },
    { { 0x2AA8, 0xF1C8, 0xE38, 0xE38, 0, 0, 1 }, 0.0f, 0 },
    { { 0x2AA8, 0xF1C8, 0, 0xE38, 0, 0x1C70, 1 }, 0.0f, 0 },
    { { 0x2AA8, 0xF1C8, 0xF1C8, 0, 0, 0, 1 }, 0.0f, 0 },
    { { 0x71C, 0xF1C8, 0xE38, 0x1C70, 0, 0, 1 }, 0.0f, 0 },
    { { 0xE38, 0xF1C8, 0, 0x1C70, 0, 0xE38, 1 }, 0.0f, 0 },
    { { 0x2AA8, 0xE390, 0x1C70, 0xE38, 0xF1C8, 0xE38, 1 }, 0.0f, 0 },
    { { 0x18E2, 0xF1C8, 0xE38, 0xE38, 0, 0, 1 }, 0.0f, 0 },
    { { 0x2A6C, 0xE390, 0x1C70, 0x1554, 0, 0, 0 }, 170.0f, 0x3FFC },
};

void func_800BD384(Actor* actor, struct_800BD888_arg1* arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7,
                   u8 arg8) {
    s16 sp46;
    s16 sp44;
    s16 temp2;
    s16 sp40;
    s16 temp1;
    Vec3f sp30;

    sp30.x = actor->world.pos.x;
    sp30.y = actor->world.pos.y + arg1->unk_14;
    sp30.z = actor->world.pos.z;

    sp46 = Math_Vec3f_Pitch(&sp30, &arg1->unk_18);
    sp44 = Math_Vec3f_Yaw(&sp30, &arg1->unk_18);
    sp40 = Math_Vec3f_Yaw(&actor->world.pos, &arg1->unk_18) - actor->shape.rot.y;

    temp1 = CLAMP(sp40, -arg2, arg2);
    Math_SmoothStepToS(&arg1->unk_08.y, temp1, 6, 2000, 1);

    temp1 = (ABS_ALT(sp40) >= 0x8000) ? 0 : ABS_ALT(sp40);
    arg1->unk_08.y = CLAMP(arg1->unk_08.y, -temp1, temp1);

    sp40 -= arg1->unk_08.y;

    temp1 = CLAMP(sp40, -arg5, arg5);
    Math_SmoothStepToS(&arg1->unk_0E.y, temp1, 6, 2000, 1);

    temp1 = (ABS_ALT(sp40) >= 0x8000) ? 0 : ABS_ALT(sp40);
    arg1->unk_0E.y = CLAMP(arg1->unk_0E.y, -temp1, temp1);

    if (arg8) {
        Math_SmoothStepToS(&actor->shape.rot.y, sp44, 6, 2000, 1);
    }

    temp1 = CLAMP(sp46, arg4, (s16)(u16)arg3);
    Math_SmoothStepToS(&arg1->unk_08.x, temp1, 6, 2000, 1);

    temp2 = sp46 - arg1->unk_08.x;

    temp1 = CLAMP(temp2, arg7, arg6);
    Math_SmoothStepToS(&arg1->unk_0E.x, temp1, 6, 2000, 1);
}

// unused
s16 func_800BD6B8(s16 arg0) {
    return D_801AEE38[arg0].unk_14;
}

s16 func_800BD6E4(Actor* actor, struct_800BD888_arg1* arg1, f32 arg2, s16 arg3, s16 flag) {
    s32 pad;

    if (flag) {
        return flag;
    } else if (arg1->unk_00 != 0) {
        return 4;
    } else if (arg2 < Math_Vec3f_DistXYZ(&actor->world.pos, &arg1->unk_18)) {
        arg1->unk_04 = 0;
        arg1->unk_06 = 0;
        return 1;
    } else {
        s16 yaw = Math_Vec3f_Yaw(&actor->world.pos, &arg1->unk_18);
        s16 phi_a0 = ABS_ALT(BINANG_SUB(yaw, actor->shape.rot.y));

        if (arg3 >= phi_a0) {
            arg1->unk_04 = 0;
            arg1->unk_06 = 0;
            return 2;
        } else if (DECR(arg1->unk_04) != 0) {
            return arg1->unk_02;
        } else {
            switch (arg1->unk_06) {
                case 0:
                case 2:
                    arg1->unk_04 = Rand_S16Offset(30, 30);
                    arg1->unk_06++;
                    return 1;

                case 1:
                    arg1->unk_04 = Rand_S16Offset(10, 10);
                    arg1->unk_06++;
                    return 3;

                default:
                    return 4;
            }
        }
    }
}

// This function is very similar to OoT's func_80034A14
void func_800BD888(Actor* actor, struct_800BD888_arg1* arg1, s16 arg2, s16 arg3) {
    struct_801AEE38_0 sp38;

    arg1->unk_02 = func_800BD6E4(actor, arg1, D_801AEE38[arg2].unk_10, D_801AEE38[arg2].unk_14, arg3);
    sp38 = D_801AEE38[arg2].sub_00;

    switch (arg1->unk_02) {
        case 1:
            sp38.unk_00 = 0;
            sp38.unk_04 = 0;
            sp38.unk_02 = 0;
        case 3:
            sp38.unk_06 = 0;
            sp38.unk_0A = 0;
            sp38.unk_08 = 0;
        case 2:
            sp38.unk_0C = 0;
    }

    func_800BD384(actor, arg1, sp38.unk_00, sp38.unk_04, sp38.unk_02, sp38.unk_06, sp38.unk_0A, sp38.unk_08,
                  sp38.unk_0C);
}

Gfx D_801AEF88[] = {
    gsDPSetRenderMode(AA_EN | Z_CMP | Z_UPD | IM_RD | CLR_ON_CVG | CVG_DST_WRAP | ZMODE_XLU | FORCE_BL |
                          G_RM_FOG_SHADE_A,
                      AA_EN | Z_CMP | Z_UPD | IM_RD | CLR_ON_CVG | CVG_DST_WRAP | ZMODE_XLU | FORCE_BL |
                          GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)),
    gsDPSetAlphaCompare(G_AC_THRESHOLD),
    gsSPEndDisplayList(),
};

Gfx D_801AEFA0[] = {
    gsSPEndDisplayList(),
};

void* func_800BD9A0(GraphicsContext* gfxCtx) {
    Gfx* displayListHead;
    Gfx* displayList;

    displayListHead = displayList = GRAPH_ALLOC(gfxCtx, 0x10);

    gDPSetRenderMode(displayListHead++,
                     AA_EN | Z_CMP | Z_UPD | IM_RD | CLR_ON_CVG | CVG_DST_WRAP | ZMODE_XLU | FORCE_BL |
                         G_RM_FOG_SHADE_A,
                     AA_EN | Z_CMP | Z_UPD | IM_RD | CLR_ON_CVG | CVG_DST_WRAP | ZMODE_XLU | FORCE_BL |
                         GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA));
    gSPEndDisplayList(displayListHead++);

    return displayList;
}

// unused
void func_800BD9E0(GlobalContext* globalCtx, SkelAnime* skelAnime, OverrideLimbDraw2 overrideLimbDraw,
                   PostLimbDraw2 postLimbDraw, Actor* actor, s16 alpha) {
    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);

    gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, alpha);
    gSPSegment(POLY_OPA_DISP++, 0x0C, gEmptyDL);

    POLY_OPA_DISP = SkelAnime_DrawSV2(globalCtx, skelAnime->skeleton, skelAnime->limbDrawTbl, skelAnime->dListCount,
                                      overrideLimbDraw, postLimbDraw, actor, POLY_OPA_DISP);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_800BDAA0(GlobalContext* globalCtx, SkelAnime* skelAnime, OverrideLimbDraw2 overrideLimbDraw,
                   PostLimbDraw2 postLimbDraw, Actor* actor, s16 alpha) {
    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C2DC(globalCtx->state.gfxCtx);

    gDPSetEnvColor(POLY_XLU_DISP++, 0, 0, 0, alpha);
    gSPSegment(POLY_XLU_DISP++, 0x0C, func_800BD9A0(globalCtx->state.gfxCtx));

    POLY_XLU_DISP = SkelAnime_DrawSV2(globalCtx, skelAnime->skeleton, skelAnime->limbDrawTbl, skelAnime->dListCount,
                                      overrideLimbDraw, postLimbDraw, actor, POLY_XLU_DISP);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

// Unused
s16 func_800BDB6C(Actor* actor, GlobalContext* globalCtx, s16 arg2, f32 arg3) {
    Player* player = PLAYER;
    f32 phi_f2;

    if ((globalCtx->csCtx.state != 0) || (D_801D0D50 != 0)) {
        phi_f2 = Math_Vec3f_DistXYZ(&actor->world.pos, &globalCtx->view.eye) * 0.25f;
    } else {
        phi_f2 = Math_Vec3f_DistXYZ(&actor->world.pos, &player->actor.world.pos);
    }

    if (arg3 < phi_f2) {
        actor->flags &= -2;
        Math_SmoothStepToS(&arg2, 0, 6, 0x14, 1);
    } else {
        actor->flags |= 1;
        Math_SmoothStepToS(&arg2, 0xFF, 6, 0x14, 1);
    }

    return arg2;
}

void func_800BDC5C(SkelAnime* skelAnime, ActorAnimationEntry* animation, s32 index) {
    f32 frameCount;

    animation += index;
    if (animation->frameCount > 0.0f) {
        frameCount = animation->frameCount;
    } else {
        frameCount = SkelAnime_GetFrameCount(&animation->animation->common);
    }

    SkelAnime_ChangeAnim(skelAnime, animation->animation, animation->playSpeed, animation->startFrame, frameCount,
                         animation->mode, animation->morphFrames);
}

// Unused
void func_800BDCF4(GlobalContext* globalCtx, s16* arg1, s16* arg2, s32 size) {
    s32 frames = globalCtx->gameplayFrames;
    s32 i;

    for (i = 0; i < size; i++) {
        arg1[i] = (0x814 + 50 * i) * frames;
        arg2[i] = (0x940 + 50 * i) * frames;
    }
}

void Actor_Noop(Actor* actor, GlobalContext* globalCtx) {
}

void Gfx_DrawDListOpa(GlobalContext* globalCtx, Gfx* dlist) {
    Gfx* dl;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    dl = POLY_OPA_DISP;

    gSPDisplayList(&dl[0], &sSetupDL[6 * 0x19]);
    gSPMatrix(&dl[1], Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(&dl[2], dlist);

    POLY_OPA_DISP = &dl[3];

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/Gfx_DrawDListXlu.s")

Actor* func_800BE0B8(GlobalContext* globalCtx, Actor* inActor, s16 arg2, u8 arg3, f32 arg4) {
    Actor* actor = globalCtx->actorCtx.actorList[arg3].first;

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

UNK_TYPE4 D_801AEFA8[] = {
    0x04091DE0,
    0x04091FE0,
    0x040921E0,
    0x040923E0,
};

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BE680.s")

static Color_RGBA8 D_801AEFB8 = { 170, 255, 255, 255 };
static Color_RGBA8 D_801AEFBC = { 200, 200, 255, 255 };
static Vec3f D_801AEFC0 = { 0.0f, -1.0f, 0.0f };

#pragma GLOBAL_ASM("asm/non_matchings/code/z_actor/func_800BF7CC.s")
