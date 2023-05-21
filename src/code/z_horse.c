#include "global.h"
#include "overlays/actors/ovl_Bg_Umajump/z_bg_umajump.h"
#include "overlays/actors/ovl_En_Horse/z_en_horse.h"

s32 func_800F3940(PlayState* play) {
    Actor* actor;

    for (actor = NULL;; actor = actor->next) {
        actor = SubS_FindActor(play, actor, ACTORCAT_PROP, ACTOR_BG_UMAJUMP);

        if (actor == NULL) {
            break;
        }

        if (actor->params == 2) {
            return ((BgUmajump*)actor)->objectIndex;
        }
    }

    return -1;
}

// unused
s32 func_800F39B4(PlayState* play, s32 arg1, s32 arg2, Vec3s* arg3, s16* arg4) {
    Path* path = &play->setupPathList[arg1];
    Vec3s* points;
    s32 count;

    count = path->count;
    arg3->x = 0;
    arg3->y = 0;
    arg3->z = 0;
    *arg4 = 0;

    if (count == 0) {
        return 0;
    }
    if (arg2 >= count) {
        return 0;
    }

    points = Lib_SegmentedToVirtual(path->points);
    points += arg2;

    arg3->x = points->x;
    arg3->y = points->y;
    arg3->z = points->z;
    *arg4 = 0;
    return 1;
}

typedef struct {
    /* 0x0 */ s16 sceneNum;
    /* 0x2 */ s16 sceneSetupIndex;
} struct_801BDAA8; // size = 0x4

// extern struct_801BDAA8 sValidScenes[];
struct_801BDAA8 D_801BDA70[] = {
    { SCENE_00KEIKOKU, 0 },      // Termina Field
    { SCENE_24KEMONOMITI, 0 },   // Road to southern swap
    { SCENE_F01, 0 },            // Romani ranch
    { SCENE_KOEPONARACE, 0 },    // Gorman track
    { SCENE_20SICHITAI, 0 },     // Southern swamp poisoned
    { SCENE_20SICHITAI2, 0 },    // Souther swamp clear
    { SCENE_30GYOSON, 0 },       // Great bay coast
    { SCENE_31MISAKI, 0 },       // Zora cape
    { SCENE_ROMANYMAE, 0 },      // Milk road
    { SCENE_IKANAMAE, 0 },       // Road to Ikana
    { SCENE_13HUBUKINOMITI, 0 }, // Path to Mountain Village
};

s32 func_800F3A64(s16 sceneNum) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_801BDA70); i++) {
        if (sceneNum == D_801BDA70[i].sceneNum) {
            return true;
        }
    }

    return false;
}

void func_800F3B2C(PlayState* play) {
    gSaveContext.save.saveInfo.horseData.sceneId = SCENE_F01;
    gSaveContext.save.saveInfo.horseData.pos.x = -1420;
    gSaveContext.save.saveInfo.horseData.pos.y = 257;
    gSaveContext.save.saveInfo.horseData.pos.z = -1285;
    gSaveContext.save.saveInfo.horseData.yaw = 0x2AAA;
}

s32 D_801BDA9C = false;
s32 D_801BDAA0 = false;
s32 D_801BDAA4 = false;

struct_801BDAA8 D_801BDAA8[] = {
    { SCENE_00KEIKOKU, 4 },      // Termina Field - First Cycle
    { SCENE_30GYOSON, 0 },       // Great Bay Coast - Post-Gyorg
    { SCENE_31MISAKI, 0 },       // Zora Cape - Post-Gyorg
    { SCENE_13HUBUKINOMITI, 0 }, // Path to Mountain Village - Post-Goht
};

s32 func_800F3B68(PlayState* play, Player* player) {
    s32 i;

    if (gSaveContext.sceneLayer == 0) {
        return true;
    }

    for (i = 0; i < ARRAY_COUNT(D_801BDAA8); i++) {
        if ((D_801BDAA8[i].sceneNum == play->sceneId) &&
            (gSaveContext.sceneLayer == (D_801BDAA8[i].sceneSetupIndex + 1))) {
            return true;
        }
    }
    return false;
}

void func_800F3C44(PlayState* play, Player* player) {
    if (!func_800F3B68(play, player)) {
        return;
    }

    if (D_801BDA9C && CHECK_QUEST_ITEM(QUEST_SONG_EPONA)) {
        s32 pad;
        Vec3f pos;
        f32 yIntersect;
        CollisionPoly* poly;
        s32 pad2[3];

        pos = player->actor.world.pos;
        pos.y += 5.0f;
        yIntersect = BgCheck_EntityRaycastFloor1(&play->colCtx, &poly, &pos);
        if (yIntersect == BGCHECK_Y_MIN) {
            yIntersect = player->actor.world.pos.y;
        }
        player->rideActor = Actor_Spawn(&play->actorCtx, play, ACTOR_EN_HORSE, player->actor.world.pos.x, yIntersect,
                                        player->actor.world.pos.z, player->actor.shape.rot.x, player->actor.shape.rot.y,
                                        player->actor.shape.rot.z, ENHORSE_PARAMS(ENHORSE_PARAM_4000, ENHORSE_11));
        Actor_MountHorse(play, player, player->rideActor);
        Actor_SetCameraHorseSetting(play, player);
    } else if ((play->sceneId == gSaveContext.save.saveInfo.horseData.sceneId) && CHECK_QUEST_ITEM(QUEST_SONG_EPONA)) {
        if (func_800F3A64(gSaveContext.save.saveInfo.horseData.sceneId)) {
            Actor_Spawn(&play->actorCtx, play, ACTOR_EN_HORSE, gSaveContext.save.saveInfo.horseData.pos.x,
                        gSaveContext.save.saveInfo.horseData.pos.y, gSaveContext.save.saveInfo.horseData.pos.z, 0,
                        gSaveContext.save.saveInfo.horseData.yaw, 0, ENHORSE_PARAMS(ENHORSE_PARAM_4000, ENHORSE_1));
        } else {
            func_800F3B2C(play);
        }
    } else if ((play->sceneId == SCENE_F01) && !CHECK_QUEST_ITEM(QUEST_SONG_EPONA)) {
        Actor_Spawn(&play->actorCtx, play, ACTOR_EN_HORSE, -1420.0f, 257.0f, -1285.0f, 0, 0x2AAA, 0, ENHORSE_PARAMS(ENHORSE_PARAM_4000, ENHORSE_1));
    } else if (CHECK_QUEST_ITEM(QUEST_SONG_EPONA) && (func_800F3A64(play->sceneId))) {
        Actor_Spawn(&play->actorCtx, play, ACTOR_EN_HORSE, player->actor.world.pos.x, player->actor.world.pos.y,
                    player->actor.world.pos.z, 0, player->actor.shape.rot.y, 0, ENHORSE_PARAMS(ENHORSE_PARAM_4000, ENHORSE_2));
    }
}

void func_800F3ED4(PlayState* play, Player* player) {
    if ((play->sceneId == SCENE_KOEPONARACE) && ((gSaveContext.save.saveInfo.weekEventReg[92] & 7) == 1)) {
        player->rideActor =
            Actor_Spawn(&play->actorCtx, play, ACTOR_EN_HORSE, -1262.0f, -106.0f, 470.0f, 0, 0x7FFF, 0, ENHORSE_PARAMS(ENHORSE_PARAM_4000, ENHORSE_13));
        Actor_MountHorse(play, player, player->rideActor);
        Actor_SetCameraHorseSetting(play, player);
    } else if ((play->sceneId == SCENE_KOEPONARACE) &&
               ((((gSaveContext.save.saveInfo.weekEventReg[92] & 7) == 3)) || ((gSaveContext.save.saveInfo.weekEventReg[92] & 7) == 2))) {
        Actor_Spawn(&play->actorCtx, play, ACTOR_EN_HORSE, -1741.0f, -106.0f, -641.0f, 0, -0x4FA4, 0, ENHORSE_PARAMS(ENHORSE_PARAM_4000, ENHORSE_1));
    } else if ((gSaveContext.save.entrance == 0x6400) && (Cutscene_GetSceneLayer(play) != 0) &&
               (player->transformation == PLAYER_FORM_HUMAN)) {
        player->rideActor =
            Actor_Spawn(&play->actorCtx, play, ACTOR_EN_HORSE, -1106.0f, 260.0f, -1185.0f, 0, 0x13, 0, ENHORSE_PARAMS(ENHORSE_PARAM_4000, ENHORSE_7));
        Actor_MountHorse(play, player, player->rideActor);
        Actor_SetCameraHorseSetting(play, player);
    }
}

// Horse_Spawn?
void func_800F40A0(PlayState* play, Player* player) {
    if (((play->sceneId == SCENE_KOEPONARACE) && ((gSaveContext.save.saveInfo.weekEventReg[92] & 7) == 1)) ||
        ((play->sceneId == SCENE_F01) &&
         (((gSaveContext.sceneLayer == 1)) || (gSaveContext.sceneLayer == 5)) &&
         (player->transformation == PLAYER_FORM_HUMAN)) ||
        ((play->sceneId == SCENE_KOEPONARACE) &&
         ((((gSaveContext.save.saveInfo.weekEventReg[92] & 7) == 3)) || ((gSaveContext.save.saveInfo.weekEventReg[92] & 7) == 2)))) {
        func_800F3ED4(play, player);
    } else {
        func_800F3C44(play, player);
    }
    D_801BDAA0 = false;
}

void Horse_RotateToPoint(Actor* actor, Vec3f* pos, s16 turnAmount) {
    s16 yaw = Math_Vec3f_Yaw(&actor->world.pos, pos) - actor->world.rot.y;

    if (turnAmount < yaw) {
        actor->world.rot.y += turnAmount;
    } else if (yaw < -turnAmount) {
        actor->world.rot.y -= turnAmount;
    } else {
        actor->world.rot.y += yaw;
    }

    actor->shape.rot.y = actor->world.rot.y;
}

s32 func_800F41E4(PlayState* play, ActorContext* actorCtx) {
    Actor* bgActor = actorCtx->actorLists[ACTORCAT_BG].first;

    if (bgActor != NULL) {
        while (true) {
            if ((bgActor->update != NULL) && (bgActor->init == NULL)) {
                if (Object_IsLoaded(&play->objectCtx, bgActor->objBankIndex)) {
                    if ((bgActor->id == ACTOR_EN_HORSE) && (((EnHorse*)bgActor)->action != ENHORSE_ACTION_INACTIVE)) {
                        return true;
                    }
                }
            }
            bgActor = bgActor->next;
            if (bgActor == NULL) {
                break;
            }
        }
    }

    return false;
}
