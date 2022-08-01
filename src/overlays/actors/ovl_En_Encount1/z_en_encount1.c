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

const ActorInit En_Encount1_InitVars = {
    ACTOR_EN_ENCOUNT1,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnEncount1),
    (ActorFunc)EnEncount1_Init,
    (ActorFunc)NULL,
    (ActorFunc)EnEncount1_Update,
    (ActorFunc)NULL,
};

static s16 sActorList[] = { ACTOR_EN_GRASSHOPPER, ACTOR_EN_WALLMAS, ACTOR_EN_PR2, ACTOR_EN_PR2 };

static s16 sActorParams[] = { 1, 0, 1, 3 };

void EnEncount1_Init(Actor* thisx, PlayState* play) {
    EnEncount1* this = THIS;

    if (this->actor.params <= 0) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    this->unk150 = (this->actor.params >> 0xB) & 0x1F;
    this->unk14C = (this->actor.params >> 6) & 0x1F;
    this->unk154 = ENENCOUNT1_GET_3F(&this->actor);
    this->unk158 = this->actor.world.rot.x;
    this->unk15C = this->actor.world.rot.y;
    this->unk160 = (this->actor.world.rot.z * 40.0f) + 120.0f;

    if (this->unk154 >= 0x3F) {
        this->unk154 = -1;
    }
    if (this->actor.world.rot.z < 0) {
        this->unk160 = -1.0f;
    }
    if (this->unk150 == 3) {
        this->unk_15A = ENENCOUNT1_GET_3F(&this->actor);
        this->unk148 = SubS_GetPathByIndex(play, this->unk_15A, 0x3F);
        this->unk154 = -1;
        this->unk160 = -1.0f;
    }
    this->actor.flags &= -2;
    this->actionFunc = func_808E0954;
}

void func_808E0954(EnEncount1 *this, PlayState *play) {
    Player *player = GET_PLAYER(play);
    Vec3f spawnPos;
    f32 sp64;
    f32 temp_fv0_2;
    s16 sp5E;
    s32 actorParams;
    CollisionPoly* sp54;
    s32 sp50;

    if (((this->unk_14E >= this->unk14C) ||
        ((0.0f < this->unk160) && (this->unk160 < this->actor.xzDistToPlayer)) ||
        ((0 < this->unk154) && (this->unk154 <= this->unk152)))) {
        return;
    } else if(this->unk156 != 0) {
        this->unk156++;
        if (this->unk156 < this->unk158) {
            return;
        }
    }

    this->unk156 = 0;
    switch (this->unk150) {
        case 0:
            sp64 = randPlusMinusPoint5Scaled(40.0f) + 200.0f;
            sp5E = player->actor.shape.rot.y;
            if (this->unk_14E & 1) {
                sp5E = -sp5E;
                sp64 = randPlusMinusPoint5Scaled(20.0f) + 100.0f;
            }
            spawnPos.x = player->actor.world.pos.x + (Math_SinS(sp5E) * sp64) + randPlusMinusPoint5Scaled(40.0f);
            spawnPos.y = player->actor.floorHeight + 120.0f;
            spawnPos.z = player->actor.world.pos.z + (Math_CosS(sp5E) * sp64)+ randPlusMinusPoint5Scaled(40.0f);
            temp_fv0_2 = BgCheck_EntityRaycastFloor5(&play->colCtx, &sp54, &sp50, &this->actor, &spawnPos);
            if ((temp_fv0_2 <= -32000.0f) ||
                ((player->actor.depthInWater != -32000.0f) &&
                 (temp_fv0_2 < (player->actor.world.pos.y - player->actor.depthInWater)))) {
                return;
            }
            spawnPos.y = temp_fv0_2;
            break;
        
        case 1:
            Math_Vec3f_Copy(&spawnPos, &player->actor.world.pos);
            break;
        
        case 2:
            sp64 = randPlusMinusPoint5Scaled(250.0f) + 500.0f;
            sp5E = player->actor.shape.rot.y;
            spawnPos.x = player->actor.world.pos.x + Math_SinS(sp5E) * sp64 + randPlusMinusPoint5Scaled(40.0f);
            spawnPos.y = player->actor.world.pos.y - Rand_ZeroFloat(20.0f);
            spawnPos.z = player->actor.world.pos.z + (Math_CosS(sp5E) * sp64) + randPlusMinusPoint5Scaled(40.0f);
            temp_fv0_2 = BgCheck_EntityRaycastFloor5(&play->colCtx, &sp54, &sp50, &this->actor, &spawnPos);
            if ((!(player->stateFlags1 & 0x08000000) || (temp_fv0_2 <= (-32000.0f))||
                (player->actor.depthInWater < temp_fv0_2))) {
                return;
            }
            break;
        
        case 3:
            if ((this->unk148 != NULL) && (SubS_CopyPointFromPath(this->unk148, 0, &spawnPos) == 0)) {
                Actor_MarkForDeath(&this->actor);
            }
            break;
    }
    
    actorParams = sActorParams[this->unk150];
    if (Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, sActorList[this->unk150], spawnPos.x, spawnPos.y,
                           spawnPos.z, 0, 0, 0, actorParams) != NULL) {
        this->unk_14E++;
        if (this->unk154 > 0) {
            this->unk152++;
        }
    
        if ((this->unk_14E >= this->unk14C) && (this->unk158 != 0)) {
            this->unk156 = 1;
        }
    }
}

void EnEncount1_Update(Actor* thisx, PlayState* play) {
    EnEncount1* this = THIS;

    this->actionFunc(this, play);
}
