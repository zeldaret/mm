#include "global.h"

#define THIS ((TransitionFade*)thisx)

static Gfx sFadeSetupDL[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN |
                          G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH),
    gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_BAYER | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_1PRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_CLD_SURF | G_RM_CLD_SURF2),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE),
    gsSPEndDisplayList(),
};

TransitionInit TransitionFade_InitVars = {
    TransitionFade_Init,   TransitionFade_Destroy, TransitionFade_Update,   TransitionFade_Draw,
    TransitionFade_Start,  TransitionFade_SetType, TransitionFade_SetColor, NULL,
    TransitionFade_IsDone,
};

void TransitionFade_Start(void* thisx) {
    TransitionFade* this = THIS;

    switch (this->type) {
        case 0:
            break;

        case 1:
            this->timer = 0;
            this->color.a = (this->direction != 0) ? 255 : 0;
            break;

        case 2:
            this->color.a = 0;
            break;
    }
    this->isDone = false;
}

void* TransitionFade_Init(void* thisx) {
    TransitionFade* this = THIS;

    bzero(this, sizeof(TransitionFade));
    return this;
}

void TransitionFade_Destroy(void* thisx) {
}

void TransitionFade_Update(void* thisx, s32 updateRate) {
    s32 alpha;
    s16 newAlpha;
    TransitionFade* this = THIS;

    switch (this->type) {
        case 0:
            break;

        case 1:
            //! FAKE:
            THIS->timer += updateRate;

            if (this->timer >= gSaveContext.transFadeDuration) {
                this->timer = gSaveContext.transFadeDuration;
                this->isDone = true;
            }

            alpha = (255.0f * this->timer) / ((void)0, gSaveContext.transFadeDuration);
            this->color.a = (this->direction != 0) ? 255 - alpha : alpha;
            break;

        case 2:
            newAlpha = this->color.a;
            if (iREG(50) != 0) {
                if (iREG(50) < 0) {
                    if (Math_StepToS(&newAlpha, 255, 255)) {
                        iREG(50) = 150;
                    }
                } else {
                    Math_StepToS(&iREG(50), 20, 60);
                    if (Math_StepToS(&newAlpha, 0, iREG(50))) {
                        iREG(50) = 0;
                        this->isDone = true;
                    }
                }
            }
            this->color.a = newAlpha;
            break;
    }
}

void TransitionFade_Draw(void* thisx, Gfx** gfxP) {
    TransitionFade* this = THIS;
    Gfx* gfx;
    Color_RGBA8_u32* color = &this->color;

    if (color->a != 0) {
        gfx = *gfxP;
        gSPDisplayList(gfx++, sFadeSetupDL);
        gDPSetPrimColor(gfx++, 0, 0, color->r, color->g, color->b, color->a);
        gSPDisplayList(gfx++, D_0E000000.fillRect);
        *gfxP = gfx;
    }
}

s32 TransitionFade_IsDone(void* thisx) {
    TransitionFade* this = THIS;

    return this->isDone;
}

void TransitionFade_SetColor(void* thisx, u32 color) {
    TransitionFade* this = THIS;

    this->color.rgba = color;
}

void TransitionFade_SetType(void* thisx, s32 type) {
    TransitionFade* this = THIS;

    if (type == TRANS_FADE_TYPE_IN) {
        this->type = 1;
        this->direction = 1;
    } else if (type == TRANS_FADE_TYPE_OUT) {
        this->type = 1;
        this->direction = 0;
    } else if (type == TRANS_FADE_TYPE_FLASH) {
        this->type = 2;
    } else {
        this->type = 0;
    }
}
