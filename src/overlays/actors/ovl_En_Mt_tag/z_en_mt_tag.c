/*
 * File: z_en_mt_tag.c
 * Overlay: ovl_En_Mt_tag
 * Description: Controls the Goron Race minigame
 */

#include "z_en_mt_tag.h"

#define FLAGS ACTOR_FLAG_10

#define THIS ((EnMttag*)thisx)

void EnMttag_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMttag_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMttag_Update(Actor* thisx, GlobalContext* globalCtx);

void EnMttag_ShowIntroCutscene(EnMttag* this, GlobalContext* globalCtx);
void EnMttag_WaitForIntroCutsceneToEnd(EnMttag* this, GlobalContext* globalCtx);
void EnMttag_StartRace(EnMttag* this, GlobalContext* globalCtx);
void EnMttag_HandleRace(EnMttag* this, GlobalContext* globalCtx);
void EnMttag_FinishRace(EnMttag* this, GlobalContext* globalCtx);
void EnMttag_PotentiallyRestartRace(EnMttag* this, GlobalContext* globalCtx);
void EnMttag_HandleCantWinChoice(EnMttag* this, GlobalContext* globalCtx);

typedef enum {
    PLAYER_CHEAT_STATUS_NO_CHEATING,
    PLAYER_CHEAT_STATUS_FALSE_START,
    PLAYER_CHEAT_STATUS_TRYING_TO_REACH_GOAL_FROM_BEHIND
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

static Vec3f sCheckpointPositions[] = {
    { -105.0, 1000.0, -240.0 },   { -1751.0, 1000.0, -240.0 },  { -3138.0, 1000.0, -74.0 },
    { -4617.0, 1000.0, 277.0 },   { -5060.0, 1000.0, 388.0 },   { -5412.0, 1000.0, 573.0 },
    { -5523.0, 1000.0, 1035.0 },  { -5393.0, 1000.0, 1405.0 },  { -5060.0, 1000.0, 1553.0 },
    { -3933.0, 1000.0, 1479.0 },  { -3212.0, 1000.0, 1461.0 },  { -2805.0, 1000.0, 1645.0 },
    { -2638.0, 1000.0, 2071.0 },  { -2823.0, 1000.0, 2422.0 },  { -3212.0, 1000.0, 2607.0 },
    { -3785.0, 1000.0, 2977.0 },  { -4321.0, 1000.0, 3501.0 },  { -4654.0, 1000.0, 4185.0 },
    { -4802.0, 1000.0, 4779.0 },  { -4672.0, 1000.0, 5426.0 },  { -4339.0, 1000.0, 6037.0 },
    { -3748.0, 1000.0, 6314.0 },  { -2749.0, 1000.0, 6478.0 },  { -2453.0, 1000.0, 6922.0 },
    { -2269.0, 1000.0, 7754.0 },  { -2453.0, 1000.0, 8309.0 },  { -3008.0, 1000.0, 8438.0 },
    { -3304.0, 1000.0, 8179.0 },  { -3600.0, 1000.0, 7606.0 },  { -3600.0, 1000.0, 6885.0 },
    { -3618.0, 1000.0, 4392.0 },  { -3600.0, 1000.0, 3855.0 },  { -3396.0, 1000.0, 3189.0 },
    { -3396.0, 1000.0, 2283.0 },  { -3600.0, 1000.0, 818.0 },   { -3803.0, 1000.0, -88.0 },
    { -4543.0, 1000.0, -2457.0 }, { -4543.0, 1000.0, -2938.0 }, { -4543.0, 1000.0, -3530.0 },
    { -4284.0, 1000.0, -4333.0 }, { -3581.0, 1000.0, -4795.0 }, { -2805.0, 1000.0, -4850.0 },
    { -1825.0, 1000.0, -4703.0 }, { -1326.0, 1000.0, -4166.0 }, { -1122.0, 1000.0, -3186.0 },
    { -1085.0, 1000.0, -2059.0 }, { -1067.0, 1000.0, -912.0 },
};

s32 EnMttag_IsInGoal(Vec3f* pos) {
    return Math3D_XZBoundCheck(-1261.0f, -901.0f, -1600.0f, -1520.0f, pos->x, pos->z);
}

s32 EnMttag_CheckPlayerCheatStatus(Vec3f* pos) {
    if (!(gSaveContext.eventInf[1] & 1)) {
        if (Math3D_XZBoundCheck(-466.0f, -386.0f, -687.0f, 193.0f, pos->x, pos->z)) {
            // The race hasn't started yet, but the player is beyond the starting line
            return PLAYER_CHEAT_STATUS_FALSE_START;
        }
    } else if (Math3D_XZBoundCheck(-1127.0f, -1007.0f, -867.0f, -787.0f, pos->x, pos->z)) {
        // The goal is actually quite close to the start, just behind a large wall.
        // This checks if the player is in an area "behind" the goal that is not accessible
        // in normal play; it can only be reached by climbing the wall somehow. Perhaps they
        // were worried that players would find a way to climb the wall with a glitch, or
        // perhaps they just wanted to punish people using cheat codes
        return PLAYER_CHEAT_STATUS_TRYING_TO_REACH_GOAL_FROM_BEHIND;
    }
    return PLAYER_CHEAT_STATUS_NO_CHEATING;
}

s32 EnMttag_InitializeRace(EnMttag* this, GlobalContext* globalCtx) {
    Actor* actor = NULL;
    s32 i = 0;
    s32 ret;

    do {
        actor = SubS_FindActor(globalCtx, actor, ACTORCAT_NPC, ACTOR_EN_RG);
        if (actor != NULL) {
            this->raceGorons[i] = (EnRg*)actor;
            i++;
        } else if ((actor == NULL) || (actor->next == NULL)) {
            break;
        }

        actor = actor->next;
    } while (i < 4);

    if (i < 4) {
        ret = false;
    } else {
        ret = true;
    }

    return ret;
}

s32 EnMttag_GetCurrentCheckpoint(Actor* actor, GlobalContext* globalCtx, s32* upcomingCheckpoint, f32* arg2,
                                 f32* arg3) {
    s32 curentCheckpoint = -1;
    s32 hasSetCurrentCheckpointOnce = false;
    f32 minLineLengthSq = 0.0f;
    s32 sceneExitIndex;
    f32 perpendicularPointX;
    f32 perpendicularPointY;
    f32 lineLenSq;
    s32 checkpointIterator;

    sceneExitIndex = SurfaceType_GetSceneExitIndex(&globalCtx->colCtx, actor->floorPoly, actor->floorBgId);
    if ((sceneExitIndex < 4) || (sceneExitIndex >= 19)) {
        return -1;
    }

    checkpointIterator = sStartingCheckpointPerSceneExitIndex[sceneExitIndex];

    do {
        if ((Math3D_PointDistToLine2D(
                actor->world.pos.x, actor->world.pos.z, (&sCheckpointPositions[checkpointIterator])[-1].x,
                (&sCheckpointPositions[checkpointIterator])[-1].z, (&sCheckpointPositions[checkpointIterator])[1].x,
                (&sCheckpointPositions[checkpointIterator])[1].z, &perpendicularPointX, &perpendicularPointY,
                &lineLenSq)) &&
            (!hasSetCurrentCheckpointOnce || ((curentCheckpoint + 1) == checkpointIterator) ||
             (lineLenSq < minLineLengthSq))) {
            minLineLengthSq = lineLenSq;
            curentCheckpoint = checkpointIterator;
            *arg2 = perpendicularPointX;
            *arg3 = perpendicularPointY;
            hasSetCurrentCheckpointOnce = true;
        }
        checkpointIterator++;
    } while (checkpointIterator < sStartingCheckpointPerSceneExitIndex[sceneExitIndex + 1]);

    *upcomingCheckpoint = curentCheckpoint + 1;
    return curentCheckpoint;
}

s32 EnMttag_PlayerProbablyCantWin(EnMttag* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    EnRg* rg;
    s32 currentCheckpoints[5];
    s32 upcomingCheckpoints[5];
    f32 perpendicularPointsX[5];
    f32 perpendicularPointsZ[5];
    s32 highestCurrentCheckpoint;
    s32 i;
    s32 ret = false;

    highestCurrentCheckpoint = -1;
    currentCheckpoints[0] = EnMttag_GetCurrentCheckpoint(&player->actor, globalCtx, &upcomingCheckpoints[0],
                                                         &perpendicularPointsX[0], &perpendicularPointsZ[0]);
    for (i = 1; i < 5; i++) {
        currentCheckpoints[i] =
            EnMttag_GetCurrentCheckpoint(&this->raceGorons[i - 1]->actor, globalCtx, &upcomingCheckpoints[i],
                                         &perpendicularPointsX[i], &perpendicularPointsZ[i]);
        if (highestCurrentCheckpoint < currentCheckpoints[i]) {
            highestCurrentCheckpoint = currentCheckpoints[i];
        }
    }

    for (i = 1; i < 5; i++) {
        rg = this->raceGorons[i - 1];
        if ((upcomingCheckpoints[i] != -1) && (upcomingCheckpoints[0] != -1)) {
            rg->unk_348 = (upcomingCheckpoints[i] - upcomingCheckpoints[0]);
        } else {
            rg->unk_348 = 0;
        }
    }

    if ((currentCheckpoints[0] > 0) && (currentCheckpoints[0] < highestCurrentCheckpoint) &&
        (player->actor.bgCheckFlags & 1) && ((highestCurrentCheckpoint - currentCheckpoints[0]) >= 24)) {
        ret = true;
    }

    return ret;
}

s32 EnMttag_ExitRace(GlobalContext* globalCtx, s32 arg1, s32 nextTransition) {
    CUR_FORM_EQUIP(EQUIP_SLOT_B) = ITEM_SWORD_KOKIRI;
    globalCtx->nextEntranceIndex = 0xD020;
    if ((gSaveContext.weekEventReg[0x21] & 0x80)) {
        gSaveContext.nextCutsceneIndex = 0xFFF0;
    } else {
        gSaveContext.nextCutsceneIndex = 0;
    }

    globalCtx->sceneLoadFlag = 0x14;
    globalCtx->unk_1887F = arg1;
    gSaveContext.nextTransition = nextTransition;
    func_801477B4(globalCtx);
    return 1;
}

void EnMttag_ShowFalseStartMessage(EnMttag* this, GlobalContext* globalCtx) {
    gSaveContext.unk_3DD0[4] = 0;
    func_801518B0(globalCtx, 0xE95, NULL); // An entrant made a false start
    func_800B7298(globalCtx, &this->actor, 7);
    Audio_QueueSeqCmd(0x101400FF);
    this->actionFunc = EnMttag_PotentiallyRestartRace;
}

void EnMttag_ShowCantWinMessage(EnMttag* this, GlobalContext* globalCtx) {
    func_801518B0(globalCtx, 0xE97, NULL); // You can't win now...
    func_800B7298(globalCtx, &this->actor, 7);
    this->actionFunc = EnMttag_HandleCantWinChoice;
}

void EnMttag_ShowIntroCutscene(EnMttag* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->actor.cutscene, &this->actor);
        this->actionFunc = EnMttag_WaitForIntroCutsceneToEnd;
    } else {
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    }
}

void EnMttag_WaitForIntroCutsceneToEnd(EnMttag* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCurrentIndex() != this->actor.cutscene) {
        gSaveContext.weekEventReg[0xC] |= 2;
        this->actionFunc = EnMttag_StartRace;
    }
}

void EnMttag_StartRace(EnMttag* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 playerCheatStatus;

    if (this->raceInitialized == true) {
        playerCheatStatus = EnMttag_CheckPlayerCheatStatus(&player->actor.world.pos);
        if (playerCheatStatus != PLAYER_CHEAT_STATUS_NO_CHEATING) {
            if (playerCheatStatus == PLAYER_CHEAT_STATUS_FALSE_START) {
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
                this->actionFunc = EnMttag_HandleRace;
            }
        }
    } else {
        if (EnMttag_InitializeRace(this, globalCtx)) {
            this->raceInitialized = true;
        }
    }
}

s32 EnMttag_IsAnyRaceGoronInGoal(EnMttag* this) {
    s32 ret = false;
    s32 i;

    for (i = 0; i < 4; i++) {
        if ((EnMttag_IsInGoal(&this->raceGorons[i]->actor.world.pos)) && (this->raceGorons[i]->actor.update != NULL)) {
            ret = true;
            break;
        }
    }
    return ret;
}

void EnMttag_HandleRace(EnMttag* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    Vec3f* playerPos = &player->actor.world.pos;
    s32 playerCheatStatus;

    if (EnMttag_IsInGoal(playerPos)) {
        gSaveContext.unk_3DD0[4] = 6;
        play_sound(NA_SE_SY_START_SHOT);
        Audio_QueueSeqCmd(NA_BGM_GORON_GOAL | 0x8000);
        this->timer = 55;
        gSaveContext.eventInf[1] |= 2;
        this->actionFunc = EnMttag_FinishRace;
    } else if (EnMttag_IsAnyRaceGoronInGoal(this)) {
        gSaveContext.unk_3DD0[4] = 6;
        play_sound(NA_SE_SY_START_SHOT);
        Audio_QueueSeqCmd(NA_BGM_GORON_GOAL | 0x8000);
        this->timer = 55;
        gSaveContext.eventInf[1] |= 4;
        this->actionFunc = EnMttag_FinishRace;
    } else {
        playerCheatStatus = EnMttag_CheckPlayerCheatStatus(playerPos);
        if (playerCheatStatus != PLAYER_CHEAT_STATUS_NO_CHEATING) {
            if (playerCheatStatus == PLAYER_CHEAT_STATUS_FALSE_START) {
                this->shouldRestartRace = true;
            } else {
                this->shouldRestartRace = false;
            }

            EnMttag_ShowFalseStartMessage(this, globalCtx);
            gSaveContext.eventInf[1] |= 8;
        } else if ((EnMttag_PlayerProbablyCantWin(this, globalCtx)) && (this->timer == 0)) {
            EnMttag_ShowCantWinMessage(this, globalCtx);
            gSaveContext.eventInf[1] |= 8;
        }
    }
}

void EnMttag_FinishRace(EnMttag* this, GlobalContext* globalCtx) {
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

void EnMttag_PotentiallyRestartRace(EnMttag* this, GlobalContext* globalCtx) {
    u8 talkState;

    talkState = Message_GetState(&globalCtx->msgCtx);
    if (((talkState == 5 && func_80147624(globalCtx)) || talkState == 2)) {
        if (this->shouldRestartRace) {
            globalCtx->nextEntranceIndex = 0xD010;

            if ((gSaveContext.weekEventReg[0x21] & 0x80)) {
                gSaveContext.nextCutsceneIndex = 0xFFF0;
            } else {
                gSaveContext.nextCutsceneIndex = 0;
            }

            globalCtx->sceneLoadFlag = 0x14;
            globalCtx->unk_1887F = 2;
            gSaveContext.nextTransition = 2;
            func_801477B4(globalCtx);
            func_800B7298(globalCtx, &this->actor, 7);
            Parameter_AddMagic(globalCtx, ((void)0, gSaveContext.unk_3F30) + (gSaveContext.doubleMagic * 48) + 48);

            gSaveContext.eventInf[1] &= 0xFE;
            gSaveContext.eventInf[1] &= 0xFD;
            gSaveContext.eventInf[1] &= 0xFB;
            gSaveContext.eventInf[1] &= 0xF7;
            gSaveContext.eventInf[2] = ((gSaveContext.eventInf[2] & 0xF) + 1) | (gSaveContext.eventInf[2] & 0xF0);
        } else {
            EnMttag_ExitRace(globalCtx, 2, 2);
        }
        Actor_MarkForDeath(&this->actor);
    }
}

void EnMttag_HandleCantWinChoice(EnMttag* this, GlobalContext* globalCtx) {
    if ((Message_GetState(&globalCtx->msgCtx) == 4) && (func_80147624(globalCtx))) {
        if (globalCtx->msgCtx.choiceIndex != 0) {
            func_8019F230();
            gSaveContext.unk_3DD0[4] = 0;
            EnMttag_ExitRace(globalCtx, 2, 2);
            gSaveContext.eventInf[1] &= 0xF7;
            gSaveContext.eventInf[1] |= 4;
            Actor_MarkForDeath(&this->actor);
        } else {
            func_8019F208();
            func_801477B4(globalCtx);
            func_800B7298(globalCtx, &this->actor, 6);
            gSaveContext.eventInf[1] &= 0xF7;
            this->timer = 100;
            this->actionFunc = EnMttag_HandleRace;
        }
    }
}

void EnMttag_Init(Actor* thisx, GlobalContext* globalCtx) {
    Player* player;
    EnMttag* this = THIS;

    if (gSaveContext.entranceIndex == 0xD010) {
        player = GET_PLAYER(globalCtx);
        player->stateFlags1 |= 0x20;
        this->raceInitialized = false;
        this->timer = 100;

        gSaveContext.eventInf[1] &= 0xFE;
        gSaveContext.eventInf[1] &= 0xFD;
        gSaveContext.eventInf[1] &= 0xFB;
        gSaveContext.eventInf[1] &= 0xF7;

        if (!(gSaveContext.weekEventReg[0xC] & 2)) {
            this->actionFunc = EnMttag_ShowIntroCutscene;
        } else {
            s32 requiredScopeTemp;

            this->actionFunc = EnMttag_StartRace;
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
