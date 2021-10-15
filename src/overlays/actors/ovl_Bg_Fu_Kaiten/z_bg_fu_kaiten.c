#include "z_bg_fu_kaiten.h"

#define FLAGS 0x00000030

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

extern Gfx D_060005D0[];
extern CollisionHeader D_06002D30;

void BgFuKaiten_Init(Actor* thisx, GlobalContext* globalCtx) {
    UNK_TYPE pad0;
    UNK_TYPE pad1;
    CollisionHeader* header = 0;

    Actor_SetScale(thisx, 1.0);
    BgCheck3_BgActorInit(&THIS->dyna, 3);
    CollisionHeader_GetVirtual(&D_06002D30, &header);
    THIS->dyna.bgId = DynaPoly_SetBgActor(globalCtx, &globalCtx->colCtx.dyna, &THIS->dyna.actor, header);

    THIS->bouceHeight = 0.0;
    THIS->rotationSpeed = 0;
    THIS->bounceSpeed = 0;
    THIS->bounce = 0;
}

void BgFuKaiten_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, THIS->dyna.bgId);
}

void BgFuKaiten_UpdateRotation(BgFuKaiten* this) {
    f32 f0;
    this->dyna.actor.shape.rot.y += this->rotationSpeed;
    if (this->rotationSpeed > 0) {
        f0 = this->rotationSpeed * .002f;
        func_8019FAD8(&this->dyna.actor.projectedPos, 8310, f0);
    }
}

void BgFuKaiten_UpdateHeight(BgFuKaiten* this) {
    this->bounce += this->bounceSpeed;
    this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y + this->elevation + this->bouceHeight;

    this->dyna.actor.world.pos.y -= this->bouceHeight * Math_CosS(this->bounce);
}

void BgFuKaiten_Update(Actor* thisx, GlobalContext* globalCtx) {
    BgFuKaiten_UpdateRotation(THIS);
    BgFuKaiten_UpdateHeight(THIS);
}

void BgFuKaiten_Draw(Actor* thisx, GlobalContext* globalCtx) {
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    UNK_TYPE pad;

    func_8012C28C(gfxCtx);

    gSPMatrix(gfxCtx->polyOpa.p++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfxCtx->polyOpa.p++, D_060005D0);
}
