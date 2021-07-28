#include "z_en_vm.h"

#define FLAGS 0x00000405

#define THIS ((EnVm*)thisx)

void EnVm_Init(Actor* thisx, GlobalContext* globalCtx);
void EnVm_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnVm_Update(Actor* thisx, GlobalContext* globalCtx);
void EnVm_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Vm_InitVars = {
    ACTOR_EN_VM,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_VM,
    sizeof(EnVm),
    (ActorFunc)EnVm_Init,
    (ActorFunc)EnVm_Destroy,
    (ActorFunc)EnVm_Update,
    (ActorFunc)EnVm_Draw,
};


// static ColliderJntSphElementInit sJntSphElementsInit[2] = {
static ColliderJntSphElementInit D_808CD4C0[2] = {
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
        { 2, { { 0, 0, 0 }, 20 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
        { 10, { { 0, 2300, 0 }, 33 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_808CD508 = {
    { COLTYPE_METAL, AT_NONE, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    2, D_808CD4C0, // sJntSphElementsInit,
};


// static ColliderTrisElementInit sTrisElementsInit[1] = {
static ColliderTrisElementInit D_808CD518[1] = {
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x10 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } },
    },
};

// static ColliderTrisInit sTrisInit = {
static ColliderTrisInit D_808CD554 = {
    { COLTYPE_METAL, AT_ON | AT_TYPE_ENEMY, AC_NONE, OC1_NONE, OC2_NONE, COLSHAPE_TRIS, },
    1, D_808CD518, // sTrisElementsInit,
};


// static DamageTable sDamageTable = {
static DamageTable D_808CD564 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0xF),
    /* Deku Stick     */ DMG_ENTRY(0, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0xF),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(0, 0xF),
    /* Normal arrow   */ DMG_ENTRY(0, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0xF),
    /* Hookshot       */ DMG_ENTRY(0, 0xF),
    /* Goron punch    */ DMG_ENTRY(0, 0xF),
    /* Sword          */ DMG_ENTRY(0, 0xF),
    /* Goron pound    */ DMG_ENTRY(0, 0xF),
    /* Fire arrow     */ DMG_ENTRY(0, 0xF),
    /* Ice arrow      */ DMG_ENTRY(0, 0xF),
    /* Light arrow    */ DMG_ENTRY(0, 0xF),
    /* Goron spikes   */ DMG_ENTRY(0, 0xF),
    /* Deku spin      */ DMG_ENTRY(0, 0xF),
    /* Deku bubble    */ DMG_ENTRY(0, 0xF),
    /* Deku launch    */ DMG_ENTRY(0, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0xF),
    /* Zora barrier   */ DMG_ENTRY(0, 0xF),
    /* Normal shield  */ DMG_ENTRY(0, 0xF),
    /* Light ray      */ DMG_ENTRY(0, 0xF),
    /* Thrown object  */ DMG_ENTRY(0, 0xF),
    /* Zora punch     */ DMG_ENTRY(0, 0xF),
    /* Spin attack    */ DMG_ENTRY(0, 0xF),
    /* Sword beam     */ DMG_ENTRY(0, 0xF),
    /* Normal Roll    */ DMG_ENTRY(0, 0xF),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0xF),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0xF),
    /* Unblockable    */ DMG_ENTRY(0, 0xF),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0xF),
    /* Powder Keg     */ DMG_ENTRY(1, 0x0),
};


// sColChkInfoInit
static CollisionCheckInfoInit D_808CD584 = { 2, 25, 100, MASS_IMMOVABLE };


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_808CD5AC[] = {
    ICHAIN_VEC3F_DIV1000(scale, 14, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 1000, ICHAIN_CONTINUE),
    ICHAIN_S8(hintId, 57, ICHAIN_STOP),
};


extern ColliderJntSphElementInit D_808CD4C0[2];
extern ColliderJntSphInit D_808CD508;
extern ColliderTrisElementInit D_808CD518[1];
extern ColliderTrisInit D_808CD554;
extern DamageTable D_808CD564;
extern CollisionCheckInfoInit D_808CD584;
extern InitChainEntry D_808CD5AC[];
#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Vm/EnVm_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Vm/EnVm_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Vm/func_808CC420.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Vm/func_808CC490.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Vm/func_808CC5C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Vm/func_808CC610.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Vm/func_808CC788.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Vm/func_808CC820.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Vm/func_808CCA10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Vm/func_808CCAA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Vm/func_808CCB08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Vm/func_808CCB50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Vm/func_808CCBE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Vm/func_808CCCF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Vm/func_808CCDE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Vm/EnVm_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Vm/func_808CD020.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Vm/func_808CD08C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Vm/EnVm_Draw.s")
