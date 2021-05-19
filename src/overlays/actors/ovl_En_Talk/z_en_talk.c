#include "z_en_talk.h"

#define FLAGS 0x00000009

#define THIS ((EnTalk*)thisx)

void EnTalk_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTalk_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTalk_Update(Actor* thisx, GlobalContext* globalCtx);

/*
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
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Talk_0x80BDDFE0/EnTalk_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Talk_0x80BDDFE0/EnTalk_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Talk_0x80BDDFE0/func_80BDE058.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Talk_0x80BDDFE0/func_80BDE090.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Talk_0x80BDDFE0/EnTalk_Update.asm")
