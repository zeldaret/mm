/*
 * File: z_sub_s.c
 * Description: Various miscellaneous helpers
 */

#include "global.h"
#include "overlays/actors/ovl_En_Door/z_en_door.h"

/**
 * Finds the first EnDoor instance with unk_1A4 == 5 and the specified unk_1A5.
 */
EnDoor* SubS_FindDoor(GlobalContext* globalCtx, s32 unk_1A5) {
    Actor* actor = NULL;
    EnDoor* door;

    while (true) {
        actor = SubS_FindActor(globalCtx, actor, ACTORCAT_DOOR, ACTOR_EN_DOOR);
        door = (EnDoor*)actor;

        if (actor == NULL) {
            break;
        }

        if ((door->unk_1A4 == 5) && (door->unk_1A5 == (u8)unk_1A5)) {
            break;
        }

        if (actor->next == NULL) {
            door = NULL;
            break;
        }

        actor = actor->next;
    }

    return door;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013A860.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013AB00.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013AD6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013AD9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013AED4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013AF00.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013B010.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013B0C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013B350.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013B6B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013B878.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013BB34.s")

/**
 * Finds the nearest actor instance of a specified Id and category to an actor.
 */
Actor* SubS_FindNearestActor(Actor* actor, GlobalContext* globalCtx, u8 actorCategory, s16 actorId) {
    Actor* actorIter = NULL;
    Actor* actorTmp;
    f32 dist;
    Actor* closestActor = NULL;
    f32 minDist = 99999.0f;
    s32 isSetup = false;

    do {
        actorIter = SubS_FindActor(globalCtx, actorIter, actorCategory, actorId);

        actorTmp = actorIter;
        if (actorTmp == NULL) {
            break;
        }
        actorIter = actorTmp;

        if (actorIter != actor) {
            dist = Actor_DistanceBetweenActors(actor, actorIter);
            if (!isSetup || dist < minDist) {
                closestActor = actorIter;
                minDist = dist;
                isSetup = true;
            }
        }

        actorIter = actorIter->next;
    } while (actorIter != NULL);

    return closestActor;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013BC6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013BD40.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013BEDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013C068.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013C624.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013C8B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013C964.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013CC2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013CD64.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013CF04.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013D0E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013D2E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013D5E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013D648.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013D68C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013D720.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013D768.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013D83C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013D8DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013D924.s")

/**
 * Finds the first actor instance of a specified Id and category.
 */
Actor* SubS_FindActor(GlobalContext* globalCtx, Actor* actorListStart, u8 actorCategory, s16 actorId) {
    Actor* actor = actorListStart;

    if (actor == NULL) {
        actor = globalCtx->actorCtx.actorLists[actorCategory].first;
    }

    while (actor != NULL && actorId != actor->id) {
        actor = actor->next;
    }

    return actor;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013D9C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013DB90.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013DC40.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013DCCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013DCE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013DE04.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013DF3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013E054.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013E07C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013E0A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013E1C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013E2D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013E3B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013E4B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013E5CC.s")

/**
 * Finds the first actor instance of a specified Id and category verified with a custom callback.
 * The callback should return `true` when the actor is succesfully verified.
 */
Actor* SubS_FindActorCustom(GlobalContext* globalCtx, Actor* actor, Actor* actorListStart, u8 actorCategory,
                            s16 actorId, void* verifyData, VerifyActor verifyActor) {
    Actor* actorIter = actorListStart;

    if (actorListStart == NULL) {
        actorIter = globalCtx->actorCtx.actorLists[actorCategory].first;
    }

    while (actorIter != NULL && (actorId != actorIter->id ||
                                 (actorId == actorIter->id &&
                                  (verifyActor == NULL ||
                                   (verifyActor != NULL && !verifyActor(globalCtx, actor, actorIter, verifyData)))))) {
        actorIter = actorIter->next;
    }

    return actorIter;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013E748.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013E7C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013E8F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_sub_s/func_8013E950.s")
