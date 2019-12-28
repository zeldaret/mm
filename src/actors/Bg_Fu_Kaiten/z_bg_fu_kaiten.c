#include <ultra64.h>
#include <global.h>

ActorInitData bgFuKaitenInitData = {
    0x01AE,
    1,
    0,
    0x30,
    0x01A0,
    0, 0,
    sizeof(ActorBgFuKaiten),
    (actor_func)&BgFuKaiten_Init,
    (actor_func)&BgFuKaiten_Fini,
    (actor_func)&BgFuKaiten_Main,
    (actor_func)&BgFuKaiten_Draw
};

void BgFuKaiten_Init(ActorBgFuKaiten* this, GlobalContext* ctxt) {
    UNK_TYPE pad0;
    UNK_TYPE pad1;
    BgMeshHeader* header = 0;

    Actor_SetScale(&this->bg.base, 1.0);
    BcCheck3_BgActorInit(&this->bg, 3);
    BgCheck_RelocateMeshHeader(&object_fu_kaiten_002D30, &header);
    this->bg.bgActorId = BgCheck_AddActorMesh(ctxt, &ctxt->bgCheckContext.dyna, &this->bg, header);

    this->bouceHeight = 0.0;
    this->rotationSpeed = 0;
    this->bounceSpeed = 0;
    this->bounce = 0;
}

void BgFuKaiten_Fini(ActorBgFuKaiten* this, GlobalContext* ctxt) {
    BgCheck_RemoveActorMesh(ctxt, &ctxt->bgCheckContext.dyna, this->bg.bgActorId);
}

void BgFuKaiten_UpdateRotation(ActorBgFuKaiten* this) {
    f32 f0;
    this->bg.base.postDrawParams.rotation.y += this->rotationSpeed;
    if (this->rotationSpeed > 0)
    {
        f0 = this->rotationSpeed * .002f;
        func_8019FAD8(&this->bg.base.unkEC, 8310, f0);
    }
}

void BgFuKaiten_UpdateHeight(ActorBgFuKaiten* this) {
    this->bounce += this->bounceSpeed;
    this->bg.base.unk24.pos.y = this->bg.base.initPosRot.pos.y + this->elevation + this->bouceHeight;

    this->bg.base.unk24.pos.y -= this->bouceHeight * Lib_cos(this->bounce);
}

void BgFuKaiten_Main(ActorBgFuKaiten* this, GlobalContext* ctxt) {
    BgFuKaiten_UpdateRotation(this);
    BgFuKaiten_UpdateHeight(this);
}

void BgFuKaiten_Draw(ActorBgFuKaiten* this, GlobalContext* ctxt) {
    GraphicsContext* gCtxt = ctxt->common.gCtxt;
    UNK_TYPE pad;

    func_8012C28C(gCtxt);

    gSPMatrix(gCtxt->polyOpa.append++, SysMatrix_AppendStateToPolyOpaDisp(ctxt->common.gCtxt), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gCtxt->polyOpa.append++, object_fu_kaiten_0005D0);
}
