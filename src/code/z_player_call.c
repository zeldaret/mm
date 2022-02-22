#include "global.h"

// #define FLAGS (ACTOR_FLAG_0 | ACTOR_FLAG_2 | ACTOR_FLAG_4 | ACTOR_FLAG_5 | ACTOR_FLAG_25 | ACTOR_FLAG_26)

extern ActorFunc sPlayerCallInitFunc;
extern ActorFunc sPlayerCallDestroyFunc;
extern ActorFunc sPlayerCallUpdateFunc;
extern ActorFunc sPlayerCallDrawFunc;


void Player_Init(Actor* thisx, GlobalContext* globalCtx);
void Player_Destroy(Actor* thisx, GlobalContext* globalCtx);
void Player_Update(Actor* thisx, GlobalContext* globalCtx);
void Player_Draw(Actor* thisx, GlobalContext* globalCtx);


void PlayerCall_InitFuncPtrs(void) {
    sPlayerCallInitFunc = KaleidoManager_GetRamAddr(Player_Init);
    sPlayerCallDestroyFunc = KaleidoManager_GetRamAddr(Player_Destroy);
    sPlayerCallUpdateFunc = KaleidoManager_GetRamAddr(Player_Update);
    sPlayerCallDrawFunc = KaleidoManager_GetRamAddr(Player_Draw);
}

void PlayerCall_Init(s32 arg0, s32 arg1) {
    KaleidoScopeCall_LoadPlayer();
    PlayerCall_InitFuncPtrs();
    sPlayerCallInitFunc(arg0, arg1);
}

void PlayerCall_Destroy(s32 arg0, s32 arg1) {
    KaleidoScopeCall_LoadPlayer();
    sPlayerCallDestroyFunc(arg0, arg1);
}

void PlayerCall_Update(s32 arg0, s32 arg1) {
    KaleidoScopeCall_LoadPlayer();
    sPlayerCallUpdateFunc(arg0, arg1);
}

void PlayerCall_Draw(s32 arg0, s32 arg1) {
    KaleidoScopeCall_LoadPlayer();
    sPlayerCallDrawFunc(arg0, arg1);
}
