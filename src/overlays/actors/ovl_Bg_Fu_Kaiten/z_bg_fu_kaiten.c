/*
 * File: z_bg_fu_kaiten.c
 * Overlay: ovl_Bg_Fu_Kaiten
 * Description: Honey & Darling's Shop - Rotating Platform
 */

#include "z_bg_fu_kaiten.h"
#include "objects/object_fu_kaiten/object_fu_kaiten.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((BgFuKaiten*)thisx)

void BgFuKaiten_Init(Actor* thisx, GlobalContext* globalCtx);
void BgFuKaiten_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgFuKaiten_Update(Actor* thisx, GlobalContext* globalCtx);
void BgFuKaiten_Draw(Actor* thisx, GlobalContext* globalCtx);

const ActorInit Bg_Fu_Kaiten_InitVars = {
    ACTOR_BG_FU_KAITEN,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_FU_KAITEN,
    sizeof(BgFuKaiten),
    (ActorFunc)BgFuKaiten_Init,
    (ActorFunc)BgFuKaiten_Destroy,
    (ActorFunc)BgFuKaiten_Update,
    (ActorFunc)BgFuKaiten_Draw,
};

void BgFuKaiten_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    BgFuKaiten* this = THIS;
    CollisionHeader* header = NULL;

    Actor_SetScale(thisx, 1.0);
    DynaPolyActor_Init(&this->dyna, 3);
    CollisionHeader_GetVirtual(&object_fu_kaiten_Colheader_002D30, &header);
    this->dyna.bgId = DynaPoly_SetBgActor(globalCtx, &globalCtx->colCtx.dyna, &this->dyna.actor, header);

    this->bounceHeight = 0.0;
    this->rotationSpeed = 0;
    this->bounceSpeed = 0;
    this->bounce = 0;
}

void BgFuKaiten_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    BgFuKaiten* this = THIS;

    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
}

void BgFuKaiten_UpdateRotation(BgFuKaiten* this) {
    f32 f0;

    this->dyna.actor.shape.rot.y += this->rotationSpeed;
    if (this->rotationSpeed > 0) {
        f0 = this->rotationSpeed * 0.002f;
        func_8019FAD8(&this->dyna.actor.projectedPos, NA_SE_EV_WOOD_GEAR - SFX_FLAG, f0);
    }
}

void BgFuKaiten_UpdateHeight(BgFuKaiten* this) {
    this->bounce += this->bounceSpeed;
    this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y + this->elevation + this->bounceHeight;

    this->dyna.actor.world.pos.y -= this->bounceHeight * Math_CosS(this->bounce);
}

void BgFuKaiten_Update(Actor* thisx, GlobalContext* globalCtx) {
    BgFuKaiten* this = THIS;

    BgFuKaiten_UpdateRotation(this);
    BgFuKaiten_UpdateHeight(this);
}

void BgFuKaiten_Draw(Actor* thisx, GlobalContext* globalCtx) {
    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, object_fu_kaiten_DL_0005D0);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
