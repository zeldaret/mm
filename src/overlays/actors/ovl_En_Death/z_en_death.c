#include "z_en_death.h"

#define FLAGS 0x00001035

#define THIS ((EnDeath*)thisx)

void EnDeath_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDeath_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDeath_Update(Actor* thisx, GlobalContext* globalCtx);
void EnDeath_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Death_InitVars = {
    ACTOR_EN_DEATH,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_DEATH,
    sizeof(EnDeath),
    (ActorFunc)EnDeath_Init,
    (ActorFunc)EnDeath_Destroy,
    (ActorFunc)EnDeath_Update,
    (ActorFunc)EnDeath_Draw,
};


// static ColliderSphereInit sSphereInit = {
static ColliderSphereInit D_808C98E0 = {
    { COLTYPE_HIT3, AT_NONE, AC_NONE | AC_TYPE_PLAYER, OC1_NONE, OC2_TYPE_1, COLSHAPE_SPHERE, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
    { 1, { { 0, 0, 0 }, 22 }, 100 },
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_808C990C = {
    { COLTYPE_NONE, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 35, 90, 20, { 0, 0, 0 } },
};


// static ColliderTrisElementInit sTrisElementsInit[2] = {
static ColliderTrisElementInit D_808C9938[2] = {
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x04, 0x20 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x04, 0x20 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } },
    },
};

// static ColliderTrisInit sTrisInit = {
static ColliderTrisInit D_808C99B0 = {
    { COLTYPE_METAL, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_NONE, OC2_TYPE_1, COLSHAPE_TRIS, },
    2, D_808C9938, // sTrisElementsInit,
};


// static ColliderQuadInit sQuadInit = {
static ColliderQuadInit D_808C99C0 = {
    { COLTYPE_NONE, AT_NONE | AT_TYPE_ENEMY, AC_NONE, OC1_NONE, OC2_TYPE_2, COLSHAPE_QUAD, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x04, 0x20 }, { 0x00000000, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL | TOUCH_UNK7, BUMP_NONE, OCELEM_NONE, },
    { { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } },
};


// static DamageTable sDamageTable = {
static DamageTable D_808C9A10 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0x0),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(0, 0x0),
    /* Fire arrow     */ DMG_ENTRY(1, 0x2),
    /* Ice arrow      */ DMG_ENTRY(1, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(0, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(2, 0x0),
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
    /* Powder Keg     */ DMG_ENTRY(1, 0xF),
};


// sColChkInfoInit
static CollisionCheckInfoInit2 D_808C9A30 = { 20, 28, 90, 20, 100 };


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_808C9A60[] = {
    ICHAIN_VEC3F(scale, 0, ICHAIN_CONTINUE),
    ICHAIN_S8(hintId, 26, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 6000, ICHAIN_CONTINUE),
    ICHAIN_U8(targetMode, 5, ICHAIN_STOP),
};


extern ColliderSphereInit D_808C98E0;
extern ColliderCylinderInit D_808C990C;
extern ColliderTrisElementInit D_808C9938[2];
extern ColliderTrisInit D_808C99B0;
extern ColliderQuadInit D_808C99C0;
extern DamageTable D_808C9A10;
extern CollisionCheckInfoInit2 D_808C9A30;
extern InitChainEntry D_808C9A60[];
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/EnDeath_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/EnDeath_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C5310.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C5394.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C5428.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C54F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C566C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C571C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C589C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C597C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C5AB8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C5C0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C5CB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C5D6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C5E90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C5F58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C6070.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C645C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C64DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C6620.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C66A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C67C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C682C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C68B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C692C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C6A08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C6AB0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C6C5C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C6CDC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C6D40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C6F6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C70D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C72AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C74A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C74F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C7800.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C7888.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C7A30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C7AAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C7AEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C7B88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C7C04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C7C88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C7CFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C7D34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C7DB8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C7DCC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C7E24.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C7EDC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/EnDeath_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C84A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C8690.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C882C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C8D18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C9160.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C9220.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/func_808C9340.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Death_0x808C4F80/EnDeath_Draw.asm")
