#include "z_en_tanron3.h"

#define FLAGS 0x00000035

#define THIS ((EnTanron3*)thisx)

void EnTanron3_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTanron3_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTanron3_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTanron3_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Tanron3_InitVars = {
    ACTOR_EN_TANRON3,
    ACTORTYPE_BOSS,
    FLAGS,
    OBJECT_BOSS03,
    sizeof(EnTanron3),
    (ActorFunc)EnTanron3_Init,
    (ActorFunc)EnTanron3_Destroy,
    (ActorFunc)EnTanron3_Update,
    (ActorFunc)EnTanron3_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Tanron3_0x80BB85A0/func_80BB85A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tanron3_0x80BB85A0/EnTanron3_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tanron3_0x80BB85A0/EnTanron3_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tanron3_0x80BB85A0/func_80BB87D4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tanron3_0x80BB85A0/func_80BB897C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tanron3_0x80BB85A0/func_80BB8A48.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tanron3_0x80BB85A0/func_80BB91D4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tanron3_0x80BB85A0/func_80BB9288.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tanron3_0x80BB85A0/func_80BB9308.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tanron3_0x80BB85A0/EnTanron3_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tanron3_0x80BB85A0/func_80BB95FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tanron3_0x80BB85A0/EnTanron3_Draw.asm")
