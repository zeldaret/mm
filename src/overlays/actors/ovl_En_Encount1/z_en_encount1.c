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

void func_808E0954(EnEncount1* this, PlayState* play) {
    Player* sp74 = GET_PLAYER(play);
    Vec3f sp68;
    f32 sp64;
    s16 sp5E;
    CollisionPoly* sp54;
    s32 sp50;
    f32 sp48;
    Path* temp_a0_3;
    f32 temp_fv0_2;
    f32 temp_fv0_3;

    if ((((this->unk_14E < this->unk14C) &&
          ((!(this->unk160 > 0.0f)) || (!(this->unk160 < this->actor.xzDistToPlayer)))) &&
         ((this->unk154 <= 0) || (this->unk152 < this->unk154))) &&
        ((this->unk156 == 0) || ((this->unk156 = this->unk156 + 1, (this->unk156 < this->unk158) == 0)))) {
        this->unk156 = 0;
        switch (this->unk150) {
            case 0:
                sp64 = randPlusMinusPoint5Scaled(40.0f) + 200.0f;
                sp5E = sp74->actor.shape.rot.y;
                if (this->unk_14E & 1) {
                    sp5E = sp74->actor.shape.rot.y * (-1);
                    sp64 = randPlusMinusPoint5Scaled(20.0f) + 100.0f;
                }
                sp48 = Math_SinS(sp5E);
                sp68.x = randPlusMinusPoint5Scaled(40.0f) + (sp74->actor.world.pos.x + (sp48 * sp64));
                sp68.y = sp74->actor.floorHeight + 120.0f;
                sp48 = Math_CosS(sp5E);
                sp68.z = randPlusMinusPoint5Scaled(40.0f) + (sp74->actor.world.pos.z + (sp48 * sp64));
                temp_fv0_2 = BgCheck_EntityRaycastFloor5(&play->colCtx, &sp54, &sp50, &this->actor, &sp68);
                if ((!(temp_fv0_2 <= (-32000.0f))) &&
                    (((sp74->actor.depthInWater == (-32000.0f))) ||
                     (!(temp_fv0_2 < (sp74->actor.world.pos.y - sp74->actor.depthInWater))))) {
                    sp68.y = temp_fv0_2;
                }
                break;

            case 1:
                Math_Vec3f_Copy(&sp68, &sp74->actor.world.pos);
                break;

            case 2:
                sp64 = randPlusMinusPoint5Scaled(250.0f) + 500.0f;
                sp5E = sp74->actor.shape.rot.y;
                sp48 = Math_SinS(sp5E);
                sp68.x = randPlusMinusPoint5Scaled(40.0f) + (sp74->actor.world.pos.x + (sp48 * sp64));
                sp68.y = sp74->actor.world.pos.y - Rand_ZeroFloat(20.0f);
                sp48 = Math_CosS(sp5E);
                sp68.z = randPlusMinusPoint5Scaled(40.0f) + (sp74->actor.world.pos.z + (sp48 * sp64));
                temp_fv0_3 = BgCheck_EntityRaycastFloor5(&play->colCtx, &sp54, &sp50, &this->actor, &sp68);
                if ((((sp74->stateFlags1 & 0x08000000)) && (!(temp_fv0_3 <= (-32000.0f)))) &&
                    (!(sp74->actor.depthInWater < temp_fv0_3))) {
                    break;

                    case 3:
                        temp_a0_3 = this->unk148;
                        if ((temp_a0_3 != NULL) && (SubS_CopyPointFromPath(temp_a0_3, 0, &sp68) == 0)) {
                            Actor_MarkForDeath(&this->actor);
                        }
                }
            default:
                if (Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, D_808E0DF0[this->unk150], sp68.x, sp68.y,
                                       sp68.z, 0, 0, 0, D_808E0DF8[this->unk150]) != NULL) {
                    this->unk_14E += 1;
                    if (this->unk154 > 0) {
                        this->unk152 += 1;
                    }
                }
                if ((this->unk_14E >= this->unk14C) && (this->unk158 != 0)) {
                    this->unk156 = 1;
                }
        }
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Encount1/EnEncount1_Update.s")

void EnEncount1_Update(Actor* thisx, PlayState* play) {
    EnEncount1* this = THIS;

    this->actionFunc(this, play);
    return;
}
