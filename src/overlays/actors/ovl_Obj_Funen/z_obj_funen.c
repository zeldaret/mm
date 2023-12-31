/*
 * File: z_obj_funen.c
 * Overlay: ovl_Obj_Funen
 * Description: Unused(?) Stone Tower smoke
 */

#include "z_obj_funen.h"
#include "objects/object_funen/object_funen.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((ObjFunen*)thisx)

void ObjFunen_Init(Actor* thisx, PlayState* play);
void ObjFunen_Draw(Actor* thisx, PlayState* play);

ActorInit Obj_Funen_InitVars = {
    /**/ ACTOR_OBJ_FUNEN,
    /**/ ACTORCAT_PROP,
    /**/ FLAGS,
    /**/ OBJECT_FUNEN,
    /**/ sizeof(ObjFunen),
    /**/ ObjFunen_Init,
    /**/ Actor_Noop,
    /**/ Actor_Noop,
    /**/ ObjFunen_Draw,
};

f32 D_80A198D0[] = { 0.1f, 0.024390244f };

void ObjFunen_Init(Actor* thisx, PlayState* play) {
    ObjFunen* this = THIS;

    Actor_SetScale(&this->actor, D_80A198D0[this->actor.params & 1]);
}

void ObjFunen_Draw(Actor* thisx, PlayState* play) {
    s32 temp;
    s32 pad[2];

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL25_Xlu(play->state.gfxCtx);
    Matrix_RotateYS((s16)(Camera_GetCamDirYaw(GET_ACTIVE_CAM(play)) - 0x8000), MTXMODE_APPLY);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);

    temp = -(play->gameplayFrames & 0x7FFFFFFF) & 0x7F;

    gSPSegment(POLY_XLU_DISP++, 0x08,
               Gfx_TwoTexScroll(play->state.gfxCtx, 0, 0, temp, 0x20, 0x20, 1, 0, temp, 0x20, 0x20));
    gSPDisplayList(POLY_XLU_DISP++, gStoneTowerSmokeDL);
    CLOSE_DISPS(play->state.gfxCtx);
}
