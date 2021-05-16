#include "z_en_snowwd.h"

#define FLAGS 0x00000000

#define THIS ((EnSnowwd*)thisx)

void EnSnowwd_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSnowwd_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSnowwd_Update(Actor* thisx, GlobalContext* globalCtx);
void EnSnowwd_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Snowwd_InitVars = {
    ACTOR_EN_SNOWWD,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_SNOWWD,
    sizeof(EnSnowwd),
    (ActorFunc)EnSnowwd_Init,
    (ActorFunc)EnSnowwd_Destroy,
    (ActorFunc)EnSnowwd_Update,
    (ActorFunc)EnSnowwd_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowwd/EnSnowwd_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowwd/EnSnowwd_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowwd/func_80AF76F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowwd/EnSnowwd_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Snowwd/EnSnowwd_Draw.s")
