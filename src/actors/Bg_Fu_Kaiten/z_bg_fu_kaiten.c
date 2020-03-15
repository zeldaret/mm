#include <ultra64.h>
#include <global.h>

ActorInit bgFuKaitenInitData = {
    0x01AE,
    1,
    0,
    0x30,
    0x01A0,
    sizeof(ActorBgFuKaiten),
    (actor_func)&BgFuKaiten_Init,
    (actor_func)&BgFuKaiten_Destroy,
    (actor_func)&BgFuKaiten_Update,
    (actor_func)&BgFuKaiten_Draw
};

void BgFuKaiten_Init(ActorBgFuKaiten* this, GlobalContext* ctxt) {
    UNK_TYPE pad0;
    UNK_TYPE pad1;
    BgMeshHeader* header = 0;

    Actor_SetScale(&this->bg.actor, 1.0);
    BcCheck3_BgActorInit(&this->bg, 3);
    BgCheck_RelocateMeshHeader(&object_fu_kaiten_002D30, &header);
    this->bg.dynaPolyId = BgCheck_AddActorMesh(ctxt, &ctxt->colCtx.dyna, &this->bg, header);

    this->bouceHeight = 0.0;
    this->rotationSpeed = 0;
    this->bounceSpeed = 0;
    this->bounce = 0;
}

void BgFuKaiten_Destroy(ActorBgFuKaiten* this, GlobalContext* ctxt) {
    BgCheck_RemoveActorMesh(ctxt, &ctxt->colCtx.dyna, this->bg.dynaPolyId);
}

void BgFuKaiten_UpdateRotation(ActorBgFuKaiten* this) {
    f32 f0;
    this->bg.actor.shape.rot.y += this->rotationSpeed;
    if (this->rotationSpeed > 0)
    {
        f0 = this->rotationSpeed * .002f;
        func_8019FAD8(&this->bg.actor.unkEC, 8310, f0);
    }
}

void BgFuKaiten_UpdateHeight(ActorBgFuKaiten* this) {
    this->bounce += this->bounceSpeed;
    this->bg.actor.currPosRot.pos.y = this->bg.actor.initPosRot.pos.y + this->elevation + this->bouceHeight;

    this->bg.actor.currPosRot.pos.y -= this->bouceHeight * Math_Coss(this->bounce);
}

void BgFuKaiten_Update(ActorBgFuKaiten* this, GlobalContext* ctxt) {
    BgFuKaiten_UpdateRotation(this);
    BgFuKaiten_UpdateHeight(this);
}

void BgFuKaiten_Draw(ActorBgFuKaiten* this, GlobalContext* ctxt) {
    GraphicsContext* gfxCtx = ctxt->state.gfxCtx;
    UNK_TYPE pad;

    func_8012C28C(gfxCtx);

    gSPMatrix(gfxCtx->polyOpa.p++, SysMatrix_AppendStateToPolyOpaDisp(ctxt->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfxCtx->polyOpa.p++, object_fu_kaiten_0005D0);
}
