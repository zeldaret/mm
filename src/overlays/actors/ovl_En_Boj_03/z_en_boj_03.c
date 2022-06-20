/*
 * File: z_en_boj_03.c
 * Overlay: ovl_En_Boj_03
 * Description: [Empty]
 */

#include "z_en_boj_03.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10)

#define THIS ((EnBoj03*)thisx)

void EnBoj03_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBoj03_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBoj03_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBoj03_Draw(Actor* thisx, GlobalContext* globalCtx);

const ActorInit En_Boj_03_InitVars = {
    ACTOR_EN_BOJ_03,
    ACTORCAT_NPC,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnBoj03),
    (ActorFunc)EnBoj03_Init,
    (ActorFunc)EnBoj03_Destroy,
    (ActorFunc)EnBoj03_Update,
    (ActorFunc)EnBoj03_Draw,
};

void EnBoj03_Init(Actor* thisx, GlobalContext* globalCtx) {
}
void EnBoj03_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}
void EnBoj03_Update(Actor* thisx, GlobalContext* globalCtx) {
}
void EnBoj03_Draw(Actor* thisx, GlobalContext* globalCtx) {
}
