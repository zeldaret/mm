/*
 * File: z_obj_visiblock.c
 * Overlay: ovl_Obj_Visiblock
 * Description: Lens of Truth Platform
 */

#include "z_obj_visiblock.h"
#include "objects/object_visiblock/object_visiblock.h"

#define FLAGS (ACTOR_FLAG_80)

#define THIS ((ObjVisiblock*)thisx)

void ObjVisiblock_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjVisiblock_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjVisiblock_Draw(Actor* thisx, GlobalContext* globalCtx);

const ActorInit Obj_Visiblock_InitVars = {
    ACTOR_OBJ_VISIBLOCK,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_VISIBLOCK,
    sizeof(ObjVisiblock),
    (ActorFunc)ObjVisiblock_Init,
    (ActorFunc)ObjVisiblock_Destroy,
    (ActorFunc)Actor_Noop,
    (ActorFunc)ObjVisiblock_Draw,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 150, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

void ObjVisiblock_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjVisiblock* this = THIS;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    DynaPolyActor_Init(&this->dyna, 0);
    DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &object_visiblock_Colheader_000AD0);
}

void ObjVisiblock_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    ObjVisiblock* this = THIS;

    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
}

void ObjVisiblock_Draw(Actor* thisx, GlobalContext* globalCtx) {
    Gfx_DrawDListXlu(globalCtx, object_visiblock_DL_000140);
}
