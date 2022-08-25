/*
 * File: z_fbdemo_triforce.c
 * Overlay: ovl_fbdemo_triforce
 * Description:
 */

#include "z_fbdemo_triforce.h"
#include "assets/objects/object_fbdemo_triforce/ovl_fbdemo_triforce.c"

void* TransitionTriforce_Init(void* thisx);
void TransitionTriforce_Destroy(void* thisx);
void TransitionTriforce_Update(void* thisx, s32 updateRate);
void TransitionTriforce_Draw(void* thisx, Gfx** gfxP);
void TransitionTriforce_Start(void* thisx);
void TransitionTriforce_SetType(void* thisx, s32 type);
void TransitionTriforce_SetColor(void* thisx, u32 color);
s32 TransitionTriforce_IsDone(void* thisx);

const TransitionInit TransitionTriforce_InitVars = {
    TransitionTriforce_Init,   TransitionTriforce_Destroy, TransitionTriforce_Update,   TransitionTriforce_Draw,
    TransitionTriforce_Start,  TransitionTriforce_SetType, TransitionTriforce_SetColor, NULL,
    TransitionTriforce_IsDone,
};

void TransitionTriforce_Start(void* thisx) {
    TransitionTriforce* this = (TransitionTriforce*)thisx;

    switch (this->state) {
        case 1:
        case 2:
            this->transPos = 1.0f;
            return;
    }
    this->transPos = 0.03f;
}

void* TransitionTriforce_Init(void* thisx) {
    TransitionTriforce* this = (TransitionTriforce*)thisx;

    bzero(this, sizeof(*this));
    guOrtho(&this->projection, -160.0f, 160.0f, -120.0f, 120.0f, -1000.0f, 1000.0f, 1.0f);
    this->transPos = 1.0f;
    this->state = 2;
    this->step = 0.015f;
    this->fadeDirection = 1;
    return this;
}

void TransitionTriforce_Destroy(void* thisx) {
}

void TransitionTriforce_Update(void* thisx, s32 updateRate) {
    TransitionTriforce* this = (TransitionTriforce*)thisx;
    f32 temp_f0;
    s32 i;

    for (i = updateRate; i > 0; i--) {
        if (this->state == 1) {
            this->transPos = CLAMP_MIN(this->transPos * (1.0f - this->step), 0.03f);
        } else if (this->state == 2) {
            this->transPos = CLAMP_MIN(this->transPos - this->step, 0.03f);
        } else if (this->state == 3) {
            this->transPos = CLAMP_MAX(this->transPos / (1.0f - this->step), 1.0f);
        } else if (this->state == 4) {
            this->transPos = CLAMP_MAX(this->transPos + this->step, 1.0f);
        }
    }
}

void TransitionTriforce_SetColor(void* thisx, u32 color) {
    TransitionTriforce* this = (TransitionTriforce*)thisx;

    this->color.rgba = color;
}

void TransitionTriforce_SetType(void* thisx, s32 type) {
    TransitionTriforce* this = (TransitionTriforce*)thisx;

    this->fadeDirection = type;
}

void func_80AC5280(void* thisx, s32 state) {
    TransitionTriforce* this = (TransitionTriforce*)thisx;

    this->state = state;
}

void TransitionTriforce_Draw(void* thisx, Gfx** gfxP) {
    Gfx* gfx = *gfxP;
    Mtx* modelView;
    s32 pad[2];
    TransitionTriforce* this = (TransitionTriforce*)thisx;
    f32 rotation = this->transPos * 360.0f;

    modelView = this->modelView[this->frame];
    this->frame ^= 1;
    guScale(&modelView[0], this->transPos * 0.625f, this->transPos * 0.625f, 1.0f);
    guRotate(&modelView[1], rotation, 0.0f, 0.0f, 1.0f);
    guTranslate(&modelView[2], 0.0f, 0.0f, 0.0f);
    gDPPipeSync(gfx++);
    gSPDisplayList(gfx++, &sTriforceWipeDL);
    gDPSetColor(gfx++, G_SETPRIMCOLOR, this->color.rgba);
    gDPSetCombineMode(gfx++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
    gSPMatrix(gfx++, &this->projection, G_MTX_LOAD | G_MTX_PROJECTION);
    gSPMatrix(gfx++, &modelView[0], G_MTX_LOAD);
    gSPMatrix(gfx++, &modelView[1], G_MTX_NOPUSH | G_MTX_MODELVIEW);
    gSPMatrix(gfx++, &modelView[2], G_MTX_NOPUSH | G_MTX_MODELVIEW);
    gSPVertex(gfx++, &sTriforceWipeVtx, 10, 0);
    if (!TransitionTriforce_IsDone(this)) {
        switch (this->fadeDirection) {
            case 1:
                gSP2Triangles(gfx++, 0, 4, 5, 0, 4, 1, 3, 0);
                gSP1Triangle(gfx++, 5, 3, 2, 0);
                break;

            case 2:
                gSP2Triangles(gfx++, 3, 4, 5, 0, 0, 2, 6, 0);
                gSP2Triangles(gfx++, 0, 6, 7, 0, 1, 0, 7, 0);
                gSP2Triangles(gfx++, 1, 7, 8, 0, 1, 8, 9, 0);
                gSP2Triangles(gfx++, 1, 9, 2, 0, 2, 9, 6, 0);
                break;
        }

    } else {
        switch (this->fadeDirection) {
            case 1:
                break;

            case 2:
                gSP1Quadrangle(gfx++, 6, 7, 8, 9, 0);
                break;
        }
    }
    gDPPipeSync(gfx++);
    *gfxP = gfx;
}

s32 TransitionTriforce_IsDone(void* thisx) {
    TransitionTriforce* this = (TransitionTriforce*)thisx;

    s32 ret = 0;

    if (this->state == 1 || this->state == 2) {
        return this->transPos <= 0.03f;

    } else if (this->state == 3 || this->state == 4) {
        return this->transPos >= 1.0f;
    }
    return ret;
}
