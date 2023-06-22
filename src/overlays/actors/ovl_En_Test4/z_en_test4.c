/*
 * File: z_en_test4.c
 * Overlay: ovl_En_Test4
 * Description: Three-Day Events
 */

#include "z_en_test4.h"
#include "z64horse.h"
#include "overlays/gamestates/ovl_daytelop/z_daytelop.h"
#include "overlays/actors/ovl_En_Horse/z_en_horse.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20 | ACTOR_FLAG_100000)

#define THIS ((EnTest4*)thisx)

void EnTest4_Init(Actor* thisx, PlayState* play);
void EnTest4_Destroy(Actor* thisx, PlayState* play);
void EnTest4_Update(Actor* thisx, PlayState* play);

void func_80A42AB8(EnTest4* this, PlayState* play);
void func_80A42F20(EnTest4* this, PlayState* play);

ActorInit En_Test4_InitVars = {
    ACTOR_EN_TEST4,
    ACTORCAT_SWITCH,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnTest4),
    (ActorFunc)EnTest4_Init,
    (ActorFunc)EnTest4_Destroy,
    (ActorFunc)EnTest4_Update,
    (ActorFunc)NULL,
};

static s32 sIsLoaded = false;
// "Night of ..."
static s16 sNightMessages1[] = { 0x1BB4, 0x1BB5, 0x1BB6 };
// "Dawn of ..." (Note: first two message are the same)
static s16 sDayMessages1[] = { 0x1BB2, 0x1BB2, 0x1BB3 };
// "Night of ..."
static s16 sNightMessages2[] = { 0x1BB4, 0x1BB5, 0x1BB6 };
// "Dawn of ..." (Note: first two message are the same)
static s16 sDayMessages2[] = { 0x1BB2, 0x1BB2, 0x1BB3 };
static u16 D_80A43364[] = { CLOCK_TIME(6, 0), CLOCK_TIME(18, 0) };

static s16 sCsIdList[2];
static s16 sCurCsId;

void func_80A41D70(EnTest4* this, PlayState* play) {
    if (this->csIdIndex != 0) {
        Message_DisplaySceneTitleCard(play, sNightMessages1[CURRENT_DAY - 1]);
    } else if ((sCsIdList[this->csIdIndex] < 0) || (play->actorCtx.flags & ACTORCTX_FLAG_1)) {
        if (play->actorCtx.flags & ACTORCTX_FLAG_1) {
            Sram_IncrementDay();
            gSaveContext.save.time = CLOCK_TIME(6, 0);
            Message_DisplaySceneTitleCard(play, sDayMessages1[CURRENT_DAY - 1]);
        } else {
            this->csIdIndex = 0;
            this->unk_146 = gSaveContext.save.time += CLOCK_TIME_MINUTE;
        }

        Interface_NewDay(play, CURRENT_DAY);
        D_801BDBC8 = 0xFE;
        func_800FB758(play);
        func_800FEAF4(&play->envCtx);
        this->actionFunc = func_80A42AB8;
    }

    if (gSaveContext.cutsceneTrigger == 0) {
        if ((sCsIdList[this->csIdIndex] >= 0) && !(play->actorCtx.flags & ACTORCTX_FLAG_1)) {
            this->actionFunc = func_80A42F20;
            sCurCsId = sCsIdList[this->csIdIndex];
            this->transitionCsTimer = 0;
            SET_EVENTINF(EVENTINF_17);
        } else if (this->csIdIndex == 0) {
            Audio_PlaySfx(NA_SE_EV_CHICKEN_CRY_M);
        } else {
            Audio_PlaySfx_2(NA_SE_EV_DOG_CRY_EVENING);
        }
    } else {
        this->actionFunc = func_80A42AB8;
        if (this->csIdIndex == 0) {
            this->csIdIndex = 1;
        } else {
            this->csIdIndex = 0;
        }

        this->unk_146 = gSaveContext.save.time += CLOCK_TIME_MINUTE;
    }
}

void func_80A41FA4(EnTest4* this, PlayState* play) {
    if (this->csIdIndex != 0) {
        Message_DisplaySceneTitleCard(play, sNightMessages2[CURRENT_DAY - 1]);
    } else if ((sCsIdList[this->csIdIndex] < 0) || (play->actorCtx.flags & ACTORCTX_FLAG_1)) {
        Sram_IncrementDay();
        gSaveContext.save.time = CLOCK_TIME(6, 0);
        Interface_NewDay(play, CURRENT_DAY);
        Message_DisplaySceneTitleCard(play, sDayMessages2[CURRENT_DAY - 1]);
        D_801BDBC8 = 0xFE;
        func_800FB758(play);
        func_800FEAF4(&play->envCtx);
        this->actionFunc = func_80A42AB8;
    }

    if (gSaveContext.cutsceneTrigger == 0) {
        if ((sCsIdList[this->csIdIndex] >= 0) && !(play->actorCtx.flags & ACTORCTX_FLAG_1)) {
            this->actionFunc = func_80A42F20;
            sCurCsId = sCsIdList[this->csIdIndex];
            this->transitionCsTimer = 0;
            SET_EVENTINF(EVENTINF_17);
        } else if (this->csIdIndex == 0) {
            Audio_PlaySfx(NA_SE_EV_CHICKEN_CRY_M);
        } else {
            Audio_PlaySfx_2(NA_SE_EV_DOG_CRY_EVENING);
        }
    } else {
        this->actionFunc = func_80A42AB8;
        if (this->csIdIndex == 0) {
            this->csIdIndex = 1;
        } else {
            this->csIdIndex = 0;
        }

        this->unk_146 = gSaveContext.save.time += CLOCK_TIME_MINUTE;
    }
}

// Bells on last day
void func_80A42198(EnTest4* this) {
    if ((gSaveContext.save.time >= CLOCK_TIME(6, 0)) && (gSaveContext.save.time <= CLOCK_TIME(18, 0))) {
        if (gSaveContext.save.time < CLOCK_TIME(17, 30)) {
            this->nextBellTime = CLOCK_TIME(17, 30);
        } else if (gSaveContext.save.time < CLOCK_TIME(17, 36)) {
            this->nextBellTime = CLOCK_TIME(17, 36);
        } else if (gSaveContext.save.time < CLOCK_TIME(17, 42)) {
            this->nextBellTime = CLOCK_TIME(17, 42);
        } else if (gSaveContext.save.time < CLOCK_TIME(17, 48)) {
            this->nextBellTime = CLOCK_TIME(17, 48);
        } else if (gSaveContext.save.time < CLOCK_TIME(17, 54)) {
            this->nextBellTime = CLOCK_TIME(17, 54);
        } else {
            this->nextBellTime = CLOCK_TIME(0, 0);
        }
    } else if (gSaveContext.save.time > CLOCK_TIME(6, 0)) {
        this->nextBellTime = CLOCK_TIME(0, 0);
    } else if (gSaveContext.save.time < CLOCK_TIME(0, 10)) {
        this->nextBellTime = CLOCK_TIME(0, 10);
    } else if (gSaveContext.save.time < CLOCK_TIME(0, 20)) {
        this->nextBellTime = CLOCK_TIME(0, 20);
    } else if (gSaveContext.save.time < CLOCK_TIME(0, 30)) {
        this->nextBellTime = CLOCK_TIME(0, 30);
    } else if (gSaveContext.save.time < CLOCK_TIME(0, 40)) {
        this->nextBellTime = CLOCK_TIME(0, 40);
    } else if (gSaveContext.save.time < CLOCK_TIME(0, 50)) {
        this->nextBellTime = CLOCK_TIME(0, 50);
    } else if (gSaveContext.save.time < CLOCK_TIME(1, 0)) {
        this->nextBellTime = CLOCK_TIME(1, 0);
    } else if (gSaveContext.save.time < CLOCK_TIME(1, 10)) {
        this->nextBellTime = CLOCK_TIME(1, 10);
    } else if (gSaveContext.save.time < CLOCK_TIME(1, 20)) {
        this->nextBellTime = CLOCK_TIME(1, 20);
    } else if (gSaveContext.save.time < CLOCK_TIME(1, 30) - 1) {
        this->nextBellTime = CLOCK_TIME(1, 30) - 1;
    } else if (gSaveContext.save.time < CLOCK_TIME(1, 40) - 1) {
        this->nextBellTime = CLOCK_TIME(1, 40) - 1;
    } else if (gSaveContext.save.time < CLOCK_TIME(1, 50) - 1) {
        this->nextBellTime = CLOCK_TIME(1, 50) - 1;
    } else if (gSaveContext.save.time < CLOCK_TIME(2, 0)) {
        this->nextBellTime = CLOCK_TIME(2, 0);
    } else if (gSaveContext.save.time < CLOCK_TIME(2, 10)) {
        this->nextBellTime = CLOCK_TIME(2, 10);
    } else if (gSaveContext.save.time < CLOCK_TIME(2, 20)) {
        this->nextBellTime = CLOCK_TIME(2, 20);
    } else if (gSaveContext.save.time < CLOCK_TIME(2, 30)) {
        this->nextBellTime = CLOCK_TIME(2, 30);
    } else if (gSaveContext.save.time < CLOCK_TIME(2, 40)) {
        this->nextBellTime = CLOCK_TIME(2, 40);
    } else if (gSaveContext.save.time < CLOCK_TIME(2, 50)) {
        this->nextBellTime = CLOCK_TIME(2, 50);
    } else if (gSaveContext.save.time < CLOCK_TIME(3, 0)) {
        this->nextBellTime = CLOCK_TIME(3, 0);
    } else if (gSaveContext.save.time < CLOCK_TIME(3, 10)) {
        this->nextBellTime = CLOCK_TIME(3, 10);
    } else if (gSaveContext.save.time < CLOCK_TIME(3, 20)) {
        this->nextBellTime = CLOCK_TIME(3, 20);
    } else if (gSaveContext.save.time < CLOCK_TIME(3, 30)) {
        this->nextBellTime = CLOCK_TIME(3, 30);
    } else if (gSaveContext.save.time < CLOCK_TIME(3, 40)) {
        this->nextBellTime = CLOCK_TIME(3, 40);
    } else if (gSaveContext.save.time < CLOCK_TIME(3, 50)) {
        this->nextBellTime = CLOCK_TIME(3, 50);
    } else if (gSaveContext.save.time < CLOCK_TIME(4, 0)) {
        this->nextBellTime = CLOCK_TIME(4, 0);
    } else if (gSaveContext.save.time < CLOCK_TIME(4, 10)) {
        this->nextBellTime = CLOCK_TIME(4, 10);
    } else if (gSaveContext.save.time < CLOCK_TIME(4, 20)) {
        this->nextBellTime = CLOCK_TIME(4, 20);
    } else if (gSaveContext.save.time < CLOCK_TIME(4, 30) - 1) {
        this->nextBellTime = CLOCK_TIME(4, 30) - 1;
    } else if (gSaveContext.save.time < CLOCK_TIME(4, 40) - 1) {
        this->nextBellTime = CLOCK_TIME(4, 40) - 1;
    } else if (gSaveContext.save.time < CLOCK_TIME(4, 50) - 1) {
        this->nextBellTime = CLOCK_TIME(4, 50) - 1;
    } else if (gSaveContext.save.time < CLOCK_TIME(5, 0)) {
        this->nextBellTime = CLOCK_TIME(5, 0);
    } else if (gSaveContext.save.time < CLOCK_TIME(5, 5)) {
        this->nextBellTime = CLOCK_TIME(5, 5);
    } else if (gSaveContext.save.time < CLOCK_TIME(5, 10)) {
        this->nextBellTime = CLOCK_TIME(5, 10);
    } else if (gSaveContext.save.time < CLOCK_TIME(5, 15) - 1) {
        this->nextBellTime = CLOCK_TIME(5, 15) - 1;
    } else if (gSaveContext.save.time < CLOCK_TIME(5, 20)) {
        this->nextBellTime = CLOCK_TIME(5, 20);
    } else if (gSaveContext.save.time < CLOCK_TIME(5, 25) - 1) {
        this->nextBellTime = CLOCK_TIME(5, 25) - 1;
    } else if (gSaveContext.save.time < CLOCK_TIME(5, 30)) {
        this->nextBellTime = CLOCK_TIME(5, 30);
    } else if (gSaveContext.save.time < CLOCK_TIME(5, 33) - 1) {
        this->nextBellTime = CLOCK_TIME(5, 33) - 1;
    } else if (gSaveContext.save.time < CLOCK_TIME(5, 36)) {
        this->nextBellTime = CLOCK_TIME(5, 36);
    } else if (gSaveContext.save.time < CLOCK_TIME(5, 39) - 1) {
        this->nextBellTime = CLOCK_TIME(5, 39) - 1;
    } else if (gSaveContext.save.time < CLOCK_TIME(5, 42)) {
        this->nextBellTime = CLOCK_TIME(5, 42);
    } else if (gSaveContext.save.time < CLOCK_TIME(5, 45)) {
        this->nextBellTime = CLOCK_TIME(5, 45);
    } else if (gSaveContext.save.time < CLOCK_TIME(5, 48)) {
        this->nextBellTime = CLOCK_TIME(5, 48);
    } else if (gSaveContext.save.time < CLOCK_TIME(5, 51)) {
        this->nextBellTime = CLOCK_TIME(5, 51);
    } else if (gSaveContext.save.time < CLOCK_TIME(5, 54)) {
        this->nextBellTime = CLOCK_TIME(5, 54);
    } else if (gSaveContext.save.time < CLOCK_TIME(5, 57)) {
        this->nextBellTime = CLOCK_TIME(5, 57);
    } else if (gSaveContext.save.time < CLOCK_TIME(6, 0)) {
        this->nextBellTime = CLOCK_TIME(6, 0);
    }
}

// Bells on first and second day
void func_80A425E4(EnTest4* this, PlayState* play) {
    gSaveContext.screenScale = 1000.0f;

    if ((gSaveContext.save.time >= CLOCK_TIME(6, 0)) && (gSaveContext.save.time < CLOCK_TIME(18, 0))) {
        if (gSaveContext.save.time < CLOCK_TIME(17, 30)) {
            this->nextBellTime = CLOCK_TIME(17, 30);
        } else if (gSaveContext.save.time < CLOCK_TIME(17, 36)) {
            this->nextBellTime = CLOCK_TIME(17, 36);
        } else if (gSaveContext.save.time < CLOCK_TIME(17, 42)) {
            this->nextBellTime = CLOCK_TIME(17, 42);
        } else if (gSaveContext.save.time < CLOCK_TIME(17, 48)) {
            this->nextBellTime = CLOCK_TIME(17, 48);
        } else if (gSaveContext.save.time < CLOCK_TIME(17, 54)) {
            this->nextBellTime = CLOCK_TIME(17, 54);
        } else {
            this->nextBellTime = CLOCK_TIME(5, 30);
        }
    } else {
        if (gSaveContext.save.time < CLOCK_TIME(5, 30)) {
            this->nextBellTime = CLOCK_TIME(5, 30);
        } else if (gSaveContext.save.time < CLOCK_TIME(5, 36)) {
            this->nextBellTime = CLOCK_TIME(5, 36);
        } else if (gSaveContext.save.time < CLOCK_TIME(5, 42)) {
            this->nextBellTime = CLOCK_TIME(5, 42);
            gSaveContext.screenScale -= 50.0f;
        } else if (gSaveContext.save.time < CLOCK_TIME(5, 48)) {
            this->nextBellTime = CLOCK_TIME(5, 48);
            gSaveContext.screenScale -= 100.0f;
        } else if (gSaveContext.save.time < CLOCK_TIME(5, 54)) {
            this->nextBellTime = CLOCK_TIME(5, 54);
            gSaveContext.screenScale -= 150.0f;
        } else if (gSaveContext.save.time < CLOCK_TIME(6, 0)) {
            this->nextBellTime = CLOCK_TIME(17, 30);
            gSaveContext.screenScale -= 200.0f;
        } else {
            this->nextBellTime = CLOCK_TIME(17, 30);
        }

        if ((sCsIdList[this->csIdIndex] < 0) || (play->actorCtx.flags & ACTORCTX_FLAG_1) || (CURRENT_DAY == 3) ||
            (gSaveContext.save.time >= CLOCK_TIME(17, 0))) {
            gSaveContext.screenScale = 1000.0f;
        }
        if (gSaveContext.screenScale != 1000.0f) {
            gSaveContext.screenScaleFlag = true;
        }
    }
}

void EnTest4_Init(Actor* thisx, PlayState* play) {
    s32 dayTemp;
    EnTest4* this = THIS;
    Player* player = GET_PLAYER(play);
    s8 csId = this->actor.csId;

    sCsIdList[0] = csId;
    if (csId >= 0) {
        ActorCutscene* csEntry = CutsceneManager_GetCutsceneEntry(sCsIdList[0]);

        SET_EVENTINF(EVENTINF_52);
        sCsIdList[1] = csEntry->additionalCsId;
    } else {
        CLEAR_EVENTINF(EVENTINF_52);
        sCsIdList[1] = sCsIdList[0];
    }

    if (sIsLoaded || CHECK_EVENTINF(EVENTINF_TRIGGER_DAYTELOP)) {
        Actor_Kill(&this->actor);
    } else {
        sIsLoaded = true;
        this->actor.room = -1;
        gSaveContext.screenScaleFlag = false;
        gSaveContext.screenScale = 1000.0f;
        if (CURRENT_DAY == 0) {
            if (gSaveContext.save.time < CLOCK_TIME(6, 1)) {
                gSaveContext.save.time = CLOCK_TIME(6, 0);
                gSaveContext.gameMode = GAMEMODE_NORMAL;
                STOP_GAMESTATE(&play->state);
                SET_NEXT_GAMESTATE(&play->state, DayTelop_Init, sizeof(DayTelopState));
                this->csIdIndex = 1;
                gSaveContext.save.time = CLOCK_TIME(6, 0);
                Actor_Kill(&this->actor);
            } else {
                gSaveContext.save.day = 1;
                dayTemp = gSaveContext.save.day;
                gSaveContext.save.daysElapsed = dayTemp;
                this->csIdIndex = 1;
                this->unk_146 = gSaveContext.save.time;
                this->actionFunc = func_80A42AB8;
            }
        } else if (gSaveContext.save.time == CLOCK_TIME(6, 0)) {
            this->csIdIndex = 0;
            func_80A41D70(this, play);
            if ((gSaveContext.cutsceneTrigger == 0) && (sCsIdList[this->csIdIndex] >= 0) &&
                !(play->actorCtx.flags & ACTORCTX_FLAG_1)) {
                player->stateFlags1 |= PLAYER_STATE1_200;
            }
        } else {
            if ((gSaveContext.save.time > CLOCK_TIME(18, 0)) || (gSaveContext.save.time < CLOCK_TIME(6, 0))) {
                this->csIdIndex = 0;
            } else {
                this->csIdIndex = 1;
            }
            this->unk_146 = gSaveContext.save.time;
            this->actionFunc = func_80A42AB8;
        }
    }

    if (CURRENT_DAY == 3) {
        func_80A42198(this);
    } else {
        func_80A425E4(this, play);
    }

    this->lastBellTime = gSaveContext.save.time;
    if ((sCsIdList[this->csIdIndex] < 0) || (play->actorCtx.flags & ACTORCTX_FLAG_1)) {
        gSaveContext.screenScaleFlag = false;
        gSaveContext.screenScale = 1000.0f;
    }
}

void EnTest4_Destroy(Actor* thisx, PlayState* play) {
}

void func_80A42AB8(EnTest4* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if ((play->transitionMode == TRANS_MODE_OFF) && !Play_InCsMode(play) && (play->numSetupActors <= 0) &&
        (play->roomCtx.status == 0) && !Play_IsDebugCamEnabled()) {
        s16 temp_a2;
        u16 temp_a0 = D_80A43364[this->csIdIndex];
        s16 temp_a3;
        s16 bellDiff;
        s16 new_var;

        temp_a3 = gSaveContext.save.time - temp_a0;
        temp_a2 = this->unk_146 - temp_a0;
        bellDiff = this->lastBellTime - this->nextBellTime;
        new_var = gSaveContext.save.time - this->nextBellTime;

        if ((temp_a3 * temp_a2) <= 0) {
            gSaveContext.unk_3CA7 = 1;
            if (play->actorCtx.flags & ACTORCTX_FLAG_PICTO_BOX_ON) {
                play->actorCtx.flags &= ~ACTORCTX_FLAG_PICTO_BOX_ON;
            }

            if (temp_a0 != CLOCK_TIME(6, 0)) {
                func_80A41FA4(this, play);
            } else if (temp_a0 == CLOCK_TIME(6, 0)) {
                if (CURRENT_DAY == 3) {
                    Interface_StartMoonCrash(play);
                    Actor_Kill(&this->actor);
                    SET_EVENTINF(EVENTINF_17);
                } else if (((sCsIdList[this->csIdIndex] < 0) || (play->actorCtx.flags & ACTORCTX_FLAG_1)) &&
                           (CURRENT_DAY != 3)) {
                    func_80A41FA4(this, play);
                } else {
                    gSaveContext.screenScale = 0.0f;
                    Play_SetRespawnData(&play->state, RESPAWN_MODE_DOWN, Entrance_CreateFromSpawn(0), player->unk_3CE,
                                        PLAYER_PARAMS(0xFF, PLAYER_INITMODE_B), &player->unk_3C0, player->unk_3CC);
                    func_80169EFC(&play->state);
                    if (player->stateFlags1 & PLAYER_STATE1_800000) {
                        EnHorse* rideActor = (EnHorse*)player->rideActor;

                        if ((rideActor->type == HORSE_TYPE_EPONA) || (rideActor->type == HORSE_TYPE_2)) {
                            if (CURRENT_DAY < 3) {
                                gHorseIsMounted = true;
                            } else {
                                gHorseIsMounted = false;
                            }
                        }
                    }

                    gSaveContext.respawnFlag = -4;
                    SET_EVENTINF(EVENTINF_TRIGGER_DAYTELOP);
                    Actor_Kill(&this->actor);
                }
            }

            if ((sCsIdList[this->csIdIndex] >= 0) && !(play->actorCtx.flags & ACTORCTX_FLAG_1)) {
                player->stateFlags1 |= PLAYER_STATE1_200;
                this->unk_146 = gSaveContext.save.time;
            } else {
                if (this->csIdIndex == 0) {
                    this->csIdIndex = 1;
                } else {
                    this->csIdIndex = 0;
                }

                this->unk_146 = gSaveContext.save.time += CLOCK_TIME_MINUTE;
            }
        } else if ((new_var * bellDiff) <= 0) {
            Audio_PlaySfx_BigBells(&this->actor.projectedPos, (this->actor.params >> 5) & 0xF);
            this->lastBellTime = gSaveContext.save.time;

            if (CURRENT_DAY == 3) {
                if ((this->nextBellTime == CLOCK_TIME(0, 0)) &&
                    ((gSaveContext.save.saveInfo.inventory.items[SLOT_OCARINA] == ITEM_NONE) ||
                     (play->sceneId == SCENE_CLOCKTOWER))) {
                    s32 playerParams;
                    u32 entrance = gSaveContext.save.entrance;

                    if ((play->actorCtx.flags & ACTORCTX_FLAG_1)) {
                        playerParams = PLAYER_PARAMS(0xFF, PLAYER_INITMODE_TELESCOPE);
                    } else {
                        playerParams = PLAYER_PARAMS(0xFF, PLAYER_INITMODE_B);
                    }
                    Play_SetRespawnData(&play->state, RESPAWN_MODE_RETURN, entrance, player->unk_3CE, playerParams,
                                        &player->unk_3C0, player->unk_3CC);

                    if ((play->sceneId == SCENE_TENMON_DAI) || (play->sceneId == SCENE_00KEIKOKU)) {
                        play->nextEntrance = ENTRANCE(TERMINA_FIELD, 0);
                    } else {
                        play->nextEntrance = ENTRANCE(SOUTH_CLOCK_TOWN, 0);
                    }
                    gSaveContext.nextCutsceneIndex = 0xFFF1;
                    play->transitionTrigger = TRANS_TRIGGER_START;
                    play->transitionType = TRANS_TYPE_FADE_BLACK;
                    player->stateFlags1 |= PLAYER_STATE1_200;
                    Actor_Kill(&this->actor);
                }
                func_80A42198(this);
            } else {
                func_80A425E4(this, play);
            }
        }
    }
}

void func_80A42F20(EnTest4* this, PlayState* play) {
    if (!this->transitionCsTimer) {
        if (sCurCsId >= 0) {
            if (!CutsceneManager_IsNext(sCurCsId)) {
                CutsceneManager_Queue(sCurCsId);
            } else {
                CutsceneManager_Start(sCurCsId, &this->actor);
                this->transitionCsTimer = 1;
            }
        } else {
            this->transitionCsTimer = 1;
        }
    } else if (this->transitionCsTimer < 60) {
        this->transitionCsTimer++;
        if (this->transitionCsTimer == 10) {
            if (this->csIdIndex == 0) {
                Audio_PlaySfx(NA_SE_EV_CHICKEN_CRY_M);
            } else {
                Audio_PlaySfx_2(NA_SE_EV_DOG_CRY_EVENING);
            }
        }
        if (this->transitionCsTimer == 60) {
            Player* player = GET_PLAYER(play);

            gSaveContext.save.time += CLOCK_TIME_MINUTE;
            this->unk_146 = gSaveContext.save.time;
            play->numSetupActors = -play->numSetupActors;
            player->stateFlags1 &= ~PLAYER_STATE1_200;
        }
    } else {
        this->actionFunc = func_80A42AB8;
        if (this->csIdIndex == 0) {
            this->csIdIndex = 1;
        } else {
            this->csIdIndex = 0;
        }

        if (sCurCsId >= 0) {
            CutsceneManager_Stop(sCurCsId);
        }

        gSaveContext.hudVisibility = HUD_VISIBILITY_IDLE;
        CLEAR_EVENTINF(EVENTINF_17);
        Interface_SetHudVisibility(HUD_VISIBILITY_ALL);
    }
}

void func_80A430C8(EnTest4* this, PlayState* play) {
    if ((CURRENT_DAY == 2) && (gSaveContext.save.time >= CLOCK_TIME(7, 0)) &&
        (gSaveContext.save.time < CLOCK_TIME(17, 30)) && (play->envCtx.unk_F2[2] == 0)) {
        // rain?

        gWeatherMode = 1;
        func_800FD78C(play);
        play->envCtx.unk_E3 = 1;
        play->envCtx.unk_F2[0] = 0x3C;
    } else {
        if (play->envCtx.unk_F2[0] != 0) {
            if ((play->state.frames % 4) == 0) {
                play->envCtx.unk_F2[0]--;
                if ((play->envCtx.unk_F2[0]) == 8) {
                    func_800FD858(play);
                }
            }
        }
    }

    if (gWeatherMode == 1) {
        this->state = TEST4_STATE_1;
    }
}

void func_80A431C8(EnTest4* this, PlayState* play) {
    if (((gSaveContext.save.time >= CLOCK_TIME(17, 30)) && (gSaveContext.save.time < CLOCK_TIME(23, 0)) &&
         (play->envCtx.unk_F2[0] != 0)) ||
        (play->envCtx.unk_F2[2] != 0)) {
        gWeatherMode = 0;
        play->envCtx.unk_E3 = 2;
    }

    if (gWeatherMode == 0) {
        this->state = TEST4_STATE_0;
    }
}

void func_80A4323C(EnTest4* this, PlayState* play) {
    s32 temp_v0 = (this->actor.params >> 0xA) * 0x64;

    if (temp_v0 > 0) {
        D_801F4E7A = temp_v0;
    }
}

void EnTest4_Update(Actor* thisx, PlayState* play) {
    EnTest4* this = THIS;
    Player* player = GET_PLAYER(play);

    if (!(player->stateFlags1 & PLAYER_STATE1_2)) {
        this->actionFunc(this, play);

        if (func_800FE4B8(play) != 0) {
            switch (this->state) {
                case TEST4_STATE_0:
                    func_80A430C8(this, play);
                    break;
                case TEST4_STATE_1:
                    func_80A431C8(this, play);
                    break;
            }
        }
        func_80A4323C(this, play);
    }
}
