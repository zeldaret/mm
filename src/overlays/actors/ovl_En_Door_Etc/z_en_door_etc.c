/*
 * File: z_en_door_etc.c
 * Overlay: ovl_En_Door_Etc
 * Description: Wooden Door
 */

#include "z_en_door_etc.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((EnDoorEtc*)thisx)

void EnDoorEtc_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDoorEtc_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDoorEtc_Update(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Door_Etc_InitVars = {
    ACTOR_EN_DOOR_ETC,
    ACTORCAT_DOOR,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnDoorEtc),
    (ActorFunc)EnDoorEtc_Init,
    (ActorFunc)EnDoorEtc_Destroy,
    (ActorFunc)EnDoorEtc_Update,
    (ActorFunc)NULL,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80AC25A0 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 100, 40, 0, { 0, 0, 0 } },
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80AC2634[] = {
    ICHAIN_U8(targetMode, 0, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_U16(shape.rot.x, 0, ICHAIN_CONTINUE),
    ICHAIN_U16(shape.rot.z, 0, ICHAIN_STOP),
};

#endif

extern ColliderCylinderInit D_80AC25A0;
extern InitChainEntry D_80AC2634[];

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Door_Etc/EnDoorEtc_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Door_Etc/EnDoorEtc_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Door_Etc/func_80AC2044.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Door_Etc/func_80AC20A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Door_Etc/func_80AC2118.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Door_Etc/func_80AC2154.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Door_Etc/func_80AC21A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Door_Etc/func_80AC2354.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Door_Etc/EnDoorEtc_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Door_Etc/func_80AC24A8.s")
