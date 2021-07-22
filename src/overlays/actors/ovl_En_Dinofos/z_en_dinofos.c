#include "z_en_dinofos.h"

#define FLAGS 0x00000435

#define THIS ((EnDinofos*)thisx)

void EnDinofos_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDinofos_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDinofos_Update(Actor* thisx, GlobalContext* globalCtx);
void EnDinofos_Draw(Actor* thisx, GlobalContext* globalCtx);

#if(0)
const ActorInit En_Dinofos_InitVars = {
    ACTOR_EN_DINOFOS,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_DINOFOS,
    sizeof(EnDinofos),
    (ActorFunc)EnDinofos_Init,
    (ActorFunc)EnDinofos_Destroy,
    (ActorFunc)EnDinofos_Update,
    (ActorFunc)EnDinofos_Draw,
};


// static ColliderJntSphElementInit sJntSphElementsInit[9] = {
static ColliderJntSphElementInit D_8089E170[9] = {
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
        { 1, { { 200, 300, 0 }, 19 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
        { 8, { { 200, 200, 0 }, 17 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
        { 16, { { 600, 200, 0 }, 15 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
        { 15, { { 700, 100, 0 }, 10 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
        { 2, { { 1300, 100, 0 }, 12 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
        { 5, { { 1300, 100, 0 }, 12 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0x20000000, 0x09, 0x08 }, { 0x00000000, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_NONE, },
        { 21, { { 0, -10, 35 }, 20 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0x20000000, 0x09, 0x08 }, { 0x00000000, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_NONE, },
        { 21, { { 0, -10, 70 }, 28 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0x20000000, 0x09, 0x08 }, { 0x00000000, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_NONE, },
        { 21, { { 0, -5, 110 }, 30 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_8089E2B4 = {
    { COLTYPE_HIT0, AT_NONE | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    9, D_8089E170, // sJntSphElementsInit,
};


// static ColliderQuadInit sQuadInit = {
static ColliderQuadInit D_8089E2C4 = {
    { COLTYPE_NONE, AT_NONE | AT_TYPE_ENEMY, AC_NONE, OC1_NONE, OC2_NONE, COLSHAPE_QUAD, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x04 }, { 0x00000000, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL | TOUCH_UNK7, BUMP_NONE, OCELEM_NONE, },
    { { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } },
};


// static DamageTable sDamageTable = {
static DamageTable D_8089E314 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0xF),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(1, 0x0),
    /* Fire arrow     */ DMG_ENTRY(1, 0x2),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(0, 0x1),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(2, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x1),
    /* Zora barrier   */ DMG_ENTRY(0, 0x5),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0x0),
    /* Zora punch     */ DMG_ENTRY(1, 0x0),
    /* Spin attack    */ DMG_ENTRY(1, 0x0),
    /* Sword beam     */ DMG_ENTRY(1, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0x0),
};


// sColChkInfoInit
static CollisionCheckInfoInit D_8089E334 = { 4, 40, 100, 80 };


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_8089E354[] = {
    ICHAIN_F32(targetArrowOffset, 2000, ICHAIN_CONTINUE),
    ICHAIN_S8(hintId, 16, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -2000, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 15, ICHAIN_STOP),
};


extern ColliderJntSphElementInit D_8089E170[9];
extern ColliderJntSphInit D_8089E2B4;
extern ColliderQuadInit D_8089E2C4;
extern DamageTable D_8089E314;
extern CollisionCheckInfoInit D_8089E334;
extern InitChainEntry D_8089E354[];
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/EnDinofos_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/EnDinofos_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089A900.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089A968.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089A9B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089ABF4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089AC70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089ACEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089AD70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089AE00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089B100.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089B288.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089B320.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089B3D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089B4A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089B580.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089B6E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089B72C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089B7B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089B834.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089B8B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089B98C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089BAC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089BB60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089BBB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089BD28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089C024.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089C0DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089C164.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089C1F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089C244.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089C2A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089C398.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089C44C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089C4F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089C56C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089C690.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089C724.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089C784.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089C7B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089C87C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089C938.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089CA14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089CA74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089CB10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089CBEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089CF00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089CF70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089CFAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089D018.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089D11C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089D1E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089D2E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089D318.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089D42C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089D60C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/EnDinofos_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089DC4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/func_8089DC84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dinofos_0x8089A6E0/EnDinofos_Draw.asm")
