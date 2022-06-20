/*
 * File: z_en_boj_05.c
 * Overlay: ovl_En_Boj_05
 * Description: [Empty]
 */

#include "z_en_boj_05.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10)

#define THIS ((EnBoj05*)thisx)

void EnBoj05_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBoj05_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBoj05_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBoj05_Draw(Actor* thisx, GlobalContext* globalCtx);

const ActorInit En_Boj_05_InitVars = {
    ACTOR_EN_BOJ_05,
    ACTORCAT_NPC,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnBoj05),
    (ActorFunc)EnBoj05_Init,
    (ActorFunc)EnBoj05_Destroy,
    (ActorFunc)EnBoj05_Update,
    (ActorFunc)EnBoj05_Draw,
};

void EnBoj05_Init(Actor* thisx, GlobalContext* globalCtx) {
}
void EnBoj05_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}
void EnBoj05_Update(Actor* thisx, GlobalContext* globalCtx) {
}
void EnBoj05_Draw(Actor* thisx, GlobalContext* globalCtx) {
}
