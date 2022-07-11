#include "global.h"
#include "overlays/actors/ovl_Bg_Umajump/z_bg_umajump.h"
#include "overlays/actors/ovl_En_Horse/z_en_horse.h"

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

#pragma GLOBAL_ASM("asm/non_matchings/code/z_horse/func_800F39B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_horse/func_800F3A64.s")

void func_800F3B2C(PlayState* play) {
    gSaveContext.save.horseData.scene = 0x35;
    gSaveContext.save.horseData.pos.x = -0x58C;
    gSaveContext.save.horseData.pos.y = 0x101;
    gSaveContext.save.horseData.pos.z = -0x505;
    gSaveContext.save.horseData.yaw = 0x2AAA;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_horse/func_800F3B68.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_horse/func_800F3C44.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_horse/func_800F3ED4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_horse/func_800F40A0.s")

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
