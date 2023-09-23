/*
 * File: z_eff_ss_d_fire.c
 * Overlay: ovl_Effect_Ss_D_Fire
 * Description: Dodongo Fire
 */

#include "z_eff_ss_d_fire.h"
#include "objects/object_dodongo/object_dodongo.h"

#define rScale regs[0]
#define rTexIndex regs[1]
#define rAlpha regs[5]
#define rAlphaStep regs[6]
#define rFadeDelay regs[7]
#define rScaleStep regs[8]
#define rObjectIndex regs[9]

#define PARAMS ((EffectSsDFireInitParams*)initParamsx)

u32 EffectSsDFire_Init(PlayState* play, u32 index, EffectSs* this, void* initParamsx);
void EffectSsDFire_Update(PlayState* play, u32 index, EffectSs* this);
void EffectSsDFire_Draw(PlayState* play, u32 index, EffectSs* this);

EffectSsInit Effect_Ss_D_Fire_InitVars = {
    EFFECT_SS_D_FIRE,
    EffectSsDFire_Init,
};

static TexturePtr sFireTextures[] = { gDodongoFire0Tex, gDodongoFire1Tex, gDodongoFire2Tex, gDodongoFire3Tex };

s32 EffectSsDFire_CheckForObject(EffectSs* this, PlayState* play) {
    if (((this->rObjectIndex = Object_GetIndex(&play->objectCtx, OBJECT_DODONGO)) < 0) ||
        !Object_IsLoaded(&play->objectCtx, this->rObjectIndex)) {
        this->life = -1;
        this->draw = NULL;
        return false;
    }
    return true;
}

u32 EffectSsDFire_Init(PlayState* play, u32 index, EffectSs* this, void* initParamsx) {
    EffectSsDFireInitParams* initParams = PARAMS;

    if (EffectSsDFire_CheckForObject(this, play)) {
        Math_Vec3f_Copy(&this->pos, &initParams->pos);
        Math_Vec3f_Copy(&this->velocity, &initParams->velocity);
        Math_Vec3f_Copy(&this->accel, &initParams->accel);
        this->gfx = gDodongoFireDL;
        this->life = initParams->life;
        this->rScale = initParams->scale;
        this->rScaleStep = initParams->scaleStep;
        this->draw = EffectSsDFire_Draw;
        this->update = EffectSsDFire_Update;
        this->rTexIndex = (play->state.frames & 3) ^ 3; // The xor reverses order, i.e 3 -> 2 -> 1 -> 0 -> 3
        this->rAlpha = initParams->alpha;
        this->rFadeDelay = this->life - initParams->fadeDelay;
        this->rAlphaStep = initParams->alphaStep;

        return 1;
    }

    return 0;
}

void EffectSsDFire_Draw(PlayState* play, u32 index, EffectSs* this) {
    GraphicsContext* gfxCtx = play->state.gfxCtx;
    s32 pad;
    void* object;
    f32 scale;

    if (EffectSsDFire_CheckForObject(this, play)) {
        object = play->objectCtx.status[this->rObjectIndex].segment;

        OPEN_DISPS(gfxCtx);

        gSegments[6] = VIRTUAL_TO_PHYSICAL(object);
        gSPSegment(POLY_XLU_DISP++, 0x06, object);

        scale = this->rScale / 100.0f;

        Matrix_Translate(this->pos.x, this->pos.y, this->pos.z, MTXMODE_NEW);
        Matrix_Scale(scale, scale, scale, MTXMODE_APPLY);
        Matrix_Mult(&play->billboardMtxF, MTXMODE_APPLY);

        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        Gfx_SetupDL60_XluNoCD(gfxCtx);
        gDPSetEnvColor(POLY_XLU_DISP++, 255, 0, 0, 0);
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 50, this->rAlpha);

        {
            TexturePtr* tex = sFireTextures[this->rTexIndex];

            gSPSegment(POLY_XLU_DISP++, 0x08, Lib_SegmentedToVirtual(tex));
        }

        gSPDisplayList(POLY_XLU_DISP++, this->gfx);

        CLOSE_DISPS(gfxCtx);
    }
}

void EffectSsDFire_Update(PlayState* play, u32 index, EffectSs* this) {
    this->rTexIndex++;
    this->rTexIndex &= 3;
    this->rScale += this->rScaleStep;
    if (this->life < this->rFadeDelay) {
        this->rAlpha -= this->rAlphaStep;
        if (this->rAlpha < 0) {
            this->rAlpha = 0;
            this->life = -1;
        }
    }

    EffectSsDFire_CheckForObject(this, play);
}
