/*
 * File: z_eff_en_ice_block.c
 * Overlay: ovl_Effect_En_Ice_Block
 * Description: Ice Shard (Pentagon shaped) thrown off of the Obj_Iceblock actor during growth animation
 * Object Requirement: OBJECT_ICE_BLOCK
 */

#include "z_eff_en_ice_block.h"
#include "objects/object_ice_block/object_ice_block.h"

#define PARAMS ((EffectEnIceBlockInitParams*)initParamsx)

u32 EffectEnIceBlock_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx);
void EffectEnIceBlock_Update(GlobalContext* globalCtx, u32 index, EffectSs* this);
void EffectEnIceBlock_Draw(GlobalContext* globalCtx, u32 index, EffectSs* this);

const EffectSsInit Effect_En_Ice_Block_InitVars = {
    EFFECT_EN_ICE_BLOCK,
    EffectEnIceBlock_Init,
};

#define rObjId regs[0]
#define rScale regs[1]
#define rRot regs[2]
#define rRotVel regs[3]

u32 EffectEnIceBlock_CheckIceBlockObject(EffectSs* this, GlobalContext* globalCtx) {
    if (((this->rObjId = Object_GetIndex(&globalCtx->objectCtx, OBJECT_ICE_BLOCK)) < 0) ||
        (!Object_IsLoaded(&globalCtx->objectCtx, this->rObjId))) {
        this->life = -1;
        this->draw = NULL;
        return false;
    } else {
        return true;
    }
}

u32 EffectEnIceBlock_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx) {
    EffectEnIceBlockInitParams* params = PARAMS;

    Math_Vec3f_Copy(&this->pos, &params->pos);
    Math_Vec3f_Copy(&this->velocity, &params->velocity);
    Math_Vec3f_Copy(&this->accel, &params->accel);
    this->rScale = params->scale;
    this->rRot = Rand_ZeroOne() * 65535.0f;
    this->rRotVel = (s32)(Rand_ZeroOne() * 512.0f) + 0x400;
    this->life = 40;

    this->draw = EffectEnIceBlock_Draw;
    this->update = EffectEnIceBlock_Update;
    EffectEnIceBlock_CheckIceBlockObject(this, globalCtx);

    return 1;
}

void EffectEnIceBlock_Draw(GlobalContext* globalCtx, u32 index, EffectSs* this) {
    s32 pad;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;

    if (EffectEnIceBlock_CheckIceBlockObject(this, globalCtx)) {
        f32 scale = this->rScale * 0.1f * 0.01f;

        OPEN_DISPS(gfxCtx);

        gSPSegment(POLY_XLU_DISP++, 0x06,
                   globalCtx->objectCtx.status[this->rObjId].segment); // object: OBJECT_ICE_BLOCK

        func_8012C2DC(globalCtx->state.gfxCtx);
        Matrix_InsertTranslation(this->pos.x, this->pos.y, this->pos.z, MTXMODE_NEW);
        Matrix_Scale(scale, scale, scale, MTXMODE_APPLY);
        Matrix_InsertMatrix(&globalCtx->billboardMtxF, MTXMODE_APPLY);
        Matrix_InsertZRotation_s(this->rRot, MTXMODE_APPLY);

        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        gSPDisplayList(POLY_XLU_DISP++, &gIceBlockShardEffectDL);

        CLOSE_DISPS(gfxCtx);
    }
}

void EffectEnIceBlock_Update(GlobalContext* globalCtx, u32 index, EffectSs* this) {
    this->rRot += this->rRotVel;
    EffectEnIceBlock_CheckIceBlockObject(this, globalCtx);
}
