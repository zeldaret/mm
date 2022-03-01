/*
 * File: z_en_kaizoku.c
 * Overlay: ovl_En_Kaizoku
 * Description: Fighter pirate
 */

#include "z_en_kaizoku.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_10 | ACTOR_FLAG_100000)

#define THIS ((EnKaizoku*)thisx)

void EnKaizoku_Init(Actor* thisx, GlobalContext* globalCtx);
void EnKaizoku_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnKaizoku_Update(Actor* thisx, GlobalContext* globalCtx);

#if 0
// static DamageTable sDamageTable = {
static DamageTable D_80B8AB3C = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(1, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(0, 0x1),
    /* Normal arrow   */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0x1),
    /* Goron punch    */ DMG_ENTRY(1, 0xE),
    /* Sword          */ DMG_ENTRY(1, 0xE),
    /* Goron pound    */ DMG_ENTRY(0, 0xD),
    /* Fire arrow     */ DMG_ENTRY(2, 0x2),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0xE),
    /* Deku spin      */ DMG_ENTRY(0, 0x1),
    /* Deku bubble    */ DMG_ENTRY(1, 0xE),
    /* Deku launch    */ DMG_ENTRY(2, 0xE),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x1),
    /* Zora barrier   */ DMG_ENTRY(0, 0x5),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0xE),
    /* Zora punch     */ DMG_ENTRY(1, 0xE),
    /* Spin attack    */ DMG_ENTRY(1, 0xD),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0xE),
};

const ActorInit En_Kaizoku_InitVars = {
    ACTOR_EN_KAIZOKU,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_KZ,
    sizeof(EnKaizoku),
    (ActorFunc)EnKaizoku_Init,
    (ActorFunc)EnKaizoku_Destroy,
    (ActorFunc)EnKaizoku_Update,
    (ActorFunc)NULL,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B8AB7C = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
    { 20, 50, 0, { 0, 0, 0 } },
};

// static ColliderQuadInit sQuadInit = {
static ColliderQuadInit D_80B8ABA8 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_PLAYER | AT_TYPE_ENEMY, AC_NONE, OC1_NONE, OC2_NONE, COLSHAPE_QUAD, },
    { ELEMTYPE_UNK4, { 0xF7CFFFFF, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL | TOUCH_UNK7, BUMP_NONE, OCELEM_NONE, },
    { { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } },
};

#endif

extern DamageTable D_80B8AB3C;
extern ColliderCylinderInit D_80B8AB7C;
extern ColliderQuadInit D_80B8ABA8;

extern UNK_TYPE D_060058B8;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/EnKaizoku_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/EnKaizoku_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B85858.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B85900.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B85A00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B85E18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B85EA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B85F48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B85FA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B86804.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B868B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B86B58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B86B74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B872A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B872F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B874D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B8760C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B87900.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B8798C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B87C7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B87CF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B87D3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B87E28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B87E9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B87F70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B87FDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B88214.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B88278.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B8833C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B88378.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B88770.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B887AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B88910.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B88964.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B88CD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B88D6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B891B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B89280.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B893CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B894C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B8960C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B8971C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B89A08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/EnKaizoku_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B8A318.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B8A468.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B8A6B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kaizoku/func_80B8A718.s")
