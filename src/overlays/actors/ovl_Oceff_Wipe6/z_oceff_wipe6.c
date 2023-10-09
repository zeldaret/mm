/*
 * File: z_oceff_wipe6.c
 * Overlay: ovl_Oceff_Wipe6
 * Description: Song of Soaring Ocarina Effect
 */

#include "z_oceff_wipe6.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_2000000)

#define THIS ((OceffWipe6*)thisx)

void OceffWipe6_Init(Actor* thisx, PlayState* play);
void OceffWipe6_Destroy(Actor* thisx, PlayState* play);
void OceffWipe6_Update(Actor* thisx, PlayState* play);
void OceffWipe6_Draw(Actor* thisx, PlayState* play);

ActorInit Oceff_Wipe6_InitVars = {
    /**/ ACTOR_OCEFF_WIPE6,
    /**/ ACTORCAT_ITEMACTION,
    /**/ FLAGS,
    /**/ GAMEPLAY_KEEP,
    /**/ sizeof(OceffWipe6),
    /**/ OceffWipe6_Init,
    /**/ OceffWipe6_Destroy,
    /**/ OceffWipe6_Update,
    /**/ OceffWipe6_Draw,
};

#include "overlays/ovl_Oceff_Wipe6/ovl_Oceff_Wipe6.c"

void OceffWipe6_Init(Actor* thisx, PlayState* play) {
    OceffWipe6* this = THIS;

    Actor_SetScale(&this->actor, 1.0f);
    this->counter = 0;
    this->actor.world.pos = GET_ACTIVE_CAM(play)->eye;
}

void OceffWipe6_Destroy(Actor* thisx, PlayState* play) {
    Magic_Reset(play);
    play->msgCtx.ocarinaSongEffectActive = false;
}

void OceffWipe6_Update(Actor* thisx, PlayState* play) {
    OceffWipe6* this = THIS;

    this->actor.world.pos = GET_ACTIVE_CAM(play)->eye;
    if (this->counter < 100) {
        this->counter++;
    } else {
        Actor_Kill(&this->actor);
    }
}

void OceffWipe6_Draw(Actor* thisx, PlayState* play) {
    OceffWipe6* this = THIS;
    f32 z;
    u8 alpha;
    s32 i;
    s32 counter;
    Vec3f activeCamEye;
    s32 pad;
    Vec3f quakeOffset;
    s32 pad2;

    activeCamEye = GET_ACTIVE_CAM(play)->eye;
    Camera_GetQuakeOffset(&quakeOffset, GET_ACTIVE_CAM(play));

    if (this->counter < 32) {
        counter = this->counter;
        z = Math_SinS(counter * 0x200) * 1220.0f;
    } else {
        z = 1220.0f;
    }

    if (this->counter >= 80) {
        alpha = 12 * (100 - this->counter);
    } else {
        alpha = 255;
    }

    for (i = 1; i < ARRAY_COUNT(gOceff6Vtx); i += 2) {
        gOceff6Vtx[i].v.cn[3] = alpha;
    }

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL25_Xlu(play->state.gfxCtx);
    Matrix_Translate(activeCamEye.x + quakeOffset.x, activeCamEye.y + quakeOffset.y, activeCamEye.z + quakeOffset.z,
                     MTXMODE_NEW);
    Matrix_Scale(0.1f, 0.1f, 0.1f, MTXMODE_APPLY);
    Matrix_ReplaceRotation(&play->billboardMtxF);
    Matrix_RotateXS(0x708, MTXMODE_APPLY);
    Matrix_Translate(0.0f, 0.0f, -z, MTXMODE_APPLY);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    AnimatedMat_Draw(play, ovl_Oceff_Wipe6_Matanimheader_000338);
    gSPDisplayList(POLY_XLU_DISP++, gOceff6DL);

    CLOSE_DISPS(play->state.gfxCtx);
}
