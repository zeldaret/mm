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

void ObjHariko_NoAction(ObjHariko* this, GlobalContext* globalCtx);
void ObjHariko_BobHead(ObjHariko* this, GlobalContext* globalCtx);
void ObjHariko_SetNoAction(ObjHariko* this);
void ObjHariko_CheckForQuakes(Actor* thisx);

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

void ObjHariko_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjHariko* this = THIS;
    Actor_SetScale(&this->actor, 0.1f);
    this->headRotation.x = 0;
    this->headRotation.y = 0;
    this->headRotation.z = 0;
    this->headOffset = 0;
    this->bobbleStep = 0.0f;
    ObjHariko_SetNoAction(this);
}

void ObjHariko_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void ObjHariko_SetNoAction(ObjHariko* this) {
    this->actionFunc = ObjHariko_NoAction;
}

void ObjHariko_NoAction(ObjHariko* this, GlobalContext* globalCtx) {
}

void ObjHariko_StartBobbing(Actor* thisx) {
    ObjHariko* this = THIS;
    this->bobbleStep = 2730.0f;
    this->unk154 = 0;
    this->actionFunc = ObjHariko_BobHead;
}

void ObjHariko_BobHead(ObjHariko* this, GlobalContext* globalCtx) {
    this->headOffset = this->headOffset + 5461;
    this->headRotation.x = Math_SinS(this->headOffset) * this->bobbleStep;
    this->headRotation.y = Math_CosS(this->headOffset) * this->bobbleStep;
    Math_SmoothStepToF(&this->bobbleStep, 0, 0.5f, 18.0f, 18.0f);
    if (this->bobbleStep < 182.0f) {
        ObjHariko_SetNoAction(this);
    }
}

void ObjHariko_CheckForQuakes(Actor* thisx) {
    if (Quake_NumActiveQuakes() != 0) {
        ObjHariko_StartBobbing(thisx);
    }
}

void ObjHariko_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjHariko* this = THIS;
    this->actionFunc(this, globalCtx);
    ObjHariko_CheckForQuakes(thisx);
}

void ObjHariko_Draw(Actor* thisx, GlobalContext* globalCtx) {
    ObjHariko* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);

    Matrix_StatePush();
    Matrix_InsertXRotation_s(this->headRotation.x, 1);
    Matrix_RotateY(this->headRotation.y, 1);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, object_hariko_DL_000080);
    gSPDisplayList(POLY_OPA_DISP++, object_hariko_DL_000110);

    Matrix_StatePop();
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
