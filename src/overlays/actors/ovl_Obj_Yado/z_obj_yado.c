/*
 * File: z_obj_yado.c
 * Overlay: ovl_Obj_Yado
 * Description: Stockpot Inn - 2nd Floor Window
 */

#include "z_obj_yado.h"
#include "objects/object_yado_obj/object_yado_obj.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((ObjYado*)thisx)

void ObjYado_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjYado_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjYado_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjYado_Draw(Actor* thisx, GlobalContext* globalCtx);

const ActorInit Obj_Yado_InitVars = {
    ACTOR_OBJ_YADO,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_YADO_OBJ,
    sizeof(ObjYado),
    (ActorFunc)ObjYado_Init,
    (ActorFunc)ObjYado_Destroy,
    (ActorFunc)ObjYado_Update,
    (ActorFunc)ObjYado_Draw,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

AnimatedMaterial* D_80C16470;

void ObjYado_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjYado* this = THIS;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    D_80C16470 = Lib_SegmentedToVirtual(object_yado_obj_Matanimheader_0012E8);
    this->isNight = gSaveContext.save.isNight;
}

void ObjYado_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void ObjYado_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjYado* this = THIS;

    this->isNight = gSaveContext.save.isNight;
}

void ObjYado_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    ObjYado* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    if (this->isNight) {
        gSPSegment(POLY_XLU_DISP++, 0x09, Gfx_PrimColor(globalCtx->state.gfxCtx, 128, 95, 95, 70, 155));
        gSPSegment(POLY_OPA_DISP++, 0x0A, Gfx_PrimColor(globalCtx->state.gfxCtx, 128, 0, 40, 40, 255));
    } else {
        gSPSegment(POLY_XLU_DISP++, 0x09, Gfx_PrimColor(globalCtx->state.gfxCtx, 128, 255, 255, 215, 110));
        gSPSegment(POLY_OPA_DISP++, 0x0A, Gfx_PrimColor(globalCtx->state.gfxCtx, 128, 255, 255, 215, 255));
    }

    AnimatedMat_Draw(globalCtx, D_80C16470);
    Gfx_DrawDListOpa(globalCtx, object_yado_obj_DL_000430);
    Gfx_DrawDListXlu(globalCtx, object_yado_obj_DL_000320);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
