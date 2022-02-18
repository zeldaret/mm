/*
 * File: z_bg_lbfshot.c
 * Overlay: ovl_Bg_Lbfshot
 * Description: Rainbow Hookshot Pillar
 */

#include "z_bg_lbfshot.h"
#include "objects/object_lbfshot/object_lbfshot.h"

#define FLAGS 0x00000000

#define THIS ((BgLbfshot*)thisx)

void BgLbfshot_Init(Actor* thisx, GlobalContext* globalCtx);
void BgLbfshot_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgLbfshot_Draw(Actor* thisx, GlobalContext* globalCtx);

const ActorInit Bg_Lbfshot_InitVars = {
    ACTOR_BG_LBFSHOT,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_LBFSHOT,
    sizeof(BgLbfshot),
    (ActorFunc)BgLbfshot_Init,
    (ActorFunc)BgLbfshot_Destroy,
    (ActorFunc)Actor_Noop,
    (ActorFunc)BgLbfshot_Draw,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

void BgLbfshot_Init(Actor* thisx, GlobalContext* globalCtx) {
    BgLbfshot* this = THIS;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    this->dyna.actor.uncullZoneForward = 4000.0f;
    DynaPolyActor_Init(&this->dyna, 1);
    DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &object_lbfshot_Colheader_0014D8);
}
void BgLbfshot_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    BgLbfshot* this = THIS;

    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
}
void BgLbfshot_Draw(Actor* thisx, GlobalContext* globalCtx) {
    Gfx_DrawDListOpa(globalCtx, object_lbfshot_DL_000228);
}
