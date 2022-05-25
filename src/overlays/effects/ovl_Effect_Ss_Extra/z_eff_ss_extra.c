/*
 * File: z_eff_ss_extra.c
 * Overlay: ovl_Effect_Ss_Extra
 * Description: The floating points hovering over a target you hit in OoT
 *   i.e. 30/60/100 points when hitting the target in lost woods with slingshot to get a bigger seed sack
 */

#include "z_eff_ss_extra.h"
#include "objects/object_yabusame_point/object_yabusame_point.h"

#define PARAMS ((EffectSsExtraInitParams*)initParamsx)

u32 EffectSsExtra_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx);
void EffectSsExtra_Update(GlobalContext* globalCtx, u32 index, EffectSs* this);
void EffectSsExtra_Draw(GlobalContext* globalCtx, u32 index, EffectSs* this);

static s16 gScores[] = { 30, 60, 100 };

const EffectSsInit Effect_Ss_Extra_InitVars = {
    EFFECT_SS_EXTRA,
    EffectSsExtra_Init,
};

static u64* gPointTextures[] = { gYabusamePoint30Tex, gYabusamePoint60Tex, gYabusamePoint100Tex };

#define rObjId regs[0]
#define rTimer regs[1]
#define rScoreIdx regs[2]
#define rScale regs[3]

u32 EffectSsExtra_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx) {
    s32 pad;
    EffectSsExtraInitParams* params = PARAMS;
    s32 objIndex;

    objIndex = Object_GetIndex(&globalCtx->objectCtx, OBJECT_YABUSAME_POINT);
    if ((objIndex >= 0) && (Object_IsLoaded(&globalCtx->objectCtx, objIndex))) {
        void* segBackup = gSegments[6];

        gSegments[6] = PHYSICAL_TO_VIRTUAL(globalCtx->objectCtx.status[objIndex].segment);

        this->pos = PARAMS->pos;
        this->velocity = PARAMS->velocity;
        this->accel = PARAMS->accel;
        this->draw = EffectSsExtra_Draw;
        this->update = EffectSsExtra_Update;
        this->life = 50;
        this->rScoreIdx = PARAMS->scoreIdx;
        this->rScale = PARAMS->scale;
        this->rTimer = 5;
        this->rObjId = objIndex;

        gSegments[6] = segBackup;
        return 1;
    }
    return 0;
}

void EffectSsExtra_Draw(GlobalContext* globalCtx, u32 index, EffectSs* this) {
    s32 pad;
    f32 scale;
    void* storedSegment;

    scale = this->rScale / 100.0f;
    storedSegment = globalCtx->objectCtx.status[this->rObjId].segment;
    OPEN_DISPS(globalCtx->state.gfxCtx);
    gSegments[6] = PHYSICAL_TO_VIRTUAL(storedSegment);

    gSPSegment(POLY_XLU_DISP++, 0x06, storedSegment);

    Matrix_InsertTranslation(this->pos.x, this->pos.y, this->pos.z, MTXMODE_NEW);
    Matrix_Scale(scale, scale, scale, MTXMODE_APPLY);
    func_8012C2DC(globalCtx->state.gfxCtx);
    Matrix_NormalizeXYZ(&globalCtx->billboardMtxF);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gSPSegment(POLY_XLU_DISP++, 0x08, Lib_SegmentedToVirtual(gPointTextures[this->rScoreIdx]));

    gSPDisplayList(POLY_XLU_DISP++, &gYabusamePointDL);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void EffectSsExtra_Update(GlobalContext* globalCtx, u32 index, EffectSs* this) {
    if (this->rTimer != 0) {
        this->rTimer--;
    } else {
        this->velocity.y = 0.0f;
    }

    if (this->rTimer == 1) {
        globalCtx->interfaceCtx.unk_25C = gScores[this->rScoreIdx];
    }
}
