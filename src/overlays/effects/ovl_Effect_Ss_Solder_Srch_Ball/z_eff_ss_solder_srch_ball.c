/*
 * File: z_eff_ss_solder_srch_ball.c
 * Overlay: ovl_Effect_Ss_Solder_Srch_Ball
 * Description:
 */

#include "z_eff_ss_solder_srch_ball.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define rDrawFlag regs[0]
#define rScale regs[1]

#define PARAMS ((EffectSsSolderSrchBallInitParams*)initParamsx)

u32 EffectSsSolderSrchBall_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx);
void EffectSsSolderSrchBall_Update(GlobalContext* globalCtx, u32 index, EffectSs* this);
void EffectSsSolderSrchBall_Draw(GlobalContext* globalCtx, u32 index, EffectSs* this);

const EffectSsInit Effect_Ss_Solder_Srch_Ball_InitVars = {
    EFFECT_SS_SOLDER_SRCH_BALL,
    EffectSsSolderSrchBall_Init,
};

u32 EffectSsSolderSrchBall_Init(GlobalContext* globalCtx, u32 index, EffectSs* this, void* initParamsx) {
    EffectSsSolderSrchBallInitParams* initParams = PARAMS;

    this->pos = initParams->pos;
    this->velocity = initParams->velocity;
    this->accel = initParams->accel;
    this->update = EffectSsSolderSrchBall_Update;
    if (!(initParams->drawFlag & 1)) {
        this->draw = EffectSsSolderSrchBall_Draw;
    }
    this->life = 10;
    this->rScale = initParams->scale;
    this->rDrawFlag = initParams->drawFlag;
    this->actor = initParams->linkDetected; // actor field was incorrectly used as a pointer to something else
    return 1;
}

void EffectSsSolderSrchBall_Draw(GlobalContext* globalCtx, u32 index, EffectSs* this) {
    s32 pad;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    f32 scale = this->rScale / 100.0f;

    func_8012C28C(gfxCtx);
    func_8012C2DC(globalCtx->state.gfxCtx);
    
    OPEN_DISPS(gfxCtx);
    
    Matrix_InsertTranslation(this->pos.x, this->pos.y, this->pos.z, MTXMODE_NEW);
    Matrix_Scale(scale, scale, scale, MTXMODE_APPLY);
    POLY_XLU_DISP = Gfx_CallSetupDL(POLY_XLU_DISP, 20);
    gSPSegment(POLY_XLU_DISP++, 0x08, Lib_SegmentedToVirtual(gSun1Tex));
    gSPDisplayList(POLY_XLU_DISP++, gameplay_keep_DL_07AB10);
    gDPPipeSync(POLY_XLU_DISP++);
    gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 255, 255);
    gDPSetEnvColor(POLY_XLU_DISP++, 250, 180, 255, 255);
    Matrix_InsertMatrix(&globalCtx->billboardMtxF, MTXMODE_APPLY);
    Matrix_InsertZRotation_f(DEGF_TO_RADF(20.0f * globalCtx->state.frames), MTXMODE_APPLY);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, gameplay_keep_DL_07AB58);

    CLOSE_DISPS(gfxCtx);
}

void EffectSsSolderSrchBall_Update(GlobalContext* globalCtx, u32 index, EffectSs* this) {
    s32 pad;
    f32 playerPosDiffX;
    f32 playerPosDiffY;
    f32 playerPosDiffZ;
    s16* linkDetected;
    Player* player = GET_PLAYER(globalCtx);

    linkDetected = this->actor;

    playerPosDiffX = player->actor.world.pos.x - this->pos.x;
    playerPosDiffY = player->actor.world.pos.y - this->pos.y;
    playerPosDiffZ = player->actor.world.pos.z - this->pos.z;

    if (this->regs[0] >= 2) {
        if (sqrtf(SQ(playerPosDiffX) + SQ(playerPosDiffZ)) < 10.0f &&  sqrtf(SQ(playerPosDiffY)) < 10.0f) {
                *linkDetected = true;
        }
    } else {
        if (!BgCheck_SphVsFirstWall(&globalCtx->colCtx, &this->pos, 30.0f)) {
            if (sqrtf(SQ(playerPosDiffX) + SQ(playerPosDiffZ)) < 40.0f &&  sqrtf(SQ(playerPosDiffY)) < 80.0f) {
                *linkDetected = true;
            }
        } else {
            if (this->life > 1) {
                this->life = 1;
            }
        }
    }
}
