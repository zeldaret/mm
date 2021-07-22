#include "z_en_dnk.h"

#define FLAGS 0x00000009

#define THIS ((EnDnk*)thisx)

void EnDnk_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDnk_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDnk_Update(Actor* thisx, GlobalContext* globalCtx);

#if(0)
const ActorInit En_Dnk_InitVars = {
    ACTOR_EN_DNK,
    ACTORCAT_NPC,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnDnk),
    (ActorFunc)EnDnk_Init,
    (ActorFunc)EnDnk_Destroy,
    (ActorFunc)EnDnk_Update,
    (ActorFunc)NULL,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80A521C4 = {
    { COLTYPE_HIT0, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 18, 46, 0, { 0, 0, 0 } },
};


// sColChkInfoInit
static CollisionCheckInfoInit2 D_80A521F0 = { 1, 0, 0, 0, MASS_IMMOVABLE };


// static DamageTable sDamageTable = {
static DamageTable D_80A521FC = {
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


extern ColliderCylinderInit D_80A521C4;
extern CollisionCheckInfoInit2 D_80A521F0;
extern DamageTable D_80A521FC;
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnk_0x80A514F0/func_80A514F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnk_0x80A514F0/func_80A515C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnk_0x80A514F0/func_80A51648.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnk_0x80A514F0/func_80A51890.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnk_0x80A514F0/func_80A518DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnk_0x80A514F0/EnDnk_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnk_0x80A514F0/EnDnk_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnk_0x80A514F0/EnDnk_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnk_0x80A514F0/func_80A51A78.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnk_0x80A514F0/func_80A51AA4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnk_0x80A514F0/func_80A51CB8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnk_0x80A514F0/func_80A51D78.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnk_0x80A514F0/func_80A51DA4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnk_0x80A514F0/func_80A51FC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnk_0x80A514F0/func_80A52018.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnk_0x80A514F0/func_80A52074.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dnk_0x80A514F0/func_80A52134.asm")
