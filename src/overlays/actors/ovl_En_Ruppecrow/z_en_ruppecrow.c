/*
 * File: z_en_ruppecrow.c
 * Overlay: ovl_En_Ruppecrow
 * Description: Guay Circling Clock Town
 */

#include "z_en_ruppecrow.h"

#define FLAGS 0x00004030

#define THIS ((EnRuppecrow*)thisx)

void EnRuppecrow_Init(Actor* thisx, GlobalContext* globalCtx);
void EnRuppecrow_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnRuppecrow_Update(Actor* thisx, GlobalContext* globalCtx);
void EnRuppecrow_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Ruppecrow_InitVars = {
    ACTOR_EN_RUPPECROW,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_CROW,
    sizeof(EnRuppecrow),
    (ActorFunc)EnRuppecrow_Init,
    (ActorFunc)EnRuppecrow_Destroy,
    (ActorFunc)EnRuppecrow_Update,
    (ActorFunc)EnRuppecrow_Draw,
};

// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_80BE39B0[1] = {
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 20 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_80BE39D4 = {
    { COLTYPE_HIT3, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    1, D_80BE39B0, // sJntSphElementsInit,
};

// sColChkInfoInit
static CollisionCheckInfoInit D_80BE39E4 = { 1, 15, 30, 30 };

// static DamageTable sDamageTable = {
static DamageTable D_80BE39EC = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0x0),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(1, 0x0),
    /* Fire arrow     */ DMG_ENTRY(2, 0x2),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(1, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(2, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x1),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0x0),
    /* Zora punch     */ DMG_ENTRY(1, 0x0),
    /* Spin attack    */ DMG_ENTRY(1, 0x0),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0x0),
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80BE3A0C[] = {
    ICHAIN_F32_DIV1000(gravity, -500, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 2000, ICHAIN_STOP),
};

#endif

extern ColliderJntSphElementInit D_80BE39B0[1];
extern ColliderJntSphInit D_80BE39D4;
extern CollisionCheckInfoInit D_80BE39E4;
extern DamageTable D_80BE39EC;
extern InitChainEntry D_80BE3A0C[];

extern UNK_TYPE D_060000F0;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ruppecrow/func_80BE2260.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ruppecrow/func_80BE2330.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ruppecrow/func_80BE24CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ruppecrow/func_80BE2668.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ruppecrow/func_80BE2728.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ruppecrow/func_80BE2794.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ruppecrow/func_80BE2808.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ruppecrow/func_80BE2874.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ruppecrow/func_80BE2B80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ruppecrow/func_80BE2D4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ruppecrow/func_80BE2E18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ruppecrow/func_80BE2F6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ruppecrow/func_80BE30F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ruppecrow/func_80BE3178.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ruppecrow/func_80BE32DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ruppecrow/func_80BE3354.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ruppecrow/func_80BE348C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ruppecrow/func_80BE35A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ruppecrow/EnRuppecrow_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ruppecrow/EnRuppecrow_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ruppecrow/EnRuppecrow_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ruppecrow/EnRuppecrow_Draw.s")
