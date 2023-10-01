/**
 * @file z_fbdemo_wipe4.c
 * Overlay: ovl_fbdemo_wipe4
 * Description:
 *
 * @note The bug in TransitionWipe4_Draw() makes this transition do nothing apart from increase its timer until it is
 * finished.
 */

#include "global.h"
#include "z_fbdemo_wipe4.h"

#define THIS ((TransitionWipe4*)thisx)

// TODO: determine how generic these macros are. Requires rest of the fbdemos decompiled.
#define TW4_SET_PARAMS (1 << 7)
#define TW4_GET_COLORTYPE(type) (((type) >> 1) & 3)
#define TW4_GET_SPEEDTYPE(type) ((type)&1)

void* TransitionWipe4_Init(void* thisx);
void TransitionWipe4_Destroy(void* thisx);
void TransitionWipe4_Update(void* thisx, s32 updateRate);
void TransitionWipe4_Draw(void* thisx, Gfx** gfxP);
void TransitionWipe4_Start(void* thisx);
void TransitionWipe4_SetType(void* thisx, s32 type);
void TransitionWipe4_SetColor(void* thisx, u32 color);
void TransitionWipe4_SetEnvColor(void* thisx, u32 color);
s32 TransitionWipe4_IsDone(void* thisx);

TransitionInit TransitionWipe4_InitVars = {
    TransitionWipe4_Init,     TransitionWipe4_Destroy,     TransitionWipe4_Update,
    TransitionWipe4_Draw,     TransitionWipe4_Start,       TransitionWipe4_SetType,
    TransitionWipe4_SetColor, TransitionWipe4_SetEnvColor, TransitionWipe4_IsDone,
};

void TransitionWipe4_Start(void* thisx) {
    TransitionWipe4* this = (TransitionWipe4*)thisx;

    this->isDone = false;

    switch (this->speedType) {
        default:
            this->baseSpeed = 0.2f;
            break;

        case 0:
            this->baseSpeed = 0.1f;
            break;

        case 1:
            this->baseSpeed = 0.05f;
            break;
    }

    switch (this->colorType) {
        default:
            this->primColor.rgba = RGBA8(160, 160, 160, 255);
            break;

        case 0:
            this->primColor.rgba = RGBA8(0, 0, 0, 255);
            break;

        case 1:
            this->primColor.rgba = RGBA8(160, 160, 160, 255);
            break;
    }
}

void* TransitionWipe4_Init(void* thisx) {
    TransitionWipe4* this = (TransitionWipe4*)thisx;

    bzero(this, sizeof(TransitionWipe4));

    return this;
}

void TransitionWipe4_Destroy(void* thisx) {
}

void TransitionWipe4_Update(void* thisx, s32 updateRate) {
    TransitionWipe4* this = (TransitionWipe4*)thisx;

    this->progress += (this->baseSpeed * 3.0f) / updateRate;
    if (this->progress >= 1.0f) {
        this->progress = 1.0f;
        this->isDone = true;
    }
}

// Use of THIS in this function is required to match
void TransitionWipe4_Draw(void* thisx, Gfx** gfxP) {
    Gfx* gfx = *gfxP;
    VisFbCopyFx* copyFx = &THIS->copyFx;

    copyFx->primColor.rgba = THIS->primColor.rgba;

    if (THIS->direction != 0) {
        copyFx->scale = THIS->progress;
        copyFx->lodProportion = 1.0f - THIS->progress;
    } else {
        copyFx->scale = 1.0f - THIS->progress;
        copyFx->lodProportion = THIS->progress;
    }

    //! @bug (Possibly) Since copyFx->mode is never set after being initialised to 0, the switch in VisFbCopyFx_Draw()
    //! does nothing, so this function call does nothing but change to the sprite microcode, then back to 3D microcode.
    VisFbCopyFx_Draw(copyFx, &gfx, SysCfb_GetZBuffer());
    *gfxP = gfx;
}

s32 TransitionWipe4_IsDone(void* thisx) {
    TransitionWipe4* this = (TransitionWipe4*)thisx;

    return this->isDone;
}

void TransitionWipe4_SetType(void* thisx, s32 type) {
    TransitionWipe4* this = (TransitionWipe4*)thisx;

    if (type & TW4_SET_PARAMS) {
        this->colorType = TW4_GET_COLORTYPE(type);
        this->speedType = TW4_GET_SPEEDTYPE(type);
    } else if (type == 1) {
        this->direction = 1;
    } else {
        this->direction = 0;
    }
}

void TransitionWipe4_SetColor(void* thisx, u32 color) {
    TransitionWipe4* this = (TransitionWipe4*)thisx;

    this->primColor.rgba = color;
}

void TransitionWipe4_SetEnvColor(void* thisx, u32 color) {
    TransitionWipe4* this = (TransitionWipe4*)thisx;

    this->envColor.rgba = color;
}
