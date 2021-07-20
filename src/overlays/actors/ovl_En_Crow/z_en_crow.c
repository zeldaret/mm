#include "z_en_crow.h"

#define FLAGS 0x00005005

#define THIS ((EnCrow*)thisx)

void EnCrow_Init(Actor* thisx, GlobalContext* globalCtx);
void EnCrow_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnCrow_Update(Actor* thisx, GlobalContext* globalCtx);
void EnCrow_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0

const ActorInit En_Crow_InitVars = {
    ACTOR_EN_CROW,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_CROW,
    sizeof(EnCrow),
    (ActorFunc)EnCrow_Init,
    (ActorFunc)EnCrow_Destroy,
    (ActorFunc)EnCrow_Update,
    (ActorFunc)EnCrow_Draw,
};


// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_8099C070[1] = {
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x08 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_HARD, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 0, 0 }, 20 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_8099C094 = {
    { COLTYPE_HIT3, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    1, D_8099C070, // sJntSphElementsInit,
};


// sColChkInfoInit
static CollisionCheckInfoInit D_8099C0A4 = { 1, 15, 30, 30 };


// static DamageTable sDamageTable = {
static DamageTable D_8099C0AC = {
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
static InitChainEntry D_8099C0D0[] = {
    ICHAIN_F32(uncullZoneForward, 3000, ICHAIN_CONTINUE),
    ICHAIN_S8(hintId, 88, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -500, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 2000, ICHAIN_STOP),
};

#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Crow_0x8099AB30/EnCrow_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Crow_0x8099AB30/EnCrow_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Crow_0x8099AB30/func_8099AC58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Crow_0x8099AB30/func_8099AC8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Crow_0x8099AB30/func_8099B098.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Crow_0x8099AB30/func_8099B0CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Crow_0x8099AB30/func_8099B318.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Crow_0x8099AB30/func_8099B384.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Crow_0x8099AB30/func_8099B584.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Crow_0x8099AB30/func_8099B6AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Crow_0x8099AB30/func_8099B6C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Crow_0x8099AB30/func_8099B778.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Crow_0x8099AB30/func_8099B838.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Crow_0x8099AB30/func_8099B8EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Crow_0x8099AB30/func_8099B9E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Crow_0x8099AB30/func_8099BAB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Crow_0x8099AB30/EnCrow_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Crow_0x8099AB30/func_8099BE48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Crow_0x8099AB30/func_8099BF20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Crow_0x8099AB30/EnCrow_Draw.asm")
