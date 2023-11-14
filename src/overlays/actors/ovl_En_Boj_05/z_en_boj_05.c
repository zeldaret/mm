/*
 * File: z_en_boj_05.c
 * Overlay: ovl_En_Boj_05
 * Description: [Empty]
 */

#include "z_en_boj_05.h"

#define FLAGS (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_FRIENDLY | ACTOR_FLAG_10)

#define THIS ((EnBoj05*)thisx)

void EnBoj05_Init(Actor* thisx, PlayState* play);
void EnBoj05_Destroy(Actor* thisx, PlayState* play);
void EnBoj05_Update(Actor* thisx, PlayState* play);
void EnBoj05_Draw(Actor* thisx, PlayState* play);

ActorInit En_Boj_05_InitVars = {
    /**/ ACTOR_EN_BOJ_05,
    /**/ ACTORCAT_NPC,
    /**/ FLAGS,
    /**/ GAMEPLAY_KEEP,
    /**/ sizeof(EnBoj05),
    /**/ EnBoj05_Init,
    /**/ EnBoj05_Destroy,
    /**/ EnBoj05_Update,
    /**/ EnBoj05_Draw,
};

void EnBoj05_Init(Actor* thisx, PlayState* play) {
}

void EnBoj05_Destroy(Actor* thisx, PlayState* play) {
}

void EnBoj05_Update(Actor* thisx, PlayState* play) {
}

void EnBoj05_Draw(Actor* thisx, PlayState* play) {
}
