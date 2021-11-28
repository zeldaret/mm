/*
 * File: z_en_talk.c
 * Overlay: ovl_En_Talk
 * Description: Green Target Spot (e.g., Indigo-Go's Poster)
 */

#include "z_en_talk.h"

#define FLAGS 0x00000009

#define THIS ((EnTalk*)thisx)

void EnTalk_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTalk_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTalk_Update(Actor* thisx, GlobalContext* globalCtx);

void func_80BDE058(EnTalk* this, GlobalContext* globalCtx);
void func_80BDE090(EnTalk* this, GlobalContext* globalCtx);

#if 0
const ActorInit En_Talk_InitVars = {
    ACTOR_EN_TALK,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnTalk),
    (ActorFunc)EnTalk_Init,
    (ActorFunc)EnTalk_Destroy,
    (ActorFunc)EnTalk_Update,
    (ActorFunc)NULL,
};

#endif

void EnTalk_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnTalk* this = THIS;
    s8 temp_v0;

    temp_v0 = this->actor.home.rot.x - 0x1;

    if (temp_v0 >= 0x0 && temp_v0 < 0x7) {
        this->actor.targetMode = temp_v0;
    }

    Actor_SetScale(&this->actor, 1.0f);
    this->actionFunc = func_80BDE090;
    this->actor.textId = (this->actor.params & 0x3F) + 0x1C00;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk/EnTalk_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk/func_80BDE058.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk/func_80BDE090.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Talk/EnTalk_Update.s")
