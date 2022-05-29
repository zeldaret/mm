/*
 * File: z_bg_icefloe.c
 * Overlay: ovl_Bg_Icefloe
 * Description: Ice Platform Created by Ice Arrow
 */

#include "z_bg_icefloe.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((BgIcefloe*)thisx)

void BgIcefloe_Init(Actor* thisx, GlobalContext* globalCtx);
void BgIcefloe_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgIcefloe_Update(Actor* thisx, GlobalContext* globalCtx);
void BgIcefloe_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Bg_Icefloe_InitVars = {
    ACTOR_BG_ICEFLOE,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_ICEFLOE,
    sizeof(BgIcefloe),
    (ActorFunc)BgIcefloe_Init,
    (ActorFunc)BgIcefloe_Destroy,
    (ActorFunc)BgIcefloe_Update,
    (ActorFunc)BgIcefloe_Draw,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80AC4F3C[] = {
    ICHAIN_VEC3F_DIV1000(scale, 0, ICHAIN_STOP),
};

#endif

extern InitChainEntry D_80AC4F3C[];

extern UNK_TYPE D_060001E0;
extern UNK_TYPE D_06000C90;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Icefloe/BgIcefloe_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Icefloe/BgIcefloe_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Icefloe/func_80AC4A80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Icefloe/func_80AC4AE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Icefloe/func_80AC4C18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Icefloe/func_80AC4C34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Icefloe/func_80AC4CF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Icefloe/func_80AC4D2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Icefloe/BgIcefloe_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Icefloe/BgIcefloe_Draw.s")
