#include "z_en_minislime.h"

#define FLAGS 0x00000235

#define THIS ((EnMinislime*)thisx)

void EnMinislime_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMinislime_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMinislime_Update(Actor* thisx, GlobalContext* globalCtx);

#if(0)
const ActorInit En_Minislime_InitVars = {
    ACTOR_EN_MINISLIME,
    ACTORCAT_BOSS,
    FLAGS,
    OBJECT_BIGSLIME,
    sizeof(EnMinislime),
    (ActorFunc)EnMinislime_Init,
    (ActorFunc)EnMinislime_Destroy,
    (ActorFunc)EnMinislime_Update,
    (ActorFunc)NULL,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_809857E0 = {
    { COLTYPE_NONE, AT_NONE | AT_TYPE_ENEMY, AC_NONE | AC_TYPE_PLAYER, OC1_NONE | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_HARD, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
    { 54, 60, -30, { 0, 0, 0 } },
};


// sColChkInfoInit
static CollisionCheckInfoInit D_8098580C = { 4, 40, 40, 30 };


// static DamageTable sDamageTable = {
static DamageTable D_80985814 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(1, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0xE),
    /* Goron punch    */ DMG_ENTRY(1, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(1, 0xF),
    /* Fire arrow     */ DMG_ENTRY(1, 0x2),
    /* Ice arrow      */ DMG_ENTRY(1, 0x3),
    /* Light arrow    */ DMG_ENTRY(1, 0x0),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(1, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(1, 0x0),
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


extern ColliderCylinderInit D_809857E0;
extern CollisionCheckInfoInit D_8098580C;
extern DamageTable D_80985814;
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/EnMinislime_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/EnMinislime_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_8098399C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_80983B38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_80983DBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_80983E9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_80983EB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_80983F1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_80984030.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_809840A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_8098419C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_8098420C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_80984248.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_80984410.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_80984450.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_809844FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_809845A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_8098470C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_80984748.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_80984964.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_809849C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_80984B34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_80984C28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_80984CA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_80984D08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_80984E38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_80984ECC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_80985018.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_80985088.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_80985154.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_80985168.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_8098518C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_809851E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_809852DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_8098537C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/func_80985480.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minislime_0x809838F0/EnMinislime_Update.asm")
