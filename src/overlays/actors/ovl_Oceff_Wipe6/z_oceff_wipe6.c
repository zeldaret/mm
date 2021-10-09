#include "z_oceff_wipe6.h"

#define FLAGS 0x02000010

#define THIS ((OceffWipe6*)thisx)

void OceffWipe6_Init(Actor* thisx, GlobalContext* globalCtx);
void OceffWipe6_Destroy(Actor* thisx, GlobalContext* globalCtx);
void OceffWipe6_Update(Actor* thisx, GlobalContext* globalCtx);
void OceffWipe6_Draw(Actor* thisx, GlobalContext* globalCtx);

const ActorInit Oceff_Wipe6_InitVars = {
    ACTOR_OCEFF_WIPE6,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(OceffWipe6),
    (ActorFunc)OceffWipe6_Init,
    (ActorFunc)OceffWipe6_Destroy,
    (ActorFunc)OceffWipe6_Update,
    (ActorFunc)OceffWipe6_Draw,
};

/* Parameters for gOceffScroll */
UNK_TYPE1 gOceff6ScrollParams[] = {
    0xFF, 0x01, 0x20, 0x20, 0xFF, 0x04, 0x20, 0x20
};

/* Animated Material Properties for Scrolling Texture */
AnimatedMaterial gOceff6Scroll = {
    0xFF, 0x0001, gOceff6ScrollParams
};

#include "overlays/ovl_Oceff_Wipe6/ovl_Oceff_Wipe6.c"

void OceffWipe6_Init(Actor* thisx, GlobalContext* globalCtx) {
    OceffWipe6* this = THIS;

    Actor_SetScale(&this->actor, 1.0f);
    this->counter = 0;
    this->actor.world.pos = ACTIVE_CAM->eye;
}

void OceffWipe6_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    func_80115D5C(globalCtx);
    globalCtx->msgCtx.pad12080[0x30] = 0;
}

void OceffWipe6_Update(Actor* thisx, GlobalContext* globalCtx) {
    OceffWipe6* this = THIS;

    this->actor.world.pos = ACTIVE_CAM->eye;
    if (this->counter < 100) {
        this->counter++;
    } else {
        Actor_MarkForDeath(&this->actor);
    }
}

void OceffWipe6_Draw(Actor* thisx, GlobalContext* globalCtx) {
    OceffWipe6* this = THIS;
    f32 z;
    u8 alpha;
    s32 i;
    s32 counter;
    Vec3f eye;
    s32 pad;
    Vec3f vec;
    s32 pad2;

    eye = ACTIVE_CAM->eye;
    Camera_GetSkyboxOffset(&vec, ACTIVE_CAM);

    if (this->counter < 32) {
        counter = this->counter;
        z = Math_SinS(counter * 0x200) * 1220.0f;
    } else {
        z = 1220.0f;
    }

    if (this->counter >= 80) {
        alpha = 12 * (100 - this->counter);
    } else {
        alpha = 0xFF;
    }

    for(i = 1; i < 22; i += 2) {
        gOceff6Vtx[i].v.cn[3] = alpha;
    }

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C2DC(globalCtx->state.gfxCtx);
    SysMatrix_InsertTranslation(eye.x + vec.x, eye.y + vec.y, eye.z + vec.z, MTXMODE_NEW);
    Matrix_Scale(0.1f, 0.1f, 0.1f, MTXMODE_APPLY);
    SysMatrix_NormalizeXYZ(&globalCtx->mf_187FC);
    SysMatrix_InsertXRotation_s(0x708, MTXMODE_APPLY);
    SysMatrix_InsertTranslation(0.0f, 0.0f, -z, MTXMODE_APPLY);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    AnimatedMat_Draw(globalCtx, &gOceff6Scroll);
    gSPDisplayList(POLY_XLU_DISP++, gOceff6DL);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
