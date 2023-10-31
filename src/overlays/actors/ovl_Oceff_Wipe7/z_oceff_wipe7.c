/*
 * File: z_oceff_wipe7.c
 * Overlay: ovl_Oceff_Wipe7
 * Description: Song of Healing Ocarina Effect
 */

#include "z_oceff_wipe7.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_2000000)

#define THIS ((OceffWipe7*)thisx)

void OceffWipe7_Init(Actor* thisx, PlayState* play);
void OceffWipe7_Destroy(Actor* thisx, PlayState* play);
void OceffWipe7_Update(Actor* thisx, PlayState* play);
void OceffWipe7_Draw(Actor* thisx, PlayState* play);

ActorInit Oceff_Wipe7_InitVars = {
    /**/ ACTOR_OCEFF_WIPE7,
    /**/ ACTORCAT_ITEMACTION,
    /**/ FLAGS,
    /**/ GAMEPLAY_KEEP,
    /**/ sizeof(OceffWipe7),
    /**/ OceffWipe7_Init,
    /**/ OceffWipe7_Destroy,
    /**/ OceffWipe7_Update,
    /**/ OceffWipe7_Draw,
};

#include "assets/overlays/ovl_Oceff_Wipe7/ovl_Oceff_Wipe7.c"

s32 D_80BCEB10;

void OceffWipe7_Init(Actor* thisx, PlayState* play) {
    OceffWipe7* this = THIS;

    Actor_SetScale(&this->actor, 1.0f);
    this->counter = 0;
    this->actor.world.pos = GET_ACTIVE_CAM(play)->eye;
}

void OceffWipe7_Destroy(Actor* thisx, PlayState* play) {
    OceffWipe7* this = THIS;

    Magic_Reset(play);
    play->msgCtx.ocarinaSongEffectActive = false;
}

void OceffWipe7_Update(Actor* thisx, PlayState* play) {
    OceffWipe7* this = THIS;

    this->actor.world.pos = GET_ACTIVE_CAM(play)->eye;
    if (this->counter < 100) {
        this->counter++;
    } else {
        Actor_Kill(&this->actor);
    }
}

void OceffWipe7_Draw(Actor* thisx, PlayState* play) {
    OceffWipe7* this = THIS;
    f32 z;
    u8 alpha;
    s32 i;
    s32 counter;
    Vec3f activeCamEye = GET_ACTIVE_CAM(play)->eye;
    s32 pad;
    Vec3f quakeOffset;
    s32 pad2;

    Camera_GetQuakeOffset(&quakeOffset, GET_ACTIVE_CAM(play));

    if (this->counter < 32) {
        z = Math_SinS(this->counter * 0x200) * 1220.0f;
    } else {
        z = 1220.0f;
    }

    if (this->counter >= 80) {
        alpha = 12 * (100 - this->counter);
    } else {
        alpha = 255;
    }

    for (i = 1; i < ARRAY_COUNT(sSongofHealingEffectFrustrumVtx); i += 2) {
        sSongofHealingEffectFrustrumVtx[i].v.cn[3] = alpha;
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
    AnimatedMat_Draw(play, sSongofHealingEffectTexAnim);
    gSPDisplayList(POLY_XLU_DISP++, sSongOfHealingEffectFrustumDL);

    CLOSE_DISPS(play->state.gfxCtx);
}
