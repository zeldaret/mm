#include "z_en_baba.h"

#define FLAGS 0x00000019

#define THIS ((EnBaba*)thisx)

void EnBaba_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBaba_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBaba_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBaba_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0

const ActorInit En_Baba_InitVars = {
    ACTOR_EN_BABA,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_BBA,
    sizeof(EnBaba),
    (ActorFunc)EnBaba_Init,
    (ActorFunc)EnBaba_Destroy,
    (ActorFunc)EnBaba_Update,
    (ActorFunc)EnBaba_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BAA430 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 18, 64, 0, { 0, 0, 0 } },
};


// sColChkInfoInit
static CollisionCheckInfoInit2 D_80BAA45C = { 0, 0, 0, 0, MASS_IMMOVABLE };


// static DamageTable sDamageTable = {
static DamageTable D_80BAA468 = {
    /* Deku Nut       */ DMG_ENTRY(1, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(1, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0x0),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(1, 0x0),
    /* Fire arrow     */ DMG_ENTRY(1, 0x0),
    /* Ice arrow      */ DMG_ENTRY(1, 0x0),
    /* Light arrow    */ DMG_ENTRY(1, 0x0),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(1, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(1, 0x0),
    /* Zora barrier   */ DMG_ENTRY(1, 0x0),
    /* Normal shield  */ DMG_ENTRY(1, 0x0),
    /* Light ray      */ DMG_ENTRY(1, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0x0),
    /* Zora punch     */ DMG_ENTRY(1, 0x0),
    /* Spin attack    */ DMG_ENTRY(1, 0x0),
    /* Sword beam     */ DMG_ENTRY(1, 0x0),
    /* Normal Roll    */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(1, 0x0),
    /* Unblockable    */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(1, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0x0),
};

#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baba_0x80BA8820/func_80BA8820.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baba_0x80BA8820/func_80BA886C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baba_0x80BA8820/func_80BA8C4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baba_0x80BA8820/func_80BA8C90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baba_0x80BA8820/func_80BA8D2C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baba_0x80BA8820/func_80BA8DF4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baba_0x80BA8820/func_80BA8F88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baba_0x80BA8820/func_80BA9110.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baba_0x80BA8820/func_80BA9160.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baba_0x80BA8820/func_80BA93AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baba_0x80BA8820/func_80BA9480.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baba_0x80BA8820/func_80BA9758.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baba_0x80BA8820/func_80BA9848.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baba_0x80BA8820/func_80BA98EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baba_0x80BA8820/func_80BA9AB8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baba_0x80BA8820/func_80BA9B24.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baba_0x80BA8820/func_80BA9B80.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baba_0x80BA8820/func_80BA9CD4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baba_0x80BA8820/func_80BA9E00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baba_0x80BA8820/func_80BA9E10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baba_0x80BA8820/func_80BA9E48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baba_0x80BA8820/EnBaba_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baba_0x80BA8820/EnBaba_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baba_0x80BA8820/EnBaba_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baba_0x80BA8820/func_80BA9FB0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baba_0x80BA8820/func_80BAA198.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baba_0x80BA8820/func_80BAA20C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Baba_0x80BA8820/EnBaba_Draw.asm")
