#include "z_en_zl1.h"

#define FLAGS 0x00000019

#define THIS ((EnZl1*)thisx)

void EnZl1_Init(Actor* thisx, GlobalContext* globalCtx);
void EnZl1_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnZl1_Update(Actor* thisx, GlobalContext* globalCtx);
void EnZl1_Draw(Actor* thisx, GlobalContext* globalCtx);

const ActorInit En_Zl1_InitVars = {
    ACTOR_EN_ZL1,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_ZL1,
    sizeof(EnZl1),
    (ActorFunc)EnZl1_Init,
    (ActorFunc)EnZl1_Destroy,
    (ActorFunc)EnZl1_Update,
    (ActorFunc)EnZl1_Draw,
};

void EnZl1_Init(Actor* thisx, GlobalContext* globalCtx) {
}
void EnZl1_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}
void EnZl1_Update(Actor* thisx, GlobalContext* globalCtx) {
}
void EnZl1_Draw(Actor* thisx, GlobalContext* globalCtx) {
}
