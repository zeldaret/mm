/*
 * File: z_oceff_wipe5.c
 * Overlay: ovl_Oceff_Wipe5
 * Description: Sonata/Lullaby/Bossa Nova/Elegy/Oath Ocarina Effect
 */

#include "z_oceff_wipe5.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_2000000)

#define THIS ((OceffWipe5*)thisx)

void OceffWipe5_Init(Actor* thisx, PlayState* play);
void OceffWipe5_Destroy(Actor* thisx, PlayState* play);
void OceffWipe5_Update(Actor* thisx, PlayState* play);
void OceffWipe5_Draw(Actor* thisx, PlayState* play);

ActorInit Oceff_Wipe5_InitVars = {
    /**/ ACTOR_OCEFF_WIPE5,
    /**/ ACTORCAT_ITEMACTION,
    /**/ FLAGS,
    /**/ GAMEPLAY_KEEP,
    /**/ sizeof(OceffWipe5),
    /**/ OceffWipe5_Init,
    /**/ OceffWipe5_Destroy,
    /**/ OceffWipe5_Update,
    /**/ OceffWipe5_Draw,
};

UNK_TYPE4 D_80BC9260;

void OceffWipe5_Init(Actor* thisx, PlayState* play) {
    OceffWipe5* this = THIS;

    Actor_SetScale(&this->actor, 1.0f);
    this->counter = 0;
    this->actor.world.pos = play->cameraPtrs[play->activeCamId]->eye;
}

void OceffWipe5_Destroy(Actor* thisx, PlayState* play) {
    OceffWipe5* this = THIS;

    Magic_Reset(play);
    play->msgCtx.ocarinaSongEffectActive = false;
}

void OceffWipe5_Update(Actor* thisx, PlayState* play) {
    OceffWipe5* this = THIS;

    this->actor.world.pos = GET_ACTIVE_CAM(play)->eye;
    if (this->counter < 100) {
        this->counter++;
    } else {
        Actor_Kill(&this->actor);
    }
}

#include "assets/overlays/ovl_Oceff_Wipe5/ovl_Oceff_Wipe5.c"

static u8 sPrimColors[] = {
    255, 255, 200, 255, 255, 200, 200, 255, 255, 255, 255, 200, 255, 200, 255,
};

static u8 sEnvColors[] = {
    50, 200, 0, 255, 50, 0, 0, 100, 255, 255, 150, 0, 255, 0, 200,
};

void OceffWipe5_Draw(Actor* thisx, PlayState* play) {
    OceffWipe5* this = THIS;
    f32 z;
    s32 pad;
    s32 i;
    s32 pad2;
    Vec3f activeCamEye = GET_ACTIVE_CAM(play)->eye;
    Camera* activeCam = GET_ACTIVE_CAM(play);
    Vec3f quakeOffset;
    u8 alpha;
    s32 colorIndex = OCEFF_WIPE5_GET_SONG_TYPE(thisx) * 3;
    f32 phi_fv1 = 1220.0f;

    if ((((OCEFF_WIPE5_GET_SONG_TYPE(thisx) == 2) && (play->sceneId == SCENE_LABO)) &&
         ((play->csCtx.scriptIndex == 0) || (play->csCtx.scriptIndex == 1))) &&
        (play->csCtx.state != CS_STATE_IDLE)) {
        phi_fv1 = 1150.0f;
    }

    if (colorIndex >= 13) {
        colorIndex = 0;
    }

    Camera_GetQuakeOffset(&quakeOffset, activeCam);

    if (this->counter < 32) {
        z = Math_SinS(this->counter << 9) * phi_fv1;
    } else {
        z = phi_fv1;
    }

    if (this->counter >= 80) {
        alpha = 12 * (100 - this->counter);
    } else {
        alpha = 255;
    }
    for (i = 1; i < ARRAY_COUNT(gOceff5Vtx); i += 2) {
        gOceff5Vtx[i].v.cn[3] = alpha;
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
    gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x80, sPrimColors[colorIndex], sPrimColors[colorIndex + 1],
                    sPrimColors[colorIndex + 2], 255);
    gDPSetEnvColor(POLY_XLU_DISP++, sEnvColors[colorIndex], sEnvColors[colorIndex + 1], sEnvColors[colorIndex + 2],
                   255);

    AnimatedMat_Draw(play, gOceff5TexAnim);

    gSPDisplayList(POLY_XLU_DISP++, &gOceff5DL);

    CLOSE_DISPS(play->state.gfxCtx);
}
