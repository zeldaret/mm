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
    (ActorFunc)BgOpenShutter_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Open_Shutter/func_80ACAB10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Open_Shutter/func_80ACABA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Open_Shutter/BgOpenShutter_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Open_Shutter/BgOpenShutter_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Open_Shutter/func_80ACAD88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Open_Shutter/func_80ACAE5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Open_Shutter/func_80ACAEF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Open_Shutter/BgOpenShutter_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Open_Shutter/BgOpenShutter_Draw.s")
