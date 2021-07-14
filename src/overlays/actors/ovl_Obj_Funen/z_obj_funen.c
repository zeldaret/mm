#include "z_obj_funen.h"

#define FLAGS 0x00000030

#define THIS ((ObjFunen*)thisx)

void ObjFunen_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjFunen_Draw(Actor* thisx, GlobalContext* globalCtx);

const ActorInit Obj_Funen_InitVars = {
    ACTOR_OBJ_FUNEN,       ACTORCAT_PROP,         FLAGS,
    OBJECT_FUNEN,          sizeof(ObjFunen),      (ActorFunc)ObjFunen_Init,
    (ActorFunc)Actor_Noop, (ActorFunc)Actor_Noop, (ActorFunc)ObjFunen_Draw,
};

extern Gfx D_060000D0[];

f32 D_80A198D0[] = { 0.1f, 0.024390244f };

void ObjFunen_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjFunen* this = THIS;

    Actor_SetScale(&this->actor, D_80A198D0[this->actor.params & 1]);
}

void ObjFunen_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 temp;
    s32 pad[2];

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C2DC(globalCtx->state.gfxCtx);
    Matrix_RotateY((s16)(func_800DFCDC(ACTIVE_CAM) - 0x8000), 1);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);

    temp = -(globalCtx->gameplayFrames & 0x7FFFFFFF) & 0x7F;

    gSPSegment(POLY_XLU_DISP++, 0x08,
               Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0, temp, 0x20, 0x20, 1, 0, temp, 0x20, 0x20));
    gSPDisplayList(POLY_XLU_DISP++, D_060000D0);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
