/*
 * File: z_en_bh.c
 * Overlay: ovl_En_Bh
 * Description: Brown Bird (on the Moon)
 */

#include "z_en_bh.h"
#include "objects/object_bh/object_bh.h"

#define FLAGS 0x00000000

#define THIS ((EnBh*)thisx)

void EnBh_Init(Actor* thisx, PlayState* play);
void EnBh_Destroy(Actor* thisx, PlayState* play);
void EnBh_Update(Actor* thisx, PlayState* play);
void EnBh_Draw(Actor* thisx, PlayState* play);

void func_80C22DEC(EnBh* this, PlayState* play);

const ActorInit En_Bh_InitVars = {
    ACTOR_EN_BH,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_BH,
    sizeof(EnBh),
    (ActorFunc)EnBh_Init,
    (ActorFunc)EnBh_Destroy,
    (ActorFunc)EnBh_Update,
    (ActorFunc)EnBh_Draw,
};

void EnBh_Init(Actor* thisx, PlayState* play) {
    EnBh* this = THIS;

    this->actor.flags &= ~ACTOR_FLAG_1;
    Actor_SetScale(&this->actor, 0.01f);
    SkelAnime_InitFlex(play, &this->skelanime, &object_bh_Skel_001E60, &object_bh_Anim_000074, &this->unk188,
                       &this->unk1AC, 6);
    Animation_PlayLoop(&this->skelanime, &object_bh_Anim_000074);
    this->actionFunc = func_80C22DEC;
}

void EnBh_Destroy(Actor* thisx, PlayState* play) {
}

void func_80C22DEC(EnBh* this, PlayState* play) {
    f32 xDiff;
    f32 yDiff;
    f32 zDiff;
    f32 hypotenuse;
    s16 xRot;
    s16 yRot;
    s16 zRot;

    this->actor.speedXZ = 3.0f;
    xDiff = this->pos.x - this->actor.world.pos.x;
    yDiff = this->pos.y - this->actor.world.pos.y;
    zDiff = this->pos.z - this->actor.world.pos.z;
    hypotenuse = sqrtf(SQ(xDiff) + SQ(zDiff));

    if ((this->unk1DE == 0) || (hypotenuse < 100.0f)) {
        this->pos.x = randPlusMinusPoint5Scaled(300.0f) + this->actor.home.pos.x;
        this->pos.y = randPlusMinusPoint5Scaled(100.0f) + this->actor.home.pos.y;
        this->pos.z = randPlusMinusPoint5Scaled(300.0f) + this->actor.home.pos.z;
        this->unk1DE = Rand_ZeroFloat(50.0f) + 30.0f;
        this->step = 0;
    }

    yRot = Math_Atan2S(xDiff, zDiff);
    xRot = Math_Atan2S(yDiff, hypotenuse);
    zRot = Math_SmoothStepToS(&this->actor.world.rot.y, yRot, 0xA, this->step, 0);

    if (zRot > 0x1000) {
        zRot = 0x1000;
    } else if (zRot < (-0x1000)) {
        zRot = -0x1000;
    }

    Math_ApproachS(&this->actor.world.rot.x, xRot, 0xA, this->step);
    Math_ApproachS(&this->actor.world.rot.z, (zRot * (-1)), 0xA, this->step);
    Math_ApproachS(&this->step, 0x200, 1, 0x10);

    if (((s32)this->skelanime.playSpeed) == 0) {
        if (this->unk1DC == 0) {
            this->skelanime.playSpeed = 1.0f;
            this->unk1DC = Rand_ZeroFloat(70.0f) + 50.0f;
        } else if (((this->unk1DC & 7) == 7) && (Rand_ZeroOne() < 0.5f)) {
            this->unk1E4 = randPlusMinusPoint5Scaled(3000.0f);
        }
    } else {
        SkelAnime_Update(&this->skelanime);
        if ((this->unk1DC == 0) && (Animation_OnFrame(&this->skelanime, 6.0f) != 0)) {
            this->skelanime.playSpeed = 0.0f;
            this->unk1DC = Rand_ZeroFloat(50.0f) + 50.0f;
        }
    }

    this->actor.shape.rot.x = -this->actor.world.rot.x;
    this->actor.shape.rot.y = this->actor.world.rot.y;
    this->actor.shape.rot.z = this->actor.world.rot.z;
    Math_ApproachS(&this->unk1E2, this->unk1E4, 3, 0x3E8);
}

void EnBh_Update(Actor* thisx, PlayState* play) {
    EnBh* this = THIS;

    Actor_MoveWithoutGravity(&this->actor);
    if (this->unk1DE != 0) {
        this->unk1DE--;
    }
    if (this->unk1DC != 0) {
        this->unk1DC--;
    }
    this->actionFunc(this, play);
    Math_Vec3f_Copy(&this->actor.focus.pos, &this->actor.world.pos);
}

void EnBh_Draw(Actor* thisx, PlayState* play) {
    EnBh* this = THIS;

    func_8012C28C(play->state.gfxCtx);
    Matrix_RotateZS(this->unk1E2, MTXMODE_APPLY);
    SkelAnime_DrawFlexOpa(play, this->skelanime.skeleton, this->skelanime.jointTable, this->skelanime.dListCount, NULL,
                          NULL, &this->actor);
}
