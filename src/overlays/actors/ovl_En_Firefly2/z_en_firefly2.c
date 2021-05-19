#include "z_en_firefly2.h"

#define FLAGS 0x00005015

#define THIS ((EnFirefly2*)thisx)

void EnFirefly2_Init(Actor* thisx, GlobalContext* globalCtx);
void EnFirefly2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnFirefly2_Update(Actor* thisx, GlobalContext* globalCtx);
void EnFirefly2_Draw(Actor* thisx, GlobalContext* globalCtx);

const ActorInit En_Firefly2_InitVars = {
    ACTOR_EN_FIREFLY2,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_FIREFLY,
    sizeof(EnFirefly2),
    (ActorFunc)EnFirefly2_Init,
    (ActorFunc)EnFirefly2_Destroy,
    (ActorFunc)EnFirefly2_Update,
    (ActorFunc)EnFirefly2_Draw,
};

void EnFirefly2_Init(Actor* thisx, GlobalContext* globalCtx) {
}
void EnFirefly2_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}
void EnFirefly2_Update(Actor* thisx, GlobalContext* globalCtx) {
}
void EnFirefly2_Draw(Actor* thisx, GlobalContext* globalCtx) {
}
