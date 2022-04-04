/*
 * File: z_opening.c
 * Overlay: ovl_opening
 * Description: Initializes the game into the title screen
 */

#include "z_opening.h"

void Opening_SetupForTitleCutscene(OpeningContext* this) {
    static s32 openingEntrances[] = { 0x1C00, 0x1C10 };
    static s32 openingCutscenes[] = { 0xFFFA, 0xFFFA };

    gSaveContext.eventInf[1] &= (u8)~0x80;
    gSaveContext.gameMode = 1;

    Sram_InitNewSave();

    gSaveContext.save.entranceIndex = openingEntrances[D_801BB12C];
    gSaveContext.nextCutsceneIndex = gSaveContext.save.cutscene = openingCutscenes[D_801BB12C];
    gSaveContext.sceneSetupIndex = 0;

    gSaveContext.save.time = CLOCK_TIME(8, 0);
    gSaveContext.save.day = 1;

    {
        GameState* thisx = &this->gameState;
        thisx->running = false;
    }
    SET_NEXT_GAMESTATE(&this->gameState, Play_Init, GlobalContext);
    gSaveContext.save.playerForm = PLAYER_FORM_HUMAN;
}

void func_80803EA0(OpeningContext* this) {
    SREG(33) |= 1;
}

void Opening_Main(GameState* thisx) {
    OpeningContext* this = (OpeningContext*)thisx;

    func_8012CF0C(this->gameState.gfxCtx, false, true, 0, 0, 0);
    Opening_SetupForTitleCutscene(this);
    func_80803EA0(this);
}

void Opening_Destroy(GameState* thisx) {
    ShrinkWindow_Destroy();
}

void Opening_Init(GameState* thisx) {
    OpeningContext* this = (OpeningContext*)thisx;

    Game_SetFramerateDivisor(&this->gameState, 1);
    Matrix_StateAlloc(&this->gameState);
    ShrinkWindow_Init();
    View_Init(&this->view, this->gameState.gfxCtx);
    this->gameState.main = Opening_Main;
    this->gameState.destroy = Opening_Destroy;

    gSaveContext.respawnFlag = 0;
    gSaveContext.respawn[RESPAWN_MODE_GORON].entranceIndex = 0xFF;
    gSaveContext.respawn[RESPAWN_MODE_ZORA].entranceIndex = 0xFF;
    gSaveContext.respawn[RESPAWN_MODE_DEKU].entranceIndex = 0xFF;
    gSaveContext.respawn[RESPAWN_MODE_HUMAN].entranceIndex = 0xFF;
}
