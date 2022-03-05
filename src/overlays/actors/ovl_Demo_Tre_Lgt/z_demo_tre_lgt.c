/*
 * File: z_demo_tre_lgt.c
 * Overlay: ovl_Demo_Tre_Lgt
 * Description: Light Radiating From Treasure Chest
 */

#include "z_demo_tre_lgt.h"
#include "../ovl_En_Box/z_en_box.h"
#include "objects/object_box/object_box.h"

#define FLAGS 0x00000010

#define THIS ((DemoTreLgt*)thisx)

void DemoTreLgt_Init(Actor* thisx, GlobalContext* globalCtx);
void DemoTreLgt_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DemoTreLgt_Update(Actor* thisx, GlobalContext* globalCtx);
void DemoTreLgt_Draw(Actor* thisx, GlobalContext* globalCtx);

void DemoTreLgt_SetupWait(DemoTreLgt* this);

void DemoTreLgt_Wait(DemoTreLgt* this, GlobalContext* globalCtx);
void DemoTreLgt_SetupAnimate(DemoTreLgt* this, GlobalContext* globalCtx, f32 frame);
void DemoTreLgt_Animate(DemoTreLgt* this, GlobalContext* globalCtx);

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
} DemoTreLgtInfo;

static DemoTreLgtInfo D_808E1490[2] = {
    { 1.0f, 136.0f, 190.0f, 40.0f },
    { 1.0f, 136.0f, 220.0f, 50.0f },
};

const ActorInit Demo_Tre_Lgt_InitVars = {
    ACTOR_DEMO_TRE_LGT,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_BOX,
    sizeof(DemoTreLgt),
    (ActorFunc)DemoTreLgt_Init,
    (ActorFunc)DemoTreLgt_Destroy,
    (ActorFunc)DemoTreLgt_Update,
    (ActorFunc)DemoTreLgt_Draw,
};

static TransformUpdateIndex* sBoxLightAnimations[] = {
    &gBoxLight0CurveAnim,
    &gBoxLight1CurveAnim,
};

static DemoTreLgtActionFunc sActionFuncs[] = {
    DemoTreLgt_Wait,
    DemoTreLgt_Animate,
};

void DemoTreLgt_Init(Actor* thisx, GlobalContext* globalCtx) {
    DemoTreLgt* this = (DemoTreLgt*)thisx;
    SkelCurve_Init(globalCtx, &this->skelCurve, &gBoxLightCurveSkel, sBoxLightAnimations[0]);
    this->colorAlpha1 = 255;
    this->colorAlpha2 = 255;
    this->status = 0;
    if (gSaveContext.playerForm == 0) {
        this->animationType = 0;
    } else {
        this->animationType = 1;
    }
    DemoTreLgt_SetupWait(this);
}

void DemoTreLgt_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    DemoTreLgt* this = (DemoTreLgt*)thisx;

    SkelCurve_Destroy(globalCtx, &this->skelCurve);
}

void DemoTreLgt_SetupWait(DemoTreLgt* this) {
    this->action = DEMO_TRE_LGT_ACTION_WAIT;
}

void DemoTreLgt_Wait(DemoTreLgt* this, GlobalContext* globalCtx) {
    EnBox* chest = (EnBox*)this->actor.parent;

    if (chest != NULL) {
        if (Animation_OnFrame(&chest->skelAnime, 10.0f) != 0) {
            DemoTreLgt_SetupAnimate(this, globalCtx, chest->skelAnime.curFrame);
        }
    }
}

void DemoTreLgt_SetupAnimate(DemoTreLgt* this, GlobalContext* globalCtx, f32 frame) {
    this->action = DEMO_TRE_LGT_ACTION_ANIMATE;
    SkelCurve_SetAnim(&this->skelCurve, sBoxLightAnimations[this->animationType], 1.0f,
                      D_808E1490[this->animationType].unk4 + D_808E1490[this->animationType].unk8, frame, 1.0f);
    SkelCurve_Update(globalCtx, &this->skelCurve);
}

void DemoTreLgt_Animate(DemoTreLgt* this, GlobalContext* globalCtx) {
    f32 curFrame = this->skelCurve.animCurFrame;

    if (curFrame < D_808E1490[this->animationType].unk4) {
        this->colorAlpha1 = 255;
    } else if (curFrame <= (D_808E1490[this->animationType].unk4 + D_808E1490[this->animationType].unk8)) {
        this->colorAlpha1 = ((D_808E1490[this->animationType].unk4 - curFrame) / D_808E1490[this->animationType].unk8) * 255 + 255;
    } else {
        this->colorAlpha1 = 0;
    }

    if (curFrame < D_808E1490[this->animationType].unkC) {
        this->colorAlpha2 = 255;
    } else if (curFrame < (D_808E1490[this->animationType].unkC + 10.0f)) {
        this->colorAlpha2 = ((D_808E1490[this->animationType].unkC - curFrame) / 10.0f) * 255 + 255;
    } else {
        this->colorAlpha2 = 0;
    }
    if (curFrame > 30.0f) {
        if (!(this->status & 1)) {
            this->status |= 1;
            Audio_PlaySfxAtPos(&this->actor.projectedPos, NA_SE_EV_TRE_BOX_FLASH);
        }
    }
    if (SkelCurve_Update(globalCtx, &this->skelCurve) != 0) {
        Actor_MarkForDeath(&this->actor);
    }
}

void DemoTreLgt_Update(Actor* thisx, GlobalContext* globalCtx) {
    DemoTreLgt* this = (DemoTreLgt*)thisx;

    sActionFuncs[this->action](this, globalCtx);
}

s32 DemoTreLgt_OverrideLimbDraw(GlobalContext* globalCtx, SkelAnimeCurve* skelCuve, s32 limbIndex, Actor* thisx) {
    s32 pad;
    DemoTreLgt* this = (DemoTreLgt*)thisx;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    gSPSegment(POLY_XLU_DISP++, 0x08,
               Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, (globalCtx->state.frames * 2) % 256, 0, 64, 32, 1,
                                (globalCtx->state.frames * -2) % 256, 0, 64, 32));

    if (limbIndex == 1) {
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x80, 255, 255, 180, this->colorAlpha1);
    } else if (limbIndex == 13 || limbIndex == 7 || limbIndex == 4 || limbIndex == 10) {
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x80, 255, 255, 180, this->colorAlpha2);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);

    return true;
}

void DemoTreLgt_Draw(Actor* thisx, GlobalContext* globalCtx) {
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    DemoTreLgt* this = (DemoTreLgt*)thisx;

    OPEN_DISPS(gfxCtx);
    if (this->action == DEMO_TRE_LGT_ACTION_ANIMATE) {
        func_8012C2DC(gfxCtx);
        gDPSetEnvColor(POLY_XLU_DISP++, 200, 255, 0, 0);
        SkelCurve_Draw(&this->actor, globalCtx, &this->skelCurve, DemoTreLgt_OverrideLimbDraw, NULL, 1, &this->actor);
    }
    CLOSE_DISPS(gfxCtx);
}
