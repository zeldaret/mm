/*
 * File: z_en_boj_03.c
 * Overlay: ovl_En_Boj_03
 * Description: [Empty]
 */

#include "z_en_boj_03.h"

#define FLAGS (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_FRIENDLY | ACTOR_FLAG_10)

#define THIS ((EnBoj03*)thisx)

void EnBoj03_Init(Actor* thisx, PlayState* play);
void EnBoj03_Destroy(Actor* thisx, PlayState* play);
void EnBoj03_Update(Actor* thisx, PlayState* play);
void EnBoj03_Draw(Actor* thisx, PlayState* play);

ActorInit En_Boj_03_InitVars = {
    /**/ ACTOR_EN_BOJ_03,
    /**/ ACTORCAT_NPC,
    /**/ FLAGS,
    /**/ GAMEPLAY_KEEP,
    /**/ sizeof(EnBoj03),
    /**/ EnBoj03_Init,
    /**/ EnBoj03_Destroy,
    /**/ EnBoj03_Update,
    /**/ EnBoj03_Draw,
};

void EnBoj03_Init(Actor* thisx, PlayState* play) {
}

void EnBoj03_Destroy(Actor* thisx, PlayState* play) {
}

void EnBoj03_Update(Actor* thisx, PlayState* play) {
}

void EnBoj03_Draw(Actor* thisx, PlayState* play) {
}
