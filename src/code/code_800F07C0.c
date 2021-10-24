#include "global.h"
#include "overlays/actors/ovl_En_Door/z_en_door.h"

extern AnimationHeader D_0600007C;
extern AnimationHeader D_0600066C;
extern AnimationHeader D_0600071C;
extern AnimationHeader D_060008C0;
extern AnimationHeader D_06000AB0;
extern AnimationHeader D_06000FDC;
extern AnimationHeader D_06001494;
extern AnimationHeader D_06001908;
extern AnimationHeader D_06001EE0;
extern AnimationHeader D_06005DC4;
extern AnimationHeader D_06005D9C;
extern AnimationHeader D_0600DED8;
extern AnimationHeader D_0600F920;
extern AnimationHeader D_0600FC1C;
extern AnimationHeader D_0600FEE4;
extern AnimationHeader D_06010330;

static ActorAnimationEntryS animations[] = {
    { &D_0600007C, 1.0f, 0, -1, 0, 0 },  { &D_06001494, 1.0f, 0, -1, 0, 0 },  { &D_06001494, 1.0f, 0, -1, 0, -8 },
    { &D_06001908, 1.0f, 0, -1, 0, 0 },  { &D_06001908, 1.0f, 0, -1, 0, -8 }, { &D_060008C0, 1.0f, 0, -1, 0, 0 },
    { &D_06005DC4, 1.0f, 0, -1, 0, 0 },  { &D_06000FDC, 1.0f, 0, -1, 0, 0 },  { &D_06000AB0, 1.0f, 0, -1, 0, -8 },
    { &D_0600066C, 1.0f, 0, -1, 0, 0 },  { &D_0600071C, 1.0f, 0, -1, 0, 0 },  { &D_06001EE0, 1.0f, 0, -1, 0, 0 },
    { &D_0600DED8, 1.5f, 0, -1, 2, 0 },  { &D_0600F920, 1.5f, 0, -1, 2, 0 },  { &D_0600FC1C, 1.0f, 0, -1, 0, 0 },
    { &D_0600FEE4, 1.0f, 0, -1, 0, 0 },  { &D_06010330, 1.0f, 0, -1, 0, 0 },  { &D_0600FC1C, 1.0f, 0, -1, 0, -8 },
    { &D_0600FEE4, 1.0f, 0, -1, 0, -8 }, { &D_06010330, 1.0f, 0, -1, 0, -8 }, { &D_06005D9C, 1.0f, 0, -1, 0, -8 },
};

s8 D_801BC3F0[] = { -1, 1, 12, 13, 14, 9, 10, 11, 0, 6, 7, 8, 3, 4, 5, 2 };

UNK_TYPE D_801BC400[] = { 0x00000000, 0x03040006, 0x0700090A, 0x000C0D00 };

UNK_TYPE D_801BC410[] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000 };

s32 UnusedNPC_ChangeAnim(SkelAnime* skelAnime, s16 animIndex) {
    s16 frameCount;
    s32 ret = false;

    if (animIndex >= 0 && animIndex <= 20) {
        ret = true;
        frameCount = animations[animIndex].frameCount;
        if (frameCount < 0) {
            frameCount = Animation_GetLastFrame(&animations[animIndex].animationSeg->common);
        }
        Animation_Change(skelAnime, animations[animIndex].animationSeg, animations[animIndex].playbackSpeed,
                         animations[animIndex].frame, frameCount, animations[animIndex].mode,
                         animations[animIndex].transitionRate);
    }
    return ret;
}

//! @TODO: Return Door instance when c and h files are split
Actor* UnusedNPC_FindNearestDoor(Actor* actor, GlobalContext* globalCtx) {
    Actor* doorIter;
    Actor* door;
    f32 dist;
    s32 haveFound;
    f32 minDist;
    Actor* nearestDoor;

    nearestDoor = NULL;
    doorIter = NULL;
    haveFound = false;
    minDist = 0.0f;

    do {
        do {
            doorIter = func_ActorCategoryIterateById(globalCtx, doorIter, ACTORCAT_DOOR, ACTOR_EN_DOOR);
            door = doorIter;
            dist = Actor_DistanceBetweenActors(actor, door);
            if (!haveFound || (dist < minDist)) {
                nearestDoor = door;
                minDist = dist;
                haveFound = true;
            }
            doorIter = door->next;
        } while (doorIter != NULL);
    } while (0);

    return nearestDoor;
}

void UnusedNPC_ChangeObjectAndAnim(UnusedNPC* unusedNPC, GlobalContext* globalCtx, s16 animIndex) {
    gSegments[6] = PHYSICAL_TO_VIRTUAL(globalCtx->objectCtx.status[unusedNPC->animObjIndex].segment);
    UnusedNPC_ChangeAnim(&unusedNPC->skelAnime, animIndex);
}

s32 UnusedNPC_UpdateSkelAnime(UnusedNPC* unusedNPC, GlobalContext* globalCtx) {
    s32 ret = false;

    if (unusedNPC->actor.draw != NULL) {
        gSegments[6] = PHYSICAL_TO_VIRTUAL(globalCtx->objectCtx.status[unusedNPC->animObjIndex].segment);
        SkelAnime_Update(&unusedNPC->skelAnime);
        ret = true;
    }
    return ret;
}

void UnusedNPC_Blink(UnusedNPC* unusedNPC, s32 eyeTexMaxIndex) {
    if (DECR(unusedNPC->blinkTimer) == 0) {
        unusedNPC->eyeTexIndex += 1;
        if (unusedNPC->eyeTexIndex >= eyeTexMaxIndex) {
            unusedNPC->eyeTexIndex = 0;
            unusedNPC->blinkTimer = Rand_S16Offset(30, 30);
        }
    }
}

s32 UnusedNPC_Init(UnusedNPC* unusedNPC, GlobalContext* globalCtx, FlexSkeletonHeader* skeletonHeaderSeg,
                   s16 animIndex) {
    s32 ret = false;

    if ((func_8013D8DC(unusedNPC->animObjIndex, globalCtx) == 1) &&
        (func_8013D8DC(unusedNPC->unk190, globalCtx) == 1) && (func_8013D8DC(unusedNPC->unk191, globalCtx) == 1) &&
        (func_8013D8DC(unusedNPC->unk192, globalCtx) == 1)) {
        unusedNPC->actor.objBankIndex = unusedNPC->unk192;
        ret = true;
        ActorShape_Init(&unusedNPC->actor.shape, 0.0f, NULL, 0.0f);
        gSegments[6] = PHYSICAL_TO_VIRTUAL(globalCtx->objectCtx.status[unusedNPC->actor.objBankIndex].segment);
        SkelAnime_InitFlex(globalCtx, &unusedNPC->skelAnime, skeletonHeaderSeg, NULL, unusedNPC->jointTable,
                           unusedNPC->morphTable, 16);
        UnusedNPC_ChangeObjectAndAnim(unusedNPC, globalCtx, animIndex);
    }
    return ret;
}

//! @TODO: Should just take EnDoor instead of actor when c and h are split
void func_800F0BB4(UnusedNPC* unusedNPC, GlobalContext* globalCtx, Actor* door, s16 arg3, s16 arg4) {
    s32 pad;
    s8 sp3B;
    Vec3f offset;
    f32 phi_f0;

    Actor_CalcOffsetOrientedToDrawRotation(door, &offset, &unusedNPC->actor.world.pos);
    phi_f0 = (offset.z >= 0.0f) ? 1.0f : -1.0f;
    sp3B = ((s8)phi_f0 < 0) ? 0 : 2;
    UnusedNPC_ChangeObjectAndAnim(unusedNPC, globalCtx, (sp3B == 0) ? arg3 : arg4);
    unusedNPC->skelAnime.baseTransl = *unusedNPC->skelAnime.jointTable;
    unusedNPC->skelAnime.prevTransl = *unusedNPC->skelAnime.jointTable;
    unusedNPC->skelAnime.moveFlags |= 3;
    AnimationContext_SetMoveActor(globalCtx, &unusedNPC->actor, &unusedNPC->skelAnime, 1.0f);
    ((EnDoor*)door)->unk1A1 = 1;
    ((EnDoor*)door)->unk1A0 = sp3B;
}

s32 func_800F0CE4(UnusedNPC* unusedNPC, GlobalContext* globalCtx, ActorFunc draw, s16 arg3, s16 arg4, f32 arg5) {
    s32 ret;
    s16 yaw;
    Actor* door;
    s32 pad;

    ret = false;
    if (func_8013D68C(unusedNPC->path, unusedNPC->curPoint, &unusedNPC->actor.world.pos)) {
        door = UnusedNPC_FindNearestDoor(&unusedNPC->actor, globalCtx);
        if (door != NULL) {
            ret = true;
            func_800F0BB4(unusedNPC, globalCtx, door, arg3, arg4);
            yaw = Math_Vec3f_Yaw(&unusedNPC->actor.world.pos, &door->world.pos);
            unusedNPC->actor.world.pos.x += arg5 * Math_SinS(yaw);
            unusedNPC->actor.world.pos.z += arg5 * Math_CosS(yaw);
            unusedNPC->actor.world.rot.y = -yaw;
            unusedNPC->actor.shape.rot.y = -yaw;
            unusedNPC->actor.draw = draw;
        }
    }
    return ret;
}

s32 func_800F0DD4(UnusedNPC* unusedNPC, GlobalContext* globalCtx, s16 arg2, s16 arg3) {
    s32 ret = 0;
    s32 pad;
    Actor* door;

    unusedNPC->curPoint = 0;
    if (func_8013D68C(unusedNPC->path, unusedNPC->curPoint, &unusedNPC->actor.world.pos)) {
        door = UnusedNPC_FindNearestDoor(&unusedNPC->actor, globalCtx);
        if (door != NULL) {
            ret = 1;
            func_800F0BB4(unusedNPC, globalCtx, door, arg2, arg3);
            unusedNPC->actor.shape.rot.y = Math_Vec3f_Yaw(&unusedNPC->actor.world.pos, &door->world.pos);
            unusedNPC->actor.world.rot.y = unusedNPC->actor.shape.rot.y;
            unusedNPC->actor.gravity = 0.0f;
            unusedNPC->actor.flags &= ~1;
        }
    }
    return ret;
}

s32 func_800F0E94(UnusedNPC* unusedNPC, GlobalContext* globalCtx, f32 gravity, s16 animIndex) {
    unusedNPC->actor.gravity = gravity;
    unusedNPC->actor.flags |= 1;
    UnusedNPC_ChangeObjectAndAnim(unusedNPC, globalCtx, animIndex);
    unusedNPC->curPoint++;
    return 0;
}

s32 func_800F0EEC(UnusedNPC* unusedNPC, GlobalContext* globalCtx, s16 animIndex) {
    UnusedNPC_ChangeObjectAndAnim(unusedNPC, globalCtx, animIndex);
    unusedNPC->curPoint--;
    return 0;
}

s32 UnusedNPC_MoveForwards(UnusedNPC* unusedNPC, f32 speedTarget) {
    s16 rotStep;
    s32 reachedEnd;
    Vec3f curPointPos;

    reachedEnd = false;
    Math_SmoothStepToF(&unusedNPC->actor.speedXZ, speedTarget, 0.4f, 1000.0f, 0.0f);
    rotStep = unusedNPC->actor.speedXZ * 400.0f;
    if (func_8013D68C(unusedNPC->path, unusedNPC->curPoint, &curPointPos) && func_8013D768(&unusedNPC->actor, &curPointPos, rotStep)) {
        unusedNPC->curPoint++;
        if (unusedNPC->curPoint >= unusedNPC->path->count) {
            reachedEnd = true;
        }
    }
    return reachedEnd;
}

s32 UnusedNPC_MoveBackwards(UnusedNPC* unusedNPC, f32 speedTarget) {
    s16 rotStep;
    s32 reachedEnd;
    Vec3f curPointPos;

    reachedEnd = false;
    Math_SmoothStepToF(&unusedNPC->actor.speedXZ, speedTarget, 0.4f, 1000.0f, 0.0f);
    rotStep = unusedNPC->actor.speedXZ * 400.0f;
    if (func_8013D68C(unusedNPC->path, unusedNPC->curPoint, &curPointPos) && func_8013D768(&unusedNPC->actor, &curPointPos, rotStep)) {
        unusedNPC->curPoint--;
        if (unusedNPC->curPoint < 0) {
            reachedEnd = true;
        }
    }
    return reachedEnd;
}

void UnusedNPC_UpdateCollider(UnusedNPC* unusedNPC, GlobalContext* globalCtx) {
    unusedNPC->collider.dim.pos.x = unusedNPC->actor.world.pos.x;
    unusedNPC->collider.dim.pos.y = unusedNPC->actor.world.pos.y;
    unusedNPC->collider.dim.pos.z = unusedNPC->actor.world.pos.z;

    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &unusedNPC->collider.base);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &unusedNPC->collider.base);
}

s32 UnusedNPC_PlayWalkingSound(UnusedNPC* unusedNPC, GlobalContext* globalCtx, f32 distAboveThreshold) {
    u8 wasLeftFootOnGround = unusedNPC->isLeftFootOnGround;
    u8 wasRightFootOnGround = unusedNPC->isRightFootOnGround;
    s32 pad;
    u16 sound;
    u8 isFootOnGround;

    if (unusedNPC->actor.bgCheckFlags & 0x20) {
        sound = ((unusedNPC->actor.yDistToWater < 20.0f) ? (NA_SE_PL_WALK_WATER0 - SFX_FLAG)
                                                         : (NA_SE_PL_WALK_WATER1 - SFX_FLAG)) +
                SFX_FLAG;
    } else {
        sound = func_800C9BDC(&globalCtx->colCtx, unusedNPC->actor.floorPoly, unusedNPC->actor.floorBgId) + SFX_FLAG;
    }
    unusedNPC->isLeftFootOnGround = isFootOnGround =
        func_8013DB90(globalCtx, &unusedNPC->leftFootPos, distAboveThreshold);
    if (unusedNPC->isLeftFootOnGround && !wasLeftFootOnGround && isFootOnGround) {
        Audio_PlayActorSound2(&unusedNPC->actor, sound);
    }
    unusedNPC->isRightFootOnGround = isFootOnGround =
        func_8013DB90(globalCtx, &unusedNPC->rightFootPos, distAboveThreshold);
    if (unusedNPC->isRightFootOnGround && !wasRightFootOnGround && isFootOnGround) {
        Audio_PlayActorSound2(&unusedNPC->actor, sound);
    }
    return 0;
}
