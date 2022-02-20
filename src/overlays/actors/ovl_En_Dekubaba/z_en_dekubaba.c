/*
 * File: z_en_dekubaba.c
 * Overlay: ovl_En_Dekubaba
 * Description: Deku Baba
 */

#include "z_en_dekubaba.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_400)

#define THIS ((EnDekubaba*)thisx)

void EnDekubaba_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDekubaba_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDekubaba_Update(Actor* thisx, GlobalContext* globalCtx);
void EnDekubaba_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_808B1B14(EnDekubaba* this, GlobalContext* globalCtx);
void func_808B1CF0(EnDekubaba* this, GlobalContext* globalCtx);
void func_808B2240(EnDekubaba* this, GlobalContext* globalCtx);
void func_808B2660(EnDekubaba* this, GlobalContext* globalCtx);
void func_808B28B4(EnDekubaba* this, GlobalContext* globalCtx);
void func_808B29C4(EnDekubaba* this, GlobalContext* globalCtx);
void func_808B2CB8(EnDekubaba* this, GlobalContext* globalCtx);
void func_808B3078(EnDekubaba* this, GlobalContext* globalCtx);
void func_808B3280(EnDekubaba* this, GlobalContext* globalCtx);
void func_808B3404(EnDekubaba* this, GlobalContext* globalCtx);
void func_808B37E8(EnDekubaba* this, GlobalContext* globalCtx);
void func_808B3B48(EnDekubaba* this, GlobalContext* globalCtx);
void func_808B3C50(EnDekubaba* this, GlobalContext* globalCtx);
void func_808B3DA8(EnDekubaba* this, GlobalContext* globalCtx);
void func_808B3EE8(EnDekubaba* this, GlobalContext* globalCtx);

#if 0
const ActorInit En_Dekubaba_InitVars = {
    ACTOR_EN_DEKUBABA,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_DEKUBABA,
    sizeof(EnDekubaba),
    (ActorFunc)EnDekubaba_Init,
    (ActorFunc)EnDekubaba_Destroy,
    (ActorFunc)EnDekubaba_Update,
    (ActorFunc)EnDekubaba_Draw,
};

// static ColliderJntSphElementInit sJntSphElementsInit[7] = {
static ColliderJntSphElementInit D_808B4D60[7] = {
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x08 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_HARD, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
        { 1, { { 0, 100, 1000 }, 15 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
        { 51, { { 0, 0, 1500 }, 8 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_NONE, },
        { 52, { { 0, 0, 500 }, 8 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_NONE, },
        { 53, { { 0, 0, 1500 }, 8 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_NONE, },
        { 54, { { 0, 0, 500 }, 8 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_NONE, },
        { 55, { { 0, 0, 1500 }, 8 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_NONE, },
        { 56, { { 0, 0, 500 }, 8 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_808B4E5C = {
    { COLTYPE_HIT6, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    7, D_808B4D60, // sJntSphElementsInit,
};

// sColChkInfoInit
static CollisionCheckInfoInit D_808B4E6C = { 2, 25, 25, MASS_IMMOVABLE };

// static DamageTable sDamageTable = {
static DamageTable D_808B4E74 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(3, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0xF),
    /* Normal arrow   */ DMG_ENTRY(3, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0xD),
    /* Goron punch    */ DMG_ENTRY(2, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(4, 0x0),
    /* Fire arrow     */ DMG_ENTRY(1, 0x2),
    /* Ice arrow      */ DMG_ENTRY(3, 0x3),
    /* Light arrow    */ DMG_ENTRY(3, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(1, 0xF),
    /* Deku bubble    */ DMG_ENTRY(3, 0x0),
    /* Deku launch    */ DMG_ENTRY(2, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x1),
    /* Zora barrier   */ DMG_ENTRY(0, 0x5),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0x0),
    /* Zora punch     */ DMG_ENTRY(1, 0x0),
    /* Spin attack    */ DMG_ENTRY(1, 0xF),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0x0),
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_808B4E94[] = {
    ICHAIN_F32(targetArrowOffset, 1500, ICHAIN_STOP),
};

#endif

extern ColliderJntSphElementInit D_808B4D60[7];
extern ColliderJntSphInit D_808B4E5C;
extern CollisionCheckInfoInit D_808B4E6C;
extern DamageTable D_808B4E74;
extern InitChainEntry D_808B4E94[];

extern UNK_TYPE D_06000208;
extern UNK_TYPE D_060002B8;
extern UNK_TYPE D_060010F0;
extern UNK_TYPE D_06001330;
extern UNK_TYPE D_06001828;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/EnDekubaba_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/EnDekubaba_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B1530.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B15B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B16BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B1798.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B1814.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B18A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B1B14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B1BC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B1CF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B2158.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B2240.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B2608.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B2660.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B2890.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B28B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B2980.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B29C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B2C40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B2CB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B3044.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B3078.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B3170.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B3280.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B3390.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B3404.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B3768.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B37E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B39AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B3B48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B3BE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B3C50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B3D74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B3DA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B3E40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B3EE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B3F50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/EnDekubaba_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B4548.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B465C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B48FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B49C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/func_808B4ABC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekubaba/EnDekubaba_Draw.s")
