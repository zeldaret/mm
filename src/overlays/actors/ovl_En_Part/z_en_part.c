/*
 * File: z_en_part.c
 * Overlay: ovl_En_Part
 * Description: Enemy body parts (spawned when dying)
 */

#include "z_en_part.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((EnPart*)thisx)

void EnPart_Init(Actor* thisx, PlayState* play);
void EnPart_Destroy(Actor* thisx, PlayState* play);
void EnPart_Update(Actor* thisx, PlayState* play);
void EnPart_Draw(Actor* thisx, PlayState* play);

void func_80865390(EnPart* this, PlayState* play);
void func_808654C4(EnPart* this, PlayState* play);

const ActorInit En_Part_InitVars = {
    ACTOR_EN_PART,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnPart),
    (ActorFunc)EnPart_Init,
    (ActorFunc)EnPart_Destroy,
    (ActorFunc)EnPart_Update,
    (ActorFunc)EnPart_Draw,
};

Vec3f D_80865900 = { 0.0f, 0.0f, 0.0f };

static void (*D_8086590C[5])(EnPart*, PlayState*) = {
    func_80865390, func_808654C4, 0x00000000, 0x00000000, 0x00000000,
};

void EnPart_Init(Actor* thisx, PlayState* play) {
    EnPart* this = THIS;
}

void EnPart_Destroy(Actor* thisx, PlayState* play) {
    EnPart* this = THIS;
}

void func_80865390(EnPart* this, PlayState* play) {
    f32 randVar;

    this->unk144 = 1;
    this->actor.world.rot.y = (s16)(Rand_ZeroOne() * 20000.0f);
    switch (this->actor.params) {
        case 1:

        case 4:
            randVar = Rand_ZeroOne() * 17.0f;
            this->unk146 += (s16)randVar + 5;
            this->actor.velocity.y = (Rand_ZeroOne() * 5.0f) + 4.0f;
            this->actor.gravity = (-0.6f) - (Rand_ZeroOne() * 0.5f);
            this->unk14C = 0.15f;
            break;

        case 15:
            this->actor.world.rot.y = this->actor.parent->shape.rot.y + 32768;
            this->unk146 = 100;
            this->actor.velocity.y = 7.0f;
            this->actor.speedXZ = 2.0f;
            this->actor.gravity = -1.0f;
            break;
    }
}

void func_808654C4(EnPart* this, PlayState* play) {
    s16 tempVar;
    Vec3f sp88;
    Vec3f sp74;
    s32 counter;
    Vec3f sp64;

    sp74 = D_80865900;

    if (this->actor.params == 15) {
        this->unk146 -= 1;
        if (this->unk146 > 0) {
            this->actor.shape.rot.x += 15000;
            this->actor.shape.rot.y = this->actor.shape.rot.y;
            this->actor.shape.rot.z = this->actor.shape.rot.z;
            if (BgCheck_SphVsFirstPoly(&play->colCtx, &this->actor.world.pos, 20.0f)) {
                this->unk146 = 0;
            }
        } else {
            Math_Vec3f_Copy(&sp64, &this->actor.world.pos);
            sp64.y = this->actor.floorHeight;
            func_800B3030(play, &sp64, &gZeroVec3f, &gZeroVec3f, (s16)(this->actor.scale.y * 1400.0f), 7, 0);
            SoundSource_PlaySfxAtFixedWorldPos(play, &this->actor.world.pos, 10, 14456);
            Actor_MarkForDeath(&this->actor);
        }
    } else {
        if (this->unk146 <= 0) {
            switch (this->actor.params) {
                case 1:
                    func_800B3030(play, &this->actor.world.pos, &gZeroVec3f, &gZeroVec3f,
                                  (s16)(this->actor.scale.y * 4000.0f), 7, 1);
                    SoundSource_PlaySfxAtFixedWorldPos(play, &this->actor.world.pos, 10, 14456);
                    break;
                case 4:
                    for (counter = 7; counter >= 0; counter--) {
                        sp88.x = randPlusMinusPoint5Scaled(60.0f) + this->actor.world.pos.x;
                        sp88.y = randPlusMinusPoint5Scaled(50.0f) +
                                 (this->actor.world.pos.y + (this->actor.shape.yOffset * this->actor.scale.y));
                        sp88.z = randPlusMinusPoint5Scaled(60.0f) + this->actor.world.pos.z;
                        sp74.y = Rand_ZeroOne() + 1.0f;
                        tempVar = Rand_S16Offset(80, 100);
                        EffectSsDtBubble_SpawnColorProfile(play, &sp88, &sp74, &gZeroVec3f, tempVar, 25, 0, 1);
                    }
                    break;
            }
            Actor_MarkForDeath(&this->actor);
        } else {
            this->unk146 -= 1;
            this->unk148 += this->unk14C;
        }
    }
}

void EnPart_Update(Actor* thisx, PlayState* play) {
    EnPart* this = (EnPart*)thisx;

    Actor_MoveWithGravity(&this->actor);
    D_8086590C[this->unk144](this, play);
}

void EnPart_Draw(Actor* thisx, PlayState* play) {
    EnPart* this = (EnPart*)thisx;

    OPEN_DISPS(play->state.gfxCtx);

    if (this->actor.params > 0) {
        Matrix_RotateZF(this->unk148, MTXMODE_APPLY);
    }
    func_8012C28C(play->state.gfxCtx);
    func_800B8050(&this->actor, play, 0);
    if (this->actor.params == 15) {
        gSPSegment(POLY_OPA_DISP++, 0x0C, gEmptyDL);
    }
    if (this->unk_150 != NULL) {
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, this->unk_150);
    }

    CLOSE_DISPS(play->state.gfxCtx);
}
