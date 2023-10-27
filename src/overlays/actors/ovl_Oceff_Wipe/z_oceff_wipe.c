/*
 * File: z_oceff_wipe.c
 * Overlay: ovl_Oceff_Wipe
 * Description: Song of Time Ocarina Effect
 */

#include "z_oceff_wipe.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_2000000)

#define THIS ((OceffWipe*)thisx)

void OceffWipe_Init(Actor* thisx, PlayState* play);
void OceffWipe_Destroy(Actor* thisx, PlayState* play);
void OceffWipe_Update(Actor* thisx, PlayState* play);
void OceffWipe_Draw(Actor* thisx, PlayState* play);

ActorInit Oceff_Wipe_InitVars = {
    /**/ ACTOR_OCEFF_WIPE,
    /**/ ACTORCAT_ITEMACTION,
    /**/ FLAGS,
    /**/ GAMEPLAY_KEEP,
    /**/ sizeof(OceffWipe),
    /**/ OceffWipe_Init,
    /**/ OceffWipe_Destroy,
    /**/ OceffWipe_Update,
    /**/ OceffWipe_Draw,
};

UNK_TYPE4 D_80977200;

void OceffWipe_Init(Actor* thisx, PlayState* play) {
    OceffWipe* this = THIS;

    Actor_SetScale(&this->actor, 0.1f);
    this->counter = 0;
    this->actor.world.pos = GET_ACTIVE_CAM(play)->eye;
}

void OceffWipe_Destroy(Actor* thisx, PlayState* play) {
    OceffWipe* this = THIS;

    Magic_Reset(play);
    play->msgCtx.ocarinaSongEffectActive = false;
}

void OceffWipe_Update(Actor* thisx, PlayState* play) {
    OceffWipe* this = THIS;

    this->actor.world.pos = GET_ACTIVE_CAM(play)->eye;
    if (this->counter < 100) {
        this->counter++;
    } else {
        Actor_Kill(&this->actor);
    }
}

#include "assets/overlays/ovl_Oceff_Wipe/ovl_Oceff_Wipe.c"

static u8 sAlphaIndices[] = {
    0x01, 0x10, 0x22, 0x01, 0x20, 0x12, 0x01, 0x20, 0x12, 0x01,
    0x10, 0x22, 0x01, 0x20, 0x12, 0x01, 0x12, 0x21, 0x01, 0x02,
};

void OceffWipe_Draw(Actor* thisx, PlayState* play) {
    u32 scroll = play->state.frames & 0xFF;
    OceffWipe* this = THIS;
    f32 z;
    s32 pad;
    u8 alphaTable[3];
    s32 i;
    Vec3f eye = GET_ACTIVE_CAM(play)->eye;
    Vtx* vtxPtr;
    Vec3f quakeOffset;

    Camera_GetQuakeOffset(&quakeOffset, GET_ACTIVE_CAM(play));

    OPEN_DISPS(play->state.gfxCtx);

    if (this->counter < 32) {
        z = Math_SinS(this->counter << 9) * 1360.0f;
    } else {
        z = 1360.0f;
    }

    if (this->counter >= 80) {
        alphaTable[0] = 0;
        alphaTable[1] = (100 - this->counter) * 8;
        alphaTable[2] = (100 - this->counter) * 12;
    } else {
        alphaTable[0] = 0;
        alphaTable[1] = 160;
        alphaTable[2] = 255;
    }

    for (i = 0; i < 20; i++) {
        vtxPtr = sSongOfTimeFrustumVtx;
        vtxPtr[i * 2 + 0].v.cn[3] = alphaTable[(sAlphaIndices[i] & 0xF0) >> 4];
        vtxPtr[i * 2 + 1].v.cn[3] = alphaTable[sAlphaIndices[i] & 0xF];
    }

    Gfx_SetupDL25_Xlu(play->state.gfxCtx);

    Matrix_Translate(eye.x + quakeOffset.x, eye.y + quakeOffset.y, eye.z + quakeOffset.z, MTXMODE_NEW);
    Matrix_Scale(0.1f, 0.1f, 0.1f, MTXMODE_APPLY);
    Matrix_ReplaceRotation(&play->billboardMtxF);
    Matrix_RotateXS(0x708, MTXMODE_APPLY);
    Matrix_Translate(0.0f, 0.0f, -z, MTXMODE_APPLY);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    if (this->actor.params != OCEFF_WIPE_ZL) {
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 170, 255, 255, 255);
        gDPSetEnvColor(POLY_XLU_DISP++, 0, 150, 255, 128);
    } else {
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 200, 255);
        gDPSetEnvColor(POLY_XLU_DISP++, 100, 0, 255, 128);
    }

    gSPDisplayList(POLY_XLU_DISP++, sSongOfTimeFrustumMaterialDL);
    gSPDisplayList(POLY_XLU_DISP++, Gfx_TwoTexScroll(play->state.gfxCtx, G_TX_RENDERTILE, 0 - scroll, scroll * -2, 32,
                                                     32, 1, 0 - scroll, scroll * -2, 32, 32));
    gSPDisplayList(POLY_XLU_DISP++, sSongOfTimeFrustumModelDL);

    CLOSE_DISPS(play->state.gfxCtx);
}
