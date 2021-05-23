#include "z_en_boj_01.h"

#define FLAGS 0x00000019

#define THIS ((EnBoj01*)thisx)

void EnBoj01_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBoj01_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBoj01_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBoj01_Draw(Actor* thisx, GlobalContext* globalCtx);

const ActorInit En_Boj_01_InitVars = {
    ACTOR_EN_BOJ_01,
    ACTORCAT_NPC,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnBoj01),
    (ActorFunc)EnBoj01_Init,
    (ActorFunc)EnBoj01_Destroy,
    (ActorFunc)EnBoj01_Update,
    (ActorFunc)EnBoj01_Draw,
};

void EnBoj01_Init(Actor* thisx, GlobalContext* globalCtx) {
}
void EnBoj01_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}
void EnBoj01_Update(Actor* thisx, GlobalContext* globalCtx) {
}
void EnBoj01_Draw(Actor* thisx, GlobalContext* globalCtx) {
}
