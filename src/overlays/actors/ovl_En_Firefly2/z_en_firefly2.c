/*
 * File: z_en_firefly2.c
 * Overlay: ovl_En_Firefly2
 * Description: [Empty]
 */

#include "z_en_firefly2.h"

#define FLAGS \
    (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_UNFRIENDLY | ACTOR_FLAG_10 | ACTOR_FLAG_IGNORE_QUAKE | ACTOR_FLAG_4000)

#define THIS ((EnFirefly2*)thisx)

void EnFirefly2_Init(Actor* thisx, PlayState* play);
void EnFirefly2_Destroy(Actor* thisx, PlayState* play);
void EnFirefly2_Update(Actor* thisx, PlayState* play);
void EnFirefly2_Draw(Actor* thisx, PlayState* play);

ActorInit En_Firefly2_InitVars = {
    /**/ ACTOR_EN_FIREFLY2,
    /**/ ACTORCAT_ENEMY,
    /**/ FLAGS,
    /**/ OBJECT_FIREFLY,
    /**/ sizeof(EnFirefly2),
    /**/ EnFirefly2_Init,
    /**/ EnFirefly2_Destroy,
    /**/ EnFirefly2_Update,
    /**/ EnFirefly2_Draw,
};

void EnFirefly2_Init(Actor* thisx, PlayState* play) {
}
void EnFirefly2_Destroy(Actor* thisx, PlayState* play) {
}
void EnFirefly2_Update(Actor* thisx, PlayState* play) {
}
void EnFirefly2_Draw(Actor* thisx, PlayState* play) {
}
