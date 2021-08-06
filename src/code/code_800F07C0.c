#include "global.h"

s32 func_800F07C0(SkelAnime* skelAnime, s16 animIndex) {
    s16 frameCount;
    s32 ret = false;

    if (animIndex >= 0 && animIndex <= 20) {
        ret = true;
        frameCount = D_801BC2A0[animIndex].frameCount;
        if (frameCount < 0) {
            frameCount = SkelAnime_GetFrameCount(&D_801BC2A0[animIndex].animationSeg->common);
        }
        SkelAnime_ChangeAnim(skelAnime, D_801BC2A0[animIndex].animationSeg, D_801BC2A0[animIndex].playbackSpeed,
                             D_801BC2A0[animIndex].frame, frameCount, D_801BC2A0[animIndex].mode,
                             D_801BC2A0[animIndex].transitionRate);
    }
    return ret;
}

// FindNearestDoor
Actor* func_800F0888(Actor* actor, GlobalContext* globalCtx) {
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

void func_800F0944(struct_800F0944_arg0* arg0, GlobalContext* globalCtx, s16 animIndex) {
    gSegments[6] = PHYSICAL_TO_VIRTUAL(globalCtx->objectCtx.status[arg0->unk193].segment);
    func_800F07C0(&arg0->skelAnime, animIndex);
}

s32 func_800F09B4(struct_800F0944_arg0* arg0, GlobalContext* globalCtx) {
    s32 ret = false;

    if (arg0->actor.draw != NULL) {
        gSegments[6] = PHYSICAL_TO_VIRTUAL(globalCtx->objectCtx.status[arg0->unk193].segment);
        SkelAnime_FrameUpdateMatrix(&arg0->skelAnime);
        ret = true;
    }
    return ret;
}

void func_800F0A20(struct_800F0944_arg0 *arg0, s32 arg1) {
    if (DECR(arg0->unk3E8) == 0) {
        arg0->unk3E6 += 1;
        if (arg0->unk3E6 >= arg1) {
            arg0->unk3E6 = 0;
            arg0->unk3E8 = Rand_S16Offset(30, 30);
        }
    }
}

s32 func_800F0A94(struct_800F0944_arg0* arg0, GlobalContext* globalCtx, FlexSkeletonHeader* skeletonHeaderSeg,
                  s16 animIndex) {
    s32 ret = 0;

    if ((func_8013D8DC(arg0->unk193, globalCtx) == 1) && (func_8013D8DC(arg0->unk190, globalCtx) == 1) &&
        (func_8013D8DC(arg0->unk191, globalCtx) == 1) && (func_8013D8DC(arg0->unk192, globalCtx) == 1)) {
        arg0->actor.objBankIndex = arg0->unk192;
        ret = 1;
        ActorShape_Init(&arg0->actor.shape, 0.0f, NULL, 0.0f);
        gSegments[6] = PHYSICAL_TO_VIRTUAL(globalCtx->objectCtx.status[arg0->actor.objBankIndex].segment);
        SkelAnime_InitSV(globalCtx, &arg0->skelAnime, skeletonHeaderSeg, NULL, arg0->jointTable, arg0->morphTable, 16);
        func_800F0944(arg0, globalCtx, animIndex);
    }
    return ret;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/code_800F07C0/func_800F0BB4.s")

s32 func_800F0CE4(struct_800F0944_arg0* arg0, GlobalContext* globalCtx, ActorFunc draw, s16 arg3, s16 arg4, f32 arg5) {
    s32 ret;
    s16 yaw;
    Actor* door;
    s32 pad;

    ret = 0;
    if (func_8013D68C(arg0->path, arg0->unk1E8, &arg0->actor.world.pos)) {
        door = func_800F0888(&arg0->actor, globalCtx);
        if (door != NULL) {
            ret = 1;
            func_800F0BB4(arg0, globalCtx, door, arg3, arg4);
            yaw = Math_Vec3f_Yaw(&arg0->actor.world.pos, &door->world.pos);
            arg0->actor.world.pos.x += arg5 * Math_SinS(yaw);
            arg0->actor.world.pos.z += arg5 * Math_CosS(yaw);
            arg0->actor.world.rot.y = -yaw;
            arg0->actor.shape.rot.y = -yaw;
            arg0->actor.draw = draw;
        }
    }
    return ret;
}

s32 func_800F0DD4(struct_800F0944_arg0* arg0, GlobalContext* globalCtx, s16 arg2, s16 arg3) {
    s32 ret = 0;
    s32 pad;
    Actor* door;

    arg0->unk1E8 = 0;
    if (func_8013D68C(arg0->path, arg0->unk1E8, &arg0->actor.world.pos)) {
        door = func_800F0888(&arg0->actor, globalCtx);
        if (door != NULL) {
            ret = 1;
            func_800F0BB4(arg0, globalCtx, door, arg2, arg3);
            arg0->actor.shape.rot.y = Math_Vec3f_Yaw(&arg0->actor.world.pos, &door->world.pos);
            arg0->actor.world.rot.y = arg0->actor.shape.rot.y;
            arg0->actor.gravity = 0.0f;
            arg0->actor.flags &= ~1;
        }
    }
    return ret;
}

s32 func_800F0E94(struct_800F0944_arg0* arg0, GlobalContext* globalCtx, f32 gravity, s16 animIndex) {
    arg0->actor.gravity = gravity;
    arg0->actor.flags |= 1;
    func_800F0944(arg0, globalCtx, animIndex);
    arg0->unk1E8++;
    return 0;
}

s32 func_800F0EEC(struct_800F0944_arg0* arg0, GlobalContext* globalCtx, s16 animIndex) {
    func_800F0944(arg0, globalCtx, animIndex);
    arg0->unk1E8--;
    return 0;
}

s32 func_800F0F28(struct_800F0944_arg0* arg0, f32 arg1) {
    s16 sp3E;
    s32 ret;
    Vec3f sp2C;

    ret = 0;
    Math_SmoothStepToF(&arg0->actor.speedXZ, arg1, 0.4f, 1000.0f, 0.0f);
    sp3E = arg0->actor.speedXZ * 400.0f;
    if (func_8013D68C(arg0->path, arg0->unk1E8, &sp2C) && func_8013D768(&arg0->actor, &sp2C, sp3E)) {
        arg0->unk1E8++;
        if (arg0->unk1E8 >= arg0->path->count) {
            ret = 1;
        }
    }
    return ret;
}

s32 func_800F0FF0(struct_800F0944_arg0* arg0, f32 arg1) {
    s16 sp3E;
    s32 ret;
    Vec3f sp2C;

    ret = 0;
    Math_SmoothStepToF(&arg0->actor.speedXZ, arg1, 0.4f, 1000.0f, 0.0f);
    sp3E = arg0->actor.speedXZ * 400.0f;
    if (func_8013D68C(arg0->path, arg0->unk1E8, &sp2C) && func_8013D768(&arg0->actor, &sp2C, sp3E)) {
        arg0->unk1E8--;
        if (arg0->unk1E8 < 0) {
            ret = 1;
        }
    }
    return ret;
}

void func_800F10AC(struct_800F0944_arg0* arg0, GlobalContext* globalCtx) {
    arg0->collider.dim.pos.x = arg0->actor.world.pos.x;
    arg0->collider.dim.pos.y = arg0->actor.world.pos.y;
    arg0->collider.dim.pos.z = arg0->actor.world.pos.z;

    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &arg0->collider.base);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &arg0->collider.base);
}

s32 func_800F112C(struct_800F0944_arg0* arg0, GlobalContext* globalCtx, f32 arg2) {
    u8 prevUnk204 = arg0->unk204;
    u8 prevUnk205 = arg0->unk205;
    s32 pad;
    u16 sound;
    u8 tmp;

    if (arg0->actor.bgCheckFlags & 0x20) {
        sound = ((arg0->actor.yDistToWater < 20.0f) ? (NA_SE_PL_WALK_WATER0 - SFX_FLAG)
                                                    : (NA_SE_PL_WALK_WATER1 - SFX_FLAG)) +
                SFX_FLAG;
    } else {
        sound = func_800C9BDC(&globalCtx->colCtx, arg0->actor.floorPoly, arg0->actor.floorBgId) + SFX_FLAG;
    }
    arg0->unk204 = tmp = func_8013DB90(globalCtx, &arg0->unk1EC, arg2);
    if (arg0->unk204 != 0 && prevUnk204 == 0 && tmp != 0) {
        Audio_PlayActorSound2(&arg0->actor, sound);
    }
    arg0->unk205 = tmp = func_8013DB90(globalCtx, &arg0->unk1F8, arg2);
    if (arg0->unk205 != 0 && prevUnk205 == 0 && tmp != 0) {
        Audio_PlayActorSound2(&arg0->actor, sound);
    }
    return 0;
}
