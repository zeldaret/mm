/*
 * File: z_en_boj_02.c
 * Overlay: ovl_En_Boj_02
 * Description: [Empty]
 */

#include "z_en_boj_02.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10)

#define THIS ((EnBoj02*)thisx)

void EnBoj02_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBoj02_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBoj02_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBoj02_Draw(Actor* thisx, GlobalContext* globalCtx);

const ActorInit En_Boj_02_InitVars = {
    ACTOR_EN_BOJ_02,
    ACTORCAT_NPC,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnBoj02),
    (ActorFunc)EnBoj02_Init,
    (ActorFunc)EnBoj02_Destroy,
    (ActorFunc)EnBoj02_Update,
    (ActorFunc)EnBoj02_Draw,
};

void EnBoj02_Init(Actor* thisx, GlobalContext* globalCtx) {
}
void EnBoj02_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}
void EnBoj02_Update(Actor* thisx, GlobalContext* globalCtx) {
}
void EnBoj02_Draw(Actor* thisx, GlobalContext* globalCtx) {
}
