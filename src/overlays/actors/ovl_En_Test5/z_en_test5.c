/*
 * File: z_en_test5.c
 * Overlay: ovl_En_Test5
 * Description: Spring Water Modifier
 */

#include "z_en_test5.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((EnTest5*)thisx)

void EnTest5_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTest5_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTest5_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTest5_HandleBottleAction(EnTest5* this, GlobalContext* globalCtx);
void EnTest5_SetupAction(EnTest5* this, EnTest5ActionFunc actionFunc);

const ActorInit En_Test5_InitVars = {
    ACTOR_EN_TEST5,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnTest5),
    (ActorFunc)EnTest5_Init,
    (ActorFunc)EnTest5_Destroy,
    (ActorFunc)EnTest5_Update,
    (ActorFunc)NULL,
};

void EnTest5_SetupAction(EnTest5* this, EnTest5ActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

void EnTest5_Init(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    EnTest5* this = THIS;
    WaterBox* water;
    f32 ySurface;

    // If not spawned above a water source, immediately despawn
    if (!WaterBox_GetSurface1(globalCtx, &globalCtx->colCtx, this->actor.world.pos.x, this->actor.world.pos.z,
                              &ySurface, &water)) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    Math_Vec3s_ToVec3f(&this->minPos, &water->minPos);
    this->xLength = (f32)water->xLength;
    this->zLength = (f32)water->zLength;

    EnTest5_SetupAction(this, EnTest5_HandleBottleAction);
}

void EnTest5_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void EnTest5_HandleBottleAction(EnTest5* this, GlobalContext* globalCtx) {
    Player* player;
    Vec3f playerPosRelativeToWater;

    if (Actor_HasParent(&this->actor, globalCtx)) {
        this->actor.parent = NULL;
        return;
    }

    player = GET_PLAYER(globalCtx);

    if (player->interactRangeActor == NULL || player->getItemId != GI_MAX) {
        Math_Vec3f_DistXYZAndStoreDiff(&this->minPos, &player->actor.world.pos, &playerPosRelativeToWater);

        // Make sure that the player is within the bounds of the water and deep enough to grab some
        if (playerPosRelativeToWater.x >= 0.0f && playerPosRelativeToWater.x <= this->xLength &&
            playerPosRelativeToWater.z >= 0.0f && playerPosRelativeToWater.z <= this->zLength &&
            fabsf(playerPosRelativeToWater.y) < 100.0f && player->actor.depthInWater > 12.0f) {
            Actor_PickUp(&this->actor, globalCtx, GI_MAX, this->actor.xzDistToPlayer,
                         fabsf(this->actor.playerHeightRel));
        }
    }
}

void EnTest5_Update(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    EnTest5* this = THIS;
    Vec3f steamPos;
    CollisionPoly* poly;
    s32 pad;

    this->actionFunc(this, globalCtx);

    // If it's the hot spring variant, generate steam clouds
    if (ENTEST5_IS_HOT_SPRING(&this->actor) && (globalCtx->state.frames % 4) == 0) {
        steamPos.x = (Rand_ZeroOne() * this->xLength) + this->minPos.x;
        steamPos.y = this->minPos.y + 100.0f;
        steamPos.z = (Rand_ZeroOne() * this->zLength) + this->minPos.z;

        if ((BgCheck_EntityRaycastFloor2(globalCtx, &globalCtx->colCtx, &poly, &steamPos) + 10.0f) < this->minPos.y) {
            Vec3f steamVel;

            steamPos.y = this->minPos.y + 10.0f;
            steamVel.y = 0.5f;
            steamVel.x = 0.0f;
            steamVel.z = 0.0f;

            EffectSsIceSmoke_Spawn(globalCtx, &steamPos, &steamVel, &gZeroVec3f,
                                   (s16)((-200) - (s32)(Rand_ZeroOne() * 50.0f)));
        }
    }
}
