/*
 * File: z_en_okarina_effect.c
 * Overlay: ovl_En_Okarina_Effect
 * Description: Manages the storm created when playing Song of Storms
 */

#include "z_en_okarina_effect.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_2000000)

#define THIS ((EnOkarinaEffect*)thisx)

void EnOkarinaEffect_Init(Actor* thisx, GlobalContext* globalCtx);
void EnOkarinaEffect_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnOkarinaEffect_Update(Actor* thisx, GlobalContext* globalCtx);

void func_8096B104(EnOkarinaEffect* this, GlobalContext* globalCtx);
void func_8096B174(EnOkarinaEffect* this, GlobalContext* globalCtx);
void func_8096B1FC(EnOkarinaEffect* this, GlobalContext* globalCtx);

const ActorInit En_Okarina_Effect_InitVars = {
    ACTOR_EN_OKARINA_EFFECT,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnOkarinaEffect),
    (ActorFunc)EnOkarinaEffect_Init,
    (ActorFunc)EnOkarinaEffect_Destroy,
    (ActorFunc)EnOkarinaEffect_Update,
    (ActorFunc)NULL,
};

void EnOkarinaEffect_SetupAction(EnOkarinaEffect* this, EnOkarinaEffectActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

void EnOkarinaEffect_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void EnOkarinaEffect_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnOkarinaEffect* this = THIS;

    if (globalCtx->envCtx.unk_F2[1]) {
        Actor_MarkForDeath(&this->actor);
    }
    EnOkarinaEffect_SetupAction(this, func_8096B104);
}

void func_8096B104(EnOkarinaEffect* this, GlobalContext* globalCtx) {
    this->unk144 = 0x50;
    globalCtx->envCtx.unk_F2[4] = 0x3C;
    D_801F4E70 = 501.0f;
    globalCtx->envCtx.unk_E3 = 2;
    func_800FD78C(globalCtx);
    EnOkarinaEffect_SetupAction(this, func_8096B174);
}

void func_8096B174(EnOkarinaEffect* this, GlobalContext* globalCtx) {
    DECR(this->unk144);
    if (!globalCtx->pauseCtx.state && !globalCtx->gameOverCtx.state && !globalCtx->msgCtx.unk11F10 &&
        !FrameAdvance_IsEnabled(&globalCtx->state) && this->unk144 == 0) {
        EnOkarinaEffect_SetupAction(this, func_8096B1FC);
    }
}

void func_8096B1FC(EnOkarinaEffect* this, GlobalContext* globalCtx) {
    if (globalCtx->envCtx.unk_F2[4]) {
        if ((globalCtx->state.frames & 3) == 0) {
            --globalCtx->envCtx.unk_F2[4];
            if (globalCtx->envCtx.unk_F2[4] == 8) {
                func_800FD858(globalCtx);
            }
        }
    } else {
        Actor_MarkForDeath(&this->actor);
    }
}

void EnOkarinaEffect_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnOkarinaEffect* this = THIS;

    this->actionFunc(this, globalCtx);
}
