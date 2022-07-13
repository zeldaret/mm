#include "global.h"
#include "overlays/actors/ovl_En_Kakasi/z_en_kakasi.h"

/**
 * Test every loaded actor to see if it is a pictographable `PictoActor`, and if so, run its `pictoFunc` to set
 * appropriate flags.
 *
 * @return s32 Number of pictograph actors validly captured.
 */
s32 Snap_RecordPictographedActors(PlayState* play) {
    PictoActor* pictoActor;
    Actor* actor;
    s32 category = ACTORCAT_SWITCH;
    s32 seen;
    s32 count = 0;

    gSaveContext.save.pictoFlags0 = 0;
    gSaveContext.save.pictoFlags1 = 0;

    if (play->sceneNum == SCENE_20SICHITAI) {
        Snap_SetFlag(1);
    }

    for (; category < ACTORCAT_MAX; category++) {
        for (actor = play->actorCtx.actorLists[category].first; actor != NULL; actor = actor->next) {
            seen = 0;

            // Actors which must be pictographed in a specific scene
            switch (play->sceneNum) {
                case SCENE_20SICHITAI:
                    if ((actor->id == ACTOR_EN_MNK) || (actor->id == ACTOR_EN_BIGOKUTA)) {
                        seen = 1;
                    }
                    break;

                default:
                    seen = 0;
                    break;
            }

            if (actor->id) {
                ; // Needed to match
            }

            // Actors which may be pictographed anywhere
            switch (actor->id) {
                case ACTOR_EN_KAKASI:
                    if (GET_KAKASI_ABOVE_GROUND(actor) == 1) {
                        seen |= 2;
                        break; //! @bug break is inside conditional, meaning it falls through if it is false
                    }
                case ACTOR_EN_ZOV:
                    seen |= 2;
                    break;

                case ACTOR_EN_BAL:
                    seen |= 2;
                    break;

                case ACTOR_EN_DNQ:
                    seen |= 2;
                    break;

                case ACTOR_EN_GE1:
                case ACTOR_EN_GE3:
                case ACTOR_EN_KAIZOKU:
                case ACTOR_EN_GE2:
                    seen |= 2;
                    break;
            }

            // If actor is recordable, run its validity function and record if valid
            if (seen != 0) {
                pictoActor = (PictoActor*)actor;
                if (pictoActor->pictoFunc != NULL) {
                    if ((pictoActor->pictoFunc)(play, actor) == 0) {
                        count++;
                    }
                }
            }
        }
    }

    return count;
}

// Only used by Snap_ValidatePictograph
void Snap_SetFlag(s32 flag) {
    if (flag < 0x20) {
        gSaveContext.save.pictoFlags0 |= (1 << flag);
    } else {
        flag &= 0x1F;
        gSaveContext.save.pictoFlags1 |= (1 << flag);
    }
}

// Unused
void Snap_UnsetFlag(s32 flag) {
    if (flag < 0x20) {
        gSaveContext.save.pictoFlags0 &= ~(1 << flag);
    } else {
        flag &= 0x1F;
        gSaveContext.save.pictoFlags1 &= ~(1 << flag);
    }
}

u32 Snap_CheckFlag(s32 flag) {
    SaveContext* saveCtx = &gSaveContext;

    if (flag < 0x20) {
        return saveCtx->save.pictoFlags0 & (1 << flag);
    } else {
        flag &= 0x1F;
        return saveCtx->save.pictoFlags1 & (1 << flag);
    }
}

s16 Snap_AbsS(s16 val) {
    return ABS(val);
}

/**
 * Test if a pictograph is a valid pictograph of an actor
 *
 * @param play
 * @param actor Actor to test
 * @param flag Flag to set if checks successful
 * @param pos position of point to test (generally a particular point in the actor's model)
 * @param rot rotation of point to test (for facing camera)
 * @param distanceMin closest point may be
 * @param distanceMax farthest away point may be
 * @param angleRange Size of range that counts as facing the camera (-1 is used for any allowed)
 * @return s32 0 on success, `or`ed combination of the validity flags if not
 *
 * @note It is generally not possible to recover the actual failure mode(s) from the return value)
 */
s32 Snap_ValidatePictograph(PlayState* play, Actor* actor, s32 flag, Vec3f* pos, Vec3s* rot, f32 distanceMin, f32 distanceMax,
                  s16 angleRange) {
    Vec3f projectedPos;
    s16 x;
    s16 y;
    f32 distance;
    CollisionPoly* poly;
    Camera* camera = GET_ACTIVE_CAM(play);
    Actor* actors[2];
    s32 ret = 0;
    s32 bgId;

    // Check distance
    distance = OLib_Vec3fDist(pos, &camera->eye);
    if ((distance < distanceMin) || (distanceMax < distance)) {
        Snap_SetFlag(PICTOGRAPH_BAD_DISTANCE);
        ret = PICTOGRAPH_BAD_DISTANCE;
    }

    // Check rot is facing camera?
    x = Snap_AbsS(Camera_GetCamDirPitch(camera) + rot->x);
    y = Snap_AbsS(Camera_GetCamDirYaw(camera) - BINANG_SUB(rot->y, 0x7FFF));
    if ((0 < angleRange) && ((angleRange < x) || (angleRange < y))) {
        Snap_SetFlag(PICTOGRAPH_BAD_ANGLE);
        ret |= PICTOGRAPH_BAD_ANGLE;
    }

    // Check in viewfinder
    Actor_GetProjectedPos(play, pos, &projectedPos, &distance);
    x = (s16)(projectedPos.x * distance * 160.0f + 160.0f) - 85;
    y = (s16)(projectedPos.y * distance * -120.0f + 120.0f) - 67;
    if ((x < 0) || (x > 150) || (y < 0) || (y > 105)) {
        Snap_SetFlag(PICTOGRAPH_NOT_IN_VIEW);
        ret |= PICTOGRAPH_NOT_IN_VIEW;
    }

    // Check not obscured by bg collision
    if (BgCheck_ProjectileLineTest(&play->colCtx, pos, &camera->eye, &projectedPos, &poly, true, true, true, true,
                                   &bgId)) {
        Snap_SetFlag(PICTOGRAPH_BEHIND_BG);
        ret |= PICTOGRAPH_BEHIND_BG;
    }

    // Check not obscured by actor collision
    actors[0] = actor;
    actors[1] = &GET_PLAYER(play)->actor;
    if (CollisionCheck_LineOCCheck(play, &play->colChkCtx, pos, &camera->eye, actors, 2)) {
        Snap_SetFlag(PICTOGRAPH_BEHIND_COLLISION);
        ret |= PICTOGRAPH_BEHIND_COLLISION;
    }

    // If all of the above checks pass, set the flag
    if (ret == 0) {
        Snap_SetFlag(flag);
    }

    return ret;
}
