/*
 * File: z_demo_shd.c
 * Overlay: ovl_Demo_Shd
 * Description:
 */

#include "z_demo_shd.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((DemoShd*)thisx)

void DemoShd_Init(Actor* thisx, GlobalContext* globalCtx);
void DemoShd_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DemoShd_Update(Actor* thisx, GlobalContext* globalCtx);
void DemoShd_Draw(Actor* thisx, GlobalContext* globalCtx);

const ActorInit Demo_Shd_InitVars = {
    ACTOR_DEMO_SHD,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_FWALL,
    sizeof(DemoShd),
    (ActorFunc)DemoShd_Init,
    (ActorFunc)DemoShd_Destroy,
    (ActorFunc)DemoShd_Update,
    (ActorFunc)DemoShd_Draw,
};

void DemoShd_Init(Actor* thisx, GlobalContext* globalCtx) {
}
void DemoShd_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}
void DemoShd_Update(Actor* thisx, GlobalContext* globalCtx) {
}
void DemoShd_Draw(Actor* thisx, GlobalContext* globalCtx) {
}
