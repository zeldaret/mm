/*
 * File: z_en_boj_04.c
 * Overlay: ovl_En_Boj_04
 * Description: [Empty]
 */

#include "z_en_boj_04.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10)

#define THIS ((EnBoj04*)thisx)

void EnBoj04_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBoj04_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBoj04_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBoj04_Draw(Actor* thisx, GlobalContext* globalCtx);

const ActorInit En_Boj_04_InitVars = {
    ACTOR_EN_BOJ_04,
    ACTORCAT_NPC,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnBoj04),
    (ActorFunc)EnBoj04_Init,
    (ActorFunc)EnBoj04_Destroy,
    (ActorFunc)EnBoj04_Update,
    (ActorFunc)EnBoj04_Draw,
};

void EnBoj04_Init(Actor* thisx, GlobalContext* globalCtx) {
}
void EnBoj04_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}
void EnBoj04_Update(Actor* thisx, GlobalContext* globalCtx) {
}
void EnBoj04_Draw(Actor* thisx, GlobalContext* globalCtx) {
}
