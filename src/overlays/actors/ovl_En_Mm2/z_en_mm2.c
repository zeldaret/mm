/*
 * File: z_en_mm2.c
 * Overlay: ovl_En_Mm2
 * Description: Postman's Letter to Himself
 */

#include "z_en_mm2.h"

#define FLAGS 0x00000010

#define THIS ((EnMm2*)thisx)

void EnMm2_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMm2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMm2_Update(Actor* thisx, GlobalContext* globalCtx);
void EnMm2_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnMm2_Reading(EnMm2* this, GlobalContext* globalCtx);
void EnMm2_WaitForRead(EnMm2* this, GlobalContext* globalCtx);

const ActorInit En_Mm2_InitVars = {
    ACTOR_EN_MM2,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnMm2),
    (ActorFunc)EnMm2_Init,
    (ActorFunc)EnMm2_Destroy,
    (ActorFunc)EnMm2_Update,
    (ActorFunc)EnMm2_Draw,
};

#include "overlays/ovl_En_Mm2/ovl_En_Mm2.c"

void EnMm2_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnMm2* this = THIS;

    Actor_SetScale(&this->actor, 0.015f);
    this->actionFunc = EnMm2_WaitForRead;
}

void EnMm2_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

// Action function whilst Link is reading the letter.
void EnMm2_Reading(EnMm2* this, GlobalContext* globalCtx) {
    u8 talkState = func_80152498(&globalCtx->msgCtx);

    if (talkState != 2) {
        if (talkState == 5 && func_80147624(globalCtx)) {
            func_801477B4(globalCtx);
            this->actionFunc = EnMm2_WaitForRead;
        }
    } else {
        this->actionFunc = EnMm2_WaitForRead;
    }
}

// Action function that awaits Link to read the letter, changing the A button to "Check" when he is within range to do
// so (and facing the letter).
void EnMm2_WaitForRead(EnMm2* this, GlobalContext* globalCtx) {
    if (func_800B84D0(&this->actor, globalCtx)) {
        func_801518B0(globalCtx, 0x277B, &this->actor);
        this->actionFunc = EnMm2_Reading;
    } else if ((this->actor.xzDistToPlayer < 60.0f) && (Actor_IsLinkFacingActor(&this->actor, 0x3000, globalCtx))) {
        func_800B8614(&this->actor, globalCtx, 110.0f);
    }
}

void EnMm2_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnMm2* this = THIS;

    this->actionFunc(this, globalCtx);
}

/*void EnMm2_Draw(Actor* thisx, GlobalContext* globalCtx) {
    GraphicsContext* gfxCtx;
    EnMm2* this = THIS;

    gfxCtx = globalCtx->state.gfxCtx;
    func_8012C28C(globalCtx->state.gfxCtx);
    gSPMatrix(gfxCtx->polyOpa.p++, Matrix_NewMtx(globalCtx->state.gfxCtx), (0x00 | 0x02) | 0x00);
    gSPDisplayList(gfxCtx->polyOpa.p++, sEnMm2DL);
}*/

void EnMm2_Draw(Actor* thisx, GlobalContext* globalCtx) {
    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), (0x00 | 0x02) | 0x00);
    gSPDisplayList(POLY_OPA_DISP++, sEnMm2DL);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
