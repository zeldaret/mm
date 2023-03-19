#include "prevent_bss_reordering.h"
#include "global.h"

#define FLAGS                                                                                               \
    (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10 | ACTOR_FLAG_20 | ACTOR_FLAG_200000 | ACTOR_FLAG_2000000 | \
     ACTOR_FLAG_4000000 | ACTOR_FLAG_80000000)

ActorFunc sPlayerCallInitFunc;
ActorFunc sPlayerCallDestroyFunc;
ActorFunc sPlayerCallUpdateFunc;
ActorFunc sPlayerCallDrawFunc;

void PlayerCall_Init(Actor* thisx, PlayState* play);
void PlayerCall_Destroy(Actor* thisx, PlayState* play);
void PlayerCall_Update(Actor* thisx, PlayState* play);
void PlayerCall_Draw(Actor* thisx, PlayState* play);

ActorInit Player_InitVars = {
    ACTOR_PLAYER,
    ACTORCAT_PLAYER,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(Player),
    (ActorFunc)PlayerCall_Init,
    (ActorFunc)PlayerCall_Destroy,
    (ActorFunc)PlayerCall_Update,
    (ActorFunc)PlayerCall_Draw,
};

void Player_Init(Actor* thisx, PlayState* play);
void Player_Destroy(Actor* thisx, PlayState* play);
void Player_Update(Actor* thisx, PlayState* play);
void Player_Draw(Actor* thisx, PlayState* play);

void PlayerCall_InitFuncPtrs(void) {
    sPlayerCallInitFunc = KaleidoManager_GetRamAddr(Player_Init);
    sPlayerCallDestroyFunc = KaleidoManager_GetRamAddr(Player_Destroy);
    sPlayerCallUpdateFunc = KaleidoManager_GetRamAddr(Player_Update);
    sPlayerCallDrawFunc = KaleidoManager_GetRamAddr(Player_Draw);
}

void PlayerCall_Init(Actor* thisx, PlayState* play) {
    KaleidoScopeCall_LoadPlayer();
    PlayerCall_InitFuncPtrs();
    sPlayerCallInitFunc(thisx, play);
}

void PlayerCall_Destroy(Actor* thisx, PlayState* play) {
    KaleidoScopeCall_LoadPlayer();
    sPlayerCallDestroyFunc(thisx, play);
}

void PlayerCall_Update(Actor* thisx, PlayState* play) {
    KaleidoScopeCall_LoadPlayer();
    sPlayerCallUpdateFunc(thisx, play);
}

void PlayerCall_Draw(Actor* thisx, PlayState* play) {
    KaleidoScopeCall_LoadPlayer();
    sPlayerCallDrawFunc(thisx, play);
}
