/*
 * File: z_en_nnh.c
 * Overlay: ovl_En_Nnh
 * Description: Twisted Corpse of Deku Butler's Son
 */

#include "z_en_nnh.h"
#include "objects/object_nnh/object_nnh.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10)

#define THIS ((EnNnh*)thisx)

void EnNnh_Init(Actor* thisx, GlobalContext* globalCtx);
void EnNnh_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnNnh_Update(Actor* thisx, GlobalContext* globalCtx);
void EnNnh_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80C08828(EnNnh* this);
void func_80C0883C(EnNnh* this, GlobalContext* globalCtx);
void func_80C088A4(EnNnh* this);
void func_80C088B8(EnNnh* this, GlobalContext* globalCtx);

const ActorInit En_Nnh_InitVars = {
    ACTOR_EN_NNH,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_NNH,
    sizeof(EnNnh),
    (ActorFunc)EnNnh_Init,
    (ActorFunc)EnNnh_Destroy,
    (ActorFunc)EnNnh_Update,
    (ActorFunc)EnNnh_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_TREE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK1,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 20, 50, 0, { 0, 0, 0 } },
};

void EnNnh_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnNnh* this = THIS;

    Actor_SetScale(&this->actor, 0.01f);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    this->actor.targetMode = 1;
    this->actor.focus.pos = this->actor.world.pos;
    this->actor.focus.pos.y += 30.0f;
    func_80C08828(this);
}

void EnNnh_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnNnh* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void func_80C08828(EnNnh* this) {
    this->actionFunc = func_80C0883C;
}

void func_80C0883C(EnNnh* this, GlobalContext* globalCtx) {
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        Message_StartTextbox(globalCtx, 0x228U, &this->actor);
        func_80C088A4(this);
        return;
    }
    func_800B8614(&this->actor, globalCtx, 100.0f);
}

void func_80C088A4(EnNnh* this) {
    this->actionFunc = func_80C088B8;
}

void func_80C088B8(EnNnh* this, GlobalContext* globalCtx) {
    if (Actor_TextboxIsClosing(&this->actor, globalCtx)) {
        func_80C08828(this);
    }
}

void EnNnh_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnNnh* this = THIS;
    s32 pad;

    this->actionFunc(this, globalCtx);
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

void EnNnh_Draw(Actor* thisx, GlobalContext* globalCtx) {
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    s32 pad;

    func_8012C28C(gfxCtx);
    gSPMatrix(gfxCtx->polyOpa.p++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfxCtx->polyOpa.p++, object_nnh_DL_001510);
}
