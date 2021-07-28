#include "z_en_tanron2.h"

#define FLAGS 0x00000035

#define THIS ((EnTanron2*)thisx)

void EnTanron2_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTanron2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTanron2_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTanron2_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Tanron2_InitVars = {
    ACTOR_EN_TANRON2,
    ACTORCAT_BOSS,
    FLAGS,
    OBJECT_BOSS04,
    sizeof(EnTanron2),
    (ActorFunc)EnTanron2_Init,
    (ActorFunc)EnTanron2_Destroy,
    (ActorFunc)EnTanron2_Update,
    (ActorFunc)EnTanron2_Draw,
};

// static DamageTable sDamageTable = {
static DamageTable D_80BB8170 = {
    /* Deku Nut       */ DMG_ENTRY(1, 0xF),
    /* Deku Stick     */ DMG_ENTRY(1, 0xF),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(2, 0xF),
    /* Zora boomerang */ DMG_ENTRY(1, 0xF),
    /* Normal arrow   */ DMG_ENTRY(2, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0xF),
    /* Goron punch    */ DMG_ENTRY(2, 0xF),
    /* Sword          */ DMG_ENTRY(2, 0xF),
    /* Goron pound    */ DMG_ENTRY(2, 0xF),
    /* Fire arrow     */ DMG_ENTRY(2, 0x2),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(2, 0xF),
    /* Deku spin      */ DMG_ENTRY(1, 0xF),
    /* Deku bubble    */ DMG_ENTRY(1, 0xF),
    /* Deku launch    */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(1, 0xF),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0xF),
    /* Light ray      */ DMG_ENTRY(0, 0xF),
    /* Thrown object  */ DMG_ENTRY(2, 0xF),
    /* Zora punch     */ DMG_ENTRY(2, 0xF),
    /* Spin attack    */ DMG_ENTRY(2, 0xF),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(2, 0x2),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0xF),
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BB8190 = {
    { COLTYPE_HIT3, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xFFFFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
    { 30, 50, -25, { 0, 0, 0 } },
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BB81BC = {
    { COLTYPE_HIT3, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK3, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7FFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
    { 22, 42, -21, { 0, 0, 0 } },
};

#endif

extern DamageTable D_80BB8170;
extern ColliderCylinderInit D_80BB8190;
extern ColliderCylinderInit D_80BB81BC;

extern UNK_TYPE D_06003450;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron2/EnTanron2_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron2/EnTanron2_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron2/func_80BB69C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron2/func_80BB69FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron2/func_80BB6B80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron2/func_80BB6BD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron2/func_80BB6F64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron2/func_80BB6F78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron2/func_80BB71C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron2/func_80BB7398.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron2/func_80BB7408.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron2/func_80BB7578.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron2/EnTanron2_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron2/func_80BB7B90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron2/EnTanron2_Draw.s")
