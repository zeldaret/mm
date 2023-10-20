/*
 * File: z_en_warp_tag.c
 * Overlay: ovl_En_Warp_tag
 * Description: Warp to Trial Entrance
 *   if GoronTrial, has model: Uses GAMEPLAY_DANGEON_KEEP object assigned in EnWarptag_Init
 */

#include "z_en_warp_tag.h"
#include "objects/gameplay_dangeon_keep/gameplay_dangeon_keep.h"

#define FLAGS (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_10 | ACTOR_FLAG_2000000 | ACTOR_FLAG_CANT_LOCK_ON)

#define THIS ((EnWarptag*)thisx)

void EnWarptag_Init(Actor* thisx, PlayState* play);
void EnWarptag_Destroy(Actor* thisx, PlayState* play);
void EnWarptag_Update(Actor* thisx, PlayState* play);
void EnWarpTag_Draw(Actor* thisx, PlayState* play);

void EnWarpTag_CheckDungeonKeepObject(EnWarptag* this, PlayState* play);
void EnWarpTag_WaitForPlayer(EnWarptag* this, PlayState* play);
void EnWarpTag_Unused809C09A0(EnWarptag* this, PlayState* play);
void EnWarpTag_Unused809C0A20(EnWarptag* this, PlayState* play);
void EnWarpTag_RespawnPlayer(EnWarptag* this, PlayState* play);
void EnWarpTag_GrottoReturn(EnWarptag* this, PlayState* play);

ActorInit En_Warp_tag_InitVars = {
    ACTOR_EN_WARP_TAG,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnWarptag),
    (ActorFunc)EnWarptag_Init,
    (ActorFunc)EnWarptag_Destroy,
    (ActorFunc)EnWarptag_Update,
    (ActorFunc)NULL,
};

// this appears to be unused, as the code never accesses it in known vanilla cases
u8 D_809C1000[] = {
    OCARINA_ACTION_CHECK_TIME,    OCARINA_ACTION_CHECK_HEALING, OCARINA_ACTION_CHECK_EPONAS,
    OCARINA_ACTION_CHECK_SOARING, OCARINA_ACTION_CHECK_SUNS,    OCARINA_ACTION_CHECK_STORMS,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F(scale, 1, ICHAIN_CONTINUE),
    ICHAIN_VEC3S(shape.rot, 0, ICHAIN_STOP),
};

void EnWarptag_Init(Actor* thisx, PlayState* play) {
    EnWarptag* this = THIS;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    Actor_SetFocus(&this->dyna.actor, 0.0f);

    if (WARPTAG_GET_3C0_MAX(thisx) == WARPTAG_3C0_MAX) {
        this->dyna.actor.flags &= ~ACTOR_FLAG_TARGETABLE;

        if (WARPTAG_GET_INVISIBLE(&this->dyna.actor)) {
            this->actionFunc = EnWarpTag_WaitForPlayer;

        } else {
            if ((this->dangeonKeepObjectSlot = Object_GetSlot(&play->objectCtx, GAMEPLAY_DANGEON_KEEP)) <=
                OBJECT_SLOT_NONE) {
                Actor_Kill(&this->dyna.actor);
            }

            this->actionFunc = EnWarpTag_CheckDungeonKeepObject;
        }

    } else { // not used by known variants
        this->actionFunc = EnWarpTag_Unused809C09A0;
    }
}

void EnWarptag_Destroy(Actor* thisx, PlayState* play) {
    EnWarptag* this = THIS;
    if (this->dyna.actor.draw != NULL) {
        DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
    }
}

/**
 * Loads DynaPoly from GAMEPLAY_DANGEON_KEEP.
 */
void EnWarpTag_CheckDungeonKeepObject(EnWarptag* this, PlayState* play) {
    if (Object_IsLoaded(&play->objectCtx, this->dangeonKeepObjectSlot)) {
        this->actionFunc = EnWarpTag_WaitForPlayer;
        DynaPolyActor_Init(&this->dyna, 0x1);
        DynaPolyActor_LoadMesh(play, &this->dyna, &gWarpTagGoronTrialBaseCol);
        this->dyna.actor.objectSlot = this->dangeonKeepObjectSlot;
        this->dyna.actor.draw = EnWarpTag_Draw;
    }
}

void EnWarpTag_WaitForPlayer(EnWarptag* this, PlayState* play) {
    if (!Player_InCsMode(play) && (this->dyna.actor.xzDistToPlayer <= 30.0f) &&
        (this->dyna.actor.playerHeightRel <= 10.0f)) {
        if (WARPTAG_GET_INVISIBLE(&this->dyna.actor)) {
            func_800B7298(play, NULL, PLAYER_CSMODE_81);
            this->actionFunc = EnWarpTag_GrottoReturn;
        } else {
            func_800B7298(play, NULL, PLAYER_CSMODE_15);
            this->actionFunc = EnWarpTag_RespawnPlayer;
        }
    }
}

/**
 * Unused ActionFunc: assigned in EnWarpTag_Init, no known variants use.
 */
void EnWarpTag_Unused809C09A0(EnWarptag* this, PlayState* play) {
    if (func_800B8718(&this->dyna.actor, &play->state)) {
        // func above: checks for ACTOR_FLAG_20000000, returns true and resets if set, else return false
        //   this actor doesnt have that flag set default, or in init, and this is called shortly after init
        //   and I doubt its set externally by another actor, so I believe this is unused
        // might be a bug, they might have meant to set actor flag (0x2000 0000) up above but mistyped (0x200 0000)
        // also WARPTAG_GET_3C0 should always return 2C0 -> 0xF for all known in-game uses, which is OOB
        Message_DisplayOcarinaStaff(play, D_809C1000[WARPTAG_GET_3C0(&this->dyna.actor)]);
        this->actionFunc = EnWarpTag_Unused809C0A20;

    } else {
        func_800B8804(&this->dyna.actor, play, 50.0f); // updates player->unk_A90
    }
}

/**
 * Unused ActionFunc: assigned by EnWarpTag_Unused809C09A0, no known variants use.
 */
void EnWarpTag_Unused809C0A20(EnWarptag* this, PlayState* play) {
    if (play->msgCtx.ocarinaMode == OCARINA_MODE_PLAYED_STORMS) {
        func_800B7298(play, NULL, PLAYER_CSMODE_WAIT);
        this->actionFunc = EnWarpTag_RespawnPlayer;
        CutsceneManager_Stop(CutsceneManager_GetCurrentCsId());

    } else if (play->msgCtx.ocarinaMode >= OCARINA_MODE_WARP) {
        play->msgCtx.ocarinaMode = OCARINA_MODE_END;
        this->actionFunc = EnWarpTag_Unused809C09A0;
    }
}

/**
 * ActionFunc: Goron Trial (Moon), respawn at the beginning of goron rolling track, try again.
 */
void EnWarpTag_RespawnPlayer(EnWarptag* this, PlayState* play) {
    ActorEntry* playerActorEntry;
    Player* player = GET_PLAYER(play);
    s32 playerSpawnIndex;
    s32 new15E;
    s32 entrance;
    u32 playerSpawnIndexPerForm[PLAYER_FORM_MAX];
    u8 playerForm;
    s16 playerParams;

    if ((play->playerCsIds[PLAYER_CS_ID_WARP_PAD_MOON] >= 0) &&
        (CutsceneManager_GetCurrentCsId() != play->playerCsIds[PLAYER_CS_ID_WARP_PAD_MOON])) {
        if (!CutsceneManager_IsNext(play->playerCsIds[PLAYER_CS_ID_WARP_PAD_MOON])) {
            CutsceneManager_Queue(play->playerCsIds[PLAYER_CS_ID_WARP_PAD_MOON]);

        } else {
            CutsceneManager_StartWithPlayerCs(play->playerCsIds[PLAYER_CS_ID_WARP_PAD_MOON], &this->dyna.actor);
            Player_PlaySfx(player, NA_SE_PL_WARP_PLATE);
            Play_EnableMotionBlur(0);
        }

    } else {
        f32 diffX = player->actor.world.pos.x - this->dyna.actor.world.pos.x;
        Vec3f newRespawnPos;
        f32 diffZ = player->actor.world.pos.z - this->dyna.actor.world.pos.z;
        f32 distance = sqrtf(SQ(diffX) + SQ(diffZ));

        // some weird float behavior prevention?
        if (distance != 0.0f) {
            distance = (distance - 1.0f) / distance;
            distance = CLAMP_MIN(distance, 0.0f);
        }

        player->actor.world.pos.x = this->dyna.actor.world.pos.x + (diffX * distance);
        player->actor.world.pos.z = this->dyna.actor.world.pos.z + (diffZ * distance);

        if (Math_StepToS(&this->unkValue15E, 0x2710, 0xC8)) {
            player->stateFlags3 |= PLAYER_STATE3_1;
            player->actor.gravity = -0.5f;

            if (this->dyna.actor.playerHeightRel < -80.0f) {
                playerSpawnIndexPerForm[PLAYER_FORM_FIERCE_DEITY] = WARPTAG_GET_EXIT_INDEX(&this->dyna.actor);
                playerSpawnIndexPerForm[PLAYER_FORM_HUMAN] = playerSpawnIndexPerForm[PLAYER_FORM_FIERCE_DEITY];
                playerSpawnIndexPerForm[PLAYER_FORM_GORON] = this->dyna.actor.world.rot.x;
                playerSpawnIndexPerForm[PLAYER_FORM_ZORA] = this->dyna.actor.world.rot.y;
                playerSpawnIndexPerForm[PLAYER_FORM_DEKU] = this->dyna.actor.world.rot.z;

                if (this->dyna.actor.draw != NULL) {
                    playerForm = PLAYER_BOOTS_FIERCE_DEITY;
                } else {
                    playerForm = player->transformation;
                }

                entrance = gSaveContext.save.entrance;

                playerSpawnIndex = playerSpawnIndexPerForm[playerForm];
                playerActorEntry = &play->linkActorEntry[playerSpawnIndex];
                newRespawnPos.x = playerActorEntry->pos.x;
                newRespawnPos.y = playerActorEntry->pos.y;
                newRespawnPos.z = playerActorEntry->pos.z;

                if (WARPTAG_GET_3C0_MAX(&this->dyna.actor) == WARPTAG_3C0_MAX) {
                    playerParams = PLAYER_PARAMS(0xFF, PLAYER_INITMODE_9);
                } else { // not used by any known variant
                    playerParams = PLAYER_PARAMS(0xFF, PLAYER_INITMODE_8);
                }

                // why are we getting player home rotation from the room data? doesnt player have home.rot.y?
                // especially because we are converting from deg to binang, but isnt home.rot.y already in binang??
                Play_SetRespawnData(&play->state, RESPAWN_MODE_DOWN, entrance,
                                    play->setupEntranceList[playerSpawnIndex].room, playerParams, &newRespawnPos,
                                    DEG_TO_BINANG_ALT((playerActorEntry->rot.y >> 7) & 0x1FF));

                func_80169EFC(&play->state);
                gSaveContext.respawnFlag = -5;
                Play_DisableMotionBlur();
            }
        }

        player->actor.shape.rot.y += this->unkValue15E;
        new15E = this->unkValue15E - 0xFA0;
        if (new15E < 0) {
            new15E = 0;
        }
        Play_SetMotionBlurAlpha(new15E * (1 / 25.0f));
    }
}

/**
 * ActionFunc: Deku Playground, return to North Clock Town.
 */
void EnWarpTag_GrottoReturn(EnWarptag* this, PlayState* play) {
    if (CutsceneManager_GetCurrentCsId() != this->dyna.actor.csId) {
        if (CutsceneManager_IsNext(this->dyna.actor.csId)) {
            CutsceneManager_StartWithPlayerCs(this->dyna.actor.csId, &this->dyna.actor);
        } else {
            CutsceneManager_Queue(this->dyna.actor.csId);
        }
    }

    if (this->grottoExitDelay++ == 10) {
        play->nextEntrance = play->setupExitList[WARPTAG_GET_EXIT_INDEX(&this->dyna.actor)];
        Scene_SetExitFade(play);
        play->transitionTrigger = TRANS_TRIGGER_START;
        Audio_PlaySfx_2(NA_SE_OC_SECRET_HOLE_OUT);
        func_801A4058(5);
        gSaveContext.seqId = (u8)NA_BGM_DISABLED;
        gSaveContext.ambienceId = AMBIENCE_ID_DISABLED;
    }
}

void EnWarptag_Update(Actor* thisx, PlayState* play) {
    EnWarptag* this = THIS;
    this->actionFunc(this, play);
}

/**
 * Only draws for Goron Trial (a rainblow animated target).
 */
void EnWarpTag_Draw(Actor* thisx, PlayState* play) {
    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL25_Opa(play->state.gfxCtx);
    AnimatedMat_Draw(play, Lib_SegmentedToVirtual(gWarpTagRainbowTexAnim));
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gSPDisplayList(POLY_OPA_DISP++, gWarpTagGoronTrialBaseDL);

    CLOSE_DISPS(play->state.gfxCtx);
}
