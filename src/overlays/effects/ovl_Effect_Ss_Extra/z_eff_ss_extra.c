/*
 * File: z_eff_ss_extra.c
 * Overlay: ovl_Effect_Ss_Extra
 * Description:
 */

#include "z_eff_ss_extra.h"
#include "objects/object_yabusame_point/object_yabusame_point.h"

#define PARAMS ((EffectSsExtraInitParams*)initParamsx)

s32 EffectSsExtra_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx);
void EffectSsExtra_Update(GlobalContext* globalCtx, u32 index, EffectSs* this);
void EffectSsExtra_Draw(GlobalContext* globalCtx, u32 index, EffectSs* this);

s16 D_809808E0[] = { 0x1E, 0x3C, 0x64};


const EffectSsInit Effect_Ss_Extra_InitVars = {
    EFFECT_SS_EXTRA,
    EffectSsExtra_Init,
};

// wtf
Gfx* D_809808F0[] = { 0x06000000, 0x06000480, 0x06000900};

s32 EffectSsExtra_Init(GlobalContext *globalCtx, u32 index, EffectSs *this, void *initParamsx) {
    EffectSsExtraInitParams* params = PARAMS;
    s32 pad;
    s32 objIndex;

    objIndex = Object_GetIndex(&globalCtx->objectCtx, 0xE7);
    if (objIndex >= 0) {
        if (Object_IsLoaded(&globalCtx->objectCtx, objIndex)) {
            void* segBackup = gSegments[6];
            gSegments[6] = PHYSICAL_TO_VIRTUAL(globalCtx->objectCtx.status[objIndex].segment);


            this->pos = PARAMS->pos;
            this->velocity = PARAMS->velocity;
            this->accel = PARAMS->accel;
            this->draw = EffectSsExtra_Draw;
            this->update = EffectSsExtra_Update;
            this->life = 0x32;

            this->regs[2] = PARAMS->scoreIdx;
            this->regs[3] = PARAMS->scale;
            this->regs[1] = 5;
            this->regs[0] = objIndex;

            gSegments[6] = segBackup;
            return 1;
        }
    }
    return 0;
}

void EffectSsExtra_Draw(GlobalContext *globalCtx, u32 index, EffectSs *this) {
    s32 pad;
    f32 scale;
    void *storedSegment;

    scale = this->regs[3] / 100.0f;
    storedSegment = globalCtx->objectCtx.status[this->regs[0]].segment;
    OPEN_DISPS(globalCtx->state.gfxCtx);
    gSegments[6] = PHYSICAL_TO_VIRTUAL(storedSegment);

    gSPSegment(POLY_XLU_DISP++, 0x06, storedSegment);

    Matrix_InsertTranslation(this->pos.x, this->pos.y, this->pos.z, 0);
    Matrix_Scale(scale, scale, scale, 1);
    func_8012C2DC(globalCtx->state.gfxCtx);
    Matrix_NormalizeXYZ(&globalCtx->billboardMtxF);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gSPSegment(POLY_XLU_DISP++, 0x08, Lib_SegmentedToVirtual(D_809808F0[this->regs[2]]));

    gSPDisplayList(POLY_XLU_DISP++, &gYabusamePointDL);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void EffectSsExtra_Update(GlobalContext *globalCtx, u32 index, EffectSs *this) {
    // stop after 5 frames
    if (this->regs[1] != 0) {
        this->regs[1]--;
    } else {
        this->velocity.y = 0.0f;
    }

    if (this->regs[1] == 1) {
        globalCtx->interfaceCtx.unk_25C = D_809808E0[this->regs[2]];
    }
}
