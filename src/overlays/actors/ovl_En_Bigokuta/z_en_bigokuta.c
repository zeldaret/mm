/*
 * File: z_en_bigokuta.c
 * Overlay: ovl_En_Bigokuta
 * Description: Big Octo
 */

#include "z_en_bigokuta.h"

#define FLAGS 0x00000005

#define THIS ((EnBigokuta*)thisx)

void EnBigokuta_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBigokuta_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBigokuta_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBigokuta_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Bigokuta_InitVars = {
    ACTOR_EN_BIGOKUTA,
    ACTORCAT_BOSS,
    FLAGS,
    OBJECT_BIGOKUTA,
    sizeof(EnBigokuta),
    (ActorFunc)EnBigokuta_Init,
    (ActorFunc)EnBigokuta_Destroy,
    (ActorFunc)EnBigokuta_Update,
    (ActorFunc)EnBigokuta_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80AC4530 = {
    { COLTYPE_HARD, AT_NONE, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFC74F, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 75, 125, 0, { 0, 0, 0 } },
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80AC455C = {
    { COLTYPE_HIT0, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x000038B0, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
    { 70, 125, 0, { 0, 0, 0 } },
};

// sColChkInfoInit
static CollisionCheckInfoInit D_80AC4588 = { 4, 130, 120, MASS_HEAVY };

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80AC4590[] = {
    ICHAIN_F32(uncullZoneForward, 2500, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 2000, ICHAIN_CONTINUE),
    ICHAIN_U8(targetMode, 2, ICHAIN_CONTINUE),
    ICHAIN_S8(hintId, 89, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 33, ICHAIN_STOP),
};

#endif

extern ColliderCylinderInit D_80AC4530;
extern ColliderCylinderInit D_80AC455C;
extern CollisionCheckInfoInit D_80AC4588;
extern InitChainEntry D_80AC4590[];

extern UNK_TYPE D_06000444;
extern UNK_TYPE D_06000A74;
extern UNK_TYPE D_060014B8;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/EnBigokuta_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/EnBigokuta_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC28B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC299C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC2A1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC2A7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC2B4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC2B98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC2C30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC2C84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC2CE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC2DAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC2EBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC2F20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC2F64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC3054.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC30EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC31EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC33A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC33C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC3460.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC34A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC35E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC3650.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC3930.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC39A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/EnBigokuta_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC3D48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC4204.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/EnBigokuta_Draw.s")
