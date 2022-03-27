/*
 * File: z_en_attack_niw.c
 * Overlay: ovl_En_Attack_Niw
 * Description: Attacking cucco
 */

#include "z_en_attack_niw.h"
#include "overlays/actors/ovl_En_Niw/z_en_niw.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((EnAttackNiw*)thisx)

void EnAttackNiw_Init(Actor* thisx, GlobalContext* globalCtx);
void EnAttackNiw_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnAttackNiw_Update(Actor* thisx, GlobalContext* globalCtx);
void EnAttackNiw_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80958634(EnAttackNiw* this, GlobalContext* globalCtx);
void func_80958974(EnAttackNiw* this, GlobalContext* globalCtx);
void func_80958BE4(EnAttackNiw* this, GlobalContext* globalCtx);

const ActorInit En_Attack_Niw_InitVars = {
    ACTOR_EN_ATTACK_NIW,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_NIW,
    sizeof(EnAttackNiw),
    (ActorFunc)EnAttackNiw_Init,
    (ActorFunc)EnAttackNiw_Destroy,
    (ActorFunc)EnAttackNiw_Update,
    (ActorFunc)EnAttackNiw_Draw,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_U8(targetMode, 1, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -2000, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 0, ICHAIN_STOP),
};

void EnAttackNiw_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnAttackNiw* this = THIS;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 25.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_niw_Skel_002530, &object_niw_Anim_0000E8, this->jointTable,
                       this->morphTable, OBJECT_NIW_LIMB_MAX);

    if (this->actor.params < 0) {
        this->actor.params = 0;
    }

    Actor_SetScale(&this->actor, 0.01f);
    this->actor.gravity = 0.0f;

    this->unk_290.x = randPlusMinusPoint5Scaled(100.0f);
    this->unk_290.y = randPlusMinusPoint5Scaled(10.0f);
    this->unk_290.z = randPlusMinusPoint5Scaled(100.0f);

    Actor_SetScale(&this->actor, 0.01f);
    this->actor.flags &= ~ACTOR_FLAG_1;
    this->actor.shape.rot.y = this->actor.world.rot.y = (Rand_ZeroOne() - 0.5f) * 60000.0f;
    this->actionFunc = func_80958634;
}

void EnAttackNiw_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnAttackNiw* this = THIS;
    EnNiw* parent = (EnNiw*)this->actor.parent;

    if ((thisx->parent != NULL) && (thisx->parent->update != NULL)) {
        if (parent->unk290 > 0) {
            parent->unk290--;
        }
    }
}

void func_80958228(EnAttackNiw* this, GlobalContext* globalCtx, s16 arg2) {
    if (this->unk_24C == 0) {
        if (arg2 == 0) {
            this->unk_25C = 0.0f;
        } else {
            this->unk_25C = -10000.0f;
        }
        this->unk_286++;
        this->unk_24C = 3;
        if ((this->unk_286 % 2) == 0) {
            this->unk_25C = 0.0f;
            if (arg2 == 0) {
                this->unk_24C = Rand_ZeroFloat(30.0f);
            }
        }
    }

    if (this->unk_250 == 0) {
        this->unk_28A++;
        this->unk_28A &= 1;

        switch (arg2) {
            case 0:
                this->unk_264 = 0.0f;
                this->unk_260 = 0.0f;
                break;

            case 1:
                this->unk_250 = 3;
                this->unk_264 = 7000.0f;
                this->unk_260 = 7000.0f;
                if (this->unk_28A == 0) {
                    this->unk_264 = 0.0f;
                    this->unk_260 = 0.0f;
                }
                break;

            case 2:
                this->unk_250 = 2;
                this->unk_264 = -10000.0f;
                this->unk_260 = -10000.0f;
                this->unk_278 = 25000.0f;
                this->unk_270 = 25000.0f;
                this->unk_27C = 6000.0f;
                this->unk_274 = 6000.0f;
                if (this->unk_28A == 0) {
                    this->unk_270 = 8000.0f;
                    this->unk_278 = 8000.0f;
                }
                break;

            case 3:
                this->unk_250 = 2;
                this->unk_270 = 10000.0f;
                this->unk_278 = 10000.0f;
                if (this->unk_28A == 0) {
                    this->unk_270 = 3000.0f;
                    this->unk_278 = 3000.0f;
                }
                break;

            case 4:
                this->unk_24E = 5;
                this->unk_24C = this->unk_24E;
                break;

            case 5:
                this->unk_250 = 5;
                this->unk_270 = 14000.0f;
                this->unk_278 = 14000.0f;
                if (this->unk_28A == 0) {
                    this->unk_270 = 10000.0f;
                    this->unk_278 = 10000.0f;
                }
                break;
        }
    }

    if (this->unk_280 != this->unk_2B8) {
        Math_ApproachF(&this->unk_2B8, this->unk_280, 0.5f, 4000.0f);
    }

    if (this->unk_25C != this->unk_2B4) {
        Math_ApproachF(&this->unk_2B4, this->unk_25C, 0.5f, 4000.0f);
    }

    if (this->unk_264 != this->unk_29C) {
        Math_ApproachF(&this->unk_29C, this->unk_264, 0.8f, 7000.0f);
    }

    if (this->unk_278 != this->unk_2A0) {
        Math_ApproachF(&this->unk_2A0, this->unk_278, 0.8f, 7000.0f);
    }

    if (this->unk_27C != this->unk_2A4) {
        Math_ApproachF(&this->unk_2A4, this->unk_27C, 0.8f, 7000.0f);
    }

    if (this->unk_260 != this->unk_2A8) {
        Math_ApproachF(&this->unk_2A8, this->unk_260, 0.8f, 7000.0f);
    }

    if (this->unk_270 != this->unk_2AC) {
        Math_ApproachF(&this->unk_2AC, this->unk_270, 0.8f, 7000.0f);
    }

    if (this->unk_274 != this->unk_2B0) {
        Math_ApproachF(&this->unk_2B0, this->unk_274, 0.8f, 7000.0f);
    }
}

s32 func_809585B0(EnAttackNiw* this, GlobalContext* globalCtx) {
    s16 sp1E;
    s16 sp1C;

    Actor_SetFocus(&this->actor, this->unk_2DC);
    Actor_GetScreenPos(globalCtx, &this->actor, &sp1E, &sp1C);

    if ((this->actor.projectedPos.z < -20.0f) || (sp1E < 0) || (sp1E > SCREEN_WIDTH) || (sp1C < 0) ||
        (sp1C > SCREEN_HEIGHT)) {
        return false;
    }
    return true;
}

void func_80958634(EnAttackNiw* this, GlobalContext* globalCtx) {
    s16 sp4E;
    s16 sp4C;
    Vec3f temp;
    Vec3f sp34;
    s32 pad;

    this->actor.speedXZ = 10.0f;

    temp.x = (this->unk_290.x + globalCtx->view.at.x) - globalCtx->view.eye.x;
    temp.y = (this->unk_290.y + globalCtx->view.at.y) - globalCtx->view.eye.y;
    temp.z = (this->unk_290.z + globalCtx->view.at.z) - globalCtx->view.eye.z;

    sp34.x = globalCtx->view.at.x + temp.x;
    sp34.y = globalCtx->view.at.y + temp.y;
    sp34.z = globalCtx->view.at.z + temp.z;

    this->unk_2CC = Math_Vec3f_Yaw(&this->actor.world.pos, &sp34);
    this->unk_2C8 = Math_Vec3f_Pitch(&this->actor.world.pos, &sp34) * -1.0f;

    Math_SmoothStepToS(&this->actor.world.rot.y, this->unk_2CC, 5, this->unk_2D4, 0);
    Math_SmoothStepToS(&this->actor.world.rot.x, this->unk_2C8, 5, this->unk_2D4, 0);
    Math_ApproachF(&this->unk_2D4, 5000.0f, 1.0f, 100.0f);

    Actor_SetFocus(&this->actor, this->unk_2DC);
    Actor_GetScreenPos(globalCtx, &this->actor, &sp4E, &sp4C);

    if (this->actor.bgCheckFlags & 8) {
        this->unk_2CC = this->actor.yawTowardsPlayer;
        this->unk_2C8 = this->actor.world.rot.x - 3000.0f;
        this->unk_252 = 0;
        this->unk_254 = 100;
        this->unk_2D4 = 0.0f;
        this->unk_27C = 0.0f;
        this->unk_274 = 0.0f;
        this->unk_250 = this->unk_252;
        this->unk_24E = this->unk_252;
        this->unk_24C = this->unk_252;
        this->actor.gravity = -0.2f;
        this->unk_280 = 0.0f;
        this->actionFunc = func_80958974;
        this->unk_2D8 = 5.0f;
    } else if (((this->actor.projectedPos.z > 0.0f) && (fabsf(sp34.x - this->actor.world.pos.x) < 50.0f) &&
                (fabsf(sp34.y - this->actor.world.pos.y) < 50.0f) &&
                (fabsf(sp34.z - this->actor.world.pos.z) < 50.0f)) ||
               (this->actor.bgCheckFlags & 1)) {
        this->unk_252 = 0;
        this->unk_250 = this->unk_252;
        this->unk_24E = this->unk_252;
        this->unk_24C = this->unk_252;
        this->unk_2D4 = 0.0f;
        this->unk_274 = 0.0f;
        this->unk_27C = 0.0f;
        this->unk_2CC = this->actor.yawTowardsPlayer;
        this->unk_2C8 = this->actor.world.rot.x - 2000.0f;
        this->actor.gravity = -0.2f;
        this->unk_280 = 0.0f;
        this->actionFunc = func_80958974;
        this->unk_2D8 = 5.0f;
    } else {
        this->unk_24C = 10;
        this->unk_25C = -10000.0f;
        this->unk_280 = -3000.0f;
        func_80958228(this, globalCtx, 2);
    }
}

void func_80958974(EnAttackNiw* this, GlobalContext* globalCtx) {
    if (!func_809585B0(this, globalCtx)) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    if (this->actor.bgCheckFlags & 1) {
        if (this->unk_252 == 0) {
            this->unk_252 = 3;
            this->actor.velocity.y = 3.5f;
        }

        if (this->actor.gravity != -2.0f) {
            this->unk_2CC = this->actor.yawTowardsPlayer;
            this->unk_25A = 50;
            this->unk_254 = 100;
            this->unk_270 = 14000.0f;
            this->unk_278 = 14000.0f;
            this->unk_274 = 0.0f;
            this->unk_27C = 0.0f;
            this->unk_260 = 0.0f;
            this->unk_264 = 0.0f;
            this->unk_2C8 = 0.0f;
            this->actor.gravity = -2.0f;
        }
    }

    if (this->unk_254 == 50) {
        this->unk_2CC = randPlusMinusPoint5Scaled(200.0f) + this->actor.yawTowardsPlayer;
    }

    Math_SmoothStepToS(&this->actor.world.rot.y, this->unk_2CC, 2, this->unk_2D4, 0);
    Math_SmoothStepToS(&this->actor.world.rot.x, this->unk_2C8, 2, this->unk_2D4, 0);
    Math_ApproachF(&this->unk_2D4, 10000.0f, 1.0f, 1000.0f);
    Math_ApproachF(&this->actor.speedXZ, this->unk_2D8, 0.9f, 1.0f);

    if ((this->actor.gravity == -2.0f) && (this->unk_25A == 0) &&
        ((this->actor.bgCheckFlags & 8) || (this->unk_254 == 0))) {
        this->unk_2D8 = 0.0f;
        this->actor.gravity = 0.0f;
        this->unk_2D4 = 0.0f;
        this->unk_2C8 = this->actor.world.rot.x - 5000.0f;
        this->actionFunc = func_80958BE4;
    } else if (this->actor.bgCheckFlags & 1) {
        func_80958228(this, globalCtx, 5);
    } else {
        func_80958228(this, globalCtx, 2);
    }
}

void func_80958BE4(EnAttackNiw* this, GlobalContext* globalCtx) {
    if (!func_809585B0(this, globalCtx)) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    Math_SmoothStepToS(&this->actor.world.rot.x, this->unk_2C8, 5, this->unk_2D4, 0);
    Math_ApproachF(&this->unk_2D4, 5000.0f, 1.0f, 100.0f);
    Math_ApproachF(&this->actor.velocity.y, 5.0f, 0.3f, 1.0f);
    func_80958228(this, globalCtx, 2);
}

void EnAttackNiw_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnAttackNiw* this = THIS;
    s32 pad;
    EnNiw* parent;
    Player* player = GET_PLAYER(globalCtx);
    s32 pad2;
    Vec3f sp30;

    this->unk_284++;

    if (this->unk_24C != 0) {
        this->unk_24C--;
    }

    if (this->unk_250 != 0) {
        this->unk_250--;
    }

    if (this->unk_252 != 0) {
        this->unk_252--;
    }

    if (this->unk_256 != 0) {
        this->unk_256--;
    }

    if (this->unk_258 != 0) {
        this->unk_258--;
    }

    if (this->unk_254 != 0) {
        this->unk_254--;
    }

    if (this->unk_25A != 0) {
        this->unk_25A--;
    }

    this->actor.shape.rot = this->actor.world.rot;
    this->actor.shape.shadowScale = 15.0f;

    this->actionFunc(this, globalCtx);

    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 20.0f, 20.0f, 60.0f, 0x1D);

    if (this->actionFunc == func_80958634) {
        Actor_MoveWithoutGravity(&this->actor);
    } else {
        Actor_MoveWithGravity(&this->actor);
    }

    if (this->actor.floorHeight <= -32000.0f) {
        Actor_MarkForDeath(&this->actor);
    } else if ((this->actor.bgCheckFlags & 0x20) && (this->actionFunc != func_80958BE4)) {
        Math_Vec3f_Copy(&sp30, &this->actor.world.pos);
        sp30.y += this->actor.depthInWater;

        EffectSsGSplash_Spawn(globalCtx, &sp30, NULL, NULL, 0, 400);
        this->unk_2D4 = 0.0f;
        this->actor.gravity = 0.0f;
        this->unk_2D8 = 0.0f;
        this->unk_2C8 = this->actor.world.rot.x - 5000.0f;
        this->actionFunc = func_80958BE4;
    } else {
        f32 temp = 20.0f;

    label:

        if (this->actor.xyzDistToPlayerSq < SQ(temp)) {
            parent = (EnNiw*)this->actor.parent;
            if ((this->actor.parent->update != NULL) && (this->actor.parent != NULL) && (parent != NULL) &&
                (parent->unusedTimer25E == 0) && (player->invincibilityTimer == 0)) {
                func_800B8D50(globalCtx, &this->actor, 2.0f, this->actor.world.rot.y, 0.0f, 0x10);
                parent->unusedTimer25E = 70;
            }
        }

        if (this->unk_256 == 0) {
            this->unk_256 = 30;
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_CHICKEN_CRY_A);
        }

        if (this->unk_258 == 0) {
            this->unk_258 = 7;
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_CHICKEN_FLUTTER);
        }
    }
}

s32 EnAttackNiw_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                                 Actor* thisx) {
    EnAttackNiw* this = THIS;

    if (limbIndex == OBJECT_NIW_LIMB_0D) {
        rot->y += (s16)this->unk_2B4;
    }

    if (limbIndex == OBJECT_NIW_LIMB_0F) {
        rot->z += (s16)this->unk_2B8;
    }

    if (limbIndex == OBJECT_NIW_LIMB_0B) {
        rot->x += (s16)this->unk_2B0;
        rot->y += (s16)this->unk_2AC;
        rot->z += (s16)this->unk_2A8;
    }

    if (limbIndex == OBJECT_NIW_LIMB_07) {
        rot->x += (s16)this->unk_2A4;
        rot->y += (s16)this->unk_2A0;
        rot->z += (s16)this->unk_29C;
    }
    return false;
}

void EnAttackNiw_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnAttackNiw* this = THIS;

    func_8012C28C(globalCtx->state.gfxCtx);
    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnAttackNiw_OverrideLimbDraw, NULL, &this->actor);
}
