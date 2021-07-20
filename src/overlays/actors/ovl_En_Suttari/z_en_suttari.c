#include "z_en_suttari.h"

#define FLAGS 0x00000019

#define THIS ((EnSuttari*)thisx)

void EnSuttari_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSuttari_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSuttari_Update(Actor* thisx, GlobalContext* globalCtx);
void EnSuttari_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0

const ActorInit En_Suttari_InitVars = {
    ACTOR_EN_SUTTARI,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_BOJ,
    sizeof(EnSuttari),
    (ActorFunc)EnSuttari_Init,
    (ActorFunc)EnSuttari_Destroy,
    (ActorFunc)EnSuttari_Update,
    (ActorFunc)EnSuttari_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BAE7A8 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 18, 64, 0, { 0, 0, 0 } },
};


// sColChkInfoInit
static CollisionCheckInfoInit2 D_80BAE7D4 = { 0, 18, 64, 0, MASS_IMMOVABLE };


// static DamageTable sDamageTable = {
static DamageTable D_80BAE7E0 = {
    /* Deku Nut       */ DMG_ENTRY(1, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xE),
    /* Zora boomerang */ DMG_ENTRY(1, 0xE),
    /* Normal arrow   */ DMG_ENTRY(1, 0xE),
    /* UNK_DMG_0x06   */ DMG_ENTRY(1, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0xE),
    /* Goron punch    */ DMG_ENTRY(1, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(1, 0x0),
    /* Fire arrow     */ DMG_ENTRY(1, 0xE),
    /* Ice arrow      */ DMG_ENTRY(1, 0xE),
    /* Light arrow    */ DMG_ENTRY(1, 0xE),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(1, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(1, 0x0),
    /* Zora barrier   */ DMG_ENTRY(1, 0x0),
    /* Normal shield  */ DMG_ENTRY(1, 0x0),
    /* Light ray      */ DMG_ENTRY(1, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0x0),
    /* Zora punch     */ DMG_ENTRY(1, 0xF),
    /* Spin attack    */ DMG_ENTRY(1, 0xF),
    /* Sword beam     */ DMG_ENTRY(1, 0xE),
    /* Normal Roll    */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(1, 0x0),
    /* Unblockable    */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(1, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0xE),
};

#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAA6D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAA848.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAA88C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAA8D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAA904.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAA9B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAAA94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAAB78.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAAF1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAAFDC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAB1A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAB374.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAB434.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAB490.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAB4F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAB698.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAB758.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAB8F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BABA90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BABB90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BABC48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BABDD8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BABF64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BABFD4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAC220.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAC2FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAC6E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BACA14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BACBB0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BACD2C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BACE4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BACEE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAD004.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAD130.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAD230.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAD2B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAD380.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAD5F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAD7F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BADA08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BADA9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BADD0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BADDB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BADE14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BADE8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BADF3C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/EnSuttari_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/EnSuttari_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/EnSuttari_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAE250.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAE3C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/func_80BAE524.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Suttari_0x80BAA6D0/EnSuttari_Draw.asm")
