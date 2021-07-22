#include "z_en_dekubaba.h"

#define FLAGS 0x00000405

#define THIS ((EnDekubaba*)thisx)

void EnDekubaba_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDekubaba_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDekubaba_Update(Actor* thisx, GlobalContext* globalCtx);
void EnDekubaba_Draw(Actor* thisx, GlobalContext* globalCtx);

#if(0)
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


extern ColliderJntSphElementInit D_808B4D60[7];
extern ColliderJntSphInit D_808B4E5C;
extern CollisionCheckInfoInit D_808B4E6C;
extern DamageTable D_808B4E74;
extern InitChainEntry D_808B4E94[];
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/EnDekubaba_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/EnDekubaba_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B1530.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B15B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B16BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B1798.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B1814.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B18A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B1B14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B1BC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B1CF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B2158.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B2240.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B2608.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B2660.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B2890.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B28B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B2980.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B29C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B2C40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B2CB8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B3044.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B3078.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B3170.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B3280.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B3390.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B3404.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B3768.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B37E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B39AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B3B48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B3BE4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B3C50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B3D74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B3DA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B3E40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B3EE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B3F50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/EnDekubaba_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B4548.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B465C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B48FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B49C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/func_808B4ABC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekubaba_0x808B1330/EnDekubaba_Draw.asm")
