#include "z_en_look_nuts.h"

#define FLAGS 0x80000000

#define THIS ((EnLookNuts*)thisx)

void EnLookNuts_Init(Actor* thisx, GlobalContext* globalCtx);
void EnLookNuts_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnLookNuts_Update(Actor* thisx, GlobalContext* globalCtx);
void EnLookNuts_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Look_Nuts_InitVars = {
    ACTOR_EN_LOOK_NUTS,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_DNK,
    sizeof(EnLookNuts),
    (ActorFunc)EnLookNuts_Init,
    (ActorFunc)EnLookNuts_Destroy,
    (ActorFunc)EnLookNuts_Update,
    (ActorFunc)EnLookNuts_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80A68600 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_NONE, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
    { 20, 50, 0, { 0, 0, 0 } },
};

// static DamageTable sDamageTable = {
static DamageTable D_80A68630 = {
    /* Deku Nut       */ DMG_ENTRY(1, 0xF),
    /* Deku Stick     */ DMG_ENTRY(1, 0xF),
    /* Horse trample  */ DMG_ENTRY(1, 0xF),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(1, 0xF),
    /* Normal arrow   */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(1, 0xF),
    /* Hookshot       */ DMG_ENTRY(1, 0xE),
    /* Goron punch    */ DMG_ENTRY(1, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(1, 0xF),
    /* Fire arrow     */ DMG_ENTRY(1, 0xF),
    /* Ice arrow      */ DMG_ENTRY(1, 0xF),
    /* Light arrow    */ DMG_ENTRY(1, 0xF),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(1, 0xF),
    /* Deku bubble    */ DMG_ENTRY(1, 0xF),
    /* Deku launch    */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(1, 0xF),
    /* Zora barrier   */ DMG_ENTRY(1, 0xF),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0xF),
    /* Zora punch     */ DMG_ENTRY(1, 0xF),
    /* Spin attack    */ DMG_ENTRY(1, 0xF),
    /* Sword beam     */ DMG_ENTRY(1, 0xF),
    /* Normal Roll    */ DMG_ENTRY(0, 0xF),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0xF),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0xF),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(1, 0xF),
    /* Powder Keg     */ DMG_ENTRY(1, 0xF),
};

#endif

extern ColliderCylinderInit D_80A68600;
extern DamageTable D_80A68630;

extern UNK_TYPE D_06000430;
extern UNK_TYPE D_06002B6C;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Look_Nuts/EnLookNuts_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Look_Nuts/EnLookNuts_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Look_Nuts/func_80A67A34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Look_Nuts/func_80A67AA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Look_Nuts/func_80A67C48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Look_Nuts/func_80A67D0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Look_Nuts/func_80A67F30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Look_Nuts/func_80A67FC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Look_Nuts/func_80A68080.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Look_Nuts/func_80A680FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Look_Nuts/EnLookNuts_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Look_Nuts/EnLookNuts_Draw.s")
