#include "global.h"

void GameOver_Init(GlobalContext* globalCtx) {
    globalCtx->gameOverCtx.state = GAMEOVER_INACTIVE;
}

void GameOver_FadeLights(GlobalContext* globalCtx) {
    GameOverContext* gameOverCtx = &globalCtx->gameOverCtx;

    if ((gameOverCtx->state >= GAMEOVER_DEATH_WAIT_GROUND && gameOverCtx->state < GAMEOVER_REVIVE_START) ||
        (gameOverCtx->state >= GAMEOVER_REVIVE_RUMBLE && gameOverCtx->state < GAMEOVER_REVIVE_FADE_OUT)) {
        Kankyo_FadeInGameOverLights(globalCtx);
    }
}

static s16 sGameOverTimer = 0;

void GameOver_Update(GlobalContext* globalCtx) {
    GameOverContext* gameOverCtx = &globalCtx->gameOverCtx;
    s16 i;

    switch (gameOverCtx->state) {
        case GAMEOVER_DEATH_START:
            func_801477B4(globalCtx);

            for (i = 0; i < ARRAY_COUNT(gSaveContext.unk_3DD0); i++) {
                gSaveContext.unk_3DD0[i] = 0;
            }

            gSaveContext.eventInf[1] &= ~1;

            if (CUR_FORM == 0) {
                if (CUR_FORM_EQUIP(EQUIP_SLOT_B) != ITEM_SWORD_KOKIRI &&
                    CUR_FORM_EQUIP(EQUIP_SLOT_B) != ITEM_SWORD_RAZOR &&
                    CUR_FORM_EQUIP(EQUIP_SLOT_B) != ITEM_SWORD_GILDED &&
                    CUR_FORM_EQUIP(EQUIP_SLOT_B) != ITEM_SWORD_DEITY) {

                    if (gSaveContext.buttonStatus[0] != BTN_ENABLED) {
                        CUR_FORM_EQUIP(EQUIP_SLOT_B) = gSaveContext.buttonStatus[0];
                    } else {
                        CUR_FORM_EQUIP(EQUIP_SLOT_B) = ITEM_NONE;
                    }
                }
            }

            gSaveContext.unk_3DC0 = 2000;
            gSaveContext.save.playerData.tatlTimer = 0;
            gSaveContext.seqIndex = (u8)NA_BGM_DISABLED;
            gSaveContext.nightSeqIndex = 0xFF;
            gSaveContext.eventInf[0] = 0;
            gSaveContext.eventInf[1] = 0;
            gSaveContext.eventInf[2] = 0;
            gSaveContext.eventInf[3] = 0;
            gSaveContext.buttonStatus[0] = BTN_ENABLED;
            gSaveContext.buttonStatus[1] = BTN_ENABLED;
            gSaveContext.buttonStatus[2] = BTN_ENABLED;
            gSaveContext.buttonStatus[3] = BTN_ENABLED;
            gSaveContext.buttonStatus[4] = BTN_ENABLED;
            gSaveContext.unk_3F1E = 0;
            gSaveContext.unk_3F20 = 0;
            gSaveContext.unk_3F22 = 0;
            gSaveContext.unk_3F24 = 0;
            Kankyo_InitGameOverLights(globalCtx);
            sGameOverTimer = 20;
            func_8013ECE0(0.0f, 126, 124, 63);
            gameOverCtx->state = GAMEOVER_DEATH_WAIT_GROUND;
            break;
        case GAMEOVER_DEATH_FADE_OUT:
            if (func_801A8A50(1) != NA_BGM_GAME_OVER) {
                func_80169F78(&globalCtx->state);
                if (gSaveContext.respawnFlag != -7) {
                    gSaveContext.respawnFlag = -6;
                }
                gSaveContext.nextTransition = 2;
                gSaveContext.save.playerData.health = 48;
                gameOverCtx->state++;
                if (INV_CONTENT(ITEM_MASK_DEKU) == ITEM_MASK_DEKU) {
                    gSaveContext.save.playerForm = PLAYER_FORM_HUMAN;
                    gSaveContext.save.equippedMask = PLAYER_MASK_NONE;
                }
                func_8013EE24();
            }
            break;
        case GAMEOVER_REVIVE_START:
            gameOverCtx->state++;
            sGameOverTimer = 0;
            Kankyo_InitGameOverLights(globalCtx);
            ShrinkWindow_SetLetterboxTarget(32);
            break;
        case GAMEOVER_REVIVE_RUMBLE:
            sGameOverTimer = 50;
            gameOverCtx->state++;
            func_8013ECE0(0.0f, 126, 124, 63);
            break;
        case GAMEOVER_REVIVE_WAIT_GROUND:
            sGameOverTimer--;
            if (sGameOverTimer == 0) {
                sGameOverTimer = 64;
                gameOverCtx->state++;
            }
            break;
        case GAMEOVER_REVIVE_WAIT_FAIRY:
            sGameOverTimer--;
            if (sGameOverTimer == 0) {
                sGameOverTimer = 50;
                gameOverCtx->state++;
            }
            break;
        case GAMEOVER_REVIVE_FADE_OUT:
            Kankyo_FadeOutGameOverLights(globalCtx);
            sGameOverTimer--;
            if (sGameOverTimer == 0) {
                gameOverCtx->state = GAMEOVER_INACTIVE;
            }
            break;
    }
}
