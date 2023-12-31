/*
 * File: z_en_boj_04.c
 * Overlay: ovl_En_Boj_04
 * Description: [Empty]
 */

#include "z_en_boj_04.h"

#define FLAGS (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_FRIENDLY | ACTOR_FLAG_10)

#define THIS ((EnBoj04*)thisx)

void EnBoj04_Init(Actor* thisx, PlayState* play);
void EnBoj04_Destroy(Actor* thisx, PlayState* play);
void EnBoj04_Update(Actor* thisx, PlayState* play);
void EnBoj04_Draw(Actor* thisx, PlayState* play);

ActorInit En_Boj_04_InitVars = {
    /**/ ACTOR_EN_BOJ_04,
    /**/ ACTORCAT_NPC,
    /**/ FLAGS,
    /**/ GAMEPLAY_KEEP,
    /**/ sizeof(EnBoj04),
    /**/ EnBoj04_Init,
    /**/ EnBoj04_Destroy,
    /**/ EnBoj04_Update,
    /**/ EnBoj04_Draw,
};

void EnBoj04_Init(Actor* thisx, PlayState* play) {
}

void EnBoj04_Destroy(Actor* thisx, PlayState* play) {
}

void EnBoj04_Update(Actor* thisx, PlayState* play) {
}

void EnBoj04_Draw(Actor* thisx, PlayState* play) {
}
