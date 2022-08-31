/*
 * File: z_en_paper.c
 * Overlay: ovl_En_Paper
 * Description: Tingle Confetti
 */

#include "z_en_paper.h"
#include "objects/object_bal/object_bal.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_100000 | ACTOR_FLAG_2000000)

#define THIS ((EnPaper*)thisx)

void EnPaper_Init(Actor* thisx, PlayState* play);
void EnPaper_Destroy(Actor* thisx, PlayState* play);
void EnPaper_Update(Actor* thisx, PlayState* play);
void EnPaper_Draw(Actor* thisx, PlayState* play);

void func_80C1F480(EnPaper* this, PlayState* play);
void func_80C1F4FC(EnPaper* this, PlayState* play);
void func_80C1F46C(EnPaper* this);
void func_80C1F4E8(EnPaper* this);
void func_80C1F55C(EnPaper* this, EnPaperPiece* piece);
void func_80C1F6E0(EnPaper* this, EnPaperPiece* piece);

const ActorInit En_Paper_InitVars = {
    ACTOR_EN_PAPER,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_BAL,
    sizeof(EnPaper),
    (ActorFunc)EnPaper_Init,
    (ActorFunc)EnPaper_Destroy,
    (ActorFunc)EnPaper_Update,
    (ActorFunc)EnPaper_Draw,
};

static Vec3f sUnitVectorZ = { 0.0f, 0.0f, 1.0f };

void EnPaper_Init(Actor* thisx, PlayState* play) {
    EnPaper* this = THIS;

    Actor_SetScale(&this->actor, 0.01f);
    this->timer = 70;
    this->unk_D78 = sUnitVectorZ;
    Actor_UpdateBgCheckInfo(play, &this->actor, 0.0f, 0.0f, 0.0f, 4);
    func_80C1F46C(this);
}

void EnPaper_Destroy(Actor* thisx, PlayState* play) {
}

void func_80C1F46C(EnPaper* this) {
    this->actionFunc = func_80C1F480;
}

// Setup
void func_80C1F480(EnPaper* this, PlayState* play) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(this->pieces); i++) {
        func_80C1F55C(this, &this->pieces[i]);
    }

    func_80C1F4E8(this);
}

void func_80C1F4E8(EnPaper* this) {
    this->actionFunc = func_80C1F4FC;
}

// Main falling function
void func_80C1F4FC(EnPaper* this, PlayState* play) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(this->pieces); i++) {
        func_80C1F6E0(this, &this->pieces[i]);
    }
}

// axis/pos/vel/angle/angVel setup
void func_80C1F55C(EnPaper* this, EnPaperPiece* piece) {
    // Pick rotation axis randomly (biased towards the z == 0 plane)
    Matrix_RotateZYX(Rand_Next(), Rand_Next(), Rand_Next(), MTXMODE_NEW);
    Matrix_MultVec3f(&sUnitVectorZ, &piece->axis);

    // copy actor position and distribute uniformly in a cube of side 2 around it
    piece->pos = this->actor.world.pos;
    piece->pos.x += Rand_Centered() * 4.0f;
    piece->pos.y += Rand_Centered() * 4.0f;
    piece->pos.z += Rand_Centered() * 4.0f;

    // copy actor velocity and distrbute uniformly in a cuboid with sides 4.5, 6, 4.5.
    piece->vel = this->actor.velocity;
    piece->vel.x += Rand_Centered() * 9.0f;
    piece->vel.y += Rand_ZeroOne() * 6.0f;
    piece->vel.z += Rand_Centered() * 9.0f;

    // Choose random starting angle and angular velocity
    piece->angle = Rand_Next();
    piece->angVel = (Rand_Next() >> 4) + (0x10000 / 180);

    // Rotate the unit Z-vector by the random starting axis and angle
    Matrix_RotateAxisS(piece->angle, &piece->axis, MTXMODE_NEW);
    Matrix_MultVec3f(&sUnitVectorZ, &piece->unk_00);
}

// Main falling motions function
void func_80C1F6E0(EnPaper* this, EnPaperPiece* piece) {
    f32 cos = Math_CosS(piece->angle);
    f32 sin = Math_SinS(piece->angle);
    f32 versin = 1.0f - cos;

    if (piece->pos.y < (this->actor.floorHeight - 40.0f)) {
        return;
    }

    // acceleration due to gravity
    piece->vel.y += this->actor.gravity;

    // drag?
    piece->vel.x -= 0.2f * fabsf(piece->unk_00.x) * (piece->vel.x + this->unk_D78.x);
    piece->vel.y -= 0.2f * fabsf(piece->unk_00.y) * (piece->vel.y + this->unk_D78.y);
    piece->vel.z -= 0.2f * fabsf(piece->unk_00.z) * (piece->vel.z + this->unk_D78.z);

    // rotate around axis
    piece->angle += piece->angVel;

    // move
    piece->pos.x += piece->vel.x;
    piece->pos.y += piece->vel.y;
    piece->pos.z += piece->vel.z;

    // Rotate unit Z vector about `axis` by `angle` to get unk_00. This is the same calculation as at the bottom of
    // func_80C1F55C(), but done manually instead of using any matrix functions.
    piece->unk_00.x = (versin * piece->axis.x * piece->axis.z) - (piece->axis.y * sin);
    piece->unk_00.y = (versin * piece->axis.y * piece->axis.z) + (piece->axis.x * sin);
    piece->unk_00.z = (versin * piece->axis.z * piece->axis.z) + cos;
}

// Used in Update. Update shape rotation randomly and 
void func_80C1F87C(EnPaper* this) {
    f32 force = (Rand_Centered() * 4.0f) + 6.0f;
    f32 cosX;

    this->unk_D78.y = Math_SinS(this->actor.shape.rot.x) * -force;

    cosX = Math_CosS(this->actor.shape.rot.x) * -force;
    this->unk_D78.x = Math_SinS(this->actor.shape.rot.y) * cosX;
    this->unk_D78.z = Math_CosS(this->actor.shape.rot.y) * cosX;

    this->actor.shape.rot.x += (s16)(Rand_Next() >> 8);
    this->actor.shape.rot.y += (s16)(Rand_Next() >> 6);

    // Essentially a clamp
    if (ABS_ALT(this->actor.shape.rot.x) > 0x10000 / 12) {
        if (this->actor.shape.rot.x > 0) {
            this->actor.shape.rot.x = 0x10000 / 12;
        } else {
            this->actor.shape.rot.x = -0x10000 / 12;
        }
    }
}

void EnPaper_Update(Actor* thisx, PlayState* play) {
    EnPaper* this = THIS;

    this->actionFunc(this, play);

    func_80C1F87C(this);
    if (this->timer == 0) {
        Actor_MarkForDeath(&this->actor);
    } else {
        this->timer--;
    }
}

void EnPaper_Draw(Actor* thisx, PlayState* play) {
    EnPaper* this = THIS;
    EnPaperPiece* piece = this->pieces;
    s32 i;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C5B0(play->state.gfxCtx);

    gDPSetRenderMode(POLY_OPA_DISP++, G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2);
    gDPSetCombineLERP(POLY_OPA_DISP++, 0, 0, 0, SHADE, 0, 0, 0, SHADE, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED);
    gSPLoadGeometryMode(POLY_OPA_DISP++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH);

    for (i = 0; i < ARRAY_COUNT(this->pieces); i++, piece++) {
        // colour the first 30 white and 10 each of the other 3 colours
        if (i == 0) {
            gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, 255);
        } else if (i == 30) {
            gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 32, 32, 255);
        } else if (i == 40) {
            gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 64, 128, 255, 255);
        } else if (i == 50) {
            gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 64, 255, 128, 255);
        }

        if ((this->actor.floorHeight - 40.0f) < piece->pos.y) {
            Mtx* mtx = GRAPH_ALLOC(play->state.gfxCtx, sizeof(Mtx));

            func_8017842C(mtx, this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, piece->angle,
                          piece->axis.x, piece->axis.y, piece->axis.z, piece->pos.x, piece->pos.y, piece->pos.z);

            gSPMatrix(POLY_OPA_DISP++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_OPA_DISP++, gTingleConfettiDL);
        }
    }

    CLOSE_DISPS(play->state.gfxCtx);
}
