/*
 * File: z_en_firefly2.c
 * Overlay: ovl_En_Firefly2
 * Description: [Empty]
 */

#include "z_en_firefly2.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_10 | ACTOR_FLAG_1000 | ACTOR_FLAG_4000)

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
