#include "z_en_geg.h"

#define FLAGS 0x00000019

#define THIS ((EnGeg*)thisx)

void EnGeg_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGeg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGeg_Update(Actor* thisx, GlobalContext* globalCtx);
void EnGeg_Draw(Actor* thisx, GlobalContext* globalCtx);

#if(0)
const ActorInit En_Geg_InitVars = {
    ACTOR_EN_GEG,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_OF1D_MAP,
    sizeof(EnGeg),
    (ActorFunc)EnGeg_Init,
    (ActorFunc)EnGeg_Destroy,
    (ActorFunc)EnGeg_Update,
    (ActorFunc)EnGeg_Draw,
};


// static ColliderSphereInit sSphereInit = {
static ColliderSphereInit D_80BB3E70 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_SPHERE, },
    { ELEMTYPE_UNK0, { 0x20000000, 0x00, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 0, { { 0, 0, 0 }, 0 }, 100 },
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BB3E9C = {
    { COLTYPE_HIT1, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 0, 0, 0, { 0, 0, 0 } },
};


// sColChkInfoInit
static CollisionCheckInfoInit2 D_80BB3EC8 = { 0, 0, 0, 0, MASS_IMMOVABLE };


// static DamageTable sDamageTable = {
static DamageTable D_80BB3ED4 = {
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


extern ColliderSphereInit D_80BB3E70;
extern ColliderCylinderInit D_80BB3E9C;
extern CollisionCheckInfoInit2 D_80BB3EC8;
extern DamageTable D_80BB3ED4;
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB16D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB178C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB18FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB19C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB1B14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB1C1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB1C8C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB1D04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB1D64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB1FCC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB2020.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB2088.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB217C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB221C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB2520.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB26EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB27D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB2944.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB2A54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB2B1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB2E00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB2F7C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB30B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB31B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB32AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB3318.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB347C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/EnGeg_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/EnGeg_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/EnGeg_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB3728.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB3860.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB387C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB39F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB3BE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/func_80BB3CB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Geg_0x80BB16D0/EnGeg_Draw.asm")
