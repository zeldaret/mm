/*
 * File: z_en_nnh.c
 * Overlay: ovl_En_Nnh
 * Description: Twisted Corpse of Deku Butler's Son
 */

#include "z_en_nnh.h"
#include "objects/object_nnh/object_nnh.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10)

#define THIS ((EnNnh*)thisx)

void EnNnh_Init(Actor* thisx, PlayState* play);
void EnNnh_Destroy(Actor* thisx, PlayState* play);
void EnNnh_Update(Actor* thisx, PlayState* play);
void EnNnh_Draw(Actor* thisx, PlayState* play);

void EnNnh_SetupWaitForDialogue(EnNnh* this);
void EnNnh_WaitForDialogue(EnNnh* this, PlayState* play);
void EnNnh_SetupDialogue(EnNnh* this);
void EnNnh_Dialogue(EnNnh* this, PlayState* play);

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

void EnNnh_Init(Actor* thisx, PlayState* play) {
    EnNnh* this = THIS;

    Actor_SetScale(&this->actor, 0.01f);
    Collider_InitCylinder(play, &this->collider);
    Collider_SetCylinder(play, &this->collider, &this->actor, &sCylinderInit);
    this->actor.targetMode = 1;
    this->actor.focus.pos = this->actor.world.pos;
    this->actor.focus.pos.y += 30.0f;
    EnNnh_SetupWaitForDialogue(this);
}

void EnNnh_Destroy(Actor* thisx, PlayState* play) {
    EnNnh* this = THIS;

    Collider_DestroyCylinder(play, &this->collider);
}

void EnNnh_SetupWaitForDialogue(EnNnh* this) {
    this->actionFunc = EnNnh_WaitForDialogue;
}

void EnNnh_WaitForDialogue(EnNnh* this, PlayState* play) {
    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        Message_StartTextbox(play, 0x228, &this->actor);
        EnNnh_SetupDialogue(this);
    } else {
        func_800B8614(&this->actor, play, 100.0f);
    }
}

void EnNnh_SetupDialogue(EnNnh* this) {
    this->actionFunc = EnNnh_Dialogue;
}

void EnNnh_Dialogue(EnNnh* this, PlayState* play) {
    if (Actor_TextboxIsClosing(&this->actor, play)) {
        EnNnh_SetupWaitForDialogue(this);
    }
}

void EnNnh_Update(Actor* thisx, PlayState* play) {
    EnNnh* this = THIS;
    s32 pad;

    this->actionFunc(this, play);
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
}

void EnNnh_Draw(Actor* thisx, PlayState* play) {
    GraphicsContext* gfxCtx = play->state.gfxCtx;
    s32 pad;

    func_8012C28C(gfxCtx);
    gSPMatrix(gfxCtx->polyOpa.p++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfxCtx->polyOpa.p++, gButlerSonMainBodyDL);
}
