/*
 * File: z_en_hy.c
 * Description: Unused System for NPCs (includes animation, door interaction, blinking, pathing, and collider helpers)
 */

#include "z_en_hy_code.h"
#include "overlays/actors/ovl_En_Door/z_en_door.h"
#include "objects/object_aob/object_aob.h"
#include "objects/object_bba/object_bba.h"
#include "objects/object_bji/object_bji.h"
#include "objects/object_boj/object_boj.h"
#include "objects/object_os_anime/object_os_anime.h"

static AnimationInfoS sAnimationInfo[] = {
    { &gMamamuYanUnusedIdleAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_boj_Anim_001494, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_boj_Anim_001494, 1.0f, 0, -1, ANIMMODE_LOOP, -8 },
    { &object_boj_Anim_001908, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_boj_Anim_001908, 1.0f, 0, -1, ANIMMODE_LOOP, -8 },
    { &object_boj_Anim_0008C0, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &gBbaIdleHoldingBagAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_bji_Anim_000FDC, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_bji_Anim_000AB0, 1.0f, 0, -1, ANIMMODE_LOOP, -8 },
    { &object_bji_Anim_00066C, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_boj_Anim_00071C, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_os_anime_Anim_001EE0, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_boj_Anim_00DED8, 1.5f, 0, -1, ANIMMODE_ONCE, 0 },
    { &object_boj_Anim_00F920, 1.5f, 0, -1, ANIMMODE_ONCE, 0 },
    { &object_boj_Anim_00FC1C, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_boj_Anim_00FEE4, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_boj_Anim_010330, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &object_boj_Anim_00FC1C, 1.0f, 0, -1, ANIMMODE_LOOP, -8 },
    { &object_boj_Anim_00FEE4, 1.0f, 0, -1, ANIMMODE_LOOP, -8 },
    { &object_boj_Anim_010330, 1.0f, 0, -1, ANIMMODE_LOOP, -8 },
    { &object_boj_Anim_005D9C, 1.0f, 0, -1, ANIMMODE_LOOP, -8 },
};

s8 gEnHyBodyParts[] = { -1, 1, 12, 13, 14, 9, 10, 11, 0, 6, 7, 8, 3, 4, 5, 2 };

s8 gEnHyParentBodyParts[] = { 0, 0, 0, 0, 3, 4, 0, 6, 7, 0, 9, 10, 0, 12, 13 };

u8 gEnHyShadowSizes[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s32 EnHy_ChangeAnim(SkelAnime* skelAnime, s16 animIndex) {
    s16 frameCount;
    s32 isChanged = false;

    if (animIndex >= ENHY_ANIM_AOB_0 && animIndex < ENHY_ANIM_MAX) {
        isChanged = true;
        frameCount = sAnimationInfo[animIndex].frameCount;
        if (frameCount < 0) {
            frameCount = Animation_GetLastFrame(&sAnimationInfo[animIndex].animation->common);
        }
        Animation_Change(skelAnime, sAnimationInfo[animIndex].animation, sAnimationInfo[animIndex].playSpeed,
                         sAnimationInfo[animIndex].startFrame, frameCount, sAnimationInfo[animIndex].mode,
                         sAnimationInfo[animIndex].morphFrames);
    }
    return isChanged;
}

EnDoor* EnHy_FindNearestDoor(Actor* actor, PlayState* play) {
    EnDoor* nearestDoor = NULL;
    Actor* doorIter = NULL;
    f32 dist;
    EnDoor* door;
    s32 isSetup = false;
    f32 minDist = 0.0f;

    do {
        doorIter = SubS_FindActor(play, doorIter, ACTORCAT_DOOR, ACTOR_EN_DOOR);
        door = (EnDoor*)doorIter;
        dist = Actor_DistanceBetweenActors(actor, &door->door.dyna.actor);
        if (!isSetup || (dist < minDist)) {
            nearestDoor = door;
            minDist = dist;
            isSetup = true;
        }
        doorIter = door->door.dyna.actor.next;
    } while (doorIter != NULL);

    if (1) {}

    return nearestDoor;
}

void EnHy_ChangeObjectAndAnim(EnHy* enHy, PlayState* play, s16 animIndex) {
    gSegments[6] = VIRTUAL_TO_PHYSICAL(play->objectCtx.status[enHy->animObjIndex].segment);
    EnHy_ChangeAnim(&enHy->skelAnime, animIndex);
}

s32 EnHy_UpdateSkelAnime(EnHy* enHy, PlayState* play) {
    s32 isUpdated = false;

    if (enHy->actor.draw != NULL) {
        gSegments[6] = VIRTUAL_TO_PHYSICAL(play->objectCtx.status[enHy->animObjIndex].segment);
        SkelAnime_Update(&enHy->skelAnime);
        isUpdated = true;
    }
    return isUpdated;
}

void EnHy_Blink(EnHy* enHy, s32 eyeTexMaxIndex) {
    if (DECR(enHy->blinkTimer) == 0) {
        enHy->eyeTexIndex++;
        if (enHy->eyeTexIndex >= eyeTexMaxIndex) {
            enHy->eyeTexIndex = 0;
            enHy->blinkTimer = Rand_S16Offset(30, 30);
        }
    }
}

s32 EnHy_Init(EnHy* enHy, PlayState* play, FlexSkeletonHeader* skeletonHeaderSeg, s16 animIndex) {
    s32 isInitialized = false;

    if ((SubS_IsObjectLoaded(enHy->animObjIndex, play) == true) &&
        (SubS_IsObjectLoaded(enHy->headObjIndex, play) == true) &&
        (SubS_IsObjectLoaded(enHy->skelUpperObjIndex, play) == true) &&
        (SubS_IsObjectLoaded(enHy->skelLowerObjIndex, play) == true)) {
        enHy->actor.objBankIndex = enHy->skelLowerObjIndex;
        isInitialized = true;
        ActorShape_Init(&enHy->actor.shape, 0.0f, NULL, 0.0f);
        gSegments[6] = VIRTUAL_TO_PHYSICAL(play->objectCtx.status[enHy->actor.objBankIndex].segment);
        SkelAnime_InitFlex(play, &enHy->skelAnime, skeletonHeaderSeg, NULL, enHy->jointTable, enHy->morphTable,
                           ENHY_LIMB_MAX);
        EnHy_ChangeObjectAndAnim(enHy, play, animIndex);
    }

    return isInitialized;
}

void func_800F0BB4(EnHy* enHy, PlayState* play, EnDoor* door, s16 arg3, s16 arg4) {
    s32 pad;
    s8 animIndex;
    Vec3f offset;
    f32 phi_f0;

    Actor_OffsetOfPointInActorCoords(&door->door.dyna.actor, &offset, &enHy->actor.world.pos);
    phi_f0 = (offset.z >= 0.0f) ? 1.0f : -1.0f;
    animIndex = ((s8)phi_f0 < 0) ? 0 : 2;
    EnHy_ChangeObjectAndAnim(enHy, play, (animIndex == 0) ? arg3 : arg4);
    enHy->skelAnime.baseTransl = *enHy->skelAnime.jointTable;
    enHy->skelAnime.prevTransl = *enHy->skelAnime.jointTable;
    enHy->skelAnime.moveFlags |= (ANIM_FLAG_UPDATE_Y | ANIM_FLAG_1);
    AnimationContext_SetMoveActor(play, &enHy->actor, &enHy->skelAnime, 1.0f);
    door->door.playOpenAnim = true;
    door->door.animIndex = animIndex;
}

s32 func_800F0CE4(EnHy* enHy, PlayState* play, ActorFunc draw, s16 arg3, s16 arg4, f32 arg5) {
    s32 ret = false;
    s16 yaw;
    EnDoor* door;
    s32 pad;

    if (SubS_CopyPointFromPath(enHy->path, enHy->curPoint, &enHy->actor.world.pos)) {
        door = EnHy_FindNearestDoor(&enHy->actor, play);
        if (door != NULL) {
            ret = true;
            func_800F0BB4(enHy, play, door, arg3, arg4);
            yaw = Math_Vec3f_Yaw(&enHy->actor.world.pos, &door->door.dyna.actor.world.pos);
            enHy->actor.world.pos.x += arg5 * Math_SinS(yaw);
            enHy->actor.world.pos.z += arg5 * Math_CosS(yaw);
            enHy->actor.world.rot.y = -yaw;
            enHy->actor.shape.rot.y = -yaw;
            enHy->actor.draw = draw;
        }
    }
    return ret;
}

s32 func_800F0DD4(EnHy* enHy, PlayState* play, s16 arg2, s16 arg3) {
    s32 ret = false;
    s32 pad;
    EnDoor* door;

    enHy->curPoint = 0;
    if (SubS_CopyPointFromPath(enHy->path, enHy->curPoint, &enHy->actor.world.pos)) {
        door = EnHy_FindNearestDoor(&enHy->actor, play);
        if (door != NULL) {
            ret = true;
            func_800F0BB4(enHy, play, door, arg2, arg3);
            enHy->actor.shape.rot.y = Math_Vec3f_Yaw(&enHy->actor.world.pos, &door->door.dyna.actor.world.pos);
            enHy->actor.world.rot.y = enHy->actor.shape.rot.y;
            enHy->actor.gravity = 0.0f;
            enHy->actor.flags &= ~ACTOR_FLAG_1;
        }
    }
    return ret;
}

s32 EnHy_SetPointFowards(EnHy* enHy, PlayState* play, f32 gravity, s16 animIndex) {
    enHy->actor.gravity = gravity;
    enHy->actor.flags |= ACTOR_FLAG_1;
    EnHy_ChangeObjectAndAnim(enHy, play, animIndex);
    enHy->curPoint++;
    return false;
}

s32 EnHy_SetPointBackwards(EnHy* enHy, PlayState* play, s16 animIndex) {
    EnHy_ChangeObjectAndAnim(enHy, play, animIndex);
    enHy->curPoint--;
    return false;
}

s32 EnHy_MoveForwards(EnHy* enHy, f32 speedTarget) {
    s16 rotStep;
    s32 reachedEnd = false;
    Vec3f curPointPos;

    Math_SmoothStepToF(&enHy->actor.speedXZ, speedTarget, 0.4f, 1000.0f, 0.0f);
    rotStep = enHy->actor.speedXZ * 400.0f;
    if (SubS_CopyPointFromPath(enHy->path, enHy->curPoint, &curPointPos) &&
        SubS_MoveActorToPoint(&enHy->actor, &curPointPos, rotStep)) {
        enHy->curPoint++;
        if (enHy->curPoint >= enHy->path->count) {
            reachedEnd = true;
        }
    }

    return reachedEnd;
}

s32 EnHy_MoveBackwards(EnHy* enHy, f32 speedTarget) {
    s16 rotStep;
    s32 reachedEnd = false;
    Vec3f curPointPos;

    Math_SmoothStepToF(&enHy->actor.speedXZ, speedTarget, 0.4f, 1000.0f, 0.0f);
    rotStep = enHy->actor.speedXZ * 400.0f;
    if (SubS_CopyPointFromPath(enHy->path, enHy->curPoint, &curPointPos) &&
        SubS_MoveActorToPoint(&enHy->actor, &curPointPos, rotStep)) {
        enHy->curPoint--;
        if (enHy->curPoint < 0) {
            reachedEnd = true;
        }
    }

    return reachedEnd;
}

void EnHy_UpdateCollider(EnHy* enHy, PlayState* play) {
    enHy->collider.dim.pos.x = enHy->actor.world.pos.x;
    enHy->collider.dim.pos.y = enHy->actor.world.pos.y;
    enHy->collider.dim.pos.z = enHy->actor.world.pos.z;

    CollisionCheck_SetAC(play, &play->colChkCtx, &enHy->collider.base);
    CollisionCheck_SetOC(play, &play->colChkCtx, &enHy->collider.base);
}

s32 EnHy_PlayWalkingSound(EnHy* enHy, PlayState* play, f32 distAboveThreshold) {
    u8 wasLeftFootOnGround = enHy->isLeftFootOnGround;
    u8 wasRightFootOnGround = enHy->isRightFootOnGround;
    s32 waterSfxId;
    u16 sfxId;
    u8 isFootOnGround;

    if (enHy->actor.bgCheckFlags & 0x20) {
        if (enHy->actor.depthInWater < 20.0f) {
            waterSfxId = NA_SE_PL_WALK_WATER0 - SFX_FLAG;
        } else {
            waterSfxId = NA_SE_PL_WALK_WATER1 - SFX_FLAG;
        }
        sfxId = waterSfxId + SFX_FLAG;
    } else {
        sfxId = SurfaceType_GetSfxIdOffset(&play->colCtx, enHy->actor.floorPoly, enHy->actor.floorBgId) + SFX_FLAG;
    }

    enHy->isLeftFootOnGround = isFootOnGround = SubS_IsFloorAbove(play, &enHy->leftFootPos, distAboveThreshold);
    if (enHy->isLeftFootOnGround && !wasLeftFootOnGround && isFootOnGround) {
        Actor_PlaySfxAtPos(&enHy->actor, sfxId);
    }

    enHy->isRightFootOnGround = isFootOnGround = SubS_IsFloorAbove(play, &enHy->rightFootPos, distAboveThreshold);
    if (enHy->isRightFootOnGround && !wasRightFootOnGround && isFootOnGround) {
        Actor_PlaySfxAtPos(&enHy->actor, sfxId);
    }

    return false;
}
