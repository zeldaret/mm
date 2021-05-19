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
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_BG,
    sizeof(EnTakaraya),
    (ActorFunc)EnTakaraya_Init,
    (ActorFunc)EnTakaraya_Destroy,
    (ActorFunc)EnTakaraya_Update,
    (ActorFunc)EnTakaraya_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Takaraya_0x80ADEB90/EnTakaraya_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Takaraya_0x80ADEB90/EnTakaraya_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Takaraya_0x80ADEB90/func_80ADED8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Takaraya_0x80ADEB90/func_80ADEDF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Takaraya_0x80ADEB90/func_80ADEE4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Takaraya_0x80ADEB90/func_80ADEF74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Takaraya_0x80ADEB90/func_80ADF03C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Takaraya_0x80ADEB90/func_80ADF050.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Takaraya_0x80ADEB90/func_80ADF2D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Takaraya_0x80ADEB90/func_80ADF338.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Takaraya_0x80ADEB90/func_80ADF4E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Takaraya_0x80ADEB90/func_80ADF520.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Takaraya_0x80ADEB90/func_80ADF608.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Takaraya_0x80ADEB90/func_80ADF654.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Takaraya_0x80ADEB90/func_80ADF6DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Takaraya_0x80ADEB90/func_80ADF730.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Takaraya_0x80ADEB90/func_80ADF7B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Takaraya_0x80ADEB90/func_80ADF7CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Takaraya_0x80ADEB90/EnTakaraya_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Takaraya_0x80ADEB90/func_80ADF94C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Takaraya_0x80ADEB90/func_80ADF984.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Takaraya_0x80ADEB90/EnTakaraya_Draw.asm")
