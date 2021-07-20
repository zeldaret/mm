#include "z_en_dodongo.h"

#define FLAGS 0x00000405

#define THIS ((EnDodongo*)thisx)

void EnDodongo_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDodongo_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDodongo_Update(Actor* thisx, GlobalContext* globalCtx);
void EnDodongo_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0

const ActorInit En_Dodongo_InitVars = {
    ACTOR_EN_DODONGO,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_DODONGO,
    sizeof(EnDodongo),
    (ActorFunc)EnDodongo_Init,
    (ActorFunc)EnDodongo_Destroy,
    (ActorFunc)EnDodongo_Update,
    (ActorFunc)EnDodongo_Draw,
};


// static ColliderJntSphElementInit sJntSphElementsInit[10] = {
static ColliderJntSphElementInit D_808790D0[10] = {
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x800CB019, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
        { 7, { { 500, 0, 0 }, 27 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x800CB019, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
        { 21, { { -200, 0, 0 }, 20 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x800CB019, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
        { 28, { { -200, 0, 0 }, 20 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x800CB019, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
        { 22, { { 400, -400, 0 }, 20 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x800CB019, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
        { 29, { { 400, -400, 0 }, 20 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
        { 16, { { 1000, 0, 0 }, 28 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x08 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
        { 14, { { -300, 300, 0 }, 17 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x08 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
        { 14, { { 800, 100, 0 }, 15 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x08 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
        { 13, { { 600, 0, 0 }, 12 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x08 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_NONE, },
        { 13, { { 1500, 0, 0 }, 12 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_80879238 = {
    { COLTYPE_HIT0, AT_NONE | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    10, D_808790D0, // sJntSphElementsInit,
};


// static ColliderJntSphElementInit sJntSphElementsInit[3] = {
static ColliderJntSphElementInit D_808790D0[3] = {
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x800CB019, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
        { 7, { { 500, 0, 0 }, 27 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x800CB019, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
        { 21, { { -200, 0, 0 }, 20 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x800CB019, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
        { 28, { { -200, 0, 0 }, 20 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_80879248 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_NONE, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    3, D_808790D0, // sJntSphElementsInit,
};


// static ColliderJntSphElementInit sJntSphElementsInit[3] = {
static ColliderJntSphElementInit D_80879258[3] = {
    {
        { ELEMTYPE_UNK0, { 0x20000000, 0x01, 0x10 }, { 0x00000000, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_NONE, },
        { 2, { { 0, -10, 10 }, 25 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0x20000000, 0x01, 0x10 }, { 0x00000000, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_NONE, },
        { 2, { { 0, -5, 50 }, 37 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0x20000000, 0x01, 0x10 }, { 0x00000000, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_NONE, },
        { 2, { { 0, 0, 90 }, 50 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_808792C4 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_ENEMY, AC_NONE, OC1_NONE, OC2_NONE, COLSHAPE_JNTSPH, },
    3, D_80879258, // sJntSphElementsInit,
};


// static DamageTable sDamageTable = {
static DamageTable D_808792D4 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(0, 0x1),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0xF),
    /* Goron punch    */ DMG_ENTRY(2, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(3, 0x0),
    /* Fire arrow     */ DMG_ENTRY(1, 0x2),
    /* Ice arrow      */ DMG_ENTRY(1, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(0, 0x1),
    /* Deku bubble    */ DMG_ENTRY(1, 0xE),
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


// sColChkInfoInit
static CollisionCheckInfoInit D_808792F4 = { 3, 100, 100, 80 };


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_808792FC[] = {
    ICHAIN_S8(hintId, 13, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -1000, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 1400, ICHAIN_STOP),
};

#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/EnDodongo_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/EnDodongo_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_80876930.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_80876B08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_80876BD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_80876CAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_80876D28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_80876DC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_8087721C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_80877278.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_808773C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_80877424.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_80877494.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_80877500.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_808777A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_8087784C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_80877D50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_80877D90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_80877DE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_80877E60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_80878354.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_80878424.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_80878594.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_808785B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_8087864C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_808786C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_80878724.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_808787B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_80878910.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/EnDodongo_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_80878E44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/func_80878EB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dodongo_0x80876670/EnDodongo_Draw.asm")
