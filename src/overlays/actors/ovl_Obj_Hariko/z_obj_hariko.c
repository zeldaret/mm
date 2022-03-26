/*
 * File: z_obj_hariko.c
 * Overlay: ovl_Obj_Hariko
 * Description: Little Cow Statue Head
 */

#include "z_obj_hariko.h"
#include "assets/objects/object_hariko/object_hariko.h"

#define FLAGS (ACTOR_FLAG_20 | ACTOR_FLAG_2000000)

#define THIS ((ObjHariko*)thisx)

void ObjHariko_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjHariko_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjHariko_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjHariko_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80B66A90(ObjHariko* this, GlobalContext* globalCtx);
void func_80B66AC4(ObjHariko* this, GlobalContext* globalCtx);
void func_80B66A7C(ObjHariko* this);
void func_80B66B78(Actor *thisx);

const ActorInit Obj_Hariko_InitVars = {
    ACTOR_OBJ_HARIKO,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_HARIKO,
    sizeof(ObjHariko),
    (ActorFunc)ObjHariko_Init,
    (ActorFunc)ObjHariko_Destroy,
    (ActorFunc)ObjHariko_Update,
    (ActorFunc)ObjHariko_Draw,
};

void ObjHariko_Init(Actor* thisx, GlobalContext* globalCtx){
    ObjHariko *this = THIS;
    Actor_SetScale(&this->actor, 0.1f);
    this->unk14C = 0;
    this->unk14E = 0;
    this->unk150 = 0;
    this->unk152 = 0;
    this->unk148 = 0.0f;
    func_80B66A7C(this);
}

void ObjHariko_Destroy(Actor* thisx, GlobalContext* globalCtx){ }

void func_80B66A7C(ObjHariko* this) {
    this->actionFunc = func_80B66A90;
}

void func_80B66A90 (ObjHariko* this, GlobalContext* globalCtx) {

}

void func_80B66AA0(Actor* thisx) {
    ObjHariko *this = THIS;
    this->unk148 = 2730.0f;
    this->unk154 = 0;
    this->actionFunc = func_80B66AC4;
}

void func_80B66AC4(ObjHariko* this, GlobalContext* globalCtx) {
    this->unk152 = (s16) this->unk152 + 0x1555;
    this->unk14C = (s16) (Math_SinS(this->unk152) * this->unk148);
    this->unk14E = (s16) (Math_CosS(this->unk152) * this->unk148);
    Math_SmoothStepToF(&this->unk148, 0, 0.5f, 18.0f, 18.0f);
    if (this->unk148 < 182.0f) {
        func_80B66A7C(this);
    }
}

void func_80B66B78(Actor *thisx) {
    if (Quake_NumActiveQuakes() != 0) {
        func_80B66AA0(thisx);
    }
}

void ObjHariko_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjHariko *this = THIS;
    this->actionFunc(this, globalCtx);
    func_80B66B78(thisx);
}

void ObjHariko_Draw(Actor* thisx, GlobalContext* globalCtx) {
    ObjHariko *this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);

    Matrix_StatePush();
    Matrix_InsertXRotation_s(this->unk14C, 1);
    Matrix_RotateY(this->unk14E, 1);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, object_hariko_DL_000080);
    gSPDisplayList(POLY_OPA_DISP++, object_hariko_DL_000110);

    Matrix_StatePop();
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
