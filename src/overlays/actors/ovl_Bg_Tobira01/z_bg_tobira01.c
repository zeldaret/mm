#include "z_bg_tobira01.h"

#define FLAGS 0x00000030

#define THIS ((BgTobira01*)thisx)

void BgTobira01_Init(Actor* thisx, GlobalContext* globalCtx);
void BgTobira01_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgTobira01_Update(Actor* thisx, GlobalContext* globalCtx);
void BgTobira01_Draw(Actor* thisx, GlobalContext* globalCtx);

const ActorInit Bg_Tobira01_InitVars = {
    ACTOR_BG_TOBIRA01,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_SPOT11_OBJ,
    sizeof(BgTobira01),
    (ActorFunc)BgTobira01_Init,
    (ActorFunc)BgTobira01_Destroy,
    (ActorFunc)BgTobira01_Update,
    (ActorFunc)BgTobira01_Draw,
};

extern Gfx D_06000088[];
extern CollisionHeader D_060011C0;

void func_80B12430(BgTobira01* this, GlobalContext* globalCtx);
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Tobira01_0x80B12430/func_80B12430.asm")

void BgTobira01_Init(Actor* thisx, GlobalContext* globalCtx) {
    BgTobira01* this = THIS;
    s32 pad;

    BcCheck3_BgActorInit(&this->dyna, 1);
    BgCheck3_LoadMesh(globalCtx, &this->dyna, &D_060011C0);
    gSaveContext.weekEventReg[88] &= 0xBF;
    Actor_SetScale(&this->dyna.actor, 1.0f);
    this->isNight = gSaveContext.isNight;
    this->timer = 0;
    this->actionFunc = func_80B12430;
}

void BgTobira01_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    BgTobira01* this = THIS;
    s32 pad;

    BgCheck_RemoveActorMesh(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
}

void BgTobira01_Update(Actor* thisx, GlobalContext* globalCtx) {
    BgTobira01* this = THIS;
    s32 pad;

    this->actionFunc(this, globalCtx);
}

void BgTobira01_Draw(Actor* thisx, GlobalContext* globalCtx) {
    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, D_06000088);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
