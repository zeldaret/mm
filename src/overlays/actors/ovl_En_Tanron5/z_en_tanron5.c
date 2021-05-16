#include "z_en_tanron5.h"

#define FLAGS 0x00000030

#define THIS ((EnTanron5*)thisx)

void EnTanron5_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTanron5_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTanron5_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTanron5_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Tanron5_InitVars = {
    ACTOR_EN_TANRON5,
    ACTORCAT_BOSS,
    FLAGS,
    OBJECT_BOSS02,
    sizeof(EnTanron5),
    (ActorFunc)EnTanron5_Init,
    (ActorFunc)EnTanron5_Destroy,
    (ActorFunc)EnTanron5_Update,
    (ActorFunc)EnTanron5_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron5/func_80BE4930.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron5/func_80BE4A2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron5/EnTanron5_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron5/EnTanron5_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron5/EnTanron5_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron5/func_80BE5818.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron5/EnTanron5_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron5/func_80BE5C10.s")
