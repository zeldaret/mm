#include "global.h"
#include "z64rumble.h"

void GameOver_Init(PlayState* play) {
    play->gameOverCtx.state = GAMEOVER_INACTIVE;
}

void GameOver_FadeLights(PlayState* play) {
    GameOverContext* gameOverCtx = &play->gameOverCtx;

    if ((gameOverCtx->state >= GAMEOVER_DEATH_WAIT_GROUND && gameOverCtx->state < GAMEOVER_REVIVE_START) ||
        (gameOverCtx->state >= GAMEOVER_REVIVE_RUMBLE && gameOverCtx->state < GAMEOVER_REVIVE_FADE_OUT)) {
        Kankyo_FadeInGameOverLights(play);
    }
}

static s16 sGameOverTimer = 0;

void GameOver_Update(PlayState* play) {
    GameOverContext* gameOverCtx = &play->gameOverCtx;
    s16 i;

    switch (gameOverCtx->state) {
        case GAMEOVER_DEATH_START:
            func_801477B4(play);

            for (i = 0; i < ARRAY_COUNT(gSaveContext.unk_3DD0); i++) {
                gSaveContext.unk_3DD0[i] = 0;
            }

            gSaveContext.eventInf[1] &= ~1;

            if (CUR_FORM == 0) {
                if (CUR_FORM_EQUIP(EQUIP_SLOT_B) != ITEM_SWORD_KOKIRI &&
                    CUR_FORM_EQUIP(EQUIP_SLOT_B) != ITEM_SWORD_RAZOR &&
                    CUR_FORM_EQUIP(EQUIP_SLOT_B) != ITEM_SWORD_GILDED &&
                    CUR_FORM_EQUIP(EQUIP_SLOT_B) != ITEM_SWORD_DEITY) {

                    if (gSaveContext.buttonStatus[EQUIP_SLOT_B] != BTN_ENABLED) {
                        CUR_FORM_EQUIP(EQUIP_SLOT_B) = gSaveContext.buttonStatus[EQUIP_SLOT_B];
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
            gSaveContext.buttonStatus[EQUIP_SLOT_B] = BTN_ENABLED;
            gSaveContext.buttonStatus[EQUIP_SLOT_C_LEFT] = BTN_ENABLED;
            gSaveContext.buttonStatus[EQUIP_SLOT_C_DOWN] = BTN_ENABLED;
            gSaveContext.buttonStatus[EQUIP_SLOT_C_RIGHT] = BTN_ENABLED;
            gSaveContext.buttonStatus[EQUIP_SLOT_A] = BTN_ENABLED;
            gSaveContext.unk_3F1E = 0;
            gSaveContext.unk_3F20 = 0;
            gSaveContext.unk_3F22 = 0;
            gSaveContext.unk_3F24 = 0;
            Kankyo_InitGameOverLights(play);
            sGameOverTimer = 20;
            Rumble_Request(0.0f, 126, 124, 63);
            gameOverCtx->state = GAMEOVER_DEATH_WAIT_GROUND;
            break;
        case GAMEOVER_DEATH_FADE_OUT:
            if (func_801A8A50(1) != NA_BGM_GAME_OVER) {
                func_80169F78(&play->state);
                if (gSaveContext.respawnFlag != -7) {
                    gSaveContext.respawnFlag = -6;
                }
                gSaveContext.nextTransitionType = TRANS_TYPE_02;
                gSaveContext.save.playerData.health = 0x30;
                gameOverCtx->state++;
                if (INV_CONTENT(ITEM_MASK_DEKU) == ITEM_MASK_DEKU) {
                    gSaveContext.save.playerForm = PLAYER_FORM_HUMAN;
                    gSaveContext.save.equippedMask = PLAYER_MASK_NONE;
                }
                Rumble_StateReset();
            }
            break;
        case GAMEOVER_REVIVE_START:
            gameOverCtx->state++;
            sGameOverTimer = 0;
            Kankyo_InitGameOverLights(play);
            ShrinkWindow_SetLetterboxTarget(32);
            break;
        case GAMEOVER_REVIVE_RUMBLE:
            sGameOverTimer = 50;
            gameOverCtx->state++;
            Rumble_Request(0.0f, 126, 124, 63);
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
            Kankyo_FadeOutGameOverLights(play);
            sGameOverTimer--;
            if (sGameOverTimer == 0) {
                gameOverCtx->state = GAMEOVER_INACTIVE;
            }
            break;
    }
}
