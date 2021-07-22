#include "z_bg_open_shutter.h"

#define FLAGS 0x00000010

#define THIS ((BgOpenShutter*)thisx)

void BgOpenShutter_Init(Actor* thisx, GlobalContext* globalCtx);
void BgOpenShutter_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgOpenShutter_Update(Actor* thisx, GlobalContext* globalCtx);
void BgOpenShutter_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
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


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80ACB140[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 350, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 350, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};


extern InitChainEntry D_80ACB140[];
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Open_Shutter_0x80ACAB10/func_80ACAB10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Open_Shutter_0x80ACAB10/func_80ACABA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Open_Shutter_0x80ACAB10/BgOpenShutter_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Open_Shutter_0x80ACAB10/BgOpenShutter_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Open_Shutter_0x80ACAB10/func_80ACAD88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Open_Shutter_0x80ACAB10/func_80ACAE5C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Open_Shutter_0x80ACAB10/func_80ACAEF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Open_Shutter_0x80ACAB10/BgOpenShutter_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Open_Shutter_0x80ACAB10/BgOpenShutter_Draw.asm")
