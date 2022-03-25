/*
 * File: z_en_scopecoin.c
 * Overlay: ovl_En_Scopecoin
 * Description: Termina Field rupees visible from the telescope
 */

#include "z_en_scopecoin.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

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
    if (Flags_GetCollectible(globalCtx, (this->actor.params & 0x7F0) >> 4)) {
        Item_DropCollectible(globalCtx, &this->actor.world.pos, ITEM00_RUPEE_RED);
        Actor_MarkForDeath(&this->actor);
    }
}

void EnScopecoin_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnScopecoin* this = THIS;

    Actor_SetScale(&this->actor, 0.01f);
    ActorShape_Init(&this->actor.shape, 0, ActorShadow_DrawCircle, 10.0f);
    this->unk148 = (this->actor.params & 0xF);
    if (this->unk148 < 0 || this->unk148 >= 8) {
        this->unk148 = 0;
    }

    if (globalCtx->actorCtx.unk5 & 2) {
        if (this->unk148 == 2 || this->unk148 == 6) {
            if (Flags_GetCollectible(globalCtx, (this->actor.params & 0x7F0) >> 4)) {
                Actor_MarkForDeath(&this->actor);
                return;
            }
        }
        this->actor.shape.yOffset = 700.0f;
        this->actionFunc = func_80BFCFA0;
        return;
    }
    if (this->unk148 == 2 || this->unk148 == 6) {
        if (Flags_GetCollectible(globalCtx, (this->actor.params & 0x7F0) >> 4)) {
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

static TexturePtr D_80BFD280[] = {
    gameplay_keep_Tex_061FC0, gameplay_keep_Tex_061FE0, gameplay_keep_Tex_062000, gameplay_keep_Tex_062040,
    gameplay_keep_Tex_062020, gameplay_keep_Tex_062060, gameplay_keep_Tex_062000,
};

void EnScopecoin_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnScopecoin* this = THIS;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;

    func_8012C28C(globalCtx->state.gfxCtx);
    func_800B8050(&this->actor, globalCtx, 0);
    OPEN_DISPS(gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80BFD280[this->unk148]));
    gSPDisplayList(POLY_OPA_DISP++, gameplay_keep_DL_0622C0);

    CLOSE_DISPS(gfxCtx);
}
