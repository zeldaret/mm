/*
 * File: z_en_bu.c
 * Overlay: ovl_En_Bu
 * Description: Unused dummied-out enemy
 */

#include "z_en_bu.h"

#define FLAGS (ACTOR_FLAG_1)

#define THIS ((EnBu*)thisx)

void EnBu_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBu_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBu_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBu_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnBu_DoNothing(EnBu* this, GlobalContext* globalCtx);

const ActorInit En_Bu_InitVars = {
    ACTOR_EN_BU,
    ACTORCAT_ENEMY,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnBu),
    (ActorFunc)EnBu_Init,
    (ActorFunc)EnBu_Destroy,
    (ActorFunc)EnBu_Update,
    (ActorFunc)EnBu_Draw,
};

void EnBu_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnBu* this = THIS;

    this->actionFunc = EnBu_DoNothing;
}

void EnBu_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void EnBu_DoNothing(EnBu* this, GlobalContext* globalCtx) {
}

void EnBu_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnBu* this = THIS;

    Actor_MoveWithGravity(&this->actor);
    this->actionFunc(this, globalCtx);
}

void EnBu_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnBu* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    Matrix_InsertTranslation(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, MTXMODE_NEW);
    Matrix_InsertZRotation_s(this->actor.shape.rot.z, MTXMODE_APPLY);
    Matrix_RotateY(this->actor.shape.rot.y, MTXMODE_APPLY);
    Matrix_InsertXRotation_s(this->actor.shape.rot.x, MTXMODE_APPLY);
    Matrix_Scale(0.01f, 0.01f, 0.01f, MTXMODE_APPLY);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, this->displayListPtr);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
