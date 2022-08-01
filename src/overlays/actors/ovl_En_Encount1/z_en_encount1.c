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

#if 0
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

static s16 D_808E0DF0[4] = { 0x109, 0xA, 0x180, 0x180 };
static s16 D_808E0DF8[4] = { 1, 0, 1, 3 };

#endif

extern s16 D_808E0DF0[];
extern s16 D_808E0DF8[];

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Encount1/EnEncount1_Init.s")

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
    Player *sp74 = (Player *) play->actorCtx.actorLists[ACTORCAT_PLAYER].first;
    Vec3f spawnPos;
    f32 sp64;
    f32 temp_fv0_2;
    s16 sp5E;
    s32 temp;
    CollisionPoly* sp54;
    s32 sp50;

    if (((this->unk_14E >= this->unk14C) ||
        ((0.0f < this->unk160) && (this->unk160 < this->actor.xzDistToPlayer)) ||
        ((0 < this->unk154 ) && (this->unk154 <= this->unk152)))) {
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
            sp5E = sp74->actor.shape.rot.y;
            if (this->unk_14E & 1) {
                sp5E = -sp5E;
                sp64 = randPlusMinusPoint5Scaled(20.0f) + 100.0f;
            }
            spawnPos.x = sp74->actor.world.pos.x + (Math_SinS(sp5E) * sp64) + randPlusMinusPoint5Scaled(40.0f);
            spawnPos.y = sp74->actor.floorHeight + 120.0f;
            spawnPos.z = sp74->actor.world.pos.z + (Math_CosS(sp5E) * sp64)+ randPlusMinusPoint5Scaled(40.0f);
            temp_fv0_2 = BgCheck_EntityRaycastFloor5(&play->colCtx, &sp54, &sp50, &this->actor, &spawnPos);
            if ((temp_fv0_2 <= -32000.0f) ||
                ((sp74->actor.depthInWater != -32000.0f) &&
                 (temp_fv0_2 < (sp74->actor.world.pos.y - sp74->actor.depthInWater)))) {
                return;
            }
            spawnPos.y = temp_fv0_2;
            break;
        
        case 1:
            Math_Vec3f_Copy(&spawnPos, &sp74->actor.world.pos);
            break;
        
        case 2:
            sp64 = randPlusMinusPoint5Scaled(250.0f) + 500.0f;
            sp5E = sp74->actor.shape.rot.y;
            spawnPos.x = sp74->actor.world.pos.x + Math_SinS(sp5E) * sp64 + randPlusMinusPoint5Scaled(40.0f);
            spawnPos.y = sp74->actor.world.pos.y - Rand_ZeroFloat(20.0f);
            spawnPos.z = sp74->actor.world.pos.z + (Math_CosS(sp5E) * sp64) + randPlusMinusPoint5Scaled(40.0f);
            temp_fv0_2 = BgCheck_EntityRaycastFloor5(&play->colCtx, &sp54, &sp50, &this->actor, &spawnPos);
            if ((!(sp74->stateFlags1 & 0x08000000) || (temp_fv0_2 <= (-32000.0f))||
                (sp74->actor.depthInWater < temp_fv0_2))) {
                return;
            }
            break;
        
        case 3:
            if ((this->unk148 != NULL) && (SubS_CopyPointFromPath(this->unk148, 0, &spawnPos) == 0)) {
                Actor_MarkForDeath(&this->actor);
            }
            break;
    }
    
    temp = D_808E0DF8[this->unk150];
    if (Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, D_808E0DF0[this->unk150], spawnPos.x, spawnPos.y,
                           spawnPos.z, 0, 0, 0, temp) != NULL) {
        this->unk_14E++;
        if (this->unk154 > 0) {
            this->unk152++;
        }
    
        if ((this->unk_14E >= this->unk14C) && (this->unk158 != 0)) {
            this->unk156 = 1;
        }
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Encount1/EnEncount1_Update.s")

void EnEncount1_Update(Actor* thisx, PlayState* play) {
    EnEncount1* this = THIS;

    this->actionFunc(this, play);
}
