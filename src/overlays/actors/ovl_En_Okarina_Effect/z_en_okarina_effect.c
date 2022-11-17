/*
 * File: z_en_okarina_effect.c
 * Overlay: ovl_En_Okarina_Effect
 * Description: Manages the storm created when playing Song of Storms
 */

#include "z_en_okarina_effect.h"
#include "overlays/kaleido_scope/ovl_kaleido_scope/z_kaleido_scope.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_2000000)

#define THIS ((EnOkarinaEffect*)thisx)

void EnOkarinaEffect_Init(Actor* thisx, PlayState* play);
void EnOkarinaEffect_Destroy(Actor* thisx, PlayState* play);
void EnOkarinaEffect_Update(Actor* thisx, PlayState* play);

void func_8096B104(EnOkarinaEffect* this, PlayState* play);
void func_8096B174(EnOkarinaEffect* this, PlayState* play);
void func_8096B1FC(EnOkarinaEffect* this, PlayState* play);

ActorInit En_Okarina_Effect_InitVars = {
    /**/ ACTOR_EN_OKARINA_EFFECT,
    /**/ ACTORCAT_ITEMACTION,
    /**/ FLAGS,
    /**/ GAMEPLAY_KEEP,
    /**/ sizeof(EnOkarinaEffect),
    /**/ EnOkarinaEffect_Init,
    /**/ EnOkarinaEffect_Destroy,
    /**/ EnOkarinaEffect_Update,
    /**/ NULL,
};

void EnOkarinaEffect_SetupAction(EnOkarinaEffect* this, EnOkarinaEffectActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

void EnOkarinaEffect_Destroy(Actor* thisx, PlayState* play) {
}

void EnOkarinaEffect_Init(Actor* thisx, PlayState* play) {
    EnOkarinaEffect* this = THIS;

    if (play->envCtx.unk_F2[1]) {
        Actor_Kill(&this->actor);
    }
    EnOkarinaEffect_SetupAction(this, func_8096B104);
}

void func_8096B104(EnOkarinaEffect* this, PlayState* play) {
    this->unk144 = 0x50;
    play->envCtx.unk_F2[4] = 0x3C;
    D_801F4E70 = 501.0f;
    play->envCtx.unk_E3 = 2;
    func_800FD78C(play);
    EnOkarinaEffect_SetupAction(this, func_8096B174);
}

void func_8096B174(EnOkarinaEffect* this, PlayState* play) {
    DECR(this->unk144);
    if ((play->pauseCtx.state == PAUSE_STATE_OFF) && (play->gameOverCtx.state == GAMEOVER_INACTIVE) &&
        (play->msgCtx.msgLength == 0) && !FrameAdvance_IsEnabled(&play->state) && (this->unk144 == 0)) {
        EnOkarinaEffect_SetupAction(this, func_8096B1FC);
    }
}

void func_8096B1FC(EnOkarinaEffect* this, PlayState* play) {
    if (play->envCtx.unk_F2[4]) {
        if ((play->state.frames & 3) == 0) {
            play->envCtx.unk_F2[4]--;
            if (play->envCtx.unk_F2[4] == 8) {
                func_800FD858(play);
            }
        }
    } else {
        Actor_Kill(&this->actor);
    }
}

void EnOkarinaEffect_Update(Actor* thisx, PlayState* play) {
    EnOkarinaEffect* this = THIS;

    this->actionFunc(this, play);
}
