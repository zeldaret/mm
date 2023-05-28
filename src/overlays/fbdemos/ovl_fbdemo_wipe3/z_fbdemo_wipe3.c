/*
 * File: z_fbdemo_wipe3.c
 * Overlay: ovl_fbdemo_wipe3
 * Description:
 */

#include "global.h"
#include "z_fbdemo_wipe3.h"

#define THIS ((TransitionWipe3*)thisx)

void* TransitionWipe3_Init(void* thisx);
void TransitionWipe3_Destroy(void* thisx);
void TransitionWipe3_Update(void* thisx, s32 updateRate);
void TransitionWipe3_Draw(void* thisx, Gfx** gfxP);
void TransitionWipe3_Start(void* thisx);
void TransitionWipe3_SetType(void* thisx, s32 type);
void TransitionWipe3_SetColor(void* thisx, u32 color);
void TransitionWipe3_SetEnvColor(void* thisx, u32 color);
s32 TransitionWipe3_IsDone(void* thisx);

#include "assets/overlays/ovl_fbdemo_wipe3/ovl_fbdemo_wipe3.c"

TexturePtr sTransWipe3Textures[] = {
    fbdemo_tex_000520, fbdemo_tex_000920, fbdemo_tex_000D20, fbdemo_tex_001120,
    fbdemo_tex_001520, fbdemo_tex_000520, fbdemo_tex_000520, fbdemo_tex_000520,
};

TransitionInit TransitionWipe3_InitVars = {
    TransitionWipe3_Init,     TransitionWipe3_Destroy,     TransitionWipe3_Update,
    TransitionWipe3_Draw,     TransitionWipe3_Start,       TransitionWipe3_SetType,
    TransitionWipe3_SetColor, TransitionWipe3_SetEnvColor, TransitionWipe3_IsDone,
};

void TransitionWipe3_Start(void* thisx) {
    TransitionWipe3* this = THIS;

    this->isDone = false;
    this->curTexture = sTransWipe3Textures[this->texIndex & 7];
    if (this->unk_16 == 0) {
        this->wipeSpeed = 20;
    } else {
        this->wipeSpeed = 10;
    }
    if (this->unk_15 == 0) {
        this->color.rgba = RGBA8(0, 0, 0, 255);
    } else if (this->unk_15 == 1) {
        this->color.rgba = RGBA8(255, 255, 255, 255);
    } else {
        this->color.rgba = RGBA8(160, 160, 160, 255);
    }
    if (this->unk_14) {
        this->scrollY = 0;
    } else {
        this->scrollY = 500;
        if (this->texIndex == 2) {
            func_8019F128(NA_SE_OC_SECRET_WARP_OUT);
        }
    }
    guPerspective(&this->projection, &this->normal, 60.0f, 1.3333334f, 10.0f, 12800.0f, 1.0f);
    guLookAt(&this->lookAt, 0.0f, 0.0f, 400.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
}

void* TransitionWipe3_Init(void* thisx) {
    TransitionWipe3* this = THIS;

    bzero(this, sizeof(TransitionWipe3));
    return this;
}

void TransitionWipe3_Destroy(void* thisx) {
}

void TransitionWipe3_UpdateScrollY(void* thisx, f32 scroll) {
    TransitionWipe3* this = THIS;

    this->scrollY = (s32)(500.0f * scroll);
}

void TransitionWipe3_Update(void* thisx, s32 updateRate) {
    TransitionWipe3* this = THIS;

    if (this->unk_14) {
        if ((this->scrollY == 0) && (this->texIndex == 2)) {
            func_8019F128(NA_SE_OC_SECRET_WARP_IN);
        }
        this->scrollY += (this->wipeSpeed * 3) / updateRate;
        if (this->scrollY >= 500) {
            this->scrollY = 500;
            this->isDone = true;
        }
    } else {
        this->scrollY -= (this->wipeSpeed * 3) / updateRate;
        if (this->scrollY <= 0) {
            this->scrollY = 0;
            this->isDone = true;
        }
    }
}

void TransitionWipe3_Draw(void* thisx, Gfx** gfxP) {
    Gfx* dl = *gfxP;
    Mtx* modelView = &THIS->modelView[THIS->frame];
    f32 scale = 14.8f;
    Gfx* texScroll;

    THIS->frame ^= 1;
    gDPPipeSync(dl++);
    texScroll = Gfx_BranchTexScroll(&dl, THIS->scrollX, THIS->scrollY, 16, 64);
    gSPSegment(dl++, 0x09, texScroll);
    gSPSegment(dl++, 0x08, THIS->curTexture);
    gDPSetColor(dl++, G_SETPRIMCOLOR, THIS->color.rgba);
    gDPSetColor(dl++, G_SETENVCOLOR, THIS->color.rgba);
    gSPMatrix(dl++, &THIS->projection, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPPerspNormalize(dl++, THIS->normal);
    gSPMatrix(dl++, &THIS->lookAt, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);

    if (scale != 1.0f) {
        guScale(modelView, scale, scale, 1.0f);
        gSPMatrix(dl++, modelView, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    }
    gSPDisplayList(dl++, sTransWipe3DL);
    gDPPipeSync(dl++);
    *gfxP = dl;
}

s32 TransitionWipe3_IsDone(void* thisx) {
    TransitionWipe3* this = THIS;

    return this->isDone;
}

void TransitionWipe3_SetType(void* thisx, s32 type) {
    TransitionWipe3* this = THIS;

    if (type & 0x80) {
        this->unk_16 = (s8)(type & 1);
        this->texIndex = (s8)((type >> 1) & 7);
        this->unk_15 = (s8)((type >> 4) & 3);
        return;
    }
    if (type == 1) {
        this->unk_14 = true;
        return;
    }
    this->unk_14 = false;
}

void TransitionWipe3_SetColor(void* thisx, u32 color) {
    TransitionWipe3* this = THIS;

    this->color.rgba = color;
}

void TransitionWipe3_SetEnvColor(void* thisx, u32 color) {
    TransitionWipe3* this = THIS;

    this->envColor.rgba = color;
}
