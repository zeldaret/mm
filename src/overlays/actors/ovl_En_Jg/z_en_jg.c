/*
 * File: z_en_jg.c
 * Overlay: ovl_En_Jg
 * Description: Goron Elder
 */

#include "z_en_jg.h"

#define FLAGS 0x00000019

#define THIS ((EnJg*)thisx)

void EnJg_Init(Actor* thisx, GlobalContext* globalCtx);
void EnJg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnJg_Update(Actor* thisx, GlobalContext* globalCtx);
void EnJg_Draw(Actor* thisx, GlobalContext* globalCtx);

extern AnimationHeader D_060077CC;
extern AnimationHeader D_06009440;
extern AnimationHeader D_0600A07C;
extern AnimationHeader D_0600BDD8;
extern AnimationHeader D_0600C7A8;
extern AnimationHeader D_0600D630;
extern AnimationHeader D_0600DB54;
extern AnimationHeader D_0600E8FC;
extern AnimationHeader D_0600FE48;
extern AnimationHeader D_06011F50;
extern AnimationHeader D_060129F4;
extern AnimationHeader D_06013DD8;
extern AnimationHeader D_0601436C;
extern AnimationHeader D_06018CE4;
extern AnimationHeader D_0601ADC0;

const ActorInit En_Jg_InitVars = {
    ACTOR_EN_JG,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_JG,
    sizeof(EnJg),
    (ActorFunc)EnJg_Init,
    (ActorFunc)EnJg_Destroy,
    (ActorFunc)EnJg_Update,
    (ActorFunc)EnJg_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B75820 = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 60, 80, 0, { 0, 0, 0 } },
};

// sColChkInfoInit
static CollisionCheckInfoInit2 D_80B7584C = { 0, 50, 80, 0, MASS_IMMOVABLE };

// static DamageTable sDamageTable = {
static DamageTable D_80B75858 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(0, 0x0),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(0, 0x0),
    /* Zora boomerang */ DMG_ENTRY(0, 0x0),
    /* Normal arrow   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0x0),
    /* Goron punch    */ DMG_ENTRY(0, 0x0),
    /* Sword          */ DMG_ENTRY(0, 0x0),
    /* Goron pound    */ DMG_ENTRY(0, 0x0),
    /* Fire arrow     */ DMG_ENTRY(0, 0x0),
    /* Ice arrow      */ DMG_ENTRY(0, 0x0),
    /* Light arrow    */ DMG_ENTRY(0, 0x0),
    /* Goron spikes   */ DMG_ENTRY(0, 0x0),
    /* Deku spin      */ DMG_ENTRY(0, 0x0),
    /* Deku bubble    */ DMG_ENTRY(0, 0x0),
    /* Deku launch    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(0, 0x0),
    /* Zora punch     */ DMG_ENTRY(0, 0x0),
    /* Spin attack    */ DMG_ENTRY(0, 0x0),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(0, 0x0),
};

static ActorAnimationEntryS D_80B75878[] = {
    { &D_0601ADC0, 1.0f, 0, -1, 0, -10 },  { &D_06009440, 1.0f, 0, -1, 0, -10 }, { &D_0600BDD8, 1.0f, 0, -1, 0, -10 },
    { &D_0600C7A8, 1.0f, 0, -1, 0, -10 },  { &D_0600DB54, 1.0f, 0, -1, 2, -10 }, { &D_0600E8FC, 1.0f, 0, -1, 0, -10 },
    { &D_0601436C, 1.0f, 0, -1, 0, -10 },  { &D_0600DB54, 2.0f, 0, -1, 2, 0 },   { &D_0600DB54, -2.0f, 0, -1, 2, 0 },
    { &D_06009440, -1.0f, 0, -1, 0, -10 }, { &D_06011F50, 1.0f, 0, -1, 2, 0 },   { &D_060129F4, 1.0f, 0, -1, 0, 0 },
    { &D_06013DD8, 1.0f, 1, 44, 2, 0 },    { &D_060077CC, 1.0f, 0, -1, 0, 0 },   { &D_0600D630, 1.0f, 0, -1, 2, 0 },
    { &D_0600FE48, 1.0f, 0, -1, 2, 0 },    { &D_06018CE4, 1.0f, 0, -1, 0, 0 },   { &D_0601ADC0, 1.0f, 0, -1, 0, 0 },
    { &D_0600A07C, 1.0f, 0, -1, 0, 0 },
};

static Vec3f D_80B759A8 = { 0.0f, 0.0f, 0.0f };

static Vec3f D_80B759B4 = { 0.0f, 0.0f, 0.0f };

static Vec3f D_80B759C0 = { 1000.0f, -500.0f, 0.0f };

static Vec3f D_80B759CC = { 0.0f, 0.0f, 0.75f };

static Vec3f D_80B759D8 = { 0.0f, 0.0f, -0.070000000298f };

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/func_80B73A90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/func_80B73AE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/func_80B73B98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/func_80B73C58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/func_80B73DF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/func_80B73E3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/func_80B73F1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/func_80B7406C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/func_80B7408C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/func_80B74134.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/func_80B741F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/func_80B742F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/func_80B74440.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/func_80B74550.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/func_80B747C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/func_80B74840.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/func_80B749D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/func_80B74AD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/func_80B74B54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/func_80B74BC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/func_80B74E5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/func_80B750A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/func_80B7517C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/func_80B751F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/EnJg_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/EnJg_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/EnJg_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/func_80B75658.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/func_80B75708.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Jg/EnJg_Draw.s")
