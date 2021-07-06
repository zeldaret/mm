#include <ultra64.h>
#include <global.h>

typedef struct {
    Actor actor;
    s32 (*pictoFunc)(GlobalContext* globalCtx, Actor* actor);
} PictoActor;

s32 func_8013A240(GlobalContext* globalCtx) {
    PictoActor* pictoActor;
    Actor* actor;
    s32 type = 0;
    s32 seen;
    s32 count = 0;

    gSaveContext.roomInf[123][3] = 0;
    gSaveContext.roomInf[123][4] = 0;

    if (globalCtx->sceneNum == SCENE_20SICHITAI) {
        func_8013A41C(1);
    }

    for (; type < 12; type++) {
        for (actor = globalCtx->actorCtx.actorList[type].first; actor != NULL; actor = actor->next) {
            seen = 0;

            switch (globalCtx->sceneNum) {
                case SCENE_20SICHITAI:
                    if ((actor->id == ACTOR_EN_MNK) || (actor->id == ACTOR_EN_BIGOKUTA)) {
                        seen = 1;
                    }
                    break;
                default:
                    seen = 0;
            }

            if (actor->id) {
                ; // Needed to match
            }

            switch (actor->id) {
                case ACTOR_EN_KAKASI:
                    if ((actor->params & 1) == 1) {
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

            if (seen != 0) {
                pictoActor = (PictoActor*)actor;
                if (pictoActor->pictoFunc != NULL) {
                    if ((pictoActor->pictoFunc)(globalCtx, actor) == 0) {
                        count++;
                    }
                }
            }
        }
    }

    return count;
}

void func_8013A41C(s32 flag) {
    if (flag < 0x20) {
        gSaveContext.roomInf[123][3] |= (1 << flag);
    } else {
        flag &= 0x1F;
        gSaveContext.roomInf[123][4] |= (1 << flag);
    }
}

void func_8013A46C(s32 flag) {
    if (flag < 0x20) {
        gSaveContext.roomInf[123][3] &= ~(1 << flag);
    } else {
        flag &= 0x1F;
        gSaveContext.roomInf[123][4] &= ~(1 << flag);
    }
}

u32 func_8013A4C4(s32 flag) {
    SaveContext* saveCtx = &gSaveContext;

    if (flag < 0x20) {
        return saveCtx->roomInf[123][3] & (1 << flag);
    } else {
        flag &= 0x1F;
        return saveCtx->roomInf[123][4] & (1 << flag);
    }
}

s16 func_8013A504(s16 val) {
    return (val >= 0) ? val : -val;
}

s32 func_8013A530(GlobalContext* globalCtx, Actor* actor, s32 flag, Vec3f* pos, Vec3s* rot, f32 distanceMin,
                  f32 distanceMax, s16 angleError) {
    Vec3f screenSpace;
    s16 x;
    s16 y;
    f32 distance;
    CollisionPoly* unk1;
    Camera* camera;
    Actor* actors[2];
    s32 ret = 0;
    u32 unk2;

    camera = ACTIVE_CAM;

    distance = CamMath_Distance(pos, &camera->eye);
    if ((distance < distanceMin) || (distanceMax < distance)) {
        func_8013A41C(0x3f);
        ret = 0x3f;
    }

    x = func_8013A504(func_800DFCB4(camera) + rot->x);
    y = func_8013A504(func_800DFCDC(camera) - (s16)(rot->y - 0x7FFF));
    if ((0 < angleError) && ((angleError < x) || (angleError < y))) {
        func_8013A41C(0x3e);
        ret |= 0x3e;
    }

    func_800B4EDC(globalCtx, pos, &screenSpace, &distance);
    x = (s16)(screenSpace.x * distance * 160.0f + 160.0f) - 85;
    y = (s16)(screenSpace.y * distance * -120.0f + 120.0f) - 67;
    if ((x < 0) || (0x96 < x) || (y < 0) || (0x69 < y)) {
        func_8013A41C(0x3d);
        ret |= 0x3d;
    }

    if (func_800C576C(&globalCtx->colCtx, pos, &camera->eye, &screenSpace, &unk1, 1, 1, 1, 1, &unk2) != 0) {
        func_8013A41C(0x3c);
        ret |= 0x3c;
    }

    actors[0] = actor;
    actors[1] = &PLAYER->actor;
    if (CollisionCheck_LineOCCheck(globalCtx, &globalCtx->colChkCtx, pos, &camera->eye, actors, 2) != 0) {
        func_8013A41C(0x3b);
        ret |= 0x3b;
    }

    if (ret == 0) {
        func_8013A41C(flag);
    }

    return ret;
}
