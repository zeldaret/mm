/*
 * File: z_bg_ikana_block.c
 * Overlay: ovl_Bg_Ikana_Block
 * Description: Stone Tower Temple - Rotating Room Pushblock
 */

#include "z_bg_ikana_block.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((BgIkanaBlock*)thisx)

void BgIkanaBlock_Init(Actor* thisx, GlobalContext* globalCtx);
void BgIkanaBlock_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgIkanaBlock_Update(Actor* thisx, GlobalContext* globalCtx);

void func_80B7F034(BgIkanaBlock* this, GlobalContext* globalCtx);
void func_80B7F0D0(BgIkanaBlock* this, GlobalContext* globalCtx);
void func_80B7F290(BgIkanaBlock* this, GlobalContext* globalCtx);
void func_80B7F398(BgIkanaBlock* this, GlobalContext* globalCtx);

#if 0
const ActorInit Bg_Ikana_Block_InitVars = {
    ACTOR_BG_IKANA_BLOCK,
    ACTORCAT_BG,
    FLAGS,
    GAMEPLAY_DANGEON_KEEP,
    sizeof(BgIkanaBlock),
    (ActorFunc)BgIkanaBlock_Init,
    (ActorFunc)BgIkanaBlock_Destroy,
    (ActorFunc)BgIkanaBlock_Update,
    (ActorFunc)NULL,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80B7F640[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 250, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 250, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

#endif

extern InitChainEntry D_80B7F640[];

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Block/func_80B7EA60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Block/func_80B7EB30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Block/func_80B7EB64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Block/func_80B7EB7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Block/func_80B7EB94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Block/func_80B7ECFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Block/func_80B7ED54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Block/func_80B7EDC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Block/func_80B7EE70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Block/func_80B7EEB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Block/BgIkanaBlock_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Block/BgIkanaBlock_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Block/func_80B7F00C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Block/func_80B7F034.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Block/func_80B7F0A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Block/func_80B7F0D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Block/func_80B7F1A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Block/func_80B7F290.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Block/func_80B7F360.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Block/func_80B7F398.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Block/BgIkanaBlock_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Block/func_80B7F564.s")
