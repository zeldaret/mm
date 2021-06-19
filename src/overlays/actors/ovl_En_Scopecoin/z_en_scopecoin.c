#include "z_en_scopecoin.h"

#define FLAGS 0x00000030

#define THIS ((EnScopecoin*)thisx)

void EnScopecoin_Init(Actor* thisx, GlobalContext* globalCtx);
void EnScopecoin_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnScopecoin_Update(Actor* thisx, GlobalContext* globalCtx);
void EnScopecoin_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80BFCFA0(EnScopecoin* this, GlobalContext* globalCtx);
void func_80BFCFB8(EnScopecoin* this, GlobalContext* globalCtx);

const ActorInit En_Scopecoin_InitVars = {
    ACTOR_EN_SCOPECOIN,
    ACTORCAT_NPC,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnScopecoin),
    (ActorFunc)EnScopecoin_Init,
    (ActorFunc)EnScopecoin_Destroy,
    (ActorFunc)EnScopecoin_Update,
    (ActorFunc)EnScopecoin_Draw,
};

void func_80BFCFA0(EnScopecoin* this, GlobalContext* globalCtx) {
    this->actor.shape.rot.y += 500;
}

void func_80BFCFB8(EnScopecoin* this, GlobalContext* globalCtx) {
    if (Actor_GetCollectibleFlag(globalCtx, (this->actor.params & 0x7F0) >> 4)) {
        Item_DropCollectible(globalCtx, &this->actor.world.pos, 2);
        Actor_MarkForDeath(&this->actor);
    }
}

void EnScopecoin_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnScopecoin* this = THIS;

    Actor_SetScale(&this->actor, 0.01f);
    ActorShape_Init(&this->actor.shape, 0, func_800B3FC0, 10.0f);
    this->unk148 = (this->actor.params & 0xF);
    if (this->unk148 < 0 || this->unk148 >= 8) {
        this->unk148 = 0;
    }

    if (globalCtx->actorCtx.unk5 & 2) {
        if (this->unk148 == 2 || this->unk148 == 6) {
            if (Actor_GetCollectibleFlag(globalCtx, (this->actor.params & 0x7F0) >> 4)) {
                Actor_MarkForDeath(&this->actor);
                return;
            }
        }
        this->actor.shape.yOffset = 700.0f;
        this->actionFunc = func_80BFCFA0;
        return;
    }
    if (this->unk148 == 2 || this->unk148 == 6) {
        if (Actor_GetCollectibleFlag(globalCtx, (this->actor.params & 0x7F0) >> 4)) {
            Actor_MarkForDeath(&this->actor);
        } else {
            this->actor.draw = NULL;
            this->actionFunc = func_80BFCFB8;
        }
    } else {
        Actor_MarkForDeath(&this->actor);
    }
}

void EnScopecoin_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void EnScopecoin_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnScopecoin* this = THIS;

    this->actionFunc(this, globalCtx);
}

static UNK_PTR D_80BFD280[] = { &D_04061FC0, &D_04061FE0, &D_04062000, &D_04062040,
                                &D_04062020, &D_04062060, &D_04062000 };

void EnScopecoin_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnScopecoin* this = THIS;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;

    func_8012C28C(globalCtx->state.gfxCtx);
    func_800B8050(&this->actor, globalCtx, 0);
    OPEN_DISPS(gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80BFD280[this->unk148]));
    gSPDisplayList(POLY_OPA_DISP++, D_040622C0);

    CLOSE_DISPS(gfxCtx);
}
