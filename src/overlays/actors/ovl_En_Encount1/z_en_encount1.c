/*
 * File: z_en_encount1.c
 * Overlay: ovl_En_Encount1
 * Description: Spawner for Dragonflies, Skullfish, and Wallmasters
 */

#include "z_en_encount1.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_100000 | ACTOR_FLAG_8000000)

#define THIS ((EnEncount1*)thisx)

void EnEncount1_Init(Actor* thisx, PlayState* play);
void EnEncount1_Update(Actor* thisx, PlayState* play);

void func_808E0954(EnEncount1* this, PlayState* play);

ActorInit En_Encount1_InitVars = {
    ACTOR_EN_ENCOUNT1, ACTORCAT_PROP, FLAGS, GAMEPLAY_KEEP, sizeof(EnEncount1), EnEncount1_Init, NULL,
    EnEncount1_Update, NULL,
};

static s16 sActorList[] = {
    ACTOR_EN_GRASSHOPPER,
    ACTOR_EN_WALLMAS,
    ACTOR_EN_PR2,
    ACTOR_EN_PR2,
};

static s16 sActorParams[] = { 1, 0, 1, 3 };

void EnEncount1_Init(Actor* thisx, PlayState* play) {
    EnEncount1* this = THIS;

    if (this->actor.params <= 0) {
        Actor_Kill(&this->actor);
        return;
    }

    this->actorType = ENENCOUNT1_GET_TYPE(&this->actor);
    this->unk_14C = ENENCOUNT1_GET_7C0(&this->actor);
    this->unk_154 = ENENCOUNT1_GET_PATH(&this->actor);
    this->unk_158 = this->actor.world.rot.x;
    this->unk_15C = this->actor.world.rot.y;
    this->unk_160 = (this->actor.world.rot.z * 40.0f) + 120.0f;

    if (this->unk_154 >= 0x3F) {
        this->unk_154 = -1;
    }
    if (this->actor.world.rot.z < 0) {
        this->unk_160 = -1.0f;
    }
    if (this->actorType == EN_ENCOUNT1_SKULLFISH_2) {
        this->unk_15A = ENENCOUNT1_GET_PATH(&this->actor);
        this->path = SubS_GetPathByIndex(play, this->unk_15A, 0x3F);
        this->unk_154 = -1;
        this->unk_160 = -1.0f;
    }
    this->actor.flags &= ~ACTOR_FLAG_1;
    this->actionFunc = func_808E0954;
}

void func_808E0954(EnEncount1* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    Vec3f spawnPos;
    f32 sp64;
    f32 temp_fv0_2;
    s16 sp5E;
    s16 actorList;
    s32 actorParams;
    CollisionPoly* sp54;
    s32 sp50;

    if (((this->unk_14E >= this->unk_14C) || ((this->unk_160 > 0.0f) && (this->unk_160 < this->actor.xzDistToPlayer)) ||
         ((this->unk_154 > 0) && (this->unk_154 <= this->unk_152)))) {
        return;
    } else if (this->unk_156 != 0) {
        this->unk_156++;
        if (this->unk_156 < this->unk_158) {
            return;
        }
    }

    this->unk_156 = 0;
    switch (this->actorType) {
        case EN_ENCOUNT1_GRASSHOPPER:
            sp64 = randPlusMinusPoint5Scaled(40.0f) + 200.0f;
            sp5E = player->actor.shape.rot.y;
            if (this->unk_14E & 1) {
                sp5E = -sp5E;
                sp64 = randPlusMinusPoint5Scaled(20.0f) + 100.0f;
            }
            spawnPos.x = player->actor.world.pos.x + (Math_SinS(sp5E) * sp64) + randPlusMinusPoint5Scaled(40.0f);
            spawnPos.y = player->actor.floorHeight + 120.0f;
            spawnPos.z = player->actor.world.pos.z + (Math_CosS(sp5E) * sp64) + randPlusMinusPoint5Scaled(40.0f);
            temp_fv0_2 = BgCheck_EntityRaycastFloor5(&play->colCtx, &sp54, &sp50, &this->actor, &spawnPos);
            if ((temp_fv0_2 <= BGCHECK_Y_MIN) ||
                ((player->actor.depthInWater != BGCHECK_Y_MIN) &&
                 (temp_fv0_2 < (player->actor.world.pos.y - player->actor.depthInWater)))) {
                return;
            }
            spawnPos.y = temp_fv0_2;
            break;

        case EN_ENCOUNT1_WALLMASTER:
            Math_Vec3f_Copy(&spawnPos, &player->actor.world.pos);
            break;

        case EN_ENCOUNT1_SKULLFISH:
            sp64 = randPlusMinusPoint5Scaled(250.0f) + 500.0f;
            sp5E = player->actor.shape.rot.y;
            spawnPos.x = player->actor.world.pos.x + Math_SinS(sp5E) * sp64 + randPlusMinusPoint5Scaled(40.0f);
            spawnPos.y = player->actor.world.pos.y - Rand_ZeroFloat(20.0f);
            spawnPos.z = player->actor.world.pos.z + (Math_CosS(sp5E) * sp64) + randPlusMinusPoint5Scaled(40.0f);
            temp_fv0_2 = BgCheck_EntityRaycastFloor5(&play->colCtx, &sp54, &sp50, &this->actor, &spawnPos);
            if ((!(player->stateFlags1 & 0x8000000) || (temp_fv0_2 <= (BGCHECK_Y_MIN)) ||
                 (player->actor.depthInWater < temp_fv0_2))) {
                return;
            }
            break;

        case EN_ENCOUNT1_SKULLFISH_2:
            if ((this->path != NULL) && (!SubS_CopyPointFromPath(this->path, 0, &spawnPos))) {
                Actor_Kill(&this->actor);
            }
            break;
    }

    actorList = sActorList[this->actorType];
    actorParams = sActorParams[this->actorType];
    if (Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, actorList, spawnPos.x, spawnPos.y, spawnPos.z, 0, 0, 0,
                           actorParams) != NULL) {
        this->unk_14E++;
        if (this->unk_154 > 0) {
            this->unk_152++;
        }

        if ((this->unk_14E >= this->unk_14C) && (this->unk_158 != 0)) {
            this->unk_156 = 1;
        }
    }
}

void EnEncount1_Update(Actor* thisx, PlayState* play) {
    EnEncount1* this = THIS;

    this->actionFunc(this, play);
}
