#include "z_bg_icefloe.h"

#define FLAGS 0x00000010

#define THIS ((BgIcefloe*)thisx)

void BgIcefloe_Init(Actor* thisx, GlobalContext* globalCtx);
void BgIcefloe_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgIcefloe_Update(Actor* thisx, GlobalContext* globalCtx);
void BgIcefloe_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Bg_Icefloe_InitVars = {
    ACTOR_BG_ICEFLOE,
    ACTORTYPE_BG,
    FLAGS,
    OBJECT_ICEFLOE,
    sizeof(BgIcefloe),
    (ActorFunc)BgIcefloe_Init,
    (ActorFunc)BgIcefloe_Destroy,
    (ActorFunc)BgIcefloe_Update,
    (ActorFunc)BgIcefloe_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Icefloe_0x80AC48F0/BgIcefloe_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Icefloe_0x80AC48F0/BgIcefloe_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Icefloe_0x80AC48F0/func_80AC4A80.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Icefloe_0x80AC48F0/func_80AC4AE8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Icefloe_0x80AC48F0/func_80AC4C18.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Icefloe_0x80AC48F0/func_80AC4C34.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Icefloe_0x80AC48F0/func_80AC4CF0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Icefloe_0x80AC48F0/func_80AC4D2C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Icefloe_0x80AC48F0/BgIcefloe_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Icefloe_0x80AC48F0/BgIcefloe_Draw.asm")
