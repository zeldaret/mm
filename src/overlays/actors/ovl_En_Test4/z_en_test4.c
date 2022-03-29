/*
 * File: z_en_test4.c
 * Overlay: ovl_En_Test4
 * Description: Three-Day Timer
 */

#include "z_en_test4.h"
#include "overlays/gamestates/ovl_daytelop/z_daytelop.h"
#include "overlays/actors/ovl_En_Horse/z_en_horse.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20 | ACTOR_FLAG_100000)

#define THIS ((EnTest4*)thisx)

void EnTest4_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTest4_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTest4_Update(Actor* thisx, GlobalContext* globalCtx);

void func_80A42AB8(EnTest4* this, GlobalContext* globalCtx);
void func_80A42F20(EnTest4* this, GlobalContext* globalCtx);

const ActorInit En_Test4_InitVars = {
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

static s16 sCutscenes[2];
static s16 sCurrentCs;

void func_80A41D70(EnTest4* this, GlobalContext* globalCtx) {
    if (this->unk_144 != 0) {
        func_80151A68(globalCtx, sNightMessages1[CURRENT_DAY - 1]);
    } else if ((sCutscenes[this->unk_144] < 0) || ((globalCtx->actorCtx.unk5 & 2) != 0)) {
        if (globalCtx->actorCtx.unk5 & 2) {
            Sram_IncrementDay();
            gSaveContext.save.time = CLOCK_TIME(6, 0);
            func_80151A68(globalCtx, sDayMessages1[CURRENT_DAY - 1]);
        } else {
            this->unk_144 = 0;
            this->unk_146 = gSaveContext.save.time += CLOCK_TIME_MINUTE;
        }

        func_8010EE74(globalCtx, CURRENT_DAY);
        D_801BDBC8 = 0xFE;
        func_800FB758(globalCtx);
        func_800FEAF4(&globalCtx->envCtx);
        this->actionFunc = func_80A42AB8;
    }

    if (gSaveContext.cutsceneTrigger == 0) {
        if ((sCutscenes[this->unk_144] >= 0) && !(globalCtx->actorCtx.unk5 & 2)) {
            this->actionFunc = func_80A42F20;
            sCurrentCs = sCutscenes[this->unk_144];
            this->transitionCsTimer = 0;
            gSaveContext.eventInf[1] |= 0x80;
        } else if (this->unk_144 == 0) {
            play_sound(NA_SE_EV_CHICKEN_CRY_M);
        } else {
            func_8019F128(NA_SE_EV_DOG_CRY_EVENING);
        }
    } else {
        this->actionFunc = func_80A42AB8;
        if (this->unk_144 == 0) {
            this->unk_144 = 1;
        } else {
            this->unk_144 = 0;
        }

        this->unk_146 = gSaveContext.save.time += CLOCK_TIME_MINUTE;
    }
}

void func_80A41FA4(EnTest4* this, GlobalContext* globalCtx) {
    if (this->unk_144 != 0) {
        func_80151A68(globalCtx, sNightMessages2[CURRENT_DAY - 1]);
    } else if ((sCutscenes[this->unk_144] < 0) || ((globalCtx->actorCtx.unk5 & 2) != 0)) {
        Sram_IncrementDay();
        gSaveContext.save.time = CLOCK_TIME(6, 0);
        func_8010EE74(globalCtx, CURRENT_DAY);
        func_80151A68(globalCtx, sDayMessages2[CURRENT_DAY - 1]);
        D_801BDBC8 = 0xFE;
        func_800FB758(globalCtx);
        func_800FEAF4(&globalCtx->envCtx);
        this->actionFunc = func_80A42AB8;
    }

    if (gSaveContext.cutsceneTrigger == 0) {
        if ((sCutscenes[this->unk_144] >= 0) && ((globalCtx->actorCtx.unk5 & 2) == 0)) {
            this->actionFunc = func_80A42F20;
            sCurrentCs = sCutscenes[this->unk_144];
            this->transitionCsTimer = 0;
            gSaveContext.eventInf[1] |= 0x80;
        } else if (this->unk_144 == 0) {
            play_sound(NA_SE_EV_CHICKEN_CRY_M);
        } else {
            func_8019F128(NA_SE_EV_DOG_CRY_EVENING);
        }
    } else {
        this->actionFunc = func_80A42AB8;
        if (this->unk_144 == 0) {
            this->unk_144 = 1;
        } else {
            this->unk_144 = 0;
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
void func_80A425E4(EnTest4* this, GlobalContext* globalCtx) {
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

        if ((sCutscenes[this->unk_144] < 0) || ((globalCtx->actorCtx.unk5 & 2) != 0) || (CURRENT_DAY == 3) ||
            (gSaveContext.save.time >= CLOCK_TIME(17, 0))) {
            gSaveContext.screenScale = 1000.0f;
        }
        if (gSaveContext.screenScale != 1000.0f) {
            gSaveContext.screenScaleFlag = 1;
        }
    }
}

void EnTest4_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 dayTemp;
    EnTest4* this = THIS;
    Player* player = GET_PLAYER(globalCtx);
    s8 temp_v0 = this->actor.cutscene;

    sCutscenes[0] = temp_v0;
    if (temp_v0 >= 0) {
        ActorCutscene* temp_v0_2 = ActorCutscene_GetCutscene(sCutscenes[0]);

        gSaveContext.eventInf[5] |= 0x4;
        sCutscenes[1] = temp_v0_2->additionalCutscene;
    } else {
        gSaveContext.eventInf[5] &= (u8)~0x4;
        sCutscenes[1] = sCutscenes[0];
    }

    if (sIsLoaded || (gSaveContext.eventInf[2] & 0x80)) {
        Actor_MarkForDeath(&this->actor);
    } else {
        sIsLoaded = true;
        this->actor.room = -1;
        gSaveContext.screenScaleFlag = 0;
        gSaveContext.screenScale = 1000.0f;
        if (CURRENT_DAY == 0) {
            if (gSaveContext.save.time < CLOCK_TIME(6, 1)) {
                gSaveContext.save.time = CLOCK_TIME(6, 0);
                gSaveContext.gameMode = 0;
                {
                    GameState* state = &globalCtx->state;
                    state->running = false;
                }
                SET_NEXT_GAMESTATE(&globalCtx->state, Daytelop_Init, DaytelopContext);
                if (this && this && this) {}
                this->unk_144 = 1;
                gSaveContext.save.time = CLOCK_TIME(6, 0);
                Actor_MarkForDeath(&this->actor);
            } else {
                gSaveContext.save.day = 1;
                dayTemp = gSaveContext.save.day;
                gSaveContext.save.daysElapsed = dayTemp;
                this->unk_144 = 1;
                this->unk_146 = gSaveContext.save.time;
                this->actionFunc = func_80A42AB8;
            }
        } else if (gSaveContext.save.time == CLOCK_TIME(6, 0)) {
            this->unk_144 = 0;
            func_80A41D70(this, globalCtx);
            if ((gSaveContext.cutsceneTrigger == 0) && (sCutscenes[this->unk_144] >= 0) &&
                !(globalCtx->actorCtx.unk5 & 2)) {
                player->stateFlags1 |= 0x200;
            }
        } else {
            if ((gSaveContext.save.time > CLOCK_TIME(18, 0)) || (gSaveContext.save.time < CLOCK_TIME(6, 0))) {
                this->unk_144 = 0;
            } else {
                this->unk_144 = 1;
            }
            this->unk_146 = gSaveContext.save.time;
            this->actionFunc = func_80A42AB8;
        }
    }

    if (CURRENT_DAY == 3) {
        func_80A42198(this);
    } else {
        func_80A425E4(this, globalCtx);
    }

    this->lastBellTime = gSaveContext.save.time;
    if ((sCutscenes[this->unk_144] < 0) || (globalCtx->actorCtx.unk5 & 2)) {
        gSaveContext.screenScaleFlag = 0;
        gSaveContext.screenScale = 1000.0f;
    }
}

void EnTest4_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void func_80A42AB8(EnTest4* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if ((globalCtx->unk_18B4A == 0) && !Play_InCsMode(globalCtx) && (globalCtx->numSetupActors <= 0) &&
        (globalCtx->roomCtx.unk31 == 0) && (func_8016A168() == 0)) {
        s16 temp_a2;
        u16 temp_a0 = D_80A43364[this->unk_144];
        s16 temp_a3;
        s16 bellDiff;
        s16 new_var;

        temp_a3 = gSaveContext.save.time - temp_a0;
        temp_a2 = this->unk_146 - temp_a0;
        bellDiff = this->lastBellTime - this->nextBellTime;
        new_var = gSaveContext.save.time - this->nextBellTime;

        if ((temp_a3 * temp_a2) <= 0) {
            gSaveContext.unk_3CA7 = 1;
            if (globalCtx->actorCtx.unk5 & 0x4) {
                globalCtx->actorCtx.unk5 &= ~0x4;
            }

            if (temp_a0 != CLOCK_TIME(6, 0)) {
                func_80A41FA4(this, globalCtx);
            } else if (temp_a0 == CLOCK_TIME(6, 0)) {
                if (CURRENT_DAY == 3) {
                    func_8011C808(globalCtx);
                    Actor_MarkForDeath(&this->actor);
                    gSaveContext.eventInf[1] |= 0x80;
                } else if (((sCutscenes[this->unk_144] < 0) || (globalCtx->actorCtx.unk5 & 2)) && CURRENT_DAY != 3) {
                    func_80A41FA4(this, globalCtx);
                } else {
                    gSaveContext.screenScale = 0.0f;
                    Play_SetRespawnData(&globalCtx->state, RESTART_MODE_DOWN, Entrance_CreateIndexFromSpawn(0),
                                        player->unk_3CE, 0xBFF, &player->unk_3C0, player->unk_3CC);
                    func_80169EFC(&globalCtx->state);
                    if (player->stateFlags1 & 0x800000) {
                        EnHorse* rideActor = (EnHorse*)player->rideActor;

                        if ((rideActor->type == HORSE_EPONA) || (rideActor->type == HORSE_2)) {
                            if (CURRENT_DAY < 3) {
                                D_801BDA9C = 1;
                            } else {
                                D_801BDA9C = 0;
                            }
                        }
                    }

                    gSaveContext.respawnFlag = -4;
                    gSaveContext.eventInf[2] |= 0x80;
                    Actor_MarkForDeath(&this->actor);
                }
            }

            if ((sCutscenes[this->unk_144] >= 0) && ((globalCtx->actorCtx.unk5 & 2) == 0)) {
                player->stateFlags1 |= 0x200;
                this->unk_146 = gSaveContext.save.time;
            } else {
                if (this->unk_144 == 0) {
                    this->unk_144 = 1;
                } else {
                    this->unk_144 = 0;
                }

                this->unk_146 = gSaveContext.save.time += CLOCK_TIME_MINUTE;
            }
        } else if ((new_var * bellDiff) <= 0) {
            func_801A0124(&this->actor.projectedPos, (this->actor.params >> 5) & 0xF);
            this->lastBellTime = gSaveContext.save.time;

            if (CURRENT_DAY == 3) {
                if ((this->nextBellTime == CLOCK_TIME(0, 0)) &&
                    ((gSaveContext.save.inventory.items[SLOT_OCARINA] == ITEM_NONE) ||
                     (globalCtx->sceneNum == SCENE_CLOCKTOWER))) {
                    s32 playerParams;
                    u32 entranceIndex = gSaveContext.save.entranceIndex;

                    if ((globalCtx->actorCtx.unk5 & 2)) {
                        playerParams = 0xCFF;
                    } else {
                        playerParams = 0xBFF;
                    }
                    Play_SetRespawnData(&globalCtx->state, RESTART_MODE_RETURN, entranceIndex, player->unk_3CE,
                                        playerParams, &player->unk_3C0, player->unk_3CC);

                    if ((globalCtx->sceneNum == SCENE_TENMON_DAI) || (globalCtx->sceneNum == SCENE_00KEIKOKU)) {
                        globalCtx->nextEntranceIndex = 0x5400;
                    } else {
                        globalCtx->nextEntranceIndex = 0xD800;
                    }
                    gSaveContext.nextCutsceneIndex = 0xFFF1;
                    globalCtx->sceneLoadFlag = 0x14;
                    globalCtx->unk_1887F = 2;
                    player->stateFlags1 |= 0x200;
                    Actor_MarkForDeath(&this->actor);
                }
                func_80A42198(this);
            } else {
                func_80A425E4(this, globalCtx);
            }
        }
    }
}

void func_80A42F20(EnTest4* this, GlobalContext* globalCtx) {
    if (!this->transitionCsTimer) {
        if (sCurrentCs >= 0) {
            if (ActorCutscene_GetCanPlayNext(sCurrentCs) == 0) {
                ActorCutscene_SetIntentToPlay(sCurrentCs);
            } else {
                ActorCutscene_Start(sCurrentCs, &this->actor);
                this->transitionCsTimer = 1;
            }
        } else {
            this->transitionCsTimer = 1;
        }
    } else if (this->transitionCsTimer < 60) {
        this->transitionCsTimer++;
        if (this->transitionCsTimer == 10) {
            if (this->unk_144 == 0) {
                play_sound(NA_SE_EV_CHICKEN_CRY_M);
            } else {
                func_8019F128(NA_SE_EV_DOG_CRY_EVENING);
            }
        }
        if (this->transitionCsTimer == 60) {
            Player* player = GET_PLAYER(globalCtx);

            gSaveContext.save.time += CLOCK_TIME_MINUTE;
            this->unk_146 = gSaveContext.save.time;
            globalCtx->numSetupActors = -globalCtx->numSetupActors;
            player->stateFlags1 &= ~0x200;
        }
    } else {
        this->actionFunc = func_80A42AB8;
        if (this->unk_144 == 0) {
            this->unk_144 = 1;
        } else {
            this->unk_144 = 0;
        }

        if (sCurrentCs >= 0) {
            ActorCutscene_Stop(sCurrentCs);
        }
        gSaveContext.unk_3F22 = 0;
        gSaveContext.eventInf[1] &= (u8)~0x80;
        Interface_ChangeAlpha(50);
    }
}

void func_80A430C8(EnTest4* this, GlobalContext* globalCtx) {
    if ((CURRENT_DAY == 2) && (gSaveContext.save.time >= CLOCK_TIME(7, 0)) &&
        (gSaveContext.save.time < CLOCK_TIME(17, 30)) && (globalCtx->envCtx.unk_F2[2] == 0)) {
        // rain?

        D_801BDBB0 = 1;
        func_800FD78C(globalCtx);
        globalCtx->envCtx.unk_E3 = 1;
        globalCtx->envCtx.unk_F2[0] = 0x3C;
    } else {
        if (globalCtx->envCtx.unk_F2[0] != 0) {
            if ((globalCtx->state.frames % 4) == 0) {
                globalCtx->envCtx.unk_F2[0]--;
                if ((globalCtx->envCtx.unk_F2[0]) == 8) {
                    func_800FD858(globalCtx);
                }
            }
        }
    }

    if (D_801BDBB0 == 1) {
        this->state = TEST4_STATE_1;
    }
}

void func_80A431C8(EnTest4* this, GlobalContext* globalCtx) {
    if (((gSaveContext.save.time >= CLOCK_TIME(17, 30)) && (gSaveContext.save.time < CLOCK_TIME(23, 0)) &&
         (globalCtx->envCtx.unk_F2[0] != 0)) ||
        (globalCtx->envCtx.unk_F2[2] != 0)) {
        D_801BDBB0 = 0;
        globalCtx->envCtx.unk_E3 = 2;
    }

    if (D_801BDBB0 == 0) {
        this->state = TEST4_STATE_0;
    }
}

void func_80A4323C(EnTest4* this, GlobalContext* globalCtx) {
    s32 temp_v0 = (this->actor.params >> 0xA) * 0x64;

    if (temp_v0 > 0) {
        D_801F4E7A = temp_v0;
    }
}

void EnTest4_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnTest4* this = THIS;
    Player* player = GET_PLAYER(globalCtx);

    if (!(player->stateFlags1 & 2)) {
        this->actionFunc(this, globalCtx);

        if (func_800FE4B8(globalCtx) != 0) {
            switch (this->state) {
                case TEST4_STATE_0:
                    func_80A430C8(this, globalCtx);
                    break;
                case TEST4_STATE_1:
                    func_80A431C8(this, globalCtx);
                    break;
            }
        }
        func_80A4323C(this, globalCtx);
    }
}
