/*
 * File: z_bg_tobira01.c
 * Overlay: ovl_Bg_Tobira01
 * Description: Gate to Goron Shrine
 */

#include "z_bg_tobira01.h"
#include "objects/object_spot11_obj/object_spot11_obj.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((BgTobira01*)thisx)

void BgTobira01_Init(Actor* thisx, PlayState* play);
void BgTobira01_Destroy(Actor* thisx, PlayState* play);
void BgTobira01_Update(Actor* thisx, PlayState* play);
void BgTobira01_Draw(Actor* thisx, PlayState* play);
void BgTobira01_Listen(BgTobira01* this, PlayState* play);

const ActorInit Bg_Tobira01_InitVars = {
    ACTOR_BG_TOBIRA01,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_SPOT11_OBJ,
    sizeof(BgTobira01),
    (ActorFunc)BgTobira01_Init,
    (ActorFunc)BgTobira01_Destroy,
    (ActorFunc)BgTobira01_Update,
    (ActorFunc)BgTobira01_Draw,
};

void BgTobira01_Action(BgTobira01* this, PlayState* play) {
    Player* sp1C = GET_PLAYER(play);
    s16 actorCutscene = this->dyna.actor.csId;
    s16 tempDoorYPosition;

    if (this->cutscenePlayed != 0) {
        if (CutsceneManager_GetCurrentCsId() == CS_ID_GLOBAL_TALK) {
            CutsceneManager_Stop(CS_ID_GLOBAL_TALK);
        } else if (CutsceneManager_IsNext(actorCutscene) != 0) {
            CutsceneManager_StartWithPlayerCs(actorCutscene, &this->dyna.actor);
            gSaveContext.save.saveInfo.weekEventReg[88] |= 0x40;
            this->cutscenePlayed = 0;
        } else {
            CutsceneManager_Queue(actorCutscene);
        }
    } else if (!(gSaveContext.save.saveInfo.weekEventReg[88] & 0x40) && (this->doorYPositionTick == 0) &&
               (play->actorCtx.playerImpact.timer != 0) && (play->actorCtx.playerImpact.type == 0) &&
               (SurfaceType_GetSceneExitIndex(&play->colCtx, sp1C->actor.floorPoly, sp1C->actor.floorBgId) == 6)) {
        this->cutscenePlayed = 1;
        this->unk16C = 0;
    }

    tempDoorYPosition = this->doorYPositionTick;
    if (gSaveContext.save.saveInfo.weekEventReg[88] & 0x40) {
        this->doorYPositionTick += 1;
    } else {
        this->doorYPositionTick -= 1;
    }

    this->doorYPositionTick = CLAMP(this->doorYPositionTick, DOOR_POS_MIN, DOOR_POS_MAX);
    if (tempDoorYPosition != this->doorYPositionTick) {
        Actor_PlaySfx(&this->dyna.actor, NA_SE_EV_STONEDOOR_OPEN_S - SFX_FLAG);
        this->dyna.actor.world.pos.y =
            (this->yPosition = (this->doorYPositionTick * (5.0f / 3.0f)) + this->dyna.actor.home.pos.y);
        this->isNight = 0xB4;
    }

    if (!(sp1C->stateFlags1 & 0x40) && (gSaveContext.save.saveInfo.weekEventReg[88] & 0x40) &&
        DECR(this->isNight) == 0) {
        gSaveContext.save.saveInfo.weekEventReg[88] &= 0xBF;
    }
}

void BgTobira01_Init(Actor* thisx, PlayState* play) {
    BgTobira01* this = THIS;

    DynaPolyActor_Init((DynaPolyActor*)this, 1);
    DynaPolyActor_LoadMesh(play, (DynaPolyActor*)this, &gGoronDoorCol);
    gSaveContext.save.saveInfo.weekEventReg[88] &= 0xBF;
    Actor_SetScale(&this->dyna.actor, 1.0f);
    this->isNight = gSaveContext.save.isNight;
    this->doorYPositionTick = 0;
    this->actionFunction = BgTobira01_Action;
}

void BgTobira01_Destroy(Actor* thisx, PlayState* play) {
    BgTobira01* this = THIS;
    DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
}

void BgTobira01_Update(Actor* thisx, PlayState* play) {
    BgTobira01* this = THIS;
    this->actionFunction(this, play);
}

void BgTobira01_Draw(Actor* thisx, PlayState* play) {
    OPEN_DISPS(play->state.gfxCtx);
    func_8012C28C(play->state.gfxCtx);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, gGoronDoorDL);
    CLOSE_DISPS(play->state.gfxCtx);
}
