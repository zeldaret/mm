#include "global.h"

// #define FLAGS (ACTOR_FLAG_0 | ACTOR_FLAG_2 | ACTOR_FLAG_4 | ACTOR_FLAG_5 | ACTOR_FLAG_25 | ACTOR_FLAG_26)

#define sPlayerCallInitFunc D_801F6B30
#define sPlayerCallDestroyFunc D_801F6B34
#define sPlayerCallUpdateFunc D_801F6B38
#define sPlayerCallDrawFunc D_801F6B3C

extern ActorFunc D_801F6B30;
extern ActorFunc D_801F6B34;
extern ActorFunc D_801F6B38;
extern ActorFunc D_801F6B3C;

#define Player_Init func_80841AC4
#define Player_Destroy func_808470D4
#define Player_Update func_808460B8
#define Player_Draw func_80846528


void Player_Init(Actor* thisx, GlobalContext* globalCtx);
void Player_Destroy(Actor* thisx, GlobalContext* globalCtx);
void Player_Update(Actor* thisx, GlobalContext* globalCtx);
void Player_Draw(Actor* thisx, GlobalContext* globalCtx);


void func_80160A90(void) {
    D_801F6B30 = KaleidoManager_GetRamAddr(func_80841AC4);
    D_801F6B34 = KaleidoManager_GetRamAddr(func_808470D4);
    D_801F6B38 = KaleidoManager_GetRamAddr(func_808460B8);
    D_801F6B3C = KaleidoManager_GetRamAddr(func_80846528);
}

void func_80160AF8(s32 arg0, s32 arg1) {
    KaleidoScopeCall_LoadPlayer();
    func_80160A90();
    D_801F6B30(arg0, arg1);
}

void func_80160B40(s32 arg0, s32 arg1) {
    KaleidoScopeCall_LoadPlayer();
    D_801F6B34(arg0, arg1);
}

void func_80160B80(s32 arg0, s32 arg1) {
    KaleidoScopeCall_LoadPlayer();
    D_801F6B38(arg0, arg1);
}

void func_80160BC0(s32 arg0, s32 arg1) {
    KaleidoScopeCall_LoadPlayer();
    D_801F6B3C(arg0, arg1);
}
