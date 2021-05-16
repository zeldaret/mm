#include "z_en_jc_mato.h"

#define FLAGS 0x00004030

#define THIS ((EnJcMato*)thisx)

void EnJcMato_Init(Actor* thisx, GlobalContext* globalCtx);
void EnJcMato_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnJcMato_Update(Actor* thisx, GlobalContext* globalCtx);
void EnJcMato_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Jc_Mato_InitVars = {
    ACTOR_EN_JC_MATO,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_TRU,
    sizeof(EnJcMato),
    (ActorFunc)EnJcMato_Init,
    (ActorFunc)EnJcMato_Destroy,
    (ActorFunc)EnJcMato_Update,
    (ActorFunc)EnJcMato_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jc_Mato/func_80B9DEE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jc_Mato/func_80B9DFC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jc_Mato/func_80B9DFDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jc_Mato/EnJcMato_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jc_Mato/EnJcMato_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jc_Mato/EnJcMato_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jc_Mato/EnJcMato_Draw.s")
