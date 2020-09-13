#include "z_demo_shd.h"

#define FLAGS 0x00000030

#define THIS ((DemoShd*)thisx)

void DemoShd_Init(Actor* thisx, GlobalContext* globalCtx);
void DemoShd_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DemoShd_Update(Actor* thisx, GlobalContext* globalCtx);
void DemoShd_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Demo_Shd_InitVars = {
    ACTOR_DEMO_SHD,
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_FWALL,
    sizeof(DemoShd),
    (ActorFunc)DemoShd_Init,
    (ActorFunc)DemoShd_Destroy,
    (ActorFunc)DemoShd_Update,
    (ActorFunc)DemoShd_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Demo_Shd_0x8092C530/DemoShd_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Demo_Shd_0x8092C530/DemoShd_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Demo_Shd_0x8092C530/DemoShd_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Demo_Shd_0x8092C530/DemoShd_Draw.asm")
