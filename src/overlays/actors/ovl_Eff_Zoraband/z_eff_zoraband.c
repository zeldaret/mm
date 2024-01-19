/*
 * File: z_eff_zoraband.c
 * Overlay: ovl_Eff_Zoraband
 * Description: Indigo-Go's (Mikau's healing cutscene)
 */

#include "z_eff_zoraband.h"
#include "objects/object_zoraband/object_zoraband.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((EffZoraband*)thisx)

void EffZoraband_Init(Actor* thisx, PlayState* play);
void EffZoraband_Destroy(Actor* thisx, PlayState* play);
void EffZoraband_Update(Actor* thisx, PlayState* play);
void EffZoraband_Draw(Actor* thisx, PlayState* play2);

void EffZoraband_MikauFadeOut(EffZoraband* this, PlayState* play);

ActorInit Eff_Zoraband_InitVars = {
    /**/ ACTOR_EFF_ZORABAND,
    /**/ ACTORCAT_ITEMACTION,
    /**/ FLAGS,
    /**/ OBJECT_ZORABAND,
    /**/ sizeof(EffZoraband),
    /**/ EffZoraband_Init,
    /**/ EffZoraband_Destroy,
    /**/ EffZoraband_Update,
    /**/ EffZoraband_Draw,
};

void EffZoraband_Init(Actor* thisx, PlayState* play) {
    EffZoraband* this = THIS;

    Actor_SetScale(&this->actor, 1.0f);
    this->actionFunc = EffZoraband_MikauFadeOut;
    this->alpha = 0;
    this->actor.shape.rot.z = 0;
}

void EffZoraband_Destroy(Actor* thisx, PlayState* play) {
}

void EffZoraband_MikauFadeOut(EffZoraband* this, PlayState* play) {
    if (Cutscene_IsCueInChannel(play, CS_CMD_ACTOR_CUE_527)) {
        if ((EFFZORABAND_GET_F(&this->actor) + 2) ==
            play->csCtx.actorCues[Cutscene_GetCueChannel(play, CS_CMD_ACTOR_CUE_527)]->id) {
            this->stateFlags |= 2;
        }
        if (play->csCtx.actorCues[Cutscene_GetCueChannel(play, CS_CMD_ACTOR_CUE_527)]->id == 7) {
            this->actor.draw = NULL;
        } else {
            this->actor.draw = EffZoraband_Draw;
        }
    }
    if ((this->actor.home.rot.z != 0) && (this->actor.draw != NULL)) {
        Actor_PlaySfx_Flagged(&this->actor, NA_SE_EV_UFO_LIGHT_BEAM - SFX_FLAG);
    }
    if (this->stateFlags & 2) {
        if (this->alpha < 240) {
            this->alpha += 25;
        } else {
            this->alpha = 255;
        }
    }
}

void EffZoraband_Update(Actor* thisx, PlayState* play) {
    EffZoraband* this = THIS;

    this->actionFunc(this, play);
}

void EffZoraband_Draw(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EffZoraband* this = THIS;

    if (this->alpha != 0) {
        OPEN_DISPS(play->state.gfxCtx);

        Gfx_SetupDL25_Xlu(play->state.gfxCtx);
        Matrix_RotateYS((Camera_GetCamDirYaw(GET_ACTIVE_CAM(play)) + 0x8000), MTXMODE_APPLY);
        AnimatedMat_DrawXlu(play, Lib_SegmentedToVirtual(object_zoraband_Matanimheader_000F38));
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        if (this->actor.home.rot.z != 0) {
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x80, 255, 255, 100, this->alpha);
            gDPSetEnvColor(POLY_XLU_DISP++, 255, 200, 0, 255);
        } else {
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x80, 0, 100, 255, this->alpha);
            gDPSetEnvColor(POLY_XLU_DISP++, 0, 0, 100, 255);
        }
        gSPDisplayList(POLY_XLU_DISP++, object_zoraband_DL_000180);
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0xFF, 200, 255, 255, this->alpha);
        gDPSetEnvColor(POLY_XLU_DISP++, 0, 100, 255, 255);
        gSPDisplayList(POLY_XLU_DISP++, object_zoraband_DL_0002A8);

        CLOSE_DISPS(play->state.gfxCtx);
    }
}
