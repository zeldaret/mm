/*
 * File: z_eff_zoraband.c
 * Overlay: ovl_Eff_Zoraband
 * Description: Indigo-Go's (Mikau's healing cutscene)
 */

#include "z_eff_zoraband.h"
#include "objects/object_zoraband/object_zoraband.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((EffZoraband*)thisx)

void EffZoraband_Init(Actor* thisx, GlobalContext* globalCtx);
void EffZoraband_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EffZoraband_Update(Actor* thisx, GlobalContext* globalCtx);
void EffZoraband_Draw(Actor* thisx, GlobalContext* globalCtx2);

void EffZoraband_Mikau_FadeOut(EffZoraband* this, GlobalContext* globalCtx);

const ActorInit Eff_Zoraband_InitVars = {
    ACTOR_EFF_ZORABAND,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_ZORABAND,
    sizeof(EffZoraband),
    (ActorFunc)EffZoraband_Init,
    (ActorFunc)EffZoraband_Destroy,
    (ActorFunc)EffZoraband_Update,
    (ActorFunc)EffZoraband_Draw,
};

void EffZoraband_Init(Actor* thisx, GlobalContext* globalCtx) {
    EffZoraband* this = THIS;

    Actor_SetScale(&this->actor, 1.0f);
    this->actionFunc = EffZoraband_Mikau_FadeOut;
    this->alpha = 0;
    this->actor.shape.rot.z = 0;
}

void EffZoraband_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void EffZoraband_Mikau_FadeOut(EffZoraband* this, GlobalContext* globalCtx) {
    if (Cutscene_CheckActorAction(globalCtx, 0x20F) != 0) {
        if ((EFFZORABAND_GET_F(&this->actor) + 2) ==
            globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, 0x20F)]->action) {
            this->stateFlags |= 2;
        }
        if (globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, 0x20F)]->action == 7) {
            this->actor.draw = NULL;
        } else {
            this->actor.draw = EffZoraband_Draw;
        }
    }
    if ((this->actor.home.rot.z != 0) && (this->actor.draw != NULL)) {
        func_800B9010(&this->actor, NA_SE_EV_UFO_LIGHT_BEAM - SFX_FLAG);
    }
    if (this->stateFlags & 2) {
        if (this->alpha < 240) {
            this->alpha += 25;
        } else {
            this->alpha = 255;
        }
    }
}

void EffZoraband_Update(Actor* thisx, GlobalContext* globalCtx) {
    EffZoraband* this = THIS;

    this->actionFunc(this, globalCtx);
}

void EffZoraband_Draw(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    EffZoraband* this = THIS;

    if (this->alpha != 0) {
        OPEN_DISPS(globalCtx->state.gfxCtx);

        func_8012C2DC(globalCtx->state.gfxCtx);
        Matrix_RotateYS((Camera_GetCamDirYaw(globalCtx->cameraPtrs[globalCtx->activeCamera]) + 0x8000), MTXMODE_APPLY);
        AnimatedMat_DrawXlu(globalCtx, Lib_SegmentedToVirtual(object_zoraband_Matanimheader_000F38));
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
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

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}
