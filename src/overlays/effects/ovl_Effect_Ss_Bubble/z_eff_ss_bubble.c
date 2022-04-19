/*
 * File: z_eff_ss_bubble.c
 * Overlay: ovl_Effect_Ss_Bubble
 * Description:
 */

#include "z_eff_ss_bubble.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define rScale regs[0]
#define rVecAdjX regs[1]
#define rVecAdjZ regs[2]

#define PARAMS ((EffectSsBubbleInitParams*)initParamsx)

u32 EffectSsBubble_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx);
void EffectSsBubble_Update(GlobalContext* globalCtx, u32 index, EffectSs* this);
void EffectSsBubble_Draw(GlobalContext* globalCtx, u32 index, EffectSs* this);

const EffectSsInit Effect_Ss_Bubble_InitVars = {
    EFFECT_SS_BUBBLE,
    EffectSsBubble_Init,
};

static f32 sVecAdjMaximums[] = { 291.0f, 582.0f, 1600.0f };

u32 EffectSsBubble_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx) {
    EffectSsBubbleInitParams* initParams = (EffectSsBubbleInitParams*)initParamsx;

    {
        TexturePtr tex = (Rand_ZeroOne() < 0.5f) ? gEffBubble1Tex : gEffBubble2Tex;

        this->gfx = VIRTUAL_TO_PHYSICAL(SEGMENTED_TO_VIRTUAL(tex));
    }

    this->pos.x = ((Rand_ZeroOne() - 0.5f) * initParams->xzPosRandScale) + initParams->pos.x;
    this->pos.y = (((Rand_ZeroOne() - 0.5f) * initParams->yPosRandScale) + initParams->yPosOffset) + initParams->pos.y;
    this->pos.z = ((Rand_ZeroOne() - 0.5f) * initParams->xzPosRandScale) + initParams->pos.z;
    Math_Vec3f_Copy(&this->vec, &this->pos);
    this->life = 1;
    this->rScale = (((Rand_ZeroOne() * 0.5f) + 1.0f) * initParams->scale) * 100.0f;
    this->draw = EffectSsBubble_Draw;
    this->update = EffectSsBubble_Update;

    return 1;
}

void EffectSsBubble_Draw(GlobalContext* globalCtx, u32 index, EffectSs* this) {
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    f32 scale = this->rScale / 100.0f;

    OPEN_DISPS(gfxCtx);

    Matrix_InsertTranslation(this->pos.x, this->pos.y, this->pos.z, MTXMODE_NEW);
    Matrix_Scale(scale, scale, scale, MTXMODE_APPLY);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    func_8012C28C(gfxCtx);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, 255);
    gDPSetEnvColor(POLY_OPA_DISP++, 150, 150, 150, 0);
    gSPSegment(POLY_OPA_DISP++, 0x08, this->gfx);
    gSPDisplayList(POLY_OPA_DISP++, gEffBubbleDL);

    CLOSE_DISPS(gfxCtx);
}

void EffectSsBubble_Update(GlobalContext* globalCtx2, u32 index, EffectSs* this) {
    WaterBox* waterBox;
    f32 waterSurfaceY = this->pos.y;
    Vec3f ripplePos;
    GlobalContext* globalCtx = globalCtx2;

    if (!WaterBox_GetSurface1(globalCtx, &globalCtx->colCtx, this->pos.x, this->pos.z, &waterSurfaceY, &waterBox)) {
        this->life = -1;
        return;
    }
    if (waterSurfaceY < this->pos.y) {
        ripplePos.x = this->pos.x;
        ripplePos.y = waterSurfaceY;
        ripplePos.z = this->pos.z;
        EffectSsGRipple_Spawn(globalCtx, &ripplePos, 0, 80, 0);
        this->life = -1;
    label:
        return;
    }
    if (((globalCtx->gameplayFrames + index) % 8) == 0) {
        CollisionPoly* colPoly;
        u32 speed;
        s16 direction;
        f32 rVecAdjMax;

        BgCheck_EntityRaycastFloor2_1(globalCtx, &globalCtx->colCtx, &colPoly, &this->pos);
        speed = SurfaceType_GetConveyorSpeed(&globalCtx->colCtx, colPoly, BGCHECK_SCENE);
        if ((speed != 0) && !SurfaceType_GetConveyorType(&globalCtx->colCtx, colPoly, BGCHECK_SCENE)) {
            direction = SurfaceType_GetConveyorDirection(&globalCtx->colCtx, colPoly, BGCHECK_SCENE) << 0xA;
            rVecAdjMax = sVecAdjMaximums[speed - 1];
            this->rVecAdjX = Math_SinS(direction) * rVecAdjMax;
            this->rVecAdjZ = Math_CosS(direction) * rVecAdjMax;
        }
    }
    this->vec.x += this->rVecAdjX / 100.0f;
    this->vec.z += this->rVecAdjZ / 100.0f;
    this->pos.x = ((Rand_ZeroOne() * 0.5f) - 0.25f) + this->vec.x;
    this->accel.y = (Rand_ZeroOne() - 0.3f) * 0.2f;
    this->pos.z = (Rand_ZeroOne() * 0.5f - 0.25f) + this->vec.z;
    this->life++;
}
