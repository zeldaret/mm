/*
 * File: z_dm_hina.c
 * Overlay: ovl_Dm_Hina
 * Description: Boss mask cutscene objects
 */

#include "z_dm_hina.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((DmHina*)thisx)

void DmHina_Init(Actor* thisx, PlayState* play);
void DmHina_Destroy(Actor* thisx, PlayState* play);
void DmHina_Update(Actor* thisx, PlayState* play);
void DmHina_Draw(Actor* thisx, PlayState* play);

void DmHina_Idle(DmHina* this, PlayState* play);
void DmHina_AwaitMessageBoxClosing(DmHina* this, PlayState* play);
void DmHina_SetupSubCamera(DmHina* this, PlayState* play);
void DmHina_MoveSubCamera(DmHina* this, PlayState* play);

typedef enum {
    /* 0 */ PARAMS_REMAINS_ODOLWA,
    /* 1 */ PARAMS_REMAINS_GOHT,
    /* 2 */ PARAMS_REMAINS_GYORG,
    /* 3 */ PARAMS_REMAINS_TWINMOLD
} DmHinaType;

typedef enum {
    /* 0 */ LIGHT_ORB_STATE_OFF,
    /* 1 */ LIGHT_ORB_STATE_ON
} LightOrbState;

const ActorInit Dm_Hina_InitVars = {
    ACTOR_DM_HINA,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_BSMASK,
    sizeof(DmHina),
    (ActorFunc)DmHina_Init,
    (ActorFunc)DmHina_Destroy,
    (ActorFunc)DmHina_Update,
    (ActorFunc)DmHina_Draw,
};

void DmHina_Init(Actor* thisx, PlayState* play) {
    DmHina* this = THIS;

    this->isVisible = true;
    this->actionFunc = DmHina_Idle;
    this->blueWarpPosY = this->actor.world.pos.y;
    this->maskScale = 0.0f;
    this->yDimScaleFactor = 1.0f;
    this->actor.focus.pos.x = this->actor.world.pos.x;
    this->actor.focus.pos.y = this->actor.world.pos.y;
    this->actor.focus.pos.z = this->actor.world.pos.z;
}

void DmHina_Destroy(Actor* thisx, PlayState* play) {
}

void DmHina_Idle(DmHina* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    Math_SmoothStepToF(&this->maskScale, 0.6f, 0.5f, 0.05f, 0.001f);
    this->oscilationFactor = Math_SinS(play->gameplayFrames * 1800) * 8.0f;
    if ((player->stateFlags1 & PLAYER_STATE1_400) && (this->actor.xzDistToPlayer < 80.0f)) {
        this->isVisible = false;
        this->oscilationFactor = 0.0f;
        this->actor.world.pos.y += 40.0f;
        this->actionFunc = DmHina_AwaitMessageBoxClosing;
    }
}

void DmHina_AwaitMessageBoxClosing(DmHina* this, PlayState* play) {
    if (Message_GetState(&play->msgCtx) == TEXT_STATE_CLOSING) {
        this->timer = 2;
        this->actionFunc = DmHina_SetupSubCamera;
    }
}

void DmHina_SetupSubCamera(DmHina* this, PlayState* play) {
    this->timer--;
    if (this->timer == 0) {
        this->isVisible = true;
        Cutscene_Start(play, &play->csCtx);
        this->subCamId = Play_CreateSubCamera(play);
        Play_ChangeCameraStatus(play, CAM_ID_MAIN, CAM_STATUS_WAIT);
        Play_ChangeCameraStatus(play, this->subCamId, CAM_STATUS_ACTIVE);
        this->actionFunc = DmHina_MoveSubCamera;
    }
}

void DmHina_MoveSubCamera(DmHina* this, PlayState* play) {
    this->subCamEye.x = this->actor.world.pos.x + 100.0f;
    this->subCamEye.y = this->blueWarpPosY + 260.0f;
    this->subCamEye.z = this->actor.world.pos.z + 100.0f;
    this->subCamAt.x = this->actor.world.pos.x;
    this->subCamAt.y =
        this->actor.world.pos.y + (this->oscilationFactor * this->yDimScaleFactor) + (40.0f * this->yDimScaleFactor);
    this->subCamAt.z = this->actor.world.pos.z;
    Play_SetCameraAtEye(play, this->subCamId, &this->subCamAt, &this->subCamEye);
    Math_SmoothStepToF(&this->actor.world.pos.y, this->blueWarpPosY + 300.0f, 0.5f, 2.0f, 0.1f);
    if (((this->blueWarpPosY + 240.0f) < this->actor.world.pos.y) && (this->csState != LIGHT_ORB_STATE_ON)) {
        this->csState = LIGHT_ORB_STATE_ON;
        Actor_PlaySfxAtPos(&this->actor, NA_SE_OC_WHITE_OUT_INTO_KYOJIN);
    }
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_MASK_RISING - SFX_FLAG);
}

void DmHina_UpdateLightOrb(DmHina* this, PlayState* play) {
    s32 i;
    s16 light1Color;

    switch (this->csState) {
        case LIGHT_ORB_STATE_OFF:
            this->lightOrbAlpha = 0;
            this->scale = 0.0f;
            break;

        case LIGHT_ORB_STATE_ON:
            Math_SmoothStepToF(&this->scale, 1.0f, 0.4f, 0.05f, 0.001f);
            this->lightOrbAlpha = this->scale * 255.0f;

            this->drawOrbEffect = Math_SinS(play->state.frames * 8000);

            for (i = 0; i < 3; i++) {
                light1Color = this->scale * -255.0f;
                play->envCtx.lightSettings.diffuseColor1[i] = light1Color;
                play->envCtx.lightSettings.fogColor[i] = light1Color;
                play->envCtx.lightSettings.ambientColor[i] = light1Color;
            }

            play->envCtx.lightSettings.fogNear = this->scale * -500.0f;

            if (play->envCtx.lightSettings.fogNear < -300) {
                play->roomCtx.curRoom.segment = NULL;
            }

            break;
    }
}

void DmHina_Update(Actor* thisx, PlayState* play) {
    DmHina* this = THIS;

    this->actionFunc(this, play);
    DmHina_UpdateLightOrb(this, play);
}

void DmHina_DrawLightOrb(DmHina* this, PlayState* play) {
    GraphicsContext* gfxCtx = play->state.gfxCtx;

    if (this->csState != LIGHT_ORB_STATE_OFF) {
        OPEN_DISPS(gfxCtx);

        func_8012C2DC(play->state.gfxCtx);
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, (u8)(this->scale * 100.0f) + 155, this->lightOrbAlpha);
        gDPSetEnvColor(POLY_XLU_DISP++, 255, 255, (u8)(this->drawOrbEffect * 100.0f) + 50, 0);
        gSPDisplayList(POLY_XLU_DISP++, gLightOrbMaterial1DL);
        Matrix_Translate(this->actor.world.pos.x,
                         this->actor.world.pos.y + (this->oscilationFactor * this->yDimScaleFactor) +
                             (40.0f * this->yDimScaleFactor),
                         this->actor.world.pos.z, MTXMODE_NEW);
        Matrix_ReplaceRotation(&play->billboardMtxF);
        Matrix_Scale(this->scale * 20.0f, this->scale * 20.0f, this->scale * 20.0f, MTXMODE_APPLY);
        Matrix_RotateZF(Rand_ZeroFloat(2 * M_PI), MTXMODE_APPLY);
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, gLightOrbModelDL);

        CLOSE_DISPS(gfxCtx);
    }
}

void DmHina_Draw(Actor* thisx, PlayState* play) {
    DmHina* this = THIS;
    f32 scale;

    if (this->isVisible) {
        Matrix_Translate(this->actor.world.pos.x,
                         this->actor.world.pos.y + (this->oscilationFactor * this->yDimScaleFactor) +
                             (40.0f * this->yDimScaleFactor),
                         this->actor.world.pos.z, MTXMODE_NEW);
        Matrix_RotateZYX(0, play->gameplayFrames * 1000, 0, MTXMODE_APPLY);
        scale = this->maskScale * (1.0f - this->scale) * this->yDimScaleFactor;
        Matrix_Scale(scale, scale, scale, MTXMODE_APPLY);
        switch (this->actor.params) {
            case PARAMS_REMAINS_ODOLWA:
                GetItem_Draw(play, GID_REMAINS_ODOLWA);
                break;

            case PARAMS_REMAINS_GOHT:
                GetItem_Draw(play, GID_REMAINS_GOHT);
                break;

            case PARAMS_REMAINS_GYORG:
                GetItem_Draw(play, GID_REMAINS_GYORG);
                break;

            case PARAMS_REMAINS_TWINMOLD:
                GetItem_Draw(play, GID_REMAINS_TWINMOLD);
                break;
        }
        DmHina_DrawLightOrb(this, play);
    }
}
