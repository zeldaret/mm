/*
 * File: z_en_ik.c
 * Overlay: ovl_En_Ik
 * Description: Iron Knuckle
 */

#include "z_en_ik.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_400)

#define THIS ((EnIk*)thisx)

void EnIk_Init(Actor* thisx, GlobalContext* globalCtx);
void EnIk_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnIk_Update(Actor* thisx, GlobalContext* globalCtx);
void EnIk_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Ik_InitVars = {
    ACTOR_EN_IK,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_IK,
    sizeof(EnIk),
    (ActorFunc)EnIk_Init,
    (ActorFunc)EnIk_Destroy,
    (ActorFunc)EnIk_Update,
    (ActorFunc)EnIk_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_8092C01C = {
    { COLTYPE_METAL, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK2, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
    { 25, 80, 0, { 0, 0, 0 } },
};

// static ColliderTrisElementInit sTrisElementsInit[2] = {
static ColliderTrisElementInit D_8092C048[2] = {
    {
        { ELEMTYPE_UNK2, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { -10.0f, 14.0f, 2.0f }, { -10.0f, -6.0f, 2.0f }, { 9.0f, 14.0f, 2.0f } } },
    },
    {
        { ELEMTYPE_UNK2, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { -10.0f, -6.0f, 2.0f }, { 9.0f, -6.0f, 2.0f }, { 9.0f, 14.0f, 2.0f } } },
    },
};

// static ColliderTrisInit sTrisInit = {
static ColliderTrisInit D_8092C0C0 = {
    { COLTYPE_METAL, AT_NONE, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_NONE, OC2_TYPE_2, COLSHAPE_TRIS, },
    2, D_8092C048, // sTrisElementsInit,
};

// static ColliderQuadInit sQuadInit = {
static ColliderQuadInit D_8092C0D0 = {
    { COLTYPE_NONE, AT_NONE | AT_TYPE_ENEMY, AC_NONE, OC1_NONE, OC2_TYPE_2, COLSHAPE_QUAD, },
    { ELEMTYPE_UNK0, { 0x20000000, 0x04, 0x40 }, { 0x00000000, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL | TOUCH_UNK7, BUMP_NONE, OCELEM_NONE, },
    { { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } },
};

// static DamageTable sDamageTable = {
static DamageTable D_8092C120 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0xF),
    /* Deku Stick     */ DMG_ENTRY(0, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(0, 0xF),
    /* Normal arrow   */ DMG_ENTRY(0, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0xF),
    /* Goron punch    */ DMG_ENTRY(2, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(3, 0x0),
    /* Fire arrow     */ DMG_ENTRY(0, 0xF),
    /* Ice arrow      */ DMG_ENTRY(0, 0xF),
    /* Light arrow    */ DMG_ENTRY(1, 0x4),
    /* Goron spikes   */ DMG_ENTRY(0, 0xF),
    /* Deku spin      */ DMG_ENTRY(0, 0xF),
    /* Deku bubble    */ DMG_ENTRY(0, 0xF),
    /* Deku launch    */ DMG_ENTRY(0, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0xF),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0x0),
    /* Zora punch     */ DMG_ENTRY(0, 0xF),
    /* Spin attack    */ DMG_ENTRY(1, 0x0),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0x0),
};

// static DamageTable sDamageTable = {
static DamageTable D_8092C140 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0xF),
    /* Goron punch    */ DMG_ENTRY(2, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(3, 0x0),
    /* Fire arrow     */ DMG_ENTRY(2, 0x2),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(0, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
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

// sColChkInfoInit
static CollisionCheckInfoInit D_8092C160 = { 18, 25, 80, MASS_HEAVY };

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_8092C168[] = {
    ICHAIN_F32(targetArrowOffset, 2916, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 12, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -1000, ICHAIN_STOP),
};

#endif

extern ColliderCylinderInit D_8092C01C;
extern ColliderTrisElementInit D_8092C048[2];
extern ColliderTrisInit D_8092C0C0;
extern ColliderQuadInit D_8092C0D0;
extern DamageTable D_8092C120;
extern DamageTable D_8092C140;
extern CollisionCheckInfoInit D_8092C160;
extern InitChainEntry D_8092C168[];

extern UNK_TYPE D_06000CE8;
extern UNK_TYPE D_060015F8;
extern UNK_TYPE D_06001ABC;
extern UNK_TYPE D_06002484;
extern UNK_TYPE D_0600391C;
extern UNK_TYPE D_06004A04;
extern UNK_TYPE D_06005254;
extern UNK_TYPE D_060057F4;
extern UNK_TYPE D_06006294;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/EnIk_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/EnIk_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_80929AF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_80929B6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_80929BEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_80929C80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_80929D04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_80929E2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_80929E88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_80929F20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_80929FC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_8092A020.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_8092A124.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_8092A188.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_8092A28C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_8092A33C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_8092A570.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_8092A5BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_8092A680.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_8092A754.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_8092A8D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_8092A994.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_8092AA6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_8092AB14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_8092AB50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_8092ABD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_8092AC4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_8092ACFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_8092ADB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_8092AE14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_8092AFB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_8092AFD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_8092B03C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_8092B098.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_8092B1B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_8092B46C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/EnIk_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_8092B900.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_8092B93C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/func_8092BC6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ik/EnIk_Draw.s")
