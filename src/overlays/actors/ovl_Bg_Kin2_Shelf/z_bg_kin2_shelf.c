/*
 * File: z_bg_kin2_shelf.c
 * Overlay: ovl_Bg_Kin2_Shelf
 * Description: Ocean Spider House - Drawers
 */

#include "z_bg_kin2_shelf.h"

#define FLAGS 0x00000000

#define THIS ((BgKin2Shelf*)thisx)

void BgKin2Shelf_Init(Actor* thisx, GlobalContext* globalCtx);
void BgKin2Shelf_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgKin2Shelf_Update(Actor* thisx, GlobalContext* globalCtx);
void BgKin2Shelf_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Bg_Kin2_Shelf_InitVars = {
    ACTOR_BG_KIN2_SHELF,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_KIN2_OBJ,
    sizeof(BgKin2Shelf),
    (ActorFunc)BgKin2Shelf_Init,
    (ActorFunc)BgKin2Shelf_Destroy,
    (ActorFunc)BgKin2Shelf_Update,
    (ActorFunc)BgKin2Shelf_Draw,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80B7077C[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_STOP),
};

#endif

extern InitChainEntry D_80B7077C[];

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Shelf/func_80B6FB30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Shelf/func_80B6FCA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Shelf/func_80B6FE08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Shelf/func_80B6FE48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Shelf/func_80B6FEBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Shelf/func_80B6FF28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Shelf/BgKin2Shelf_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Shelf/BgKin2Shelf_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Shelf/func_80B700A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Shelf/func_80B700C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Shelf/func_80B70214.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Shelf/func_80B70230.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Shelf/func_80B70498.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Shelf/func_80B704B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Shelf/BgKin2Shelf_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Shelf/BgKin2Shelf_Draw.s")
