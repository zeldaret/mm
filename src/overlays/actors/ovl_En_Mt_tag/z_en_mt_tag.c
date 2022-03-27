/*
 * File: z_en_mt_tag.c
 * Overlay: ovl_En_Mt_tag
 * Description: Controls the Goron Race minigame
 */

#include "z_en_mt_tag.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((EnMttag*)thisx)

void EnMttag_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMttag_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMttag_Update(Actor* thisx, GlobalContext* globalCtx);

void EnMttag_ShowIntroCutscene(EnMttag* this, GlobalContext* globalCtx);
void EnMttag_WaitForIntroCutsceneToEnd(EnMttag* this, GlobalContext* globalCtx);
void EnMttag_RaceStart(EnMttag* this, GlobalContext* globalCtx);
void EnMttag_Race(EnMttag* this, GlobalContext* globalCtx);
void EnMttag_RaceFinish(EnMttag* this, GlobalContext* globalCtx);
void EnMttag_PotentiallyRestartRace(EnMttag* this, GlobalContext* globalCtx);
void EnMttag_HandleCantWinChoice(EnMttag* this, GlobalContext* globalCtx);

typedef enum {
    GORON_RACE_CHEAT_NO_CHEATING,
    GORON_RACE_CHEAT_FALSE_START,
    GORON_RACE_CHEAT_TRYING_TO_REACH_GOAL_FROM_BEHIND,
} PlayerCheatStatus;

const ActorInit En_Mt_tag_InitVars = {
    ACTOR_EN_MT_TAG,
    ACTORCAT_BG,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnMttag),
    (ActorFunc)EnMttag_Init,
    (ActorFunc)EnMttag_Destroy,
    (ActorFunc)EnMttag_Update,
    (ActorFunc)NULL,
};

static s32 sStartingCheckpointPerSceneExitIndex[] = {
    0, 0, 0, 0, 1, 9, 12, 16, 19, 22, 26, 29, 30, 32, 34, 36, 39, 42, 45,
};

// The Y-positions here are never used by any part of this actor.
static Vec3f sCheckpointPositions[] = {
    { -105.0f, 1000.0f, -240.0f },   { -1751.0f, 1000.0f, -240.0f },  { -3138.0f, 1000.0f, -74.0f },
    { -4617.0f, 1000.0f, 277.0f },   { -5060.0f, 1000.0f, 388.0f },   { -5412.0f, 1000.0f, 573.0f },
    { -5523.0f, 1000.0f, 1035.0f },  { -5393.0f, 1000.0f, 1405.0f },  { -5060.0f, 1000.0f, 1553.0f },
    { -3933.0f, 1000.0f, 1479.0f },  { -3212.0f, 1000.0f, 1461.0f },  { -2805.0f, 1000.0f, 1645.0f },
    { -2638.0f, 1000.0f, 2071.0f },  { -2823.0f, 1000.0f, 2422.0f },  { -3212.0f, 1000.0f, 2607.0f },
    { -3785.0f, 1000.0f, 2977.0f },  { -4321.0f, 1000.0f, 3501.0f },  { -4654.0f, 1000.0f, 4185.0f },
    { -4802.0f, 1000.0f, 4779.0f },  { -4672.0f, 1000.0f, 5426.0f },  { -4339.0f, 1000.0f, 6037.0f },
    { -3748.0f, 1000.0f, 6314.0f },  { -2749.0f, 1000.0f, 6478.0f },  { -2453.0f, 1000.0f, 6922.0f },
    { -2269.0f, 1000.0f, 7754.0f },  { -2453.0f, 1000.0f, 8309.0f },  { -3008.0f, 1000.0f, 8438.0f },
    { -3304.0f, 1000.0f, 8179.0f },  { -3600.0f, 1000.0f, 7606.0f },  { -3600.0f, 1000.0f, 6885.0f },
    { -3618.0f, 1000.0f, 4392.0f },  { -3600.0f, 1000.0f, 3855.0f },  { -3396.0f, 1000.0f, 3189.0f },
    { -3396.0f, 1000.0f, 2283.0f },  { -3600.0f, 1000.0f, 818.0f },   { -3803.0f, 1000.0f, -88.0f },
    { -4543.0f, 1000.0f, -2457.0f }, { -4543.0f, 1000.0f, -2938.0f }, { -4543.0f, 1000.0f, -3530.0f },
    { -4284.0f, 1000.0f, -4333.0f }, { -3581.0f, 1000.0f, -4795.0f }, { -2805.0f, 1000.0f, -4850.0f },
    { -1825.0f, 1000.0f, -4703.0f }, { -1326.0f, 1000.0f, -4166.0f }, { -1122.0f, 1000.0f, -3186.0f },
    { -1085.0f, 1000.0f, -2059.0f }, { -1067.0f, 1000.0f, -912.0f },
};

/**
 * Returns true if the specified position is in the finish line.
 * The range extends a little bit beyond the finish line's in-game visual.
 */
s32 EnMttag_IsInFinishLine(Vec3f* pos) {
    return Math3D_XZBoundCheck(-1261.0f, -901.0f, -1600.0f, -1520.0f, pos->x, pos->z);
}

/**
 * Returns a value in PlayerCheatStatus that indicates if the player is cheating
 * and, if so, what kind of cheating the player is performing.
 */
s32 EnMttag_CheckPlayerCheatStatus(Vec3f* pos) {
    if (!(gSaveContext.eventInf[1] & 1)) {
        if (Math3D_XZBoundCheck(-466.0f, -386.0f, -687.0f, 193.0f, pos->x, pos->z)) {
            // The race hasn't started yet, but the player is beyond the starting line.
            return GORON_RACE_CHEAT_FALSE_START;
        }
    } else if (Math3D_XZBoundCheck(-1127.0f, -1007.0f, -867.0f, -787.0f, pos->x, pos->z)) {
        // The goal is actually quite close to the start, just behind a large wall.
        // This checks if the player is in an area "behind" the goal that is not accessible
        // in normal play; it can only be reached by climbing the wall somehow. Perhaps they
        // were worried that players would find a way to climb the wall with a glitch, or
        // perhaps they just wanted to punish people using cheat codes.
        return GORON_RACE_CHEAT_TRYING_TO_REACH_GOAL_FROM_BEHIND;
    }
    return GORON_RACE_CHEAT_NO_CHEATING;
}

/**
 * This function tries to find all four Race Gorons present in the racetrack.
 * If it finds them, it stores a pointer to each one in the actor's struct.
 * Returns true if all four Race Gorons are found.
 */
s32 EnMttag_AreFourRaceGoronsPresent(EnMttag* this, GlobalContext* globalCtx) {
    Actor* actor = NULL;
    s32 i = 0;
    s32 areGoronsPresent;

    do {
        actor = SubS_FindActor(globalCtx, actor, ACTORCAT_NPC, ACTOR_EN_RG);
        if (actor != NULL) {
            this->raceGorons[i] = (EnRg*)actor;
            i++;
        } else if ((actor == NULL) || (actor->next == NULL)) {
            break;
        }

        actor = actor->next;
    } while (i < ARRAY_COUNT(this->raceGorons));

    if (i < ARRAY_COUNT(this->raceGorons)) {
        areGoronsPresent = false;
    } else {
        areGoronsPresent = true;
    }

    return areGoronsPresent;
}

/**
 * Returns the checkpoint number for the supplied actor.
 * At the start of the race, all race entrants are at checkpoint 1, and their
 * checkpoint number gradually increases as they move forward through the racetrack.
 * The player can have a checkpoint number of -1 if they move far enough backwards
 * from the starting line.
 */
s32 EnMttag_GetCurrentCheckpoint(Actor* actor, GlobalContext* globalCtx, s32* upcomingCheckpoint,
                                 f32* outPerpendicularPointX, f32* outPerpendicularPointZ) {
    s32 curentCheckpoint = -1;
    s32 hasSetCurrentCheckpointOnce = false;
    f32 minLineLengthSq = 0.0f;
    s32 sceneExitIndex;
    f32 perpendicularPointX;
    f32 perpendicularPointZ;
    f32 lineLenSq;
    s32 checkpointIterator;

    // The Goron Racetrack is configured such that the sceneExitIndex for any given floor polygon
    // gradually increases as you move forward through the racetrack.
    sceneExitIndex = SurfaceType_GetSceneExitIndex(&globalCtx->colCtx, actor->floorPoly, actor->floorBgId);
    if ((sceneExitIndex < 4) || (sceneExitIndex >= 19)) {
        //! @bug - upcomingCheckpoint is not initialized here
        return -1;
    }

    checkpointIterator = sStartingCheckpointPerSceneExitIndex[sceneExitIndex];

    // Iterates through all possible checkpoints that are associated with this sceneExitIndex.
    do {
        if ((Math3D_PointDistToLine2D(
                actor->world.pos.x, actor->world.pos.z, (&sCheckpointPositions[checkpointIterator])[-1].x,
                (&sCheckpointPositions[checkpointIterator])[-1].z, (&sCheckpointPositions[checkpointIterator])[1].x,
                (&sCheckpointPositions[checkpointIterator])[1].z, &perpendicularPointX, &perpendicularPointZ,
                &lineLenSq)) &&
            (!hasSetCurrentCheckpointOnce || ((curentCheckpoint + 1) == checkpointIterator) ||
             (lineLenSq < minLineLengthSq))) {
            minLineLengthSq = lineLenSq;
            curentCheckpoint = checkpointIterator;
            *outPerpendicularPointX = perpendicularPointX;
            *outPerpendicularPointZ = perpendicularPointZ;
            hasSetCurrentCheckpointOnce = true;
        }
        checkpointIterator++;
    } while (checkpointIterator < sStartingCheckpointPerSceneExitIndex[sceneExitIndex + 1]);

    *upcomingCheckpoint = curentCheckpoint + 1;
    return curentCheckpoint;
}

/**
 * Returns true if the player is almost certainly going to lose the race.
 * Specifically, it checks if the player's current checkpoint is 24 or more
 * checkpoints behind the leading racer. This value was probably chosen because
 * falling off the wooden bridge in the middle of the track can set the player
 * back up to 23 checkpoints.
 *
 * This function also has the side effect of updating the number of checkpoints
 * ahead of the player each Race Goron is.
 */
s32 EnMttag_UpdateCheckpoints(EnMttag* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    EnRg* rg;
    s32 currentCheckpoints[5];
    s32 upcomingCheckpoints[5];
    f32 perpendicularPointsX[5];
    f32 perpendicularPointsZ[5];
    s32 highestCurrentCheckpoint;
    s32 i;
    s32 playerIsLikelyToLose = false;

    highestCurrentCheckpoint = -1;
    currentCheckpoints[0] = EnMttag_GetCurrentCheckpoint(&player->actor, globalCtx, &upcomingCheckpoints[0],
                                                         &perpendicularPointsX[0], &perpendicularPointsZ[0]);
    for (i = 1; i < ARRAY_COUNT(this->raceGorons) + 1; i++) {
        currentCheckpoints[i] =
            EnMttag_GetCurrentCheckpoint(&this->raceGorons[i - 1]->actor, globalCtx, &upcomingCheckpoints[i],
                                         &perpendicularPointsX[i], &perpendicularPointsZ[i]);
        if (highestCurrentCheckpoint < currentCheckpoints[i]) {
            highestCurrentCheckpoint = currentCheckpoints[i];
        }
    }

    for (i = 1; i < ARRAY_COUNT(this->raceGorons) + 1; i++) {
        rg = this->raceGorons[i - 1];

        // Because of the bug described in EnMttag_GetCurrentCheckpoint, these values may not be initialized.
        //! @bug When initialized, this check is pointless because upcomingCheckpoint is always 0 or higher.
        if ((upcomingCheckpoints[i] != -1) && (upcomingCheckpoints[0] != -1)) {
            rg->numCheckpointsAheadOfPlayer = (upcomingCheckpoints[i] - upcomingCheckpoints[0]);
        } else {
            rg->numCheckpointsAheadOfPlayer = 0;
        }
    }

    if ((currentCheckpoints[0] > 0) && (currentCheckpoints[0] < highestCurrentCheckpoint) &&
        (player->actor.bgCheckFlags & 1) && ((highestCurrentCheckpoint - currentCheckpoints[0]) >= 24)) {
        playerIsLikelyToLose = true;
    }

    return playerIsLikelyToLose;
}

/**
 * Exits the race and returns the player back to "normal" gameplay.
 * Whether the player won or lost the race is determined by arg1 and nextTransition.
 */
s32 EnMttag_ExitRace(GlobalContext* globalCtx, s32 arg1, s32 nextTransition) {
    CUR_FORM_EQUIP(EQUIP_SLOT_B) = ITEM_SWORD_KOKIRI;
    globalCtx->nextEntranceIndex = 0xD020;
    if ((gSaveContext.save.weekEventReg[33] & 0x80)) {
        // Spring
        gSaveContext.nextCutsceneIndex = 0xFFF0;
    } else {
        // Winter
        gSaveContext.nextCutsceneIndex = 0;
    }

    globalCtx->sceneLoadFlag = 0x14;
    globalCtx->unk_1887F = arg1;
    gSaveContext.nextTransition = nextTransition;
    func_801477B4(globalCtx);
    return 1;
}

/**
 * Displays the text which says that the player has made a false start.
 */
void EnMttag_ShowFalseStartMessage(EnMttag* this, GlobalContext* globalCtx) {
    gSaveContext.unk_3DD0[4] = 0;
    Message_StartTextbox(globalCtx, 0xE95, NULL); // An entrant made a false start
    func_800B7298(globalCtx, &this->actor, 7);
    Audio_QueueSeqCmd(0x101400FF);
    this->actionFunc = EnMttag_PotentiallyRestartRace;
}

/**
 * Displays the text from the Goron Elder's child which tells the player that
 * they probably can't win the race.
 */
void EnMttag_ShowCantWinMessage(EnMttag* this, GlobalContext* globalCtx) {
    Message_StartTextbox(globalCtx, 0xE97, NULL); // You can't win now...
    func_800B7298(globalCtx, &this->actor, 7);
    this->actionFunc = EnMttag_HandleCantWinChoice;
}

/**
 * Shows the cutscene that pans over the race track and shows all five race entrants.
 */
void EnMttag_ShowIntroCutscene(EnMttag* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->actor.cutscene, &this->actor);
        this->actionFunc = EnMttag_WaitForIntroCutsceneToEnd;
    } else {
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    }
}

/**
 * When the intro cutscene concludes, this sets the weekEventReg to prevent it
 * from showing again and starts the race.
 */
void EnMttag_WaitForIntroCutsceneToEnd(EnMttag* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCurrentIndex() != this->actor.cutscene) {
        gSaveContext.save.weekEventReg[12] |= 2;
        this->actionFunc = EnMttag_RaceStart;
    }
}

/**
 * Handles the race from when the Gorons are first lined up at the
 * starting block to when the countdown finishes.
 */
void EnMttag_RaceStart(EnMttag* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 playerCheatStatus;

    if (this->raceInitialized == true) {
        playerCheatStatus = EnMttag_CheckPlayerCheatStatus(&player->actor.world.pos);
        if (playerCheatStatus != GORON_RACE_CHEAT_NO_CHEATING) {
            if (playerCheatStatus == GORON_RACE_CHEAT_FALSE_START) {
                this->shouldRestartRace = true;
            } else {
                this->shouldRestartRace = false;
            }

            EnMttag_ShowFalseStartMessage(this, globalCtx);
            gSaveContext.eventInf[1] |= 8;
        } else {
            if (DECR(this->timer) == 60) {
                func_8010E9F0(4, 0);
                globalCtx->interfaceCtx.unk_280 = 1;
                Audio_QueueSeqCmd(NA_BGM_GORON_RACE | 0x8000);
                globalCtx->envCtx.unk_E4 = 0xFE;
                player->stateFlags1 &= ~0x20;
            } else if ((this->timer < 60) && (globalCtx->interfaceCtx.unk_280 == 8)) {
                this->timer = 0;
                gSaveContext.eventInf[1] |= 1;
                this->actionFunc = EnMttag_Race;
            }
        }
    } else {
        if (EnMttag_AreFourRaceGoronsPresent(this, globalCtx)) {
            this->raceInitialized = true;
        }
    }
}

/**
 * Returns true if any Race Goron is over the finish line.
 */
s32 EnMttag_IsAnyRaceGoronOverFinishLine(EnMttag* this) {
    s32 isAnyRaceGoronOverFinishLine = false;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(this->raceGorons); i++) {
        if ((EnMttag_IsInFinishLine(&this->raceGorons[i]->actor.world.pos)) &&
            (this->raceGorons[i]->actor.update != NULL)) {
            isAnyRaceGoronOverFinishLine = true;
            break;
        }
    }
    return isAnyRaceGoronOverFinishLine;
}

/**
 * Handles the race from when the countdown finishes to when
 * any race entrant crosses the finish line.
 */
void EnMttag_Race(EnMttag* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    Vec3f* playerPos = &player->actor.world.pos;
    s32 playerCheatStatus;

    if (EnMttag_IsInFinishLine(playerPos)) {
        gSaveContext.unk_3DD0[4] = 6;
        play_sound(NA_SE_SY_START_SHOT);
        Audio_QueueSeqCmd(NA_BGM_GORON_GOAL | 0x8000);
        this->timer = 55;
        gSaveContext.eventInf[1] |= 2;
        this->actionFunc = EnMttag_RaceFinish;
    } else if (EnMttag_IsAnyRaceGoronOverFinishLine(this)) {
        gSaveContext.unk_3DD0[4] = 6;
        play_sound(NA_SE_SY_START_SHOT);
        Audio_QueueSeqCmd(NA_BGM_GORON_GOAL | 0x8000);
        this->timer = 55;
        gSaveContext.eventInf[1] |= 4;
        this->actionFunc = EnMttag_RaceFinish;
    } else {
        playerCheatStatus = EnMttag_CheckPlayerCheatStatus(playerPos);
        if (playerCheatStatus != GORON_RACE_CHEAT_NO_CHEATING) {
            if (playerCheatStatus == GORON_RACE_CHEAT_FALSE_START) {
                this->shouldRestartRace = true;
            } else {
                this->shouldRestartRace = false;
            }

            EnMttag_ShowFalseStartMessage(this, globalCtx);
            gSaveContext.eventInf[1] |= 8;
        } else if ((EnMttag_UpdateCheckpoints(this, globalCtx)) && (this->timer == 0)) {
            EnMttag_ShowCantWinMessage(this, globalCtx);
            gSaveContext.eventInf[1] |= 8;
        }
    }
}

/**
 * Handles the race after any race entrant crosses the finish line.
 * This function simply waits for a bit before exiting the race.
 */
void EnMttag_RaceFinish(EnMttag* this, GlobalContext* globalCtx) {
    if (DECR(this->timer) == 0) {
        if ((gSaveContext.eventInf[1] & 2)) {
            // Player won
            EnMttag_ExitRace(globalCtx, 3, 3);
        } else {
            // A non-player Goron won
            EnMttag_ExitRace(globalCtx, 2, 2);
        }

        Actor_MarkForDeath(&this->actor);
    }
}

/**
 * Restarts the race if this->shouldRestartRace is true. Otherwise, it exits the race.
 * In practice, the only time this exits the race is if the player tries to cheat by
 * reaching the goal from behind.
 */
void EnMttag_PotentiallyRestartRace(EnMttag* this, GlobalContext* globalCtx) {
    u8 talkState = Message_GetState(&globalCtx->msgCtx);

    if (((talkState == 5 && Message_ShouldAdvance(globalCtx)) || talkState == 2)) {
        if (this->shouldRestartRace) {
            globalCtx->nextEntranceIndex = 0xD010;

            if (gSaveContext.save.weekEventReg[33] & 0x80) {
                // Spring
                gSaveContext.nextCutsceneIndex = 0xFFF0;
            } else {
                // Winter
                gSaveContext.nextCutsceneIndex = 0;
            }

            globalCtx->sceneLoadFlag = 0x14;
            globalCtx->unk_1887F = 2;
            gSaveContext.nextTransition = 2;
            func_801477B4(globalCtx);
            func_800B7298(globalCtx, &this->actor, 7);
            Parameter_AddMagic(globalCtx,
                               ((void)0, gSaveContext.unk_3F30) + (gSaveContext.save.playerData.doubleMagic * 48) + 48);

            gSaveContext.eventInf[1] &= (u8)~1;
            gSaveContext.eventInf[1] &= (u8)~2;
            gSaveContext.eventInf[1] &= (u8)~4;
            gSaveContext.eventInf[1] &= (u8)~8;
            gSaveContext.eventInf[2] = ((gSaveContext.eventInf[2] & 0xF) + 1) | (gSaveContext.eventInf[2] & 0xF0);
        } else {
            EnMttag_ExitRace(globalCtx, 2, 2);
        }
        Actor_MarkForDeath(&this->actor);
    }
}

/**
 * This function either exits the race or resumes it based on how the player
 * responded to the Goron Elder's son's question.
 */
void EnMttag_HandleCantWinChoice(EnMttag* this, GlobalContext* globalCtx) {
    if ((Message_GetState(&globalCtx->msgCtx) == 4) && (Message_ShouldAdvance(globalCtx))) {
        if (globalCtx->msgCtx.choiceIndex != 0) {
            // Exit the race
            func_8019F230();
            gSaveContext.unk_3DD0[4] = 0;
            EnMttag_ExitRace(globalCtx, 2, 2);
            gSaveContext.eventInf[1] &= (u8)~8;
            gSaveContext.eventInf[1] |= 4;
            Actor_MarkForDeath(&this->actor);
        } else {
            // Keep racing
            func_8019F208();
            func_801477B4(globalCtx);
            func_800B7298(globalCtx, &this->actor, 6);
            gSaveContext.eventInf[1] &= (u8)~8;
            this->timer = 100;
            this->actionFunc = EnMttag_Race;
        }
    }
}

void EnMttag_Init(Actor* thisx, GlobalContext* globalCtx) {
    Player* player;
    EnMttag* this = THIS;

    if (gSaveContext.save.entranceIndex == 0xD010) {
        player = GET_PLAYER(globalCtx);
        player->stateFlags1 |= 0x20;
        this->raceInitialized = false;
        this->timer = 100;

        gSaveContext.eventInf[1] &= (u8)~1;
        gSaveContext.eventInf[1] &= (u8)~2;
        gSaveContext.eventInf[1] &= (u8)~4;
        gSaveContext.eventInf[1] &= (u8)~8;

        if (!(gSaveContext.save.weekEventReg[12] & 2)) {
            this->actionFunc = EnMttag_ShowIntroCutscene;
        } else {
            s32 requiredScopeTemp;

            this->actionFunc = EnMttag_RaceStart;
        }
    } else {
        Actor_MarkForDeath(&this->actor);
    }
}

void EnMttag_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnMttag* this = THIS;
    if (gSaveContext.unk_3DD0[4] != 6) {
        gSaveContext.unk_3DD0[4] = 5;
    }
}

void EnMttag_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnMttag* this = THIS;
    this->actionFunc(this, globalCtx);
}
