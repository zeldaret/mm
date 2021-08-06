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

#pragma GLOBAL_ASM("asm/non_matchings/code/code_800F07C0/func_800F0A20.s")

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

#pragma GLOBAL_ASM("asm/non_matchings/code/code_800F07C0/func_800F0CE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_800F07C0/func_800F0DD4.s")

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

#pragma GLOBAL_ASM("asm/non_matchings/code/code_800F07C0/func_800F0F28.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_800F07C0/func_800F0FF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_800F07C0/func_800F10AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_800F07C0/func_800F112C.s")
