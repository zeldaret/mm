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


extern ColliderCylinderInit D_80BAE7A8;
extern CollisionCheckInfoInit2 D_80BAE7D4;
extern DamageTable D_80BAE7E0;
#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Suttari/func_80BAA6D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Suttari/func_80BAA848.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Suttari/func_80BAA88C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Suttari/func_80BAA8D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Suttari/func_80BAA904.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Suttari/func_80BAA9B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Suttari/func_80BAAA94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Suttari/func_80BAAB78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Suttari/func_80BAAF1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Suttari/func_80BAAFDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Suttari/func_80BAB1A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Suttari/func_80BAB374.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Suttari/func_80BAB434.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Suttari/func_80BAB490.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Suttari/func_80BAB4F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Suttari/func_80BAB698.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Suttari/func_80BAB758.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Suttari/func_80BAB8F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Suttari/func_80BABA90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Suttari/func_80BABB90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Suttari/func_80BABC48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Suttari/func_80BABDD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Suttari/func_80BABF64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Suttari/func_80BABFD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Suttari/func_80BAC220.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Suttari/func_80BAC2FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Suttari/func_80BAC6E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Suttari/func_80BACA14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Suttari/func_80BACBB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Suttari/func_80BACD2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Suttari/func_80BACE4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Suttari/func_80BACEE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Suttari/func_80BAD004.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Suttari/func_80BAD130.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Suttari/func_80BAD230.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Suttari/func_80BAD2B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Suttari/func_80BAD380.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Suttari/func_80BAD5F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Suttari/func_80BAD7F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Suttari/func_80BADA08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Suttari/func_80BADA9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Suttari/func_80BADD0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Suttari/func_80BADDB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Suttari/func_80BADE14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Suttari/func_80BADE8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Suttari/func_80BADF3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Suttari/EnSuttari_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Suttari/EnSuttari_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Suttari/EnSuttari_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Suttari/func_80BAE250.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Suttari/func_80BAE3C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Suttari/func_80BAE524.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Suttari/EnSuttari_Draw.s")
