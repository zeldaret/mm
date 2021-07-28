#include "z_en_sw.h"

#define FLAGS 0x00000005

#define THIS ((EnSw*)thisx)

void EnSw_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSw_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSw_Update(Actor* thisx, GlobalContext* globalCtx);
void EnSw_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Sw_InitVars = {
    ACTOR_EN_SW,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_ST,
    sizeof(EnSw),
    (ActorFunc)EnSw_Init,
    (ActorFunc)EnSw_Destroy,
    (ActorFunc)EnSw_Update,
    (ActorFunc)EnSw_Draw,
};

// static ColliderSphereInit sSphereInit = {
static ColliderSphereInit D_808DB9E0 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_SPHERE, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 0, { { 0, 0, 0 }, 16 }, 100 },
};

// sColChkInfoInit
static CollisionCheckInfoInit2 D_808DBA0C = { 1, 0, 0, 0, MASS_IMMOVABLE };

// static DamageTable sDamageTable = {
static DamageTable D_808DBA18 = {
    /* Deku Nut       */ DMG_ENTRY(1, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0x0),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(2, 0x0),
    /* Fire arrow     */ DMG_ENTRY(2, 0x2),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(1, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(2, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(1, 0x0),
    /* Zora barrier   */ DMG_ENTRY(1, 0x5),
    /* Normal shield  */ DMG_ENTRY(1, 0x0),
    /* Light ray      */ DMG_ENTRY(1, 0x0),
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
static CollisionCheckInfoInit2 D_808DBA38 = { 1, 0, 0, 0, MASS_IMMOVABLE };

// static DamageTable sDamageTable = {
static DamageTable D_808DBA44 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0x0),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(2, 0x0),
    /* Fire arrow     */ DMG_ENTRY(2, 0x2),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(1, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(2, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x1),
    /* Zora barrier   */ DMG_ENTRY(1, 0x5),
    /* Normal shield  */ DMG_ENTRY(1, 0x0),
    /* Light ray      */ DMG_ENTRY(1, 0x0),
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

#endif

extern ColliderSphereInit D_808DB9E0;
extern CollisionCheckInfoInit2 D_808DBA0C;
extern DamageTable D_808DBA18;
extern CollisionCheckInfoInit2 D_808DBA38;
extern DamageTable D_808DBA44;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808D8940.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808D8B58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808D8D60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808D8ED0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808D8FC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808D90C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808D90F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808D91C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808D93BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808D9440.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808D94D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808D9894.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808D9968.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808D99C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808D9A70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808D9C18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808D9DA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808D9E44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808D9F08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808D9F78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808DA024.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808DA08C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808DA350.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808DA3F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808DA578.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808DA6FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808DA89C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808DAA60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808DACF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808DAEB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808DB100.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808DB25C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808DB2E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/EnSw_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/EnSw_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/EnSw_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/func_808DB7F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Sw/EnSw_Draw.s")
