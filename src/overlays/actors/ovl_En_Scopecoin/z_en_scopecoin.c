#include "z_en_scopecoin.h"

#define FLAGS 0x00000030

#define THIS ((EnScopecoin*)thisx)

void EnScopecoin_Init(Actor* thisx, GlobalContext* globalCtx);
void EnScopecoin_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnScopecoin_Update(Actor* thisx, GlobalContext* globalCtx);
void EnScopecoin_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80BFCFA0(EnScopecoin* this, GlobalContext* globalCtx);
void func_80BFCFB8(EnScopecoin* this, GlobalContext* globalCtx);

/*
const ActorInit En_Scopecoin_InitVars = {
    ACTOR_EN_SCOPECOIN,
    ACTORCAT_NPC,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnScopecoin),
    (ActorFunc)EnScopecoin_Init,
    (ActorFunc)EnScopecoin_Destroy,
    (ActorFunc)EnScopecoin_Update,
    (ActorFunc)EnScopecoin_Draw
};
*/

void func_80BFCFA0(EnScopecoin* this, GlobalContext* globalCtx) {
    this->actor.shape.rot.y += 500;
}

void func_80BFCFB8(EnScopecoin* this, GlobalContext* globalCtx) {
    if (Actor_GetCollectibleFlag(globalCtx, (this->actor.params & 0x7F0) >> 4)) {
        func_800A7730();
        Actor_MarkForDeath(&this->actor);
    }
}

void EnScopecoin_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnScopecoin* this = THIS;

    Actor_SetScale(&this->actor, 0.01f);
    Actor_SetDrawParams(&this->actor.shape, 0.0f, func_800B3FC0, 10.0f);
    this->unk148 = this->actor.params & 0xF;

    if ((this->unk148 < 0) || (this->unk148 >= 8)) {
        this->unk148 = 0;
    }
    if ((globalCtx->actorCtx.unk5 & 2) != 0) {
        if ((this->unk148 == 2) || (this->unk148 == 6)) {

        } else {
block_8:
            this->actionFunc = func_80BFCFA0;
            this->actor.shape.yOffset = 700.0f;
            return;
        }
        if (Actor_GetCollectibleFlag(globalCtx, (this->actor.params & 0x7F0) >> 4) == 0) {
            goto block_8;
        }
        Actor_MarkForDeath(&this->actor);
        return;
    }
    if (this->unk148 == 2) {
block_11:
        if (Actor_GetCollectibleFlag(globalCtx, (this->actor.params & 0x7F0) >> 4) == 0) {
            this->actor.draw = NULL;
            this->actionFunc = func_80BFCFB8;
            return;
        }
        Actor_MarkForDeath(&this->actor);
        return;
    }
    if (this->unk148 == 6) {
        goto block_11;
    }
    Actor_MarkForDeath(&this->actor);
}

void EnScopecoin_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void EnScopecoin_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnScopecoin* this = THIS;

    this->actionFunc(this, globalCtx);
}

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_Scopecoin_0x80BFCFA0/EnScopecoin_Draw.asm")
