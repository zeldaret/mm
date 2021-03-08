#include "z_bg_ctower_gear.h"

#define FLAGS 0x00000010

#define THIS ((BgCtowerGear*)thisx)

void BgCtowerGear_Init(Actor* thisx, GlobalContext* globalCtx);
void BgCtowerGear_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgCtowerGear_Update(Actor* thisx, GlobalContext* globalCtx);
void BgCtowerGear_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Bg_Ctower_Gear_InitVars = {
    ACTOR_BG_CTOWER_GEAR,
    ACTORTYPE_PROP,
    FLAGS,
    OBJECT_CTOWER_ROT,
    sizeof(BgCtowerGear),
    (ActorFunc)BgCtowerGear_Init,
    (ActorFunc)BgCtowerGear_Destroy,
    (ActorFunc)BgCtowerGear_Update,
    (ActorFunc)BgCtowerGear_Draw
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ctower_Gear_0x80AD2B70/func_80AD2B70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ctower_Gear_0x80AD2B70/BgCtowerGear_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ctower_Gear_0x80AD2B70/BgCtowerGear_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ctower_Gear_0x80AD2B70/BgCtowerGear_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ctower_Gear_0x80AD2B70/func_80AD3054.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ctower_Gear_0x80AD2B70/BgCtowerGear_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ctower_Gear_0x80AD2B70/func_80AD3164.asm")
