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

u32 EffectSsDFire_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx);
void EffectSsDFire_Update(GlobalContext* globalCtx, u32 index, EffectSs* this);
void EffectSsDFire_Draw(GlobalContext* globalCtx, u32 index, EffectSs* this);

const EffectSsInit Effect_Ss_D_Fire_InitVars = {
    EFFECT_SS_D_FIRE,
    EffectSsDFire_Init,
};

static TexturePtr sFireTextures[] = { gDodongoFire0Tex, gDodongoFire1Tex, gDodongoFire2Tex, gDodongoFire3Tex };

s32 EffectSsDFire_CheckForObject(EffectSs* this, GlobalContext* globalCtx) {
    if (((this->rObjectIndex = Object_GetIndex(&globalCtx->objectCtx, OBJECT_DODONGO)) < 0) ||
        !Object_IsLoaded(&globalCtx->objectCtx, this->rObjectIndex)) {
        this->life = -1;
        this->draw = NULL;
        return false;
    }
    return true;
}

u32 EffectSsDFire_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx) {
    EffectSsDFireInitParams* initParams = PARAMS;

    if (EffectSsDFire_CheckForObject(this, globalCtx)) {
        Math_Vec3f_Copy(&this->pos, &initParams->pos);
        Math_Vec3f_Copy(&this->velocity, &initParams->velocity);
        Math_Vec3f_Copy(&this->accel, &initParams->accel);
        this->gfx = gDodongoFireDL;
        this->life = initParams->life;
        this->rScale = initParams->scale;
        this->rScaleStep = initParams->scaleStep;
        this->draw = EffectSsDFire_Draw;
        this->update = EffectSsDFire_Update;
        this->rTexIndex = (globalCtx->state.frames % 4) ^ 3;
        this->rAlpha = initParams->alpha;
        this->rFadeDelay = this->life - initParams->fadeDelay;
        this->rAlphaStep = initParams->alphaStep;

        return 1;
    }

    return 0;
}

void EffectSsDFire_Draw(GlobalContext* globalCtx, u32 index, EffectSs* this) {
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    s32 pad;
    void* object;
    f32 scale;

    if (EffectSsDFire_CheckForObject(this, globalCtx)) {
        object = globalCtx->objectCtx.status[this->rObjectIndex].segment;

        OPEN_DISPS(gfxCtx);

        gSegments[6] = PHYSICAL_TO_VIRTUAL2(object);
        gSPSegment(POLY_XLU_DISP++, 0x06, object);

        scale = this->rScale / 100.0f;

        Matrix_InsertTranslation(this->pos.x, this->pos.y, this->pos.z, 0);
        Matrix_Scale(scale, scale, scale, 1);
        Matrix_InsertMatrix(&globalCtx->billboardMtxF, 1);

        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        func_8012C974(gfxCtx);
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

void EffectSsDFire_Update(GlobalContext* globalCtx, u32 index, EffectSs* this) {
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

    EffectSsDFire_CheckForObject(this, globalCtx);
}
