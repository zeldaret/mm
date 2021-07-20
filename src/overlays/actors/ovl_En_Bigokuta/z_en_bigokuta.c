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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigokuta_0x80AC26F0/EnBigokuta_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigokuta_0x80AC26F0/EnBigokuta_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigokuta_0x80AC26F0/func_80AC28B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigokuta_0x80AC26F0/func_80AC299C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigokuta_0x80AC26F0/func_80AC2A1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigokuta_0x80AC26F0/func_80AC2A7C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigokuta_0x80AC26F0/func_80AC2B4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigokuta_0x80AC26F0/func_80AC2B98.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigokuta_0x80AC26F0/func_80AC2C30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigokuta_0x80AC26F0/func_80AC2C84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigokuta_0x80AC26F0/func_80AC2CE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigokuta_0x80AC26F0/func_80AC2DAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigokuta_0x80AC26F0/func_80AC2EBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigokuta_0x80AC26F0/func_80AC2F20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigokuta_0x80AC26F0/func_80AC2F64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigokuta_0x80AC26F0/func_80AC3054.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigokuta_0x80AC26F0/func_80AC30EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigokuta_0x80AC26F0/func_80AC31EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigokuta_0x80AC26F0/func_80AC33A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigokuta_0x80AC26F0/func_80AC33C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigokuta_0x80AC26F0/func_80AC3460.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigokuta_0x80AC26F0/func_80AC34A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigokuta_0x80AC26F0/func_80AC35E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigokuta_0x80AC26F0/func_80AC3650.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigokuta_0x80AC26F0/func_80AC3930.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigokuta_0x80AC26F0/func_80AC39A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigokuta_0x80AC26F0/EnBigokuta_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigokuta_0x80AC26F0/func_80AC3D48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigokuta_0x80AC26F0/func_80AC4204.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bigokuta_0x80AC26F0/EnBigokuta_Draw.asm")
