/*
 * File: z_en_s_goro.c
 * Overlay: ovl_En_S_Goro
 * Description: Goron in Goron Shrine / Bomb Shop Goron
 */

#include "z_en_s_goro.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10)

#define THIS ((EnSGoro*)thisx)

void EnSGoro_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSGoro_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSGoro_Update(Actor* thisx, GlobalContext* globalCtx);
void EnSGoro_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_S_Goro_InitVars = {
    ACTOR_EN_S_GORO,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_OF1D_MAP,
    sizeof(EnSGoro),
    (ActorFunc)EnSGoro_Init,
    (ActorFunc)EnSGoro_Destroy,
    (ActorFunc)EnSGoro_Update,
    (ActorFunc)EnSGoro_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BBF820 = {
    { COLTYPE_HIT1, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 0, 0, 0, { 0, 0, 0 } },
};

// sColChkInfoInit
static CollisionCheckInfoInit2 D_80BBF84C = { 0, 0, 0, 0, MASS_IMMOVABLE };

// static DamageTable sDamageTable = {
static DamageTable D_80BBF858 = {
    /* Deku Nut       */ DMG_ENTRY(1, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(1, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0x0),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(1, 0x0),
    /* Fire arrow     */ DMG_ENTRY(1, 0x0),
    /* Ice arrow      */ DMG_ENTRY(1, 0x0),
    /* Light arrow    */ DMG_ENTRY(1, 0x0),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(1, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(1, 0x0),
    /* Zora barrier   */ DMG_ENTRY(1, 0x0),
    /* Normal shield  */ DMG_ENTRY(1, 0x0),
    /* Light ray      */ DMG_ENTRY(1, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0x0),
    /* Zora punch     */ DMG_ENTRY(1, 0x0),
    /* Spin attack    */ DMG_ENTRY(1, 0x0),
    /* Sword beam     */ DMG_ENTRY(1, 0x0),
    /* Normal Roll    */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(1, 0x0),
    /* Unblockable    */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(1, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0x0),
};

#endif

extern ColliderCylinderInit D_80BBF820;
extern CollisionCheckInfoInit2 D_80BBF84C;
extern DamageTable D_80BBF858;

extern UNK_TYPE D_060091A8;
extern UNK_TYPE D_06012DE0;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBCA80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBD348.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBD8F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBD93C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBD98C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBDACC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBDC34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBDCFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBDDF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBDE78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBDF28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBDFA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBE05C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBE0E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBE144.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBE374.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBE498.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBE73C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBE844.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBE904.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBE9F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBEAD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBEBF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBECBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBEEB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBEF34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBEFA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBF01C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/EnSGoro_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/EnSGoro_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/EnSGoro_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBF298.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBF3D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBF3EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBF5F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/func_80BBF6BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_S_Goro/EnSGoro_Draw.s")
