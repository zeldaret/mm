#include "global.h"
#include "overlays/actors/ovl_Bg_Umajump/z_bg_umajump.h"
#include "overlays/actors/ovl_En_Horse/z_en_horse.h"

extern s16 D_801BDA74;
extern s16 D_801BDA78;
//extern s16 D_801BDAA8;
extern s16 D_801BDAAA;
extern s16 D_801BDAAC;
extern s16 D_801BDAAE;
extern s16 D_801BDAB0;
extern s16 D_801BDAB2;
extern s16 D_801BDAB4;
extern s16 D_801BDAB6;
extern s32 D_801BDAA0;


s32 func_800F3940(PlayState* play) {
    Actor* actor;

    for (actor = NULL; ; actor = actor->next) {
        actor = SubS_FindActor(play, actor, ACTORCAT_PROP, ACTOR_BG_UMAJUMP);

        if (actor == NULL) {
            break;
        }

        if (actor->params == 2) {
            return ((BgUmajump*)actor)->unk_160;
        }
    }

    return -1;
}

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


// ??
//extern s32 sValidScenes[11];
s32 D_801BDA70[] = {
    0x002D0000,
    0x00400000,
    0x00350000,
    0x006A0000,
    0x00450000,
    0x00000000,
    0x00370000,
    0x00380000,
    0x00220000,
    0x00530000,
    0x001C0000,
};
s32 func_800F3A64(s16 scene) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_801BDA70); i++) {
        if (scene == ((s16*)D_801BDA70)[i*2]) {
            return true;
        }
    }

    return false;
}

s32 D_801BDA9C = false;

s32 D_801BDAA0 = 0x00000000;
s32 D_801BDAA4 = 0;

typedef struct {
    /* 0x0 */ s16 sceneNum;
    /* 0x2 */ s16 sceneSetupIndex;
} struct_801BDAA8; // size = 0x4

struct_801BDAA8 D_801BDAA8[] = {
    {0x002D, 0x0004},
    {0x0037, 0x0000},
    {0x0038, 0x0000},
    {0x001C, 0x0000},
};

void func_800F3B2C(PlayState* play) {
    gSaveContext.save.horseData.scene = 0x35;
    gSaveContext.save.horseData.pos.x = -0x58C;
    gSaveContext.save.horseData.pos.y = 0x101;
    gSaveContext.save.horseData.pos.z = -0x505;
    gSaveContext.save.horseData.yaw = 0x2AAA;
}

s32 func_800F3B68(PlayState* play, Player* player) {
    s32 i;

    if (gSaveContext.sceneSetupIndex == 0) {
        return true;
    }

    for (i = 0; i < ARRAY_COUNT(D_801BDAA8); i++) {
        if ((D_801BDAA8[i].sceneNum == play->sceneNum) && (gSaveContext.sceneSetupIndex == (D_801BDAA8[i].sceneSetupIndex + 1))) {
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
        Vec3f sp60;
        f32 var_fv1;
        CollisionPoly* sp58;
        s32 pad2[3];

        sp60 = player->actor.world.pos;
        sp60.y += 5.0f;
        var_fv1 = BgCheck_EntityRaycastFloor1(&play->colCtx, &sp58, &sp60);
        if (var_fv1 == BGCHECK_Y_MIN) {
            var_fv1 = player->actor.world.pos.y;
        }
        player->rideActor = Actor_Spawn(&play->actorCtx, play, ACTOR_EN_HORSE, player->actor.world.pos.x, var_fv1, player->actor.world.pos.z,  player->actor.shape.rot.x, player->actor.shape.rot.y, player->actor.shape.rot.z, 0x400B);
        Actor_MountHorse(play, player, player->rideActor);
        Actor_SetCameraHorseSetting(play, player);
    } else if ((play->sceneNum == gSaveContext.save.horseData.scene) && CHECK_QUEST_ITEM(QUEST_SONG_EPONA)) {
        if (func_800F3A64(gSaveContext.save.horseData.scene)) {
            Actor_Spawn(&play->actorCtx, play, ACTOR_EN_HORSE, gSaveContext.save.horseData.pos.x, gSaveContext.save.horseData.pos.y, gSaveContext.save.horseData.pos.z, 0, gSaveContext.save.horseData.yaw, 0, 0x4001);
        } else {
            func_800F3B2C(play);
        }
    } else if ((play->sceneNum == 0x35) && !CHECK_QUEST_ITEM(QUEST_SONG_EPONA)) {
        Actor_Spawn(&play->actorCtx, play, ACTOR_EN_HORSE, -1420.0f, 257.0f, -1285.0f, 0, 0x2AAA, 0, 0x4001);
    } else if (CHECK_QUEST_ITEM(QUEST_SONG_EPONA) && (func_800F3A64(play->sceneNum))) {
        Actor_Spawn(&play->actorCtx, play, ACTOR_EN_HORSE, player->actor.world.pos.x, player->actor.world.pos.y, player->actor.world.pos.z, 0, player->actor.shape.rot.y, 0, 0x4002);
    }
}

void func_800F3ED4(PlayState* play, Player* player) {
    if ((play->sceneNum == 0x6A) && ((gSaveContext.save.weekEventReg[92] & 7) == 1)) {
        player->rideActor = Actor_Spawn(&play->actorCtx, play, ACTOR_EN_HORSE, -1262.0f, -106.0f, 470.0f, 0, 0x7FFF, 0, 0x400D);
        Actor_MountHorse(play, player, player->rideActor);
        Actor_SetCameraHorseSetting(play, player);
    } else if ((play->sceneNum == 0x6A) && ((((gSaveContext.save.weekEventReg[92] & 7) == 3)) || ((gSaveContext.save.weekEventReg[92] & 7) == 2))) {
        Actor_Spawn(&play->actorCtx, play, ACTOR_EN_HORSE, -1741.0f, -106.0f, -641.0f, 0, -0x4FA4, 0, 0x4001);
    } else if ((gSaveContext.save.entranceIndex == 0x6400) && (Cutscene_GetSceneSetupIndex(play) != 0) && (player->transformation == PLAYER_FORM_HUMAN)) {
        player->rideActor = Actor_Spawn(&play->actorCtx, play, ACTOR_EN_HORSE, -1106.0f, 260.0f, -1185.0f, 0, 0x13, 0, 0x4007);
        Actor_MountHorse(play, player, player->rideActor);
        Actor_SetCameraHorseSetting(play, player);
    }
}

void func_800F40A0(PlayState* play, Player* player) {
    if (((play->sceneNum == 0x6A) && ((gSaveContext.save.weekEventReg[92] & 7) == 1)) || ((play->sceneNum == 0x35) && (((gSaveContext.sceneSetupIndex == 1)) || (gSaveContext.sceneSetupIndex == 5)) && (player->transformation == 4)) || ((play->sceneNum == 0x6A) && ((((gSaveContext.save.weekEventReg[92] & 7) == 3)) || ((gSaveContext.save.weekEventReg[92] & 7) == 2)))) {
        func_800F3ED4(play, player);
    } else {
        func_800F3C44(play, player);
    }
    D_801BDAA0 = 0;
}

void func_800F415C(Actor* actor, Vec3f* arg1, s16 arg2) {
    s16 yaw = Math_Vec3f_Yaw(&actor->world.pos, arg1) - actor->world.rot.y;

    if (arg2 < yaw) {
        actor->world.rot.y += arg2;
    } else if (yaw < -arg2) {
        actor->world.rot.y -= arg2;
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
                    if ((bgActor->id == ACTOR_EN_HORSE) && (((EnHorse*)bgActor)->action != 1)) {
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
