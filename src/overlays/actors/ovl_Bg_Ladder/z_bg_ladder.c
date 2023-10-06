/*
 * File: z_bg_ladder.c
 * Overlay: ovl_Bg_Ladder
 * Description: Wooden Ladder
 */

#include "z_bg_ladder.h"
#include "objects/object_ladder/object_ladder.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((BgLadder*)thisx)

void BgLadder_Init(Actor* thisx, PlayState* play);
void BgLadder_Destroy(Actor* thisx, PlayState* play);
void BgLadder_Update(Actor* thisx, PlayState* play);
void BgLadder_Draw(Actor* thisx, PlayState* play);
void BgLadder_Wait(BgLadder* this, PlayState* play);
void BgLadder_StartCutscene(BgLadder* this, PlayState* play);
void BgLadder_FadeIn(BgLadder* this, PlayState* play);
void BgLadder_DoNothing(BgLadder* this, PlayState* play);

ActorInit Bg_Ladder_InitVars = {
    ACTOR_BG_LADDER,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_LADDER,
    sizeof(BgLadder),
    (ActorFunc)BgLadder_Init,
    (ActorFunc)BgLadder_Destroy,
    (ActorFunc)BgLadder_Update,
    (ActorFunc)BgLadder_Draw,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

static Gfx* sLadderDLists[] = {
    object_ladder_DL_0000A0, // 12 Rung
    object_ladder_DL_0002D0, // 16 Rung
    object_ladder_DL_000500, // 20 Rung
    object_ladder_DL_000730, // 24 Rung
};

void BgLadder_Init(Actor* thisx, PlayState* play) {
    BgLadder* this = THIS;
    BgLadderSize size;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);

    this->switchFlag = BGLADDER_GET_SWITCH_FLAG(thisx);
    thisx->params = BGLADDER_GET_SIZE(thisx);
    DynaPolyActor_Init(&this->dyna, 0);
    size = thisx->params;

    if (size == LADDER_SIZE_12RUNG) {
        DynaPolyActor_LoadMesh(play, &this->dyna, &object_ladder_Colheader_0001D8);
    } else if (size == LADDER_SIZE_16RUNG) {
        DynaPolyActor_LoadMesh(play, &this->dyna, &object_ladder_Colheader_000408);
    } else if (size == LADDER_SIZE_20RUNG) {
        DynaPolyActor_LoadMesh(play, &this->dyna, &object_ladder_Colheader_000638);
    } else if (size == LADDER_SIZE_24RUNG) {
        DynaPolyActor_LoadMesh(play, &this->dyna, &object_ladder_Colheader_000868);
    } else {
        Actor_Kill(&this->dyna.actor);
        return;
    }

    if (Flags_GetSwitch(play, this->switchFlag)) {
        // If the flag is set, then the ladder draws immediately
        this->alpha = 255;
        this->dyna.actor.flags &= ~ACTOR_FLAG_10; // always update = off
        this->action = BgLadder_DoNothing;
    } else {
        // Otherwise, the ladder doesn't draw; wait for the flag to be set
        this->alpha = 5;
        DynaPoly_DisableCollision(play, &play->colCtx.dyna, this->dyna.bgId);
        this->dyna.actor.draw = NULL;
        this->action = BgLadder_Wait;
    }
}

void BgLadder_Destroy(Actor* thisx, PlayState* play) {
    BgLadder* this = THIS;

    DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
}

void BgLadder_Wait(BgLadder* this, PlayState* play) {
    // Wait for the flag to be set, then trigger the cutscene
    if (Flags_GetSwitch(play, this->switchFlag)) {
        CutsceneManager_Queue(this->dyna.actor.csId);
        this->action = BgLadder_StartCutscene;
    }
}

void BgLadder_StartCutscene(BgLadder* this, PlayState* play) {
    // Trigger the cutscene, then make the ladder fade in
    if (CutsceneManager_IsNext(this->dyna.actor.csId)) {
        CutsceneManager_StartWithPlayerCs(this->dyna.actor.csId, &this->dyna.actor);
        this->dyna.actor.draw = BgLadder_Draw;
        Actor_PlaySfx(&this->dyna.actor, NA_SE_EV_SECRET_LADDER_APPEAR);
        this->action = BgLadder_FadeIn;
    } else {
        CutsceneManager_Queue(this->dyna.actor.csId);
    }
}

void BgLadder_FadeIn(BgLadder* this, PlayState* play) {
    // Fade in the ladder, then stop the cutscene & go idle
    this->alpha += 5;
    if (this->alpha >= 255) {
        this->alpha = 255;
        CutsceneManager_Stop(this->dyna.actor.csId);
        DynaPoly_EnableCollision(play, &play->colCtx.dyna, this->dyna.bgId);
        this->dyna.actor.flags &= ~ACTOR_FLAG_10; // always update = off
        this->action = BgLadder_DoNothing;
    }
}

void BgLadder_DoNothing(BgLadder* this, PlayState* play) {
}

void BgLadder_Update(Actor* thisx, PlayState* play) {
    BgLadder* this = THIS;

    this->action(this, play);
}

void BgLadder_Draw(Actor* thisx, PlayState* play) {
    BgLadder* this = THIS;
    s32 pad;
    Gfx* gfx;

    OPEN_DISPS(play->state.gfxCtx);

    if (this->alpha == 255) {
        Scene_SetRenderModeXlu(play, 0, 0x01);
        gfx = POLY_OPA_DISP;
    } else {
        Scene_SetRenderModeXlu(play, 1, 0x02);
        gfx = POLY_XLU_DISP;
    }

    gSPDisplayList(&gfx[0], gSetupDLs[SETUPDL_25]);
    gDPSetEnvColor(&gfx[1], 255, 255, 255, this->alpha);
    gSPMatrix(&gfx[2], Matrix_NewMtx(play->state.gfxCtx), G_MTX_LOAD);
    gSPDisplayList(&gfx[3], sLadderDLists[this->dyna.actor.params]);

    if (this->alpha == 255) {
        POLY_OPA_DISP = gfx + 4;
    } else {
        POLY_XLU_DISP = gfx + 4;
    }

    CLOSE_DISPS(play->state.gfxCtx);
}
