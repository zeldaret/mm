#include "global.h"

void PreNMI_Stop(PreNMIContext* prenmiCtx) {
    prenmiCtx->state.running = 0;
    prenmiCtx->state.nextGameStateInit = NULL;
    prenmiCtx->state.nextGameStateSize = 0;
}

void PreNMI_Update(PreNMIContext* prenmiCtx) {
    if (prenmiCtx->timer == 0) {
        ViConfig_UpdateVi(1);
        PreNMI_Stop(prenmiCtx);
        return;
    }

    prenmiCtx->timer--;
}

// #ifdef NON_MATCHING
// Minor reordering around call to func_8012C470
void PreNMI_Draw(PreNMIContext* prenmiCtx) {
    GraphicsContext* gfxCtx = prenmiCtx->state.gfxCtx;

    func_8012CF0C(gfxCtx, 1, 1, 0, 0, 0);

    OPEN_DISPS(gfxCtx);
    
    func_8012C470(gfxCtx);

    gDPSetFillColor(POLY_OPA_DISP++,
                    (GPACK_RGBA5551(0xFF, 0xFF, 0xFF, 1) << 16) | GPACK_RGBA5551(0xFF, 0xFF, 0xFF, 1));
    gDPFillRectangle(POLY_OPA_DISP++, 0, prenmiCtx->timer + 100, 320 /*SCREEN_WIDTH*/ - 1, prenmiCtx->timer + 100);
    CLOSE_DISPS(gfxCtx);
}
// #else
// #pragma GLOBAL_ASM("asm/non_matchings/code/z_prenmi/PreNMI_Draw.s")
// #endif

void PreNMI_Main(PreNMIContext* prenmiCtx) {
    PreNMI_Update(prenmiCtx);
    PreNMI_Draw(prenmiCtx);

    prenmiCtx->state.unkA3 = 1;
}

void PreNMI_Destroy(PreNMIContext* prenmiCtx) {
}

void PreNMI_Init(PreNMIContext* prenmiCtx) {
    prenmiCtx->state.main = (GameStateFunc)PreNMI_Main;
    prenmiCtx->state.destroy = (GameStateFunc)PreNMI_Destroy;
    prenmiCtx->timer = 30;
    prenmiCtx->unkA8 = 10;

    Game_SetFramerateDivisor(&prenmiCtx->state, 1);
}
