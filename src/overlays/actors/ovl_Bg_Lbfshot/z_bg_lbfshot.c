#include "z_bg_lbfshot.h"

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

extern CollisionHeader D_060014D8;
extern Gfx D_06000228[];

void BgLbfshot_Init(Actor* thisx, GlobalContext* globalCtx) {
    BgLbfshot* this = THIS;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    this->dyna.actor.uncullZoneForward = 4000.0f;
    BcCheck3_BgActorInit(&this->dyna, 1);
    BgCheck3_LoadMesh(globalCtx, &this->dyna, &D_060014D8);
}
void BgLbfshot_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    BgLbfshot* this = THIS;

    BgCheck_RemoveActorMesh(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
}
void BgLbfshot_Draw(Actor* thisx, GlobalContext* globalCtx) {
    func_800BDFC0(globalCtx, D_06000228);
}
