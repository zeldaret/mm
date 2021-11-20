/*
 * File: z_bg_f40_switch.c
 * Overlay: ovl_Bg_F40_Switch
 * Description: Stone Tower Switch
 */

#include "z_bg_f40_switch.h"

#define FLAGS 0x00000010

#define THIS ((BgF40Switch*)thisx)

void BgF40Switch_Init(Actor* thisx, GlobalContext* globalCtx);
void BgF40Switch_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgF40Switch_Update(Actor* thisx, GlobalContext* globalCtx);
void BgF40Switch_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80BC4B20(BgF40Switch* this, GlobalContext* globalCtx);
void func_80BC4B94(BgF40Switch* this, GlobalContext* globalCtx);
void func_80BC4BB8(BgF40Switch* this, GlobalContext* globalCtx);
void func_80BC4C68(BgF40Switch* this, GlobalContext* globalCtx);
void func_80BC4D30(BgF40Switch* this, GlobalContext* globalCtx);

#if 0
const ActorInit Bg_F40_Switch_InitVars = {
    ACTOR_BG_F40_SWITCH,
    ACTORCAT_SWITCH,
    FLAGS,
    OBJECT_F40_SWITCH,
    sizeof(BgF40Switch),
    (ActorFunc)BgF40Switch_Init,
    (ActorFunc)BgF40Switch_Destroy,
    (ActorFunc)BgF40Switch_Update,
    (ActorFunc)BgF40Switch_Draw,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80BC4E04[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 200, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 123, ICHAIN_STOP),
};

#endif

extern InitChainEntry D_80BC4E04[];

extern UNK_TYPE D_06000118;
extern UNK_TYPE D_06000438;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_F40_Switch/func_80BC47B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_F40_Switch/BgF40Switch_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_F40_Switch/BgF40Switch_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_F40_Switch/func_80BC4B20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_F40_Switch/func_80BC4B94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_F40_Switch/func_80BC4BB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_F40_Switch/func_80BC4C68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_F40_Switch/func_80BC4D30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_F40_Switch/BgF40Switch_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_F40_Switch/BgF40Switch_Draw.s")
