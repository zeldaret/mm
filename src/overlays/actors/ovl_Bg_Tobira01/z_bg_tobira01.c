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

void BgTobira01_Open(BgTobira01* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    s16 cutsceneId = this->dyna.actor.cutscene;
    s16 prevTimer;

    if (this->playCutscene) {
        if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
        } else if (ActorCutscene_GetCanPlayNext(cutsceneId)) {
            ActorCutscene_StartAndSetUnkLinkFields(cutsceneId, &this->dyna.actor);
            gSaveContext.weekEventReg[88] |= 0x40;
            this->playCutscene = false;
        } else {
            ActorCutscene_SetIntentToPlay(cutsceneId);
        }
    } else if (!(gSaveContext.weekEventReg[88] & 0x40) && (this->timer == 0) && (globalCtx->actorCtx.unk1F5 != 0) &&
               (globalCtx->actorCtx.unk1F4 == 0) &&
               (func_800C99AC(&globalCtx->colCtx, player->actor.floorPoly, player->actor.floorBgId) == 6)) {
        this->playCutscene = true;
        this->unk_16C = 0; // this variable is not used anywhere else
    }

    prevTimer = this->timer;

    if (gSaveContext.weekEventReg[88] & 0x40) {
        this->timer++;
    } else {
        this->timer--;
    };

    this->timer = CLAMP(this->timer, 0, 60);

    if (this->timer != prevTimer) {
        if (1) {}
        Audio_PlayActorSound2(&this->dyna.actor, NA_SE_EV_STONEDOOR_OPEN_S - SFX_FLAG);
        this->dyna.actor.world.pos.y = (this->yOffset = (this->timer * (5.0f / 3.0f)) + this->dyna.actor.home.pos.y);
        this->timer2 = 180;
    }

    if (!(player->stateFlags1 & 0x40) && (gSaveContext.weekEventReg[88] & 0x40) && (DECR(this->timer2) == 0)) {
        gSaveContext.weekEventReg[88] &= (u8)~0x40;
    }
}

void BgTobira01_Init(Actor* thisx, GlobalContext* globalCtx) {
    BgTobira01* this = THIS;
    s32 pad;

    BcCheck3_BgActorInit(&this->dyna, 1);
    BgCheck3_LoadMesh(globalCtx, &this->dyna, &D_060011C0);
    gSaveContext.weekEventReg[88] &= (u8)~0x40;
    Actor_SetScale(&this->dyna.actor, 1.0f);
    this->timer2 = gSaveContext.isNight;
    this->timer = 0;
    this->actionFunc = BgTobira01_Open;
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
