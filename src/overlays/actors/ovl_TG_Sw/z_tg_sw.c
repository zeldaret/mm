#include "z_tg_sw.h"

#define FLAGS 0x00000010

#define THIS ((TGSw*)thisx)

void TGSw_Init(Actor* thisx, GlobalContext* globalCtx);
void TGSw_Destroy(Actor* thisx, GlobalContext* globalCtx);
void TGSw_Update(Actor* thisx, GlobalContext* globalCtx);
void TGSw_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit TG_Sw_InitVars = {
    ACTOR_TG_SW,
    ACTORTYPE_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(TGSw),
    (ActorFunc)TGSw_Init,
    (ActorFunc)TGSw_Destroy,
    (ActorFunc)TGSw_Update,
    (ActorFunc)TGSw_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_TG_Sw_0x80B19F60/func_80B19F60.asm")

GLOBAL_ASM("asm/non_matchings/ovl_TG_Sw_0x80B19F60/func_80B1A008.asm")

GLOBAL_ASM("asm/non_matchings/ovl_TG_Sw_0x80B19F60/TGSw_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_TG_Sw_0x80B19F60/TGSw_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_TG_Sw_0x80B19F60/TGSw_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_TG_Sw_0x80B19F60/TGSw_Draw.asm")
