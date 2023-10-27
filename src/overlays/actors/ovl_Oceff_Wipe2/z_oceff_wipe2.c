/*
 * File: z_oceff_wipe2.c
 * Overlay: ovl_Oceff_Wipe2
 * Description: Epona's Song Ocarina Effect
 */

#include "z_oceff_wipe2.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_2000000)

#define THIS ((OceffWipe2*)thisx)

void OceffWipe2_Init(Actor* thisx, PlayState* play);
void OceffWipe2_Destroy(Actor* thisx, PlayState* play);
void OceffWipe2_Update(Actor* thisx, PlayState* play);
void OceffWipe2_Draw(Actor* thisx, PlayState* play);

ActorInit Oceff_Wipe2_InitVars = {
    /**/ ACTOR_OCEFF_WIPE2,
    /**/ ACTORCAT_ITEMACTION,
    /**/ FLAGS,
    /**/ GAMEPLAY_KEEP,
    /**/ sizeof(OceffWipe2),
    /**/ OceffWipe2_Init,
    /**/ OceffWipe2_Destroy,
    /**/ OceffWipe2_Update,
    /**/ OceffWipe2_Draw,
};

#include "assets/overlays/ovl_Oceff_Wipe2/ovl_Oceff_Wipe2.c"

s32 D_809879D0;

void OceffWipe2_Init(Actor* thisx, PlayState* play) {
    OceffWipe2* this = THIS;

    Actor_SetScale(&this->actor, 0.1f);
    this->timer = 0;
    this->actor.world.pos = GET_ACTIVE_CAM(play)->eye;
}

void OceffWipe2_Destroy(Actor* thisx, PlayState* play) {
    OceffWipe2* this = THIS;

    Magic_Reset(play);
    play->msgCtx.ocarinaSongEffectActive = false;
}

void OceffWipe2_Update(Actor* thisx, PlayState* play) {
    OceffWipe2* this = THIS;

    this->actor.world.pos = GET_ACTIVE_CAM(play)->eye;
    if (this->timer < 100) {
        this->timer++;
    } else {
        Actor_Kill(&this->actor);
    }
}

void OceffWipe2_Draw(Actor* thisx, PlayState* play) {
    u32 scroll = play->state.frames & 0xFF;
    OceffWipe2* this = THIS;
    f32 z;
    u8 alpha;
    s32 pad[2];
    Vec3f eye = GET_ACTIVE_CAM(play)->eye;
    Vtx* vtxPtr;
    Vec3f quakeOffset;

    Camera_GetQuakeOffset(&quakeOffset, GET_ACTIVE_CAM(play));

    vtxPtr = sEponaSongFrustumVtx;

    if (this->timer < 32) {
        z = Math_SinS(this->timer * 0x200) * 1220.0f;
    } else {
        z = 1220.0f;
    }

    if (this->timer >= 80) {
        alpha = 12 * (100 - this->timer);
    } else {
        alpha = 255;
    }

    vtxPtr[1].v.cn[3] = vtxPtr[3].v.cn[3] = vtxPtr[5].v.cn[3] = vtxPtr[7].v.cn[3] = vtxPtr[9].v.cn[3] =
        vtxPtr[11].v.cn[3] = vtxPtr[13].v.cn[3] = vtxPtr[15].v.cn[3] = vtxPtr[16].v.cn[3] = vtxPtr[18].v.cn[3] =
            vtxPtr[20].v.cn[3] = alpha;

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL25_Xlu(play->state.gfxCtx);

    Matrix_Translate(eye.x + quakeOffset.x, eye.y + quakeOffset.y, eye.z + quakeOffset.z, MTXMODE_NEW);
    Matrix_Scale(0.1f, 0.1f, 0.1f, MTXMODE_APPLY);
    Matrix_ReplaceRotation(&play->billboardMtxF);
    Matrix_RotateXS(0x708, MTXMODE_APPLY);
    Matrix_Translate(0.0f, 0.0f, -z, MTXMODE_APPLY);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 170, 255);
    gDPSetEnvColor(POLY_XLU_DISP++, 255, 100, 0, 128);
    gSPDisplayList(POLY_XLU_DISP++, sEponaSongFrustumMaterialDL);
    gSPDisplayList(POLY_XLU_DISP++, Gfx_TwoTexScroll(play->state.gfxCtx, G_TX_RENDERTILE, scroll * 6, scroll * -6, 64,
                                                     64, 1, scroll * -6, 0, 64, 64));
    gSPDisplayList(POLY_XLU_DISP++, sEponaSongFrustumModelDL);

    CLOSE_DISPS(play->state.gfxCtx);
}
