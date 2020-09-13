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
    ACTORTYPE_BOSS,
    FLAGS,
    OBJECT_BOSS02,
    sizeof(EnTanron5),
    (ActorFunc)EnTanron5_Init,
    (ActorFunc)EnTanron5_Destroy,
    (ActorFunc)EnTanron5_Update,
    (ActorFunc)EnTanron5_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Tanron5_0x80BE4930/func_80BE4930.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tanron5_0x80BE4930/func_80BE4A2C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tanron5_0x80BE4930/EnTanron5_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tanron5_0x80BE4930/EnTanron5_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tanron5_0x80BE4930/EnTanron5_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tanron5_0x80BE4930/func_80BE5818.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tanron5_0x80BE4930/EnTanron5_Draw.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tanron5_0x80BE4930/func_80BE5C10.asm")
