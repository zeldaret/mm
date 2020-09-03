#include "z_en_takaraya.h"

#define FLAGS 0x00000039

#define THIS ((EnTakaraya*)thisx)

void EnTakaraya_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTakaraya_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTakaraya_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTakaraya_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Takaraya_InitVars = {
    ACTOR_EN_TAKARAYA,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_BG,
    sizeof(EnTakaraya),
    (ActorFunc)EnTakaraya_Init,
    (ActorFunc)EnTakaraya_Destroy,
    (ActorFunc)EnTakaraya_Update,
    (ActorFunc)EnTakaraya_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Takaraya_0x80ADEB90/EnTakaraya_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Takaraya_0x80ADEB90/EnTakaraya_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Takaraya_0x80ADEB90/func_80ADED8C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Takaraya_0x80ADEB90/func_80ADEDF8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Takaraya_0x80ADEB90/func_80ADEE4C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Takaraya_0x80ADEB90/func_80ADEF74.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Takaraya_0x80ADEB90/func_80ADF03C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Takaraya_0x80ADEB90/func_80ADF050.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Takaraya_0x80ADEB90/func_80ADF2D4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Takaraya_0x80ADEB90/func_80ADF338.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Takaraya_0x80ADEB90/func_80ADF4E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Takaraya_0x80ADEB90/func_80ADF520.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Takaraya_0x80ADEB90/func_80ADF608.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Takaraya_0x80ADEB90/func_80ADF654.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Takaraya_0x80ADEB90/func_80ADF6DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Takaraya_0x80ADEB90/func_80ADF730.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Takaraya_0x80ADEB90/func_80ADF7B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Takaraya_0x80ADEB90/func_80ADF7CC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Takaraya_0x80ADEB90/EnTakaraya_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Takaraya_0x80ADEB90/func_80ADF94C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Takaraya_0x80ADEB90/func_80ADF984.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Takaraya_0x80ADEB90/EnTakaraya_Draw.asm")
