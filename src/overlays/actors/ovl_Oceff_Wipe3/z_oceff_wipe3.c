/*
 * File: z_oceff_wipe3.c
 * Overlay: ovl_Oceff_Wipe3
 * Description: Unused OoT Saria's Song Ocarina Effect
 */

#include "prevent_bss_reordering.h"
#include "z_oceff_wipe3.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_2000000)

#define THIS ((OceffWipe3*)thisx)

void OceffWipe3_Init(Actor* thisx, PlayState* play);
void OceffWipe3_Destroy(Actor* thisx, PlayState* play);
void OceffWipe3_Update(Actor* thisx, PlayState* play);
void OceffWipe3_Draw(Actor* thisx, PlayState* play);

ActorInit Oceff_Wipe3_InitVars = {
    /**/ ACTOR_OCEFF_WIPE3,
    /**/ ACTORCAT_ITEMACTION,
    /**/ FLAGS,
    /**/ GAMEPLAY_KEEP,
    /**/ sizeof(OceffWipe3),
    /**/ OceffWipe3_Init,
    /**/ OceffWipe3_Destroy,
    /**/ OceffWipe3_Update,
    /**/ OceffWipe3_Draw,
};

#include "assets/overlays/ovl_Oceff_Wipe3/ovl_Oceff_Wipe3.c"

s32 D_80989130;

void OceffWipe3_Init(Actor* thisx, PlayState* play) {
    OceffWipe3* this = THIS;

    Actor_SetScale(&this->actor, 0.1f);
    this->counter = 0;
    this->actor.world.pos = GET_ACTIVE_CAM(play)->eye;
}

void OceffWipe3_Destroy(Actor* thisx, PlayState* play) {
    OceffWipe3* this = THIS;

    Magic_Reset(play);
    play->msgCtx.ocarinaSongEffectActive = false;
}

void OceffWipe3_Update(Actor* thisx, PlayState* play) {
    OceffWipe3* this = THIS;

    this->actor.world.pos = GET_ACTIVE_CAM(play)->eye;
    if (this->counter < 100) {
        this->counter++;
    } else {
        Actor_Kill(&this->actor);
    }
}

void OceffWipe3_Draw(Actor* thisx, PlayState* play) {
    u32 scroll = play->state.frames & 0xFFF;
    OceffWipe3* this = THIS;
    f32 z;
    u8 alpha;
    s32 pad[2];
    Vec3f eye = GET_ACTIVE_CAM(play)->eye;
    Vtx* vtxPtr;
    Vec3f quakeOffset;

    Camera_GetQuakeOffset(&quakeOffset, GET_ACTIVE_CAM(play));

    vtxPtr = sSariaSongFrustumVtx;

    if (this->counter < 32) {
        z = Math_SinS(this->counter * 512) * 1220.0f;
    } else {
        z = 1220.0f;
    }

    if (this->counter >= 80) {
        alpha = 12 * (100 - this->counter);
    } else {
        alpha = 255;
    }

    vtxPtr[1].v.cn[3] = vtxPtr[3].v.cn[3] = vtxPtr[5].v.cn[3] = vtxPtr[7].v.cn[3] = vtxPtr[9].v.cn[3] =
        vtxPtr[11].v.cn[3] = vtxPtr[13].v.cn[3] = vtxPtr[15].v.cn[3] = vtxPtr[17].v.cn[3] = vtxPtr[19].v.cn[3] =
            vtxPtr[21].v.cn[3] = alpha;

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL25_Xlu(play->state.gfxCtx);
    Matrix_Translate(eye.x + quakeOffset.x, eye.y + quakeOffset.y, eye.z + quakeOffset.z, MTXMODE_NEW);
    Matrix_Scale(0.1f, 0.1f, 0.1f, MTXMODE_APPLY);
    Matrix_ReplaceRotation(&play->billboardMtxF);
    Matrix_RotateXS(0x708, MTXMODE_APPLY);
    Matrix_Translate(0.0f, 0.0f, -z, MTXMODE_APPLY);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 170, 255);
    gDPSetEnvColor(POLY_XLU_DISP++, 100, 200, 0, 128);
    gSPDisplayList(POLY_XLU_DISP++, &sSariaSongFrustrumMaterialDL);
    gSPDisplayList(POLY_XLU_DISP++, Gfx_TwoTexScroll(play->state.gfxCtx, 0, scroll * 12, scroll * -12, 64, 64, 1,
                                                     scroll * 8, scroll * -8, 64, 64));
    gSPDisplayList(POLY_XLU_DISP++, &sSariaSongFrustumModelDL);

    CLOSE_DISPS(play->state.gfxCtx);
}
