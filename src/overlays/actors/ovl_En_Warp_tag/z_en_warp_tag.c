/*
 * File: z_en_warp_tag.c
 * Overlay: ovl_En_Warp_tag
 * Description: Warp to Trial Entrance
 *   if GoronTrial, has model: Uses GAMEPLAY_DANGEON_KEEP object assigned in EnWarptag_Init
 */

#include "z_en_warp_tag.h"
#include "objects/gameplay_dangeon_keep/gameplay_dangeon_keep.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_10 | ACTOR_FLAG_2000000 | ACTOR_FLAG_8000000)

#define THIS ((EnWarptag*)thisx)

void EnWarptag_Init(Actor* thisx, GlobalContext* globalCtx);
void EnWarptag_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnWarptag_Update(Actor* thisx, GlobalContext* globalCtx);
void EnWarpTag_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnWarpTag_CheckDungeonKeepObject(EnWarptag* this, GlobalContext* globalCtx);
void EnWarpTag_WaitForPlayer(EnWarptag* this, GlobalContext* globalCtx);
void EnWarpTag_Unused809C09A0(EnWarptag* this, GlobalContext* globalCtx);
void EnWarpTag_Unused809C0A20(EnWarptag* this, GlobalContext* globalCtx);
void EnWarpTag_RespawnPlayer(EnWarptag* this, GlobalContext* globalCtx);
void EnWarpTag_GrottoReturn(EnWarptag* this, GlobalContext* globalCtx);

const ActorInit En_Warp_tag_InitVars = {
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
// these unknown values get passed to a unknown z_message function
u8 D_809C1000[] = { 0x28, 0x29, 0x2A, 0x2B, 0x2D, 0x2C, 0, 0 };

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F(scale, 1, ICHAIN_CONTINUE),
    ICHAIN_VEC3S(shape.rot, 0, ICHAIN_STOP),
};

void EnWarptag_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnWarptag* this = THIS;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    Actor_SetFocus(&this->dyna.actor, 0.0f);

    if (GET_WARPTAG_3C0_MAX(thisx) == WARPTAG_3C0_MAX) {
        this->dyna.actor.flags &= ~ACTOR_FLAG_1;

        if (GET_WARPTAG_INVISIBLE(&this->dyna.actor)) {
            this->actionFunc = EnWarpTag_WaitForPlayer;

        } else {
            if ((this->dangeonKeepObject = Object_GetIndex(&globalCtx->objectCtx, GAMEPLAY_DANGEON_KEEP)) < 0) {
                Actor_MarkForDeath(&this->dyna.actor);
            }

            this->actionFunc = EnWarpTag_CheckDungeonKeepObject;
        }

    } else { // not used by known variants
        this->actionFunc = EnWarpTag_Unused809C09A0;
    }
}

void EnWarptag_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnWarptag* this = THIS;
    if (this->dyna.actor.draw != NULL) {
        DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    }
}

/**
 * Loads DynaPoly from GAMEPLAY_DANGEON_KEEP.
 */
void EnWarpTag_CheckDungeonKeepObject(EnWarptag* this, GlobalContext* globalCtx) {
    if (Object_IsLoaded(&globalCtx->objectCtx, this->dangeonKeepObject)) {
        this->actionFunc = EnWarpTag_WaitForPlayer;
        DynaPolyActor_Init(&this->dyna, 0x1);
        DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &gWarpTagGoronTrialBaseCollider);
        this->dyna.actor.objBankIndex = this->dangeonKeepObject;
        this->dyna.actor.draw = EnWarpTag_Draw;
    }
}

void EnWarpTag_WaitForPlayer(EnWarptag* this, GlobalContext* globalCtx) {
    if (!Player_InCsMode(&globalCtx->state) && (this->dyna.actor.xzDistToPlayer <= 30.0f) &&
        (this->dyna.actor.playerHeightRel <= 10.0f)) {
        if (GET_WARPTAG_INVISIBLE(&this->dyna.actor)) {
            func_800B7298(globalCtx, NULL, 0x51);
            this->actionFunc = EnWarpTag_GrottoReturn;
        } else {
            func_800B7298(globalCtx, NULL, 0xF);
            this->actionFunc = EnWarpTag_RespawnPlayer;
        }
    }
}

/**
 * Unused ActionFunc: assigned in EnWarpTag_Init, no known variants use.
 */
void EnWarpTag_Unused809C09A0(EnWarptag* this, GlobalContext* globalCtx) {
    if (func_800B8718(&this->dyna.actor, &globalCtx->state)) {
        // func above: checks for ACTOR_FLAG_20000000, returns true and resets if set, else return false
        //   this actor doesnt have that flag set default, or in init, and this is called shortly after init
        //   and I doubt its set externally by another actor, so I believe this is unused
        // might be a bug, they might have meant to set actor flag (0x2000 0000) up above but mistyped (0x200 0000)
        // also GET_WARPTAG_3C0 should always return 2C0 -> 0xF for all known in-game uses, which is OOB
        func_80152434(globalCtx, D_809C1000[GET_WARPTAG_3C0(&this->dyna.actor)]); // unk message function
        this->actionFunc = EnWarpTag_Unused809C0A20;

    } else {
        func_800B8804(&this->dyna.actor, globalCtx, 50.0f); // updates player->unk_A90
    }
}

/**
 * Unused ActionFunc: assigned by EnWarpTag_Unused809C09A0, no known variants use.
 */
void EnWarpTag_Unused809C0A20(EnWarptag* this, GlobalContext* globalCtx) {
    if (globalCtx->msgCtx.ocarinaMode == 9) {
        func_800B7298(globalCtx, NULL, 7);
        this->actionFunc = EnWarpTag_RespawnPlayer;
        ActorCutscene_Stop(ActorCutscene_GetCurrentIndex());

    } else if (globalCtx->msgCtx.ocarinaMode >= 2) {
        globalCtx->msgCtx.ocarinaMode = 4;
        this->actionFunc = EnWarpTag_Unused809C09A0;
    }
}

/**
 * ActionFunc: Goron Trial (Moon), respawn at the beginning of goron rolling track, try again.
 */
void EnWarpTag_RespawnPlayer(EnWarptag* this, GlobalContext* globalCtx) {
    ActorEntry* playerActorEntry;
    Player* player;
    s32 playerSpawnIndex;
    s32 new15E;
    s32 entranceIndex;
    u32 playerSpawnIndexPerForm[PLAYER_FORM_MAX];
    u8 playerForm;
    s16 playerParams;

    player = GET_PLAYER(globalCtx);
    if (globalCtx->playerActorCsIds[4] >= 0 && ActorCutscene_GetCurrentIndex() != globalCtx->playerActorCsIds[4]) {
        if (ActorCutscene_GetCanPlayNext(globalCtx->playerActorCsIds[4]) == 0) {
            ActorCutscene_SetIntentToPlay(globalCtx->playerActorCsIds[4]);

        } else {
            ActorCutscene_StartAndSetUnkLinkFields(globalCtx->playerActorCsIds[4], &this->dyna.actor);
            func_800B8E58(player, NA_SE_PL_WARP_PLATE);
            func_8016566C(0);
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
            player->stateFlags3 |= 0x1;
            player->actor.gravity = -0.5f;

            if (this->dyna.actor.playerHeightRel < -80.0f) {
                playerSpawnIndexPerForm[PLAYER_FORM_FIERCE_DEITY] = GET_WARPTAG_EXIT_INDEX(&this->dyna.actor);
                playerSpawnIndexPerForm[PLAYER_FORM_HUMAN] = playerSpawnIndexPerForm[PLAYER_FORM_FIERCE_DEITY];
                playerSpawnIndexPerForm[PLAYER_FORM_GORON] = this->dyna.actor.world.rot.x;
                playerSpawnIndexPerForm[PLAYER_FORM_ZORA] = this->dyna.actor.world.rot.y;
                playerSpawnIndexPerForm[PLAYER_FORM_DEKU] = this->dyna.actor.world.rot.z;

                if (this->dyna.actor.draw != NULL) {
                    playerForm = PLAYER_BOOTS_FIERCE_DEITY;
                } else {
                    playerForm = player->transformation;
                }

                entranceIndex = gSaveContext.save.entranceIndex;

                playerSpawnIndex = playerSpawnIndexPerForm[playerForm];
                playerActorEntry = &globalCtx->linkActorEntry[playerSpawnIndex];
                newRespawnPos.x = playerActorEntry->pos.x;
                newRespawnPos.y = playerActorEntry->pos.y;
                newRespawnPos.z = playerActorEntry->pos.z;

                if (GET_WARPTAG_3C0_MAX(&this->dyna.actor) == WARPTAG_3C0_MAX) {
                    playerParams = 0x9FF;
                } else { // not used by any known variant
                    playerParams = 0x8FF;
                }

                // why are we getting player home rotation from the room data? doesnt player have home.rot.y?
                // especially because we are converting from deg to binang, but isnt home.rot.y already in binang??
                Play_SetRespawnData(
                    &globalCtx->state, 0, entranceIndex, // parameter 3 is called "sceneSetup"
                    globalCtx->setupEntranceList[playerSpawnIndex].room, playerParams, &newRespawnPos,
                    ((((playerActorEntry->rot.y >> 7) & 0x1FF) / 180.0f) * 32768.0f)); // DEG_TO_BINANG ?

                func_80169EFC(&globalCtx->state);
                gSaveContext.respawnFlag = ~0x4;
                func_80165690();
            }
        }

        player->actor.shape.rot.y += this->unkValue15E;
        new15E = this->unkValue15E - 0xFA0;
        if (new15E < 0) {
            new15E = 0;
        }
        func_80165658(new15E * 0.04f); // unknown Play_ function
    }
}

/**
 * ActionFunc: Deku Playground, return to North Clock Town.
 */
void EnWarpTag_GrottoReturn(EnWarptag* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCurrentIndex() != this->dyna.actor.cutscene) {
        if (ActorCutscene_GetCanPlayNext(this->dyna.actor.cutscene)) {
            ActorCutscene_StartAndSetUnkLinkFields(this->dyna.actor.cutscene, &this->dyna.actor);
        } else {
            ActorCutscene_SetIntentToPlay(this->dyna.actor.cutscene);
        }
    }

    if (this->grottoExitDelay++ == 10) {
        globalCtx->nextEntranceIndex = globalCtx->setupExitList[GET_WARPTAG_EXIT_INDEX(&this->dyna.actor)];
        Scene_SetExitFade(globalCtx);
        globalCtx->sceneLoadFlag = 0x14;
        func_8019F128(NA_SE_OC_SECRET_HOLE_OUT);
        func_801A4058(5);
        if (1) {}
        gSaveContext.seqIndex = 0xFF;
        gSaveContext.nightSeqIndex = 0xFF;
    }
}

void EnWarptag_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnWarptag* this = THIS;
    this->actionFunc(this, globalCtx);
}

/**
 * Only draws for Goron Trial (a rainblow animated target).
 */
void EnWarpTag_Draw(Actor* thisx, GlobalContext* globalCtx) {
    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);
    AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(&gWarpTagRainbowAnimMat));
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gSPDisplayList(POLY_OPA_DISP++, gWarpTagGoronTrialBaseDL);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
