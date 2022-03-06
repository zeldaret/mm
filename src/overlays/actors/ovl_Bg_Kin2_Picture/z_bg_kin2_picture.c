/*
 * File: z_bg_kin2_picture.c
 * Overlay: ovl_Bg_Kin2_Picture
 * Description: Ocean Spider House - Skullkid Painting
 */

#include "z_bg_kin2_picture.h"

#define FLAGS 0x00000000

#define THIS ((BgKin2Picture*)thisx)

void BgKin2Picture_Init(Actor* thisx, GlobalContext* globalCtx);
void BgKin2Picture_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgKin2Picture_Update(Actor* thisx, GlobalContext* globalCtx);
void BgKin2Picture_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80B6F4D4(BgKin2Picture* this, GlobalContext* globalCtx);
void func_80B6F5B8(BgKin2Picture* this, GlobalContext* globalCtx);
void func_80B6F640(BgKin2Picture* this, GlobalContext* globalCtx);
void func_80B6F72C(BgKin2Picture* this, GlobalContext* globalCtx);
void func_80B6F90C(BgKin2Picture* this, GlobalContext* globalCtx);

#if 0
const ActorInit Bg_Kin2_Picture_InitVars = {
    ACTOR_BG_KIN2_PICTURE,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_KIN2_OBJ,
    sizeof(BgKin2Picture),
    (ActorFunc)BgKin2Picture_Init,
    (ActorFunc)BgKin2Picture_Destroy,
    (ActorFunc)BgKin2Picture_Update,
    (ActorFunc)BgKin2Picture_Draw,
};

// static ColliderTrisElementInit sTrisElementsInit[2] = {
static ColliderTrisElementInit D_80B6F990[2] = {
    {
        { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x000138B0, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { -20.0f, 53.29999923706055f, 9.0f }, { -20.0f, 3.0f, 9.0f }, { 20.0f, 3.0f, 9.0f } } },
    },
    {
        { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x000138B0, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { -20.0f, 53.29999923706055f, 9.0f }, { 20.0f, 3.0f, 9.0f }, { 20.0f, 53.29999923706055f, 9.0f } } },
    },
};

// static ColliderTrisInit sTrisInit = {
static ColliderTrisInit D_80B6FA08 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_NONE, COLSHAPE_TRIS, },
    2, D_80B6F990, // sTrisElementsInit,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80B6FA24[] = {
    ICHAIN_F32_DIV1000(gravity, -2000, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(terminalVelocity, -20000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 100, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

#endif

extern ColliderTrisElementInit D_80B6F990[2];
extern ColliderTrisInit D_80B6FA08;
extern InitChainEntry D_80B6FA24[];

extern UNK_TYPE D_06000658;
extern UNK_TYPE D_06000798;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Picture/func_80B6EFA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Picture/func_80B6EFEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Picture/func_80B6F098.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Picture/BgKin2Picture_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Picture/BgKin2Picture_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Picture/func_80B6F4C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Picture/func_80B6F4D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Picture/func_80B6F5A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Picture/func_80B6F5B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Picture/func_80B6F61C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Picture/func_80B6F640.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Picture/func_80B6F708.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Picture/func_80B6F72C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Picture/func_80B6F8F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Picture/func_80B6F90C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Picture/BgKin2Picture_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Kin2_Picture/BgKin2Picture_Draw.s")
