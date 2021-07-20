#include "z_en_thiefbird.h"

#define FLAGS 0x80001205

#define THIS ((EnThiefbird*)thisx)

void EnThiefbird_Init(Actor* thisx, GlobalContext* globalCtx);
void EnThiefbird_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnThiefbird_Update(Actor* thisx, GlobalContext* globalCtx);
void EnThiefbird_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0

const ActorInit En_Thiefbird_InitVars = {
    ACTOR_EN_THIEFBIRD,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_THIEFBIRD,
    sizeof(EnThiefbird),
    (ActorFunc)EnThiefbird_Init,
    (ActorFunc)EnThiefbird_Destroy,
    (ActorFunc)EnThiefbird_Update,
    (ActorFunc)EnThiefbird_Draw,
};


// static ColliderJntSphElementInit sJntSphElementsInit[3] = {
static ColliderJntSphElementInit D_80C135C0[3] = {
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 24 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 9, { { 900, -600, 0 }, 20 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_HARD, BUMP_ON, OCELEM_ON, },
        { 12, { { 1200, 0, 0 }, 9 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_80C1362C = {
    { COLTYPE_HIT3, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    3, D_80C135C0, // sJntSphElementsInit,
};


// sColChkInfoInit
static CollisionCheckInfoInit D_80C1363C = { 24, 15, 30, 30 };


// static DamageTable sDamageTable = {
static DamageTable D_80C13644 = {
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
    /* Zora barrier   */ DMG_ENTRY(0, 0x5),
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
static InitChainEntry D_80C13670[] = {
    ICHAIN_F32(uncullZoneForward, 3000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 1000, ICHAIN_CONTINUE),
    ICHAIN_S8(hintId, 35, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 500, ICHAIN_STOP),
};

#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Thiefbird_0x80C10770/EnThiefbird_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Thiefbird_0x80C10770/EnThiefbird_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Thiefbird_0x80C10770/func_80C10984.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Thiefbird_0x80C10770/func_80C10B0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Thiefbird_0x80C10770/func_80C10DE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Thiefbird_0x80C10770/func_80C10E98.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Thiefbird_0x80C10770/func_80C11338.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Thiefbird_0x80C10770/func_80C11454.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Thiefbird_0x80C10770/func_80C114C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Thiefbird_0x80C10770/func_80C11538.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Thiefbird_0x80C10770/func_80C11590.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Thiefbird_0x80C10770/func_80C118E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Thiefbird_0x80C10770/func_80C1193C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Thiefbird_0x80C10770/func_80C11C60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Thiefbird_0x80C10770/func_80C11D14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Thiefbird_0x80C10770/func_80C11DC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Thiefbird_0x80C10770/func_80C11DF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Thiefbird_0x80C10770/func_80C11F6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Thiefbird_0x80C10770/func_80C1215C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Thiefbird_0x80C10770/func_80C12308.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Thiefbird_0x80C10770/func_80C12378.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Thiefbird_0x80C10770/func_80C1242C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Thiefbird_0x80C10770/func_80C124B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Thiefbird_0x80C10770/func_80C126A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Thiefbird_0x80C10770/func_80C126D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Thiefbird_0x80C10770/func_80C12744.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Thiefbird_0x80C10770/func_80C127F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Thiefbird_0x80C10770/func_80C12B1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Thiefbird_0x80C10770/func_80C12D00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Thiefbird_0x80C10770/EnThiefbird_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Thiefbird_0x80C10770/func_80C130EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Thiefbird_0x80C10770/func_80C1315C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Thiefbird_0x80C10770/func_80C13354.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Thiefbird_0x80C10770/EnThiefbird_Draw.asm")
