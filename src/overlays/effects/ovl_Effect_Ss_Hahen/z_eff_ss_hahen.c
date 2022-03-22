/*
 * File: z_eff_ss_hahen.c
 * Overlay: ovl_Effect_Ss_Hahen
 * Description:
 */

#include "z_eff_ss_hahen.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define rPitch regs[0]
#define rYaw regs[1]
#define rDrawFlags regs[2]
#define rScale regs[3]
#define rObjId regs[4]
#define rObjBankIndex regs[5]
#define rMinLife regs[6]

#define PARAMS ((EffectSsHahenInitParams*)initParamsx)

u32 EffectSsHahen_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx);
void EffectSsHahen_Update(GlobalContext* globalCtx, u32 index, EffectSs* this);
void EffectSsHahen_Draw(GlobalContext* globalCtx, u32 index, EffectSs* this);

const EffectSsInit Effect_Ss_Hahen_InitVars = {
    EFFECT_SS_HAHEN,
    EffectSsHahen_Init,
};

void EffectSsHahen_CheckForObject(EffectSs* this, GlobalContext* globalCtx) {
    if (((this->rObjBankIndex = Object_GetIndex(&globalCtx->objectCtx, this->rObjId)) < 0) ||
        !Object_IsLoaded(&globalCtx->objectCtx, this->rObjBankIndex)) {
        this->life = -1;
        this->draw = NULL;
    }
}

u32 EffectSsHahen_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx) {
    EffectSsHahenInitParams* initParams = PARAMS;

    this->pos = initParams->pos;
    this->velocity = initParams->velocity;
    this->accel = initParams->accel;
    this->life = 200;

    if (initParams->dList != NULL) {
        this->gfx = initParams->dList;
        this->rObjId = initParams->objId;
        EffectSsHahen_CheckForObject(this, globalCtx);
    } else {
        this->gfx = gameplay_keep_DL_01A620;
        this->rObjId = -1;
    }
    
    this->draw = EffectSsHahen_Draw;
    this->update = EffectSsHahen_Update;
    this->rDrawFlags = initParams->drawFlags;
    this->rScale = initParams->scale;
    this->rPitch = Rand_ZeroOne() * 314.0f;
    this->rYaw = Rand_ZeroOne() * 314.0f;
    this->rMinLife = 200 - initParams->life;

    return 1;
}

void EffectSsHahen_DrawOpa(GlobalContext* globalCtx, EffectSs* this) {
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    s32 pad;

    OPEN_DISPS(gfxCtx);

    if (this->rObjId != -1) {
        gSPSegment(POLY_OPA_DISP++, 0x06, globalCtx->objectCtx.status[this->rObjBankIndex].segment);
    }
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    func_8012C28C(globalCtx->state.gfxCtx);
    gSPDisplayList(POLY_OPA_DISP++, this->gfx);

    CLOSE_DISPS(gfxCtx);
}

void EffectSsHahen_DrawXlu(GlobalContext* globalCtx, EffectSs* this) {
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    s32 pad;

    OPEN_DISPS(gfxCtx);

    if (this->rObjId != -1) {
        gSPSegment(POLY_XLU_DISP++, 0x06, globalCtx->objectCtx.status[this->rObjBankIndex].segment);
    }
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    func_8012C2DC(globalCtx->state.gfxCtx);
    gSPDisplayList(POLY_XLU_DISP++, this->gfx);

    CLOSE_DISPS(gfxCtx);
}

void EffectSsHahen_Draw(GlobalContext* globalCtx, u32 index, EffectSs* this) {
    f32 scale;

    if (this->rDrawFlags & HAHEN_DRAWFLAGS_SMALL) {
        scale = this->rScale * (0.001f * 0.1f);
    } else {
        scale = this->rScale * 0.001f;
    }
    Matrix_InsertTranslation(this->pos.x, this->pos.y, this->pos.z, MTXMODE_NEW);
    Matrix_InsertYRotation_f(this->rYaw * 0.01f, MTXMODE_APPLY);
    Matrix_RotateStateAroundXAxis(this->rPitch * 0.01f);
    Matrix_Scale(scale, scale, scale, MTXMODE_APPLY);
    if (this->rDrawFlags & HAHEN_DRAWFLAGS_XLU) {
        EffectSsHahen_DrawXlu(globalCtx, this);
    } else {
        EffectSsHahen_DrawOpa(globalCtx, this);
    }
}

void EffectSsHahen_Update(GlobalContext* globalCtx, u32 index, EffectSs* this) {
    Player* player = GET_PLAYER(globalCtx);

    this->rPitch += 55;
    this->rYaw += 10;

    if ((this->pos.y <= player->actor.floorHeight) && (this->life < this->rMinLife)) {
        this->life = 0;
    }

    if (this->rObjId != -1) {
        EffectSsHahen_CheckForObject(this, globalCtx);
    }
}
