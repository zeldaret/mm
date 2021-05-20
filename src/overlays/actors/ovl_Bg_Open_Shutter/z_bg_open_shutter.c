#include "z_bg_open_shutter.h"

#define FLAGS 0x00000010

#define THIS ((BgOpenShutter*)thisx)

void BgOpenShutter_Init(Actor* thisx, GlobalContext* globalCtx);
void BgOpenShutter_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgOpenShutter_Update(Actor* thisx, GlobalContext* globalCtx);
void BgOpenShutter_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Bg_Open_Shutter_InitVars = {
    ACTOR_BG_OPEN_SHUTTER,
    ACTORCAT_DOOR,
    FLAGS,
    OBJECT_OPEN_OBJ,
    sizeof(BgOpenShutter),
    (ActorFunc)BgOpenShutter_Init,
    (ActorFunc)BgOpenShutter_Destroy,
    (ActorFunc)BgOpenShutter_Update,
    (ActorFunc)BgOpenShutter_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Open_Shutter_0x80ACAB10/func_80ACAB10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Open_Shutter_0x80ACAB10/func_80ACABA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Open_Shutter_0x80ACAB10/BgOpenShutter_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Open_Shutter_0x80ACAB10/BgOpenShutter_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Open_Shutter_0x80ACAB10/func_80ACAD88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Open_Shutter_0x80ACAB10/func_80ACAE5C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Open_Shutter_0x80ACAB10/func_80ACAEF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Open_Shutter_0x80ACAB10/BgOpenShutter_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Open_Shutter_0x80ACAB10/BgOpenShutter_Draw.asm")
