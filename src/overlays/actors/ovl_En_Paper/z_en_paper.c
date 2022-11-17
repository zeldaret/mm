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
void func_80C1F55C(EnPaper* this, EnPaperStruct* arg1);
void func_80C1F6E0(EnPaper* this, EnPaperStruct* arg1);

ActorInit En_Paper_InitVars = {
    /**/    ACTOR_EN_PAPER,
    /**/    ACTORCAT_ITEMACTION,
    /**/    FLAGS,
    /**/    OBJECT_BAL,
    /**/    sizeof(EnPaper),
    /**/    EnPaper_Init,
    /**/    EnPaper_Destroy,
    /**/    EnPaper_Update,
    /**/    EnPaper_Draw,
};

Vec3f D_80C1FC60 = { 0.0f, 0.0f, 1.0f };

void EnPaper_Init(Actor* thisx, PlayState* play) {
    EnPaper* this = THIS;

    Actor_SetScale(&this->actor, 0.01f);
    this->timer = 70;
    this->unk_D78 = D_80C1FC60;
    Actor_UpdateBgCheckInfo(play, &this->actor, 0.0f, 0.0f, 0.0f, 4);
    func_80C1F46C(this);
}

void EnPaper_Destroy(Actor* thisx, PlayState* play) {
}

void func_80C1F46C(EnPaper* this) {
    this->actionFunc = func_80C1F480;
}

void func_80C1F480(EnPaper* this, PlayState* play) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(this->unk_148); i++) {
        func_80C1F55C(this, &this->unk_148[i]);
    }

    func_80C1F4E8(this);
}

void func_80C1F4E8(EnPaper* this) {
    this->actionFunc = func_80C1F4FC;
}

void func_80C1F4FC(EnPaper* this, PlayState* play) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(this->unk_148); i++) {
        func_80C1F6E0(this, &this->unk_148[i]);
    }
}

void func_80C1F55C(EnPaper* this, EnPaperStruct* arg1) {
    Matrix_RotateZYX(Rand_Next(), Rand_Next(), Rand_Next(), MTXMODE_NEW);
    Matrix_MultVec3f(&D_80C1FC60, &arg1->unk_0C);

    arg1->unk_18 = this->actor.world.pos;

    arg1->unk_18.x += Rand_Centered() * 4.0f;
    arg1->unk_18.y += Rand_Centered() * 4.0f;
    arg1->unk_18.z += Rand_Centered() * 4.0f;

    arg1->unk_24 = this->actor.velocity;

    arg1->unk_24.x += Rand_Centered() * 9.0f;
    arg1->unk_24.y += Rand_ZeroOne() * 6.0f;
    arg1->unk_24.z += Rand_Centered() * 9.0f;

    arg1->unk_30 = Rand_Next();
    arg1->unk_32 = (Rand_Next() >> 4) + 0x16C;

    Matrix_RotateAxisS(arg1->unk_30, &arg1->unk_0C, MTXMODE_NEW);
    Matrix_MultVec3f(&D_80C1FC60, &arg1->unk_00);
}

void func_80C1F6E0(EnPaper* this, EnPaperStruct* arg1) {
    f32 sp1C = Math_CosS(arg1->unk_30);
    f32 sp18 = Math_SinS(arg1->unk_30);
    f32 temp_ft4 = 1.0f - sp1C;

    if (arg1->unk_18.y < (this->actor.floorHeight - 40.0f)) {
        return;
    }

    arg1->unk_24.y += this->actor.gravity;

    arg1->unk_24.x -= 0.2f * fabsf(arg1->unk_00.x) * (arg1->unk_24.x + this->unk_D78.x);
    arg1->unk_24.y -= 0.2f * fabsf(arg1->unk_00.y) * (arg1->unk_24.y + this->unk_D78.y);
    arg1->unk_24.z -= 0.2f * fabsf(arg1->unk_00.z) * (arg1->unk_24.z + this->unk_D78.z);

    arg1->unk_30 += arg1->unk_32;

    arg1->unk_18.x += arg1->unk_24.x;
    arg1->unk_18.y += arg1->unk_24.y;
    arg1->unk_18.z += arg1->unk_24.z;

    arg1->unk_00.x = (arg1->unk_0C.x * temp_ft4 * arg1->unk_0C.z) - (arg1->unk_0C.y * sp18);
    arg1->unk_00.y = (arg1->unk_0C.y * temp_ft4 * arg1->unk_0C.z) + (arg1->unk_0C.x * sp18);
    arg1->unk_00.z = (arg1->unk_0C.z * temp_ft4 * arg1->unk_0C.z) + sp1C;
}

void func_80C1F87C(EnPaper* this) {
    f32 sp2C = (Rand_Centered() * 4.0f) + 6.0f;
    f32 sp28;

    this->unk_D78.y = Math_SinS(this->actor.shape.rot.x) * -sp2C;

    sp28 = Math_CosS(this->actor.shape.rot.x) * -sp2C;
    this->unk_D78.x = Math_SinS(this->actor.shape.rot.y) * sp28;
    this->unk_D78.z = Math_CosS(this->actor.shape.rot.y) * sp28;

    this->actor.shape.rot.x += (s16)(Rand_Next() >> 8);
    this->actor.shape.rot.y += (s16)(Rand_Next() >> 6);

    if (ABS_ALT(this->actor.shape.rot.x) > 0x1555) {
        if (this->actor.shape.rot.x > 0) {
            this->actor.shape.rot.x = 0x1555;
        } else {
            this->actor.shape.rot.x = -0x1555;
        }
    }
}

void EnPaper_Update(Actor* thisx, PlayState* play) {
    EnPaper* this = THIS;

    this->actionFunc(this, play);

    func_80C1F87C(this);
    if (this->timer == 0) {
        Actor_Kill(&this->actor);
        return;
    }

    this->timer--;
}

void EnPaper_Draw(Actor* thisx, PlayState* play) {
    EnPaper* this = THIS;
    EnPaperStruct* ptr = this->unk_148;
    s32 i;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C5B0(play->state.gfxCtx);

    gDPSetRenderMode(POLY_OPA_DISP++, G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2);
    gDPSetCombineLERP(POLY_OPA_DISP++, 0, 0, 0, SHADE, 0, 0, 0, SHADE, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED);
    gSPLoadGeometryMode(POLY_OPA_DISP++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH);

    for (i = 0; i < ARRAY_COUNT(this->unk_148); i++, ptr++) {
        if (i == 0) {
            gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, 255);
        } else if (i == 30) {
            gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 32, 32, 255);
        } else if (i == 40) {
            gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 64, 128, 255, 255);
        } else if (i == 50) {
            gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 64, 255, 128, 255);
        }

        if ((this->actor.floorHeight - 40.0f) < ptr->unk_18.y) {
            MtxF* mf = GRAPH_ALLOC(play->state.gfxCtx, sizeof(MtxF));

            func_8017842C(mf, this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, ptr->unk_30, ptr->unk_0C.x,
                          ptr->unk_0C.y, ptr->unk_0C.z, ptr->unk_18.x, ptr->unk_18.y, ptr->unk_18.z);

            gSPMatrix(POLY_OPA_DISP++, mf, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_OPA_DISP++, object_bal_DL_00D5A0);
        }
    }

    CLOSE_DISPS(play->state.gfxCtx);
}
